//
// Created by khalidzhang on 2021/8/26.
//

#include "CppClassWrapper.h"

CppNs_CppClass *new_CppNs_CppClass() {
    return new CppNs::CppClass();
}
void delete_CppNs_CppClass(CppNs_CppClass *v) {
    delete v;
}
int CppNs_CppClass_foo(CppNs_CppClass *v) {
    v->foo();
}
CppGlobalClass *new_CppGlobalClass() {
    return new CppGlobalClass();
}
void delete_CppGlobalClass(CppGlobalClass *v) {
    delete v;
}
int CppGlobalClass_foo(CppGlobalClass *v) {
    return v->foo();
}
int CppGlobalClass_always_throw(CppGlobalClass *v) {
    v->always_throw();
}