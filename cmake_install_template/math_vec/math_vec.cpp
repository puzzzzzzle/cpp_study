//
// Created by root on 10/11/25.
//

#include "math_vec.h"
#include <zlib.h>
#include <filesystem>
#include <fstream>
#include <format>

#if MATH_VEC_HAVE_LIBPNG

#include <png.h>

#endif

void MathVec::load_from_bin_file(const std::string &path) {
    std::filesystem::path file(path);
    if (!exists(file) || !is_regular_file(file)) {
        throw std::runtime_error(std::format("File({}) not found!", path));
    }

    std::fstream in_file(file, std::ios::in | std::ios::binary);
    if (!in_file.is_open()) {
        throw std::runtime_error(std::format("File({}) bad!", path));
    }
    // 全部读取到内存
    in_file.seekg(0, std::ios::end);
    size_t file_size = in_file.tellg();
    in_file.seekg(0, std::ios::beg);
    std::vector<char> file_data(file_size);
    in_file.read(file_data.data(), file_size);
    if (!!in_file.good()) {
        throw std::runtime_error(std::format("File({}) read fail!", path));
    }
    in_file.close();
    load_from_memory(file_data);
}

void MathVec::load_from_zip_file(const std::string &path) {
    gzFile gz_file = gzopen(path.c_str(), "rb");
    if (!gz_file) {
        throw std::runtime_error("Cannot open gzip file: " + path);
    }

    std::vector<char> file_data;
    char buffer[4096];
    int bytes_read = 0;
    while ((bytes_read = gzread(gz_file, buffer, sizeof(buffer))) > 0) {
        file_data.insert(file_data.end(), buffer, buffer + bytes_read);
    }
    gzclose(gz_file);

    load_from_memory(file_data);
}

void MathVec::load_from_memory(const std::vector<char> &memory) {
// TODO
}

#if MATH_VEC_HAVE_LIBPNG

void MathVec::load_from_png_file(const std::string &path) {
    FILE *fp = fopen(path.c_str(), "rb");
    if (!fp) {
        throw std::runtime_error(std::format("File({}) not found!", path));
    }

    // 检查PNG签名
    png_byte header[8];
    fread(header, 1, 8, fp);
    if (png_sig_cmp(header, 0, 8)) {
        fclose(fp);
        throw std::runtime_error(std::format("File({}) is not a PNG!", path));
    }

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) {
        fclose(fp);
        throw std::runtime_error("png_create_read_struct failed");
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, nullptr, nullptr);
        fclose(fp);
        throw std::runtime_error("png_create_info_struct failed");
    }
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        fclose(fp);
        throw std::runtime_error("Error during png reading");
    }
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    int width      = png_get_image_width(png_ptr, info_ptr);
    int height     = png_get_image_height(png_ptr, info_ptr);
    int color_type = png_get_color_type(png_ptr, info_ptr);
    int bit_depth  = png_get_bit_depth(png_ptr, info_ptr);

    // 转换到 8 bit RGBA
    if (bit_depth == 16)
        png_set_strip_16(png_ptr);
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);
    // 灰度转RGB
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);
    // Alpha通道补齐
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);
    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER); // 不带 alpha的，强行补FF

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(png_ptr);

    png_read_update_info(png_ptr, info_ptr);

    // 最终一行的字节数
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);

    // 逐行读取
    std::vector<png_byte> image_data(rowbytes * height);
    std::vector<png_bytep> row_pointers(height);
    for (int y = 0; y < height; ++y) {
        row_pointers[y] = &image_data[y * rowbytes];
    }
    png_read_image(png_ptr, row_pointers.data());
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
    fclose(fp);

    //转化为1维
    data_ = std::vector<uint8_t>(image_data.begin(), image_data.end());
    shape_ = {width,height,4};
}

#endif
