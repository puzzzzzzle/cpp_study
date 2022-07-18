#include "CppClassWrapper.h"
#include <stdio.h>
// c 编译器 不认识 namespace
//namespace Test{
//
//};

int main() {
    printf("Hello, World!\n");
    CppNs_CppClass *c = new_CppNs_CppClass();
    printf("CppNs_CppClass %d\n", CppNs_CppClass_foo(c));
    delete_CppNs_CppClass(c);

    CppGlobalClass *d = new_CppGlobalClass();
    printf("Hello, World! %d\n", CppGlobalClass_foo(d));
    CppGlobalClass_always_throw(d);
    delete_CppGlobalClass(d);

    return 0;
}
