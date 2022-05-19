
co_samples_sample_2:     file format elf64-x86-64


Disassembly of section .init:

0000000000002000 <_init>:
    2000:	f3 0f 1e fa          	endbr64 
    2004:	48 83 ec 08          	sub    $0x8,%rsp
    2008:	48 8b 05 c9 3f 00 00 	mov    0x3fc9(%rip),%rax        # 5fd8 <__gmon_start__>
    200f:	48 85 c0             	test   %rax,%rax
    2012:	74 02                	je     2016 <_init+0x16>
    2014:	ff d0                	callq  *%rax
    2016:	48 83 c4 08          	add    $0x8,%rsp
    201a:	c3                   	retq   

Disassembly of section .plt:

0000000000002020 <.plt>:
    2020:	ff 35 c2 3e 00 00    	pushq  0x3ec2(%rip)        # 5ee8 <_GLOBAL_OFFSET_TABLE_+0x8>
    2026:	f2 ff 25 c3 3e 00 00 	bnd jmpq *0x3ec3(%rip)        # 5ef0 <_GLOBAL_OFFSET_TABLE_+0x10>
    202d:	0f 1f 00             	nopl   (%rax)
    2030:	f3 0f 1e fa          	endbr64 
    2034:	68 00 00 00 00       	pushq  $0x0
    2039:	f2 e9 e1 ff ff ff    	bnd jmpq 2020 <.plt>
    203f:	90                   	nop
    2040:	f3 0f 1e fa          	endbr64 
    2044:	68 01 00 00 00       	pushq  $0x1
    2049:	f2 e9 d1 ff ff ff    	bnd jmpq 2020 <.plt>
    204f:	90                   	nop
    2050:	f3 0f 1e fa          	endbr64 
    2054:	68 02 00 00 00       	pushq  $0x2
    2059:	f2 e9 c1 ff ff ff    	bnd jmpq 2020 <.plt>
    205f:	90                   	nop
    2060:	f3 0f 1e fa          	endbr64 
    2064:	68 03 00 00 00       	pushq  $0x3
    2069:	f2 e9 b1 ff ff ff    	bnd jmpq 2020 <.plt>
    206f:	90                   	nop
    2070:	f3 0f 1e fa          	endbr64 
    2074:	68 04 00 00 00       	pushq  $0x4
    2079:	f2 e9 a1 ff ff ff    	bnd jmpq 2020 <.plt>
    207f:	90                   	nop
    2080:	f3 0f 1e fa          	endbr64 
    2084:	68 05 00 00 00       	pushq  $0x5
    2089:	f2 e9 91 ff ff ff    	bnd jmpq 2020 <.plt>
    208f:	90                   	nop
    2090:	f3 0f 1e fa          	endbr64 
    2094:	68 06 00 00 00       	pushq  $0x6
    2099:	f2 e9 81 ff ff ff    	bnd jmpq 2020 <.plt>
    209f:	90                   	nop
    20a0:	f3 0f 1e fa          	endbr64 
    20a4:	68 07 00 00 00       	pushq  $0x7
    20a9:	f2 e9 71 ff ff ff    	bnd jmpq 2020 <.plt>
    20af:	90                   	nop
    20b0:	f3 0f 1e fa          	endbr64 
    20b4:	68 08 00 00 00       	pushq  $0x8
    20b9:	f2 e9 61 ff ff ff    	bnd jmpq 2020 <.plt>
    20bf:	90                   	nop
    20c0:	f3 0f 1e fa          	endbr64 
    20c4:	68 09 00 00 00       	pushq  $0x9
    20c9:	f2 e9 51 ff ff ff    	bnd jmpq 2020 <.plt>
    20cf:	90                   	nop
    20d0:	f3 0f 1e fa          	endbr64 
    20d4:	68 0a 00 00 00       	pushq  $0xa
    20d9:	f2 e9 41 ff ff ff    	bnd jmpq 2020 <.plt>
    20df:	90                   	nop
    20e0:	f3 0f 1e fa          	endbr64 
    20e4:	68 0b 00 00 00       	pushq  $0xb
    20e9:	f2 e9 31 ff ff ff    	bnd jmpq 2020 <.plt>
    20ef:	90                   	nop
    20f0:	f3 0f 1e fa          	endbr64 
    20f4:	68 0c 00 00 00       	pushq  $0xc
    20f9:	f2 e9 21 ff ff ff    	bnd jmpq 2020 <.plt>
    20ff:	90                   	nop
    2100:	f3 0f 1e fa          	endbr64 
    2104:	68 0d 00 00 00       	pushq  $0xd
    2109:	f2 e9 11 ff ff ff    	bnd jmpq 2020 <.plt>
    210f:	90                   	nop
    2110:	f3 0f 1e fa          	endbr64 
    2114:	68 0e 00 00 00       	pushq  $0xe
    2119:	f2 e9 01 ff ff ff    	bnd jmpq 2020 <.plt>
    211f:	90                   	nop
    2120:	f3 0f 1e fa          	endbr64 
    2124:	68 0f 00 00 00       	pushq  $0xf
    2129:	f2 e9 f1 fe ff ff    	bnd jmpq 2020 <.plt>
    212f:	90                   	nop
    2130:	f3 0f 1e fa          	endbr64 
    2134:	68 10 00 00 00       	pushq  $0x10
    2139:	f2 e9 e1 fe ff ff    	bnd jmpq 2020 <.plt>
    213f:	90                   	nop
    2140:	f3 0f 1e fa          	endbr64 
    2144:	68 11 00 00 00       	pushq  $0x11
    2149:	f2 e9 d1 fe ff ff    	bnd jmpq 2020 <.plt>
    214f:	90                   	nop
    2150:	f3 0f 1e fa          	endbr64 
    2154:	68 12 00 00 00       	pushq  $0x12
    2159:	f2 e9 c1 fe ff ff    	bnd jmpq 2020 <.plt>
    215f:	90                   	nop
    2160:	f3 0f 1e fa          	endbr64 
    2164:	68 13 00 00 00       	pushq  $0x13
    2169:	f2 e9 b1 fe ff ff    	bnd jmpq 2020 <.plt>
    216f:	90                   	nop
    2170:	f3 0f 1e fa          	endbr64 
    2174:	68 14 00 00 00       	pushq  $0x14
    2179:	f2 e9 a1 fe ff ff    	bnd jmpq 2020 <.plt>
    217f:	90                   	nop
    2180:	f3 0f 1e fa          	endbr64 
    2184:	68 15 00 00 00       	pushq  $0x15
    2189:	f2 e9 91 fe ff ff    	bnd jmpq 2020 <.plt>
    218f:	90                   	nop
    2190:	f3 0f 1e fa          	endbr64 
    2194:	68 16 00 00 00       	pushq  $0x16
    2199:	f2 e9 81 fe ff ff    	bnd jmpq 2020 <.plt>
    219f:	90                   	nop

Disassembly of section .plt.got:

00000000000021a0 <__cxa_finalize@plt>:
    21a0:	f3 0f 1e fa          	endbr64 
    21a4:	f2 ff 25 05 3e 00 00 	bnd jmpq *0x3e05(%rip)        # 5fb0 <__cxa_finalize@GLIBC_2.2.5>
    21ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

