//
// Created by tao on 19-1-17.
//
#include "CSharpEvent.h"
#include "common_includes.h"
using namespace CSharpEvent;

class TempClass {
    std::string name{};

public:
    TempClass(std::string _name) : name(_name) {}

public:
    void NoPara() { LOG_DEBUG("call NoPara name: " << name) }
    void ParaInt(int para) { LOG_DEBUG("call ParaInt name:\t" << name << "\tpara:\t" << para) }
};
void GNoPara() { LOG_DEBUG("call GNoPara") }
void GParaInt(int para){LOG_DEBUG("call GParaInt para:\t" << para)}

class FunctionClass{
public:
    void operator()(){
        LOG_DEBUG("call FunctionClass NoPara");
    }
    void operator()(int para){
        LOG_DEBUG("call FunctionClass ParaInt\t"<< para);
    }
};
TEST(MultiOrderedEvent, MultiOrderedEvent) {
    EXPECT_EQ(1, 1);
    MultiOrderedEvent event{};

    int i = 0;
    // lambda
    auto call1 = Delegate([&i]() {
        LOG_DEBUG("call lambda");
        ++i;
    });
    // 每次触发都会被调用,每次触发调用3次
    event += call1;
    event += call1;
    ASSERT_TRUE(event.Register(call1));
    // 只调用一次
    ASSERT_TRUE(event.RegisterOnce(call1));

    TempClass tempClass("");
    // class without para
    MakeDelegate(call2, std::bind(&TempClass::NoPara, tempClass));
    ASSERT_TRUE(event.Register(call2));
    // class with para
    MakeDelegate(call3, std::bind(&TempClass::ParaInt, tempClass, 42));
    ASSERT_TRUE(event.Register(call3));

    // global func without para
    MakeDelegate(call4, std::bind(&GNoPara));
    ASSERT_TRUE(event.Register(call4));
    // global func with para
    MakeDelegate(call5, std::bind(&GParaInt, 56));
    ASSERT_TRUE(event.Register(call5));

    // 仿函数
    FunctionClass functionClass;
    MakeDelegate(call6, std::bind(functionClass));
    ASSERT_TRUE(event.Register(call6));
    MakeDelegate(call7, std::bind(functionClass,84));
    ASSERT_TRUE(event.Register(call7));

    ASSERT_FALSE(event.FireEvent());
    LOG_DEBUG("again")
    ASSERT_FALSE(event.FireEvent());

    ASSERT_EQ(i, 7);
}
TEST(UnOrderedEvent, UnOrderedEvent) {
    int i = 0;

    EXPECT_EQ(1, 1);
    UnOrderedEvent event{};
    // lambda
    auto call1 = Delegate([&i]() {
        LOG_DEBUG("call lambda");
        ++i;
    });
    event += call1;
    ASSERT_FALSE(event.Register(call1));

    ASSERT_TRUE(event.RegisterOnce(call1));
    ASSERT_FALSE(event.RegisterOnce(call1));

    ASSERT_FALSE(event.FireEvent());
    LOG_DEBUG("again")
    ASSERT_FALSE(event.FireEvent());

    ASSERT_EQ(i, 3);
}

TEST(MultiOrderedEvent, fail) {
    int i = 0;

    EXPECT_EQ(1, 1);
    UnOrderedEvent event{};
    // lambda

    event +=  Delegate([&i]() {
      LOG_DEBUG("call lambda");
      ++i;
    });;
    ASSERT_TRUE(event.Register( Delegate([&i]() {
      LOG_DEBUG("call lambda");
      ++i;
    })));

    for(int j =0; j <10;++j){
        auto call1 = Delegate([&j]() {
          LOG_DEBUG("call lambda\t"<<j);
        });
        event += call1;
    }

    // 没有事件可以调用
    ASSERT_TRUE(event.FireEvent());

    ASSERT_EQ(i, 0);
}
int main(int argc, char **argv) {
    int iRet = 0;
    iRet = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    sleep(1);
    return iRet;
}