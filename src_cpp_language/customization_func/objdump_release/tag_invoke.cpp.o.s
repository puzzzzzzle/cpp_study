
tag_invoke.cpp.o:     file format elf64-x86-64


Disassembly of section .text:

0000000000000000 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0>:
   0:	41 55                	push   %r13
   2:	ba 07 00 00 00       	mov    $0x7,%edx
   7:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # e <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0xe>
   e:	41 54                	push   %r12
  10:	55                   	push   %rbp
  11:	53                   	push   %rbx
  12:	48 81 ec 88 00 00 00 	sub    $0x88,%rsp
  19:	48 8b 2d 00 00 00 00 	mov    0x0(%rip),%rbp        # 20 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x20>
  20:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  27:	00 00 
  29:	48 89 44 24 78       	mov    %rax,0x78(%rsp)
  2e:	31 c0                	xor    %eax,%eax
  30:	4c 8d 6c 24 30       	lea    0x30(%rsp),%r13
  35:	4c 8d 64 24 20       	lea    0x20(%rsp),%r12
  3a:	48 89 ef             	mov    %rbp,%rdi
  3d:	e8 00 00 00 00       	call   42 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x42>
  42:	ba 05 00 00 00       	mov    $0x5,%edx
  47:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 4e <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x4e>
  4e:	48 89 ef             	mov    %rbp,%rdi
  51:	e8 00 00 00 00       	call   56 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x56>
  56:	31 ff                	xor    %edi,%edi
  58:	e8 00 00 00 00       	call   5d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x5d>
  5d:	48 8d 7c 24 08       	lea    0x8(%rsp),%rdi
  62:	48 89 44 24 08       	mov    %rax,0x8(%rsp)
  67:	e8 00 00 00 00       	call   6c <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x6c>
  6c:	48 8d 15 00 00 00 00 	lea    0x0(%rip),%rdx        # 73 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x73>
  73:	be 40 00 00 00       	mov    $0x40,%esi
  78:	4c 89 ef             	mov    %r13,%rdi
  7b:	48 89 c1             	mov    %rax,%rcx
  7e:	e8 00 00 00 00       	call   83 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x83>
  83:	4c 89 ef             	mov    %r13,%rdi
  86:	4c 89 64 24 10       	mov    %r12,0x10(%rsp)
  8b:	e8 00 00 00 00       	call   90 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x90>
  90:	48 89 c3             	mov    %rax,%rbx
  93:	48 83 f8 0f          	cmp    $0xf,%rax
  97:	0f 87 b3 01 00 00    	ja     250 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x250>
  9d:	48 83 f8 01          	cmp    $0x1,%rax
  a1:	0f 84 61 01 00 00    	je     208 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x208>
  a7:	48 85 c0             	test   %rax,%rax
  aa:	0f 85 28 02 00 00    	jne    2d8 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x2d8>
  b0:	4c 89 e0             	mov    %r12,%rax
  b3:	48 89 5c 24 18       	mov    %rbx,0x18(%rsp)
  b8:	48 89 ef             	mov    %rbp,%rdi
  bb:	c6 04 18 00          	movb   $0x0,(%rax,%rbx,1)
  bf:	48 8b 54 24 18       	mov    0x18(%rsp),%rdx
  c4:	48 8b 74 24 10       	mov    0x10(%rsp),%rsi
  c9:	e8 00 00 00 00       	call   ce <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0xce>
  ce:	ba 05 00 00 00       	mov    $0x5,%edx
  d3:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # da <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0xda>
  da:	48 89 c3             	mov    %rax,%rbx
  dd:	48 89 c7             	mov    %rax,%rdi
  e0:	e8 00 00 00 00       	call   e5 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0xe5>
  e5:	48 89 df             	mov    %rbx,%rdi
  e8:	ba 01 00 00 00       	mov    $0x1,%edx
  ed:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # f4 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0xf4>
  f4:	e8 00 00 00 00       	call   f9 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0xf9>
  f9:	48 89 df             	mov    %rbx,%rdi
  fc:	ba 0c 00 00 00       	mov    $0xc,%edx
 101:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 108 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x108>
 108:	e8 00 00 00 00       	call   10d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x10d>
 10d:	48 89 df             	mov    %rbx,%rdi
 110:	ba 05 00 00 00       	mov    $0x5,%edx
 115:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 11c <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x11c>
 11c:	e8 00 00 00 00       	call   121 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x121>
 121:	48 89 df             	mov    %rbx,%rdi
 124:	ba 46 00 00 00       	mov    $0x46,%edx
 129:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 130 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x130>
 130:	e8 00 00 00 00       	call   135 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x135>
 135:	ba 01 00 00 00       	mov    $0x1,%edx
 13a:	48 89 df             	mov    %rbx,%rdi
 13d:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 144 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x144>
 144:	e8 00 00 00 00       	call   149 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x149>
 149:	48 89 df             	mov    %rbx,%rdi
 14c:	be 2a 00 00 00       	mov    $0x2a,%esi
 151:	e8 00 00 00 00       	call   156 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x156>
 156:	ba 04 00 00 00       	mov    $0x4,%edx
 15b:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 162 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x162>
 162:	48 89 c5             	mov    %rax,%rbp
 165:	48 89 c7             	mov    %rax,%rdi
 168:	e8 00 00 00 00       	call   16d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x16d>
 16d:	ba 69 00 00 00       	mov    $0x69,%edx
 172:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 179 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x179>
 179:	48 89 ef             	mov    %rbp,%rdi
 17c:	e8 00 00 00 00       	call   181 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x181>
 181:	ba 01 00 00 00       	mov    $0x1,%edx
 186:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 18d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x18d>
 18d:	48 89 ef             	mov    %rbp,%rdi
 190:	e8 00 00 00 00       	call   195 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x195>
 195:	48 8b 45 00          	mov    0x0(%rbp),%rax
 199:	48 8b 40 e8          	mov    -0x18(%rax),%rax
 19d:	48 8b 9c 05 f0 00 00 	mov    0xf0(%rbp,%rax,1),%rbx
 1a4:	00 
 1a5:	48 85 db             	test   %rbx,%rbx
 1a8:	0f 84 57 01 00 00    	je     305 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x305>
 1ae:	80 7b 38 00          	cmpb   $0x0,0x38(%rbx)
 1b2:	74 6c                	je     220 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x220>
 1b4:	0f be 73 43          	movsbl 0x43(%rbx),%esi
 1b8:	48 89 ef             	mov    %rbp,%rdi
 1bb:	e8 00 00 00 00       	call   1c0 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x1c0>
 1c0:	48 89 c7             	mov    %rax,%rdi
 1c3:	e8 00 00 00 00       	call   1c8 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x1c8>
 1c8:	48 8b 7c 24 10       	mov    0x10(%rsp),%rdi
 1cd:	4c 39 e7             	cmp    %r12,%rdi
 1d0:	74 0e                	je     1e0 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x1e0>
 1d2:	48 8b 44 24 20       	mov    0x20(%rsp),%rax
 1d7:	48 8d 70 01          	lea    0x1(%rax),%rsi
 1db:	e8 00 00 00 00       	call   1e0 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x1e0>
 1e0:	48 8b 44 24 78       	mov    0x78(%rsp),%rax
 1e5:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
 1ec:	00 00 
 1ee:	0f 85 16 01 00 00    	jne    30a <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x30a>
 1f4:	48 81 c4 88 00 00 00 	add    $0x88,%rsp
 1fb:	5b                   	pop    %rbx
 1fc:	5d                   	pop    %rbp
 1fd:	41 5c                	pop    %r12
 1ff:	41 5d                	pop    %r13
 201:	c3                   	ret    
 202:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
 208:	0f b6 44 24 30       	movzbl 0x30(%rsp),%eax
 20d:	88 44 24 20          	mov    %al,0x20(%rsp)
 211:	e9 9a fe ff ff       	jmp    b0 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0xb0>
 216:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
 21d:	00 00 00 
 220:	48 89 df             	mov    %rbx,%rdi
 223:	e8 00 00 00 00       	call   228 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x228>
 228:	48 8b 03             	mov    (%rbx),%rax
 22b:	be 0a 00 00 00       	mov    $0xa,%esi
 230:	48 8b 40 30          	mov    0x30(%rax),%rax
 234:	48 3b 05 00 00 00 00 	cmp    0x0(%rip),%rax        # 23b <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x23b>
 23b:	0f 84 77 ff ff ff    	je     1b8 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x1b8>
 241:	48 89 df             	mov    %rbx,%rdi
 244:	ff d0                	call   *%rax
 246:	0f be f0             	movsbl %al,%esi
 249:	e9 6a ff ff ff       	jmp    1b8 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x1b8>
 24e:	66 90                	xchg   %ax,%ax
 250:	48 8d 78 01          	lea    0x1(%rax),%rdi
 254:	e8 00 00 00 00       	call   259 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x259>
 259:	48 89 5c 24 20       	mov    %rbx,0x20(%rsp)
 25e:	48 89 44 24 10       	mov    %rax,0x10(%rsp)
 263:	83 fb 08             	cmp    $0x8,%ebx
 266:	73 28                	jae    290 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x290>
 268:	f6 c3 04             	test   $0x4,%bl
 26b:	75 73                	jne    2e0 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x2e0>
 26d:	85 db                	test   %ebx,%ebx
 26f:	74 0c                	je     27d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x27d>
 271:	0f b6 54 24 30       	movzbl 0x30(%rsp),%edx
 276:	88 10                	mov    %dl,(%rax)
 278:	f6 c3 02             	test   $0x2,%bl
 27b:	75 76                	jne    2f3 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x2f3>
 27d:	48 8b 44 24 10       	mov    0x10(%rsp),%rax
 282:	e9 2c fe ff ff       	jmp    b3 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0xb3>
 287:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
 28e:	00 00 
 290:	48 8b 54 24 30       	mov    0x30(%rsp),%rdx
 295:	48 8d 70 08          	lea    0x8(%rax),%rsi
 299:	48 83 e6 f8          	and    $0xfffffffffffffff8,%rsi
 29d:	48 89 10             	mov    %rdx,(%rax)
 2a0:	89 da                	mov    %ebx,%edx
 2a2:	49 8b 4c 15 f8       	mov    -0x8(%r13,%rdx,1),%rcx
 2a7:	48 89 4c 10 f8       	mov    %rcx,-0x8(%rax,%rdx,1)
 2ac:	48 29 f0             	sub    %rsi,%rax
 2af:	49 29 c5             	sub    %rax,%r13
 2b2:	01 d8                	add    %ebx,%eax
 2b4:	83 e0 f8             	and    $0xfffffff8,%eax
 2b7:	83 f8 08             	cmp    $0x8,%eax
 2ba:	72 c1                	jb     27d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x27d>
 2bc:	83 e0 f8             	and    $0xfffffff8,%eax
 2bf:	31 d2                	xor    %edx,%edx
 2c1:	89 d1                	mov    %edx,%ecx
 2c3:	83 c2 08             	add    $0x8,%edx
 2c6:	49 8b 7c 0d 00       	mov    0x0(%r13,%rcx,1),%rdi
 2cb:	48 89 3c 0e          	mov    %rdi,(%rsi,%rcx,1)
 2cf:	39 c2                	cmp    %eax,%edx
 2d1:	72 ee                	jb     2c1 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x2c1>
 2d3:	eb a8                	jmp    27d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x27d>
 2d5:	0f 1f 00             	nopl   (%rax)
 2d8:	4c 89 e0             	mov    %r12,%rax
 2db:	eb 86                	jmp    263 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x263>
 2dd:	0f 1f 00             	nopl   (%rax)
 2e0:	8b 54 24 30          	mov    0x30(%rsp),%edx
 2e4:	89 10                	mov    %edx,(%rax)
 2e6:	89 da                	mov    %ebx,%edx
 2e8:	41 8b 4c 15 fc       	mov    -0x4(%r13,%rdx,1),%ecx
 2ed:	89 4c 10 fc          	mov    %ecx,-0x4(%rax,%rdx,1)
 2f1:	eb 8a                	jmp    27d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x27d>
 2f3:	89 da                	mov    %ebx,%edx
 2f5:	41 0f b7 4c 15 fe    	movzwl -0x2(%r13,%rdx,1),%ecx
 2fb:	66 89 4c 10 fe       	mov    %cx,-0x2(%rax,%rdx,1)
 300:	e9 78 ff ff ff       	jmp    27d <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x27d>
 305:	e8 00 00 00 00       	call   30a <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x30a>
 30a:	e8 00 00 00 00       	call   30f <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0+0x30f>
 30f:	90                   	nop