00000000000021b0 <_ZNSolsEm@plt>:
    21b0:	f3 0f 1e fa          	endbr64 
    21b4:	f2 ff 25 3d 3d 00 00 	bnd jmpq *0x3d3d(%rip)        # 5ef8 <_ZNSolsEm@GLIBCXX_3.4>
    21bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000021c0 <_ZNSt15__exception_ptr13exception_ptr4swapERS0_@plt>:
    21c0:	f3 0f 1e fa          	endbr64 
    21c4:	f2 ff 25 35 3d 00 00 	bnd jmpq *0x3d35(%rip)        # 5f00 <_ZNSt15__exception_ptr13exception_ptr4swapERS0_@CXXABI_1.3.3>
    21cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000021d0 <_ZNSt15__exception_ptr13exception_ptrC1ERKS0_@plt>:
    21d0:	f3 0f 1e fa          	endbr64 
    21d4:	f2 ff 25 2d 3d 00 00 	bnd jmpq *0x3d2d(%rip)        # 5f08 <_ZNSt15__exception_ptr13exception_ptrC1ERKS0_@CXXABI_1.3.3>
    21db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000021e0 <_ZNSt15__exception_ptr13exception_ptrC1Ev@plt>:
    21e0:	f3 0f 1e fa          	endbr64 
    21e4:	f2 ff 25 25 3d 00 00 	bnd jmpq *0x3d25(%rip)        # 5f10 <_ZNSt15__exception_ptr13exception_ptrC1Ev@CXXABI_1.3.3>
    21eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000021f0 <_ZNSt13runtime_errorC1EPKc@plt>:
    21f0:	f3 0f 1e fa          	endbr64 
    21f4:	f2 ff 25 1d 3d 00 00 	bnd jmpq *0x3d1d(%rip)        # 5f18 <_ZNSt13runtime_errorC1EPKc@GLIBCXX_3.4.21>
    21fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002200 <__cxa_begin_catch@plt>:
    2200:	f3 0f 1e fa          	endbr64 
    2204:	f2 ff 25 15 3d 00 00 	bnd jmpq *0x3d15(%rip)        # 5f20 <__cxa_begin_catch@CXXABI_1.3>
    220b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002210 <__cxa_allocate_exception@plt>:
    2210:	f3 0f 1e fa          	endbr64 
    2214:	f2 ff 25 0d 3d 00 00 	bnd jmpq *0x3d0d(%rip)        # 5f28 <__cxa_allocate_exception@CXXABI_1.3>
    221b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002220 <__cxa_free_exception@plt>:
    2220:	f3 0f 1e fa          	endbr64 
    2224:	f2 ff 25 05 3d 00 00 	bnd jmpq *0x3d05(%rip)        # 5f30 <__cxa_free_exception@CXXABI_1.3>
    222b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002230 <__cxa_atexit@plt>:
    2230:	f3 0f 1e fa          	endbr64 
    2234:	f2 ff 25 fd 3c 00 00 	bnd jmpq *0x3cfd(%rip)        # 5f38 <__cxa_atexit@GLIBC_2.2.5>
    223b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002240 <_ZdlPv@plt>:
    2240:	f3 0f 1e fa          	endbr64 
    2244:	f2 ff 25 f5 3c 00 00 	bnd jmpq *0x3cf5(%rip)        # 5f40 <_ZdlPv@GLIBCXX_3.4>
    224b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002250 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>:
    2250:	f3 0f 1e fa          	endbr64 
    2254:	f2 ff 25 ed 3c 00 00 	bnd jmpq *0x3ced(%rip)        # 5f48 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@GLIBCXX_3.4>
    225b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002260 <_Znwm@plt>:
    2260:	f3 0f 1e fa          	endbr64 
    2264:	f2 ff 25 e5 3c 00 00 	bnd jmpq *0x3ce5(%rip)        # 5f50 <_Znwm@GLIBCXX_3.4>
    226b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002270 <_ZSt17rethrow_exceptionNSt15__exception_ptr13exception_ptrE@plt>:
    2270:	f3 0f 1e fa          	endbr64 
    2274:	f2 ff 25 dd 3c 00 00 	bnd jmpq *0x3cdd(%rip)        # 5f58 <_ZSt17rethrow_exceptionNSt15__exception_ptr13exception_ptrE@CXXABI_1.3.3>
    227b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002280 <_ZSt17current_exceptionv@plt>:
    2280:	f3 0f 1e fa          	endbr64 
    2284:	f2 ff 25 d5 3c 00 00 	bnd jmpq *0x3cd5(%rip)        # 5f60 <_ZSt17current_exceptionv@CXXABI_1.3.3>
    228b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002290 <__stack_chk_fail@plt>:
    2290:	f3 0f 1e fa          	endbr64 
    2294:	f2 ff 25 cd 3c 00 00 	bnd jmpq *0x3ccd(%rip)        # 5f68 <__stack_chk_fail@GLIBC_2.4>
    229b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022a0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@plt>:
    22a0:	f3 0f 1e fa          	endbr64 
    22a4:	f2 ff 25 c5 3c 00 00 	bnd jmpq *0x3cc5(%rip)        # 5f70 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@GLIBCXX_3.4>
    22ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022b0 <__cxa_rethrow@plt>:
    22b0:	f3 0f 1e fa          	endbr64 
    22b4:	f2 ff 25 bd 3c 00 00 	bnd jmpq *0x3cbd(%rip)        # 5f78 <__cxa_rethrow@CXXABI_1.3>
    22bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022c0 <_ZNSt8ios_base4InitC1Ev@plt>:
    22c0:	f3 0f 1e fa          	endbr64 
    22c4:	f2 ff 25 b5 3c 00 00 	bnd jmpq *0x3cb5(%rip)        # 5f80 <_ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4>
    22cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022d0 <__cxa_end_catch@plt>:
    22d0:	f3 0f 1e fa          	endbr64 
    22d4:	f2 ff 25 ad 3c 00 00 	bnd jmpq *0x3cad(%rip)        # 5f88 <__cxa_end_catch@CXXABI_1.3>
    22db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022e0 <__cxa_throw@plt>:
    22e0:	f3 0f 1e fa          	endbr64 
    22e4:	f2 ff 25 a5 3c 00 00 	bnd jmpq *0x3ca5(%rip)        # 5f90 <__cxa_throw@CXXABI_1.3>
    22eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022f0 <_ZNSolsEi@plt>:
    22f0:	f3 0f 1e fa          	endbr64 
    22f4:	f2 ff 25 9d 3c 00 00 	bnd jmpq *0x3c9d(%rip)        # 5f98 <_ZNSolsEi@GLIBCXX_3.4>
    22fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002300 <_Unwind_Resume@plt>:
    2300:	f3 0f 1e fa          	endbr64 
    2304:	f2 ff 25 95 3c 00 00 	bnd jmpq *0x3c95(%rip)        # 5fa0 <_Unwind_Resume@GCC_3.0>
    230b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002310 <_ZNSt15__exception_ptr13exception_ptrD1Ev@plt>:
    2310:	f3 0f 1e fa          	endbr64 
    2314:	f2 ff 25 8d 3c 00 00 	bnd jmpq *0x3c8d(%rip)        # 5fa8 <_ZNSt15__exception_ptr13exception_ptrD1Ev@CXXABI_1.3.3>
    231b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000002320 <_start>:
    2320:	f3 0f 1e fa          	endbr64 
    2324:	31 ed                	xor    %ebp,%ebp
    2326:	49 89 d1             	mov    %rdx,%r9
    2329:	5e                   	pop    %rsi
    232a:	48 89 e2             	mov    %rsp,%rdx
    232d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    2331:	50                   	push   %rax
    2332:	54                   	push   %rsp
    2333:	4c 8d 05 56 0f 00 00 	lea    0xf56(%rip),%r8        # 3290 <__libc_csu_fini>
    233a:	48 8d 0d df 0e 00 00 	lea    0xedf(%rip),%rcx        # 3220 <__libc_csu_init>
    2341:	48 8d 3d 17 09 00 00 	lea    0x917(%rip),%rdi        # 2c5f <main>
    2348:	ff 15 82 3c 00 00    	callq  *0x3c82(%rip)        # 5fd0 <__libc_start_main@GLIBC_2.2.5>
    234e:	f4                   	hlt    
    234f:	90                   	nop

0000000000002350 <deregister_tm_clones>:
    2350:	48 8d 3d e1 3c 00 00 	lea    0x3ce1(%rip),%rdi        # 6038 <__TMC_END__>
    2357:	48 8d 05 da 3c 00 00 	lea    0x3cda(%rip),%rax        # 6038 <__TMC_END__>
    235e:	48 39 f8             	cmp    %rdi,%rax
    2361:	74 15                	je     2378 <deregister_tm_clones+0x28>
    2363:	48 8b 05 5e 3c 00 00 	mov    0x3c5e(%rip),%rax        # 5fc8 <_ITM_deregisterTMCloneTable>
    236a:	48 85 c0             	test   %rax,%rax
    236d:	74 09                	je     2378 <deregister_tm_clones+0x28>
    236f:	ff e0                	jmpq   *%rax
    2371:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    2378:	c3                   	retq   
    2379:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000002380 <register_tm_clones>:
    2380:	48 8d 3d b1 3c 00 00 	lea    0x3cb1(%rip),%rdi        # 6038 <__TMC_END__>
    2387:	48 8d 35 aa 3c 00 00 	lea    0x3caa(%rip),%rsi        # 6038 <__TMC_END__>
    238e:	48 29 fe             	sub    %rdi,%rsi
    2391:	48 89 f0             	mov    %rsi,%rax
    2394:	48 c1 ee 3f          	shr    $0x3f,%rsi
    2398:	48 c1 f8 03          	sar    $0x3,%rax
    239c:	48 01 c6             	add    %rax,%rsi
    239f:	48 d1 fe             	sar    %rsi
    23a2:	74 14                	je     23b8 <register_tm_clones+0x38>
    23a4:	48 8b 05 35 3c 00 00 	mov    0x3c35(%rip),%rax        # 5fe0 <_ITM_registerTMCloneTable>
    23ab:	48 85 c0             	test   %rax,%rax
    23ae:	74 08                	je     23b8 <register_tm_clones+0x38>
    23b0:	ff e0                	jmpq   *%rax
    23b2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    23b8:	c3                   	retq   
    23b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000023c0 <__do_global_dtors_aux>:
    23c0:	f3 0f 1e fa          	endbr64 
    23c4:	80 3d 6d 3c 00 00 00 	cmpb   $0x0,0x3c6d(%rip)        # 6038 <__TMC_END__>
    23cb:	75 2b                	jne    23f8 <__do_global_dtors_aux+0x38>
    23cd:	55                   	push   %rbp
    23ce:	48 83 3d da 3b 00 00 	cmpq   $0x0,0x3bda(%rip)        # 5fb0 <__cxa_finalize@GLIBC_2.2.5>
    23d5:	00 
    23d6:	48 89 e5             	mov    %rsp,%rbp
    23d9:	74 0c                	je     23e7 <__do_global_dtors_aux+0x27>
    23db:	48 8b 3d 26 3c 00 00 	mov    0x3c26(%rip),%rdi        # 6008 <__dso_handle>
    23e2:	e8 b9 fd ff ff       	callq  21a0 <__cxa_finalize@plt>
    23e7:	e8 64 ff ff ff       	callq  2350 <deregister_tm_clones>
    23ec:	c6 05 45 3c 00 00 01 	movb   $0x1,0x3c45(%rip)        # 6038 <__TMC_END__>
    23f3:	5d                   	pop    %rbp
    23f4:	c3                   	retq   
    23f5:	0f 1f 00             	nopl   (%rax)
    23f8:	c3                   	retq   
    23f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000002400 <frame_dummy>:
    2400:	f3 0f 1e fa          	endbr64 
    2404:	e9 77 ff ff ff       	jmpq   2380 <register_tm_clones>

0000000000002409 <_ZNSt7__n486122__dummy_resume_destroyEv>:
    2409:	f3 0f 1e fa          	endbr64 
    240d:	55                   	push   %rbp
    240e:	48 89 e5             	mov    %rsp,%rbp
    2411:	90                   	nop
    2412:	5d                   	pop    %rbp
    2413:	c3                   	retq   


