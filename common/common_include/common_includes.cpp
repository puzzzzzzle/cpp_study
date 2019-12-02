//
// Created by khalidzhang on 2019/10/14.
//
#include "common_includes.h"

int beforeRun()
{
    srand(time(NULL));
    int iRet = 0;
#ifdef LOG_BOOST
    iRet = log_init();
#else
    iRet = 0;
#endif
    return iRet;
}