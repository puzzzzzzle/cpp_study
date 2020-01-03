; ----------------------------------------------------------------------------------------
; 仅使用系统调用来输出 "Hello, World" 到控制台
; ----------------------------------------------------------------------------------------

section .data

message:     db      "Hello, World1", 10      ; 注意到最后的换行
messageLen:     equ     $-message       ;

section .bss                            ; bss


section .text

global  _start

_start:
        ; write(1, message, 13)
        mov     eax, 4                  ; 1 号系统调用是写操作
        mov     ebx, 1                  ; 1 号文件系统调用是标准输出
        mov     ecx, message            ; 输出字符串的地址
        mov     edx, messageLen                 ; 字符串的长度
        int     80H                         ; 调用系统执行写操作

        ; exit(0)
        mov     eax, 1                 ; 60 号系统调用是退出
        xor     ebx, ebx                ; 0 号系统调用作为退出
        int     80H                         ; 调用系统执行退出

