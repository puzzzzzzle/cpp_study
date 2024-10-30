/**
可以恢复不带指针, 可以带虚函数的对象
即使函数内容/地址发生变更, 也可以恢复, 只要内存结构不变就行

但有以下限制:

1. 需要有默认构造函数, 且:

如果没有虚函数, 加载后不调用构造函数, 当然,
可以通过need_refresh_vtable=true强制调用

如果有虚函数, 必须有默认构造函数,
默认构造函数不能初始化类变量, 也不能用{}初始化类成员, 不然load上来会被覆盖

2. 不能有指针成员, vector map 等包含指针的成员也不行, 不然会野指针

**/

#pragma once
#include <filesystem>
#include <format>
#include <fstream>

// 如果有全局重载 operator new 的话, 可以在类中放一个这个宏, 隔离全局的重载
// 一般没用, 全局重载new操作符是不被推荐的行为
#define NULL_PLACEMENT_NEW()                              \
  void* operator new(size_t, const void* pThis) throw() { \
    if (!pThis) {                                         \
      return nullptr;                                     \
    }                                                     \
    return (void*)pThis;                                  \
  }

template <class T>
T* recreate_obj(void* ptr, bool need_refresh_vtable) {
  if (std::is_polymorphic<T>::value || need_refresh_vtable) {
    // placement new, 刷新vtable, 防止二进制地址变化
    return new (ptr) T;
  }
  return (T*)ptr;
}
template <class T>
void write_to_file(const T* obj, const std::string& file_path) {
  using namespace std;
  using namespace std::filesystem;
  // 路径校验
  path p(file_path);
  path parent = absolute(p).parent_path();
  if (!exists(parent) || !is_directory(parent)) {
    throw ios::failure(
        format("parent path not exists or parent path is not directory, path "
               "{}, parent {}",
               p.string(), parent.string()));
  }
  // 出错就抛异常
  ofstream fs(p, ios::out | ios::trunc | ios::binary);
  if (!fs.is_open()) {
    throw ios::failure(format("open fail fail, path {}", p.string()));
  }
  // 写入大小
  auto obj_size = (streamsize)sizeof(T);
  fs.write(reinterpret_cast<const char*>(&obj_size), sizeof(obj_size));
  if (fs.fail()) {
    throw ios::failure(format("write size fail, path {}", p.string()));
  }
  // 写入内容
  fs.write(reinterpret_cast<const char*>(obj), obj_size);
  if (fs.fail()) {
    throw ios::failure(format("write data fail, path {}", p.string()));
  }
  // 主动关闭下, 方便调试, 退出析构时也会关闭
  fs.close();
}
/**
 *
 * @tparam T
 * @param file_path 源文件
 * @param out_obj 目标位置
 * @param need_refresh_vtable 是否调用构造函数重新构造下, 注意,
 * 在默认构造函数/有{}初始化的类变量, 会被覆盖
 */
template <class T>
void load_from_file(const std::string& file_path, void* out_obj,
                    bool need_refresh_vtable = false) {
  using namespace std;
  using namespace std::filesystem;
  // 路径校验
  path p(file_path);
  if (!exists(p) || !is_regular_file(p)) {
    throw ios::failure(
        format("file not exists or not regular file, path {}", p.string()));
  }
  // 出错就抛异常
  ifstream fs(p, ios::in | ios::binary);
  if (!fs.is_open()) {
    throw ios::failure(format("open fail fail, path {}", p.string()));
  }
  // 大小校验
  auto obj_size = (streamsize)sizeof(T);
  streamsize file_obj_size{};
  fs.read(reinterpret_cast<char*>(&file_obj_size), sizeof(file_obj_size));
  if (fs.fail()) {
    throw ios::failure(format("read size fail, path {}", p.string()));
  }
  if (file_obj_size != obj_size) {
    throw ios::failure(format(
        "obj size not match, maybe obj mem changed, path {}", p.string()));
  }
  // 读取内容
  fs.read(reinterpret_cast<char*>(out_obj), sizeof(T));
  if (fs.fail()) {
    throw ios::failure(format("read data fail, path {}", p.string()));
  }
  // 按需刷新内存
  recreate_obj<T>(out_obj, need_refresh_vtable);
}
template <class T>
void load_from_file(const std::string& file_path, T* out_obj,
                    bool need_refresh_vtable = false) {
  load_from_file<T>(file_path, (void*)out_obj, need_refresh_vtable);
}
template <class T>
T* load_from_file(const std::string& file_path,
                  bool need_refresh_vtable = false) {
  // 直接构造内存, 恢复数据, 不调用构造函数, 晚点placement new 时再调用
  T* buff = new T;
  load_from_file<T>(file_path, (void*)buff, need_refresh_vtable);
  return buff;
}