//
// Created by tao on 19-1-17.
//
#include "boost_log_init.h"
#include <gtest/gtest.h>
#include <thread>


TEST(test_test, 1) {
    EXPECT_EQ(1, 1);
}
void test_mem(int arr[10][20]){
    INFO("size of  int arr from child scope  :"<< sizeof(arr));
    INFO("size of  int arr[5] from child scope  :"<< sizeof(arr[5]));
    INFO("size of  int arr[5][5] from child scope  :"<< sizeof(arr[5][5]));
}

void test_mem_p(int **arr){
    INFO("size of  int arr from child scope  :"<< sizeof(arr));
    INFO("size of  int arr[5] from child scope  :"<< sizeof(arr[5]));
    INFO("size of  int arr[5][5] from child scope  :"<< sizeof(arr[5][5]));
}

int main(int argc, char **argv) {
    int result=0;
    log_init();
    INFO("start gtest"<<" be happy!")
    testing::InitGoogleTest(&argc, argv);
//    result = RUN_ALL_TESTS();

    int arr[10][20];
    INFO("size of  int arr from owner scope  :"<< sizeof(arr));
    INFO("size of  int arr[5] from owner scope  :"<< sizeof(arr[5]));
    INFO("size of  int arr[5][5] from owner scope  :"<< sizeof(arr[5][5]));

    test_mem(arr);
    test_mem_p((int **)arr);

    signal()
    return result;
}