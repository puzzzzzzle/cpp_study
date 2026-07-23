// vtable_check_demo.cpp
// 演示虚函数表（vtable）一致性校验机制。
//
// 背景：GameSvr 在加载一个游戏 SO 后，会校验 SO 导出的 vtable 与
// GameSvr 本地的 IRoom/ITable 接口 vtable 是否"同序、同名"。
// 这样可以尽早发现：SO 漏实现某个虚函数、或者虚函数声明顺序和
// GameSvr 不一致（乱序）等问题，避免运行时崩溃。
//
// 本 demo 不依赖项目庞大的头文件，用最小可编译的方式还原核心思路：
//   1. 两个 SO（libgood_so.so / libbad_so.so）各自暴露自己的 vtable 区间
//      （通过临时子类 + 尾函数，方式同真实项目 GetSOIRoomVTable）。
//   2. 主程序（模拟 GameSvr）用 dlopen 加载 SO、dlsym 取出其
//      GetXxxSOIRoomVTable 接口，再逐槽位用 dladdr 翻译符号名比对。
//
// 注意：IRoom 的虚函数实现放在独立的 room_impl.cpp 里（非类内联），
// 这样链接后才有可导出的 mangled 符号，dladdr 才能解析出函数名。
// 如果像最初那样把实现写在类里内联，编译器可能将其内联掉，
// dladdr 虽能解析地址但 dli_sname 为空，check 就无法比对符号名。
//
// 注意：SO 加载使用 RTLD_LOCAL，避免两个 so 的重名符号互相干扰。

#include <cxxabi.h>
#include <dlfcn.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "room.hpp"

// 从对象实例里抠出 vtable 指针。
// 对象内存布局最前面 8 字节（64 位）就是指向 vtable 的指针。
static void** GetVTablePtr(void* pObj) {
  void** pVTable = nullptr;
  memcpy(&pVTable, pObj, sizeof(pVTable));
  return pVTable;
}

// SO 暴露的 vtable 区间接口（各 so 内用 extern "C" 导出）。
//   pVTable     —— SO 的 IRoom vtable 指针
//   pHead       —— vtable 第一个有意义虚函数的地址（用作起点标记）
//   pTail       —— 自定义尾函数地址（用作终点标记，避免越界遍历）
typedef void (*GetSOIRoomVTableFunc)(void*&, void*&, void*&);

// 翻译一个函数地址对应的 C++ 符号名（mangled -> demangled）。
static const char* Demangle(const char* mangled, char* buf, size_t bufLen) {
  if (mangled == nullptr) return "(null)";
  int status = -1;
  size_t len = bufLen;
  char* demangled = abi::__cxa_demangle(mangled, buf, &len, &status);
  return (status == 0 && demangled != nullptr) ? demangled : mangled;
}

// 判断两个 mangled 名字去掉类名后，函数名+参数是否一致。
// 从右往左：先比参数列表，再比 '::' 之前的函数名部分。
static bool IsSameCFuncName(const char* base, const char* derived) {
  if (base == nullptr || derived == nullptr) return false;

  char baseBuf[2048], derivedBuf[2048];
  const char* b = Demangle(base, baseBuf, sizeof(baseBuf));
  const char* d = Demangle(derived, derivedBuf, sizeof(derivedBuf));

  // 倒序比较：先比参数列表，再比函数名。
  int bi = (int)strlen(b) - 1;
  int di = (int)strlen(d) - 1;
  int bracket = 0;
  // 1) 参数列表部分
  while (true) {
    if (bi < 0 || di < 0 || b[bi] != d[di]) return false;
    if (b[bi] == ')') ++bracket;
    if (b[bi] == '(') {
      if (--bracket == 0) break;
    }
    --bi;
    --di;
  }
  // 2) 函数名部分（到 '::' 为止）
  while (true) {
    if (bi < 0 || di < 0 || b[bi] != d[di]) return false;
    if (b[bi] == ':') break;
    --bi;
    --di;
  }
  return true;
}

