//
// Created by tao on 19-2-25.
//

#ifndef CPP_STL_STUDYS_COMMON_INCLUDES_H
#define CPP_STL_STUDYS_COMMON_INCLUDES_H

#include <gtest/gtest.h>
#include <thread>
#include "common_funcs.h"

#ifdef LOG_BOOST
#include "log_init.h"
#else
#include "log_row.h"
#endif

int beforeRun() {
    int iRet = 0;
#ifdef LOG_BOOST
    iRet = log_init();
#else
    iRet = 0;
#endif
    return iRet;
}

#define ERROR_IN -1;
#endif //CPP_STL_STUDYS_COMMON_INCLUDES_H
