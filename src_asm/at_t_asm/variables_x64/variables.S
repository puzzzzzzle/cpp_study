// .file variable.S
.section .data
/*
标签(变量名)：关联了当前地址
这种是真的在data中有数据
*/
output: .ascii "hello,world!\n"
/* 定义字符串的长度, 直接被转换为了对应值
   . 表示 当前内存位置
   当前内存位置 - output开始位置， 就是长度
   = 或者 .equ 是一种编译期标记， data中并没有 在编译时直接替换
*/
len = . - output

/*
i1 才是内存值, 存储在 data 中
*/
i1: .int 1024

.section .text
.globl _start
_start:
     mov $1, %rax    # sys_write
     mov $1, %rdi  # fd = 1
     mov $output,%rsi  # const char *
     mov $len,%rdx   # char len
     syscall
     
 	 mov $0x3c,%rax       #系统调用值 60 syc_exit
     mov $0,%rdi       #退出码    可以用echo $? 查看
     syscall       #Linux系统调用