0000000000000310 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv>:
 310:	f3 0f 1e fa          	endbr64 
 314:	41 57                	push   %r15
 316:	4c 8d 3d 00 00 00 00 	lea    0x0(%rip),%r15        # 31d <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0xd>
 31d:	ba 07 00 00 00       	mov    $0x7,%edx
 322:	41 56                	push   %r14
 324:	4c 89 fe             	mov    %r15,%rsi
 327:	4c 8d 35 00 00 00 00 	lea    0x0(%rip),%r14        # 32e <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1e>
 32e:	41 55                	push   %r13
 330:	41 54                	push   %r12
 332:	55                   	push   %rbp
 333:	53                   	push   %rbx
 334:	48 81 ec 98 00 00 00 	sub    $0x98,%rsp
 33b:	48 8b 2d 00 00 00 00 	mov    0x0(%rip),%rbp        # 342 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x32>
 342:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
 349:	00 00 
 34b:	48 89 84 24 88 00 00 	mov    %rax,0x88(%rsp)
 352:	00 
 353:	31 c0                	xor    %eax,%eax
 355:	4c 8d 64 24 40       	lea    0x40(%rsp),%r12
 35a:	4c 8d 6c 24 30       	lea    0x30(%rsp),%r13
 35f:	48 89 ef             	mov    %rbp,%rdi
 362:	e8 00 00 00 00       	call   367 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x57>
 367:	ba 05 00 00 00       	mov    $0x5,%edx
 36c:	4c 89 f6             	mov    %r14,%rsi
 36f:	48 89 ef             	mov    %rbp,%rdi
 372:	e8 00 00 00 00       	call   377 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x67>
 377:	31 ff                	xor    %edi,%edi
 379:	e8 00 00 00 00       	call   37e <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x6e>
 37e:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
 383:	48 8d 44 24 18       	lea    0x18(%rsp),%rax
 388:	48 89 c7             	mov    %rax,%rdi
 38b:	48 89 04 24          	mov    %rax,(%rsp)
 38f:	e8 00 00 00 00       	call   394 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x84>
 394:	48 8d 15 00 00 00 00 	lea    0x0(%rip),%rdx        # 39b <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x8b>
 39b:	be 40 00 00 00       	mov    $0x40,%esi
 3a0:	4c 89 e7             	mov    %r12,%rdi
 3a3:	48 89 c1             	mov    %rax,%rcx
 3a6:	e8 00 00 00 00       	call   3ab <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x9b>
 3ab:	4c 89 e7             	mov    %r12,%rdi
 3ae:	4c 89 6c 24 20       	mov    %r13,0x20(%rsp)
 3b3:	e8 00 00 00 00       	call   3b8 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0xa8>
 3b8:	48 89 c3             	mov    %rax,%rbx
 3bb:	48 83 f8 0f          	cmp    $0xf,%rax
 3bf:	0f 87 ab 03 00 00    	ja     770 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x460>
 3c5:	48 83 f8 01          	cmp    $0x1,%rax
 3c9:	0f 84 21 03 00 00    	je     6f0 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x3e0>
 3cf:	48 85 c0             	test   %rax,%rax
 3d2:	0f 85 d8 04 00 00    	jne    8b0 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x5a0>
 3d8:	4c 89 e8             	mov    %r13,%rax
 3db:	48 89 5c 24 28       	mov    %rbx,0x28(%rsp)
 3e0:	48 89 ef             	mov    %rbp,%rdi
 3e3:	c6 04 18 00          	movb   $0x0,(%rax,%rbx,1)
 3e7:	48 8b 54 24 28       	mov    0x28(%rsp),%rdx
 3ec:	48 8b 74 24 20       	mov    0x20(%rsp),%rsi
 3f1:	e8 00 00 00 00       	call   3f6 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0xe6>
 3f6:	ba 05 00 00 00       	mov    $0x5,%edx
 3fb:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 402 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0xf2>
 402:	48 89 c3             	mov    %rax,%rbx
 405:	48 89 c7             	mov    %rax,%rdi
 408:	e8 00 00 00 00       	call   40d <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0xfd>
 40d:	48 89 df             	mov    %rbx,%rdi
 410:	ba 01 00 00 00       	mov    $0x1,%edx
 415:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 41c <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x10c>
 41c:	e8 00 00 00 00       	call   421 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x111>
 421:	48 89 df             	mov    %rbx,%rdi
 424:	ba 0a 00 00 00       	mov    $0xa,%edx
 429:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 430 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x120>
 430:	e8 00 00 00 00       	call   435 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x125>
 435:	48 89 df             	mov    %rbx,%rdi
 438:	ba 05 00 00 00       	mov    $0x5,%edx
 43d:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 444 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x134>
 444:	e8 00 00 00 00       	call   449 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x139>
 449:	48 89 df             	mov    %rbx,%rdi
 44c:	ba 46 00 00 00       	mov    $0x46,%edx
 451:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 458 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x148>
 458:	e8 00 00 00 00       	call   45d <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x14d>
 45d:	ba 01 00 00 00       	mov    $0x1,%edx
 462:	48 89 df             	mov    %rbx,%rdi
 465:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 46c <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x15c>
 46c:	e8 00 00 00 00       	call   471 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x161>
 471:	48 89 df             	mov    %rbx,%rdi
 474:	be 35 00 00 00       	mov    $0x35,%esi
 479:	e8 00 00 00 00       	call   47e <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x16e>
 47e:	ba 04 00 00 00       	mov    $0x4,%edx
 483:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 48a <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x17a>
 48a:	48 89 c3             	mov    %rax,%rbx
 48d:	48 89 c7             	mov    %rax,%rdi
 490:	e8 00 00 00 00       	call   495 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x185>
 495:	ba 6f 00 00 00       	mov    $0x6f,%edx
 49a:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 4a1 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x191>
 4a1:	48 89 df             	mov    %rbx,%rdi
 4a4:	e8 00 00 00 00       	call   4a9 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x199>
 4a9:	48 89 df             	mov    %rbx,%rdi
 4ac:	ba 01 00 00 00       	mov    $0x1,%edx
 4b1:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 4b8 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1a8>
 4b8:	e8 00 00 00 00       	call   4bd <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1ad>
 4bd:	48 8b 03             	mov    (%rbx),%rax
 4c0:	48 8b 40 e8          	mov    -0x18(%rax),%rax
 4c4:	48 8b bc 03 f0 00 00 	mov    0xf0(%rbx,%rax,1),%rdi
 4cb:	00 
 4cc:	48 85 ff             	test   %rdi,%rdi
 4cf:	0f 84 5a 04 00 00    	je     92f <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x61f>
 4d5:	80 7f 38 00          	cmpb   $0x0,0x38(%rdi)
 4d9:	0f 84 21 02 00 00    	je     700 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x3f0>
 4df:	0f be 77 43          	movsbl 0x43(%rdi),%esi
 4e3:	48 89 df             	mov    %rbx,%rdi
 4e6:	e8 00 00 00 00       	call   4eb <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1db>
 4eb:	48 89 c7             	mov    %rax,%rdi
 4ee:	e8 00 00 00 00       	call   4f3 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1e3>
 4f3:	48 8b 7c 24 20       	mov    0x20(%rsp),%rdi
 4f8:	4c 39 ef             	cmp    %r13,%rdi
 4fb:	74 0e                	je     50b <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1fb>
 4fd:	48 8b 44 24 30       	mov    0x30(%rsp),%rax
 502:	48 8d 70 01          	lea    0x1(%rax),%rsi
 506:	e8 00 00 00 00       	call   50b <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1fb>
 50b:	e8 f0 fa ff ff       	call   0 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0>
 510:	ba 07 00 00 00       	mov    $0x7,%edx
 515:	4c 89 fe             	mov    %r15,%rsi
 518:	48 89 ef             	mov    %rbp,%rdi
 51b:	e8 00 00 00 00       	call   520 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x210>
 520:	ba 05 00 00 00       	mov    $0x5,%edx
 525:	4c 89 f6             	mov    %r14,%rsi
 528:	48 89 ef             	mov    %rbp,%rdi
 52b:	e8 00 00 00 00       	call   530 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x220>
 530:	31 ff                	xor    %edi,%edi
 532:	e8 00 00 00 00       	call   537 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x227>
 537:	48 8b 3c 24          	mov    (%rsp),%rdi
 53b:	48 89 44 24 18       	mov    %rax,0x18(%rsp)
 540:	e8 00 00 00 00       	call   545 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x235>
 545:	48 8d 15 00 00 00 00 	lea    0x0(%rip),%rdx        # 54c <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x23c>
 54c:	be 40 00 00 00       	mov    $0x40,%esi
 551:	4c 89 e7             	mov    %r12,%rdi
 554:	48 89 c1             	mov    %rax,%rcx
 557:	e8 00 00 00 00       	call   55c <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x24c>
 55c:	4c 89 e7             	mov    %r12,%rdi
 55f:	4c 89 6c 24 20       	mov    %r13,0x20(%rsp)
 564:	e8 00 00 00 00       	call   569 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x259>
 569:	48 89 c3             	mov    %rax,%rbx
 56c:	48 83 f8 0f          	cmp    $0xf,%rax
 570:	0f 87 42 02 00 00    	ja     7b8 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4a8>
 576:	48 83 f8 01          	cmp    $0x1,%rax
 57a:	0f 84 80 02 00 00    	je     800 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4f0>
 580:	48 85 c0             	test   %rax,%rax
 583:	0f 85 37 03 00 00    	jne    8c0 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x5b0>
 589:	4c 89 e8             	mov    %r13,%rax
 58c:	48 89 5c 24 28       	mov    %rbx,0x28(%rsp)
 591:	48 89 ef             	mov    %rbp,%rdi
 594:	c6 04 18 00          	movb   $0x0,(%rax,%rbx,1)
 598:	48 8b 54 24 28       	mov    0x28(%rsp),%rdx
 59d:	48 8b 74 24 20       	mov    0x20(%rsp),%rsi
 5a2:	e8 00 00 00 00       	call   5a7 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x297>
 5a7:	ba 05 00 00 00       	mov    $0x5,%edx
 5ac:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 5b3 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2a3>
 5b3:	48 89 c3             	mov    %rax,%rbx
 5b6:	48 89 c7             	mov    %rax,%rdi
 5b9:	e8 00 00 00 00       	call   5be <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2ae>
 5be:	48 89 df             	mov    %rbx,%rdi
 5c1:	ba 01 00 00 00       	mov    $0x1,%edx
 5c6:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 5cd <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2bd>
 5cd:	e8 00 00 00 00       	call   5d2 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2c2>
 5d2:	48 89 df             	mov    %rbx,%rdi
 5d5:	ba 0a 00 00 00       	mov    $0xa,%edx
 5da:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 5e1 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2d1>
 5e1:	e8 00 00 00 00       	call   5e6 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2d6>
 5e6:	48 89 df             	mov    %rbx,%rdi
 5e9:	ba 05 00 00 00       	mov    $0x5,%edx
 5ee:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 5f5 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2e5>
 5f5:	e8 00 00 00 00       	call   5fa <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2ea>
 5fa:	48 89 df             	mov    %rbx,%rdi
 5fd:	ba 46 00 00 00       	mov    $0x46,%edx
 602:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 609 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2f9>
 609:	e8 00 00 00 00       	call   60e <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x2fe>
 60e:	ba 01 00 00 00       	mov    $0x1,%edx
 613:	48 89 df             	mov    %rbx,%rdi
 616:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 61d <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x30d>
 61d:	e8 00 00 00 00       	call   622 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x312>
 622:	48 89 df             	mov    %rbx,%rdi
 625:	be 35 00 00 00       	mov    $0x35,%esi
 62a:	e8 00 00 00 00       	call   62f <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x31f>
 62f:	ba 04 00 00 00       	mov    $0x4,%edx
 634:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 63b <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x32b>
 63b:	48 89 c3             	mov    %rax,%rbx
 63e:	48 89 c7             	mov    %rax,%rdi
 641:	e8 00 00 00 00       	call   646 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x336>
 646:	ba 6f 00 00 00       	mov    $0x6f,%edx
 64b:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 652 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x342>
 652:	48 89 df             	mov    %rbx,%rdi
 655:	e8 00 00 00 00       	call   65a <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x34a>
 65a:	ba 01 00 00 00       	mov    $0x1,%edx
 65f:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 666 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x356>
 666:	48 89 df             	mov    %rbx,%rdi
 669:	e8 00 00 00 00       	call   66e <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x35e>
 66e:	48 8b 03             	mov    (%rbx),%rax
 671:	48 8b 40 e8          	mov    -0x18(%rax),%rax
 675:	48 8b ac 03 f0 00 00 	mov    0xf0(%rbx,%rax,1),%rbp
 67c:	00 
 67d:	48 85 ed             	test   %rbp,%rbp
 680:	0f 84 a4 02 00 00    	je     92a <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x61a>
 686:	80 7d 38 00          	cmpb   $0x0,0x38(%rbp)
 68a:	0f 84 a8 00 00 00    	je     738 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x428>
 690:	0f be 75 43          	movsbl 0x43(%rbp),%esi
 694:	48 89 df             	mov    %rbx,%rdi
 697:	e8 00 00 00 00       	call   69c <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x38c>
 69c:	48 89 c7             	mov    %rax,%rdi
 69f:	e8 00 00 00 00       	call   6a4 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x394>
 6a4:	48 8b 7c 24 20       	mov    0x20(%rsp),%rdi
 6a9:	4c 39 ef             	cmp    %r13,%rdi
 6ac:	74 0e                	je     6bc <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x3ac>
 6ae:	48 8b 44 24 30       	mov    0x30(%rsp),%rax
 6b3:	48 8d 70 01          	lea    0x1(%rax),%rsi
 6b7:	e8 00 00 00 00       	call   6bc <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x3ac>
 6bc:	48 8b 84 24 88 00 00 	mov    0x88(%rsp),%rax
 6c3:	00 
 6c4:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
 6cb:	00 00 
 6cd:	0f 85 61 02 00 00    	jne    934 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x624>
 6d3:	48 81 c4 98 00 00 00 	add    $0x98,%rsp
 6da:	5b                   	pop    %rbx
 6db:	5d                   	pop    %rbp
 6dc:	41 5c                	pop    %r12
 6de:	41 5d                	pop    %r13
 6e0:	41 5e                	pop    %r14
 6e2:	41 5f                	pop    %r15
 6e4:	e9 17 f9 ff ff       	jmp    0 <_ZN10tag_invoke9view_base6detail10tag_invokeINS_13customization8VoidViewEEEvNS1_6Show_tERT_.isra.0>
 6e9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
 6f0:	0f b6 44 24 40       	movzbl 0x40(%rsp),%eax
 6f5:	88 44 24 30          	mov    %al,0x30(%rsp)
 6f9:	e9 da fc ff ff       	jmp    3d8 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0xc8>
 6fe:	66 90                	xchg   %ax,%ax
 700:	48 89 7c 24 08       	mov    %rdi,0x8(%rsp)
 705:	e8 00 00 00 00       	call   70a <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x3fa>
 70a:	48 8b 7c 24 08       	mov    0x8(%rsp),%rdi
 70f:	be 0a 00 00 00       	mov    $0xa,%esi
 714:	48 8b 07             	mov    (%rdi),%rax
 717:	48 8b 40 30          	mov    0x30(%rax),%rax
 71b:	48 3b 05 00 00 00 00 	cmp    0x0(%rip),%rax        # 722 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x412>
 722:	0f 84 bb fd ff ff    	je     4e3 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1d3>
 728:	ff d0                	call   *%rax
 72a:	0f be f0             	movsbl %al,%esi
 72d:	e9 b1 fd ff ff       	jmp    4e3 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x1d3>
 732:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
 738:	48 89 ef             	mov    %rbp,%rdi
 73b:	e8 00 00 00 00       	call   740 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x430>
 740:	48 8b 45 00          	mov    0x0(%rbp),%rax
 744:	be 0a 00 00 00       	mov    $0xa,%esi
 749:	48 8b 40 30          	mov    0x30(%rax),%rax
 74d:	48 3b 05 00 00 00 00 	cmp    0x0(%rip),%rax        # 754 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x444>
 754:	0f 84 3a ff ff ff    	je     694 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x384>
 75a:	48 89 ef             	mov    %rbp,%rdi
 75d:	ff d0                	call   *%rax
 75f:	0f be f0             	movsbl %al,%esi
 762:	e9 2d ff ff ff       	jmp    694 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x384>
 767:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
 76e:	00 00 
 770:	48 8d 78 01          	lea    0x1(%rax),%rdi
 774:	e8 00 00 00 00       	call   779 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x469>
 779:	48 89 5c 24 30       	mov    %rbx,0x30(%rsp)
 77e:	48 89 44 24 20       	mov    %rax,0x20(%rsp)
 783:	83 fb 08             	cmp    $0x8,%ebx
 786:	0f 83 84 00 00 00    	jae    810 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x500>
 78c:	f6 c3 04             	test   $0x4,%bl
 78f:	0f 85 3b 01 00 00    	jne    8d0 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x5c0>
 795:	85 db                	test   %ebx,%ebx
 797:	74 10                	je     7a9 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x499>
 799:	0f b6 54 24 40       	movzbl 0x40(%rsp),%edx
 79e:	88 10                	mov    %dl,(%rax)
 7a0:	f6 c3 02             	test   $0x2,%bl
 7a3:	0f 85 5d 01 00 00    	jne    906 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x5f6>
 7a9:	48 8b 44 24 20       	mov    0x20(%rsp),%rax
 7ae:	e9 28 fc ff ff       	jmp    3db <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0xcb>
 7b3:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
 7b8:	48 8d 78 01          	lea    0x1(%rax),%rdi
 7bc:	e8 00 00 00 00       	call   7c1 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4b1>
 7c1:	48 89 5c 24 30       	mov    %rbx,0x30(%rsp)
 7c6:	48 89 44 24 20       	mov    %rax,0x20(%rsp)
 7cb:	83 fb 08             	cmp    $0x8,%ebx
 7ce:	0f 83 8c 00 00 00    	jae    860 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x550>
 7d4:	f6 c3 04             	test   $0x4,%bl
 7d7:	0f 85 13 01 00 00    	jne    8f0 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x5e0>
 7dd:	85 db                	test   %ebx,%ebx
 7df:	74 10                	je     7f1 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4e1>
 7e1:	0f b6 54 24 40       	movzbl 0x40(%rsp),%edx
 7e6:	88 10                	mov    %dl,(%rax)
 7e8:	f6 c3 02             	test   $0x2,%bl
 7eb:	0f 85 27 01 00 00    	jne    918 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x608>
 7f1:	48 8b 44 24 20       	mov    0x20(%rsp),%rax
 7f6:	e9 91 fd ff ff       	jmp    58c <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x27c>
 7fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
 800:	0f b6 44 24 40       	movzbl 0x40(%rsp),%eax
 805:	88 44 24 30          	mov    %al,0x30(%rsp)
 809:	e9 7b fd ff ff       	jmp    589 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x279>
 80e:	66 90                	xchg   %ax,%ax
 810:	48 8b 54 24 40       	mov    0x40(%rsp),%rdx
 815:	48 8d 78 08          	lea    0x8(%rax),%rdi
 819:	4d 89 e0             	mov    %r12,%r8
 81c:	48 83 e7 f8          	and    $0xfffffffffffffff8,%rdi
 820:	48 89 10             	mov    %rdx,(%rax)
 823:	89 da                	mov    %ebx,%edx
 825:	49 8b 4c 14 f8       	mov    -0x8(%r12,%rdx,1),%rcx
 82a:	48 89 4c 10 f8       	mov    %rcx,-0x8(%rax,%rdx,1)
 82f:	48 29 f8             	sub    %rdi,%rax
 832:	49 29 c0             	sub    %rax,%r8
 835:	01 d8                	add    %ebx,%eax
 837:	83 e0 f8             	and    $0xfffffff8,%eax
 83a:	83 f8 08             	cmp    $0x8,%eax
 83d:	0f 82 66 ff ff ff    	jb     7a9 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x499>
 843:	83 e0 f8             	and    $0xfffffff8,%eax
 846:	31 d2                	xor    %edx,%edx
 848:	89 d1                	mov    %edx,%ecx
 84a:	83 c2 08             	add    $0x8,%edx
 84d:	49 8b 34 08          	mov    (%r8,%rcx,1),%rsi
 851:	48 89 34 0f          	mov    %rsi,(%rdi,%rcx,1)
 855:	39 c2                	cmp    %eax,%edx
 857:	72 ef                	jb     848 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x538>
 859:	e9 4b ff ff ff       	jmp    7a9 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x499>
 85e:	66 90                	xchg   %ax,%ax
 860:	48 8b 54 24 40       	mov    0x40(%rsp),%rdx
 865:	48 8d 78 08          	lea    0x8(%rax),%rdi
 869:	48 83 e7 f8          	and    $0xfffffffffffffff8,%rdi
 86d:	48 89 10             	mov    %rdx,(%rax)
 870:	89 da                	mov    %ebx,%edx
 872:	49 8b 4c 14 f8       	mov    -0x8(%r12,%rdx,1),%rcx
 877:	48 89 4c 10 f8       	mov    %rcx,-0x8(%rax,%rdx,1)
 87c:	48 29 f8             	sub    %rdi,%rax
 87f:	49 29 c4             	sub    %rax,%r12
 882:	01 d8                	add    %ebx,%eax
 884:	83 e0 f8             	and    $0xfffffff8,%eax
 887:	83 f8 08             	cmp    $0x8,%eax
 88a:	0f 82 61 ff ff ff    	jb     7f1 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4e1>
 890:	83 e0 f8             	and    $0xfffffff8,%eax
 893:	31 d2                	xor    %edx,%edx
 895:	89 d1                	mov    %edx,%ecx
 897:	83 c2 08             	add    $0x8,%edx
 89a:	49 8b 34 0c          	mov    (%r12,%rcx,1),%rsi
 89e:	48 89 34 0f          	mov    %rsi,(%rdi,%rcx,1)
 8a2:	39 c2                	cmp    %eax,%edx
 8a4:	72 ef                	jb     895 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x585>
 8a6:	e9 46 ff ff ff       	jmp    7f1 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4e1>
 8ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)
 8b0:	4c 89 e8             	mov    %r13,%rax
 8b3:	e9 cb fe ff ff       	jmp    783 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x473>
 8b8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
 8bf:	00 
 8c0:	4c 89 e8             	mov    %r13,%rax
 8c3:	e9 03 ff ff ff       	jmp    7cb <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4bb>
 8c8:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
 8cf:	00 
 8d0:	8b 54 24 40          	mov    0x40(%rsp),%edx
 8d4:	89 10                	mov    %edx,(%rax)
 8d6:	89 da                	mov    %ebx,%edx
 8d8:	41 8b 4c 14 fc       	mov    -0x4(%r12,%rdx,1),%ecx
 8dd:	89 4c 10 fc          	mov    %ecx,-0x4(%rax,%rdx,1)
 8e1:	e9 c3 fe ff ff       	jmp    7a9 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x499>
 8e6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
 8ed:	00 00 00 
 8f0:	8b 54 24 40          	mov    0x40(%rsp),%edx
 8f4:	89 10                	mov    %edx,(%rax)
 8f6:	89 da                	mov    %ebx,%edx
 8f8:	41 8b 4c 14 fc       	mov    -0x4(%r12,%rdx,1),%ecx
 8fd:	89 4c 10 fc          	mov    %ecx,-0x4(%rax,%rdx,1)
 901:	e9 eb fe ff ff       	jmp    7f1 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4e1>
 906:	89 da                	mov    %ebx,%edx
 908:	41 0f b7 4c 14 fe    	movzwl -0x2(%r12,%rdx,1),%ecx
 90e:	66 89 4c 10 fe       	mov    %cx,-0x2(%rax,%rdx,1)
 913:	e9 91 fe ff ff       	jmp    7a9 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x499>
 918:	89 da                	mov    %ebx,%edx
 91a:	41 0f b7 4c 14 fe    	movzwl -0x2(%r12,%rdx,1),%ecx
 920:	66 89 4c 10 fe       	mov    %cx,-0x2(%rax,%rdx,1)
 925:	e9 c7 fe ff ff       	jmp    7f1 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x4e1>
 92a:	e8 00 00 00 00       	call   92f <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x61f>
 92f:	e8 00 00 00 00       	call   934 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x624>
 934:	e8 00 00 00 00       	call   939 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x629>