0000000000002414 <_Z18fibonacci_sequencej>:
    2414:	f3 0f 1e fa          	endbr64
    2418:	55                   	push   %rbp
    2419:	48 89 e5             	mov    %rsp,%rbp
    241c:	53                   	push   %rbx
    241d:	48 83 ec 38          	sub    $0x38,%rsp
    2421:	48 89 7d c8          	mov    %rdi,-0x38(%rbp)     # 传入的参数 1
    2425:	89 75 c4             	mov    %esi,-0x3c(%rbp)     # 传入的参数 2
    2428:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    242f:	00 00
    2431:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    2435:	31 c0                	xor    %eax,%eax
    2437:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
    243e:	00
    243f:	c6 45 df 00          	movb   $0x0,-0x21(%rbp)
    2443:	c6 45 de 00          	movb   $0x0,-0x22(%rbp)
    2447:	b8 70 00 00 00       	mov    $0x70,%eax
    244c:	48 89 c7             	mov    %rax,%rdi
    244f:	e8 0c fe ff ff       	callq  2260 <_Znwm@plt>
    2454:	48 89 45 e0          	mov    %rax,-0x20(%rbp)         # 协程数据的指针, 存在栈上
    2458:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    245c:	c6 40 20 01          	movb   $0x1,0x20(%rax)
    2460:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2464:	48 8d 15 ee 00 00 00 	lea    0xee(%rip),%rdx        # 2559 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame>
                                                                    # _Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)
                                                                    # 函数 _Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame 的地址
    246b:	48 89 10             	mov    %rdx,(%rax)              # 在协程帧中写入 这个函数地址 +0 的位置
    246e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2472:	48 8d 15 f1 05 00 00 	lea    0x5f1(%rip),%rdx        # 2a6a <_Z31_Z18fibonacci_sequencej.destroyPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame>

                                                                    # _Z18fibonacci_sequencej.destroy(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)
                                                                    # 协程数据 destroy 的函数地址
    2479:	48 89 50 08          	mov    %rdx,0x8(%rax)           # 写入这个函数地址到 协程帧的 +8 位置上
    247d:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2481:	8b 55 c4             	mov    -0x3c(%rbp),%edx
    2484:	89 50 30             	mov    %edx,0x30(%rax)           # 把传入的参数写入到协程帧上 +0x30的偏移上
    2487:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    248b:	8b 40 30             	mov    0x30(%rax),%eax              # 在读取到 eax中
    248e:	89 c2                	mov    %eax,%edx                    # 放在 edx中
    2490:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2494:	48 89 50 10          	mov    %rdx,0x10(%rax)              # 再次写入到协程栈帧 +0x10的位置上
    2498:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    249c:	48 83 c0 18          	add    $0x18,%rax                   # rax + 0x18 偏移 指向 exception_ptr exception_
    24a0:	48 89 c7             	mov    %rax,%rdi
    24a3:	e8 38 fd ff ff       	callq  21e0 <_ZNSt15__exception_ptr13exception_ptrC1Ev@plt>     # std::__exception_ptr::exception_ptr::exception_ptr() 构造
    24a8:	c6 45 df 01          	movb   $0x1,-0x21(%rbp)
    24ac:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    24b0:	48 8d 50 10          	lea    0x10(%rax),%rdx
    24b4:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    24b8:	48 89 d6             	mov    %rdx,%rsi
    24bb:	48 89 c7             	mov    %rax,%rdi
    24be:	e8 cb 0a 00 00       	callq  2f8e <_ZN9GeneratorImE12promise_type17get_return_objectEv>   # Generator<unsigned long>::promise_type::get_return_object()
    24c3:	c6 45 de 01          	movb   $0x1,-0x22(%rbp)
    24c7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    24cb:	66 c7 40 22 00 00    	movw   $0x0,0x22(%rax)
    24d1:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    24d5:	48 89 c7             	mov    %rax,%rdi
    24d8:	e8 7c 00 00 00       	callq  2559 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame> #_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)
    24dd:	eb 5c                	jmp    253b <_Z18fibonacci_sequencej+0x127>     # fibonacci_sequence(unsigned int) + 0x127 = 253B
    24df:	f3 0f 1e fa          	endbr64
    24e3:	48 89 c7             	mov    %rax,%rdi
    24e6:	e8 15 fd ff ff       	callq  2200 <__cxa_begin_catch@plt>
    24eb:	80 7d de 00          	cmpb   $0x0,-0x22(%rbp)
    24ef:	74 0c                	je     24fd <_Z18fibonacci_sequencej+0xe9>
    24f1:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    24f5:	48 89 c7             	mov    %rax,%rdi
    24f8:	e8 c9 0a 00 00       	callq  2fc6 <_ZN9GeneratorImED1Ev>
    24fd:	80 7d df 00          	cmpb   $0x0,-0x21(%rbp)
    2501:	74 10                	je     2513 <_Z18fibonacci_sequencej+0xff>
    2503:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2507:	48 83 c0 10          	add    $0x10,%rax
    250b:	48 89 c7             	mov    %rax,%rdi
    250e:	e8 45 09 00 00       	callq  2e58 <_ZN9GeneratorImE12promise_typeD1Ev>
    2513:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2517:	48 89 c7             	mov    %rax,%rdi
    251a:	e8 21 fd ff ff       	callq  2240 <_ZdlPv@plt>
    251f:	e8 8c fd ff ff       	callq  22b0 <__cxa_rethrow@plt>
    2524:	f3 0f 1e fa          	endbr64
    2528:	48 89 c3             	mov    %rax,%rbx
    252b:	e8 a0 fd ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2530:	48 89 d8             	mov    %rbx,%rax
    2533:	48 89 c7             	mov    %rax,%rdi
    2536:	e8 c5 fd ff ff       	callq  2300 <_Unwind_Resume@plt>
    253b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    253f:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    2546:	00 00
    2548:	74 05                	je     254f <_Z18fibonacci_sequencej+0x13b>
    254a:	e8 41 fd ff ff       	callq  2290 <__stack_chk_fail@plt>
    254f:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    2553:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    2557:	c9                   	leaveq
    2558:	c3                   	retq

