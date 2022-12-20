
../../bin/src_cpp_language_class_link:     file format elf64-x86-64


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

0000000000001060 <puts@plt>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	f2 ff 25 5d 2f 00 00 	bnd jmp *0x2f5d(%rip)        # 3fc8 <puts@GLIBC_2.2.5>
    106b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001070 <__stack_chk_fail@plt>:
    1070:	f3 0f 1e fa          	endbr64 
    1074:	f2 ff 25 55 2f 00 00 	bnd jmp *0x2f55(%rip)        # 3fd0 <__stack_chk_fail@GLIBC_2.4>
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
    1098:	48 8d 3d ca 00 00 00 	lea    0xca(%rip),%rdi        # 1169 <main>
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

0000000000001169 <main>:
    1169:	f3 0f 1e fa          	endbr64 
    116d:	55                   	push   %rbp
    116e:	48 89 e5             	mov    %rsp,%rbp
    1171:	48 83 ec 10          	sub    $0x10,%rsp
    1175:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    117c:	00 00 
    117e:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1182:	31 c0                	xor    %eax,%eax
    1184:	48 8d 05 8d 0e 00 00 	lea    0xe8d(%rip),%rax        # 2018 <_IO_stdin_used+0x18>
    118b:	48 89 c7             	mov    %rax,%rdi
    118e:	e8 cd fe ff ff       	call   1060 <puts@plt>
    1193:	48 8d 45 f6          	lea    -0xa(%rbp),%rax
    1197:	48 89 c7             	mov    %rax,%rdi
    119a:	e8 4f 00 00 00       	call   11ee <_ZN6Class13funEv>
    119f:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    11a3:	48 89 c7             	mov    %rax,%rdi
    11a6:	e8 21 00 00 00       	call   11cc <_ZN6Class23funEv>
    11ab:	e8 60 00 00 00       	call   1210 <_Z4testv>
    11b0:	b8 00 00 00 00       	mov    $0x0,%eax
    11b5:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    11b9:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    11c0:	00 00 
    11c2:	74 05                	je     11c9 <main+0x60>
    11c4:	e8 a7 fe ff ff       	call   1070 <__stack_chk_fail@plt>
    11c9:	c9                   	leave  
    11ca:	c3                   	ret    
    11cb:	90                   	nop

00000000000011cc <_ZN6Class23funEv>:
    11cc:	f3 0f 1e fa          	endbr64 
    11d0:	55                   	push   %rbp
    11d1:	48 89 e5             	mov    %rsp,%rbp
    11d4:	48 83 ec 10          	sub    $0x10,%rsp
    11d8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    11dc:	48 8d 05 21 0e 00 00 	lea    0xe21(%rip),%rax        # 2004 <_IO_stdin_used+0x4>
    11e3:	48 89 c7             	mov    %rax,%rdi
    11e6:	e8 75 fe ff ff       	call   1060 <puts@plt>
    11eb:	90                   	nop
    11ec:	c9                   	leave  
    11ed:	c3                   	ret    

00000000000011ee <_ZN6Class13funEv>:
    11ee:	f3 0f 1e fa          	endbr64 
    11f2:	55                   	push   %rbp
    11f3:	48 89 e5             	mov    %rsp,%rbp
    11f6:	48 83 ec 10          	sub    $0x10,%rsp
    11fa:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    11fe:	48 8d 05 06 0e 00 00 	lea    0xe06(%rip),%rax        # 200b <_IO_stdin_used+0xb>
    1205:	48 89 c7             	mov    %rax,%rdi
    1208:	e8 53 fe ff ff       	call   1060 <puts@plt>
    120d:	90                   	nop
    120e:	c9                   	leave  
    120f:	c3                   	ret    

0000000000001210 <_Z4testv>:
    1210:	f3 0f 1e fa          	endbr64 
    1214:	55                   	push   %rbp
    1215:	48 89 e5             	mov    %rsp,%rbp
    1218:	48 83 ec 10          	sub    $0x10,%rsp
    121c:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1223:	00 00 
    1225:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1229:	31 c0                	xor    %eax,%eax
    122b:	48 8d 05 06 0e 00 00 	lea    0xe06(%rip),%rax        # 2038 <_IO_stdin_used+0x38>
    1232:	48 89 c7             	mov    %rax,%rdi
    1235:	e8 26 fe ff ff       	call   1060 <puts@plt>
    123a:	48 8d 45 f6          	lea    -0xa(%rbp),%rax
    123e:	48 89 c7             	mov    %rax,%rdi
    1241:	e8 a8 ff ff ff       	call   11ee <_ZN6Class13funEv>
    1246:	48 8d 45 f7          	lea    -0x9(%rbp),%rax
    124a:	48 89 c7             	mov    %rax,%rdi
    124d:	e8 7a ff ff ff       	call   11cc <_ZN6Class23funEv>
    1252:	90                   	nop
    1253:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1257:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    125e:	00 00 
    1260:	74 05                	je     1267 <_Z4testv+0x57>
    1262:	e8 09 fe ff ff       	call   1070 <__stack_chk_fail@plt>
    1267:	c9                   	leave  
    1268:	c3                   	ret    

Disassembly of section .fini:

000000000000126c <_fini>:
    126c:	f3 0f 1e fa          	endbr64 
    1270:	48 83 ec 08          	sub    $0x8,%rsp
    1274:	48 83 c4 08          	add    $0x8,%rsp
    1278:	c3                   	ret    