Disassembly of section .text._ZNKSt5ctypeIcE8do_widenEc:

0000000000000000 <_ZNKSt5ctypeIcE8do_widenEc>:
   0:	f3 0f 1e fa          	endbr64 
   4:	89 f0                	mov    %esi,%eax
   6:	c3                   	ret    

Disassembly of section .text._ZN7testing4Test5SetupEv:

0000000000000000 <_ZN7testing4Test5SetupEv>:
   0:	f3 0f 1e fa          	endbr64 
   4:	31 c0                	xor    %eax,%eax
   6:	c3                   	ret    

Disassembly of section .text._ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEED2Ev:

0000000000000000 <_ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEED1Ev>:
   0:	f3 0f 1e fa          	endbr64 
   4:	c3                   	ret    

Disassembly of section .text._ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEED0Ev:

0000000000000000 <_ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEED0Ev>:
   0:	f3 0f 1e fa          	endbr64 
   4:	be 08 00 00 00       	mov    $0x8,%esi
   9:	e9 00 00 00 00       	jmp    e <.LC2>

Disassembly of section .text._ZN10tag_invoke17tag_invoke_1_TestD2Ev:

0000000000000000 <_ZN10tag_invoke17tag_invoke_1_TestD1Ev>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # b <_ZN10tag_invoke17tag_invoke_1_TestD1Ev+0xb>
   b:	48 83 c0 10          	add    $0x10,%rax
   f:	48 89 07             	mov    %rax,(%rdi)
  12:	e9 00 00 00 00       	jmp    17 <.LC21+0x7>

