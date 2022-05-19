
co_samples_sample_4:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
_init():
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 2f 00 00 	mov    0x2fd9(%rip),%rax        # 3fe8 <__gmon_start__>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	callq  *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	retq   

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 52 2f 00 00    	pushq  0x2f52(%rip)        # 3f78 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 53 2f 00 00 	bnd jmpq *0x2f53(%rip)        # 3f80 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	pushq  $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmpq 1020 <.plt>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	pushq  $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmpq 1020 <.plt>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	pushq  $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmpq 1020 <.plt>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	pushq  $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmpq 1020 <.plt>
    106f:	90                   	nop
    1070:	f3 0f 1e fa          	endbr64 
    1074:	68 04 00 00 00       	pushq  $0x4
    1079:	f2 e9 a1 ff ff ff    	bnd jmpq 1020 <.plt>
    107f:	90                   	nop
    1080:	f3 0f 1e fa          	endbr64 
    1084:	68 05 00 00 00       	pushq  $0x5
    1089:	f2 e9 91 ff ff ff    	bnd jmpq 1020 <.plt>
    108f:	90                   	nop
    1090:	f3 0f 1e fa          	endbr64 
    1094:	68 06 00 00 00       	pushq  $0x6
    1099:	f2 e9 81 ff ff ff    	bnd jmpq 1020 <.plt>
    109f:	90                   	nop
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	68 07 00 00 00       	pushq  $0x7
    10a9:	f2 e9 71 ff ff ff    	bnd jmpq 1020 <.plt>
    10af:	90                   	nop
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	68 08 00 00 00       	pushq  $0x8
    10b9:	f2 e9 61 ff ff ff    	bnd jmpq 1020 <.plt>
    10bf:	90                   	nop

Disassembly of section .plt.got:

00000000000010c0 <__cxa_finalize@plt>:
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	f2 ff 25 05 2f 00 00 	bnd jmpq *0x2f05(%rip)        # 3fd0 <__cxa_finalize@GLIBC_2.2.5>
    10cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

00000000000010d0 <__cxa_begin_catch@plt>:
    10d0:	f3 0f 1e fa          	endbr64 
    10d4:	f2 ff 25 ad 2e 00 00 	bnd jmpq *0x2ead(%rip)        # 3f88 <__cxa_begin_catch@CXXABI_1.3>
    10db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010e0 <__cxa_atexit@plt>:
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	f2 ff 25 a5 2e 00 00 	bnd jmpq *0x2ea5(%rip)        # 3f90 <__cxa_atexit@GLIBC_2.2.5>
    10eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000010f0 <operator delete(void*)@plt>:
    10f0:	f3 0f 1e fa          	endbr64 
    10f4:	f2 ff 25 9d 2e 00 00 	bnd jmpq *0x2e9d(%rip)        # 3f98 <operator delete(void*)@GLIBCXX_3.4>
    10fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001100 <operator new(unsigned long)@plt>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	f2 ff 25 95 2e 00 00 	bnd jmpq *0x2e95(%rip)        # 3fa0 <operator new(unsigned long)@GLIBCXX_3.4>
    110b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001110 <__stack_chk_fail@plt>:
    1110:	f3 0f 1e fa          	endbr64 
    1114:	f2 ff 25 8d 2e 00 00 	bnd jmpq *0x2e8d(%rip)        # 3fa8 <__stack_chk_fail@GLIBC_2.4>
    111b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001120 <__cxa_rethrow@plt>:
    1120:	f3 0f 1e fa          	endbr64 
    1124:	f2 ff 25 85 2e 00 00 	bnd jmpq *0x2e85(%rip)        # 3fb0 <__cxa_rethrow@CXXABI_1.3>
    112b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001130 <std::ios_base::Init::Init()@plt>:
    1130:	f3 0f 1e fa          	endbr64 
    1134:	f2 ff 25 7d 2e 00 00 	bnd jmpq *0x2e7d(%rip)        # 3fb8 <std::ios_base::Init::Init()@GLIBCXX_3.4>
    113b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001140 <__cxa_end_catch@plt>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	f2 ff 25 75 2e 00 00 	bnd jmpq *0x2e75(%rip)        # 3fc0 <__cxa_end_catch@CXXABI_1.3>
    114b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001150 <_Unwind_Resume@plt>:
    1150:	f3 0f 1e fa          	endbr64 
    1154:	f2 ff 25 6d 2e 00 00 	bnd jmpq *0x2e6d(%rip)        # 3fc8 <_Unwind_Resume@GCC_3.0>
    115b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000001160 <_start>:
