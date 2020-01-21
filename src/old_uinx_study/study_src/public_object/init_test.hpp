//
// Created by tao on 18-11-29.
//

#ifndef UNIXSTUDYCPP_INIT_TEST_HPP
#define UNIXSTUDYCPP_INIT_TEST_HPP

#include "../log4cplus_init/log_macro.h"

class init_test {
private:
    int mi_val;

public:
    init_test() { TRACE("called default constructor"); }
    // val 的方式，会拷贝一次数据
    //    init_test(int _val) {
    //        TRACE("int _val init!");
    //        this->mi_val = _val;
    //    }

    //&val 的方式调用函数，不会拷贝原来的数据，而是吧原来的地址直接传递进来
    init_test(int &_val) {
        TRACE("int & _val init!");
        printf("mi_val:\t%p\t_val:\t%p\n", &mi_val, &_val);
        this->mi_val = _val;
    }

    // &&val的方式，会把源数据转移过来，原来的位置上不在有数据了，时编译器优化的结果，但是sdt::move是不是真的把数据转移了？？
    init_test(int &&_val) {
        TRACE("int && _val init!");
        printf("mi_val:\t%p\t_val:\t%p\n", &mi_val, &_val);
        this->mi_val = _val;
    }
};

void test_init_fun() {
    TRACE("default constructor");
    init_test t0;
    int       a = 10;
    //    TRACE(to_string(&a));
    printf("%p\n", &a);
    TRACE("&_val");
    init_test t1(a);
    TRACE("&& _val :");
    init_test t2(2);
}

#endif  // UNIXSTUDYCPP_INIT_TEST_HPP
