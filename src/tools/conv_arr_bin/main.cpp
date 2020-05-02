//
// Created by tao on 19-1-17.
//
#include <boost/foreach.hpp>
#include <boost/program_options.hpp>

#include "common_includes.h"
#include "conv_arr.h"
namespace opt = boost::program_options;

static const std::string PIC_BASE = "./data/pictures/";

#define CALL_IF_RET(caller)                                                                                            \
    {                                                                                                                  \
        int iRet = caller;                                                                                             \
        if (iRet) {                                                                                                    \
            LOG_ERROR("call  fail " << #caller << "\tret\t" << iRet);                                                  \
        }                                                                                                              \
    }

TEST(test_test, 1) { EXPECT_EQ(1, 1); }

void AddBorder(ConfigBin *bin, int size) {
    for (int x = 0; x < bin->m_width; ++x) {
        for (int y = 0; y < bin->m_height; ++y) {
            if (x <= size || y <= size) {
                bin->m_data[x][y] = 2;
            }
            if (x >= bin->m_width - size || y >= bin->m_height - size) {
                bin->m_data[x][y] = 2;
            }
        }
    }
}
void fakeBin(ConfigBin *bin, int width, int height) {
    bin->m_width   = width;
    bin->m_height  = height;
    bin->m_sideLen = 1;
    bin->Init();
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (x <= 10 || y <= 10) {
                bin->m_data[x][y] = 1;
            }
            if (x >= bin->m_width - 10 || y >= bin->m_height - 10) {
                bin->m_data[x][y] = 1;
            }
            if (x == y) {
                bin->m_data[x][y] = 1;
            }
        }
    }
}
TEST(grid, test) {
    LOG_DEBUG("#BBFFFF\t" << ConvArr::GetRGBA(0xBBFFFF))
    Mat mat(3000, 4000, CV_8UC3, ConvArr::GetRGBA(0xBBFFFF));
    ConvArr::AddGrid(mat, 100, ConvArr::GetRGBA(0x696969));
    ConfigBin bin{};
    fakeBin(&bin, 400, 300);
    bin.m_sideLen = 10;
    //    ASSERT_EQ(StaticGeographyConventHandle::LoadBin(PIC_BASE + "/in.data", &bin), 0);
    std::map<int, Scalar> colors{};
    colors[1] = ConvArr::GetRGBA(0xFF4500);
    ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors);
    ASSERT_TRUE(imwrite(PIC_BASE + "/test.jpg", mat));
}

TEST(conv_test, conv) {
    Mat mat(3000, 4000, CV_8UC3, ConvArr::GetRGBA(0xBBFFFF));
    ConvArr::AddGrid(mat, 100, ConvArr::GetRGBA(0x696969));
    ConfigBin bin{};
    //    fakeBin(&bin, 400, 300);
    //    bin.m_sideLen=10;
    bin.m_width   = 204;
    bin.m_height  = 204;
    bin.m_sideLen = 10;

    ASSERT_EQ(StaticGeographyConventHandle::LoadStaticConfig(PIC_BASE + "/in.data", &bin), 0);
    std::map<int, Scalar> colors{};
    colors[1] = ConvArr::GetRGBA(0xFF4500);

    ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors);
    ConvArr::DrawBorder(mat, Point(0, 0), Point(2048, 2048), ConvArr::GetRGBA(0x4876FF), 3);

    ConvArr::FlipMat(&mat);

    ASSERT_TRUE(imwrite(PIC_BASE + "/conv.jpg", mat));
}

