/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc 可重置的可写文件
 * 注意性能较低, 具体看磁盘性能, 我的云服务器大概1200+/s左右的写入
 * @time 2021/6/24
 * @file truncatable_file.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#include <cstdio>
#include <iostream>
#include <string>
inline char *mutable_string_data(std::string *s) { return &(*s)[0]; }
inline char *remake_mutable_string_data(std::string *s, size_t size) {
  s->clear();
  s->resize(size);
  return mutable_string_data(s);
}

class TruncatableFile {
  private:
  FILE *fs_{};
  std::string name_{};
  size_t default_size_{0};
  int open_file() {
    if (fs_ != nullptr) {
      fclose(fs_);
    }
    // 不存在就创建
    {
      fs_ = fopen(name_.c_str(), "ab+");
      fclose(fs_);
    }
    fs_ = fopen(name_.c_str(), "rb+");
    return fs_ != nullptr ? 0 : -1;
  }

  public:
  ~TruncatableFile() {
    if (fs_ != nullptr) {
      fclose(fs_);
      fs_ = nullptr;
    }
  }
  FILE *fs() { return fs_; }
  int init(const std::string &file, size_t default_size = 0) {
    name_ = file;
    default_size_ = default_size;
    return open_file();
  }
  int truncate_file() {
    assert(fs_ != nullptr);
    fseek(fs_, 0, SEEK_SET);
    auto ret = ftruncate(fs_->_fileno, default_size_);
    fseek(fs_, 0, SEEK_SET);
    return ret;
  }
  int truncate_write(const char *buf, size_t n) {
    assert(fs_ != nullptr);
    truncate_file();
    auto ret = fwrite(buf, sizeof(char), n, fs_);
    fflush(fs_);
    return ret == n ? 0 : -1;
  }
  // 只是使用string 作为容器
  std::string read_all() {
    assert(fs_ != nullptr);
    fseek(fs_, 0, SEEK_END);
    size_t length = ftell(fs_);
    fseek(fs_, 0, SEEK_SET);
    if (length <= 0) {
      return "";
    }
    std::string result{};
    char *data = remake_mutable_string_data(&result, length);
    size_t read_size = fread(data, sizeof(char), length, fs_);
    assert(read_size == length);
    return result;
  }
};