_start():
    1160:	f3 0f 1e fa          	endbr64 
    1164:	31 ed                	xor    %ebp,%ebp
    1166:	49 89 d1             	mov    %rdx,%r9
    1169:	5e                   	pop    %rsi
    116a:	48 89 e2             	mov    %rsp,%rdx
    116d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1171:	50                   	push   %rax
    1172:	54                   	push   %rsp
    1173:	4c 8d 05 16 07 00 00 	lea    0x716(%rip),%r8        # 1890 <__libc_csu_fini>
    117a:	48 8d 0d 9f 06 00 00 	lea    0x69f(%rip),%rcx        # 1820 <__libc_csu_init>
    1181:	48 8d 3d 3c 04 00 00 	lea    0x43c(%rip),%rdi        # 15c4 <main>
    1188:	ff 15 52 2e 00 00    	callq  *0x2e52(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    118e:	f4                   	hlt    
    118f:	90                   	nop

0000000000001190 <deregister_tm_clones>:
deregister_tm_clones():
    1190:	48 8d 3d 99 2e 00 00 	lea    0x2e99(%rip),%rdi        # 4030 <__TMC_END__>
    1197:	48 8d 05 92 2e 00 00 	lea    0x2e92(%rip),%rax        # 4030 <__TMC_END__>
    119e:	48 39 f8             	cmp    %rdi,%rax
    11a1:	74 15                	je     11b8 <deregister_tm_clones+0x28>
    11a3:	48 8b 05 2e 2e 00 00 	mov    0x2e2e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    11aa:	48 85 c0             	test   %rax,%rax
    11ad:	74 09                	je     11b8 <deregister_tm_clones+0x28>
    11af:	ff e0                	jmpq   *%rax
    11b1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    11b8:	c3                   	retq   
    11b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000011c0 <register_tm_clones>:
register_tm_clones():
    11c0:	48 8d 3d 69 2e 00 00 	lea    0x2e69(%rip),%rdi        # 4030 <__TMC_END__>
    11c7:	48 8d 35 62 2e 00 00 	lea    0x2e62(%rip),%rsi        # 4030 <__TMC_END__>
    11ce:	48 29 fe             	sub    %rdi,%rsi
    11d1:	48 89 f0             	mov    %rsi,%rax
    11d4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    11d8:	48 c1 f8 03          	sar    $0x3,%rax
    11dc:	48 01 c6             	add    %rax,%rsi
    11df:	48 d1 fe             	sar    %rsi
    11e2:	74 14                	je     11f8 <register_tm_clones+0x38>
    11e4:	48 8b 05 05 2e 00 00 	mov    0x2e05(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    11eb:	48 85 c0             	test   %rax,%rax
    11ee:	74 08                	je     11f8 <register_tm_clones+0x38>
    11f0:	ff e0                	jmpq   *%rax
    11f2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    11f8:	c3                   	retq   
    11f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001200 <__do_global_dtors_aux>:
__do_global_dtors_aux():
    1200:	f3 0f 1e fa          	endbr64 
    1204:	80 3d 25 2e 00 00 00 	cmpb   $0x0,0x2e25(%rip)        # 4030 <__TMC_END__>
    120b:	75 2b                	jne    1238 <__do_global_dtors_aux+0x38>
    120d:	55                   	push   %rbp
    120e:	48 83 3d ba 2d 00 00 	cmpq   $0x0,0x2dba(%rip)        # 3fd0 <__cxa_finalize@GLIBC_2.2.5>
    1215:	00 
    1216:	48 89 e5             	mov    %rsp,%rbp
    1219:	74 0c                	je     1227 <__do_global_dtors_aux+0x27>
    121b:	48 8b 3d e6 2d 00 00 	mov    0x2de6(%rip),%rdi        # 4008 <__dso_handle>
    1222:	e8 99 fe ff ff       	callq  10c0 <__cxa_finalize@plt>
    1227:	e8 64 ff ff ff       	callq  1190 <deregister_tm_clones>
    122c:	c6 05 fd 2d 00 00 01 	movb   $0x1,0x2dfd(%rip)        # 4030 <__TMC_END__>
    1233:	5d                   	pop    %rbp
    1234:	c3                   	retq   
    1235:	0f 1f 00             	nopl   (%rax)
    1238:	c3                   	retq   
    1239:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001240 <frame_dummy>:
frame_dummy():
    1240:	f3 0f 1e fa          	endbr64 
    1244:	e9 77 ff ff ff       	jmpq   11c0 <register_tm_clones>

0000000000001249 <std::__n4861::__dummy_resume_destroy()>:
_ZNSt7__n486122__dummy_resume_destroyEv():
/usr/include/c++/10/coroutine:222
  struct noop_coroutine_promise
  {
  };

  void __dummy_resume_destroy() __attribute__((__weak__));
  void __dummy_resume_destroy() {}
    1249:	f3 0f 1e fa          	endbr64 
    124d:	55                   	push   %rbp
    124e:	48 89 e5             	mov    %rsp,%rbp
    1251:	90                   	nop
    1252:	5d                   	pop    %rbp
    1253:	c3                   	retq   

0000000000001254 <resume_latter()>:
_Z13resume_latterv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
    void unhandled_exception() { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }
  };
  task(const handle_type& h) : h_(h) {}
  handle_type h_{};
};
auto resume_latter() -> task {
    1254:	f3 0f 1e fa          	endbr64 
    1258:	55                   	push   %rbp
    1259:	48 89 e5             	mov    %rsp,%rbp
    125c:	53                   	push   %rbx
    125d:	48 83 ec 18          	sub    $0x18,%rsp
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
  // 对象到调用者上
  co_await awaitable_var;

  // 这个并不会被立即执行 需要等 协程 resume 后才会
  LOG_DEBUG("end")
}
    1261:	48 c7 45 e8 00 00 00 	movq   $0x0,-0x18(%rbp)
    1268:	00 
    1269:	c6 45 e6 00          	movb   $0x0,-0x1a(%rbp)
    126d:	c6 45 e7 00          	movb   $0x0,-0x19(%rbp)
    1271:	b8 28 00 00 00       	mov    $0x28,%eax
    1276:	48 89 c7             	mov    %rax,%rdi
    1279:	e8 82 fe ff ff       	callq  1100 <operator new(unsigned long)@plt>
    127e:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
