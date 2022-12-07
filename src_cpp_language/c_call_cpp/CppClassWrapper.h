#pragma once

#ifdef __cplusplus
#include "CppClass.h"
typedef CppNs::CppClass CppNs_CppClass;
extern "C" {
#else
typedef struct CppNs_CppClass CppNs_CppClass;

typedef struct CppGlobalClass CppGlobalClass;
#endif

CppNs_CppClass *new_CppNs_CppClass();
void delete_CppNs_CppClass(CppNs_CppClass *v);
int CppNs_CppClass_foo(CppNs_CppClass *v);

CppGlobalClass * new_CppGlobalClass();
void delete_CppGlobalClass(CppGlobalClass * v);
int CppGlobalClass_foo(CppGlobalClass *v);
int CppGlobalClass_always_throw(CppGlobalClass *v);

#ifdef __cplusplus
};
#endif