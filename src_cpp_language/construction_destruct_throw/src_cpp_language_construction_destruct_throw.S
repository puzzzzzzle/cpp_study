
src_cpp_language_construction_destruct_throw:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 c9 2f 00 00 	mov    0x2fc9(%rip),%rax        # 3fd8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <printf@plt-0x10>:
    1020:	ff 35 ca 2f 00 00    	push   0x2fca(%rip)        # 3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 cc 2f 00 00    	jmp    *0x2fcc(%rip)        # 3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000001030 <printf@plt>:
    1030:	ff 25 ca 2f 00 00    	jmp    *0x2fca(%rip)        # 4000 <printf@GLIBC_2.2.5>
    1036:	68 00 00 00 00       	push   $0x0
    103b:	e9 e0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001040 <__cxa_begin_catch@plt>:
    1040:	ff 25 c2 2f 00 00    	jmp    *0x2fc2(%rip)        # 4008 <__cxa_begin_catch@CXXABI_1.3>
    1046:	68 01 00 00 00       	push   $0x1
    104b:	e9 d0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001050 <__cxa_allocate_exception@plt>:
    1050:	ff 25 ba 2f 00 00    	jmp    *0x2fba(%rip)        # 4010 <__cxa_allocate_exception@CXXABI_1.3>
    1056:	68 02 00 00 00       	push   $0x2
    105b:	e9 c0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001060 <__stack_chk_fail@plt>:
    1060:	ff 25 b2 2f 00 00    	jmp    *0x2fb2(%rip)        # 4018 <__stack_chk_fail@GLIBC_2.4>
    1066:	68 03 00 00 00       	push   $0x3
    106b:	e9 b0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001070 <puts@plt>:
    1070:	ff 25 aa 2f 00 00    	jmp    *0x2faa(%rip)        # 4020 <puts@GLIBC_2.2.5>
    1076:	68 04 00 00 00       	push   $0x4
    107b:	e9 a0 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001080 <__cxa_end_catch@plt>:
    1080:	ff 25 a2 2f 00 00    	jmp    *0x2fa2(%rip)        # 4028 <__cxa_end_catch@CXXABI_1.3>
    1086:	68 05 00 00 00       	push   $0x5
    108b:	e9 90 ff ff ff       	jmp    1020 <_init+0x20>

0000000000001090 <__cxa_throw@plt>:
    1090:	ff 25 9a 2f 00 00    	jmp    *0x2f9a(%rip)        # 4030 <__cxa_throw@CXXABI_1.3>
    1096:	68 06 00 00 00       	push   $0x6
    109b:	e9 80 ff ff ff       	jmp    1020 <_init+0x20>

00000000000010a0 <_Unwind_Resume@plt>:
    10a0:	ff 25 92 2f 00 00    	jmp    *0x2f92(%rip)        # 4038 <_Unwind_Resume@GCC_3.0>
    10a6:	68 07 00 00 00       	push   $0x7
    10ab:	e9 70 ff ff ff       	jmp    1020 <_init+0x20>

Disassembly of section .text:

