//
// Created by tao on 19-1-17.
//
#include "common_includes.h"

template <typename T>
void deleteArr(T *p) {
    delete[] p;
}

//#pragma pack(push) //保存对齐状态
//#pragma pack(1)
class Base {
public:
    Base() { INFO("base init\t" << a << "\tptr\t" << (uint64_t)this) }

    ~Base() { INFO("base delete\t" << a << "\tptr\t" << (uint64_t)this) }

    int a{1};

    int getA() { return a; }

    virtual int vGetA() { return a; }
};

class Child : public Base {
public:
    Child() { INFO("child init\t" << a << "\tptr\t" << (uint64_t)this) }

    ~Child() { INFO("child delete\t" << a << "\tptr\t" << (uint64_t)this) }

    int new_a{2};

    int buff[10];

    //    char buff[4000];
    virtual int vGetA() override { return new_a; }
};
//#pragma pack(pop)//恢复对齐状态

TEST(base, stack) { Base base[10]; }

TEST(child, stack) { Child base[10]; }

TEST(base, inline_delete) {
    Base *bases = new Base[10];
    delete[] bases;
}

TEST(child, inline_delete) {
    Child *bases = new Child[10];
    delete[] bases;
}

TEST(base, out_delete) {
    Base *bases = new Base[10];
    deleteArr(bases);
}

TEST(child, out_delete) {
    Child *bases = new Child[10];
    deleteArr(bases);
}

TEST(base2child, inline_delete) {
    Base *bases = new Child[10];
    delete[] bases;
}

TEST(base2child, out_delete) {
    Base *bases = new Child[10];
    deleteArr(bases);
}

int main(int argc, char **argv) {
    INFO("sizeof : base\t" << sizeof(Base) << "\tchild\t" << sizeof(Child))
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}