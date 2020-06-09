//
// Created by tao on 19-1-17.
//
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>

#include "common_includes.h"
#include "conv_arr.h"
namespace opt = boost::program_options;

static const std::string PIC_BASE = "./data/pictures/";

int RunTest(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
class ToolControl {
  public:
  std::map<int, Scalar> colors{};
  enum ColorDef {
    COLOR_UNKNOWN = 0,
    COLOR_BASE = 1,
    COLOR_GRID = 2,
    COLOR_STATIC_BLOCK = 3,
    COLOR_LINE = 4,
    COLOR_CITY = 5,
    COLOR_BORDER = 6,

  };
  ToolControl() {
    colors[COLOR_BASE] = ConvArr::GetRGBA(0xBBFFFF);
    colors[COLOR_GRID] = ConvArr::GetRGBA(0x696969);
    colors[COLOR_STATIC_BLOCK] = ConvArr::GetRGBA(0xFF4500);
    colors[COLOR_LINE] = ConvArr::GetRGBA(0x0000FF);
    colors[COLOR_CITY] = ConvArr::GetRGBA(0xFF00FF);
    colors[COLOR_BORDER] = ConvArr::GetRGBA(0x4876FF);
  }
  int DrawBin(const ConfigBin &bin, Mat *outMat, bool needGrid) {
    Mat mat(bin.m_height * bin.m_sideLen, bin.m_width * bin.m_sideLen, CV_8UC3,
            colors[COLOR_BASE]);
    LOG_DEBUG("width\t" << bin.m_width << "\theight\t" << bin.m_height
                        << "\tgap\t" << bin.m_sideLen);
    ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors[COLOR_STATIC_BLOCK]);
    if (needGrid) {
      ConvArr::AddGrid(mat, 100, colors[COLOR_GRID]);
      ConvArr::DrawBorder(mat, Point(0, 0), Point(mat.cols, mat.rows),
                          colors[COLOR_BORDER], 3);
    }

    (*outMat) = mat;
    return 0;
  }
  void DrawRec(Mat &mat, const Point &start, const Point &offset) {
    HTLOG_DEBUG("draw rec " << start << "\t" << offset)
    ConvArr::DrawRec(mat, start, offset, colors[COLOR_CITY]);
  }
  void DrawLine(Mat &mat, const std::vector<Point> &linePoints) {
    HTLOG_DEBUG("draw line " << linePoints)
    ConvArr::DrawLine(mat, linePoints, colors[COLOR_LINE]);
  }
};
static void SplitStdString(const string &src, const string &separator,
                           vector<string> &dest) {
  string str = src;
  string substring;
  string::size_type start{0}, index{0};
  dest.clear();
  index = str.find_first_of(separator, start);
  do {
    if (index != string::npos) {
      substring = str.substr(start, index - start);
      dest.push_back(substring);
      start = index + separator.size();
      index = str.find(separator, start);
      if (start == string::npos) break;
    }
  } while (index != string::npos);

  // the last part
  substring = str.substr(start);
  dest.push_back(substring);
}
int BuildOptions(opt::variables_map *vm, opt::options_description *gloabl,
                 int argc, char **argv) {
  opt::options_description help("help");
  help.add_options()("help,h", "show all operations");

  opt::options_description geography("geography cmds");

  geography.add_options()(
      "file,f", opt::value<std::vector<std::string>>()->required(),
      R"(map bin files,multi file will be processed in order
file also can be defined at args
eg: tools_conv_arr_bin file1 file2
    or tools_conv_arr_bin -ffile1 -f file2)");
  geography.add_options()("outfile,o",
                          opt::value<std::string>()->default_value("out.jpg"),
                          "out put image file, eg:out.jpg");
  geography.add_options()("cmd,c",
                          opt::value<std::string>()->default_value("show"),
                          R"(process type
show : conv all bin to pic
conv : conv all bin and change first to server type
raw : show origin bin data)");
  geography.add_options()("gap,g", opt::value<int>()->default_value(1),
                          "each grid size of first layer");

  geography.add_options()("grid",
                          opt::value<bool>()->default_value(true)->required(),
                          "need grid and border");

  geography.add_options()("city", opt::value<std::vector<string>>(),
                          R"(draw a city with pos:size
eg: --city 100,100:2,2)");
  geography.add_options()("line", opt::value<std::vector<string>>(),
                          R"(draw a line with pos:pos:pos...
eg: --line 100,100:500,500:100,500)");
  geography.add_options()("build-fake", opt::value<int>(),
                          R"(build a fake bin file)");
  geography.add_options()("color", opt::value<std::vector<string>>(),
                          R"(color define: key:value)");
  gloabl->add(help).add(geography);
  opt::positional_options_description p{};
  p.add("file", -1);

  opt::store(
      opt::command_line_parser(argc, argv).options(*gloabl).positional(p).run(),
      *vm);
  opt::notify(*vm);
  return 0;
}

