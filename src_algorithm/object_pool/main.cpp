//
// Created by tao on 19-1-17.
//
#include <ctime>

#include "ObjectPool.h"
#include "common_classes.h"
#include "common_includes.h"
#include "CommonClass.h"

struct DefaultObjectConstructor {
  using ObjectT = OperatorLogClass;
  void operator()(ObjectT *object) const {
    assert(object->data == nullptr);
    object->name = std::to_string(time(nullptr));
    object->data = new char[100];
    snprintf(object->data, 100, "%s", object->name.c_str());
    LOG_DEBUG("++  " << object->ToString())
  }
};
struct DefaultObjectDestructor {
  using ObjectT = OperatorLogClass;
  void operator()(ObjectT *object) const {
    LOG_DEBUG("--  " << object->ToString())
    object->name = "";
    delete[] object->data;
    object->data = nullptr;
  }
};

using MyPool = ObjectPoolImpl::ObjectPool<
    OperatorLogClass, ObjectPoolImpl::QueuePoolType<OperatorLogClass *>, 5,
    DefaultObjectConstructor, DefaultObjectDestructor>;
static MyPool pool{};
using MyManulPool = ObjectPoolImpl::ObjectManualPool<
    OperatorLogClass,
    ObjectPoolImpl::QueuePoolType<std::shared_ptr<OperatorLogClass>>, 5,
    DefaultObjectConstructor, DefaultObjectDestructor>;
static MyManulPool manulPool{};

TEST(one_class, auto_pool) {
  std::atomic_bool test{false};
  for (int i = 0; i < 10; ++i) {
    auto obj = pool.Alloc();
  }
}
TEST(multi_alloc, auto_pool) {
  std::vector<MyPool::ObjectPtrT> vec{};
  for (int i = 0; i < 10; ++i) {
    auto obj = pool.Alloc();
    vec.push_back(obj);
  }
}
TEST(rand_alloc, auto_pool) {
  std::vector<MyPool::ObjectPtrT> vec{};
  for (int i = 0; i < 30; ++i) {
    auto obj = pool.Alloc();
    if ((rand() * 100) > 50) {
      LOG_DEBUG("add to vec")
      vec.push_back(obj);
    } else {
      LOG_DEBUG("ignore")
    }
  }
}
TEST(one_class, manul_pool) {
  std::atomic_bool test{false};
  for (int i = 0; i < 10; ++i) {
    auto obj = manulPool.Alloc();
  }
}
TEST(one_class_re, manul_pool) {
  std::atomic_bool test{false};
  for (int i = 0; i < 10; ++i) {
    auto obj = manulPool.Alloc();
    manulPool.TryPushBack(obj);
    ASSERT_TRUE(obj == nullptr);
  }
}
TEST(multi_alloc_re, manul_pool) {
  std::vector<MyPool::ObjectPtrT> vec{};
  for (int i = 0; i < 10; ++i) {
    auto obj = manulPool.Alloc();
    vec.push_back(obj);
  }
  for (auto &ptr : vec) {
    manulPool.TryPushBack(ptr);
    ASSERT_TRUE(ptr == nullptr);
  }
}

TEST(rand_alloc, manul_pool) {
  std::vector<MyPool::ObjectPtrT> vec{};
  for (int i = 0; i < 30; ++i) {
    auto obj = manulPool.Alloc();
    if ((rand() * 100) > 50) {
      LOG_DEBUG("add to vec")
      vec.push_back(obj);
    } else {
      LOG_DEBUG("ignore")
    }
  }
}
TEST(big_alloc, 1) {
  using BigPool = ObjectPoolImpl::ObjectManualPool<
      OperatorLogClass,
      ObjectPoolImpl::QueuePoolType<std::shared_ptr<OperatorLogClass>>, 10000,
      DefaultObjectConstructor, DefaultObjectDestructor>;
  BigPool bigPool{};
  std::vector<MyPool::ObjectPtrT> vec{};
  for (int i = 0; i < 30; ++i) {
    auto obj = bigPool.Alloc();
    if ((rand() * 100) > 50) {
      LOG_DEBUG("add to vec")
      vec.push_back(obj);
    } else {
      LOG_DEBUG("ignore")
      bigPool.TryPushBack(obj);
      ASSERT_TRUE(obj == nullptr);
    }
  }
  for (auto &ptr : vec) {
    bigPool.TryPushBack(ptr);
    ASSERT_TRUE(ptr == nullptr);
  }
}
int main(int argc, char **argv) {
  int iRet = 0;
  iRet = beforeRun();
  if (iRet) {
    std::cerr << "init fail with " << iRet << std::endl;
  }
  testing::InitGoogleTest(&argc, argv);
  iRet = RUN_ALL_TESTS();
  return iRet;
}