TEST(conv_test, in) {
    Mat mat(3000, 4000, CV_8UC3, ConvArr::GetRGBA(0xBBFFFF));
    ConvArr::AddGrid(mat, 100, ConvArr::GetRGBA(0x696969));
    ConfigBin bin{};
    //    fakeBin(&bin, 400, 300);
    //    bin.m_sideLen=10;
    bin.m_width   = 2048;
    bin.m_height  = 2048;
    bin.m_sideLen = 1;

    ASSERT_EQ(StaticGeographyConventHandle::LoadStaticConfig(PIC_BASE + "/in.data", &bin), 0);
    std::map<int, Scalar> colors{};
    colors[1] = ConvArr::GetRGBA(0xFF4500);
    ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors);
    ConvArr::DrawBorder(mat, Point(0, 0), Point(2048, 2048), ConvArr::GetRGBA(0x4876FF), 3);

    ConvArr::FlipMat(&mat);

    ASSERT_TRUE(imwrite(PIC_BASE + "/in.jpg", mat));
}
int RunTest(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
int DrawBin(const ConfigBin &bin, Mat *outMat) {
    Mat mat(bin.m_height * bin.m_sideLen, bin.m_width * bin.m_sideLen, CV_8UC3, ConvArr::GetRGBA(0xBBFFFF));
    LOG_DEBUG("width * << bin.m_width "
              << "\theight\t" << bin.m_height << "\tgap\t" << bin.m_sideLen);
    ConvArr::AddGrid(mat, 100, ConvArr::GetRGBA(0x696969));
    std::map<int, Scalar> colors{};
    colors[1] = ConvArr::GetRGBA(0xFF4500);
    ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors);
    ConvArr::DrawBorder(mat, Point(0, 0), Point(2048, 2048), ConvArr::GetRGBA(0x4876FF), 3);
    (*outMat) = mat;
    return 0;
}
int BuildOptions(opt::variables_map *vm, opt::options_description *gloabl, int argc, char **argv) {
    opt::options_description help("help");
    help.add_options()("help,h", "show all operations");

    opt::options_description geography("geography cmds");

    geography.add_options()("file,f", opt::value<std::vector<std::string>>(),
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
)");
    geography.add_options()("gap,g", opt::value<int>()->required(), "each grid size of first layer");

    gloabl->add(help).add(geography);
    opt::positional_options_description p{};
    p.add("file", -1);

    opt::store(opt::command_line_parser(argc, argv).options(*gloabl).positional(p).run(), *vm);
    return 0;
}
int RunCmd(const opt::variables_map &vm, opt::options_description *gloabl) {
    if (vm.empty()) {
        LOG_DEBUG("no para " << *gloabl)
        return 0;
    }

    if (vm.count("help")) {
        LOG_DEBUG(*gloabl)
        return 0;
    }

    Mat         mat;
    int         gap = vm["gap"].as<int>();
    std::string cmd = vm["cmd"].as<std::string>();
    std::string out = vm["outfile"].as<std::string>();

    if (vm.count("file")) {
        auto files = vm["file"].as<std::vector<std::string>>();
        int  i     = 0;
        for (auto file : files) {
            if (i == 0) {
                ConfigBin bin{}, tmp{};
                CALL_IF_RET(StaticGeographyConventHandle::LoadBin(file, &tmp));

                if ("show" == cmd) {
                    bin.m_width  = tmp.m_width;
                    bin.m_height = tmp.m_height;
                } else if ("conv" == cmd) {
                    bin.m_width  = tmp.m_width / gap;
                    bin.m_height = tmp.m_height / gap;
                }
                CALL_IF_RET(StaticGeographyConventHandle::LoadStaticConfig(file, &bin));
                DrawBin(bin, &mat);
            }

            ++i;
        }
    } else {
        LOG_DEBUG("no bin file def, so ignore")
    }
    ConvArr::FlipMat(&mat);

    CALL_IF_RET(imwrite(out, mat) != true);

    HTLOG_DEBUG("file write to " << out);
    return 0;
}
int main(int argc, char **argv) {
    CALL_IF_RET(beforeRun());
    //    iRet = RunTest(argc, argv);
    std::string desc =
        R"(    bigWorld server map tools
usage: tools_conv_arr_bin [options] files...
good luck!!!)";
    opt::options_description opts(desc);
    opt::variables_map       vm{};

    CALL_IF_RET(BuildOptions(&vm, &opts, argc, argv));
    CALL_IF_RET(RunCmd(vm, &opts));
    return 0;
}