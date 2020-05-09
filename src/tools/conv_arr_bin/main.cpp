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
        COLOR_UNKNOWN      = 0,
        COLOR_BASE         = 1,
        COLOR_GRID         = 2,
        COLOR_STATIC_BLOCK = 3,
        COLOR_LINE         = 4,
        COLOR_CITY         = 5,
        COLOR_BORDER       = 6,

    };
    ToolControl() {
        colors[COLOR_BASE]         = ConvArr::GetRGBA(0xBBFFFF);
        colors[COLOR_GRID]         = ConvArr::GetRGBA(0x696969);
        colors[COLOR_STATIC_BLOCK] = ConvArr::GetRGBA(0xFF4500);
        colors[COLOR_LINE]         = ConvArr::GetRGBA(0x696969);
        colors[COLOR_CITY]         = ConvArr::GetRGBA(0x696969);
        colors[COLOR_BORDER]       = ConvArr::GetRGBA(0x4876FF);
    }
    int DrawBin(const ConfigBin &bin, Mat *outMat) {
        Mat mat(bin.m_height * bin.m_sideLen, bin.m_width * bin.m_sideLen, CV_8UC3, colors[COLOR_BASE]);
        LOG_DEBUG("width\t" << bin.m_width << "\theight\t" << bin.m_height << "\tgap\t" << bin.m_sideLen);
        ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors[COLOR_STATIC_BLOCK]);
        ConvArr::AddGrid(mat, 100, colors[COLOR_GRID]);
        ConvArr::DrawBorder(mat, Point(0, 0), Point(mat.cols, mat.rows), colors[COLOR_BORDER], 3);
        (*outMat) = mat;
        return 0;
    }
};

int BuildOptions(opt::variables_map *vm, opt::options_description *gloabl, int argc, char **argv) {
    opt::options_description help("help");
    help.add_options()("help,h", "show all operations");

    opt::options_description geography("geography cmds");

    geography.add_options()("file,f", opt::value<std::vector<std::string>>()->required(),
                            R"(map bin files,multi file will be processed in order
file also can be defined at args
eg: tools_conv_arr_bin file1 file2
    or tools_conv_arr_bin -ffile1 -f file2)");
    geography.add_options()("outfile,o", opt::value<std::string>()->default_value("out.jpg"),
                            "out put image file, eg:out.jpg");
    geography.add_options()("cmd,c", opt::value<std::string>()->default_value("show")->required(),
                            R"(process type
show : conv all bin to pic
conv : conv all bin and change first to server type
raw : show origin bin data)");
    geography.add_options()("gap,g", opt::value<int>()->required()->default_value(1), "each grid size of first layer");
    geography.add_options()("color",opt::value<std::vector<string>>(),
        R"(
color define: key:value
        COLOR_BASE         = 1,
        COLOR_GRID         = 2,
        COLOR_STATIC_BLOCK = 3,
        COLOR_LINE         = 4,
        COLOR_CITY         = 5,
        COLOR_BORDER       = 6,
defaule color:
        colors[COLOR_BASE]         = ConvArr::GetRGBA(0xBBFFFF);
        colors[COLOR_GRID]         = ConvArr::GetRGBA(0x696969);
        colors[COLOR_STATIC_BLOCK] = ConvArr::GetRGBA(0xFF4500);
        colors[COLOR_LINE]         = ConvArr::GetRGBA(0x696969);
        colors[COLOR_CITY]         = ConvArr::GetRGBA(0x696969);
        colors[COLOR_BORDER]       = ConvArr::GetRGBA(0x4876FF);
)");
    gloabl->add(help).add(geography);
    opt::positional_options_description p{};
    p.add("file", -1);

    opt::store(opt::command_line_parser(argc, argv).options(*gloabl).positional(p).run(), *vm);
    opt::notify(*vm);
    return 0;
}

int RunCmd(const opt::variables_map &vm, opt::options_description *gloabl) {
    ToolControl control{};
    if (vm.empty()) {
        LOG_ERROR("no para " << *gloabl)
        return 0;
    }

    if (vm.count("help")) {
        LOG_DEBUG(*gloabl)
        return 0;
    }
    if(vm.count("color")){
        for(auto color : vm["color"].as<std::vector<uint64>>()){
            HTLOG_ERROR("unsupported! color "<< color)
        }
    }
    Mat         mat{};
    int         gap   = vm["gap"].as<int>();
    std::string cmd   = vm["cmd"].as<std::string>();
    std::string out   = vm["outfile"].as<std::string>();
    auto        files = vm["file"].as<std::vector<std::string>>();
    int         i     = 0;
    for (auto file : files) {
        if (i == 0) {
            ConfigBin bin{}, tmp{};
            CALL_IF_RETURN(StaticGeographyConventHandle::LoadBin(file, &tmp));

            if ("show" == cmd) {
                LOG_INFO("show origin data")
                bin.m_width  = tmp.m_width;
                bin.m_height = tmp.m_height;
                CALL_IF_RETURN(StaticGeographyConventHandle::LoadStaticConfig(file, &bin));
                control.DrawBin(bin, &mat);
            } else if ("conv" == cmd) {
                LOG_INFO("conv data with gap " << gap)
                bin.m_width  = tmp.m_width / gap;
                bin.m_height = tmp.m_height / gap;
                CALL_IF_RETURN(StaticGeographyConventHandle::LoadStaticConfig(file, &bin));
                control.DrawBin(bin, &mat);
            } else if ("raw" == cmd) {
                //                LOG_INFO("conv data with gap " << gap)
                //                bin.m_width  = tmp.m_width / gap;
                //                bin.m_height = tmp.m_height / gap;
                //                CALL_IF_RETURN(StaticGeographyConventHandle::LoadStaticConfig(file, &bin));
                control.DrawBin(tmp, &mat);
            }

        } else {
            HTLOG_ERROR("multi file not support now " << file)
        }
        ++i;
    }
    //    HTLOG_DEBUG("flip pic")
    //    ConvArr::FlipMat(&mat);
    HTLOG_DEBUG("write pic to file " << out)
    CALL_IF_RETURN(!imwrite(out, mat));
    HTLOG_DEBUG("file write to " << out);
    return 0;
}

int main(int argc, char **argv) {
    CALL_IF_RETURN(beforeRun());
    //    iRet = RunTest(argc, argv);
    std::string desc =
        R"(bigWorld server map tools
usage: tools_conv_arr_bin [options] files...
good luck!!!)";
    opt::options_description opts(desc);
    opt::variables_map       vm{};

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