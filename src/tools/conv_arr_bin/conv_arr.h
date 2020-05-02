//
// Created by khalidzhang on 2020/5/2.
//

#pragma once

#include <fstream>
#include <opencv2/opencv.hpp>

#include "common_includes.h"

using namespace cv;
using namespace std;
#define UCHAR_MASK 0xFF
#define HTLOG_ERROR(msg) LOG_ERROR(msg)
#define HTLOG_DEBUG(msg) LOG_DEBUG(msg)

class ConfigBin {
public:
    int             m_width{}, m_height{}, m_sideLen{};
    unsigned char** m_data{};

public:
    void Init() {
        m_data = new unsigned char*[m_width];
        for (int x = 0; x < m_width; ++x) {
            m_data[x] = new unsigned char[m_height]{};
        }
    }
    ~ConfigBin() {
        if (m_data != nullptr) {
            for (int x = 0; x < m_width; ++x) {
                delete[] m_data[x];
            }
            delete[] m_data;
        }
    }

public:
    friend std::ostream& operator<<(std::ostream& oss, ConfigBin& bin) {
        int ret = bin.Save(oss);
        if (ret) {
            HTLOG_ERROR("Save fail")
            throw "Save file fail";
        }
        return oss;
    }
    friend std::istream& operator>>(std::istream& iss, ConfigBin& bin) {
        int ret = bin.Load(iss);
        if (ret) {
            HTLOG_ERROR("Load fail")
            throw "Load file fail";
        }
        return iss;
    }

public:
    int Load(std::istream& iss) {
        Read(iss, &m_width);
        Read(iss, &m_height);
        Read(iss, &m_sideLen);
        HTLOG_DEBUG("width\t" << m_width << "\theight\t" << m_height << "\tsideLen\t" << m_sideLen)
        if (m_data == nullptr) {
            Init();
        }
        for (int x = 0; x < m_width; ++x) {
            for (int y = 0; y < m_height; ++y) {
                if (iss.bad() || iss.eof()) {
                    HTLOG_ERROR("file is too short")
                    return -1;
                }
                Read(iss, &m_data[x][y]);
            }
        }
        unsigned char tmp{};
        Read(iss, &tmp);
        if (!iss.eof() || (int)tmp != 0) {
            HTLOG_ERROR("file is too long")
            return -1;
        }
        return 0;
    }
    int Save(std::ostream& oss) {
        Write(oss, &m_width);
        Write(oss, &m_height);
        Write(oss, &m_sideLen);
        for (int x = 0; x < m_width; ++x) {
            for (int y = 0; y < m_height; ++y) {
                Write(oss, &m_data[x][y]);
            }
        }
        return 0;
    }
    std::string ToString() {
        std::ostringstream oss{};
        oss << m_width << "," << m_height << "," << m_sideLen << "," << std::endl;
        for (int x = 0; x < m_width; ++x) {
            for (int y = 0; y < m_height; ++y) {
                oss << (int)m_data[x][y] << ",";
            }
            oss << std::endl;
        }
        return oss.str();
    }

private:
    template <typename T>
    void Read(std::istream& iss, T* out) {
        iss.read(reinterpret_cast<char*>(out), sizeof(T));
    }
    template <typename T>
    void Write(std::ostream& oss, T* out) {
        oss.write(reinterpret_cast<char*>(out), sizeof(T));
    }
};
class StaticGeographyConventHandle {
private:
    static int CheckPos(ConfigBin& bin, int startX, int startY, int diff) {
        for (int x = startX * diff; x < (startX + 1) * diff; ++x) {
            for (int y = startY * diff; y < (startY + 1) * diff; ++y) {
                if (bin.m_data[x][y] == 1) {
                    return 1;
                }
            }
        }
        return 0;
    }
    static int CheckPosFalse(ConfigBin& bin, int startX, int startY, int diff) {
        for (int x = startX * diff; x < (startX + 1) * diff; ++x) {
            for (int y = startY * diff; y < (startY + 1) * diff; ++y) {
                if (bin.m_data[x][y] == 0) {
                    return 1;
                }
            }
        }
        return 0;
    }

public:
    static int LoadBin(std::string fileName, ConfigBin* outBin) {
        std::ifstream inFile(fileName);
        if (!inFile.is_open()) {
            HTLOG_ERROR("open file fail " << fileName)
            return -1;
        }
        int ret = outBin->Load(inFile);
        if (ret) {
            HTLOG_ERROR("load file fail " << ret)
            return ret;
        }
        return 0;
    }
    static int LoadStaticConfig(std::string fileName, ConfigBin* outBin) {
        ConfigBin bin{};
        if (LoadBin(fileName, &bin)) {
            HTLOG_ERROR("load fail")
            return -1;
        }
        // 加载完成, 进行转换
        if (outBin->m_width == 0 || outBin->m_height == 0) {
            HTLOG_ERROR("outBin->m_width==0||outBin->m_height==0")
            return -1;
        }
        if (bin.m_width % outBin->m_width != 0 || bin.m_height % outBin->m_height != 0) {
            HTLOG_ERROR("bin.m_width %  outBin->m_width != 0 || bin.m_height %  outBin->m_height != 0")
            //            return -1;
        }
        if ((bin.m_width / outBin->m_width) != (bin.m_height / outBin->m_height)) {
            HTLOG_ERROR("( outBin->m_width/width) != ( outBin->m_height/height)")
            return -1;
        }
        int diff = bin.m_width / outBin->m_width;
        if (outBin->m_data == nullptr) {
            outBin->Init();
        }
        for (int x = 0; x < outBin->m_width; ++x) {
            for (int y = 0; y < outBin->m_height; ++y) {
                (*outBin).m_data[x][y] = CheckPosFalse(bin, x, y, diff);
            }
        }
        return 0;
    }
};
class ConvArr {
public:
    static Scalar GetRGBA(unsigned int color) {
        return Scalar((color >> 0) & UCHAR_MASK, (color >> 8) & UCHAR_MASK, (color >> 16) & UCHAR_MASK,
                      (color >> 24) & UCHAR_MASK);
    }

