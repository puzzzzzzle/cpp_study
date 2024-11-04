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
  char *c = static_cast<char *>(region.get_address());
  auto str = "hello world";
  strcpy(c, str);
}

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
TEST(managed_shm, 1) {
  bshm::managed_shared_memory managed_shm{bshm::open_or_create, "boost_shm_1",
                                          10240};
  bshm::remove_shared_memory_on_destroy rmGuard("boost_shm_1");
  int *i = managed_shm.construct<int>("Integer")(99);
  std::cout << *i << '\n';
  std::pair<int *, std::size_t> p = managed_shm.find<int>("Integer");
  if (p.first) std::cout << *p.first << '\n';

  typedef bshm::allocator<char, bshm::managed_shared_memory::segment_manager>
      CharAllocator;
  typedef bshm::basic_string<char, std::char_traits<char>, CharAllocator>
      string;

  string *s = managed_shm.find_or_construct<string>("String")(
      "Hello!", managed_shm.get_segment_manager());
  s->insert(5, ", world");
  std::cout << *s << '\n';
}

#include <boost/interprocess/offset_ptr.hpp>
TEST(offset_ptr,1)
{
  //Remove shared memory on construction and destruction
  struct shm_remove
  {
    shm_remove() { bshm::shared_memory_object::remove("MySharedMemory"); }
    ~shm_remove(){ bshm::shared_memory_object::remove("MySharedMemory"); }
  } remover;
  struct list_node
  {
    bshm::offset_ptr<list_node> next;
    int                   value;
  };

  //Create shared memory
  bshm::managed_shared_memory segment(bshm::create_only,
                                "MySharedMemory",  //segment_ name
                                65536);

  //Create linked list with 10 nodes in shared memory
  bshm::offset_ptr<list_node> prev = nullptr, current, first;

  int i;
  for(i = 0; i < 10; ++i, prev = current){
    current = static_cast<list_node*>(segment.allocate(sizeof(list_node)));
    current->value = i;
    current->next  = nullptr;

    if(!prev)
      first = current;
    else
      prev->next = current;
  }

  //Communicate list to other processes
  //. . .
  //When done, destroy list
  for(current = first; current; /**/){
    prev = current;
    current = current->next;
    segment.deallocate(prev.get());
  }
}