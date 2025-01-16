#include <iostream>
#include <fstream>

// 写入带长度的char数组到文件
void writePacket(std::ofstream& ofs, const char* data, uint32_t length) {
  // 写入包的长度
  ofs.write(reinterpret_cast<const char*>(&length), sizeof(length));
  // 写入包的数据
  ofs.write(data, length);
}

// 从文件读取带长度的char数组
bool readPacket(std::ifstream& ifs, char* buffer, uint32_t bufferSize, uint32_t& length) {
  // 读取包的长度
  if (!ifs.read(reinterpret_cast<char*>(&length), sizeof(length))) {
    return false; // 读取失败，可能是文件结束
  }
  // 检查缓冲区是否足够大
  if (length > bufferSize) {
    std::cerr << "Buffer size is too small" << std::endl;
    return false;
  }
  // 读取包的数据
  if (!ifs.read(buffer, length)) {
    return false; // 读取失败
  }
  return true;
}