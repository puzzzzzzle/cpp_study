
a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000401000 <_init>:
  401000:	f3 0f 1e fa          	endbr64
  401004:	48 83 ec 08          	sub    $0x8,%rsp
  401008:	48 8b 05 c9 2f 00 00 	mov    0x2fc9(%rip),%rax        # 403fd8 <__gmon_start__@Base>
  40100f:	48 85 c0             	test   %rax,%rax
  401012:	74 02                	je     401016 <_init+0x16>
  401014:	ff d0                	call   *%rax
  401016:	48 83 c4 08          	add    $0x8,%rsp
  40101a:	c3                   	ret

Disassembly of section .plt:

0000000000401020 <printf@plt-0x10>:
  401020:	ff 35 ca 2f 00 00    	push   0x2fca(%rip)        # 403ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
  401026:	ff 25 cc 2f 00 00    	jmp    *0x2fcc(%rip)        # 403ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
  40102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000401030 <printf@plt>:
  401030:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 404000 <printf@GLIBC_2.2.5>
  401036:	68 00 00 00 00       	push   $0x0
  40103b:	e9 e0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401040 <__cxa_begin_catch@plt>:
  401040:	ff 25 c2 2f 00 00    	jmp    *0x2fc2(%rip)        # 404008 <__cxa_begin_catch@CXXABI_1.3>
  401046:	68 01 00 00 00       	push   $0x1
  40104b:	e9 d0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401050 <__cxa_allocate_exception@plt>:
  401050:	ff 25 ba 2f 00 00    	jmp    *0x2fba(%rip)        # 404010 <__cxa_allocate_exception@CXXABI_1.3>
  401056:	68 02 00 00 00       	push   $0x2
  40105b:	e9 c0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401060 <__stack_chk_fail@plt>:
  401060:	ff 25 b2 2f 00 00    	jmp    *0x2fb2(%rip)        # 404018 <__stack_chk_fail@GLIBC_2.4>
  401066:	68 03 00 00 00       	push   $0x3
  40106b:	e9 b0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401070 <puts@plt>:
  401070:	ff 25 aa 2f 00 00    	jmp    *0x2faa(%rip)        # 404020 <puts@GLIBC_2.2.5>
  401076:	68 04 00 00 00       	push   $0x4
  40107b:	e9 a0 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401080 <__cxa_end_catch@plt>:
  401080:	ff 25 a2 2f 00 00    	jmp    *0x2fa2(%rip)        # 404028 <__cxa_end_catch@CXXABI_1.3>
  401086:	68 05 00 00 00       	push   $0x5
  40108b:	e9 90 ff ff ff       	jmp    401020 <_init+0x20>

0000000000401090 <__gxx_personality_v0@plt>:
  401090:	ff 25 9a 2f 00 00    	jmp    *0x2f9a(%rip)        # 404030 <__gxx_personality_v0@CXXABI_1.3>
  401096:	68 06 00 00 00       	push   $0x6
  40109b:	e9 80 ff ff ff       	jmp    401020 <_init+0x20>

00000000004010a0 <__cxa_throw@plt>:
  4010a0:	ff 25 92 2f 00 00    	jmp    *0x2f92(%rip)        # 404038 <__cxa_throw@CXXABI_1.3>
  4010a6:	68 07 00 00 00       	push   $0x7
  4010ab:	e9 70 ff ff ff       	jmp    401020 <_init+0x20>

00000000004010b0 <_Unwind_Resume@plt>:
  4010b0:	ff 25 8a 2f 00 00    	jmp    *0x2f8a(%rip)        # 404040 <_Unwind_Resume@GCC_3.0>
  4010b6:	68 08 00 00 00       	push   $0x8
  4010bb:	e9 60 ff ff ff       	jmp    401020 <_init+0x20>

Disassembly of section .text:

00000000004010c0 <_start>:
  4010c0:	f3 0f 1e fa          	endbr64
  4010c4:	31 ed                	xor    %ebp,%ebp
  4010c6:	49 89 d1             	mov    %rdx,%r9
  4010c9:	5e                   	pop    %rsi
  4010ca:	48 89 e2             	mov    %rsp,%rdx
  4010cd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
  4010d1:	50                   	push   %rax
  4010d2:	54                   	push   %rsp
  4010d3:	45 31 c0             	xor    %r8d,%r8d
  4010d6:	31 c9                	xor    %ecx,%ecx
  4010d8:	48 c7 c7 cc 12 40 00 	mov    $0x4012cc,%rdi
  4010df:	ff 15 e3 2e 00 00    	call   *0x2ee3(%rip)        # 403fc8 <__libc_start_main@GLIBC_2.34>
  4010e5:	f4                   	hlt
  4010e6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  4010ed:	00 00 00 

