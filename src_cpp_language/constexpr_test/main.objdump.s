
CMakeFiles/src_cpp_language_constexpr_test.dir/main.cpp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <main>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	53                   	push   %rbx
   9:	48 83 ec 18          	sub    $0x18,%rsp
   d:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  14:	00 00 
  16:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  1a:	31 c0                	xor    %eax,%eax
  1c:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 23 <main+0x23>
  23:	48 89 c6             	mov    %rax,%rsi
  26:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 2d <main+0x2d>
  2d:	48 89 c7             	mov    %rax,%rdi
  30:	e8 00 00 00 00       	call   35 <main+0x35>
  35:	48 8d 45 e2          	lea    -0x1e(%rbp),%rax
  39:	48 89 c7             	mov    %rax,%rdi
  3c:	e8 00 00 00 00       	call   41 <main+0x41>
  41:	c7 45 e4 08 00 00 00 	movl   $0x8,-0x1c(%rbp)
  48:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  4b:	89 c6                	mov    %eax,%esi
  4d:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 54 <main+0x54>
  54:	48 89 c7             	mov    %rax,%rdi
  57:	e8 00 00 00 00       	call   5c <main+0x5c>
  5c:	48 89 c2             	mov    %rax,%rdx
  5f:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 66 <main+0x66>
  66:	48 89 c6             	mov    %rax,%rsi
  69:	48 89 d7             	mov    %rdx,%rdi
  6c:	e8 00 00 00 00       	call   71 <main+0x71>
  71:	48 89 c3             	mov    %rax,%rbx
  74:	8b 45 e4             	mov    -0x1c(%rbp),%eax
  77:	89 c7                	mov    %eax,%edi
  79:	e8 00 00 00 00       	call   7e <main+0x7e>
  7e:	89 c6                	mov    %eax,%esi
  80:	48 89 df             	mov    %rbx,%rdi
  83:	e8 00 00 00 00       	call   88 <main+0x88>
  88:	be 0a 00 00 00       	mov    $0xa,%esi
  8d:	48 89 c7             	mov    %rax,%rdi
  90:	e8 00 00 00 00       	call   95 <main+0x95>
  95:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 9c <main+0x9c>
  9c:	48 89 c6             	mov    %rax,%rsi
  9f:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # a6 <main+0xa6>
  a6:	48 89 c7             	mov    %rax,%rdi
  a9:	e8 00 00 00 00       	call   ae <main+0xae>
  ae:	48 8d 45 e3          	lea    -0x1d(%rbp),%rax
  b2:	48 89 c7             	mov    %rax,%rdi
  b5:	e8 00 00 00 00       	call   ba <main+0xba>
  ba:	b8 00 00 00 00       	mov    $0x0,%eax
  bf:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  c3:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
  ca:	00 00 
  cc:	74 05                	je     d3 <main+0xd3>
  ce:	e8 00 00 00 00       	call   d3 <main+0xd3>
  d3:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
  d7:	c9                   	leave  
  d8:	c3                   	ret    

00000000000000d9 <_Z41__static_initialization_and_destruction_0ii>:
  d9:	f3 0f 1e fa          	endbr64 
  dd:	55                   	push   %rbp
  de:	48 89 e5             	mov    %rsp,%rbp
  e1:	48 83 ec 10          	sub    $0x10,%rsp
  e5:	89 7d fc             	mov    %edi,-0x4(%rbp)
  e8:	89 75 f8             	mov    %esi,-0x8(%rbp)
  eb:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
  ef:	75 3b                	jne    12c <_Z41__static_initialization_and_destruction_0ii+0x53>
  f1:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
  f8:	75 32                	jne    12c <_Z41__static_initialization_and_destruction_0ii+0x53>
  fa:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 101 <_Z41__static_initialization_and_destruction_0ii+0x28>
 101:	48 89 c7             	mov    %rax,%rdi
 104:	e8 00 00 00 00       	call   109 <_Z41__static_initialization_and_destruction_0ii+0x30>
 109:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 110 <_Z41__static_initialization_and_destruction_0ii+0x37>
 110:	48 89 c2             	mov    %rax,%rdx
 113:	48 8d 05 00 00 00 00 	lea    0x0(%rip),%rax        # 11a <_Z41__static_initialization_and_destruction_0ii+0x41>
 11a:	48 89 c6             	mov    %rax,%rsi
 11d:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 124 <_Z41__static_initialization_and_destruction_0ii+0x4b>
 124:	48 89 c7             	mov    %rax,%rdi
 127:	e8 00 00 00 00       	call   12c <_Z41__static_initialization_and_destruction_0ii+0x53>
 12c:	90                   	nop
 12d:	c9                   	leave  
 12e:	c3                   	ret    