// 核心 check：逐个槽位比对 GameSvr 的 vtable 与 SO 的 vtable 是否同名同序。
// 返回 0 表示一致，非 0 表示发现乱序/不匹配。
static int CheckGameSvrRoomSupportFunc(void** pGameSvrVTable, void** pSOVTable, void* pSOVTableHead,
                                       void* pSOVTableTail) {
  int i = 0;
  // 跳过 SO vtable 开头，直到 head 标记。
  for (; pSOVTable[i] != pSOVTableHead; ++i) {
  }

  char gameSvrSym[2048], soSym[2048];
  Dl_info gameSvrInfo;
  Dl_info soInfo;
  memset(&gameSvrInfo, 0, sizeof(gameSvrInfo));
  memset(&soInfo, 0, sizeof(soInfo));

  for (; pSOVTable[i] != pSOVTableTail; ++i) {
    if (dladdr(pGameSvrVTable[i], &gameSvrInfo) == 0) {
      printf("[FAIL] dladdr failed at index %d, gamesvr addr=%p\n", i, pGameSvrVTable[i]);
      return -1;
    }
    if (dladdr(pSOVTable[i], &soInfo) == 0) {
      printf("[FAIL] dladdr failed at index %d, so addr=%p\n", i, pSOVTable[i]);
      return -1;
    }

    if (!IsSameCFuncName(gameSvrInfo.dli_sname, soInfo.dli_sname)) {
      printf(
          "[FAIL] vtable mismatch at index %d:\n"
          "        GameSvr: %s\n"
          "        SO     : %s\n",
          i, Demangle(gameSvrInfo.dli_sname, gameSvrSym, sizeof(gameSvrSym)),
          Demangle(soInfo.dli_sname, soSym, sizeof(soSym)));
      return -2;
    }

    printf("[ OK ] index %d match: %s\n", i, Demangle(gameSvrInfo.dli_sname, gameSvrSym, sizeof(gameSvrSym)));
  }
  return 0;
}

// 加载一个 SO，取出其 GetSOIRoomVTable 接口并与 GameSvr 的 vtable 做检查。
// 返回 0 表示一致（PASS），非 0 表示 mismatch 或加载失败。
static int RunCheckWithSo(const char* szLabel, const char* szSoPath, const char* szSoFunc) {
  printf("\n==== case: %s ====\n", szLabel);
  printf("loading so: %s\n", szSoPath);

  void* hSo = dlopen(szSoPath, RTLD_LOCAL | RTLD_NOW);
  if (hSo == nullptr) {
    printf("[FAIL] dlopen failed: %s\n", dlerror());
    return -1;
  }

  GetSOIRoomVTableFunc pfnGetVTable = (GetSOIRoomVTableFunc)dlsym(hSo, szSoFunc);
  if (pfnGetVTable == nullptr) {
    printf("[FAIL] dlsym %s failed: %s\n", szSoFunc, dlerror());
    dlclose(hSo);
    return -1;
  }

  // GameSvr 本地 IRoom 的 vtable（直接在栈上构造 IRoom 抠出，
  // 与真实项目 CSOMng::CheckGameSvrRoomSupportFunc 做法一致）。
  IRoom stGameSvrIRoom;
  void** pGameSvrVTable = GetVTablePtr(&stGameSvrIRoom);

  // 被检查方（SO）暴露自己的 vtable 区间。
  void* pSOVTable = nullptr;
  void* pSOVTableHead = nullptr;
  void* pSOVTableTail = nullptr;
  pfnGetVTable(pSOVTable, pSOVTableHead, pSOVTableTail);

  int iRet = -1;
  if (pSOVTable == nullptr || pSOVTableHead == nullptr || pSOVTableTail == nullptr) {
    printf("[SKIP] SO vtable is null, nothing to check\n");
    iRet = 0;
  } else {
    iRet = CheckGameSvrRoomSupportFunc(pGameSvrVTable, (void**)pSOVTable, pSOVTableHead, pSOVTableTail);
  }

  if (iRet == 0) {
    printf("---- result: PASS (GameSvr vtable 与 SO vtable 完全一致) ----\n");
  } else {
    printf("---- result: FAIL (ret=%d, vtable 乱序/不匹配) ----\n", iRet);
  }

  dlclose(hSo);
  return iRet;
}

int main() {
  // case 1: 正常 SO，vtable 布局与 GameSvr 一致，应通过。
  int iRet1 = RunCheckWithSo("good SO (layout consistent)", "./libgood_so.so", "GetGoodSOIRoomVTable");

  // case 2: 乱序 SO，vtable 槽位顺序与 GameSvr 不一致，应被检出失败。
  int iRet2 = RunCheckWithSo("bad SO (layout mismatch)", "./libbad_so.so", "GetBadSOIRoomVTable");

  printf("\n==== summary ====\n");
  printf("good SO check ret=%d (expect 0)\n", iRet1);
  printf("bad  SO check ret=%d (expect != 0)\n", iRet2);
  // 两个 case 都符合预期才算 demo 成功。
  return (iRet1 == 0 && iRet2 != 0) ? 0 : 1;
}