0000000000002559 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame>:    # _Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)
    2559:	f3 0f 1e fa          	endbr64
    255d:	55                   	push   %rbp
    255e:	48 89 e5             	mov    %rsp,%rbp
    2561:	41 54                	push   %r12
    2563:	53                   	push   %rbx
    2564:	48 83 ec 20          	sub    $0x20,%rsp
    2568:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    256c:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2573:	00 00
    2575:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    2579:	31 c0                	xor    %eax,%eax
    257b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    257f:	0f b7 40 22          	movzwl 0x22(%rax),%eax
    2583:	83 e0 01             	and    $0x1,%eax
    2586:	66 85 c0             	test   %ax,%ax
    2589:	74 35                	je     25c0 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x67>
    258b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    258f:	0f b7 40 22          	movzwl 0x22(%rax),%eax
    2593:	0f b7 c0             	movzwl %ax,%eax
    2596:	83 f8 0b             	cmp    $0xb,%eax
    2599:	77 23                	ja     25be <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x65>
    259b:	89 c0                	mov    %eax,%eax
    259d:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    25a4:	00
    25a5:	48 8d 05 8c 1a 00 00 	lea    0x1a8c(%rip),%rax        # 4038 <_IO_stdin_used+0x38>
    25ac:	8b 04 02             	mov    (%rdx,%rax,1),%eax
    25af:	48 98                	cltq
    25b1:	48 8d 15 80 1a 00 00 	lea    0x1a80(%rip),%rdx        # 4038 <_IO_stdin_used+0x38>
    25b8:	48 01 d0             	add    %rdx,%rax
    25bb:	3e ff e0             	notrack jmpq *%rax
    25be:	0f 0b                	ud2
    25c0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    25c4:	0f b7 40 22          	movzwl 0x22(%rax),%eax
    25c8:	0f b7 c0             	movzwl %ax,%eax
    25cb:	83 f8 0a             	cmp    $0xa,%eax
    25ce:	77 68                	ja     2638 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0xdf>
    25d0:	89 c0                	mov    %eax,%eax
    25d2:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    25d9:	00
    25da:	48 8d 05 87 1a 00 00 	lea    0x1a87(%rip),%rax        # 4068 <_IO_stdin_used+0x68>
    25e1:	8b 04 02             	mov    (%rdx,%rax,1),%eax
    25e4:	48 98                	cltq
    25e6:	48 8d 15 7b 1a 00 00 	lea    0x1a7b(%rip),%rdx        # 4068 <_IO_stdin_used+0x68>
    25ed:	48 01 d0             	add    %rdx,%rax
    25f0:	3e ff e0             	notrack jmpq *%rax
    25f3:	48 8b 5d d8          	mov    -0x28(%rbp),%rbx
    25f7:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    25fb:	48 89 c7             	mov    %rax,%rdi
    25fe:	e8 e2 09 00 00       	callq  2fe5 <_ZNSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE12from_addressEPv>   # std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::from_address(void*)
    2603:	48 89 43 28          	mov    %rax,0x28(%rbx)
    2607:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    260b:	c6 40 34 00          	movb   $0x0,0x34(%rax)
    260f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2613:	48 83 c0 10          	add    $0x10,%rax
    2617:	48 89 c7             	mov    %rax,%rdi
    261a:	e8 e9 08 00 00       	callq  2f08 <_ZN9GeneratorImE12promise_type15initial_suspendEv> # Generator<unsigned long>::promise_type::initial_suspend()
    261f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2623:	48 83 c0 35          	add    $0x35,%rax
    2627:	48 89 c7             	mov    %rax,%rdi
    262a:	e8 39 07 00 00       	callq  2d68 <_ZNKSt7__n486114suspend_always11await_readyEv> # std::__n4861::suspend_always::await_ready() const
    262f:	83 f0 01             	xor    $0x1,%eax
    2632:	84 c0                	test   %al,%al
    2634:	75 04                	jne    263a <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0xe1>
    2636:	eb 31                	jmp    2669 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x110>
    2638:	0f 0b                	ud2
    263a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    263e:	66 c7 40 22 02 00    	movw   $0x2,0x22(%rax)
    2644:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2648:	48 8d 50 35          	lea    0x35(%rax),%rdx
    264c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2650:	48 8b 40 28          	mov    0x28(%rax),%rax
    2654:	48 89 c6             	mov    %rax,%rsi
    2657:	48 89 d7             	mov    %rdx,%rdi
    265a:	e8 1d 07 00 00       	callq  2d7c <_ZNKSt7__n486114suspend_always13await_suspendENS_16coroutine_handleIvEE>   # std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const
    265f:	e9 68 03 00 00       	jmpq   29cc <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x473>
    2664:	e9 2f 03 00 00       	jmpq   2998 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x43f>
    2669:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    266d:	c6 40 34 01          	movb   $0x1,0x34(%rax)
    2671:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2675:	48 83 c0 35          	add    $0x35,%rax
    2679:	48 89 c7             	mov    %rax,%rdi
    267c:	e8 0f 07 00 00       	callq  2d90 <_ZNKSt7__n486114suspend_always12await_resumeEv>    # std::__n4861::suspend_always::await_resume() const
    2681:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2685:	8b 40 30             	mov    0x30(%rax),%eax
    2688:	85 c0                	test   %eax,%eax
    268a:	75 15                	jne    26a1 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x148>
    268c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2690:	48 83 c0 10          	add    $0x10,%rax
    2694:	48 89 c7             	mov    %rax,%rdi
    2697:	e8 e0 07 00 00       	callq  2e7c <_ZN9GeneratorImE12promise_type11return_voidEv>
    269c:	e9 89 02 00 00       	jmpq   292a <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x3d1>
    26a1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    26a5:	8b 40 30             	mov    0x30(%rax),%eax
    26a8:	83 f8 5e             	cmp    $0x5e,%eax           # if n>94 throw runtime_error....
    26ab:	76 38                	jbe    26e5 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x18c>
    26ad:	bf 10 00 00 00       	mov    $0x10,%edi
    26b2:	e8 59 fb ff ff       	callq  2210 <__cxa_allocate_exception@plt>
    26b7:	48 89 c3             	mov    %rax,%rbx
    26ba:	48 8d 35 47 19 00 00 	lea    0x1947(%rip),%rsi        # 4008 <_IO_stdin_used+0x8>
    26c1:	48 89 df             	mov    %rbx,%rdi
    26c4:	e8 27 fb ff ff       	callq  21f0 <_ZNSt13runtime_errorC1EPKc@plt>
    26c9:	48 8b 05 e8 38 00 00 	mov    0x38e8(%rip),%rax        # 5fb8 <_ZNSt13runtime_errorD1Ev@GLIBCXX_3.4>
    26d0:	48 89 c2             	mov    %rax,%rdx
    26d3:	48 8b 05 16 39 00 00 	mov    0x3916(%rip),%rax        # 5ff0 <_ZTISt13runtime_error@GLIBCXX_3.4>
    26da:	48 89 c6             	mov    %rax,%rsi
    26dd:	48 89 df             	mov    %rbx,%rdi
    26e0:	e8 fb fb ff ff       	callq  22e0 <__cxa_throw@plt>       #  endif
    26e5:	48 8b 45 d8          	mov    -0x28(%rbp),%rax        # 取出协程帧地址
    26e9:	c7 40 4c 00 00 00 00 	movl   $0x0,0x4c(%rax)          # 写入返回值 在 0x4c的偏移上
    26f0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    26f4:	48 83 c0 10          	add    $0x10,%rax           # 协程帧地址 +0x10 (promise 地址)
    26f8:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx     # 取出协程帧地址
    26fc:	48 83 c2 4c          	add    $0x4c,%rdx           # 协程帧地址 +0x4c (返回值)
    2700:	48 89 d6             	mov    %rdx,%rsi            # 参数 : 返回值
    2703:	48 89 c7             	mov    %rax,%rdi            # 参数 : promise 地址 (+0x10)
    2706:	e8 93 07 00 00       	callq  2e9e <_ZN9GeneratorImE12promise_type11yield_valueIiEENSt7__n486114suspend_alwaysEOT_>    # std::__n4861::suspend_always Generator<unsigned long>::promise_type::yield_value<int>(int&&)
    270b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    270f:	48 83 c0 48          	add    $0x48,%rax   # 协程帧地址 +0x48 yield 的返回值?
    2713:	48 89 c7             	mov    %rax,%rdi
    2716:	e8 4d 06 00 00       	callq  2d68 <_ZNKSt7__n486114suspend_always11await_readyEv>     # std::__n4861::suspend_always::await_ready() const
    271b:	83 f0 01             	xor    $0x1,%eax
    271e:	84 c0                	test   %al,%al
    2720:	74 2f                	je     2751 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x1f8>
    2722:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2726:	66 c7 40 22 04 00    	movw   $0x4,0x22(%rax)
    272c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2730:	48 8d 50 48          	lea    0x48(%rax),%rdx
    2734:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2738:	48 8b 40 28          	mov    0x28(%rax),%rax
    273c:	48 89 c6             	mov    %rax,%rsi
    273f:	48 89 d7             	mov    %rdx,%rdi
    2742:	e8 35 06 00 00       	callq  2d7c <_ZNKSt7__n486114suspend_always13await_suspendENS_16coroutine_handleIvEE>   # std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const
    2747:	e9 80 02 00 00       	jmpq   29cc <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x473>
    274c:	e9 47 02 00 00       	jmpq   2998 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x43f>
    2751:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2755:	48 83 c0 48          	add    $0x48,%rax
    2759:	48 89 c7             	mov    %rax,%rdi
    275c:	e8 2f 06 00 00       	callq  2d90 <_ZNKSt7__n486114suspend_always12await_resumeEv>
    2761:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2765:	8b 40 30             	mov    0x30(%rax),%eax
    2768:	83 f8 01             	cmp    $0x1,%eax
    276b:	75 15                	jne    2782 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x229>
    276d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2771:	48 83 c0 10          	add    $0x10,%rax
    2775:	48 89 c7             	mov    %rax,%rdi
    2778:	e8 ff 06 00 00       	callq  2e7c <_ZN9GeneratorImE12promise_type11return_voidEv>
    277d:	e9 a8 01 00 00       	jmpq   292a <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x3d1>
    2782:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2786:	c7 40 54 01 00 00 00 	movl   $0x1,0x54(%rax)
    278d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2791:	48 83 c0 10          	add    $0x10,%rax
    2795:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
    2799:	48 83 c2 54          	add    $0x54,%rdx
    279d:	48 89 d6             	mov    %rdx,%rsi
    27a0:	48 89 c7             	mov    %rax,%rdi
    27a3:	e8 f6 06 00 00       	callq  2e9e <_ZN9GeneratorImE12promise_type11yield_valueIiEENSt7__n486114suspend_alwaysEOT_>
    27a8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27ac:	48 83 c0 50          	add    $0x50,%rax
    27b0:	48 89 c7             	mov    %rax,%rdi
    27b3:	e8 b0 05 00 00       	callq  2d68 <_ZNKSt7__n486114suspend_always11await_readyEv>
    27b8:	83 f0 01             	xor    $0x1,%eax
    27bb:	84 c0                	test   %al,%al
    27bd:	74 2f                	je     27ee <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x295>
    27bf:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27c3:	66 c7 40 22 06 00    	movw   $0x6,0x22(%rax)
    27c9:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27cd:	48 8d 50 50          	lea    0x50(%rax),%rdx
    27d1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27d5:	48 8b 40 28          	mov    0x28(%rax),%rax
    27d9:	48 89 c6             	mov    %rax,%rsi
    27dc:	48 89 d7             	mov    %rdx,%rdi
    27df:	e8 98 05 00 00       	callq  2d7c <_ZNKSt7__n486114suspend_always13await_suspendENS_16coroutine_handleIvEE>
    27e4:	e9 e3 01 00 00       	jmpq   29cc <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x473>
    27e9:	e9 aa 01 00 00       	jmpq   2998 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x43f>
    27ee:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27f2:	48 83 c0 50          	add    $0x50,%rax
    27f6:	48 89 c7             	mov    %rax,%rdi
    27f9:	e8 92 05 00 00       	callq  2d90 <_ZNKSt7__n486114suspend_always12await_resumeEv>
    27fe:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2802:	8b 40 30             	mov    0x30(%rax),%eax
    2805:	83 f8 02             	cmp    $0x2,%eax
    2808:	75 15                	jne    281f <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x2c6>
    280a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    280e:	48 83 c0 10          	add    $0x10,%rax
    2812:	48 89 c7             	mov    %rax,%rdi
    2815:	e8 62 06 00 00       	callq  2e7c <_ZN9GeneratorImE12promise_type11return_voidEv>
    281a:	e9 0b 01 00 00       	jmpq   292a <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x3d1>
    281f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2823:	48 c7 40 38 00 00 00 	movq   $0x0,0x38(%rax)
    282a:	00
    282b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    282f:	48 c7 40 40 01 00 00 	movq   $0x1,0x40(%rax)
    2836:	00
    2837:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    283b:	c7 40 58 02 00 00 00 	movl   $0x2,0x58(%rax)
    2842:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2846:	8b 50 58             	mov    0x58(%rax),%edx
    2849:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    284d:	8b 40 30             	mov    0x30(%rax),%eax
    2850:	39 c2                	cmp    %eax,%edx
    2852:	0f 83 c2 00 00 00    	jae    291a <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x3c1>
    2858:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    285c:	48 8b 50 38          	mov    0x38(%rax),%rdx
    2860:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2864:	48 8b 40 40          	mov    0x40(%rax),%rax
    2868:	48 01 c2             	add    %rax,%rdx
    286b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    286f:	48 89 50 60          	mov    %rdx,0x60(%rax)
    2873:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2877:	48 83 c0 10          	add    $0x10,%rax
    287b:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
    287f:	48 83 c2 60          	add    $0x60,%rdx
    2883:	48 89 d6             	mov    %rdx,%rsi
    2886:	48 89 c7             	mov    %rax,%rdi
    2889:	e8 46 06 00 00       	callq  2ed4 <_ZN9GeneratorImE12promise_type11yield_valueIRmEENSt7__n486114suspend_alwaysEOT_>
    288e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2892:	48 83 c0 68          	add    $0x68,%rax
    2896:	48 89 c7             	mov    %rax,%rdi
    2899:	e8 ca 04 00 00       	callq  2d68 <_ZNKSt7__n486114suspend_always11await_readyEv>
    289e:	83 f0 01             	xor    $0x1,%eax
    28a1:	84 c0                	test   %al,%al
    28a3:	74 2f                	je     28d4 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x37b>
    28a5:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28a9:	66 c7 40 22 08 00    	movw   $0x8,0x22(%rax)
    28af:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28b3:	48 8d 50 68          	lea    0x68(%rax),%rdx
    28b7:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28bb:	48 8b 40 28          	mov    0x28(%rax),%rax
    28bf:	48 89 c6             	mov    %rax,%rsi
    28c2:	48 89 d7             	mov    %rdx,%rdi
    28c5:	e8 b2 04 00 00       	callq  2d7c <_ZNKSt7__n486114suspend_always13await_suspendENS_16coroutine_handleIvEE>
    28ca:	e9 fd 00 00 00       	jmpq   29cc <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x473>
    28cf:	e9 c4 00 00 00       	jmpq   2998 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x43f>
    28d4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28d8:	48 83 c0 68          	add    $0x68,%rax
    28dc:	48 89 c7             	mov    %rax,%rdi
    28df:	e8 ac 04 00 00       	callq  2d90 <_ZNKSt7__n486114suspend_always12await_resumeEv>
    28e4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28e8:	48 8b 50 40          	mov    0x40(%rax),%rdx
    28ec:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28f0:	48 89 50 38          	mov    %rdx,0x38(%rax)
    28f4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28f8:	48 8b 50 60          	mov    0x60(%rax),%rdx
    28fc:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2900:	48 89 50 40          	mov    %rdx,0x40(%rax)
    2904:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2908:	8b 40 58             	mov    0x58(%rax),%eax
    290b:	8d 50 01             	lea    0x1(%rax),%edx
    290e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2912:	89 50 58             	mov    %edx,0x58(%rax)
    2915:	e9 28 ff ff ff       	jmpq   2842 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x2e9>
    291a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    291e:	48 83 c0 10          	add    $0x10,%rax
    2922:	48 89 c7             	mov    %rax,%rdi
    2925:	e8 52 05 00 00       	callq  2e7c <_ZN9GeneratorImE12promise_type11return_voidEv>
    292a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    292e:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
    2935:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2939:	48 83 c0 10          	add    $0x10,%rax
    293d:	48 89 c7             	mov    %rax,%rdi
    2940:	e8 39 06 00 00       	callq  2f7e <_ZN9GeneratorImE12promise_type13final_suspendEv>
    2945:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2949:	48 83 c0 69          	add    $0x69,%rax
    294d:	48 89 c7             	mov    %rax,%rdi
    2950:	e8 13 04 00 00       	callq  2d68 <_ZNKSt7__n486114suspend_always11await_readyEv>
    2955:	83 f0 01             	xor    $0x1,%eax
    2958:	84 c0                	test   %al,%al
    295a:	74 29                	je     2985 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x42c>
    295c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2960:	66 c7 40 22 0a 00    	movw   $0xa,0x22(%rax)
    2966:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    296a:	48 8d 50 69          	lea    0x69(%rax),%rdx
    296e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2972:	48 8b 40 28          	mov    0x28(%rax),%rax
    2976:	48 89 c6             	mov    %rax,%rsi
    2979:	48 89 d7             	mov    %rdx,%rdi
    297c:	e8 fb 03 00 00       	callq  2d7c <_ZNKSt7__n486114suspend_always13await_suspendENS_16coroutine_handleIvEE>
    2981:	eb 49                	jmp    29cc <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x473>
    2983:	eb 13                	jmp    2998 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x43f>
    2985:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2989:	48 83 c0 69          	add    $0x69,%rax
    298d:	48 89 c7             	mov    %rax,%rdi
    2990:	e8 fb 03 00 00       	callq  2d90 <_ZNKSt7__n486114suspend_always12await_resumeEv>
    2995:	eb 01                	jmp    2998 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x43f>
    2997:	90                   	nop
    2998:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    299c:	48 83 c0 10          	add    $0x10,%rax
    29a0:	48 89 c7             	mov    %rax,%rdi
    29a3:	e8 b0 04 00 00       	callq  2e58 <_ZN9GeneratorImE12promise_typeD1Ev>
    29a8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    29ac:	0f b6 40 20          	movzbl 0x20(%rax),%eax
    29b0:	0f b6 c0             	movzbl %al,%eax
    29b3:	85 c0                	test   %eax,%eax
    29b5:	0f 84 91 00 00 00    	je     2a4c <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x4f3>
    29bb:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    29bf:	48 89 c7             	mov    %rax,%rdi
    29c2:	e8 79 f8 ff ff       	callq  2240 <_ZdlPv@plt>
    29c7:	e9 80 00 00 00       	jmpq   2a4c <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x4f3>
    29cc:	f3 0f 1e fa          	endbr64
    29d0:	eb 7a                	jmp    2a4c <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x4f3>
    29d2:	f3 0f 1e fa          	endbr64
    29d6:	49 89 c4             	mov    %rax,%r12
    29d9:	48 89 df             	mov    %rbx,%rdi
    29dc:	e8 3f f8 ff ff       	callq  2220 <__cxa_free_exception@plt>
    29e1:	4c 89 e0             	mov    %r12,%rax
    29e4:	eb 04                	jmp    29ea <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x491>
    29e6:	f3 0f 1e fa          	endbr64
    29ea:	48 89 c7             	mov    %rax,%rdi
    29ed:	e8 0e f8 ff ff       	callq  2200 <__cxa_begin_catch@plt>
    29f2:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    29f6:	0f b6 40 34          	movzbl 0x34(%rax),%eax
    29fa:	83 f0 01             	xor    $0x1,%eax
    29fd:	84 c0                	test   %al,%al
    29ff:	74 05                	je     2a06 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x4ad>
    2a01:	e8 aa f8 ff ff       	callq  22b0 <__cxa_rethrow@plt>
    2a06:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2a0a:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
    2a11:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2a15:	66 c7 40 22 00 00    	movw   $0x0,0x22(%rax)
    2a1b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2a1f:	48 83 c0 10          	add    $0x10,%rax
    2a23:	48 89 c7             	mov    %rax,%rdi
    2a26:	e8 ed 04 00 00       	callq  2f18 <_ZN9GeneratorImE12promise_type19unhandled_exceptionEv>
    2a2b:	e8 a0 f8 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2a30:	e9 f5 fe ff ff       	jmpq   292a <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x3d1>
    2a35:	f3 0f 1e fa          	endbr64
    2a39:	48 89 c3             	mov    %rax,%rbx
    2a3c:	e8 8f f8 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2a41:	48 89 d8             	mov    %rbx,%rax
    2a44:	48 89 c7             	mov    %rax,%rdi
    2a47:	e8 b4 f8 ff ff       	callq  2300 <_Unwind_Resume@plt>
    2a4c:	90                   	nop
    2a4d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2a51:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    2a58:	00 00
    2a5a:	74 05                	je     2a61 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame+0x508>
    2a5c:	e8 2f f8 ff ff       	callq  2290 <__stack_chk_fail@plt>
    2a61:	48 83 c4 20          	add    $0x20,%rsp
    2a65:	5b                   	pop    %rbx
    2a66:	41 5c                	pop    %r12
    2a68:	5d                   	pop    %rbp
    2a69:	c3                   	retq

