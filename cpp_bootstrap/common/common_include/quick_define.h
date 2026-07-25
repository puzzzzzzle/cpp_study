//
// Created by khalidzhang on 2020/11/7.
//

#pragma once

#define CALL_IF_RETURN(caller)                                  \
  {                                                             \
    int iRet = caller;                                          \
    if (iRet) {                                                 \
      LOG_ERROR("call  fail " << #caller << "\tret\t" << iRet); \
      return iRet;                                              \
    }                                                           \
  }

// 编译期可以计算的bool为false时强制结束编译
#define BUILD_BUG_ON_ZERO(e) (sizeof(struct { int : -!!(e); }))
#define BUILD_BUG_ON_NULL(e) ((void *)sizeof(struct { int : -!!(e); }))
#define BUILD_BUG_ON(condition) ((void)BUILD_BUG_ON_ZERO(condition))
#define MAYBE_BUILD_BUG_ON(condition) ((void)sizeof(char[1 - 2 * !!(condition)]))

#define CALL_IF_TRUE_RETURN(caller) \
    { \
        int ret = (caller); \
        if (ret) \
        { \
            LOG_ERROR("error\t" << #caller << "\t" << ret) \
            return ret; \
        } \
    }
#define CALL_IF_TRUE_RETURN_VOID(caller) \
    { \
        int ret = (caller); \
        if (ret) \
        { \
            LOG_ERROR("error\t" << #caller << "\t" << ret) \
            return; \
        } \
    }
#define CALL_IF_TRUE_RETURN_DYN(caller, fail) \
    { \
        int ret = (caller); \
        if (ret) \
        { \
            LOG_ERROR("error\t" << #caller << "\t" << ret) \
            return fail; \
        } \
    }
#define CALL_IF_TRUE_THROW_DYN(cond, err) \
    if (cond) \
    { \
        LOG_ERROR(#cond)\
        throw err; \
    }
#define CALL_IF_TRUE_THROW(cond) \
    if (cond) \
    { \
        LOG_ERROR(#cond)\
        throw  std::invalid_argument(#cond); \
    }

