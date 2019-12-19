; -----------------------------------------------------------------------------
; 一个返回三个数字中最大值的 64 位函数。
; 函数有如下形式:
;
;   int64_t maxofthree(int64_t x, int64_t y, int64_t z)
;
; 注意到参数通过 rdi, rsi 和 rdx 传递。
; 我们只需将返回值存放在 rax 中。
; -----------------------------------------------------------------------------

        global  maxofthree
        section .text
maxofthree:
        mov     rax, rdi                ; rax 寄存器初始保存 x 的值
        cmp     rax, rsi                ; x 小于 y 吗?
        cmovl   rax, rsi                ; 如果是的话, 返回值置为 y
        cmp     rax, rdx                ; x 和 y 中的最大值小于 z 吗?
        cmovl   rax, rdx                ; 如果是的话, 返回值置为 z
        ret                             ; 最大值被存放在 rax 中