0000000000002a6a <_Z31_Z18fibonacci_sequencej.destroyPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame>:
    2a6a:	f3 0f 1e fa          	endbr64
    2a6e:	55                   	push   %rbp
    2a6f:	48 89 e5             	mov    %rsp,%rbp
    2a72:	48 83 ec 10          	sub    $0x10,%rsp
    2a76:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2a7a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2a7e:	0f b7 40 22          	movzwl 0x22(%rax),%eax
    2a82:	83 c8 01             	or     $0x1,%eax
    2a85:	89 c2                	mov    %eax,%edx
    2a87:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2a8b:	66 89 50 22          	mov    %dx,0x22(%rax)
    2a8f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2a93:	48 89 c7             	mov    %rax,%rdi
    2a96:	e8 be fa ff ff       	callq  2559 <_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame>
    2a9b:	c9                   	leaveq
    2a9c:	c3                   	retq


0000000000002a9d <_Z13run_coroutinev>:
    2a9d:	f3 0f 1e fa          	endbr64 
    2aa1:	55                   	push   %rbp
    2aa2:	48 89 e5             	mov    %rsp,%rbp
    2aa5:	41 54                	push   %r12
    2aa7:	53                   	push   %rbx
    2aa8:	48 83 ec 30          	sub    $0x30,%rsp
    2aac:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2ab3:	00 00 
    2ab5:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    2ab9:	31 c0                	xor    %eax,%eax
    2abb:	c7 45 c4 01 00 00 00 	movl   $0x1,-0x3c(%rbp) # int i = 1
    2ac2:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2ac6:	be 0a 00 00 00       	mov    $0xa,%esi #   第二个参数 : 10
    2acb:	48 89 c7             	mov    %rax,%rdi # 第一个参数 : 要返回的generator
    2ace:	e8 41 f9 ff ff       	callq  2414 <_Z18fibonacci_sequencej>  #fibonacci_sequence(unsigned int) 构造generator
    2ad3:	c7 45 c0 00 00 00 00 	movl   $0x0,-0x40(%rbp)
    2ada:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2ade:	48 89 c7             	mov    %rax,%rdi
    2ae1:	e8 48 05 00 00       	callq  302e <_ZN9GeneratorImEcvbEv> # Generator<unsigned long>::operator bool() # %al ==1, 判断返回值, start for
    2ae6:	84 c0                	test   %al,%al
    2ae8:	74 62                	je     2b4c <_Z13run_coroutinev+0xaf>
    2aea:	48 8d 35 a3 15 00 00 	lea    0x15a3(%rip),%rsi        # 4094 <_IO_stdin_used+0x94>
    2af1:	48 8b 05 c8 34 00 00 	mov    0x34c8(%rip),%rax        # 5fc0 <_ZSt4cout@GLIBCXX_3.4>
    2af8:	48 89 c7             	mov    %rax,%rdi
    2afb:	e8 50 f7 ff ff       	callq  2250 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2b00:	48 89 c2             	mov    %rax,%rdx
    2b03:	8b 45 c0             	mov    -0x40(%rbp),%eax
    2b06:	89 c6                	mov    %eax,%esi
    2b08:	48 89 d7             	mov    %rdx,%rdi
    2b0b:	e8 e0 f7 ff ff       	callq  22f0 <_ZNSolsEi@plt>
    2b10:	48 8d 35 82 15 00 00 	lea    0x1582(%rip),%rsi        # 4099 <_IO_stdin_used+0x99>
    2b17:	48 89 c7             	mov    %rax,%rdi
    2b1a:	e8 31 f7 ff ff       	callq  2250 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2b1f:	48 89 c3             	mov    %rax,%rbx
    2b22:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2b26:	48 89 c7             	mov    %rax,%rdi
    2b29:	e8 2e 05 00 00       	callq  305c <_ZN9GeneratorImEclEv>  # Generator<unsigned long>::operator()()
    2b2e:	48 89 c6             	mov    %rax,%rsi
    2b31:	48 89 df             	mov    %rbx,%rdi
    2b34:	e8 77 f6 ff ff       	callq  21b0 <_ZNSolsEm@plt>
    2b39:	be 0a 00 00 00       	mov    $0xa,%esi
    2b3e:	48 89 c7             	mov    %rax,%rdi
    2b41:	e8 5a f7 ff ff       	callq  22a0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@plt>
    2b46:	83 45 c0 01          	addl   $0x1,-0x40(%rbp)
    2b4a:	eb 8e                	jmp    2ada <_Z13run_coroutinev+0x3d>
    2b4c:	48 8d 45 d0          	lea    -0x30(%rbp),%rax # end for
    2b50:	48 89 c7             	mov    %rax,%rdi
    2b53:	e8 6e 04 00 00       	callq  2fc6 <_ZN9GeneratorImED1Ev>  # Generator<unsigned long>::~Generator()
    2b58:	b8 00 00 00 00       	mov    $0x0,%eax
    2b5d:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
    2b61:	64 48 2b 0c 25 28 00 	sub    %fs:0x28,%rcx
    2b68:	00 00 
    2b6a:	0f 84 e6 00 00 00    	je     2c56 <_Z13run_coroutinev+0x1b9>
    2b70:	e9 dc 00 00 00       	jmpq   2c51 <_Z13run_coroutinev+0x1b4>
    2b75:	f3 0f 1e fa          	endbr64 
    2b79:	49 89 c4             	mov    %rax,%r12
    2b7c:	48 89 d3             	mov    %rdx,%rbx
    2b7f:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2b83:	48 89 c7             	mov    %rax,%rdi
    2b86:	e8 3b 04 00 00       	callq  2fc6 <_ZN9GeneratorImED1Ev>
    2b8b:	4c 89 e0             	mov    %r12,%rax
    2b8e:	48 89 da             	mov    %rbx,%rdx
    2b91:	eb 04                	jmp    2b97 <_Z13run_coroutinev+0xfa>
    2b93:	f3 0f 1e fa          	endbr64 
    2b97:	48 83 fa 01          	cmp    $0x1,%rdx
    2b9b:	75 5e                	jne    2bfb <_Z13run_coroutinev+0x15e>
    2b9d:	48 89 c7             	mov    %rax,%rdi
    2ba0:	e8 5b f6 ff ff       	callq  2200 <__cxa_begin_catch@plt>
    2ba5:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
    2ba9:	48 8d 35 ec 14 00 00 	lea    0x14ec(%rip),%rsi        # 409c <_IO_stdin_used+0x9c>
    2bb0:	48 8b 05 31 34 00 00 	mov    0x3431(%rip),%rax        # 5fe8 <_ZSt4cerr@GLIBCXX_3.4>
    2bb7:	48 89 c7             	mov    %rax,%rdi
    2bba:	e8 91 f6 ff ff       	callq  2250 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2bbf:	48 89 c3             	mov    %rax,%rbx
    2bc2:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    2bc6:	48 8b 00             	mov    (%rax),%rax
    2bc9:	48 83 c0 10          	add    $0x10,%rax
    2bcd:	48 8b 10             	mov    (%rax),%rdx
    2bd0:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    2bd4:	48 89 c7             	mov    %rax,%rdi
    2bd7:	ff d2                	callq  *%rdx
    2bd9:	48 89 c6             	mov    %rax,%rsi
    2bdc:	48 89 df             	mov    %rbx,%rdi
    2bdf:	e8 6c f6 ff ff       	callq  2250 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2be4:	be 0a 00 00 00       	mov    $0xa,%esi
    2be9:	48 89 c7             	mov    %rax,%rdi
    2bec:	e8 af f6 ff ff       	callq  22a0 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@plt>
    2bf1:	e8 da f6 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2bf6:	e9 5d ff ff ff       	jmpq   2b58 <_Z13run_coroutinev+0xbb>
    2bfb:	48 89 c7             	mov    %rax,%rdi
    2bfe:	e8 fd f5 ff ff       	callq  2200 <__cxa_begin_catch@plt>
    2c03:	48 8d 35 a5 14 00 00 	lea    0x14a5(%rip),%rsi        # 40af <_IO_stdin_used+0xaf>
    2c0a:	48 8b 05 d7 33 00 00 	mov    0x33d7(%rip),%rax        # 5fe8 <_ZSt4cerr@GLIBCXX_3.4>
    2c11:	48 89 c7             	mov    %rax,%rdi
    2c14:	e8 37 f6 ff ff       	callq  2250 <_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@plt>
    2c19:	e8 b2 f6 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2c1e:	e9 35 ff ff ff       	jmpq   2b58 <_Z13run_coroutinev+0xbb>
    2c23:	f3 0f 1e fa          	endbr64 
    2c27:	48 89 c3             	mov    %rax,%rbx
    2c2a:	e8 a1 f6 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2c2f:	48 89 d8             	mov    %rbx,%rax
    2c32:	48 89 c7             	mov    %rax,%rdi
    2c35:	e8 c6 f6 ff ff       	callq  2300 <_Unwind_Resume@plt>
    2c3a:	f3 0f 1e fa          	endbr64 
    2c3e:	48 89 c3             	mov    %rax,%rbx
    2c41:	e8 8a f6 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2c46:	48 89 d8             	mov    %rbx,%rax
    2c49:	48 89 c7             	mov    %rax,%rdi
    2c4c:	e8 af f6 ff ff       	callq  2300 <_Unwind_Resume@plt>
    2c51:	e8 3a f6 ff ff       	callq  2290 <__stack_chk_fail@plt>
    2c56:	48 83 c4 30          	add    $0x30,%rsp
    2c5a:	5b                   	pop    %rbx
    2c5b:	41 5c                	pop    %r12
    2c5d:	5d                   	pop    %rbp
    2c5e:	c3                   	retq   

