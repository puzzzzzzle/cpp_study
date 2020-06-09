//
// Created by khalidzhang on 2019/9/22.
//

#ifndef CPPREFLACT_CPPOBJECT_HPP
#define CPPREFLACT_CPPOBJECT_HPP

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
  void *getClassByName(string className) {
    map<string, PTRCreateObject>::const_iterator iter;
    iter = m_ClassMap.find(className);
    if (iter == m_ClassMap.end())
      return NULL;
    else
      return iter->second();
  }

  bool registClass(string name, PTRCreateObject method) {
    return m_ClassMap.insert(pair<string, PTRCreateObject>(name, method))
        .second;
  }

  void *operator[](string className) { return getClassByName(className); }

  static CppObjectFactory &getInstance() {
    static CppObjectFactory sLo_factory;
    return sLo_factory;
  }
};

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

#define REGISTER(className)                                              \
  static className *objectCreator##className() { return new className; } \
  bool objectCreator##className##Stat = RegisterAction::RegisterFun(     \
      #className, (PTRCreateObject)objectCreator##className)
#define REFLACT(className) \
  (className *)CppObjectFactory::getInstance()[#className]

#endif  // CPPREFLACT_CPPOBJECT_HPP
