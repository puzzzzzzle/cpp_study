//
// Created by tao on 19-1-17.
//
#include <cstdarg>

#include "common_includes.h"

template<typename T>
T sumAll(int count, ...) {
    va_list ap;
    va_start(ap, count);
    T sum{};
    for (int i = 0; i < count; ++i) {
        T val = va_arg(ap, T);
        sum += val;
    }
    va_end(ap);
    return sum;
}

TEST(multi_args, c_caller) {
    EXPECT_EQ(1, sumAll<int>(1, 1));
    EXPECT_EQ(3, sumAll<int>(2, 1, 2));
    EXPECT_EQ(6, sumAll<int>(3, 1, 2, 3));
    EXPECT_EQ(10, sumAll<int>(4, 1, 2, 3, 4));
}
// void print(){}
// template<typename T, typename... Types>
// void print(const T& firstArg, const Types&...args){
//    std::cout << firstArg << std::endl;
////    INFO(firstArg)
//    print(args...);
//}

void mvPrint() {}
template<typename T, typename... Args>
void mvPrint(const T &first, const Args &... args) {
    std::cout << first << std::endl;
    mvPrint(args...);
}

TEST(multi_args, cpp_recursive) {
    //    print("sdfsf",5,6,"sdsd");
    mvPrint("sdfsf", 5, 6, "sdsd");
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