00000000004010f0 <_dl_relocate_static_pie>:
  4010f0:	f3 0f 1e fa          	endbr64
  4010f4:	c3                   	ret
  4010f5:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
  4010fc:	00 00 00 
  4010ff:	90                   	nop
  401100:	b8 58 40 40 00       	mov    $0x404058,%eax
  401105:	48 3d 58 40 40 00    	cmp    $0x404058,%rax
  40110b:	74 13                	je     401120 <_dl_relocate_static_pie+0x30>
  40110d:	48 8b 05 bc 2e 00 00 	mov    0x2ebc(%rip),%rax        # 403fd0 <_ITM_deregisterTMCloneTable@Base>
  401114:	48 85 c0             	test   %rax,%rax
  401117:	74 07                	je     401120 <_dl_relocate_static_pie+0x30>
  401119:	bf 58 40 40 00       	mov    $0x404058,%edi
  40111e:	ff e0                	jmp    *%rax
  401120:	c3                   	ret
  401121:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401128:	00 00 00 00 
  40112c:	0f 1f 40 00          	nopl   0x0(%rax)
  401130:	be 58 40 40 00       	mov    $0x404058,%esi
  401135:	48 81 ee 58 40 40 00 	sub    $0x404058,%rsi
  40113c:	48 89 f0             	mov    %rsi,%rax
  40113f:	48 c1 ee 3f          	shr    $0x3f,%rsi
  401143:	48 c1 f8 03          	sar    $0x3,%rax
  401147:	48 01 c6             	add    %rax,%rsi
  40114a:	48 d1 fe             	sar    $1,%rsi
  40114d:	74 19                	je     401168 <_dl_relocate_static_pie+0x78>
  40114f:	48 8b 05 8a 2e 00 00 	mov    0x2e8a(%rip),%rax        # 403fe0 <_ITM_registerTMCloneTable@Base>
  401156:	48 85 c0             	test   %rax,%rax
  401159:	74 0d                	je     401168 <_dl_relocate_static_pie+0x78>
  40115b:	bf 58 40 40 00       	mov    $0x404058,%edi
  401160:	ff e0                	jmp    *%rax
  401162:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
  401168:	c3                   	ret
  401169:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
  401170:	f3 0f 1e fa          	endbr64
  401174:	80 3d dd 2e 00 00 00 	cmpb   $0x0,0x2edd(%rip)        # 404058 <__TMC_END__>
  40117b:	75 13                	jne    401190 <_dl_relocate_static_pie+0xa0>
  40117d:	55                   	push   %rbp
  40117e:	48 89 e5             	mov    %rsp,%rbp
  401181:	e8 7a ff ff ff       	call   401100 <_dl_relocate_static_pie+0x10>
  401186:	c6 05 cb 2e 00 00 01 	movb   $0x1,0x2ecb(%rip)        # 404058 <__TMC_END__>
  40118d:	5d                   	pop    %rbp
  40118e:	c3                   	ret
  40118f:	90                   	nop
  401190:	c3                   	ret
  401191:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
  401198:	00 00 00 00 
  40119c:	0f 1f 40 00          	nopl   0x0(%rax)
  4011a0:	f3 0f 1e fa          	endbr64
  4011a4:	eb 8a                	jmp    401130 <_dl_relocate_static_pie+0x40>