auto resume_latter() -> task {
    1282:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1286:	c6 40 11 01          	movb   $0x1,0x11(%rax)
    128a:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    128e:	48 8d 15 7a 00 00 00 	lea    0x7a(%rip),%rdx        # 130f <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)>
    1295:	48 89 10             	mov    %rdx,(%rax)
    1298:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    129c:	48 8d 15 a7 02 00 00 	lea    0x2a7(%rip),%rdx        # 154a <_Z13resume_latterv.destroy(resume_latter()::_Z13resume_latterv.frame*)>
    12a3:	48 89 50 08          	mov    %rdx,0x8(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
}
    12a7:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12ab:	48 83 c0 10          	add    $0x10,%rax
    12af:	48 89 c7             	mov    %rax,%rdi
    12b2:	e8 25 04 00 00       	callq  16dc <task::promise_type::get_return_object()>
    12b7:	48 89 c3             	mov    %rax,%rbx
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
auto resume_latter() -> task {
    12ba:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12be:	66 c7 40 12 00 00    	movw   $0x0,0x12(%rax)
    12c4:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12c8:	48 89 c7             	mov    %rax,%rdi
    12cb:	e8 3f 00 00 00       	callq  130f <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
}
    12d0:	eb 34                	jmp    1306 <resume_latter()+0xb2>
    12d2:	f3 0f 1e fa          	endbr64 
    12d6:	48 89 c7             	mov    %rax,%rdi
    12d9:	e8 f2 fd ff ff       	callq  10d0 <__cxa_begin_catch@plt>
    12de:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    12e2:	48 89 c7             	mov    %rax,%rdi
    12e5:	e8 06 fe ff ff       	callq  10f0 <operator delete(void*)@plt>
    12ea:	e8 31 fe ff ff       	callq  1120 <__cxa_rethrow@plt>
    12ef:	f3 0f 1e fa          	endbr64 
    12f3:	48 89 c3             	mov    %rax,%rbx
    12f6:	e8 45 fe ff ff       	callq  1140 <__cxa_end_catch@plt>
    12fb:	48 89 d8             	mov    %rbx,%rax
    12fe:	48 89 c7             	mov    %rax,%rdi
    1301:	e8 4a fe ff ff       	callq  1150 <_Unwind_Resume@plt>
    1306:	48 89 d8             	mov    %rbx,%rax
    1309:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    130d:	c9                   	leaveq 
    130e:	c3                   	retq   

000000000000130f <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)>:
_Z24_Z13resume_latterv.actorPZ13resume_lattervE24_Z13resume_latterv.frame():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
    130f:	f3 0f 1e fa          	endbr64 
    1313:	55                   	push   %rbp
    1314:	48 89 e5             	mov    %rsp,%rbp
    1317:	53                   	push   %rbx
    1318:	48 83 ec 28          	sub    $0x28,%rsp
    131c:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    1320:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1327:	00 00 
    1329:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    132d:	31 c0                	xor    %eax,%eax
    132f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1333:	0f b7 40 12          	movzwl 0x12(%rax),%eax
    1337:	83 e0 01             	and    $0x1,%eax
    133a:	66 85 c0             	test   %ax,%ax
    133d:	74 3b                	je     137a <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x6b>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65 (discriminator 1)
    133f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1343:	0f b7 40 12          	movzwl 0x12(%rax),%eax
    1347:	0f b7 c0             	movzwl %ax,%eax
    134a:	83 f8 07             	cmp    $0x7,%eax
    134d:	0f 84 a6 01 00 00    	je     14f9 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x1ea>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
    1353:	83 f8 07             	cmp    $0x7,%eax
    1356:	7f 20                	jg     1378 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x69>
    1358:	83 f8 05             	cmp    $0x5,%eax
    135b:	0f 84 1a 01 00 00    	je     147b <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x16c>
    1361:	83 f8 05             	cmp    $0x5,%eax
    1364:	7f 12                	jg     1378 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x69>
    1366:	83 f8 01             	cmp    $0x1,%eax
    1369:	0f 84 9e 01 00 00    	je     150d <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x1fe>
    136f:	83 f8 03             	cmp    $0x3,%eax
    1372:	0f 84 a5 00 00 00    	je     141d <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x10e>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 1)
