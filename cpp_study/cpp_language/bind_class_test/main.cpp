//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

class Base {
    int    i;
    double j;

public:
    void set(int _i, double _j) {
        i = _i;
        j = _j;
    }
    void ToString(std::ostream &os) {
        os << "i:" << i << ",j:" << j;
    }
};

TEST(test_test, 1) {
    Base base;

    auto func = std::bind(&Base::set, &base, std::placeholders::_1, std::placeholders::_2);
    func(5, 5.5);
    base.ToString(std::cout);
    EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}