.section .data
    f1: .double 3.14
    f2: .double 2.0
    i: .int 3
    out_str_int: .asciz "out int is %d\n"
    out_str_double: .asciz "out float is %f\n"
    out_str_double_by_address: .asciz "address out float is %f\n"

.section .text
_print_int:
    push %rbp
    movq %rsp,%rbp
    # 输出 整数
    movq %rdi,%rsi
    lea out_str_int(%rip),%rdi
    call printf
    popq %rbp
    ret
_print_double:
# 这种方式需要开辟栈, 因为 vmovsd 不支持直接从r64 到xmm64, 必须由 m64中转
    push %rbp
    movq %rsp,%rbp
        # 栈对齐， sse 及后续指令需要 16 位栈对齐
    sub $0x10,%rsp
        # 输出 浮点
        # gdb : print $xmm1
        # gdb : info r xmm
    movq %rdi,-0x8(%rbp)
    vmovsd -0x8(%rbp), %xmm0
    leaq out_str_double(%rip),%rdi
    movq $1, %rax           # 1 FP arg in xmm registers (as opposed to memory)
    call printf
    movq %rbp,%rsp
    popq %rbp
    ret
_print_double_no_stack:
# 这种方式不用开辟栈
    push %rbp
    movq %rsp,%rbp

    movq %rdi,%xmm0
    leaq out_str_double(%rip),%rdi
    movq $1, %rax
    call printf

    popq %rbp
    ret
_print_double_by_address:
# 这种方式不用开辟栈
    push %rbp
    movq %rsp,%rbp
    vmovsd (%rdi), %xmm0
    leaq out_str_double_by_address(%rip),%rdi
    movq $1, %rax           # 1 FP arg in xmm registers (as opposed to memory)
    call printf
    popq %rbp
    ret
_avx_div:
    push %rbp
    movq %rsp,%rbp

    # 3.14/2.0
    movq f1(%rip), %xmm0
    movq f2(%rip), %xmm1
    vdivsd %xmm1,%xmm0,%xmm0

    movq %xmm0,%rdi
    call _print_double_no_stack

    popq %rbp
    ret


.globl _start
_start:
     call _avx_div

     movq f1(%rip), %rdi
     call _print_double

     movq f1(%rip), %rdi
     call _print_double_no_stack

     lea f1(%rip), %rdi
     call _print_double_by_address


 	 mov $0x3c,%rax       #系统调用值 60 syc_exit
     mov $0,%rdi       #退出码    可以用echo $? 查看
     syscall       #Linux系统调用