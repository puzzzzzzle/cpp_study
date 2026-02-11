# C++ 学习项目
- 依赖在`cpp_bootstrap/Docker/arch_clion_local.Dockerfile`中定义, 使用 docker 管理
- 编译方式: mkdir -p build && cd build && cmake .. && make TARGET 方式
    - 二进制名字为相对路径把`/` 替换为`_`
    - eg: `make src_linux_tests_src_asm_at_t_asm_c_call_asm`
- cmake 自动扫描指定的文件夹下的子工程, 每个工程独立编译 bin/lib
    - build 下额 makefile 下有完整的目标列表