auto resume_latter() -> task {
    1378:	0f 0b                	ud2    
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65 (discriminator 2)
}
    137a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    137e:	0f b7 40 12          	movzwl 0x12(%rax),%eax
    1382:	0f b7 c0             	movzwl %ax,%eax
    1385:	83 f8 06             	cmp    $0x6,%eax
    1388:	0f 84 6d 01 00 00    	je     14fb <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x1ec>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
    138e:	83 f8 06             	cmp    $0x6,%eax
    1391:	7f 5e                	jg     13f1 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0xe2>
    1393:	83 f8 04             	cmp    $0x4,%eax
    1396:	0f 84 e4 00 00 00    	je     1480 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x171>
    139c:	83 f8 04             	cmp    $0x4,%eax
    139f:	7f 50                	jg     13f1 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0xe2>
    13a1:	85 c0                	test   %eax,%eax
    13a3:	74 07                	je     13ac <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x9d>
    13a5:	83 f8 02             	cmp    $0x2,%eax
    13a8:	74 78                	je     1422 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x113>
    13aa:	eb 45                	jmp    13f1 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0xe2>
    13ac:	48 8b 5d d8          	mov    -0x28(%rbp),%rbx
    13b0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    13b4:	48 89 c7             	mov    %rax,%rdi
    13b7:	e8 1a 04 00 00       	callq  17d6 <std::__n4861::coroutine_handle<task::promise_type>::from_address(void*)>
    13bc:	48 89 43 18          	mov    %rax,0x18(%rbx)
    13c0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    13c4:	c6 40 20 00          	movb   $0x0,0x20(%rax)
    13c8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    13cc:	48 83 c0 10          	add    $0x10,%rax
    13d0:	48 89 c7             	mov    %rax,%rdi
    13d3:	e8 60 03 00 00       	callq  1738 <task::promise_type::initial_suspend()>
    13d8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    13dc:	48 83 c0 21          	add    $0x21,%rax
    13e0:	48 89 c7             	mov    %rax,%rdi
    13e3:	e8 84 02 00 00       	callq  166c <std::__n4861::suspend_always::await_ready() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
auto resume_latter() -> task {
    13e8:	83 f0 01             	xor    $0x1,%eax
    13eb:	84 c0                	test   %al,%al
    13ed:	75 04                	jne    13f3 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0xe4>
    13ef:	eb 31                	jmp    1422 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x113>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 5)
    13f1:	0f 0b                	ud2    
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 8)
    13f3:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    13f7:	66 c7 40 12 02 00    	movw   $0x2,0x12(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65 (discriminator 8)
}
    13fd:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1401:	48 8d 50 21          	lea    0x21(%rax),%rdx
    1405:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1409:	48 8b 40 18          	mov    0x18(%rax),%rax
    140d:	48 89 c6             	mov    %rax,%rsi
    1410:	48 89 d7             	mov    %rdx,%rdi
    1413:	e8 68 02 00 00       	callq  1680 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 8)
auto resume_latter() -> task {
    1418:	e9 0e 01 00 00       	jmpq   152b <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x21c>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
    141d:	e9 ec 00 00 00       	jmpq   150e <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x1ff>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 10)
    1422:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1426:	c6 40 20 01          	movb   $0x1,0x20(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65 (discriminator 10)
}
    142a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    142e:	48 83 c0 21          	add    $0x21,%rax
    1432:	48 89 c7             	mov    %rax,%rdi
    1435:	e8 5a 02 00 00       	callq  1694 <std::__n4861::suspend_always::await_resume() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:61 (discriminator 10)
  co_await awaitable_var;
    143a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    143e:	48 83 c0 22          	add    $0x22,%rax
    1442:	48 89 c7             	mov    %rax,%rdi
    1445:	e8 5a 02 00 00       	callq  16a4 <awaitable::await_ready()>
    144a:	83 f0 01             	xor    $0x1,%eax
    144d:	84 c0                	test   %al,%al
    144f:	74 2f                	je     1480 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x171>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:61 (discriminator 1)
    1451:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1455:	66 c7 40 12 04 00    	movw   $0x4,0x12(%rax)
    145b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    145f:	48 8d 50 22          	lea    0x22(%rax),%rdx
    1463:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1467:	48 8b 40 18          	mov    0x18(%rax),%rax
    146b:	48 89 c6             	mov    %rax,%rsi
    146e:	48 89 d7             	mov    %rdx,%rdi
    1471:	e8 42 02 00 00       	callq  16b8 <awaitable::await_suspend(std::__n4861::coroutine_handle<void>)>
    1476:	e9 b0 00 00 00       	jmpq   152b <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x21c>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:61
    147b:	e9 8e 00 00 00       	jmpq   150e <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x1ff>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:61 (discriminator 2)
    1480:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1484:	48 83 c0 22          	add    $0x22,%rax
    1488:	48 89 c7             	mov    %rax,%rdi
    148b:	e8 3c 02 00 00       	callq  16cc <awaitable::await_resume()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65 (discriminator 2)
}
    1490:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1494:	48 83 c0 10          	add    $0x10,%rax
    1498:	48 89 c7             	mov    %rax,%rdi
    149b:	e8 b8 02 00 00       	callq  1758 <task::promise_type::return_void()>
    14a0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    14a4:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
    14ab:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    14af:	48 83 c0 10          	add    $0x10,%rax
    14b3:	48 89 c7             	mov    %rax,%rdi
    14b6:	e8 8d 02 00 00       	callq  1748 <task::promise_type::final_suspend()>
    14bb:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    14bf:	48 83 c0 23          	add    $0x23,%rax
    14c3:	48 89 c7             	mov    %rax,%rdi
    14c6:	e8 a1 01 00 00       	callq  166c <std::__n4861::suspend_always::await_ready() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 2)
auto resume_latter() -> task {
    14cb:	83 f0 01             	xor    $0x1,%eax
    14ce:	84 c0                	test   %al,%al
    14d0:	74 29                	je     14fb <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x1ec>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 12)
    14d2:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    14d6:	66 c7 40 12 06 00    	movw   $0x6,0x12(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65 (discriminator 12)
}
    14dc:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    14e0:	48 8d 50 23          	lea    0x23(%rax),%rdx
    14e4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    14e8:	48 8b 40 18          	mov    0x18(%rax),%rax
    14ec:	48 89 c6             	mov    %rax,%rsi
    14ef:	48 89 d7             	mov    %rdx,%rdi
    14f2:	e8 89 01 00 00       	callq  1680 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 12)
