.section .data                           #以下为数据段           
output:                     			#标签(变量名)：关联了当前地址
       .ascii "hello,world!\n"
len = . - output  			#定义字符串的长度, 直接被转换为了对应值
.section .text  					#以下为代码段
.globl _start						#起始的函数名
_start:
     mov $1, %rax    # sys_write
     mov $1, %rdi  # fd = 1
     mov $output,%rsi  # const char *
     mov $len,%rdx   # char len
     syscall
     
 	 mov $0x3c,%rax       #系统调用值 60 syc_exit
     mov $0,%rdi       #退出码    可以用echo $? 查看
     syscall       #Linux系统调用