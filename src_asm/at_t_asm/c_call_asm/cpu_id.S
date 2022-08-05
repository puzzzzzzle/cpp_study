.section .data                           #以下为数据段
out_put:                     			#标签(变量名)：关联了当前地址
    .ascii "cpu info is 'xxxxxxxxxxxx'\n"
.equ out_put_len, . - out_put


.section .text  					#以下为代码段
.globl cpu_id						#起始的函数名
cpu_id:
    # enter $0, $0

    pushq %rbp
    movq %rsp,  %rbp

    # 获取cpuid
    movq $0, %rax
    cpuid
    # 获取out_put字符串地址
    lea out_put(%rip), %rdi

    # cpuid 每个输出寄存器上只放4byte的数据
    movl %ebx, 13(%rdi)
    movl %edx, 17(%rdi)
    movl %ecx, 21(%rdi)

#/*
    # 输出cpuip
    movq $1, %rax       #系统调用值 $1—输出(writr)

    movq $1, %rdi      # I/O设备：0-标准输入  1-标准输出  2-错误输出
    leaq out_put(%rip), %rsi
    mov $out_put_len ,%rdx
    syscall
#*/
/*
    leaq out_put(%rip), %rdi
    xor %rax,%rax
    call printf
*/
    # 下面 等价与 leave 指令
    #leave
    movq %rbp, %rsp
    popq %rbp
    ret
