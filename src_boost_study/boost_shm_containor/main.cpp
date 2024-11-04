#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/errors.hpp>

#include "common_includes.h"
#include "shm_mng.h"

namespace bip = boost::interprocess;
using namespace ShmMng;

template <class T>
using shm_vector = bip::vector<T, shm_allocator_t<T>>;
using shm_string = bip::string;
class LargeObj {
  public:
  char buff_[2048];
  LargeObj() = default;
  template <typename Allocator>
  LargeObj(const Allocator &) {}
};
class Obj {
  public:
  int val1_{};
  double val2_{};
  Obj() = default;
  Obj(int val1, double val2) : val1_(val1), val2_(val2) {}
  std::string ToString() const {
    return std::format("val1: {} ; val2: {}", val1_, val2_);
  }
  // 接受 allocator 的构造函数
  template <typename Allocator>
  Obj(const Allocator &) : val1_(0), val2_(0) {}
};

TEST(raw_shm, save) {
  static constexpr char name[] = "raw_shm.shm";
  bip::shared_memory_object::remove(name);
  bip::managed_shared_memory segment(bip::open_or_create, name, 0xffff);

  //  shm_allocator_t<shm_vector<Obj>> alloc(segment.get_segment_manager());
  //  auto *vec1 = segment.construct<shm_vector<Obj>>("vec1")(alloc);
  //  vec1->emplace_back(11, 22.5);

  shm_allocator_t<Obj> obj_alloc(segment.get_segment_manager());
  Obj *obj1{};
  auto obj_find = segment.find<Obj>("obj1");
  if (obj_find.first == nullptr) {
    obj1 = segment.construct<Obj>("obj1")(obj_alloc);
  } else {
    // 正常只能找到一个, obj_find.second 表示内存大小/单个对象的内存大小
    ASSERT_TRUE(obj_find.second == 1);
    obj1 = obj_find.first;
  }
  LOG_DEBUG("obj: " << obj1->ToString());
  obj1->val2_ = 222.5;
  obj1->val1_ = rand() % 1000;
  LOG_DEBUG("obj: " << obj1->ToString());

  // 在同一个名字上申请不同的类型查找, 可以找到,
  // 但是其实就是把内存强转为新的类型的指针
  // boost 额外要求: 必须能被查找的类型整除, 不然就assert fail

  auto int_find = segment.find<int>("obj1");
  ASSERT_TRUE(int_find.first != nullptr);
  ASSERT_TRUE(int_find.second == sizeof(Obj) / sizeof(int));
  segment.construct<int>("int_obj")();

  // 在同一个名字上重复构造, 会报错, 无论类型是否对的上
  bool errored = false;
  try {
    obj1 = segment.construct<Obj>("obj1")(obj_alloc);
  } catch (const std::exception &e) {
    LOG_DEBUG("got err " << e.what())
    errored = true;
  }
  ASSERT_TRUE(errored);

  // error: 类型错误, 且比原始内容大时, 无法整除, 直接crash(assert fail)
  //  shm_allocator_t<LargeObj> large_alloc(segment.get_segment_manager());
  //  auto large_obj_find = segment.find<LargeObj>("obj1");

  LOG_DEBUG("end")
}
TEST(shm_vector_manual_instance, load_save) {
  static constexpr char name[] = "shm_vector_manual_instance.shm";
  bip::shared_memory_object::remove(name);

  {
    using ShmVecMng = ShmContainerMng<Obj, shm_vector, bip::open_or_create_t>;
    ShmVecMng instance{};
    instance.Init(name, 0xffff);
    auto *vec = instance.Get("test1");
    vec->emplace_back(rand() % 1000, 22.5);
    for (const auto &item : *vec) {
      LOG_DEBUG("vec item : " << item.ToString());
    }
  }

  // 在同一个名字重新加载, 类型变化, 类似指针强转了
  {
    using ShmIntMng = ShmObjMng<int, bip::open_or_create_t>;
    ShmIntMng intInstance{};
    intInstance.Init(name, 0xffff);
    // int 比 Obj小, 且大小可以整除, 所以可以获取到地址, 但是数量不是1
    auto *val = intInstance.Get("test1", false);
    ASSERT_TRUE(val != nullptr);
    // 这里额外检查了大小, 且对不上时不自动删除创建, 就获取不到了
    val = intInstance.Get("test1", false, true);
    ASSERT_TRUE(val == nullptr);

    // 这里额外检查了大小, 没对上, 就重新创建了
    val = intInstance.Get("test1", true, true);
    ASSERT_TRUE(val != nullptr);
  }
}
TEST(shm_obj_singleton, load_save) {
  static constexpr char name[] = "shm_obj_singleton.shm";
  using ShmObj = ShmObjMngSingleton<Obj, bip::open_or_create_t, name, 0xffff>;
  auto obj1 = ShmObj::GetInstance().Get("test1");
}
TEST(shm_vector_singleton, load_save) {
  //  bip::shared_memory_object::remove(name);
  static constexpr char name[] = "shm_vector.shm";
  using ShmVec = ShmContainerSingleton<Obj, shm_vector, bip::open_or_create_t,
                                       name, 0xffff>;
  auto *vec = ShmVec::GetInstance().Get("vec1");
  vec->emplace_back(rand() % 1000, 22.5);
  for (const auto &item : *vec) {
    LOG_DEBUG("vec item : " << item.ToString());
  }
}
TEST(shm_map_singleton, load_save) {
  //  bip::shared_memory_object::remove(name);
  static constexpr char name[] = "shm_map.shm";
  using ShmMap =
      ShmMapMngSingleton<int, Obj, bip::open_or_create_t, name, 0xffff>;
  auto &map = *ShmMap::GetInstance().Get("map1");
  int key = rand() % 1000;
  map[key] = Obj(key, 444.0);
  for (const auto &[k,v] : map) {
    LOG_DEBUG("map item : " << k << "\t" << v.ToString());
  }
}
int main(int argc, char **argv) {
  int iRet = 0;

  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}