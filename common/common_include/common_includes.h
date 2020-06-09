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

int beforeRun();

#define CALL_IF_RETURN(caller)                                  \
  {                                                             \
    int iRet = caller;                                          \
    if (iRet) {                                                 \
      LOG_ERROR("call  fail " << #caller << "\tret\t" << iRet); \
      return iRet;                                              \
    }                                                           \
  }

#define ERROR_IN -1;
#endif  // CPP_STL_STUDYS_COMMON_INCLUDES_H
