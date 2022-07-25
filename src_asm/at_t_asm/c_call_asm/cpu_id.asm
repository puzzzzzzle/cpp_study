.section .data                           #以下为数据段
    output:                     			#标签(变量名)：关联了当前地址
        .ascii "cpu info is 'xxxxxxxxxxxx'\n"
    len = . - output  			#定义字符串的长度
.section .text  					#以下为代码段
.globl cpu_id						#起始的函数名
cpu_id:
    // enter $0, $0
    pushq %rbp
    movq %rsp,  %rbp
    
    # 获取cpuid
    movq $0, %rax
    cpuid
    // 获取output字符串地址
    movq $output, %rdi

    // cpuid 每个输出寄存器上只放4byte的数据
    movl %ebx, 13(%rdi)
    movl %edx, 17(%rdi)
    movl %ecx, 21(%rdi)

    # 输出cpuip
    movq $4, %rax       #系统调用值 $4—输出(writr)   $4---立即数（常量）
    movq $1, %rbx      # I/O设备：0-标准输入  1-标准输出  2-错误输出
    movq $output,%rcx   #输出内容的地址
    movq $len,%rdx   #输出内容的长度
    int $0x80   #Linux 0x080号系统调用

    // 下面 等价与 leave 指令
    //leave
    movq %rbp, %rsp
    popq %rbp
    ret