000000000000012f <_GLOBAL__sub_I_main.cpp>:
 12f:	f3 0f 1e fa          	endbr64 
 133:	55                   	push   %rbp
 134:	48 89 e5             	mov    %rsp,%rbp
 137:	be ff ff 00 00       	mov    $0xffff,%esi
 13c:	bf 01 00 00 00       	mov    $0x1,%edi
 141:	e8 93 ff ff ff       	call   d9 <_Z41__static_initialization_and_destruction_0ii>
 146:	5d                   	pop    %rbp
 147:	c3                   	ret    

Disassembly of section .text._Z9factoriali:

0000000000000000 <_Z9factoriali>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	89 7d fc             	mov    %edi,-0x4(%rbp)
   f:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
  13:	7e 13                	jle    28 <_Z9factoriali+0x28>
  15:	8b 45 fc             	mov    -0x4(%rbp),%eax
  18:	83 e8 01             	sub    $0x1,%eax
  1b:	89 c7                	mov    %eax,%edi
  1d:	e8 00 00 00 00       	call   22 <_Z9factoriali+0x22>
  22:	0f af 45 fc          	imul   -0x4(%rbp),%eax
  26:	eb 05                	jmp    2d <_Z9factoriali+0x2d>
  28:	b8 01 00 00 00       	mov    $0x1,%eax
  2d:	c9                   	leave  
  2e:	c3                   	ret    

Disassembly of section .text._ZN6constNILi24EEC2Ev:

0000000000000000 <_ZN6constNILi24EEC1Ev>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10:	be 18 00 00 00       	mov    $0x18,%esi
  15:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 1c <_ZN6constNILi24EEC1Ev+0x1c>
  1c:	48 89 c7             	mov    %rax,%rdi
  1f:	e8 00 00 00 00       	call   24 <_ZN6constNILi24EEC1Ev+0x24>
  24:	be 0a 00 00 00       	mov    $0xa,%esi
  29:	48 89 c7             	mov    %rax,%rdi
  2c:	e8 00 00 00 00       	call   31 <_ZN6constNILi24EEC1Ev+0x31>
  31:	90                   	nop
  32:	c9                   	leave  
  33:	c3                   	ret    

Disassembly of section .text._ZN6constNILi9EEC2Ev:

0000000000000000 <_ZN6constNILi9EEC1Ev>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	48 83 ec 10          	sub    $0x10,%rsp
   c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  10:	be 09 00 00 00       	mov    $0x9,%esi
  15:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 1c <_ZN6constNILi9EEC1Ev+0x1c>
  1c:	48 89 c7             	mov    %rax,%rdi
  1f:	e8 00 00 00 00       	call   24 <_ZN6constNILi9EEC1Ev+0x24>
  24:	be 0a 00 00 00       	mov    $0xa,%esi
  29:	48 89 c7             	mov    %rax,%rdi
  2c:	e8 00 00 00 00       	call   31 <_ZN6constNILi9EEC1Ev+0x31>
  31:	90                   	nop
  32:	c9                   	leave  
  33:	c3                   	ret    
