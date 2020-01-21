//
// Created by tao on 19-1-17.
//
#include "MultiOrderedEvent.h"
#include "UnOrderedEvent.h"
#include "common_includes.h"

TEST(UnOrderedEventImpl, void) {
    UnOrderedEventImpl<void> event{};
    int                      i = 0;
    // lambda
    auto func = DelegateUnOrdered([&i]() {
        LOG_DEBUG("hello")
        ++i;
    });
    event += func;
    ASSERT_FALSE(event.FireEvent());
    ASSERT_EQ(i, 1);
}
TEST(UnOrderedEventImpl, int) {
    UnOrderedEventImpl<int> event{};
    int                     i = 0;
    // lambda
    auto func = DelegateUnOrdered(
        [&i](int args) {
            LOG_DEBUG("hello " << args)
            ++i;
        },
        int);
    event += func;
    ASSERT_FALSE(event.FireEvent(5));
    ASSERT_EQ(i, 1);
}
TEST(UnOrderedEventImpl, multi) {
    UnOrderedEventImpl<int, double, std::string> event{};
    int                                          i = 0;
    // lambda
    auto func = DelegateUnOrdered(
        [&i](int iArg, double dArg, std::string sArg) {
            LOG_DEBUG("iArg\t" << iArg << "\tdArg\t" << dArg << "\tsArg\t" << sArg)
            ++i;
        },
        int, double, std::string);
    event += func;
    ASSERT_FALSE(event.FireEvent(5, 6.5, "aha"));
    ASSERT_EQ(i, 1);
}

TEST(MultiOrderedEventImpl, void) {
    MultiOrderedEventImpl<void> event{};
    int                         i = 0;
    // lambda
    auto func = DelegateOrdered([&i]() {
        LOG_DEBUG("hello")
        ++i;
    });
    event += func;
    ASSERT_FALSE(event.FireEvent());
    ASSERT_EQ(i, 1);
}
TEST(MultiOrderedEventImpl, int) {
    MultiOrderedEventImpl<int> event{};
    int                        i = 0;
    // lambda
    auto func = DelegateOrdered(
        [&i](int args) {
            LOG_DEBUG("hello " << args)
            ++i;
        },
        int);
    event += func;
    ASSERT_FALSE(event.FireEvent(5));
    ASSERT_EQ(i, 1);
}
TEST(MultiOrderedEventImpl, multi) {
    MultiOrderedEventImpl<int, double, std::string> event{};
    int                                             i = 0;
    // lambda
    auto func = DelegateOrdered(
        [&i](int iArg, double dArg, std::string sArg) {
            LOG_DEBUG("iArg\t" << iArg << "\tdArg\t" << dArg << "\tsArg\t" << sArg)
            ++i;
        },
        int, double, std::string);
    event += func;
    ASSERT_FALSE(event.FireEvent(5, 6.5, "aha"));
    ASSERT_EQ(i, 1);
}
int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    sleep(1);
    return iRet;
}