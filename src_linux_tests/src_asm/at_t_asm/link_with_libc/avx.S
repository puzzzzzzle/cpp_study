.section .data
    f1: .double 3.14
    f2: .double 2.0
    i: .int 3
    out_str_int: .asciz "out int is %d\n"
    out_str_double: .asciz "out float is %f\n"

.section .text
_print_int:
    push %rbp
    movq %rsp,%rbp
    # 输出 整数
    movq %rdi,%rsi
    lea out_str_int(%rip),%rax
    mov %rax,%rdi
    call printf
    leave
    ret
_print_double:
    push %rbp
    movq %rsp,%rbp
    # 栈对齐， sse 及后续指令需要 16 位栈对齐
    sub $0x10,%rsp
    # 输出 浮点
    # gdb : print $xmm1
    # gdb : info r xmm
    movq %rdi,-0x8(%rbp)
    vmovsd -0x8(%rbp), %xmm0
    leaq out_str_double(%rip),%rax
    movq %rax,%rdi
    movq $1, %rax           # 1 FP arg in xmm registers (as opposed to memory)
    call printf
    leave
    ret
_avx_div:
    push %rbp
    movq %rsp,%rbp
    sub $0x10,%rsp

    # 3.14/2.0
    vmovsd f1(%rip), %xmm0
    vmovsd f2(%rip), %xmm1
    vdivsd %xmm1,%xmm0,%xmm0

    # 把结果移回到 rdi, 并打印
    vmovsd %xmm0,-0x8(%rbp)
    mov -0x8(%rbp), %rdi
    call _print_double

    leave
    ret

/*
.globl _start
_start:
     call _avx_div
 	 mov $0x3c,%rax       #系统调用值 60 syc_exit
     mov $0,%rdi       #退出码    可以用echo $? 查看
     syscall       #Linux系统调用
*/

.globl main
main:
    push %rbp
    movq %rsp,%rbp

    call _avx_div

    mov $0, %rax
    leave
    ret