00000000004011a6 <_Z8functionv>:
  4011a6:	55                   	push   %rbp
  4011a7:	48 89 e5             	mov    %rsp,%rbp
  4011aa:	53                   	push   %rbx
  4011ab:	48 83 ec 28          	sub    $0x28,%rsp
  4011af:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
  4011b6:	00 00 
  4011b8:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  4011bc:	31 c0                	xor    %eax,%eax
  4011be:	48 8d 45 d4          	lea    -0x2c(%rbp),%rax
  4011c2:	be 01 00 00 00       	mov    $0x1,%esi
  4011c7:	48 89 c7             	mov    %rax,%rdi
  4011ca:	e8 57 01 00 00       	call   401326 <_ZN7MyClassC1Ei>
  4011cf:	48 8d 45 d8          	lea    -0x28(%rbp),%rax
  4011d3:	be 02 00 00 00       	mov    $0x2,%esi
  4011d8:	48 89 c7             	mov    %rax,%rdi
  4011db:	e8 46 01 00 00       	call   401326 <_ZN7MyClassC1Ei>
  4011e0:	48 8d 45 dc          	lea    -0x24(%rbp),%rax
  4011e4:	be 03 00 00 00       	mov    $0x3,%esi
  4011e9:	48 89 c7             	mov    %rax,%rdi
  4011ec:	e8 35 01 00 00       	call   401326 <_ZN7MyClassC1Ei>
  4011f1:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
  4011f5:	be 04 00 00 00       	mov    $0x4,%esi
  4011fa:	48 89 c7             	mov    %rax,%rdi
  4011fd:	e8 24 01 00 00       	call   401326 <_ZN7MyClassC1Ei>
  401202:	48 8d 45 e4          	lea    -0x1c(%rbp),%rax
  401206:	be 05 00 00 00       	mov    $0x5,%esi
  40120b:	48 89 c7             	mov    %rax,%rdi
  40120e:	e8 13 01 00 00       	call   401326 <_ZN7MyClassC1Ei>
  401213:	48 8d 45 e4          	lea    -0x1c(%rbp),%rax
  401217:	48 89 c7             	mov    %rax,%rdi
  40121a:	e8 61 01 00 00       	call   401380 <_ZN7MyClassD1Ev>
  40121f:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
  401223:	48 89 c7             	mov    %rax,%rdi
  401226:	e8 55 01 00 00       	call   401380 <_ZN7MyClassD1Ev>
  40122b:	48 8d 45 dc          	lea    -0x24(%rbp),%rax
  40122f:	48 89 c7             	mov    %rax,%rdi
  401232:	e8 49 01 00 00       	call   401380 <_ZN7MyClassD1Ev>
  401237:	48 8d 45 d8          	lea    -0x28(%rbp),%rax
  40123b:	48 89 c7             	mov    %rax,%rdi
  40123e:	e8 3d 01 00 00       	call   401380 <_ZN7MyClassD1Ev>
  401243:	48 8d 45 d4          	lea    -0x2c(%rbp),%rax
  401247:	48 89 c7             	mov    %rax,%rdi
  40124a:	e8 31 01 00 00       	call   401380 <_ZN7MyClassD1Ev>
  40124f:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
  401253:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
  40125a:	00 00 
  40125c:	74 68                	je     4012c6 <_Z8functionv+0x120>
  40125e:	eb 61                	jmp    4012c1 <_Z8functionv+0x11b>
  401260:	48 89 c3             	mov    %rax,%rbx
  401263:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
  401267:	48 89 c7             	mov    %rax,%rdi
  40126a:	e8 11 01 00 00       	call   401380 <_ZN7MyClassD1Ev>
  40126f:	eb 03                	jmp    401274 <_Z8functionv+0xce>
  401271:	48 89 c3             	mov    %rax,%rbx
  401274:	48 8d 45 dc          	lea    -0x24(%rbp),%rax
  401278:	48 89 c7             	mov    %rax,%rdi
  40127b:	e8 00 01 00 00       	call   401380 <_ZN7MyClassD1Ev>
  401280:	eb 03                	jmp    401285 <_Z8functionv+0xdf>
  401282:	48 89 c3             	mov    %rax,%rbx
  401285:	48 8d 45 d8          	lea    -0x28(%rbp),%rax
  401289:	48 89 c7             	mov    %rax,%rdi
  40128c:	e8 ef 00 00 00       	call   401380 <_ZN7MyClassD1Ev>
  401291:	eb 03                	jmp    401296 <_Z8functionv+0xf0>
  401293:	48 89 c3             	mov    %rax,%rbx
  401296:	48 8d 45 d4          	lea    -0x2c(%rbp),%rax
  40129a:	48 89 c7             	mov    %rax,%rdi
  40129d:	e8 de 00 00 00       	call   401380 <_ZN7MyClassD1Ev>
  4012a2:	48 89 d8             	mov    %rbx,%rax
  4012a5:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
  4012a9:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
  4012b0:	00 00 
  4012b2:	74 05                	je     4012b9 <_Z8functionv+0x113>
  4012b4:	e8 a7 fd ff ff       	call   401060 <__stack_chk_fail@plt>
  4012b9:	48 89 c7             	mov    %rax,%rdi
  4012bc:	e8 ef fd ff ff       	call   4010b0 <_Unwind_Resume@plt>
  4012c1:	e8 9a fd ff ff       	call   401060 <__stack_chk_fail@plt>
  4012c6:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
  4012ca:	c9                   	leave
  4012cb:	c3                   	ret