0000000000002c5f <main>:
    2c5f:	f3 0f 1e fa          	endbr64 
    2c63:	55                   	push   %rbp
    2c64:	48 89 e5             	mov    %rsp,%rbp
    2c67:	48 83 ec 10          	sub    $0x10,%rsp
    2c6b:	89 7d fc             	mov    %edi,-0x4(%rbp)
    2c6e:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    2c72:	e8 26 fe ff ff       	callq  2a9d <_Z13run_coroutinev>
    2c77:	b8 00 00 00 00       	mov    $0x0,%eax
    2c7c:	c9                   	leaveq 
    2c7d:	c3                   	retq   

0000000000002c7e <_Z41__static_initialization_and_destruction_0ii>:
    2c7e:	f3 0f 1e fa          	endbr64 
    2c82:	55                   	push   %rbp
    2c83:	48 89 e5             	mov    %rsp,%rbp
    2c86:	48 83 ec 10          	sub    $0x10,%rsp
    2c8a:	89 7d fc             	mov    %edi,-0x4(%rbp)
    2c8d:	89 75 f8             	mov    %esi,-0x8(%rbp)
    2c90:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
    2c94:	75 32                	jne    2cc8 <_Z41__static_initialization_and_destruction_0ii+0x4a>
    2c96:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
    2c9d:	75 29                	jne    2cc8 <_Z41__static_initialization_and_destruction_0ii+0x4a>
    2c9f:	48 8d 3d 93 33 00 00 	lea    0x3393(%rip),%rdi        # 6039 <_ZStL8__ioinit>
    2ca6:	e8 15 f6 ff ff       	callq  22c0 <_ZNSt8ios_base4InitC1Ev@plt>
    2cab:	48 8d 15 56 33 00 00 	lea    0x3356(%rip),%rdx        # 6008 <__dso_handle>
    2cb2:	48 8d 35 80 33 00 00 	lea    0x3380(%rip),%rsi        # 6039 <_ZStL8__ioinit>
    2cb9:	48 8b 05 38 33 00 00 	mov    0x3338(%rip),%rax        # 5ff8 <_ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4>
    2cc0:	48 89 c7             	mov    %rax,%rdi
    2cc3:	e8 68 f5 ff ff       	callq  2230 <__cxa_atexit@plt>
    2cc8:	90                   	nop
    2cc9:	c9                   	leaveq 
    2cca:	c3                   	retq   

0000000000002ccb <_GLOBAL__sub_I_main.cpp>:
    2ccb:	f3 0f 1e fa          	endbr64 
    2ccf:	55                   	push   %rbp
    2cd0:	48 89 e5             	mov    %rsp,%rbp
    2cd3:	be ff ff 00 00       	mov    $0xffff,%esi
    2cd8:	bf 01 00 00 00       	mov    $0x1,%edi
    2cdd:	e8 9c ff ff ff       	callq  2c7e <_Z41__static_initialization_and_destruction_0ii>
    2ce2:	5d                   	pop    %rbp
    2ce3:	c3                   	retq   

0000000000002ce4 <_ZNKSt7__n486116coroutine_handleIvE4doneEv>:
    2ce4:	f3 0f 1e fa          	endbr64 
    2ce8:	55                   	push   %rbp
    2ce9:	48 89 e5             	mov    %rsp,%rbp
    2cec:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2cf0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2cf4:	48 8b 00             	mov    (%rax),%rax
    2cf7:	48 8b 00             	mov    (%rax),%rax
    2cfa:	48 85 c0             	test   %rax,%rax
    2cfd:	0f 94 c0             	sete   %al
    2d00:	5d                   	pop    %rbp
    2d01:	c3                   	retq   

0000000000002d02 <_ZNKSt7__n486116coroutine_handleIvEclEv>:
    2d02:	f3 0f 1e fa          	endbr64 
    2d06:	55                   	push   %rbp
    2d07:	48 89 e5             	mov    %rsp,%rbp
    2d0a:	48 83 ec 10          	sub    $0x10,%rsp
    2d0e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d12:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2d16:	48 89 c7             	mov    %rax,%rdi
    2d19:	e8 04 00 00 00       	callq  2d22 <_ZNKSt7__n486116coroutine_handleIvE6resumeEv>
    2d1e:	90                   	nop
    2d1f:	c9                   	leaveq 
    2d20:	c3                   	retq   
    2d21:	90                   	nop

0000000000002d22 <_ZNKSt7__n486116coroutine_handleIvE6resumeEv>:
    2d22:	f3 0f 1e fa          	endbr64 
    2d26:	55                   	push   %rbp
    2d27:	48 89 e5             	mov    %rsp,%rbp
    2d2a:	48 83 ec 10          	sub    $0x10,%rsp
    2d2e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d32:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2d36:	48 8b 00             	mov    (%rax),%rax
    2d39:	48 8b 10             	mov    (%rax),%rdx
    2d3c:	48 89 c7             	mov    %rax,%rdi
    2d3f:	ff d2                	callq  *%rdx
    2d41:	90                   	nop
    2d42:	c9                   	leaveq 
    2d43:	c3                   	retq   

0000000000002d44 <_ZNKSt7__n486116coroutine_handleIvE7destroyEv>:
    2d44:	f3 0f 1e fa          	endbr64 
    2d48:	55                   	push   %rbp
    2d49:	48 89 e5             	mov    %rsp,%rbp
    2d4c:	48 83 ec 10          	sub    $0x10,%rsp
    2d50:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d54:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2d58:	48 8b 00             	mov    (%rax),%rax
    2d5b:	48 8b 50 08          	mov    0x8(%rax),%rdx
    2d5f:	48 89 c7             	mov    %rax,%rdi
    2d62:	ff d2                	callq  *%rdx
    2d64:	90                   	nop
    2d65:	c9                   	leaveq 
    2d66:	c3                   	retq   
    2d67:	90                   	nop

0000000000002d68 <_ZNKSt7__n486114suspend_always11await_readyEv>:
    2d68:	f3 0f 1e fa          	endbr64 
    2d6c:	55                   	push   %rbp
    2d6d:	48 89 e5             	mov    %rsp,%rbp
    2d70:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d74:	b8 00 00 00 00       	mov    $0x0,%eax
    2d79:	5d                   	pop    %rbp
    2d7a:	c3                   	retq   
    2d7b:	90                   	nop

0000000000002d7c <_ZNKSt7__n486114suspend_always13await_suspendENS_16coroutine_handleIvEE>:
    2d7c:	f3 0f 1e fa          	endbr64 
    2d80:	55                   	push   %rbp
    2d81:	48 89 e5             	mov    %rsp,%rbp
    2d84:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d88:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    2d8c:	90                   	nop
    2d8d:	5d                   	pop    %rbp
    2d8e:	c3                   	retq   
    2d8f:	90                   	nop

0000000000002d90 <_ZNKSt7__n486114suspend_always12await_resumeEv>:
    2d90:	f3 0f 1e fa          	endbr64 
    2d94:	55                   	push   %rbp
    2d95:	48 89 e5             	mov    %rsp,%rbp
    2d98:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d9c:	90                   	nop
    2d9d:	5d                   	pop    %rbp
    2d9e:	c3                   	retq   
    2d9f:	90                   	nop

0000000000002da0 <_ZNSt15__exception_ptr13exception_ptrC1EOS0_>:
    2da0:	f3 0f 1e fa          	endbr64 
    2da4:	55                   	push   %rbp
    2da5:	48 89 e5             	mov    %rsp,%rbp
    2da8:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2dac:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    2db0:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    2db4:	48 8b 10             	mov    (%rax),%rdx
    2db7:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2dbb:	48 89 10             	mov    %rdx,(%rax)
    2dbe:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    2dc2:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
    2dc9:	90                   	nop
    2dca:	5d                   	pop    %rbp
    2dcb:	c3                   	retq   

