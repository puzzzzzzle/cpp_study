//
// Created by tao on 23-2-28.
//
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "common_includes.h"
namespace bshm = boost::interprocess;

TEST(shm_test, 1) {
  // linux 一般使用 posix 共享内存 系统, 即在/dev/shm上创建文件, 然后mmap
  // shm_open(name) -> open("/dev/shm/name")
  bshm::shared_memory_object mem(bshm::open_or_create, "boost_shm_1",
                                 bshm::read_write);
  // shm_unlink(name) -> unlink("/dev/shm/name")
  bshm::remove_shared_memory_on_destroy rmGuard("boost_shm_1");
  mem.truncate(10240);

  // mmap
  bshm::mapped_region region(mem, bshm::read_write);
  char* c = static_cast<char*>(region.get_address());
  auto str = "hello world";
  memcpy(c,str, strlen(str));

}