int DrawBinCmd(Mat &mat, const opt::variables_map &vm, ToolControl &control) {
  int gap = vm["gap"].as<int>();
  std::string cmd = vm["cmd"].as<std::string>();
  auto files = vm["file"].as<std::vector<std::string>>();
  int i = 0;
  bool needGrid = vm["grid"].as<bool>();

  for (auto file : files) {
    if (i == 0) {
      ConfigBin bin{}, tmp{};
      CALL_IF_RETURN(StaticGeographyConventHandle::LoadBin(file, &tmp));

      if ("show" == cmd) {
        LOG_INFO("show origin data")
        bin.m_width = tmp.m_width;
        bin.m_height = tmp.m_height;
        CALL_IF_RETURN(
            StaticGeographyConventHandle::LoadStaticConfig(file, &bin));
        control.DrawBin(bin, &mat, needGrid);
      } else if ("conv" == cmd) {
        LOG_INFO("conv data with gap " << gap)
        bin.m_width = tmp.m_width / gap;
        bin.m_height = tmp.m_height / gap;
        CALL_IF_RETURN(
            StaticGeographyConventHandle::LoadStaticConfig(file, &bin));
        control.DrawBin(bin, &mat, needGrid);
      } else if ("raw" == cmd) {
        //                LOG_INFO("conv data with gap " << gap)
        //                bin.m_width  = tmp.m_width / gap;
        //                bin.m_height = tmp.m_height / gap;
        //                CALL_IF_RETURN(StaticGeographyConventHandle::LoadStaticConfig(file,
        //                &bin));
        control.DrawBin(tmp, &mat, needGrid);
      }

    } else {
      HTLOG_ERROR("multi file not support now " << file)
    }
    ++i;
  }
  return 0;
}
int DrawCityCmd(Mat &mat, const opt::variables_map &vm, ToolControl &control) {
  if (vm.count("city") == 0) {
    return 0;
  }
  auto citys = vm["city"].as<std::vector<std::string>>();

  for (const auto &city : citys) {
    std::vector<std::string> pointStrings{};
    SplitStdString(city, ":", pointStrings);
    if (pointStrings.size() != 2) {
      HTLOG_ERROR("pointStrings.size()!=2 " << city)
      return -1;
    }
    std::vector<Point> pos{};
    for (auto pointStr : pointStrings) {
      std::vector<std::string> posValueStrings{};
      SplitStdString(pointStr, ",", posValueStrings);
      if (posValueStrings.size() != 2) {
        HTLOG_ERROR("posValueStrings.size()!=2 " << pointStr)
        return -1;
      }
      Point point{};
      point.x = atoi(posValueStrings[0].c_str());
      point.y = atoi(posValueStrings[1].c_str());
      pos.push_back(point);
    }
    if (pos.size() != 2) {
      HTLOG_ERROR("pos.size()!=2")
      return -1;
    }
    control.DrawRec(mat, pos[0], pos[1]);
  }
  return 0;
}
int DrawLineCmd(Mat &mat, const opt::variables_map &vm, ToolControl &control) {
  if (vm.count("line") == 0) {
    return 0;
  }
  auto lines = vm["line"].as<std::vector<std::string>>();

  for (const auto &line : lines) {
    std::vector<std::string> pointStrings{};
    SplitStdString(line, ":", pointStrings);
    if (pointStrings.size() < 2) {
      HTLOG_ERROR("pointStrings.size()<2 " << line)
      return -1;
    }
    std::vector<Point> pos{};
    for (auto pointStr : pointStrings) {
      std::vector<std::string> posValueStrings{};
      SplitStdString(pointStr, ",", posValueStrings);
      if (posValueStrings.size() != 2) {
        HTLOG_ERROR("posValueStrings.size()!=2 " << pointStr)
        return -1;
      }
      Point point{};
      point.x = atoi(posValueStrings[0].c_str());
      point.y = atoi(posValueStrings[1].c_str());
      pos.push_back(point);
    }
    if (pos.size() < 2) {
      HTLOG_ERROR("pos.size()<2")
      return -1;
    }
    control.DrawLine(mat, pos);
  }
  return 0;
}
int RunCmd(const opt::variables_map &vm, opt::options_description *gloabl) {
  if (vm.empty()) {
    LOG_ERROR("no para " << *gloabl)
    return 0;
  }
  if (vm.count("help")) {
    LOG_DEBUG(*gloabl)
    return 0;
  }
  if (vm.count("build-fake")) {
    int size = vm["build-fake"].as<int>();
    ConfigBin fakeBin{};
    fakeBin.m_width = size;
    fakeBin.m_height = size;
    fakeBin.m_sideLen = 1;
    fakeBin.Init();
    auto files = vm["file"].as<std::vector<std::string>>();
    std::ofstream ofs(files[0], std::ios::binary | std::ios::trunc);
    if (!ofs.is_open()) {
      HTLOG_ERROR("open file fail " << files[0])

      return -1;
    }
    fakeBin.Save(ofs);
    return 0;
  }
  ToolControl control{};
  Mat mat{};
  CALL_IF_RETURN(DrawBinCmd(mat, vm, control))
  CALL_IF_RETURN(DrawCityCmd(mat, vm, control))
  CALL_IF_RETURN(DrawLineCmd(mat, vm, control))

  std::string out = vm["outfile"].as<std::string>();
  HTLOG_DEBUG("flip pic")
  ConvArr::FlipMat(&mat);
  HTLOG_DEBUG("write pic to file " << out)
  CALL_IF_RETURN(!imwrite(out, mat));
  HTLOG_DEBUG("file write to " << out);
  return 0;
}