Disassembly of section .text._ZN10tag_invoke17tag_invoke_1_TestD0Ev:

0000000000000000 <_ZN10tag_invoke17tag_invoke_1_TestD0Ev>:
   0:	f3 0f 1e fa          	endbr64 
   4:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # b <_ZN10tag_invoke17tag_invoke_1_TestD0Ev+0xb>
   b:	53                   	push   %rbx
   c:	48 89 fb             	mov    %rdi,%rbx
   f:	48 83 c0 10          	add    $0x10,%rax
  13:	48 89 07             	mov    %rax,(%rdi)
  16:	e8 00 00 00 00       	call   1b <_ZN10tag_invoke17tag_invoke_1_TestD0Ev+0x1b>
  1b:	48 89 df             	mov    %rbx,%rdi
  1e:	be 10 00 00 00       	mov    $0x10,%esi
  23:	5b                   	pop    %rbx
  24:	e9 00 00 00 00       	jmp    29 <.LC5+0x1>

Disassembly of section .text._ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEE10CreateTestEv:

0000000000000000 <_ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEE10CreateTestEv>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	bf 10 00 00 00       	mov    $0x10,%edi
   a:	53                   	push   %rbx
   b:	48 83 ec 08          	sub    $0x8,%rsp
   f:	e8 00 00 00 00       	call   14 <_ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEE10CreateTestEv+0x14>
  14:	48 89 c7             	mov    %rax,%rdi
  17:	48 89 c3             	mov    %rax,%rbx
  1a:	e8 00 00 00 00       	call   1f <_ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEE10CreateTestEv+0x1f>
  1f:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 26 <_ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEE10CreateTestEv+0x26>
  26:	48 83 c0 10          	add    $0x10,%rax
  2a:	48 89 03             	mov    %rax,(%rbx)
  2d:	48 83 c4 08          	add    $0x8,%rsp
  31:	48 89 d8             	mov    %rbx,%rax
  34:	5b                   	pop    %rbx
  35:	5d                   	pop    %rbp
  36:	c3                   	ret    
  37:	f3 0f 1e fa          	endbr64 
  3b:	48 89 c5             	mov    %rax,%rbp
  3e:	48 89 df             	mov    %rbx,%rdi
  41:	be 10 00 00 00       	mov    $0x10,%esi
  46:	e8 00 00 00 00       	call   4b <_ZN7testing8internal15TestFactoryImplIN10tag_invoke17tag_invoke_1_TestEE10CreateTestEv+0x4b>
  4b:	48 89 ef             	mov    %rbp,%rdi
  4e:	e8 00 00 00 00       	call   53 <.LC19+0x2>

