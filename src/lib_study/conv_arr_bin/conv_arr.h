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

#include "BinFileHolder.h"

class ConvArr {
  public:
  static Scalar GetRGBA(unsigned int color) {
    return Scalar((color >> 0) & UCHAR_MASK, (color >> 8) & UCHAR_MASK,
                  (color >> 16) & UCHAR_MASK, (color >> 24) & UCHAR_MASK);
  }

  static void AddGrid(Mat& mat, int gridGap, Scalar gridColor) {
    for (int x = 0; x < mat.cols; ++x) {
      for (int y = 0; y < mat.rows; ++y) {
        if ((x % gridGap) == 0 || (y % gridGap) == 0) {
          mat.col(x).row(y) = gridColor;
        }
      }
    }
  }
  static void DrawPos(Mat& mat, int binX, int binY, int gap, const Scalar& s) {
    for (int x = binX * gap; x < binX * gap + gap; ++x) {
      for (int y = binY * gap; y < binY * gap + gap; ++y) {
        mat.col(x).row(y) = s;
      }
    }
  }
  static void DrawBorder(Mat& mat, Point start, Point len, const Scalar& s,
                         int bordersize) {
    rectangle(mat, start, len, s, bordersize, LINE_8);
  }
  static void DrawRec(Mat& mat, const Point& start, const Point& offset,
                      const Scalar& s) {
    rectangle(mat, start, Point(start.x + offset.x, start.y + offset.y), s, -1,
              LINE_8);
  }
  static void DrawLine(Mat& mat, const std::vector<Point>& linePoints,
                       const Scalar& s) {
    for (int i = 0; i < linePoints.size() - 1; ++i) {
      cv::line(mat, linePoints[i], linePoints[i + 1], s, 1);
    }
  }
  static void PrintBin(Mat& mat, const ConfigBin& bin, int gap,
                       const Scalar& s) {
    LOG_DEBUG("start print bin")
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
        DrawPos(mat, x, y, gap, s);
        //                                                    mat.col(x).row(y)
        //                                                    =
        //                                                    colors[bin.m_data[x][y]];
      }
    }
    LOG_DEBUG("Finish print bin")
  }
  static void FlipMat(Mat* mat) {
    Mat tmp(mat->rows, mat->cols, CV_8UC3, Scalar::all(0));
    flip(*mat, tmp, 0);
    *mat = tmp;
  }
};