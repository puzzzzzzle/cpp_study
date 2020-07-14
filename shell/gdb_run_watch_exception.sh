# gdb 自动调试工具
# 监视给定的线程 发生任何exception时（包括已经被捕获的异常， 丢弃的异常）， 暂停程序， 打印堆栈， 然后再放行
# 测试中， 有问题请联系khalidzhang (khalidzhang@tencent.com)

# 本文件负责run的调度

source ./gdb_catch_reg.sh
reg_throw_handle
r
