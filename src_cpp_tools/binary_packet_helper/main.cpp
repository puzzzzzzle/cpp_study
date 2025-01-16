#include "common_includes.h"
#include "binary_packet_file_operator.h"

int main() {
  // 创建一些数据包
  const char* packet1 = "Hello";
  uint32_t length1 = 5;

  const char* packet2 = "World";
  uint32_t length2 = 5;

  // 打开文件进行写入
  std::ofstream ofs("packets.bin", std::ios::binary);
  if (!ofs) {
    std::cerr << "Failed to open file for writing" << std::endl;
    return 1;
  }

  // 写入包
  writePacket(ofs, packet1, length1);
  writePacket(ofs, packet2, length2);

  ofs.close();

  // 打开文件进行读取
  std::ifstream ifs("packets.bin", std::ios::binary);
  if (!ifs) {
    std::cerr << "Failed to open file for reading" << std::endl;
    return 1;
  }

  // 读取包
  const uint32_t bufferSize = 1024;
  char buffer[bufferSize];
  uint32_t length;

  if (readPacket(ifs, buffer, bufferSize, length)) {
    std::cout << "Read packet 1: ";
    for (uint32_t i = 0; i < length; ++i) {
      std::cout << buffer[i];
    }
    std::cout << std::endl;
  }

  if (readPacket(ifs, buffer, bufferSize, length)) {
    std::cout << "Read packet 2: ";
    for (uint32_t i = 0; i < length; ++i) {
      std::cout << buffer[i];
    }
    std::cout << std::endl;
  }

  ifs.close();

  return 0;
}