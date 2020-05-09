//
// Created by tao on 19-1-17.
//
#include <opencv2/opencv.hpp>

#include "common_includes.h"

static const std::string PIC_BASE  = "./data/pictures/";
static const std::string READ_FILE = PIC_BASE + "/read.webp";
static const std::string GRAY_FILE = PIC_BASE + "/gray.jpg";

TEST(test_test, 1) { EXPECT_EQ(1, 1); }
using namespace cv;
using namespace std;

Scalar GetRGB(double r, double g, double b) { return Scalar(b, g, r); }
TEST(opencv_1, rw) {
    Mat img{};
    img = imread(READ_FILE, IMREAD_COLOR);
    ASSERT_TRUE(img.data);

    Mat gray{};
    cvtColor(img, gray, COLOR_BGR2GRAY);
    ASSERT_TRUE(imwrite(GRAY_FILE, gray));

    //    namedWindow(READ_FILE, WINDOW_AUTOSIZE);
    //    namedWindow("Gray image", WINDOW_AUTOSIZE);
    //
    //    imshow(READ_FILE, img);
    //    imshow("Gray image", gray);
}

TEST(opencv_1, arr) {
    Scalar base  = GetRGB(187, 255, 255);
    Scalar black = GetRGB(0, 0, 0);
    Scalar white = GetRGB(255, 255, 255);

    {
        Mat img(50, 100, CV_8UC3, base);
        for (int x = 0; x < img.cols; ++x) {
            for (int y = 0; y < img.rows; ++y) {
                if (x == 50) {
                    img.col(x).row(y) = black;
                }
            }
        }
        ASSERT_TRUE(imwrite(PIC_BASE + "/arr_x_50.jpg", img));
    }

    {
        Mat img(50, 100, CV_8UC3, base);
        for (int x = 0; x < img.cols; ++x) {
            for (int y = 0; y < img.rows; ++y) {
                if (x == 0 && y == 0) {
                    img.col(x).row(y) = black;
                }
            }
        }
        ASSERT_TRUE(imwrite(PIC_BASE + "/arr_0_0.jpg", img));
    }

    {
        Mat img(50, 100, CV_8UC3, base);
        for (int x = 0; x < img.cols; ++x) {
            for (int y = 0; y < img.rows; ++y) {
                if (x == 0) {
                    img.col(x).row(y) = black;
                }
            }
        }
        ASSERT_TRUE(imwrite(PIC_BASE + "/arr_x_0.jpg", img));
    }
    {
        Mat img(50, 100, CV_8UC3, base);
        for (int x = 0; x < img.cols; ++x) {
            for (int y = 0; y < img.rows; ++y) {
                if (y == 0) {
                    img.col(x).row(y) = black;
                }
            }
        }
        ASSERT_TRUE(imwrite(PIC_BASE + "/arr_y_0.jpg", img));
    }

    {
        Mat img(50, 100, CV_8UC3, base);
        for (int x = 0; x < img.cols; ++x) {
            for (int y = 0; y < img.rows; ++y) {
                if (y == x) {
                    img.col(x).row(y) = black;
                }
            }
        }
        ASSERT_TRUE(imwrite(PIC_BASE + "/arr_y_x.jpg", img));
    }
    //    cout << "M = " << endl << " " << M << endl << endl;

    //    namedWindow(READ_FILE, WINDOW_AUTOSIZE);
    //    namedWindow("Gray image", WINDOW_AUTOSIZE);
    //
    //    imshow(READ_FILE, img);
    //    imshow("Gray image", gray);
}
TEST(opencv_1, basic) {
    Mat a{}, c{};
    a = imread(READ_FILE, IMREAD_COLOR);

    Mat b(a);

    c = a;
    Mat d(a, Rect(10, 10, 100, 100));      // using a rectangle
    Mat e = a(Range::all(), Range(1, 3));  // using row and column boundaries

    Mat M(5, 2, CV_8UC3, Scalar(0, 0, 255));
    cout << "M = " << endl << " " << M << endl << endl;
}
//TEST(grid, test) {
//    LOG_DEBUG("#BBFFFF\t" << ConvArr::GetRGBA(0xBBFFFF))
//    Mat mat(3000, 4000, CV_8UC3, ConvArr::GetRGBA(0xBBFFFF));
//    ConvArr::AddGrid(mat, 100, ConvArr::GetRGBA(0x696969));
//    ConfigBin bin{};
//    fakeBin(&bin, 400, 300);
//    bin.m_sideLen = 10;
//    //    ASSERT_EQ(StaticGeographyConventHandle::LoadBin(PIC_BASE + "/in.data", &bin), 0);
//    std::map<int, Scalar> colors{};
//    colors[1] = ConvArr::GetRGBA(0xFF4500);
//    ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors);
//    ASSERT_TRUE(imwrite(PIC_BASE + "/test.jpg", mat));
//}
//
//TEST(conv_test, conv) {
//    Mat mat(3000, 4000, CV_8UC3, ConvArr::GetRGBA(0xBBFFFF));
//    ConvArr::AddGrid(mat, 100, ConvArr::GetRGBA(0x696969));
//    ConfigBin bin{};
//    //    fakeBin(&bin, 400, 300);
//    //    bin.m_sideLen=10;
//    bin.m_width   = 204;
//    bin.m_height  = 204;
//    bin.m_sideLen = 10;
//
//    ASSERT_EQ(StaticGeographyConventHandle::LoadStaticConfig(PIC_BASE + "/in.data", &bin), 0);
//    std::map<int, Scalar> colors{};
//    colors[1] = ConvArr::GetRGBA(0xFF4500);
//
//    ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors);
//    ConvArr::DrawBorder(mat, Point(0, 0), Point(2048, 2048), ConvArr::GetRGBA(0x4876FF), 3);
//
//    ConvArr::FlipMat(&mat);
//
//    ASSERT_TRUE(imwrite(PIC_BASE + "/conv.jpg", mat));
//}
//
//TEST(conv_test, in) {
//    Mat mat(3000, 4000, CV_8UC3, ConvArr::GetRGBA(0xBBFFFF));
//    ConvArr::AddGrid(mat, 100, ConvArr::GetRGBA(0x696969));
//    ConfigBin bin{};
//    //    fakeBin(&bin, 400, 300);
//    //    bin.m_sideLen=10;
//    bin.m_width   = 2048;
//    bin.m_height  = 2048;
//    bin.m_sideLen = 1;
//
//    ASSERT_EQ(StaticGeographyConventHandle::LoadStaticConfig(PIC_BASE + "/in.data", &bin), 0);
//    std::map<int, Scalar> colors{};
//    colors[1] = ConvArr::GetRGBA(0xFF4500);
//    ConvArr::PrintBin(mat, bin, bin.m_sideLen, colors);
//    ConvArr::DrawBorder(mat, Point(0, 0), Point(2048, 2048), ConvArr::GetRGBA(0x4876FF), 3);
//
//    ConvArr::FlipMat(&mat);
//
//    ASSERT_TRUE(imwrite(PIC_BASE + "/in.jpg", mat));
//}
int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}