00000000000010b0 <_start>:
    10b0:	f3 0f 1e fa          	endbr64
    10b4:	31 ed                	xor    %ebp,%ebp
    10b6:	49 89 d1             	mov    %rdx,%r9
    10b9:	5e                   	pop    %rsi
    10ba:	48 89 e2             	mov    %rsp,%rdx
    10bd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    10c1:	50                   	push   %rax
    10c2:	54                   	push   %rsp
    10c3:	45 31 c0             	xor    %r8d,%r8d
    10c6:	31 c9                	xor    %ecx,%ecx
    10c8:	48 8d 3d 00 02 00 00 	lea    0x200(%rip),%rdi        # 12cf <main>
    10cf:	ff 15 f3 2e 00 00    	call   *0x2ef3(%rip)        # 3fc8 <__libc_start_main@GLIBC_2.34>
    10d5:	f4                   	hlt
    10d6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    10dd:	00 00 00 
    10e0:	48 8d 3d 79 2f 00 00 	lea    0x2f79(%rip),%rdi        # 4060 <__TMC_END__>
    10e7:	48 8d 05 72 2f 00 00 	lea    0x2f72(%rip),%rax        # 4060 <__TMC_END__>
    10ee:	48 39 f8             	cmp    %rdi,%rax
    10f1:	74 15                	je     1108 <_start+0x58>
    10f3:	48 8b 05 d6 2e 00 00 	mov    0x2ed6(%rip),%rax        # 3fd0 <_ITM_deregisterTMCloneTable@Base>
    10fa:	48 85 c0             	test   %rax,%rax
    10fd:	74 09                	je     1108 <_start+0x58>
    10ff:	ff e0                	jmp    *%rax
    1101:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1108:	c3                   	ret
    1109:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1110:	48 8d 3d 49 2f 00 00 	lea    0x2f49(%rip),%rdi        # 4060 <__TMC_END__>
    1117:	48 8d 35 42 2f 00 00 	lea    0x2f42(%rip),%rsi        # 4060 <__TMC_END__>
    111e:	48 29 fe             	sub    %rdi,%rsi
    1121:	48 89 f0             	mov    %rsi,%rax
    1124:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1128:	48 c1 f8 03          	sar    $0x3,%rax
    112c:	48 01 c6             	add    %rax,%rsi
    112f:	48 d1 fe             	sar    $1,%rsi
    1132:	74 14                	je     1148 <_start+0x98>
    1134:	48 8b 05 a5 2e 00 00 	mov    0x2ea5(%rip),%rax        # 3fe0 <_ITM_registerTMCloneTable@Base>
    113b:	48 85 c0             	test   %rax,%rax
    113e:	74 08                	je     1148 <_start+0x98>
    1140:	ff e0                	jmp    *%rax
    1142:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1148:	c3                   	ret
    1149:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1150:	f3 0f 1e fa          	endbr64
    1154:	80 3d 05 2f 00 00 00 	cmpb   $0x0,0x2f05(%rip)        # 4060 <__TMC_END__>
    115b:	75 33                	jne    1190 <_start+0xe0>
    115d:	55                   	push   %rbp
    115e:	48 83 3d 5a 2e 00 00 	cmpq   $0x0,0x2e5a(%rip)        # 3fc0 <__cxa_finalize@GLIBC_2.2.5>
    1165:	00 
    1166:	48 89 e5             	mov    %rsp,%rbp
    1169:	74 0d                	je     1178 <_start+0xc8>
    116b:	48 8b 3d d6 2e 00 00 	mov    0x2ed6(%rip),%rdi        # 4048 <__dso_handle>
    1172:	ff 15 48 2e 00 00    	call   *0x2e48(%rip)        # 3fc0 <__cxa_finalize@GLIBC_2.2.5>
    1178:	e8 63 ff ff ff       	call   10e0 <_start+0x30>
    117d:	c6 05 dc 2e 00 00 01 	movb   $0x1,0x2edc(%rip)        # 4060 <__TMC_END__>
    1184:	5d                   	pop    %rbp
    1185:	c3                   	ret
    1186:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    118d:	00 00 00 
    1190:	c3                   	ret
    1191:	66 66 2e 0f 1f 84 00 	data16 cs nopw 0x0(%rax,%rax,1)
    1198:	00 00 00 00 
    119c:	0f 1f 40 00          	nopl   0x0(%rax)
    11a0:	f3 0f 1e fa          	endbr64
    11a4:	e9 67 ff ff ff       	jmp    1110 <_start+0x60>