auto resume_latter() -> task {
    14f7:	eb 32                	jmp    152b <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x21c>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
    14f9:	eb 13                	jmp    150e <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x1ff>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
}
    14fb:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    14ff:	48 83 c0 23          	add    $0x23,%rax
    1503:	48 89 c7             	mov    %rax,%rdi
    1506:	e8 89 01 00 00       	callq  1694 <std::__n4861::suspend_always::await_resume() const>
    150b:	eb 01                	jmp    150e <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x1ff>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
auto resume_latter() -> task {
    150d:	90                   	nop
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65 (discriminator 4)
}
    150e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1512:	0f b6 40 11          	movzbl 0x11(%rax),%eax
    1516:	0f b6 c0             	movzbl %al,%eax
    1519:	85 c0                	test   %eax,%eax
    151b:	74 12                	je     152f <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x220>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65 (discriminator 6)
    151d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    1521:	48 89 c7             	mov    %rax,%rdi
    1524:	e8 c7 fb ff ff       	callq  10f0 <operator delete(void*)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55 (discriminator 6)
auto resume_latter() -> task {
    1529:	eb 04                	jmp    152f <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x220>
    152b:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
    152f:	90                   	nop
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
}
    1530:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1534:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    153b:	00 00 
    153d:	74 05                	je     1544 <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)+0x235>
    153f:	e8 cc fb ff ff       	callq  1110 <__stack_chk_fail@plt>
    1544:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    1548:	c9                   	leaveq 
    1549:	c3                   	retq   

000000000000154a <_Z13resume_latterv.destroy(resume_latter()::_Z13resume_latterv.frame*)>:
_Z26_Z13resume_latterv.destroyPZ13resume_lattervE24_Z13resume_latterv.frame():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
    154a:	f3 0f 1e fa          	endbr64 
    154e:	55                   	push   %rbp
    154f:	48 89 e5             	mov    %rsp,%rbp
    1552:	48 83 ec 10          	sub    $0x10,%rsp
    1556:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:55
auto resume_latter() -> task {
    155a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    155e:	0f b7 40 12          	movzwl 0x12(%rax),%eax
    1562:	83 c8 01             	or     $0x1,%eax
    1565:	89 c2                	mov    %eax,%edx
    1567:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    156b:	66 89 50 12          	mov    %dx,0x12(%rax)
    156f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    1573:	48 89 c7             	mov    %rax,%rdi
    1576:	e8 94 fd ff ff       	callq  130f <_Z13resume_latterv.actor(resume_latter()::_Z13resume_latterv.frame*)>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:65
}
    157b:	c9                   	leaveq 
    157c:	c3                   	retq   

000000000000157d <run_coroutine()>:
_Z13run_coroutinev():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:66
void run_coroutine() {
    157d:	f3 0f 1e fa          	endbr64 
    1581:	55                   	push   %rbp
    1582:	48 89 e5             	mov    %rsp,%rbp
    1585:	48 83 ec 10          	sub    $0x10,%rsp
    1589:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    1590:	00 00 
    1592:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1596:	31 c0                	xor    %eax,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:68
  LOG_DEBUG("start call coroutine")
  auto t = resume_latter();
    1598:	e8 b7 fc ff ff       	callq  1254 <resume_latter()>
    159d:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:70
  LOG_DEBUG("start resume coroutine")
  t.h_.resume();
    15a1:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    15a5:	48 89 c7             	mov    %rax,%rdi
    15a8:	e8 9d 00 00 00       	callq  164a <std::__n4861::coroutine_handle<void>::resume() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:74
  LOG_DEBUG("end resume coroutine")
  // 不用destroy
  //  t.h_.destroy();
}
    15ad:	90                   	nop
    15ae:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    15b2:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    15b9:	00 00 
    15bb:	74 05                	je     15c2 <run_coroutine()+0x45>
    15bd:	e8 4e fb ff ff       	callq  1110 <__stack_chk_fail@plt>
    15c2:	c9                   	leaveq 
    15c3:	c3                   	retq   

