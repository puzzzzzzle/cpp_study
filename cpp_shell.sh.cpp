#if 0/* run cpp source file from shell directly, eg: ./cpp_shell.sh.cpp arg1 arg2
SOURCE_NAME=$(basename "$0") ; c++ -O3 -o /tmp/$SOURCE_NAME.out "$0" && /tmp/$SOURCE_NAME.out "$@"; exit $?; */
#endif

// 上面的部分, 会被shell解析, 然后自动编制并运行
// 这样就可以像shell一样运行c++源码"脚本"了
// ./cpp_shell.sh.cpp 直接运行...

// 下面这种也等价, 只是稍微少点注释, 当然, 展开成多行脚本文件也可以
#if 0
SOURCE_NAME=$(basename "$0") && c++ -O3 -o /tmp/$SOURCE_NAME.out "$0" && /tmp/$SOURCE_NAME.out ; exit;
#endif


#include <iostream>

int main(int argc, char *argv[]) {
    std::cout << "hello world form c++ 'script'." << std::endl;
    for (int i = 0; i < argc; ++i) {
        std::cout << "arg at " << i << " is " << argv[i] << std::endl;
    }
    // 返回值也能正常收到
    return 22;
}