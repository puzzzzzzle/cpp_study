// room_impl.cpp
// IRoom 的虚函数实现放在独立的编译单元里（非类内联），
// 这样链接后才有可导出的 mangled 符号，dladdr 才能解析出函数名。
// 若写成类内联实现，编译器可能将其内联，导致 dladdr 拿到空符号名。

#include "room.hpp"

IRoom::~IRoom() {}
int IRoom::GetGameID() { return 0; }
int IRoom::GetRoomID() { return 0; }
void IRoom::OnUserEnter() {}
void IRoom::OnUserLeave() {}