00000000000015c4 <main>:
main():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:75
int main(int argc, char** argv) {
    15c4:	f3 0f 1e fa          	endbr64 
    15c8:	55                   	push   %rbp
    15c9:	48 89 e5             	mov    %rsp,%rbp
    15cc:	48 83 ec 10          	sub    $0x10,%rsp
    15d0:	89 7d fc             	mov    %edi,-0x4(%rbp)
    15d3:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:76
  run_coroutine();
    15d7:	e8 a1 ff ff ff       	callq  157d <run_coroutine()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:77
  return 0;
    15dc:	b8 00 00 00 00       	mov    $0x0,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:78
    15e1:	c9                   	leaveq 
    15e2:	c3                   	retq   

00000000000015e3 <__static_initialization_and_destruction_0(int, int)>:
_Z41__static_initialization_and_destruction_0ii():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:78
    15e3:	f3 0f 1e fa          	endbr64 
    15e7:	55                   	push   %rbp
    15e8:	48 89 e5             	mov    %rsp,%rbp
    15eb:	48 83 ec 10          	sub    $0x10,%rsp
    15ef:	89 7d fc             	mov    %edi,-0x4(%rbp)
    15f2:	89 75 f8             	mov    %esi,-0x8(%rbp)
    15f5:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
    15f9:	75 32                	jne    162d <__static_initialization_and_destruction_0(int, int)+0x4a>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:78 (discriminator 1)
    15fb:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
    1602:	75 29                	jne    162d <__static_initialization_and_destruction_0(int, int)+0x4a>
/usr/include/c++/10/iostream:74
  extern wostream wclog;	/// Linked to standard error (buffered)
#endif
  //@}

  // For construction of filebuffers for cout, cin, cerr, clog et. al.
  static ios_base::Init __ioinit;
    1604:	48 8d 3d 26 2a 00 00 	lea    0x2a26(%rip),%rdi        # 4031 <std::__ioinit>
    160b:	e8 20 fb ff ff       	callq  1130 <std::ios_base::Init::Init()@plt>
    1610:	48 8d 15 f1 29 00 00 	lea    0x29f1(%rip),%rdx        # 4008 <__dso_handle>
    1617:	48 8d 35 13 2a 00 00 	lea    0x2a13(%rip),%rsi        # 4031 <std::__ioinit>
    161e:	48 8b 05 d3 29 00 00 	mov    0x29d3(%rip),%rax        # 3ff8 <std::ios_base::Init::~Init()@GLIBCXX_3.4>
    1625:	48 89 c7             	mov    %rax,%rdi
    1628:	e8 b3 fa ff ff       	callq  10e0 <__cxa_atexit@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:78
    162d:	90                   	nop
    162e:	c9                   	leaveq 
    162f:	c3                   	retq   

0000000000001630 <_GLOBAL__sub_I_main.cpp>:
_GLOBAL__sub_I_main.cpp():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:78
    1630:	f3 0f 1e fa          	endbr64 
    1634:	55                   	push   %rbp
    1635:	48 89 e5             	mov    %rsp,%rbp
    1638:	be ff ff 00 00       	mov    $0xffff,%esi
    163d:	bf 01 00 00 00       	mov    $0x1,%edi
    1642:	e8 9c ff ff ff       	callq  15e3 <__static_initialization_and_destruction_0(int, int)>
    1647:	5d                   	pop    %rbp
    1648:	c3                   	retq   
    1649:	90                   	nop

000000000000164a <std::__n4861::coroutine_handle<void>::resume() const>:
_ZNKSt7__n486116coroutine_handleIvE6resumeEv():
/usr/include/c++/10/coroutine:126
      void resume() const { __builtin_coro_resume(_M_fr_ptr); }
    164a:	f3 0f 1e fa          	endbr64 
    164e:	55                   	push   %rbp
    164f:	48 89 e5             	mov    %rsp,%rbp
    1652:	48 83 ec 10          	sub    $0x10,%rsp
    1656:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    165a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    165e:	48 8b 00             	mov    (%rax),%rax
    1661:	48 8b 10             	mov    (%rax),%rdx
    1664:	48 89 c7             	mov    %rax,%rdi
    1667:	ff d2                	callq  *%rdx
    1669:	90                   	nop
    166a:	c9                   	leaveq 
    166b:	c3                   	retq   

000000000000166c <std::__n4861::suspend_always::await_ready() const>:
_ZNKSt7__n486114suspend_always11await_readyEv():
/usr/include/c++/10/coroutine:276

  // 17.12.5 Trivial awaitables
  /// [coroutine.trivial.awaitables]
  struct suspend_always
  {
    constexpr bool await_ready() const noexcept { return false; }
    166c:	f3 0f 1e fa          	endbr64 
    1670:	55                   	push   %rbp
    1671:	48 89 e5             	mov    %rsp,%rbp
    1674:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1678:	b8 00 00 00 00       	mov    $0x0,%eax
    167d:	5d                   	pop    %rbp
    167e:	c3                   	retq   
    167f:	90                   	nop

0000000000001680 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>:
_ZNKSt7__n486114suspend_always13await_suspendENS_16coroutine_handleIvEE():
/usr/include/c++/10/coroutine:278

    constexpr void await_suspend(coroutine_handle<>) const noexcept {}
    1680:	f3 0f 1e fa          	endbr64 
    1684:	55                   	push   %rbp
    1685:	48 89 e5             	mov    %rsp,%rbp
    1688:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    168c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1690:	90                   	nop
    1691:	5d                   	pop    %rbp
    1692:	c3                   	retq   
    1693:	90                   	nop

0000000000001694 <std::__n4861::suspend_always::await_resume() const>:
_ZNKSt7__n486114suspend_always12await_resumeEv():
/usr/include/c++/10/coroutine:280

    constexpr void await_resume() const noexcept {}
    1694:	f3 0f 1e fa          	endbr64 
    1698:	55                   	push   %rbp
    1699:	48 89 e5             	mov    %rsp,%rbp
    169c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    16a0:	90                   	nop
    16a1:	5d                   	pop    %rbp
    16a2:	c3                   	retq   
    16a3:	90                   	nop

00000000000016a4 <awaitable::await_ready()>:
_ZN9awaitable11await_readyEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:17
  bool await_ready() {
    16a4:	f3 0f 1e fa          	endbr64 
    16a8:	55                   	push   %rbp
    16a9:	48 89 e5             	mov    %rsp,%rbp
    16ac:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:19
    return false;
    16b0:	b8 00 00 00 00       	mov    $0x0,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:20
  }
    16b5:	5d                   	pop    %rbp
    16b6:	c3                   	retq   
    16b7:	90                   	nop

00000000000016b8 <awaitable::await_suspend(std::__n4861::coroutine_handle<void>)>:
_ZN9awaitable13await_suspendENSt7__n486116coroutine_handleIvEE():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:21
  void await_suspend(std::coroutine_handle<> h) {
    16b8:	f3 0f 1e fa          	endbr64 
    16bc:	55                   	push   %rbp
    16bd:	48 89 e5             	mov    %rsp,%rbp
    16c0:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    16c4:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:23
  }
    16c8:	90                   	nop
    16c9:	5d                   	pop    %rbp
    16ca:	c3                   	retq   
    16cb:	90                   	nop

00000000000016cc <awaitable::await_resume()>:
_ZN9awaitable12await_resumeEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:24
  void await_resume() {
    16cc:	f3 0f 1e fa          	endbr64 
    16d0:	55                   	push   %rbp
    16d1:	48 89 e5             	mov    %rsp,%rbp
    16d4:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:26
  }
    16d8:	90                   	nop
    16d9:	5d                   	pop    %rbp
    16da:	c3                   	retq   
    16db:	90                   	nop

00000000000016dc <task::promise_type::get_return_object()>:
_ZN4task12promise_type17get_return_objectEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:33
    task get_return_object() {
    16dc:	f3 0f 1e fa          	endbr64 
    16e0:	55                   	push   %rbp
    16e1:	48 89 e5             	mov    %rsp,%rbp
    16e4:	48 83 ec 30          	sub    $0x30,%rsp
    16e8:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    16ec:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    16f3:	00 00 
    16f5:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    16f9:	31 c0                	xor    %eax,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:35
      return handle_type::from_promise(*this);
    16fb:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    16ff:	48 89 c7             	mov    %rax,%rdi
    1702:	e8 82 00 00 00       	callq  1789 <std::__n4861::coroutine_handle<task::promise_type>::from_promise(task::promise_type&)>
    1707:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    170b:	48 8d 55 e8          	lea    -0x18(%rbp),%rdx
    170f:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    1713:	48 89 d6             	mov    %rdx,%rsi
    1716:	48 89 c7             	mov    %rax,%rdi
    1719:	e8 4a 00 00 00       	callq  1768 <task::task(std::__n4861::coroutine_handle<task::promise_type> const&)>
    171e:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:36
    }
    1722:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
    1726:	64 48 2b 0c 25 28 00 	sub    %fs:0x28,%rcx
    172d:	00 00 
    172f:	74 05                	je     1736 <task::promise_type::get_return_object()+0x5a>
    1731:	e8 da f9 ff ff       	callq  1110 <__stack_chk_fail@plt>
    1736:	c9                   	leaveq 
    1737:	c3                   	retq   

0000000000001738 <task::promise_type::initial_suspend()>:
_ZN4task12promise_type15initial_suspendEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:37
    std::suspend_always initial_suspend() {
    1738:	f3 0f 1e fa          	endbr64 
    173c:	55                   	push   %rbp
    173d:	48 89 e5             	mov    %rsp,%rbp
    1740:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:39
      return {};
    1744:	90                   	nop
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:40
    }
    1745:	5d                   	pop    %rbp
    1746:	c3                   	retq   
    1747:	90                   	nop

0000000000001748 <task::promise_type::final_suspend()>:
_ZN4task12promise_type13final_suspendEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:41
    std::suspend_always final_suspend() noexcept {
    1748:	f3 0f 1e fa          	endbr64 
    174c:	55                   	push   %rbp
    174d:	48 89 e5             	mov    %rsp,%rbp
    1750:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:43
      return {};
    1754:	90                   	nop
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:44
    }
    1755:	5d                   	pop    %rbp
    1756:	c3                   	retq   
    1757:	90                   	nop

0000000000001758 <task::promise_type::return_void()>:
_ZN4task12promise_type11return_voidEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:49
    void return_void() { LOG_DEBUG("call : " << __PRETTY_FUNCTION__) }
    1758:	f3 0f 1e fa          	endbr64 
    175c:	55                   	push   %rbp
    175d:	48 89 e5             	mov    %rsp,%rbp
    1760:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1764:	90                   	nop
    1765:	5d                   	pop    %rbp
    1766:	c3                   	retq   
    1767:	90                   	nop

0000000000001768 <task::task(std::__n4861::coroutine_handle<task::promise_type> const&)>:
_ZN4taskC2ERKNSt7__n486116coroutine_handleINS_12promise_typeEEE():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_4/main.cpp:52
  task(const handle_type& h) : h_(h) {}
    1768:	f3 0f 1e fa          	endbr64 
    176c:	55                   	push   %rbp
    176d:	48 89 e5             	mov    %rsp,%rbp
    1770:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    1774:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    1778:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    177c:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
    1780:	48 8b 12             	mov    (%rdx),%rdx
    1783:	48 89 10             	mov    %rdx,(%rax)
    1786:	90                   	nop
    1787:	5d                   	pop    %rbp
    1788:	c3                   	retq   

0000000000001789 <std::__n4861::coroutine_handle<task::promise_type>::from_promise(task::promise_type&)>:
_ZNSt7__n486116coroutine_handleIN4task12promise_typeEE12from_promiseERS2_():
/usr/include/c++/10/coroutine:185
      static coroutine_handle from_promise(_Promise& p)
    1789:	f3 0f 1e fa          	endbr64 
    178d:	55                   	push   %rbp
    178e:	48 89 e5             	mov    %rsp,%rbp
    1791:	48 83 ec 20          	sub    $0x20,%rsp
    1795:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    1799:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    17a0:	00 00 
    17a2:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    17a6:	31 c0                	xor    %eax,%eax
/usr/include/c++/10/coroutine:187
	coroutine_handle __self;
    17a8:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
    17af:	00 
/usr/include/c++/10/coroutine:189
	  = __builtin_coro_promise((char*) &p, __alignof(_Promise), true);
    17b0:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    17b4:	48 83 e8 10          	sub    $0x10,%rax
    17b8:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
/usr/include/c++/10/coroutine:190
	return __self;
    17bc:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
/usr/include/c++/10/coroutine:191
      }
    17c0:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    17c4:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    17cb:	00 00 
    17cd:	74 05                	je     17d4 <std::__n4861::coroutine_handle<task::promise_type>::from_promise(task::promise_type&)+0x4b>
    17cf:	e8 3c f9 ff ff       	callq  1110 <__stack_chk_fail@plt>
    17d4:	c9                   	leaveq 
    17d5:	c3                   	retq   

00000000000017d6 <std::__n4861::coroutine_handle<task::promise_type>::from_address(void*)>:
_ZNSt7__n486116coroutine_handleIN4task12promise_typeEE12from_addressEPv():
/usr/include/c++/10/coroutine:200
    constexpr static coroutine_handle from_address(void* __a) noexcept
    17d6:	f3 0f 1e fa          	endbr64 
    17da:	55                   	push   %rbp
    17db:	48 89 e5             	mov    %rsp,%rbp
    17de:	48 83 ec 20          	sub    $0x20,%rsp
    17e2:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    17e6:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    17ed:	00 00 
    17ef:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    17f3:	31 c0                	xor    %eax,%eax
/usr/include/c++/10/coroutine:202
      coroutine_handle __self;
    17f5:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
    17fc:	00 
/usr/include/c++/10/coroutine:203
      __self._M_fr_ptr = __a;
    17fd:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    1801:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
/usr/include/c++/10/coroutine:204
      return __self;
    1805:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
/usr/include/c++/10/coroutine:205
    }
    1809:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    180d:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    1814:	00 00 
    1816:	74 05                	je     181d <std::__n4861::coroutine_handle<task::promise_type>::from_address(void*)+0x47>
    1818:	e8 f3 f8 ff ff       	callq  1110 <__stack_chk_fail@plt>
    181d:	c9                   	leaveq 
    181e:	c3                   	retq   
    181f:	90                   	nop