00000000000011a9 <_Z8functionv>:
    11a9:	55                   	push   %rbp
    11aa:	48 89 e5             	mov    %rsp,%rbp
    11ad:	53                   	push   %rbx
    11ae:	48 83 ec 28          	sub    $0x28,%rsp
    11b2:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    11b9:	00 00 
    11bb:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    11bf:	31 c0                	xor    %eax,%eax
    11c1:	48 8d 45 d4          	lea    -0x2c(%rbp),%rax
    11c5:	be 01 00 00 00       	mov    $0x1,%esi
    11ca:	48 89 c7             	mov    %rax,%rdi
    11cd:	e8 5c 01 00 00       	call   132e <_ZN7MyClassC1Ei>
    11d2:	48 8d 45 d8          	lea    -0x28(%rbp),%rax
    11d6:	be 02 00 00 00       	mov    $0x2,%esi
    11db:	48 89 c7             	mov    %rax,%rdi
    11de:	e8 4b 01 00 00       	call   132e <_ZN7MyClassC1Ei>
    11e3:	48 8d 45 dc          	lea    -0x24(%rbp),%rax
    11e7:	be 03 00 00 00       	mov    $0x3,%esi
    11ec:	48 89 c7             	mov    %rax,%rdi
    11ef:	e8 3a 01 00 00       	call   132e <_ZN7MyClassC1Ei>
    11f4:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    11f8:	be 04 00 00 00       	mov    $0x4,%esi
    11fd:	48 89 c7             	mov    %rax,%rdi
    1200:	e8 29 01 00 00       	call   132e <_ZN7MyClassC1Ei>
    1205:	48 8d 45 e4          	lea    -0x1c(%rbp),%rax
    1209:	be 05 00 00 00       	mov    $0x5,%esi
    120e:	48 89 c7             	mov    %rax,%rdi
    1211:	e8 18 01 00 00       	call   132e <_ZN7MyClassC1Ei>
    1216:	48 8d 45 e4          	lea    -0x1c(%rbp),%rax
    121a:	48 89 c7             	mov    %rax,%rdi
    121d:	e8 72 01 00 00       	call   1394 <_ZN7MyClassD1Ev>
    1222:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    1226:	48 89 c7             	mov    %rax,%rdi
    1229:	e8 66 01 00 00       	call   1394 <_ZN7MyClassD1Ev>
    122e:	48 8d 45 dc          	lea    -0x24(%rbp),%rax
    1232:	48 89 c7             	mov    %rax,%rdi
    1235:	e8 5a 01 00 00       	call   1394 <_ZN7MyClassD1Ev>
    123a:	48 8d 45 d8          	lea    -0x28(%rbp),%rax
    123e:	48 89 c7             	mov    %rax,%rdi
    1241:	e8 4e 01 00 00       	call   1394 <_ZN7MyClassD1Ev>
    1246:	48 8d 45 d4          	lea    -0x2c(%rbp),%rax
    124a:	48 89 c7             	mov    %rax,%rdi
    124d:	e8 42 01 00 00       	call   1394 <_ZN7MyClassD1Ev>
    1252:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1256:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    125d:	00 00 
    125f:	74 68                	je     12c9 <_Z8functionv+0x120>
    1261:	eb 61                	jmp    12c4 <_Z8functionv+0x11b>
    1263:	48 89 c3             	mov    %rax,%rbx
    1266:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    126a:	48 89 c7             	mov    %rax,%rdi
    126d:	e8 22 01 00 00       	call   1394 <_ZN7MyClassD1Ev>
    1272:	eb 03                	jmp    1277 <_Z8functionv+0xce>
    1274:	48 89 c3             	mov    %rax,%rbx
    1277:	48 8d 45 dc          	lea    -0x24(%rbp),%rax
    127b:	48 89 c7             	mov    %rax,%rdi
    127e:	e8 11 01 00 00       	call   1394 <_ZN7MyClassD1Ev>
    1283:	eb 03                	jmp    1288 <_Z8functionv+0xdf>
    1285:	48 89 c3             	mov    %rax,%rbx
    1288:	48 8d 45 d8          	lea    -0x28(%rbp),%rax
    128c:	48 89 c7             	mov    %rax,%rdi
    128f:	e8 00 01 00 00       	call   1394 <_ZN7MyClassD1Ev>
    1294:	eb 03                	jmp    1299 <_Z8functionv+0xf0>
    1296:	48 89 c3             	mov    %rax,%rbx
    1299:	48 8d 45 d4          	lea    -0x2c(%rbp),%rax
    129d:	48 89 c7             	mov    %rax,%rdi
    12a0:	e8 ef 00 00 00       	call   1394 <_ZN7MyClassD1Ev>
    12a5:	48 89 d8             	mov    %rbx,%rax
    12a8:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
    12ac:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    12b3:	00 00 
    12b5:	74 05                	je     12bc <_Z8functionv+0x113>
    12b7:	e8 a4 fd ff ff       	call   1060 <__stack_chk_fail@plt>
    12bc:	48 89 c7             	mov    %rax,%rdi
    12bf:	e8 dc fd ff ff       	call   10a0 <_Unwind_Resume@plt>
    12c4:	e8 97 fd ff ff       	call   1060 <__stack_chk_fail@plt>
    12c9:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    12cd:	c9                   	leave
    12ce:	c3                   	ret

