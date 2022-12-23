
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
    1020:	ff 35 92 2f 00 00    	push   0x2f92(%rip)        # 3fb8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 93 2f 00 00 	bnd jmp *0x2f93(%rip)        # 3fc0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    104f:	90                   	nop

Disassembly of section .plt.got:

0000000000001050 <__cxa_finalize@plt>:
    1050:	f3 0f 1e fa          	endbr64 
    1054:	f2 ff 25 9d 2f 00 00 	bnd jmp *0x2f9d(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    105b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001060 <__stack_chk_fail@plt>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	f2 ff 25 5d 2f 00 00 	bnd jmp *0x2f5d(%rip)        # 3fc8 <__stack_chk_fail@GLIBC_2.4>
    106b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001070 <printf@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 55 2f 00 00 	bnd jmp *0x2f55(%rip)        # 3fd0 <printf@GLIBC_2.2.5>
    107b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001080 <_start>:
    1080:	f3 0f 1e fa          	endbr64 
    1084:	31 ed                	xor    %ebp,%ebp
    1086:	49 89 d1             	mov    %rdx,%r9
    1089:	5e                   	pop    %rsi
    108a:	48 89 e2             	mov    %rsp,%rdx
    108d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1091:	50                   	push   %rax
    1092:	54                   	push   %rsp
    1093:	45 31 c0             	xor    %r8d,%r8d
    1096:	31 c9                	xor    %ecx,%ecx
    1098:	48 8d 3d 08 01 00 00 	lea    0x108(%rip),%rdi        # 11a7 <main>
    109f:	ff 15 33 2f 00 00    	call   *0x2f33(%rip)        # 3fd8 <__libc_start_main@GLIBC_2.34>
    10a5:	f4                   	hlt    
    10a6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    10ad:	00 00 00 

00000000000010b0 <deregister_tm_clones>:
    10b0:	48 8d 3d 59 2f 00 00 	lea    0x2f59(%rip),%rdi        # 4010 <__TMC_END__>
    10b7:	48 8d 05 52 2f 00 00 	lea    0x2f52(%rip),%rax        # 4010 <__TMC_END__>
    10be:	48 39 f8             	cmp    %rdi,%rax
    10c1:	74 15                	je     10d8 <deregister_tm_clones+0x28>
    10c3:	48 8b 05 16 2f 00 00 	mov    0x2f16(%rip),%rax        # 3fe0 <_ITM_deregisterTMCloneTable@Base>
    10ca:	48 85 c0             	test   %rax,%rax
    10cd:	74 09                	je     10d8 <deregister_tm_clones+0x28>
    10cf:	ff e0                	jmp    *%rax
    10d1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10d8:	c3                   	ret    
    10d9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010e0 <register_tm_clones>:
    10e0:	48 8d 3d 29 2f 00 00 	lea    0x2f29(%rip),%rdi        # 4010 <__TMC_END__>
    10e7:	48 8d 35 22 2f 00 00 	lea    0x2f22(%rip),%rsi        # 4010 <__TMC_END__>
    10ee:	48 29 fe             	sub    %rdi,%rsi
    10f1:	48 89 f0             	mov    %rsi,%rax
    10f4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10f8:	48 c1 f8 03          	sar    $0x3,%rax
    10fc:	48 01 c6             	add    %rax,%rsi
    10ff:	48 d1 fe             	sar    %rsi
    1102:	74 14                	je     1118 <register_tm_clones+0x38>
    1104:	48 8b 05 e5 2e 00 00 	mov    0x2ee5(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable@Base>
    110b:	48 85 c0             	test   %rax,%rax
    110e:	74 08                	je     1118 <register_tm_clones+0x38>
    1110:	ff e0                	jmp    *%rax
    1112:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1118:	c3                   	ret    
    1119:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001120 <__do_global_dtors_aux>:
    1120:	f3 0f 1e fa          	endbr64 
    1124:	80 3d e5 2e 00 00 00 	cmpb   $0x0,0x2ee5(%rip)        # 4010 <__TMC_END__>
    112b:	75 2b                	jne    1158 <__do_global_dtors_aux+0x38>
    112d:	55                   	push   %rbp
    112e:	48 83 3d c2 2e 00 00 	cmpq   $0x0,0x2ec2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1135:	00 
    1136:	48 89 e5             	mov    %rsp,%rbp
    1139:	74 0c                	je     1147 <__do_global_dtors_aux+0x27>
    113b:	48 8b 3d c6 2e 00 00 	mov    0x2ec6(%rip),%rdi        # 4008 <__dso_handle>
    1142:	e8 09 ff ff ff       	call   1050 <__cxa_finalize@plt>
    1147:	e8 64 ff ff ff       	call   10b0 <deregister_tm_clones>
    114c:	c6 05 bd 2e 00 00 01 	movb   $0x1,0x2ebd(%rip)        # 4010 <__TMC_END__>
    1153:	5d                   	pop    %rbp
    1154:	c3                   	ret    
    1155:	0f 1f 00             	nopl   (%rax)
    1158:	c3                   	ret    
    1159:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001160 <frame_dummy>:
    1160:	f3 0f 1e fa          	endbr64 
    1164:	e9 77 ff ff ff       	jmp    10e0 <register_tm_clones>

0000000000001169 <_Z3foov>:
    1169:	f3 0f 1e fa          	endbr64 
    116d:	55                   	push   %rbp
    116e:	48 89 e5             	mov    %rsp,%rbp
    1171:	90                   	nop
    1172:	5d                   	pop    %rbp
    1173:	c3                   	ret    

0000000000001174 <_Z14no_inline_funcv>:
    1174:	f3 0f 1e fa          	endbr64 
    1178:	55                   	push   %rbp
    1179:	48 89 e5             	mov    %rsp,%rbp
    117c:	48 83 ec 10          	sub    $0x10,%rsp
    1180:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    1187:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    118b:	8b 45 fc             	mov    -0x4(%rbp),%eax
    118e:	89 c6                	mov    %eax,%esi
    1190:	48 8d 05 6d 0e 00 00 	lea    0xe6d(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1197:	48 89 c7             	mov    %rax,%rdi
    119a:	b8 00 00 00 00       	mov    $0x0,%eax
    119f:	e8 cc fe ff ff       	call   1070 <printf@plt>
    11a4:	90                   	nop
    11a5:	c9                   	leave  
    11a6:	c3                   	ret    

00000000000011a7 <main>:
    11a7:	f3 0f 1e fa          	endbr64 
    11ab:	55                   	push   %rbp
    11ac:	48 89 e5             	mov    %rsp,%rbp
    11af:	48 83 ec 20          	sub    $0x20,%rsp
    11b3:	89 7d ec             	mov    %edi,-0x14(%rbp)
    11b6:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    11ba:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    11c1:	00 00 
    11c3:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    11c7:	31 c0                	xor    %eax,%eax
    11c9:	e8 a6 ff ff ff       	call   1174 <_Z14no_inline_funcv>
    11ce:	e8 4b 00 00 00       	call   121e <_Z11inline_funcv>
    11d3:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    11d7:	48 89 c7             	mov    %rax,%rdi
    11da:	e8 73 00 00 00       	call   1252 <_ZN6Holder20no_inline_class_funcEv>
    11df:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    11e3:	48 89 c7             	mov    %rax,%rdi
    11e6:	e8 9f 00 00 00       	call   128a <_ZN6Holder17inline_class_funcEv>
    11eb:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    11ef:	48 89 c7             	mov    %rax,%rdi
    11f2:	e8 cb 00 00 00       	call   12c2 <_ZN6Holder29template_no_inline_class_funcIiEEvv>
    11f7:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    11fb:	48 89 c7             	mov    %rax,%rdi
    11fe:	e8 f7 00 00 00       	call   12fa <_ZN6Holder26template_inline_class_funcIiEEvv>
    1203:	b8 00 00 00 00       	mov    $0x0,%eax
    1208:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    120c:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    1213:	00 00 
    1215:	74 05                	je     121c <main+0x75>
    1217:	e8 44 fe ff ff       	call   1060 <__stack_chk_fail@plt>
    121c:	c9                   	leave  
    121d:	c3                   	ret    

000000000000121e <_Z11inline_funcv>:
    121e:	f3 0f 1e fa          	endbr64 
    1222:	55                   	push   %rbp
    1223:	48 89 e5             	mov    %rsp,%rbp
    1226:	48 83 ec 10          	sub    $0x10,%rsp
    122a:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    1231:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    1235:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1238:	89 c6                	mov    %eax,%esi
    123a:	48 8d 05 c3 0d 00 00 	lea    0xdc3(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1241:	48 89 c7             	mov    %rax,%rdi
    1244:	b8 00 00 00 00       	mov    $0x0,%eax
    1249:	e8 22 fe ff ff       	call   1070 <printf@plt>
    124e:	90                   	nop
    124f:	c9                   	leave  
    1250:	c3                   	ret    
    1251:	90                   	nop

0000000000001252 <_ZN6Holder20no_inline_class_funcEv>:
    1252:	f3 0f 1e fa          	endbr64 
    1256:	55                   	push   %rbp
    1257:	48 89 e5             	mov    %rsp,%rbp
    125a:	48 83 ec 20          	sub    $0x20,%rsp
    125e:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1262:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    1269:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    126d:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1270:	89 c6                	mov    %eax,%esi
    1272:	48 8d 05 8b 0d 00 00 	lea    0xd8b(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1279:	48 89 c7             	mov    %rax,%rdi
    127c:	b8 00 00 00 00       	mov    $0x0,%eax
    1281:	e8 ea fd ff ff       	call   1070 <printf@plt>
    1286:	90                   	nop
    1287:	c9                   	leave  
    1288:	c3                   	ret    
    1289:	90                   	nop

000000000000128a <_ZN6Holder17inline_class_funcEv>:
    128a:	f3 0f 1e fa          	endbr64 
    128e:	55                   	push   %rbp
    128f:	48 89 e5             	mov    %rsp,%rbp
    1292:	48 83 ec 20          	sub    $0x20,%rsp
    1296:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    129a:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    12a1:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    12a5:	8b 45 fc             	mov    -0x4(%rbp),%eax
    12a8:	89 c6                	mov    %eax,%esi
    12aa:	48 8d 05 53 0d 00 00 	lea    0xd53(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    12b1:	48 89 c7             	mov    %rax,%rdi
    12b4:	b8 00 00 00 00       	mov    $0x0,%eax
    12b9:	e8 b2 fd ff ff       	call   1070 <printf@plt>
    12be:	90                   	nop
    12bf:	c9                   	leave  
    12c0:	c3                   	ret    
    12c1:	90                   	nop

00000000000012c2 <_ZN6Holder29template_no_inline_class_funcIiEEvv>:
    12c2:	f3 0f 1e fa          	endbr64 
    12c6:	55                   	push   %rbp
    12c7:	48 89 e5             	mov    %rsp,%rbp
    12ca:	48 83 ec 20          	sub    $0x20,%rsp
    12ce:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    12d2:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    12d9:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    12dd:	8b 45 fc             	mov    -0x4(%rbp),%eax
    12e0:	89 c6                	mov    %eax,%esi
    12e2:	48 8d 05 1b 0d 00 00 	lea    0xd1b(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    12e9:	48 89 c7             	mov    %rax,%rdi
    12ec:	b8 00 00 00 00       	mov    $0x0,%eax
    12f1:	e8 7a fd ff ff       	call   1070 <printf@plt>
    12f6:	90                   	nop
    12f7:	c9                   	leave  
    12f8:	c3                   	ret    
    12f9:	90                   	nop

00000000000012fa <_ZN6Holder26template_inline_class_funcIiEEvv>:
    12fa:	f3 0f 1e fa          	endbr64 
    12fe:	55                   	push   %rbp
    12ff:	48 89 e5             	mov    %rsp,%rbp
    1302:	48 83 ec 20          	sub    $0x20,%rsp
    1306:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    130a:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%rbp)
    1311:	83 45 fc 0a          	addl   $0xa,-0x4(%rbp)
    1315:	8b 45 fc             	mov    -0x4(%rbp),%eax
    1318:	89 c6                	mov    %eax,%esi
    131a:	48 8d 05 e3 0c 00 00 	lea    0xce3(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1321:	48 89 c7             	mov    %rax,%rdi
    1324:	b8 00 00 00 00       	mov    $0x0,%eax
    1329:	e8 42 fd ff ff       	call   1070 <printf@plt>
    132e:	90                   	nop
    132f:	c9                   	leave  
    1330:	c3                   	ret    

Disassembly of section .fini:

0000000000001334 <_fini>:
    1334:	f3 0f 1e fa          	endbr64 
    1338:	48 83 ec 08          	sub    $0x8,%rsp
    133c:	48 83 c4 08          	add    $0x8,%rsp
    1340:	c3                   	ret    
