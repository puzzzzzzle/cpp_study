// room.hpp
// 模拟 GameSvr 这边的 IRoom 接口基类（实际项目里是 IRoom / ITable）。
// 注意：真实项目里的 IRoom 所有虚函数都有默认实现（非纯虚），
// 因此 GameSvr 才能直接在栈上构造一个 IRoom 对象来抠出 vtable。
//
// 本文件被主程序（GameSvr）和两个 SO（good/bad）共同包含，
// 保证三方看到的 IRoom 接口声明完全一致。

#ifndef __ROOM_HPP__
#define __ROOM_HPP__

class IRoom {
 public:
  virtual ~IRoom();
  virtual int GetGameID();
  virtual int GetRoomID();
  virtual void OnUserEnter();
  virtual void OnUserLeave();
};

#endif  // __ROOM_HPP__
