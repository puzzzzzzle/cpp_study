//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

/**
{
i_ = 0
}
 */
class NoVirtual {
  public:
  int i_{};
  void func() {}
};

/**
 *
(VirtualBase) {
 _vptr.VirtualBase = 0x5555555c2ae0 <vtable for VirtualBase+16>,
 i_ = 0
}

 p sizeof(n)
$2 = 16
 */
class VirtualBase {
  public:
  int i_{};
  virtual void func() {}
};
class VirtualBase2 {
  public:
  int i_{};
  virtual void func() {}
  virtual void func2() {}
};
class VirtualBase3 {
  public:
  int i_{};
  virtual void func() {}
  virtual void func3() {}
};
/**
{
  <NoVirtual> = {
    i_ = 0
  },
  members of DerivedNoVirtual:
  i_ = 0,
  j_ = 0
}
p sizeof(n)
$2 = 12
 */
class DerivedNoVirtual : public NoVirtual {
  public:
  int i_{};
  int j_{};
  void func() {}
  void func1() {}
};

/**
(DerivedVirtual) {
  <VirtualBase> = {
    _vptr.VirtualBase = 0x5555555c2ac0 <vtable for DerivedVirtual+16>,
    i_ = 0
  },
  members of DerivedVirtual:
  j_ = 0
}

 p sizeof(n)
$1 = 16
 */
class DerivedVirtual : public VirtualBase {
  public:
  int j_{};
};

/**
(DerivedVirtualAddFunc) {
  <VirtualBase> = {
    _vptr.VirtualBase = 0x5555555c2ac0 <vtable for DerivedVirtualAddFunc+16>,
    i_ = 0
  },
  members of DerivedVirtualAddFunc:
  j_ = 0
}

 p sizeof(n)
$2 = 16
 */
class DerivedVirtualAddFunc : public VirtualBase {
  public:
  int j_{};
  virtual void func() override {}
  virtual void func1() {}
};

/**
(MultiDerived) {
  <VirtualBase> = {
    _vptr.VirtualBase = 0x5555555c3a20 <vtable for MultiDerived+16>,
    i_ = 0
  },
  <VirtualBase2> = {
    _vptr.VirtualBase2 = 0x5555555c3a40 <vtable for MultiDerived+48>,
    i_ = 0
  },
  <VirtualBase3> = {
    _vptr.VirtualBase3 = 0x5555555c3a60 <vtable for MultiDerived+80>,
    i_ = 0
  },
  members of MultiDerived:
  j_ = 0
}
(gdb)  p sizeof(n)
$2 = 48
// j_ 和 VirtualBase3.i_ 对齐了 所以内存时  48 , 不是48 +8
 */
class MultiDerived : public VirtualBase,
                     public VirtualBase2,
                     public VirtualBase3 {
  public:
  int j_{};
  void func() override {}
  virtual void fff() {}
};

class A {
  public:
  int i_{};
  virtual void func() {}
};
class B : public A {
  public:
  int j_{};
  virtual void func() {}
  virtual void func1() {}
};
class C : public A {
  public:
  int j_{};
  virtual void func() {}
  virtual void func1() {}
};
class D : public virtual A {
  public:
  int j_{};
  virtual void func() {}
  virtual void func1() {}
};
class E : public virtual A {
  public:
  int j_{};
  virtual void func() {}
  virtual void func1() {}
};
/**
(gdb) p n
$1 = (RhombusDerived) {
  <B> = {
    <A> = {
      _vptr.A = 0x5555555c3a40 <vtable for RhombusDerived+16>,
      i_ = 0
    },
    members of B:
    j_ = 0
  },
  <C> = {
    <A> = {
      _vptr.A = 0x5555555c3a60 <vtable for RhombusDerived+48>,
      i_ = 0
    },
    members of C:
    j_ = 0
  },
  members of RhombusDerived:
  k_ = 0
}
(gdb)  p sizeof(n)
$2 = 40

 */
class RhombusDerived : public B, public C
{
  int k_{};
  virtual void func() {}
  virtual void func1() {}
};
/**
(gdb) p n
$1 = (RhombusDerivedC) {
  <B> = {
    <A> = {
      _vptr.A = 0x5555555c39c8 <vtable for RhombusDerivedC+24>,
      i_ = 0
    },
    members of B:
    j_ = 0
  },
  <C> = {
    <A> = {
      _vptr.A = 0x5555555c39f8 <vtable for RhombusDerivedC+72>,
      i_ = 0
    },
    members of C:
    j_ = 0
  },
  members of RhombusDerivedC:
  k_ = 0
}
(gdb)  p sizeof(n)
$2 = 40

 */
class RhombusDerivedC : public B, public virtual C
{
  int k_{};
  virtual void func() {}
  virtual void func1() {}
};
/**
(gdb) p n
$1 = (RhombusDerivedD) {
  <B> = {
    <A> = {
      _vptr.A = 0x5555555c3968 <vtable for RhombusDerivedD+24>,
      i_ = 0
    },
    members of B:
    j_ = 0
  },
  <D> = {
    <A> = {
      _vptr.A = 0x5555555c39b8 <vtable for RhombusDerivedD+104>,
      i_ = 0
    },
    members of D:
    _vptr.D = 0x5555555c3990 <vtable for RhombusDerivedD+64>,
    j_ = 0
  },
  members of RhombusDerivedD:
  k_ = 0
}
(gdb)  p sizeof(n)
$2 = 48

 */
class RhombusDerivedD : public B, public D
{
  int k_{};
  virtual void func() {}
  virtual void func1() {}
};
/**
(gdb) p n
$1 = (RhombusDerivedE) {
  <D> = {
    <A> = {
      _vptr.A = 0x5555555c3978 <vtable for RhombusDerivedE+104>,
      i_ = 0
    },
    members of D:
    _vptr.D = 0x5555555c3928 <vtable for RhombusDerivedE+24>,
    j_ = 0
  },
  <E> = {
    members of E:
    _vptr.E = 0x5555555c3950 <vtable for RhombusDerivedE+64>,
    j_ = 0
  },
  members of RhombusDerivedE:
  k_ = 0
}
(gdb)  p sizeof(n)
$2 = 48

 */
class RhombusDerivedE : public D, public E
{
  int k_{};
  virtual void func() {}
  virtual void func1() {}
};
TEST(vtable_test, 1) {
  RhombusDerivedE n{};
  EXPECT_EQ(1, 1);
}