0000000000001820 <__libc_csu_init>:
__libc_csu_init():
    1820:	f3 0f 1e fa          	endbr64 
    1824:	41 57                	push   %r15
    1826:	4c 8d 3d 0b 25 00 00 	lea    0x250b(%rip),%r15        # 3d38 <__frame_dummy_init_array_entry>
    182d:	41 56                	push   %r14
    182f:	49 89 d6             	mov    %rdx,%r14
    1832:	41 55                	push   %r13
    1834:	49 89 f5             	mov    %rsi,%r13
    1837:	41 54                	push   %r12
    1839:	41 89 fc             	mov    %edi,%r12d
    183c:	55                   	push   %rbp
    183d:	48 8d 2d 04 25 00 00 	lea    0x2504(%rip),%rbp        # 3d48 <__do_global_dtors_aux_fini_array_entry>
    1844:	53                   	push   %rbx
    1845:	4c 29 fd             	sub    %r15,%rbp
    1848:	48 83 ec 08          	sub    $0x8,%rsp
    184c:	e8 af f7 ff ff       	callq  1000 <_init>
    1851:	48 c1 fd 03          	sar    $0x3,%rbp
    1855:	74 1f                	je     1876 <__libc_csu_init+0x56>
    1857:	31 db                	xor    %ebx,%ebx
    1859:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1860:	4c 89 f2             	mov    %r14,%rdx
    1863:	4c 89 ee             	mov    %r13,%rsi
    1866:	44 89 e7             	mov    %r12d,%edi
    1869:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    186d:	48 83 c3 01          	add    $0x1,%rbx
    1871:	48 39 dd             	cmp    %rbx,%rbp
    1874:	75 ea                	jne    1860 <__libc_csu_init+0x40>
    1876:	48 83 c4 08          	add    $0x8,%rsp
    187a:	5b                   	pop    %rbx
    187b:	5d                   	pop    %rbp
    187c:	41 5c                	pop    %r12
    187e:	41 5d                	pop    %r13
    1880:	41 5e                	pop    %r14
    1882:	41 5f                	pop    %r15
    1884:	c3                   	retq   
    1885:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    188c:	00 00 00 00 

0000000000001890 <__libc_csu_fini>:
__libc_csu_fini():
    1890:	f3 0f 1e fa          	endbr64 
    1894:	c3                   	retq   

Disassembly of section .fini:

0000000000001898 <_fini>:
_fini():
    1898:	f3 0f 1e fa          	endbr64 
    189c:	48 83 ec 08          	sub    $0x8,%rsp
    18a0:	48 83 c4 08          	add    $0x8,%rsp
    18a4:	c3                   	retq   
