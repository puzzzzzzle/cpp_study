#ifndef INIT_FUNC_H
#define INIT_FUNC_H
#include <cstdio>
//#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include "log_init.hpp"
#include "log_macro.h"
static void on_exit() {
    puts("\nexit!\n\n");
}

//#define SAY_HELLO
static void init() {
    printf("******init start******\n");

#ifdef SAY_HELLO
    printf("SAY_HELLO for cmake definictions!!!\n");
#endif
    atexit(on_exit);

    char buff[100];
    getcwd(buff, 100);
    printf("start work dir : %s\n", buff);
    chdir("..");
    getcwd(buff, 100);
    printf("run work dir : %s\n", buff);


    log_init();
    INFO("logger start work now");
    printf("******init finish******\n\n");

}

#endif // INIT_FUNC_H