00000000000012cf <main>:
    12cf:	55                   	push   %rbp
    12d0:	48 89 e5             	mov    %rsp,%rbp
    12d3:	53                   	push   %rbx
    12d4:	48 83 ec 18          	sub    $0x18,%rsp
    12d8:	e8 cc fe ff ff       	call   11a9 <_Z8functionv>
    12dd:	b8 00 00 00 00       	mov    $0x0,%eax
    12e2:	eb 43                	jmp    1327 <main+0x58>
    12e4:	48 83 fa 01          	cmp    $0x1,%rdx
    12e8:	74 08                	je     12f2 <main+0x23>
    12ea:	48 89 c7             	mov    %rax,%rdi
    12ed:	e8 ae fd ff ff       	call   10a0 <_Unwind_Resume@plt>
    12f2:	48 89 c7             	mov    %rax,%rdi
    12f5:	e8 46 fd ff ff       	call   1040 <__cxa_begin_catch@plt>
    12fa:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    12fe:	48 8d 05 2e 0d 00 00 	lea    0xd2e(%rip),%rax        # 2033 <_IO_stdin_used+0x33>
    1305:	48 89 c7             	mov    %rax,%rdi
    1308:	e8 63 fd ff ff       	call   1070 <puts@plt>
    130d:	e8 6e fd ff ff       	call   1080 <__cxa_end_catch@plt>
    1312:	eb c9                	jmp    12dd <main+0xe>
    1314:	48 89 c3             	mov    %rax,%rbx
    1317:	e8 64 fd ff ff       	call   1080 <__cxa_end_catch@plt>
    131c:	48 89 d8             	mov    %rbx,%rax
    131f:	48 89 c7             	mov    %rax,%rdi
    1322:	e8 79 fd ff ff       	call   10a0 <_Unwind_Resume@plt>
    1327:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    132b:	c9                   	leave
    132c:	c3                   	ret
    132d:	90                   	nop

000000000000132e <_ZN7MyClassC1Ei>:
    132e:	55                   	push   %rbp
    132f:	48 89 e5             	mov    %rsp,%rbp
    1332:	48 83 ec 10          	sub    $0x10,%rsp
    1336:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    133a:	89 75 f4             	mov    %esi,-0xc(%rbp)
    133d:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1341:	8b 55 f4             	mov    -0xc(%rbp),%edx
    1344:	89 10                	mov    %edx,(%rax)
    1346:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    134a:	8b 00                	mov    (%rax),%eax
    134c:	89 c6                	mov    %eax,%esi
    134e:	48 8d 05 af 0c 00 00 	lea    0xcaf(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    1355:	48 89 c7             	mov    %rax,%rdi
    1358:	b8 00 00 00 00       	mov    $0x0,%eax
    135d:	e8 ce fc ff ff       	call   1030 <printf@plt>
    1362:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1366:	8b 00                	mov    (%rax),%eax
    1368:	83 f8 04             	cmp    $0x4,%eax
    136b:	75 24                	jne    1391 <_ZN7MyClassC1Ei+0x63>
    136d:	bf 01 00 00 00       	mov    $0x1,%edi
    1372:	e8 d9 fc ff ff       	call   1050 <__cxa_allocate_exception@plt>
    1377:	48 89 c1             	mov    %rax,%rcx
    137a:	ba 00 00 00 00       	mov    $0x0,%edx
    137f:	48 8d 05 1a 2a 00 00 	lea    0x2a1a(%rip),%rax        # 3da0 <_ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3>
    1386:	48 89 c6             	mov    %rax,%rsi
    1389:	48 89 cf             	mov    %rcx,%rdi
    138c:	e8 ff fc ff ff       	call   1090 <__cxa_throw@plt>
    1391:	90                   	nop
    1392:	c9                   	leave
    1393:	c3                   	ret

0000000000001394 <_ZN7MyClassD1Ev>:
    1394:	55                   	push   %rbp
    1395:	48 89 e5             	mov    %rsp,%rbp
    1398:	48 83 ec 10          	sub    $0x10,%rsp
    139c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    13a0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    13a4:	8b 00                	mov    (%rax),%eax
    13a6:	89 c6                	mov    %eax,%esi
    13a8:	48 8d 05 6d 0c 00 00 	lea    0xc6d(%rip),%rax        # 201c <_IO_stdin_used+0x1c>
    13af:	48 89 c7             	mov    %rax,%rdi
    13b2:	b8 00 00 00 00       	mov    $0x0,%eax
    13b7:	e8 74 fc ff ff       	call   1030 <printf@plt>
    13bc:	90                   	nop
    13bd:	c9                   	leave
    13be:	c3                   	ret

Disassembly of section .fini:

00000000000013c0 <_fini>:
    13c0:	f3 0f 1e fa          	endbr64
    13c4:	48 83 ec 08          	sub    $0x8,%rsp
    13c8:	48 83 c4 08          	add    $0x8,%rsp
    13cc:	c3                   	ret
