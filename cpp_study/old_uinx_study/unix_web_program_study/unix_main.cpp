//
// Created by tao on 18-12-28.
#include <cstdio>
//#include "init_func.h"
#include "../init_func.h"

#include "io_mutiplexing_test.h"
//extern  char **environ;

int main(int argc, char **argv) {
    init();

    epoll_test_main("8898");
//    test_select();
//    printf("hello unix web!");
    return 0;
}
