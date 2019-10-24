//
// Created by tao on 19-1-17.
//
#include "common_includes.h"
#include "std_chrono_study.h"
#include "common_configure.h"

#include <memory>
#include <string>

TEST(test_test, 1) {
    EXPECT_EQ(1, 1);
}

//std::shared_ptr<char> make_space_1(size_t size) {
//    auto s = std::make_shared<char>(new char[size],
//                                    [](char *p) {
//                                        TRACE("clear :" << p)
//                                        delete[] p;
//                                    });
//    return s;
//}

template<typename T>
std::shared_ptr<T> make_shared_array(size_t size) {
    //default_delete是STL中的默认删除器
    return std::shared_ptr<T>(new T[size], std::default_delete<T[]>());
}

std::shared_ptr<char> make_space(size_t size) {
    //default_delete是STL中的默认删除器
    auto s = std::shared_ptr<char>(new char[size],
                                   [](char *p) {
                                       TRACE("clear :" << p)
                                       delete[] p;
                                   });
    return s;
}

int main(int argc, char **argv) {
    int result = 0;
    log_init();
    testing::InitGoogleTest(&argc, argv);

    INFO("start raw output test")
    RAW_CLINE("version:" << VERSION_MAJOR)
    RAW_PRINTF("hello\n")
    RAW_PRINTF("hello %d\n", 1)
    RAW_PLINE("hello %d", 2)
    RAW_PLINE("hello")

    auto i_s_1 = std::make_pair(1, "hello");
    std::pair<int, const char *> i_s_2 = std::pair<int, const char *>(1, "hello");
//    auto i_t_1 = std::make_tuple(1,2,3,4,"hahaa");
    auto s = make_space(1000);
    for (int i = 0; i < 999; ++i) {
        s.get()[i] = 'a';
    }
    s.get()[999] = 0;

    auto us = std::unique_ptr<char[]>(new char[1000]);
    decltype(us) us1;
    us1 = std::move(us);
    INFO("is equal:" << (i_s_1 == i_s_2))
    INFO(std::get<1>(i_s_1))
    result = RUN_ALL_TESTS();
    test_chrono();
    return result;
}