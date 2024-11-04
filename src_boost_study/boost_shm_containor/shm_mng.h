/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc boost shm 的包装, 可以通过 自定义的实例/单例方便的访问shm
 * 使用容器时, 需要类似的特化下
 * template <class T>
 * using shm_vector = bip::vector<T, shm_allocator<T>>;
 * 字符串请使用shm版本的
 * using shm_string = bip::string;
 * @time 2024-11-04
 * @file shm_mng.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/
#pragma once
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

namespace ShmMng {
namespace bip = boost::interprocess;

template <class T, class Enable = void>
struct shm_allocator;

// 特化用于非基本类型
template <class T>
struct shm_allocator<
    T, typename std::enable_if<!std::is_fundamental<T>::value>::type> {
  using type = bip::allocator<T, bip::managed_shared_memory::segment_manager>;
};

// 特化用于基本类型
template <class T>
struct shm_allocator<
    T, typename std::enable_if<std::is_fundamental<T>::value>::type> {
  using type =
      bip::allocator<void, bip::managed_shared_memory::segment_manager>;
};

// 统一访问接口
template <class T>
using shm_allocator_t = typename shm_allocator<T>::type;

template <typename ShmCreateType, typename ObjAllocT, typename ManagedTypeT>
class ShmObjMngBase {
  public:
  using ManagedType = ManagedTypeT;
  using ObjAlloc = ObjAllocT;

  private:
  ObjAlloc *alloc_{};
  bip::managed_shared_memory segment_{};

  public:
  ~ShmObjMngBase() {
    delete alloc_;
    alloc_ = nullptr;
  }
  void Init(const char *ShmName, size_t ShmMaxSize) {
    segment_ = bip::managed_shared_memory(ShmCreateType(), ShmName, ShmMaxSize);
    alloc_ = new ObjAlloc(segment_.get_segment_manager());
  }

  /**
   * 对象名字, 需要唯一
   * 类型加名字唯一确定一个对象, 对不上就类似指针强转了
   * @param objName
   * @return
   */
  ManagedType *Get(const char *objName, bool autoCreate = true,
                   bool safeGet = false) {
    if (safeGet) {
      auto ret = segment_.find<char>(objName);
      // 已经存在的, 检查内存大小对的上
      if (ret.first != nullptr && ret.second != sizeof(ManagedType)) {
        // 内存大小对不上了
        if (!autoCreate) {
          return nullptr;
        }
        // 清理掉旧的, 重新创建
        Destroy(objName);
      }
    }
    auto ret = segment_.find<ManagedType>(objName);
    if (ret.first != nullptr) {
      return ret.first;
    }
    if (!autoCreate) {
      return nullptr;
    }
    return segment_.construct<ManagedType>(objName)(*alloc_);
  }
  /**
   * 按名字删除, 不管类型
   * @param objName
   */
  void Destroy(const char *objName) { segment_.destroy<ManagedType>(objName); }
  bip::managed_shared_memory *GetShm() { return &segment_; }
  ObjAlloc *GetAlloc() { return alloc_; }
};

// 普通对象适配, 必须满足放在shm上的对象要求
template <typename T, typename ShmCreateType>
using ShmObjMng =
    ShmObjMngBase<ShmCreateType, shm_allocator_t<T>, T>;

// 标准容器适配, vector set list 等
template <typename ValueType, template <typename> typename ContainerType,
          typename ShmCreateType>
using ShmContainerMng =
    ShmObjMngBase<ShmCreateType,
                  typename ContainerType<ValueType>::allocator_type,
                  ContainerType<ValueType>>;

// 特化用于 类似 map 类型的 Key Value 容器
template <class K, class V, class CMP = std::less<K>,
          class Options = boost::container::tree_assoc_defaults>
using shm_map =
    bip::map<K, V, CMP, shm_allocator_t<std::pair<const K, V>>,
             Options>;
template <typename KeyType, typename ValueType, typename ShmCreateType,
          typename CMP = std::less<KeyType>,
          class Options = boost::container::tree_assoc_defaults>
using ShmMapMng = ShmObjMngBase<
    ShmCreateType,
    typename shm_map<KeyType, ValueType, CMP, Options>::allocator_type,
    shm_map<KeyType, ValueType, CMP, Options>>;
// 单例模式
template <typename T>
class Singleton {
  public:
  // disable copy
  Singleton(const Singleton &) = delete;
  Singleton &operator=(const Singleton &) = delete;

  // get instance
  static T &GetInstance() {
    static T instance{};
    return instance;
  }

  protected:
  // disable construct
  Singleton() = default;
  virtual ~Singleton() = default;
};

// 普通对象单例特化
template <typename T, typename ShmCreateType, const char *ShmName,
          size_t ShmMaxSize>
class ShmObjMngSingleton
    : public ShmObjMng<T, ShmCreateType>,
      public Singleton<
          ShmObjMngSingleton<T, ShmCreateType, ShmName, ShmMaxSize>> {
  // allow Singleton visit protected: ShmContainerSingleton()
  friend class Singleton<
      ShmObjMngSingleton<T, ShmCreateType, ShmName, ShmMaxSize>>;

  protected:
  ShmObjMngSingleton() {
    ShmObjMng<T, ShmCreateType>::Init(ShmName, ShmMaxSize);
  }
};
// 单值容器单例特化
template <typename ValueType, template <typename> typename ContainerType,
          typename ShmCreateType, const char *ShmName, size_t ShmMaxSize>
class ShmContainerSingleton
    : public ShmContainerMng<ValueType, ContainerType, ShmCreateType>,
      public Singleton<ShmContainerSingleton<
          ValueType, ContainerType, ShmCreateType, ShmName, ShmMaxSize>> {
  // allow Singleton visit protected: ShmContainerSingleton()
  friend class Singleton<ShmContainerSingleton<
      ValueType, ContainerType, ShmCreateType, ShmName, ShmMaxSize>>;

  protected:
  ShmContainerSingleton() {
    ShmContainerMng<ValueType, ContainerType, ShmCreateType>::Init(ShmName,
                                                                   ShmMaxSize);
  }
};
// map 单例特化
template <typename KeyType, typename ValueType, typename ShmCreateType,
          const char *ShmName, size_t ShmMaxSize,
          typename CMP = std::less<KeyType>,
          class Options = boost::container::tree_assoc_defaults>
class ShmMapMngSingleton
    : public ShmMapMng<KeyType, ValueType, ShmCreateType, CMP, Options>,
      public Singleton<ShmMapMngSingleton<KeyType, ValueType, ShmCreateType,
                                          ShmName, ShmMaxSize, CMP, Options>> {
  // allow Singleton visit protected: ShmContainerSingleton()
  friend class Singleton<ShmMapMngSingleton<KeyType, ValueType, ShmCreateType,
                                            ShmName, ShmMaxSize, CMP, Options>>;

  protected:
  ShmMapMngSingleton() {
    ShmMapMng<KeyType, ValueType, ShmCreateType, CMP, Options>::Init(
        ShmName, ShmMaxSize);
  }
};
}  // namespace ShmMng