00000000004012cc <main>:
  4012cc:	55                   	push   %rbp
  4012cd:	48 89 e5             	mov    %rsp,%rbp
  4012d0:	53                   	push   %rbx
  4012d1:	48 83 ec 18          	sub    $0x18,%rsp
  4012d5:	e8 cc fe ff ff       	call   4011a6 <_Z8functionv>
  4012da:	b8 00 00 00 00       	mov    $0x0,%eax
  4012df:	eb 3e                	jmp    40131f <main+0x53>
  4012e1:	48 83 fa 01          	cmp    $0x1,%rdx
  4012e5:	74 08                	je     4012ef <main+0x23>
  4012e7:	48 89 c7             	mov    %rax,%rdi
  4012ea:	e8 c1 fd ff ff       	call   4010b0 <_Unwind_Resume@plt>
  4012ef:	48 89 c7             	mov    %rax,%rdi
  4012f2:	e8 49 fd ff ff       	call   401040 <__cxa_begin_catch@plt>
  4012f7:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
  4012fb:	bf 33 20 40 00       	mov    $0x402033,%edi
  401300:	e8 6b fd ff ff       	call   401070 <puts@plt>
  401305:	e8 76 fd ff ff       	call   401080 <__cxa_end_catch@plt>
  40130a:	eb ce                	jmp    4012da <main+0xe>
  40130c:	48 89 c3             	mov    %rax,%rbx
  40130f:	e8 6c fd ff ff       	call   401080 <__cxa_end_catch@plt>
  401314:	48 89 d8             	mov    %rbx,%rax
  401317:	48 89 c7             	mov    %rax,%rdi
  40131a:	e8 91 fd ff ff       	call   4010b0 <_Unwind_Resume@plt>
  40131f:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
  401323:	c9                   	leave
  401324:	c3                   	ret
  401325:	90                   	nop

0000000000401326 <_ZN7MyClassC1Ei>:
  401326:	55                   	push   %rbp
  401327:	48 89 e5             	mov    %rsp,%rbp
  40132a:	48 83 ec 10          	sub    $0x10,%rsp
  40132e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  401332:	89 75 f4             	mov    %esi,-0xc(%rbp)
  401335:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401339:	8b 55 f4             	mov    -0xc(%rbp),%edx
  40133c:	89 10                	mov    %edx,(%rax)
  40133e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401342:	8b 00                	mov    (%rax),%eax
  401344:	89 c6                	mov    %eax,%esi
  401346:	bf 04 20 40 00       	mov    $0x402004,%edi
  40134b:	b8 00 00 00 00       	mov    $0x0,%eax
  401350:	e8 db fc ff ff       	call   401030 <printf@plt>
  401355:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401359:	8b 00                	mov    (%rax),%eax
  40135b:	83 f8 04             	cmp    $0x4,%eax
  40135e:	75 1c                	jne    40137c <_ZN7MyClassC1Ei+0x56>
  401360:	bf 01 00 00 00       	mov    $0x1,%edi
  401365:	e8 e6 fc ff ff       	call   401050 <__cxa_allocate_exception@plt>
  40136a:	ba 00 00 00 00       	mov    $0x0,%edx
  40136f:	be 48 20 40 00       	mov    $0x402048,%esi
  401374:	48 89 c7             	mov    %rax,%rdi
  401377:	e8 24 fd ff ff       	call   4010a0 <__cxa_throw@plt>
  40137c:	90                   	nop
  40137d:	c9                   	leave
  40137e:	c3                   	ret
  40137f:	90                   	nop

0000000000401380 <_ZN7MyClassD1Ev>:
  401380:	55                   	push   %rbp
  401381:	48 89 e5             	mov    %rsp,%rbp
  401384:	48 83 ec 10          	sub    $0x10,%rsp
  401388:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
  40138c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
  401390:	8b 00                	mov    (%rax),%eax
  401392:	89 c6                	mov    %eax,%esi
  401394:	bf 1c 20 40 00       	mov    $0x40201c,%edi
  401399:	b8 00 00 00 00       	mov    $0x0,%eax
  40139e:	e8 8d fc ff ff       	call   401030 <printf@plt>
  4013a3:	90                   	nop
  4013a4:	c9                   	leave
  4013a5:	c3                   	ret

Disassembly of section .fini:

00000000004013a8 <_fini>:
  4013a8:	f3 0f 1e fa          	endbr64
  4013ac:	48 83 ec 08          	sub    $0x8,%rsp
  4013b0:	48 83 c4 08          	add    $0x8,%rsp
  4013b4:	c3                   	ret
