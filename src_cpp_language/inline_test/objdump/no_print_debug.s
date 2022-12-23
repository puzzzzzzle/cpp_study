
/tmp/tmp.vnh9o7HhMq/cmake-build-debug-remote-docker/bin/src_cpp_language_inline_test:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 9a 2f 00 00    	push   0x2f9a(%rip)        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 9b 2f 00 00 	bnd jmp *0x2f9b(%rip)        # 3fc8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop

Disassembly of section .plt.got:

0000000000001040 <__cxa_finalize@plt>:
    1040:	f3 0f 1e fa          	endbr64 
    1044:	f2 ff 25 ad 2f 00 00 	bnd jmp *0x2fad(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    104b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001050 <__stack_chk_fail@plt>:
    1050:	f3 0f 1e fa          	endbr64 
    1054:	f2 ff 25 75 2f 00 00 	bnd jmp *0x2f75(%rip)        # 3fd0 <__stack_chk_fail@GLIBC_2.4>
    105b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001060 <_start>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	31 ed                	xor    %ebp,%ebp
    1066:	49 89 d1             	mov    %rdx,%r9
    1069:	5e                   	pop    %rsi
    106a:	48 89 e2             	mov    %rsp,%rdx
    106d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1071:	50                   	push   %rax
    1072:	54                   	push   %rsp
    1073:	45 31 c0             	xor    %r8d,%r8d
    1076:	31 c9                	xor    %ecx,%ecx
    1078:	48 8d 3d e0 00 00 00 	lea    0xe0(%rip),%rdi        # 115f <main>
    107f:	ff 15 53 2f 00 00    	call   *0x2f53(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    1085:	f4                   	hlt    
    1086:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    108d:	00 00 00 

0000000000001090 <deregister_tm_clones>:
    1090:	48 8d 3d 79 2f 00 00 	lea    0x2f79(%rip),%rdi        # 4010 <__TMC_END__>
    1097:	48 8d 05 72 2f 00 00 	lea    0x2f72(%rip),%rax        # 4010 <__TMC_END__>
    109e:	48 39 f8             	cmp    %rdi,%rax
    10a1:	74 15                	je     10b8 <deregister_tm_clones+0x28>
    10a3:	48 8b 05 36 2f 00 00 	mov    0x2f36(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10aa:	48 85 c0             	test   %rax,%rax
    10ad:	74 09                	je     10b8 <deregister_tm_clones+0x28>
    10af:	ff e0                	jmp    *%rax
    10b1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10b8:	c3                   	ret    
    10b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010c0 <register_tm_clones>:
    10c0:	48 8d 3d 49 2f 00 00 	lea    0x2f49(%rip),%rdi        # 4010 <__TMC_END__>
    10c7:	48 8d 35 42 2f 00 00 	lea    0x2f42(%rip),%rsi        # 4010 <__TMC_END__>
    10ce:	48 29 fe             	sub    %rdi,%rsi
    10d1:	48 89 f0             	mov    %rsi,%rax
    10d4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10d8:	48 c1 f8 03          	sar    $0x3,%rax
    10dc:	48 01 c6             	add    %rax,%rsi
    10df:	48 d1 fe             	sar    %rsi
    10e2:	74 14                	je     10f8 <register_tm_clones+0x38>
    10e4:	48 8b 05 05 2f 00 00 	mov    0x2f05(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    10eb:	48 85 c0             	test   %rax,%rax
    10ee:	74 08                	je     10f8 <register_tm_clones+0x38>
    10f0:	ff e0                	jmp    *%rax
    10f2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10f8:	c3                   	ret    
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <__do_global_dtors_aux>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	80 3d 05 2f 00 00 00 	cmpb   $0x0,0x2f05(%rip)        # 4010 <__TMC_END__>
    110b:	75 2b                	jne    1138 <__do_global_dtors_aux+0x38>
    110d:	55                   	push   %rbp
    110e:	48 83 3d e2 2e 00 00 	cmpq   $0x0,0x2ee2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1115:	00 
    1116:	48 89 e5             	mov    %rsp,%rbp
    1119:	74 0c                	je     1127 <__do_global_dtors_aux+0x27>
    111b:	48 8b 3d e6 2e 00 00 	mov    0x2ee6(%rip),%rdi        # 4008 <__dso_handle>
    1122:	e8 19 ff ff ff       	call   1040 <__cxa_finalize@plt>
    1127:	e8 64 ff ff ff       	call   1090 <deregister_tm_clones>
    112c:	c6 05 dd 2e 00 00 01 	movb   $0x1,0x2edd(%rip)        # 4010 <__TMC_END__>
    1133:	5d                   	pop    %rbp
    1134:	c3                   	ret    
    1135:	0f 1f 00             	nopl   (%rax)
    1138:	c3                   	ret    
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <frame_dummy>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	e9 77 ff ff ff       	jmp    10c0 <register_tm_clones>

0000000000001149 <_Z14no_inline_funcv>:
    1149:	f3 0f 1e fa          	endbr64 
    114d:	55                   	push   %rbp
    114e:	48 89 e5             	mov    %rsp,%rbp
    1151:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    1158:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    115c:	90                   	nop
    115d:	5d                   	pop    %rbp
    115e:	c3                   	ret    

000000000000115f <main>:
    115f:	f3 0f 1e fa          	endbr64 
    1163:	55                   	push   %rbp
    1164:	48 89 e5             	mov    %rsp,%rbp
    1167:	48 83 ec 20          	sub    $0x20,%rsp
    116b:	89 7d ec             	mov    %edi,-0x14(%rbp)
    116e:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    1172:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1179:	00 00 
    117b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    117f:	31 c0                	xor    %eax,%eax
    1181:	e8 c3 ff ff ff       	call   1149 <_Z14no_inline_funcv>
    1186:	e8 4b 00 00 00       	call   11d6 <_Z11inline_funcv>
    118b:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    118f:	48 89 c7             	mov    %rax,%rdi
    1192:	e8 55 00 00 00       	call   11ec <_ZN6Holder20no_inline_class_funcEv>
    1197:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    119b:	48 89 c7             	mov    %rax,%rdi
    119e:	e8 63 00 00 00       	call   1206 <_ZN6Holder17inline_class_funcEv>
    11a3:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    11a7:	48 89 c7             	mov    %rax,%rdi
    11aa:	e8 71 00 00 00       	call   1220 <_ZN6Holder29template_no_inline_class_funcIiEEvv>
    11af:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    11b3:	48 89 c7             	mov    %rax,%rdi
    11b6:	e8 7f 00 00 00       	call   123a <_ZN6Holder26template_inline_class_funcIiEEvv>
    11bb:	b8 00 00 00 00       	mov    $0x0,%eax
    11c0:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    11c4:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    11cb:	00 00 
    11cd:	74 05                	je     11d4 <main+0x75>
    11cf:	e8 7c fe ff ff       	call   1050 <__stack_chk_fail@plt>
    11d4:	c9                   	leave  
    11d5:	c3                   	ret    

00000000000011d6 <_Z11inline_funcv>:
    11d6:	f3 0f 1e fa          	endbr64 
    11da:	55                   	push   %rbp
    11db:	48 89 e5             	mov    %rsp,%rbp
    11de:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    11e5:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    11e9:	90                   	nop
    11ea:	5d                   	pop    %rbp
    11eb:	c3                   	ret    

00000000000011ec <_ZN6Holder20no_inline_class_funcEv>:
    11ec:	f3 0f 1e fa          	endbr64 
    11f0:	55                   	push   %rbp
    11f1:	48 89 e5             	mov    %rsp,%rbp
    11f4:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    11f8:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    11ff:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    1203:	90                   	nop
    1204:	5d                   	pop    %rbp
    1205:	c3                   	ret    

0000000000001206 <_ZN6Holder17inline_class_funcEv>:
    1206:	f3 0f 1e fa          	endbr64 
    120a:	55                   	push   %rbp
    120b:	48 89 e5             	mov    %rsp,%rbp
    120e:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1212:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    1219:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    121d:	90                   	nop
    121e:	5d                   	pop    %rbp
    121f:	c3                   	ret    

0000000000001220 <_ZN6Holder29template_no_inline_class_funcIiEEvv>:
    1220:	f3 0f 1e fa          	endbr64 
    1224:	55                   	push   %rbp
    1225:	48 89 e5             	mov    %rsp,%rbp
    1228:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    122c:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    1233:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    1237:	90                   	nop
    1238:	5d                   	pop    %rbp
    1239:	c3                   	ret    

000000000000123a <_ZN6Holder26template_inline_class_funcIiEEvv>:
    123a:	f3 0f 1e fa          	endbr64 
    123e:	55                   	push   %rbp
    123f:	48 89 e5             	mov    %rsp,%rbp
    1242:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1246:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    124d:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    1251:	90                   	nop
    1252:	5d                   	pop    %rbp
    1253:	c3                   	ret    

Disassembly of section .fini:

0000000000001254 <_fini>:
    1254:	f3 0f 1e fa          	endbr64 
    1258:	48 83 ec 08          	sub    $0x8,%rsp
    125c:	48 83 c4 08          	add    $0x8,%rsp
    1260:	c3                   	ret    
