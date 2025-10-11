//
// Created by root on 10/11/25.
//

#ifndef CPP_STUDY_MATH_VEC_H
#define CPP_STUDY_MATH_VEC_H

#include <string>
#include <vector>
#include <cstdint>

class MathVec {
public:
    void load_from_memory(const std::vector<char> &memory);

    void load_from_bin_file(const std::string &path);

    void load_from_zip_file(const std::string &path);

#if MATH_VEC_HAVE_LIBPNG

    void load_from_png_file(const std::string &path);

#endif
public:
    std::vector<int64_t> shape_{};
//    std::vector<float> data_{};
    std::vector<uint8_t> data_{};

};

#endif  // CPP_STUDY_MATH_VEC_H
