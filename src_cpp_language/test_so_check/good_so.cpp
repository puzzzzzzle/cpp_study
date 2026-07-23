// good_so.cpp
// "正常 SO"：IRoom vtable 布局与 GameSvr 完全一致。
// 编译为 libgood_so.so，由主程序用 dlopen 加载并调用 GetGoodSOIRoomVTable。
//
// 注意：SO 内部自带 IRoom 实现（不依赖主程序的 room_impl.cpp），
// 这样 SO 的 vtable 槽位里存的是本 so 内导出的 IRoom::xxx 符号，
// 主程序只比对"函数名"而非地址，避免与主程序符号冲突。

#include <cstring>

#include "room.hpp"

// SO 内部 IRoom 实现（放在全局作用域，成员函数定义必须位于类所在命名空间）。
// 这些符号只在本 so 内可见，dladdr 解析时落在 so 模块内，与主程序符号隔离。
IRoom::~IRoom() {}
int IRoom::GetGameID() { return 0; }
int IRoom::GetRoomID() { return 0; }
void IRoom::OnUserEnter() {}
void IRoom::OnUserLeave() {}

// 临时子类：多一个尾函数专门用来标记 vtable 边界。
// 不 override 任何虚函数，直接复用 IRoom 基类实现，保证槽位符号与 GameSvr 一致。
class CGoodSOIRoom : public IRoom {
 public:
  virtual void __HAPPY_STUDIO__TailOfVtable() {}
};

// 从对象实例里抠出 vtable 指针（对象首 8 字节即 vtable 指针）。
static void** GetVTablePtr(void* pObj) {
  void** pVTable = nullptr;
  memcpy(&pVTable, pObj, sizeof(pVTable));
  return pVTable;
}

extern "C" void GetGoodSOIRoomVTable(void*& pVTable, void*& pHead, void*& pTail) {
  static CGoodSOIRoom stSOIRoom;  // static 保证 vtable 稳定存在

  // 用成员函数指针 + 通过对象调用，拿到 head/tail 对应的真实函数地址。
  // 地址与 vtable 槽位里存的值一致，可拿来做遍历起止标记。
  typedef int (CGoodSOIRoom::*MFPHead)();
  typedef void (CGoodSOIRoom::*MFPTail)();
  MFPHead pHeadFunc = &CGoodSOIRoom::GetGameID;
  MFPTail pTailFunc = &CGoodSOIRoom::__HAPPY_STUDIO__TailOfVtable;

  pVTable = GetVTablePtr(&stSOIRoom);
  pHead = (void*)(stSOIRoom.*pHeadFunc);
  pTail = (void*)(stSOIRoom.*pTailFunc);
}
