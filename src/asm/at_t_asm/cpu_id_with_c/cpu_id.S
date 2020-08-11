.section .data                           #以下为数据段
    output:                     			#标签(变量名)：关联了当前地址
        .ascii "cpu info is %s\n\0"
    len=.-output  			#定义字符串的长度
.section .bss
    .lcomm buffer 12
.section .text  					#以下为代码段
.globl _start						#起始的函数名
_start:
    movl $0, %eax
    cpuid
    movl $buffer, %edi
    movl %ebx, (%edi)
    movl %edx, 4(%edi)
    movl %ecx, 8(%edi)

    pushl $buffer
    pushl $output
    call printf
    addl $8, %esp
    pushl $0
    call exit
