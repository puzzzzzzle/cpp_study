
main.cpp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  13:	00 00 
  15:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
  19:	31 c0                	xor    %eax,%eax
  1b:	48 8d 45 f6          	lea    -0xa(%rbp),%rax
  1f:	48 89 c7             	mov    %rax,%rdi
  22:	e8 00 00 00 00       	call   27 <main+0x27>
  27:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
  2b:	48 89 c7             	mov    %rax,%rdi
  2e:	e8 00 00 00 00       	call   33 <main+0x33>
  33:	e8 00 00 00 00       	call   38 <main+0x38>
  38:	b8 00 00 00 00       	mov    $0x0,%eax
  3d:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
  41:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
  48:	00 00 
  4a:	74 05                	je     51 <main+0x51>
  4c:	e8 00 00 00 00       	call   51 <main+0x51>
  51:	c9                   	leave  
  52:	c3                   	ret    

Disassembly of section .text._ZN6Class23funEv:

0000000000000000 <_ZN6Class23funEv>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 17 <_ZN6Class23funEv+0x17>
  17:	48 89 c7             	mov    %rax,%rdi
  1a:	e8 00 00 00 00       	call   1f <_ZN6Class23funEv+0x1f>
  1f:	90                   	nop
  20:	c9                   	leave  
  21:	c3                   	ret    

Disassembly of section .text._ZN6Class13funEv:

0000000000000000 <_ZN6Class13funEv>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 17 <_ZN6Class13funEv+0x17>
  17:	48 89 c7             	mov    %rax,%rdi
  1a:	e8 00 00 00 00       	call   1f <_ZN6Class13funEv+0x1f>
  1f:	90                   	nop
  20:	c9                   	leave  
  21:	c3                   	ret    