void BuildFakeMap() {
  ConfigBin bin{};
  bin.m_height = 12288;
  bin.m_width = 12288;
  bin.m_sideLen = 1;
  bin.Init();
  std::ofstream ofs("fakeMap.data", ios::trunc | ios::binary);
  assert(ofs.is_open());
  bin.Save(ofs);
}
int main(int argc, char **argv) {
  CALL_IF_RETURN(beforeRun());
  //    iRet = RunTest(argc, argv);
  //    BuildFakeMap();
  //    return 0;
  std::string desc =
      R"(bigWorld server map tools
usage: tools_conv_arr_bin [options] files...
good luck!!!)";
  opt::options_description opts(desc);
  opt::variables_map vm{};

  try {
    CALL_IF_RETURN(BuildOptions(&vm, &opts, argc, argv));
  } catch (opt::required_option &e) {
    LOG_RAW_CLINE(opts)
    LOG_RAW_CLINE("error :need option " << e.get_option_name())

    return -1;
  } catch (exception &e) {
    LOG_RAW_CLINE("args wrong! " << e.what())
    LOG_RAW_CLINE(opts)
    return -1;
  } catch (...) {
    LOG_RAW_CLINE("args wrong!")
    LOG_RAW_CLINE(opts)
    return -1;
  }
  CALL_IF_RETURN(RunCmd(vm, &opts));

  return 0;
}