0000000000002dcc <_ZNSt15__exception_ptr13exception_ptraSEOS0_>:
    2dcc:	f3 0f 1e fa          	endbr64 
    2dd0:	55                   	push   %rbp
    2dd1:	48 89 e5             	mov    %rsp,%rbp
    2dd4:	48 83 ec 20          	sub    $0x20,%rsp
    2dd8:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2ddc:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    2de0:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2de7:	00 00 
    2de9:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    2ded:	31 c0                	xor    %eax,%eax
    2def:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
    2df3:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2df7:	48 89 d6             	mov    %rdx,%rsi
    2dfa:	48 89 c7             	mov    %rax,%rdi
    2dfd:	e8 9e ff ff ff       	callq  2da0 <_ZNSt15__exception_ptr13exception_ptrC1EOS0_>
    2e02:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
    2e06:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2e0a:	48 89 d6             	mov    %rdx,%rsi
    2e0d:	48 89 c7             	mov    %rax,%rdi
    2e10:	e8 ab f3 ff ff       	callq  21c0 <_ZNSt15__exception_ptr13exception_ptr4swapERS0_@plt>
    2e15:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2e19:	48 89 c7             	mov    %rax,%rdi
    2e1c:	e8 ef f4 ff ff       	callq  2310 <_ZNSt15__exception_ptr13exception_ptrD1Ev@plt>
    2e21:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2e25:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
    2e29:	64 48 2b 0c 25 28 00 	sub    %fs:0x28,%rcx
    2e30:	00 00 
    2e32:	74 05                	je     2e39 <_ZNSt15__exception_ptr13exception_ptraSEOS0_+0x6d>
    2e34:	e8 57 f4 ff ff       	callq  2290 <__stack_chk_fail@plt>
    2e39:	c9                   	leaveq 
    2e3a:	c3                   	retq   
    2e3b:	90                   	nop

0000000000002e3c <_ZNKSt15__exception_ptr13exception_ptrcvbEv>:
    2e3c:	f3 0f 1e fa          	endbr64 
    2e40:	55                   	push   %rbp
    2e41:	48 89 e5             	mov    %rsp,%rbp
    2e44:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2e48:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2e4c:	48 8b 00             	mov    (%rax),%rax
    2e4f:	48 85 c0             	test   %rax,%rax
    2e52:	0f 95 c0             	setne  %al
    2e55:	5d                   	pop    %rbp
    2e56:	c3                   	retq   
    2e57:	90                   	nop

0000000000002e58 <_ZN9GeneratorImE12promise_typeD1Ev>:
    2e58:	f3 0f 1e fa          	endbr64 
    2e5c:	55                   	push   %rbp
    2e5d:	48 89 e5             	mov    %rsp,%rbp
    2e60:	48 83 ec 10          	sub    $0x10,%rsp
    2e64:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2e68:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2e6c:	48 83 c0 08          	add    $0x8,%rax
    2e70:	48 89 c7             	mov    %rax,%rdi
    2e73:	e8 98 f4 ff ff       	callq  2310 <_ZNSt15__exception_ptr13exception_ptrD1Ev@plt>
    2e78:	90                   	nop
    2e79:	c9                   	leaveq 
    2e7a:	c3                   	retq   
    2e7b:	90                   	nop

0000000000002e7c <_ZN9GeneratorImE12promise_type11return_voidEv>:
    2e7c:	f3 0f 1e fa          	endbr64 
    2e80:	55                   	push   %rbp
    2e81:	48 89 e5             	mov    %rsp,%rbp
    2e84:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2e88:	90                   	nop
    2e89:	5d                   	pop    %rbp
    2e8a:	c3                   	retq   

0000000000002e8b <_ZSt7forwardIiEOT_RNSt16remove_referenceIS0_E4typeE>:
    2e8b:	f3 0f 1e fa          	endbr64 
    2e8f:	55                   	push   %rbp
    2e90:	48 89 e5             	mov    %rsp,%rbp
    2e93:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2e97:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2e9b:	5d                   	pop    %rbp
    2e9c:	c3                   	retq   
    2e9d:	90                   	nop

0000000000002e9e <_ZN9GeneratorImE12promise_type11yield_valueIiEENSt7__n486114suspend_alwaysEOT_>:
    2e9e:	f3 0f 1e fa          	endbr64 
    2ea2:	55                   	push   %rbp
    2ea3:	48 89 e5             	mov    %rsp,%rbp
    2ea6:	53                   	push   %rbx
    2ea7:	48 83 ec 18          	sub    $0x18,%rsp
    2eab:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2eaf:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    2eb3:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2eb7:	48 89 c7             	mov    %rax,%rdi
    2eba:	e8 cc ff ff ff       	callq  2e8b <_ZSt7forwardIiEOT_RNSt16remove_referenceIS0_E4typeE>
    2ebf:	8b 00                	mov    (%rax),%eax
    2ec1:	48 63 d0             	movslq %eax,%rdx
    2ec4:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2ec8:	48 89 10             	mov    %rdx,(%rax)
    2ecb:	90                   	nop
    2ecc:	89 d8                	mov    %ebx,%eax
    2ece:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    2ed2:	c9                   	leaveq 
    2ed3:	c3                   	retq   

0000000000002ed4 <_ZN9GeneratorImE12promise_type11yield_valueIRmEENSt7__n486114suspend_alwaysEOT_>:
    2ed4:	f3 0f 1e fa          	endbr64 
    2ed8:	55                   	push   %rbp
    2ed9:	48 89 e5             	mov    %rsp,%rbp
    2edc:	53                   	push   %rbx
    2edd:	48 83 ec 18          	sub    $0x18,%rsp
    2ee1:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2ee5:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    2ee9:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2eed:	48 89 c7             	mov    %rax,%rdi
    2ef0:	e8 a4 01 00 00       	callq  3099 <_ZSt7forwardIRmEOT_RNSt16remove_referenceIS1_E4typeE>
    2ef5:	48 8b 10             	mov    (%rax),%rdx
    2ef8:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2efc:	48 89 10             	mov    %rdx,(%rax)
    2eff:	90                   	nop
    2f00:	89 d8                	mov    %ebx,%eax
    2f02:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    2f06:	c9                   	leaveq 
    2f07:	c3                   	retq   

0000000000002f08 <_ZN9GeneratorImE12promise_type15initial_suspendEv>:
    2f08:	f3 0f 1e fa          	endbr64 
    2f0c:	55                   	push   %rbp
    2f0d:	48 89 e5             	mov    %rsp,%rbp
    2f10:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2f14:	90                   	nop
    2f15:	5d                   	pop    %rbp
    2f16:	c3                   	retq   
    2f17:	90                   	nop

0000000000002f18 <_ZN9GeneratorImE12promise_type19unhandled_exceptionEv>:
    2f18:	f3 0f 1e fa          	endbr64 
    2f1c:	55                   	push   %rbp
    2f1d:	48 89 e5             	mov    %rsp,%rbp
    2f20:	48 83 ec 20          	sub    $0x20,%rsp
    2f24:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2f28:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2f2f:	00 00 
    2f31:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    2f35:	31 c0                	xor    %eax,%eax
    2f37:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2f3b:	48 89 c7             	mov    %rax,%rdi
    2f3e:	e8 3d f3 ff ff       	callq  2280 <_ZSt17current_exceptionv@plt>
    2f43:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2f47:	48 8d 50 08          	lea    0x8(%rax),%rdx
    2f4b:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2f4f:	48 89 c6             	mov    %rax,%rsi
    2f52:	48 89 d7             	mov    %rdx,%rdi
    2f55:	e8 72 fe ff ff       	callq  2dcc <_ZNSt15__exception_ptr13exception_ptraSEOS0_>
    2f5a:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2f5e:	48 89 c7             	mov    %rax,%rdi
    2f61:	e8 aa f3 ff ff       	callq  2310 <_ZNSt15__exception_ptr13exception_ptrD1Ev@plt>
    2f66:	90                   	nop
    2f67:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2f6b:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    2f72:	00 00 
    2f74:	74 05                	je     2f7b <_ZN9GeneratorImE12promise_type19unhandled_exceptionEv+0x63>
    2f76:	e8 15 f3 ff ff       	callq  2290 <__stack_chk_fail@plt>
    2f7b:	c9                   	leaveq 
    2f7c:	c3                   	retq   
    2f7d:	90                   	nop

0000000000002f7e <_ZN9GeneratorImE12promise_type13final_suspendEv>:
    2f7e:	f3 0f 1e fa          	endbr64 
    2f82:	55                   	push   %rbp
    2f83:	48 89 e5             	mov    %rsp,%rbp
    2f86:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2f8a:	90                   	nop
    2f8b:	5d                   	pop    %rbp
    2f8c:	c3                   	retq   
    2f8d:	90                   	nop

0000000000002f8e <_ZN9GeneratorImE12promise_type17get_return_objectEv>:
    2f8e:	f3 0f 1e fa          	endbr64 
    2f92:	55                   	push   %rbp
    2f93:	48 89 e5             	mov    %rsp,%rbp
    2f96:	48 83 ec 10          	sub    $0x10,%rsp
    2f9a:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2f9e:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    2fa2:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    2fa6:	48 89 c7             	mov    %rax,%rdi
    2fa9:	e8 fd 00 00 00       	callq  30ab <_ZNSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE12from_promiseERS3_>
    2fae:	48 89 c2             	mov    %rax,%rdx
    2fb1:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2fb5:	48 89 d6             	mov    %rdx,%rsi
    2fb8:	48 89 c7             	mov    %rax,%rdi
    2fbb:	e8 38 01 00 00       	callq  30f8 <_ZN9GeneratorImEC1ENSt7__n486116coroutine_handleINS0_12promise_typeEEE>
    2fc0:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2fc4:	c9                   	leaveq 
    2fc5:	c3                   	retq   

0000000000002fc6 <_ZN9GeneratorImED1Ev>:
    2fc6:	f3 0f 1e fa          	endbr64 
    2fca:	55                   	push   %rbp
    2fcb:	48 89 e5             	mov    %rsp,%rbp
    2fce:	48 83 ec 10          	sub    $0x10,%rsp
    2fd2:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2fd6:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2fda:	48 89 c7             	mov    %rax,%rdi
    2fdd:	e8 62 fd ff ff       	callq  2d44 <_ZNKSt7__n486116coroutine_handleIvE7destroyEv>
    2fe2:	90                   	nop
    2fe3:	c9                   	leaveq 
    2fe4:	c3                   	retq   

0000000000002fe5 <_ZNSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE12from_addressEPv>:
    2fe5:	f3 0f 1e fa          	endbr64 
    2fe9:	55                   	push   %rbp
    2fea:	48 89 e5             	mov    %rsp,%rbp
    2fed:	48 83 ec 20          	sub    $0x20,%rsp
    2ff1:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2ff5:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2ffc:	00 00 
    2ffe:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    3002:	31 c0                	xor    %eax,%eax
    3004:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
    300b:	00 
    300c:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    3010:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    3014:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    3018:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    301c:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    3023:	00 00 
    3025:	74 05                	je     302c <_ZNSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE12from_addressEPv+0x47>
    3027:	e8 64 f2 ff ff       	callq  2290 <__stack_chk_fail@plt>
    302c:	c9                   	leaveq 
    302d:	c3                   	retq   