    static void AddGrid(Mat mat, int gridGap, Scalar gridColor) {
        for (int x = 0; x < mat.cols; ++x) {
            for (int y = 0; y < mat.rows; ++y) {
                if ((x % gridGap) == 0 || (y % gridGap) == 0) {
                    mat.col(x).row(y) = gridColor;
                }
            }
        }
    }
    static void DrawPos(Mat mat, int binX, int binY, int gap, const Scalar& s) {
        for (int x = binX * gap; x < binX * gap + gap; ++x) {
            for (int y = binY * gap; y < binY * gap + gap; ++y) {
                mat.col(x).row(y) = s;
            }
        }
    }
    static void DrawBorder(Mat mat, Point start, Point len, Scalar s, int bordersize) {
        rectangle(mat, start, len, s, bordersize, LINE_8);
    }
    static void PrintBin(Mat mat, const ConfigBin& bin, int gap, map<int, Scalar>& colors) {
        assert(gap >= 1);
        assert(mat.cols >= bin.m_width && mat.rows >= bin.m_height);
        assert(mat.cols >= bin.m_width * gap && mat.rows >= bin.m_height * gap);
        LOG_DEBUG(gap)
        for (int x = 0; x < bin.m_width; ++x) {
            for (int y = 0; y < bin.m_height; ++y) {
                if (bin.m_data[x][y] == 0) {
                    continue;
                }
                //                LOG_DEBUG("draw bin pos "<< x<<","<<y)
                DrawPos(mat, x, y, gap, colors[bin.m_data[x][y]]);
                //                                                    mat.col(x).row(y) = colors[bin.m_data[x][y]];
            }
        }
    }
    static void FlipMat(Mat* mat) {
        Mat tmp(mat->rows, mat->cols, CV_8UC3, Scalar::all(0));
        flip(*mat, tmp, 0);
        *mat = tmp;
    }
};