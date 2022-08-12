.section .data


.section .text
.globl _start
_start:


 	 mov $0x3c,%rax       #系统调用值 60 syc_exit
     mov $0,%rdi       #退出码    可以用echo $? 查看
     syscall       #Linux系统调用