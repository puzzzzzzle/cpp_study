/************************************************
 * @author puzzzzzzle
 * @email 2359173906@qq.com
 * @desc
 * @time 2023/2/2
 * @file astar_c_bind.h
 * @version
 * version        author            desc
 * 1.0            puzzzzzzle       create
 ************************************************/

#pragma once
#if defined(WIN32) || defined(_WIN64)
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif
#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct AstarPoint_ {
  int x{};
  int y{};
} AstarPoint;
typedef struct AstarResult_ {
  int result{};
  int len{};
  AstarPoint* path{};
} AstarResult;
EXPORT void* astar_new(int inWidth, int inHeight, uint8_t* arr);
EXPORT void astar_delete(void* astar);
EXPORT char* astar_dump_map(void* astar);
EXPORT AstarResult astar_search(void* astar, AstarPoint start, AstarPoint end);
EXPORT void astar_result_delete(AstarResult result);
EXPORT const char * version_info();
EXPORT void free_mem(void* astar);
#ifdef __cplusplus
}
#endif