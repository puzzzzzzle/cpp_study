//
// Created by tao on 18-11-29.
//

#ifndef UNIXSTUDYCPP_REF_MOVE_TEST_HPP
#define UNIXSTUDYCPP_REF_MOVE_TEST_HPP

#include "../log4cplus_init/log_macro.h"

class temp_handle {
private:
    int       val1;
    int &     val2;
    const int val3;

public:
    temp_handle(int &_val1, int &_val2, int _val3) : val2(_val2), val3(_val3) {
        val1 = std::move(_val1);
    }
};

void ref_test_main() {
    int          a1 = 1, a2 = 2, a3 = 3;
    temp_handle *t = new temp_handle(a1, a2, a3);
    TRACE("end");
    delete (t);
}

#endif  // UNIXSTUDYCPP_REF_MOVE_TEST_HPP
