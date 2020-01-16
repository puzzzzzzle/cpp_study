//
// Created by tao on 19-1-17.
//
#include <iostream>

#include "common_includes.h"
#include "dyn_aspect.hpp"
#include "time_gap.hpp"
using namespace std;

struct AspectDemo {
    void Before(...) {
        iCounter++;
        cout << "Aspect : Before, counter is " << iCounter << endl;
    }

    void After(...) {
        iCounter++;
        cout << "Aspect : After, counter is " << iCounter << endl;
    }

private:
    int iCounter = 0;
};
struct TimeElapsedAspect {
    void Before(...) {
        //        m_lastTime = m_t.elapsed();
    }

    void After(...) { cout << "time elapsed: " << m_t.gap() << endl; }

private:
    TimeGap m_t;
};

struct LoggingAspect {
    void Before(...) { std::cout << "entering" << std::endl; }

    void After(...) { std::cout << "leaving" << std::endl; }
};
double Demo1(int i) {
    cout << "Demo1 run, input int value is " << i << "." << endl;
    cout << "Demo1 has a return value with type is double and value is -1.5." << endl;
    return -1.5;
}

bool Demo2() {
    cout << "Demo2 run, without input." << endl;
    cout << "Demo2 has a return value with type is bool and value is true." << endl;
    return true;
}

int Demo3() {
    cout << "Demo3 run, without input." << endl;
    cout << "Demo3 has a return value with type is int and value is -1." << endl;
    return -1;
}

void Demo4() { cout << "Demo4 run, without input." << endl; }
TEST(AOP, test1) {
    cout << "AOP called : Demo1 : " << endl;
    cout << "Ret: " << (AOP<decltype(Demo1(0)), AspectDemo, TimeElapsedAspect, LoggingAspect>(Demo1, 12)) << endl;
    cout << endl;

    cout << "AOP called : Demo2 : " << endl;
    cout << "Ret:" << (AOP<bool, AspectDemo, AspectDemo>(Demo2)) << endl;
    cout << endl;

    cout << "Call directly : Demo3 : " << endl;
    Demo3();

    //    (VAOP<AspectDemo, AspectDemo>(Demo4));
    cout << endl;
}
int main(int argc, char **argv) {
    int iRet = 0;
    iRet     = beforeRun();
    if (iRet) {
        std::cerr << "init fail with " << iRet << std::endl;
    }
    testing::InitGoogleTest(&argc, argv);
    iRet = RUN_ALL_TESTS();
    return iRet;
}