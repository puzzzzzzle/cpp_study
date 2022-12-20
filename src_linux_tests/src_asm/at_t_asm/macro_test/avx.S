.macro print_int s,i
    movq \i(%rip),%rsi
    lea \s(%rip),%rax
    mov %rax,%rdi
    call printf
.endm

.section .data
    i: .int 3
    out_str_int: .asciz "out int is %d\n"

.section .text

.globl main
main:
    push %rbp
    movq %rsp,%rbp

    print_int out_str_int,i

    mov $0, %rax
    leave
    ret