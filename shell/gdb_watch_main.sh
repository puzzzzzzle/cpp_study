# gdb 自动调试工具
# 监视给定的线程 发生任何exception时（包括已经被捕获的异常， 丢弃的异常）， 暂停程序， 打印堆栈， 然后再放行
# 测试中， 有问题请联系khalidzhang (khalidzhang@tencent.com)


# eg : ./gdb_watch_main.sh run ./exe_process
# eg : ./gdb_watch_main.sh attach [pid] >watch.log &


if [ "attach" = $1 ];then
  gdb -p $2 -batch -q  -x gdb_attach_watch_exception.sh
elif [ "run" = $1 ] ; then
  gdb $2 -batch -q  -x gdb_run_watch_exception.sh
else
  echo "unkonun cmd type " $1
fi