Disassembly of section .text.unlikely:

0000000000000000 <_GLOBAL__sub_I_tag_invoke.cpp.cold>:
   0:	48 8b 7d a0          	mov    -0x60(%rbp),%rdi
   4:	4c 39 f7             	cmp    %r14,%rdi
   7:	74 0d                	je     16 <_GLOBAL__sub_I_tag_invoke.cpp.cold+0x16>
   9:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
   d:	48 8d 70 01          	lea    0x1(%rax),%rsi
  11:	e8 00 00 00 00       	call   16 <_GLOBAL__sub_I_tag_invoke.cpp.cold+0x16>
  16:	48 8b 7d 80          	mov    -0x80(%rbp),%rdi
  1a:	4c 39 ef             	cmp    %r13,%rdi
  1d:	74 0d                	je     2c <_GLOBAL__sub_I_tag_invoke.cpp.cold+0x2c>
  1f:	48 8b 45 90          	mov    -0x70(%rbp),%rax
  23:	48 8d 70 01          	lea    0x1(%rax),%rsi
  27:	e8 00 00 00 00       	call   2c <_GLOBAL__sub_I_tag_invoke.cpp.cold+0x2c>
  2c:	48 89 df             	mov    %rbx,%rdi
  2f:	e8 00 00 00 00       	call   34 <_GLOBAL__sub_I_tag_invoke.cpp.cold+0x34>
  34:	4c 89 e7             	mov    %r12,%rdi
  37:	e8 00 00 00 00       	call   3c <_GLOBAL__sub_I_tag_invoke.cpp.cold+0x3c>
  3c:	48 89 df             	mov    %rbx,%rdi
  3f:	e8 00 00 00 00       	call   44 <_GLOBAL__sub_I_tag_invoke.cpp.cold+0x44>
  44:	4c 89 e7             	mov    %r12,%rdi
  47:	e8 00 00 00 00       	call   4c <_GLOBAL__sub_I_tag_invoke.cpp.cold+0x4c>
  4c:	48 89 df             	mov    %rbx,%rdi
  4f:	e8 00 00 00 00       	call   54 <.LC19+0x3>

