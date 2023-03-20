/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc 通过string 名字动态创建c++类的简单反射的实现
 * @time 2021/5/24
 * @file cpp_reflact.hpp
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/
#pragma once

#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

typedef void *(*PTRCreateObject)(void);

class CppObjectFactory {
  private:
  map<string, PTRCreateObject> m_ClassMap;

  CppObjectFactory(){};

  public:
  /**
   * 通过注册的类名创建一个类
   * eg:  auto* ptr =
   * (Base*)CppObjectFactory::getInstance().getClassByName("Sub");
   * @param className
   * @return
   */
  void *getClassByName(string className) {
    map<string, PTRCreateObject>::const_iterator iter;
    iter = m_ClassMap.find(className);
    if (iter == m_ClassMap.end())
      return NULL;
    else
      return iter->second();
  }

  /**
   * 注册一个类
   * @param name 类名
   * @param method 可以创建一个这个类的函数指针, 注意 返回的是void* ,
   * 用的地方自己转
   * @return
   */
  bool registClass(string name, PTRCreateObject method) {
    std::cout << "ret class " << name << "\t i_func address " << (size_t)method
              << std::endl;
    return m_ClassMap.insert(pair<string, PTRCreateObject>(name, method))
        .second;
  }

  void *operator[](string className) { return getClassByName(className); }

  /**
   * 单例模式的实现
   * @return
   */
  static CppObjectFactory &getInstance() {
    static CppObjectFactory sLo_factory;
    return sLo_factory;
  }

  /**
   * 获取所有注册过的类和它的创建函数
   * @return
   */
  map<string, PTRCreateObject> &getAllReflection() { return m_ClassMap; }
};

/**
 * 注册一个类, 方成 类内部静态函数, 方便 head only
 *  当然, 用inline也行
 */
class RegisterAction {
  public:
  static bool RegisterFun(string className, PTRCreateObject ptrCreateFn) {
    return CppObjectFactory::getInstance().registClass(className, ptrCreateFn);
  }
};

#define Setter(varType, varName)                       \
  public:                                              \
  inline void set_##varName##_ptr(const void *value) { \
    varName = *(varType *)value;                       \
  }                                                    \
                                                       \
  public:                                              \
  inline void set_##varName(const varType &value) { varName = value; }

#define Getter(varType, varName)                                            \
  public:                                                                   \
  inline void *get_##varName##_ptr(void) const { return (void *)&varName; } \
                                                                            \
  public:                                                                   \
  inline varType get_##varName() { return varName; }

#define var(varType, varName) \
  private:                    \
  varType varName;            \
  Getter(varType, varName) Setter(varType, varName)

#define varc(varType, varName, constructor) \
  private:                                  \
  varType varName constructor;              \
  Getter(varType, varName) Setter(varType, varName)


#define REGISTER_DYN(className, classType)                                  \
  static className *objectCreator##className() { return new classType; }    \
  static bool objectCreator##className##Stat = RegisterAction::RegisterFun( \
      #className, (PTRCreateObject)objectCreator##className)
/**
 * 注册一个类的创建函数, 注意: 这个宏最好在cpp/c 中使用
 * .h 中使用时, main 启动前. 没有一个cpp include了这个.h, 那么就会注册一次
 * 后注册的会覆盖前面的, 只要保证没有重名的类被注册, 那就没问题
 *
 * 通过名字索引, 不重名就行
 *
 * 原理: c++ 全局变量 如果有赋值, 那么就会在main函数之前被执行,
 *      这样就可以在main之前注册函数指针到factory中, 不用再手动构造factory
 *      只需要在 cpp 中 , 类声明完成后, 加一个REGISTER 标记,
 * 就自动添加到factory中了
 */
#define REGISTER(classType) REGISTER_DYN(classType, classType)

/**
 * 通过类名创建一个实例的一个简单的包装. 只能使用在知道具体子类类型的情况下
 */
#define REFLACT(className) \
  (className *)CppObjectFactory::getInstance()[#className]
