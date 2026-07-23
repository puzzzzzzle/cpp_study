// bad_so.cpp
// "异常 SO"：继承扩展版接口 IBadRoom（比 GameSvr 的 IRoom 多一个 OnKickUser），
// 导致其 vtable 比 GameSvr 多一个槽位，后续虚函数整体错后一位，
// 模拟 SO 与 GameSvr 接口版本不一致导致的 vtable 乱序问题。
// 编译为 libbad_so.so，由主程序用 dlopen 加载并调用 GetBadSOIRoomVTable。

#include <cstring>

#include "room.hpp"


// 异常 SO 使用的"扩展版"接口：在 IRoom 基础上多声明了一个虚函数。
// 这样它的 vtable 比 GameSvr 的 IRoom 多了一个槽位，后续虚函数的
// 偏移整体后移，从而与 GameSvr 端 vtable 错位（模拟版本不一致）。
class IBadRoom : public IRoom {
 public:
  virtual void OnKickUser();
};
void IBadRoom::OnKickUser() {}

// 临时子类：继承 IBadRoom（多一个虚函数），并加尾函数标记 vtable 边界。
// 多出的 OnKickUser 槽位使 vtable 与 GameSvr 错位。
class CBadSOIRoom : public IBadRoom {
 public:
  virtual void __HAPPY_STUDIO__TailOfVtable() {}
};

// 从对象实例里抠出 vtable 指针（对象首 8 字节即 vtable 指针）。
static void** GetVTablePtr(void* pObj) {
  void** pVTable = nullptr;
  memcpy(&pVTable, pObj, sizeof(pVTable));
  return pVTable;
}

extern "C" void GetBadSOIRoomVTable(void*& pVTable, void*& pHead, void*& pTail) {
  static CBadSOIRoom stSOIRoom;  // static 保证 vtable 稳定存在

  typedef int (CBadSOIRoom::*MFPHead)();
  typedef void (CBadSOIRoom::*MFPTail)();
  MFPHead pHeadFunc = &CBadSOIRoom::GetGameID;
  MFPTail pTailFunc = &CBadSOIRoom::__HAPPY_STUDIO__TailOfVtable;

  pVTable = GetVTablePtr(&stSOIRoom);
  pHead = (void*)(stSOIRoom.*pHeadFunc);
  pTail = (void*)(stSOIRoom.*pTailFunc);
}