000000000000302e <_ZN9GeneratorImEcvbEv>:
    302e:	f3 0f 1e fa          	endbr64 
    3032:	55                   	push   %rbp
    3033:	48 89 e5             	mov    %rsp,%rbp
    3036:	48 83 ec 10          	sub    $0x10,%rsp
    303a:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    303e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3042:	48 89 c7             	mov    %rax,%rdi
    3045:	e8 d4 00 00 00       	callq  311e <_ZN9GeneratorImE4fillEv>
    304a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    304e:	48 89 c7             	mov    %rax,%rdi
    3051:	e8 8e fc ff ff       	callq  2ce4 <_ZNKSt7__n486116coroutine_handleIvE4doneEv>
    3056:	83 f0 01             	xor    $0x1,%eax
    3059:	c9                   	leaveq 
    305a:	c3                   	retq   
    305b:	90                   	nop

000000000000305c <_ZN9GeneratorImEclEv>:
    305c:	f3 0f 1e fa          	endbr64 
    3060:	55                   	push   %rbp
    3061:	48 89 e5             	mov    %rsp,%rbp
    3064:	48 83 ec 10          	sub    $0x10,%rsp
    3068:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    306c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3070:	48 89 c7             	mov    %rax,%rdi
    3073:	e8 a6 00 00 00       	callq  311e <_ZN9GeneratorImE4fillEv>
    3078:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    307c:	c6 40 08 00          	movb   $0x0,0x8(%rax)
    3080:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3084:	48 89 c7             	mov    %rax,%rdi
    3087:	e8 58 01 00 00       	callq  31e4 <_ZNKSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE7promiseEv>
    308c:	48 89 c7             	mov    %rax,%rdi
    308f:	e8 71 01 00 00       	callq  3205 <_ZSt4moveIRmEONSt16remove_referenceIT_E4typeEOS2_>
    3094:	48 8b 00             	mov    (%rax),%rax
    3097:	c9                   	leaveq 
    3098:	c3                   	retq   

0000000000003099 <_ZSt7forwardIRmEOT_RNSt16remove_referenceIS1_E4typeE>:
    3099:	f3 0f 1e fa          	endbr64 
    309d:	55                   	push   %rbp
    309e:	48 89 e5             	mov    %rsp,%rbp
    30a1:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    30a5:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    30a9:	5d                   	pop    %rbp
    30aa:	c3                   	retq   

00000000000030ab <_ZNSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE12from_promiseERS3_>:
    30ab:	f3 0f 1e fa          	endbr64 
    30af:	55                   	push   %rbp
    30b0:	48 89 e5             	mov    %rsp,%rbp
    30b3:	48 83 ec 20          	sub    $0x20,%rsp
    30b7:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    30bb:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    30c2:	00 00 
    30c4:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    30c8:	31 c0                	xor    %eax,%eax
    30ca:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
    30d1:	00 
    30d2:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    30d6:	48 83 e8 10          	sub    $0x10,%rax
    30da:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    30de:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    30e2:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    30e6:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    30ed:	00 00 
    30ef:	74 05                	je     30f6 <_ZNSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE12from_promiseERS3_+0x4b>
    30f1:	e8 9a f1 ff ff       	callq  2290 <__stack_chk_fail@plt>
    30f6:	c9                   	leaveq 
    30f7:	c3                   	retq   

00000000000030f8 <_ZN9GeneratorImEC1ENSt7__n486116coroutine_handleINS0_12promise_typeEEE>:
    30f8:	f3 0f 1e fa          	endbr64 
    30fc:	55                   	push   %rbp
    30fd:	48 89 e5             	mov    %rsp,%rbp
    3100:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    3104:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    3108:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    310c:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
    3110:	48 89 10             	mov    %rdx,(%rax)
    3113:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3117:	c6 40 08 00          	movb   $0x0,0x8(%rax)
    311b:	90                   	nop
    311c:	5d                   	pop    %rbp
    311d:	c3                   	retq   

000000000000311e <_ZN9GeneratorImE4fillEv>:
    311e:	f3 0f 1e fa          	endbr64 
    3122:	55                   	push   %rbp
    3123:	48 89 e5             	mov    %rsp,%rbp
    3126:	53                   	push   %rbx
    3127:	48 83 ec 28          	sub    $0x28,%rsp
    312b:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    312f:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    3136:	00 00 
    3138:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    313c:	31 c0                	xor    %eax,%eax
    313e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    3142:	0f b6 40 08          	movzbl 0x8(%rax),%eax
    3146:	83 f0 01             	xor    $0x1,%eax
    3149:	84 c0                	test   %al,%al
    314b:	74 7b                	je     31c8 <_ZN9GeneratorImE4fillEv+0xaa>
    314d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    3151:	48 89 c7             	mov    %rax,%rdi
    3154:	e8 a9 fb ff ff       	callq  2d02 <_ZNKSt7__n486116coroutine_handleIvEclEv>
    3159:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    315d:	48 89 c7             	mov    %rax,%rdi
    3160:	e8 7f 00 00 00       	callq  31e4 <_ZNKSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE7promiseEv>
    3165:	48 83 c0 08          	add    $0x8,%rax
    3169:	48 89 c7             	mov    %rax,%rdi
    316c:	e8 cb fc ff ff       	callq  2e3c <_ZNKSt15__exception_ptr13exception_ptrcvbEv>
    3171:	84 c0                	test   %al,%al
    3173:	74 2b                	je     31a0 <_ZN9GeneratorImE4fillEv+0x82>
    3175:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    3179:	48 89 c7             	mov    %rax,%rdi
    317c:	e8 63 00 00 00       	callq  31e4 <_ZNKSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE7promiseEv>
    3181:	48 8d 50 08          	lea    0x8(%rax),%rdx
    3185:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    3189:	48 89 d6             	mov    %rdx,%rsi
    318c:	48 89 c7             	mov    %rax,%rdi
    318f:	e8 3c f0 ff ff       	callq  21d0 <_ZNSt15__exception_ptr13exception_ptrC1ERKS0_@plt>
    3194:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    3198:	48 89 c7             	mov    %rax,%rdi
    319b:	e8 d0 f0 ff ff       	callq  2270 <_ZSt17rethrow_exceptionNSt15__exception_ptr13exception_ptrE@plt>
    31a0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    31a4:	c6 40 08 01          	movb   $0x1,0x8(%rax)
    31a8:	eb 1e                	jmp    31c8 <_ZN9GeneratorImE4fillEv+0xaa>
    31aa:	f3 0f 1e fa          	endbr64 
    31ae:	48 89 c3             	mov    %rax,%rbx
    31b1:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    31b5:	48 89 c7             	mov    %rax,%rdi
    31b8:	e8 53 f1 ff ff       	callq  2310 <_ZNSt15__exception_ptr13exception_ptrD1Ev@plt>
    31bd:	48 89 d8             	mov    %rbx,%rax
    31c0:	48 89 c7             	mov    %rax,%rdi
    31c3:	e8 38 f1 ff ff       	callq  2300 <_Unwind_Resume@plt>
    31c8:	90                   	nop
    31c9:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    31cd:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    31d4:	00 00 
    31d6:	74 05                	je     31dd <_ZN9GeneratorImE4fillEv+0xbf>
    31d8:	e8 b3 f0 ff ff       	callq  2290 <__stack_chk_fail@plt>
    31dd:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    31e1:	c9                   	leaveq 
    31e2:	c3                   	retq   
    31e3:	90                   	nop

00000000000031e4 <_ZNKSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE7promiseEv>:
    31e4:	f3 0f 1e fa          	endbr64 
    31e8:	55                   	push   %rbp
    31e9:	48 89 e5             	mov    %rsp,%rbp
    31ec:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    31f0:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    31f4:	48 8b 00             	mov    (%rax),%rax
    31f7:	48 83 c0 10          	add    $0x10,%rax
    31fb:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    31ff:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3203:	5d                   	pop    %rbp
    3204:	c3                   	retq   

0000000000003205 <_ZSt4moveIRmEONSt16remove_referenceIT_E4typeEOS2_>:
    3205:	f3 0f 1e fa          	endbr64 
    3209:	55                   	push   %rbp
    320a:	48 89 e5             	mov    %rsp,%rbp
    320d:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    3211:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3215:	5d                   	pop    %rbp
    3216:	c3                   	retq   
    3217:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
    321e:	00 00 

0000000000003220 <__libc_csu_init>:
    3220:	f3 0f 1e fa          	endbr64 
    3224:	41 57                	push   %r15
    3226:	4c 8d 3d 7b 2a 00 00 	lea    0x2a7b(%rip),%r15        # 5ca8 <__frame_dummy_init_array_entry>
    322d:	41 56                	push   %r14
    322f:	49 89 d6             	mov    %rdx,%r14
    3232:	41 55                	push   %r13
    3234:	49 89 f5             	mov    %rsi,%r13
    3237:	41 54                	push   %r12
    3239:	41 89 fc             	mov    %edi,%r12d
    323c:	55                   	push   %rbp
    323d:	48 8d 2d 74 2a 00 00 	lea    0x2a74(%rip),%rbp        # 5cb8 <__do_global_dtors_aux_fini_array_entry>
    3244:	53                   	push   %rbx
    3245:	4c 29 fd             	sub    %r15,%rbp
    3248:	48 83 ec 08          	sub    $0x8,%rsp
    324c:	e8 af ed ff ff       	callq  2000 <_init>
    3251:	48 c1 fd 03          	sar    $0x3,%rbp
    3255:	74 1f                	je     3276 <__libc_csu_init+0x56>
    3257:	31 db                	xor    %ebx,%ebx
    3259:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    3260:	4c 89 f2             	mov    %r14,%rdx
    3263:	4c 89 ee             	mov    %r13,%rsi
    3266:	44 89 e7             	mov    %r12d,%edi
    3269:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    326d:	48 83 c3 01          	add    $0x1,%rbx
    3271:	48 39 dd             	cmp    %rbx,%rbp
    3274:	75 ea                	jne    3260 <__libc_csu_init+0x40>
    3276:	48 83 c4 08          	add    $0x8,%rsp
    327a:	5b                   	pop    %rbx
    327b:	5d                   	pop    %rbp
    327c:	41 5c                	pop    %r12
    327e:	41 5d                	pop    %r13
    3280:	41 5e                	pop    %r14
    3282:	41 5f                	pop    %r15
    3284:	c3                   	retq   
    3285:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    328c:	00 00 00 00 

0000000000003290 <__libc_csu_fini>:
    3290:	f3 0f 1e fa          	endbr64 
    3294:	c3                   	retq   

Disassembly of section .fini:

0000000000003298 <_fini>:
    3298:	f3 0f 1e fa          	endbr64 
    329c:	48 83 ec 08          	sub    $0x8,%rsp
    32a0:	48 83 c4 08          	add    $0x8,%rsp
    32a4:	c3                   	retq   