Disassembly of section .text.startup:

0000000000000000 <_GLOBAL__sub_I_tag_invoke.cpp>:
   0:	f3 0f 1e fa          	endbr64 
   4:	55                   	push   %rbp
   5:	48 89 e5             	mov    %rsp,%rbp
   8:	41 57                	push   %r15
   a:	41 56                	push   %r14
   c:	41 55                	push   %r13
   e:	41 54                	push   %r12
  10:	53                   	push   %rbx
  11:	48 8d 1d 00 00 00 00 	lea    0x0(%rip),%rbx        # 18 <_GLOBAL__sub_I_tag_invoke.cpp+0x18>
  18:	48 89 df             	mov    %rbx,%rdi
  1b:	48 83 ec 68          	sub    $0x68,%rsp
  1f:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  26:	00 00 
  28:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
  2c:	31 c0                	xor    %eax,%eax
  2e:	e8 00 00 00 00       	call   33 <_GLOBAL__sub_I_tag_invoke.cpp+0x33>
  33:	48 8b 3d 00 00 00 00 	mov    0x0(%rip),%rdi        # 3a <_GLOBAL__sub_I_tag_invoke.cpp+0x3a>
  3a:	48 8d 15 00 00 00 00 	lea    0x0(%rip),%rdx        # 41 <_GLOBAL__sub_I_tag_invoke.cpp+0x41>
  41:	48 89 de             	mov    %rbx,%rsi
  44:	e8 00 00 00 00       	call   49 <_GLOBAL__sub_I_tag_invoke.cpp+0x49>
  49:	bf 08 00 00 00       	mov    $0x8,%edi
  4e:	e8 00 00 00 00       	call   53 <_GLOBAL__sub_I_tag_invoke.cpp+0x53>
  53:	bf 01 00 00 00       	mov    $0x1,%edi
  58:	48 89 c1             	mov    %rax,%rcx
  5b:	49 89 c7             	mov    %rax,%r15
  5e:	48 8b 05 00 00 00 00 	mov    0x0(%rip),%rax        # 65 <_GLOBAL__sub_I_tag_invoke.cpp+0x65>
  65:	48 83 c0 10          	add    $0x10,%rax
  69:	48 89 01             	mov    %rax,(%rcx)
  6c:	e8 00 00 00 00       	call   71 <_GLOBAL__sub_I_tag_invoke.cpp+0x71>
  71:	84 c0                	test   %al,%al
  73:	0f 84 f4 01 00 00    	je     26d <_GLOBAL__sub_I_tag_invoke.cpp+0x26d>
  79:	bf 01 00 00 00       	mov    $0x1,%edi
  7e:	e8 00 00 00 00       	call   83 <_GLOBAL__sub_I_tag_invoke.cpp+0x83>
  83:	84 c0                	test   %al,%al
  85:	0f 84 51 01 00 00    	je     1dc <_GLOBAL__sub_I_tag_invoke.cpp+0x1dc>
  8b:	e8 00 00 00 00       	call   90 <_GLOBAL__sub_I_tag_invoke.cpp+0x90>
  90:	4c 8d 6d 90          	lea    -0x70(%rbp),%r13
  94:	bf 47 00 00 00       	mov    $0x47,%edi
  99:	4c 8d 75 b0          	lea    -0x50(%rbp),%r14
  9d:	4c 89 6d 80          	mov    %r13,-0x80(%rbp)
  a1:	49 89 c4             	mov    %rax,%r12
  a4:	e8 00 00 00 00       	call   a9 <_GLOBAL__sub_I_tag_invoke.cpp+0xa9>
  a9:	4c 89 75 a0          	mov    %r14,-0x60(%rbp)
  ad:	66 0f 6f 05 00 00 00 	movdqa 0x0(%rip),%xmm0        # b5 <_GLOBAL__sub_I_tag_invoke.cpp+0xb5>
  b4:	00 
  b5:	bf 47 00 00 00       	mov    $0x47,%edi
  ba:	48 89 c3             	mov    %rax,%rbx
  bd:	48 89 45 80          	mov    %rax,-0x80(%rbp)
  c1:	0f 11 00             	movups %xmm0,(%rax)
  c4:	66 0f 6f 05 00 00 00 	movdqa 0x0(%rip),%xmm0        # cc <_GLOBAL__sub_I_tag_invoke.cpp+0xcc>
  cb:	00 
  cc:	48 c7 45 90 46 00 00 	movq   $0x46,-0x70(%rbp)
  d3:	00 
  d4:	0f 11 40 10          	movups %xmm0,0x10(%rax)
  d8:	66 0f 6f 05 00 00 00 	movdqa 0x0(%rip),%xmm0        # e0 <_GLOBAL__sub_I_tag_invoke.cpp+0xe0>
  df:	00 
  e0:	48 c7 45 88 46 00 00 	movq   $0x46,-0x78(%rbp)
  e7:	00 
  e8:	0f 11 40 20          	movups %xmm0,0x20(%rax)
  ec:	66 0f 6f 05 00 00 00 	movdqa 0x0(%rip),%xmm0        # f4 <_GLOBAL__sub_I_tag_invoke.cpp+0xf4>
  f3:	00 
  f4:	0f 11 40 30          	movups %xmm0,0x30(%rax)
  f8:	48 b8 76 6f 6b 65 2e 	movabs $0x7070632e656b6f76,%rax
  ff:	63 70 70 
 102:	48 89 43 3e          	mov    %rax,0x3e(%rbx)
 106:	c6 43 46 00          	movb   $0x0,0x46(%rbx)
 10a:	e8 00 00 00 00       	call   10f <_GLOBAL__sub_I_tag_invoke.cpp+0x10f>
 10f:	48 8b 53 3e          	mov    0x3e(%rbx),%rdx
 113:	f3 0f 6f 0b          	movdqu (%rbx),%xmm1
 117:	48 83 ec 08          	sub    $0x8,%rsp
 11b:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
 11f:	f3 0f 6f 53 10       	movdqu 0x10(%rbx),%xmm2
 124:	f3 0f 6f 5b 20       	movdqu 0x20(%rbx),%xmm3
 129:	c6 40 46 00          	movb   $0x0,0x46(%rax)
 12d:	31 c9                	xor    %ecx,%ecx
 12f:	f3 0f 6f 63 30       	movdqu 0x30(%rbx),%xmm4
 134:	0f 11 08             	movups %xmm1,(%rax)
 137:	4d 89 e1             	mov    %r12,%r9
 13a:	4c 8d 45 a0          	lea    -0x60(%rbp),%r8
 13e:	48 c7 45 b0 46 00 00 	movq   $0x46,-0x50(%rbp)
 145:	00 
 146:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 14d <_GLOBAL__sub_I_tag_invoke.cpp+0x14d>
 14d:	48 8d 3d 00 00 00 00 	lea    0x0(%rip),%rdi        # 154 <_GLOBAL__sub_I_tag_invoke.cpp+0x154>
 154:	0f 11 60 30          	movups %xmm4,0x30(%rax)
 158:	48 c7 45 a8 46 00 00 	movq   $0x46,-0x58(%rbp)
 15f:	00 
 160:	48 89 50 3e          	mov    %rdx,0x3e(%rax)
 164:	31 d2                	xor    %edx,%edx
 166:	c7 45 c0 68 00 00 00 	movl   $0x68,-0x40(%rbp)
 16d:	0f 11 50 10          	movups %xmm2,0x10(%rax)
 171:	0f 11 58 20          	movups %xmm3,0x20(%rax)
 175:	41 57                	push   %r15
 177:	6a 00                	push   $0x0
 179:	6a 00                	push   $0x0
 17b:	e8 00 00 00 00       	call   180 <_GLOBAL__sub_I_tag_invoke.cpp+0x180>
 180:	48 8b 15 00 00 00 00 	mov    0x0(%rip),%rdx        # 187 <_GLOBAL__sub_I_tag_invoke.cpp+0x187>
 187:	48 8b 7d a0          	mov    -0x60(%rbp),%rdi
 18b:	48 83 c4 20          	add    $0x20,%rsp
 18f:	48 89 02             	mov    %rax,(%rdx)
 192:	4c 39 f7             	cmp    %r14,%rdi
 195:	74 0d                	je     1a4 <_GLOBAL__sub_I_tag_invoke.cpp+0x1a4>
 197:	48 8b 45 b0          	mov    -0x50(%rbp),%rax
 19b:	48 8d 70 01          	lea    0x1(%rax),%rsi
 19f:	e8 00 00 00 00       	call   1a4 <_GLOBAL__sub_I_tag_invoke.cpp+0x1a4>
 1a4:	48 8b 7d 80          	mov    -0x80(%rbp),%rdi
 1a8:	4c 39 ef             	cmp    %r13,%rdi
 1ab:	74 0d                	je     1ba <_GLOBAL__sub_I_tag_invoke.cpp+0x1ba>
 1ad:	48 8b 45 90          	mov    -0x70(%rbp),%rax
 1b1:	48 8d 70 01          	lea    0x1(%rax),%rsi
 1b5:	e8 00 00 00 00       	call   1ba <_GLOBAL__sub_I_tag_invoke.cpp+0x1ba>
 1ba:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
 1be:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
 1c5:	00 00 
 1c7:	0f 85 31 01 00 00    	jne    2fe <_GLOBAL__sub_I_tag_invoke.cpp+0x2fe>
 1cd:	48 8d 65 d8          	lea    -0x28(%rbp),%rsp
 1d1:	5b                   	pop    %rbx
 1d2:	41 5c                	pop    %r12
 1d4:	41 5d                	pop    %r13
 1d6:	41 5e                	pop    %r14
 1d8:	41 5f                	pop    %r15
 1da:	5d                   	pop    %rbp
 1db:	c3                   	ret    
 1dc:	4c 8d a5 7c ff ff ff 	lea    -0x84(%rbp),%r12
 1e3:	be 03 00 00 00       	mov    $0x3,%esi
 1e8:	b9 11 02 00 00       	mov    $0x211,%ecx
 1ed:	48 8d 15 00 00 00 00 	lea    0x0(%rip),%rdx        # 1f4 <_GLOBAL__sub_I_tag_invoke.cpp+0x1f4>
 1f4:	4c 89 e7             	mov    %r12,%rdi
 1f7:	e8 00 00 00 00       	call   1fc <_GLOBAL__sub_I_tag_invoke.cpp+0x1fc>
 1fc:	48 8b 1d 00 00 00 00 	mov    0x0(%rip),%rbx        # 203 <_GLOBAL__sub_I_tag_invoke.cpp+0x203>
 203:	ba 32 00 00 00       	mov    $0x32,%edx
 208:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 20f <_GLOBAL__sub_I_tag_invoke.cpp+0x20f>
 20f:	48 89 df             	mov    %rbx,%rdi
 212:	e8 00 00 00 00       	call   217 <_GLOBAL__sub_I_tag_invoke.cpp+0x217>
 217:	ba 6a 00 00 00       	mov    $0x6a,%edx
 21c:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 223 <_GLOBAL__sub_I_tag_invoke.cpp+0x223>
 223:	48 89 df             	mov    %rbx,%rdi
 226:	e8 00 00 00 00       	call   22b <_GLOBAL__sub_I_tag_invoke.cpp+0x22b>
 22b:	ba 46 00 00 00       	mov    $0x46,%edx
 230:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 237 <_GLOBAL__sub_I_tag_invoke.cpp+0x237>
 237:	48 89 df             	mov    %rbx,%rdi
 23a:	e8 00 00 00 00       	call   23f <_GLOBAL__sub_I_tag_invoke.cpp+0x23f>
 23f:	ba 01 00 00 00       	mov    $0x1,%edx
 244:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 24b <_GLOBAL__sub_I_tag_invoke.cpp+0x24b>
 24b:	48 89 df             	mov    %rbx,%rdi
 24e:	e8 00 00 00 00       	call   253 <_GLOBAL__sub_I_tag_invoke.cpp+0x253>
 253:	be 68 00 00 00       	mov    $0x68,%esi
 258:	48 89 df             	mov    %rbx,%rdi
 25b:	e8 00 00 00 00       	call   260 <_GLOBAL__sub_I_tag_invoke.cpp+0x260>
 260:	4c 89 e7             	mov    %r12,%rdi
 263:	e8 00 00 00 00       	call   268 <_GLOBAL__sub_I_tag_invoke.cpp+0x268>
 268:	e9 1e fe ff ff       	jmp    8b <_GLOBAL__sub_I_tag_invoke.cpp+0x8b>
 26d:	4c 8d a5 7c ff ff ff 	lea    -0x84(%rbp),%r12
 274:	be 03 00 00 00       	mov    $0x3,%esi
 279:	b9 26 02 00 00       	mov    $0x226,%ecx
 27e:	48 8d 15 00 00 00 00 	lea    0x0(%rip),%rdx        # 285 <_GLOBAL__sub_I_tag_invoke.cpp+0x285>
 285:	4c 89 e7             	mov    %r12,%rdi
 288:	e8 00 00 00 00       	call   28d <_GLOBAL__sub_I_tag_invoke.cpp+0x28d>
 28d:	48 8b 1d 00 00 00 00 	mov    0x0(%rip),%rbx        # 294 <_GLOBAL__sub_I_tag_invoke.cpp+0x294>
 294:	ba 32 00 00 00       	mov    $0x32,%edx
 299:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 2a0 <_GLOBAL__sub_I_tag_invoke.cpp+0x2a0>
 2a0:	48 89 df             	mov    %rbx,%rdi
 2a3:	e8 00 00 00 00       	call   2a8 <_GLOBAL__sub_I_tag_invoke.cpp+0x2a8>
 2a8:	ba 6f 00 00 00       	mov    $0x6f,%edx
 2ad:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 2b4 <_GLOBAL__sub_I_tag_invoke.cpp+0x2b4>
 2b4:	48 89 df             	mov    %rbx,%rdi
 2b7:	e8 00 00 00 00       	call   2bc <_GLOBAL__sub_I_tag_invoke.cpp+0x2bc>
 2bc:	ba 46 00 00 00       	mov    $0x46,%edx
 2c1:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 2c8 <_GLOBAL__sub_I_tag_invoke.cpp+0x2c8>
 2c8:	48 89 df             	mov    %rbx,%rdi
 2cb:	e8 00 00 00 00       	call   2d0 <_GLOBAL__sub_I_tag_invoke.cpp+0x2d0>
 2d0:	ba 01 00 00 00       	mov    $0x1,%edx
 2d5:	48 8d 35 00 00 00 00 	lea    0x0(%rip),%rsi        # 2dc <_GLOBAL__sub_I_tag_invoke.cpp+0x2dc>
 2dc:	48 89 df             	mov    %rbx,%rdi
 2df:	e8 00 00 00 00       	call   2e4 <_GLOBAL__sub_I_tag_invoke.cpp+0x2e4>
 2e4:	be 68 00 00 00       	mov    $0x68,%esi
 2e9:	48 89 df             	mov    %rbx,%rdi
 2ec:	e8 00 00 00 00       	call   2f1 <_GLOBAL__sub_I_tag_invoke.cpp+0x2f1>
 2f1:	4c 89 e7             	mov    %r12,%rdi
 2f4:	e8 00 00 00 00       	call   2f9 <_GLOBAL__sub_I_tag_invoke.cpp+0x2f9>
 2f9:	e9 7b fd ff ff       	jmp    79 <_GLOBAL__sub_I_tag_invoke.cpp+0x79>
 2fe:	e8 00 00 00 00       	call   303 <_GLOBAL__sub_I_tag_invoke.cpp+0x303>
 303:	f3 0f 1e fa          	endbr64 
 307:	48 89 c3             	mov    %rax,%rbx
 30a:	e9 00 00 00 00       	jmp    30f <_GLOBAL__sub_I_tag_invoke.cpp+0x30f>
 30f:	f3 0f 1e fa          	endbr64 
 313:	48 89 c3             	mov    %rax,%rbx
 316:	e9 00 00 00 00       	jmp    31b <_GLOBAL__sub_I_tag_invoke.cpp+0x31b>
 31b:	f3 0f 1e fa          	endbr64 
 31f:	48 89 c3             	mov    %rax,%rbx
 322:	e9 00 00 00 00       	jmp    327 <_GLOBAL__sub_I_tag_invoke.cpp+0x327>
 327:	f3 0f 1e fa          	endbr64 
 32b:	48 89 c3             	mov    %rax,%rbx
 32e:	e9 00 00 00 00       	jmp    333 <_ZN10tag_invoke17tag_invoke_1_Test8TestBodyEv+0x23>
