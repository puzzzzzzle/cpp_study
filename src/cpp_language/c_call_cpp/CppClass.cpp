//
// Created by khalidzhang on 2021/8/26.
//

#include "CppClass.h"
#include <exception>
int ::CppNs::CppClass::foo() {
    return 42;
}
int CppGlobalClass::foo() {
    return 666;
}
void CppGlobalClass::always_throw(){
    throw std::exception();
}
