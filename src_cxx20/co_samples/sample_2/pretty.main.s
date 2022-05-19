
co_samples_sample_2:     file format elf64-x86-64


Disassembly of section .init:

0000000000002000 <_init>:
_init():
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

00000000000021b0 <std::ostream::operator<<(unsigned long)@plt>:
    21b0:	f3 0f 1e fa          	endbr64 
    21b4:	f2 ff 25 3d 3d 00 00 	bnd jmpq *0x3d3d(%rip)        # 5ef8 <std::ostream::operator<<(unsigned long)@GLIBCXX_3.4>
    21bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000021c0 <std::__exception_ptr::exception_ptr::swap(std::__exception_ptr::exception_ptr&)@plt>:
    21c0:	f3 0f 1e fa          	endbr64 
    21c4:	f2 ff 25 35 3d 00 00 	bnd jmpq *0x3d35(%rip)        # 5f00 <std::__exception_ptr::exception_ptr::swap(std::__exception_ptr::exception_ptr&)@CXXABI_1.3.3>
    21cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000021d0 <std::__exception_ptr::exception_ptr::exception_ptr(std::__exception_ptr::exception_ptr const&)@plt>:
    21d0:	f3 0f 1e fa          	endbr64 
    21d4:	f2 ff 25 2d 3d 00 00 	bnd jmpq *0x3d2d(%rip)        # 5f08 <std::__exception_ptr::exception_ptr::exception_ptr(std::__exception_ptr::exception_ptr const&)@CXXABI_1.3.3>
    21db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000021e0 <std::__exception_ptr::exception_ptr::exception_ptr()@plt>:
    21e0:	f3 0f 1e fa          	endbr64 
    21e4:	f2 ff 25 25 3d 00 00 	bnd jmpq *0x3d25(%rip)        # 5f10 <std::__exception_ptr::exception_ptr::exception_ptr()@CXXABI_1.3.3>
    21eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000021f0 <std::runtime_error::runtime_error(char const*)@plt>:
    21f0:	f3 0f 1e fa          	endbr64 
    21f4:	f2 ff 25 1d 3d 00 00 	bnd jmpq *0x3d1d(%rip)        # 5f18 <std::runtime_error::runtime_error(char const*)@GLIBCXX_3.4.21>
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

0000000000002240 <operator delete(void*)@plt>:
    2240:	f3 0f 1e fa          	endbr64 
    2244:	f2 ff 25 f5 3c 00 00 	bnd jmpq *0x3cf5(%rip)        # 5f40 <operator delete(void*)@GLIBCXX_3.4>
    224b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002250 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>:
    2250:	f3 0f 1e fa          	endbr64 
    2254:	f2 ff 25 ed 3c 00 00 	bnd jmpq *0x3ced(%rip)        # 5f48 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@GLIBCXX_3.4>
    225b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002260 <operator new(unsigned long)@plt>:
    2260:	f3 0f 1e fa          	endbr64 
    2264:	f2 ff 25 e5 3c 00 00 	bnd jmpq *0x3ce5(%rip)        # 5f50 <operator new(unsigned long)@GLIBCXX_3.4>
    226b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002270 <std::rethrow_exception(std::__exception_ptr::exception_ptr)@plt>:
    2270:	f3 0f 1e fa          	endbr64 
    2274:	f2 ff 25 dd 3c 00 00 	bnd jmpq *0x3cdd(%rip)        # 5f58 <std::rethrow_exception(std::__exception_ptr::exception_ptr)@CXXABI_1.3.3>
    227b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002280 <std::current_exception()@plt>:
    2280:	f3 0f 1e fa          	endbr64 
    2284:	f2 ff 25 d5 3c 00 00 	bnd jmpq *0x3cd5(%rip)        # 5f60 <std::current_exception()@CXXABI_1.3.3>
    228b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002290 <__stack_chk_fail@plt>:
    2290:	f3 0f 1e fa          	endbr64 
    2294:	f2 ff 25 cd 3c 00 00 	bnd jmpq *0x3ccd(%rip)        # 5f68 <__stack_chk_fail@GLIBC_2.4>
    229b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022a0 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char)@plt>:
    22a0:	f3 0f 1e fa          	endbr64 
    22a4:	f2 ff 25 c5 3c 00 00 	bnd jmpq *0x3cc5(%rip)        # 5f70 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char)@GLIBCXX_3.4>
    22ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022b0 <__cxa_rethrow@plt>:
    22b0:	f3 0f 1e fa          	endbr64 
    22b4:	f2 ff 25 bd 3c 00 00 	bnd jmpq *0x3cbd(%rip)        # 5f78 <__cxa_rethrow@CXXABI_1.3>
    22bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022c0 <std::ios_base::Init::Init()@plt>:
    22c0:	f3 0f 1e fa          	endbr64 
    22c4:	f2 ff 25 b5 3c 00 00 	bnd jmpq *0x3cb5(%rip)        # 5f80 <std::ios_base::Init::Init()@GLIBCXX_3.4>
    22cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022d0 <__cxa_end_catch@plt>:
    22d0:	f3 0f 1e fa          	endbr64 
    22d4:	f2 ff 25 ad 3c 00 00 	bnd jmpq *0x3cad(%rip)        # 5f88 <__cxa_end_catch@CXXABI_1.3>
    22db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022e0 <__cxa_throw@plt>:
    22e0:	f3 0f 1e fa          	endbr64 
    22e4:	f2 ff 25 a5 3c 00 00 	bnd jmpq *0x3ca5(%rip)        # 5f90 <__cxa_throw@CXXABI_1.3>
    22eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000022f0 <std::ostream::operator<<(int)@plt>:
    22f0:	f3 0f 1e fa          	endbr64 
    22f4:	f2 ff 25 9d 3c 00 00 	bnd jmpq *0x3c9d(%rip)        # 5f98 <std::ostream::operator<<(int)@GLIBCXX_3.4>
    22fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002300 <_Unwind_Resume@plt>:
    2300:	f3 0f 1e fa          	endbr64 
    2304:	f2 ff 25 95 3c 00 00 	bnd jmpq *0x3c95(%rip)        # 5fa0 <_Unwind_Resume@GCC_3.0>
    230b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000002310 <std::__exception_ptr::exception_ptr::~exception_ptr()@plt>:
    2310:	f3 0f 1e fa          	endbr64 
    2314:	f2 ff 25 8d 3c 00 00 	bnd jmpq *0x3c8d(%rip)        # 5fa8 <std::__exception_ptr::exception_ptr::~exception_ptr()@CXXABI_1.3.3>
    231b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

0000000000002320 <_start>:
_start():
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
    2341:	48 8d 3d 1f 09 00 00 	lea    0x91f(%rip),%rdi        # 2c67 <main>
    2348:	ff 15 82 3c 00 00    	callq  *0x3c82(%rip)        # 5fd0 <__libc_start_main@GLIBC_2.2.5>
    234e:	f4                   	hlt    
    234f:	90                   	nop

0000000000002350 <deregister_tm_clones>:
deregister_tm_clones():
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
register_tm_clones():
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
__do_global_dtors_aux():
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
frame_dummy():
    2400:	f3 0f 1e fa          	endbr64 
    2404:	e9 77 ff ff ff       	jmpq   2380 <register_tm_clones>

0000000000002409 <std::__n4861::__dummy_resume_destroy()>:
_ZNSt7__n486122__dummy_resume_destroyEv():
/usr/include/c++/10/coroutine:222
  struct noop_coroutine_promise
  {
  };

  void __dummy_resume_destroy() __attribute__((__weak__));
  void __dummy_resume_destroy() {}
    2409:	f3 0f 1e fa          	endbr64 
    240d:	55                   	push   %rbp
    240e:	48 89 e5             	mov    %rsp,%rbp
    2411:	90                   	nop
    2412:	5d                   	pop    %rbp
    2413:	c3                   	retq   

0000000000002414 <fibonacci_sequence(unsigned int)>:
_Z18fibonacci_sequencej():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
      full_ = true;
    }
  }
};

Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2414:	f3 0f 1e fa          	endbr64 
    2418:	55                   	push   %rbp
    2419:	48 89 e5             	mov    %rsp,%rbp
    241c:	53                   	push   %rbx
    241d:	48 83 ec 38          	sub    $0x38,%rsp
    2421:	48 89 7d c8          	mov    %rdi,-0x38(%rbp)
    2425:	89 75 c4             	mov    %esi,-0x3c(%rbp)
    2428:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    242f:	00 00 
    2431:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    2435:	31 c0                	xor    %eax,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
    uint64_t s = a + b;
    co_yield s;
    a = b;
    b = s;
  }
}
    2437:	48 c7 45 e0 00 00 00 	movq   $0x0,-0x20(%rbp)
    243e:	00 
    243f:	c6 45 df 00          	movb   $0x0,-0x21(%rbp)
    2443:	c6 45 de 00          	movb   $0x0,-0x22(%rbp)
    2447:	b8 70 00 00 00       	mov    $0x70,%eax
    244c:	48 89 c7             	mov    %rax,%rdi
    244f:	e8 0c fe ff ff       	callq  2260 <operator new(unsigned long)@plt>
    2454:	48 89 45 e0          	mov    %rax,-0x20(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2458:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    245c:	c6 40 20 01          	movb   $0x1,0x20(%rax)
    2460:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2464:	48 8d 15 ee 00 00 00 	lea    0xee(%rip),%rdx        # 2559 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)>
    246b:	48 89 10             	mov    %rdx,(%rax)
    246e:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2472:	48 8d 15 f1 05 00 00 	lea    0x5f1(%rip),%rdx        # 2a6a <_Z18fibonacci_sequencej.destroy(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)>
    2479:	48 89 50 08          	mov    %rdx,0x8(%rax)
    247d:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2481:	8b 55 c4             	mov    -0x3c(%rbp),%edx
    2484:	89 50 30             	mov    %edx,0x30(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    2487:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    248b:	8b 40 30             	mov    0x30(%rax),%eax
    248e:	89 c2                	mov    %eax,%edx
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2490:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2494:	48 89 50 10          	mov    %rdx,0x10(%rax)
    2498:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    249c:	48 83 c0 18          	add    $0x18,%rax
    24a0:	48 89 c7             	mov    %rax,%rdi
    24a3:	e8 38 fd ff ff       	callq  21e0 <std::__exception_ptr::exception_ptr::exception_ptr()@plt>
    24a8:	c6 45 df 01          	movb   $0x1,-0x21(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    24ac:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    24b0:	48 8d 50 10          	lea    0x10(%rax),%rdx
    24b4:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    24b8:	48 89 d6             	mov    %rdx,%rsi
    24bb:	48 89 c7             	mov    %rax,%rdi
    24be:	e8 d3 0a 00 00       	callq  2f96 <Generator<unsigned long>::promise_type::get_return_object()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    24c3:	c6 45 de 01          	movb   $0x1,-0x22(%rbp)
    24c7:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    24cb:	66 c7 40 22 00 00    	movw   $0x0,0x22(%rax)
    24d1:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    24d5:	48 89 c7             	mov    %rax,%rdi
    24d8:	e8 7c 00 00 00       	callq  2559 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    24dd:	eb 5c                	jmp    253b <fibonacci_sequence(unsigned int)+0x127>
    24df:	f3 0f 1e fa          	endbr64 
    24e3:	48 89 c7             	mov    %rax,%rdi
    24e6:	e8 15 fd ff ff       	callq  2200 <__cxa_begin_catch@plt>
    24eb:	80 7d de 00          	cmpb   $0x0,-0x22(%rbp)
    24ef:	74 0c                	je     24fd <fibonacci_sequence(unsigned int)+0xe9>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 3)
    24f1:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    24f5:	48 89 c7             	mov    %rax,%rdi
    24f8:	e8 d1 0a 00 00       	callq  2fce <Generator<unsigned long>::~Generator()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 5)
    24fd:	80 7d df 00          	cmpb   $0x0,-0x21(%rbp)
    2501:	74 10                	je     2513 <fibonacci_sequence(unsigned int)+0xff>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 6)
    2503:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2507:	48 83 c0 10          	add    $0x10,%rax
    250b:	48 89 c7             	mov    %rax,%rdi
    250e:	e8 4d 09 00 00       	callq  2e60 <Generator<unsigned long>::promise_type::~promise_type()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 8)
    2513:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2517:	48 89 c7             	mov    %rax,%rdi
    251a:	e8 21 fd ff ff       	callq  2240 <operator delete(void*)@plt>
    251f:	e8 8c fd ff ff       	callq  22b0 <__cxa_rethrow@plt>
    2524:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
    2528:	48 89 c3             	mov    %rax,%rbx
    252b:	e8 a0 fd ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2530:	48 89 d8             	mov    %rbx,%rax
    2533:	48 89 c7             	mov    %rax,%rdi
    2536:	e8 c5 fd ff ff       	callq  2300 <_Unwind_Resume@plt>
    253b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    253f:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    2546:	00 00 
    2548:	74 05                	je     254f <fibonacci_sequence(unsigned int)+0x13b>
    254a:	e8 41 fd ff ff       	callq  2290 <__stack_chk_fail@plt>
    254f:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    2553:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    2557:	c9                   	leaveq 
    2558:	c3                   	retq   

0000000000002559 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)>:
_Z29_Z18fibonacci_sequencej.actorPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
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
    2589:	74 35                	je     25c0 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x67>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 1)
    258b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    258f:	0f b7 40 22          	movzwl 0x22(%rax),%eax
    2593:	0f b7 c0             	movzwl %ax,%eax
    2596:	83 f8 0b             	cmp    $0xb,%eax
    2599:	77 23                	ja     25be <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x65>
    259b:	89 c0                	mov    %eax,%eax
    259d:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    25a4:	00 
    25a5:	48 8d 05 8c 1a 00 00 	lea    0x1a8c(%rip),%rax        # 4038 <_IO_stdin_used+0x38>
    25ac:	8b 04 02             	mov    (%rdx,%rax,1),%eax
    25af:	48 98                	cltq   
    25b1:	48 8d 15 80 1a 00 00 	lea    0x1a80(%rip),%rdx        # 4038 <_IO_stdin_used+0x38>
    25b8:	48 01 d0             	add    %rdx,%rax
    25bb:	3e ff e0             	notrack jmpq *%rax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 1)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    25be:	0f 0b                	ud2    
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 2)
}
    25c0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    25c4:	0f b7 40 22          	movzwl 0x22(%rax),%eax
    25c8:	0f b7 c0             	movzwl %ax,%eax
    25cb:	83 f8 0a             	cmp    $0xa,%eax
    25ce:	77 68                	ja     2638 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0xdf>
    25d0:	89 c0                	mov    %eax,%eax
    25d2:	48 8d 14 85 00 00 00 	lea    0x0(,%rax,4),%rdx
    25d9:	00 
    25da:	48 8d 05 87 1a 00 00 	lea    0x1a87(%rip),%rax        # 4068 <_IO_stdin_used+0x68>
    25e1:	8b 04 02             	mov    (%rdx,%rax,1),%eax
    25e4:	48 98                	cltq   
    25e6:	48 8d 15 7b 1a 00 00 	lea    0x1a7b(%rip),%rdx        # 4068 <_IO_stdin_used+0x68>
    25ed:	48 01 d0             	add    %rdx,%rax
    25f0:	3e ff e0             	notrack jmpq *%rax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
    25f3:	48 8b 5d d8          	mov    -0x28(%rbp),%rbx
    25f7:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    25fb:	48 89 c7             	mov    %rax,%rdi
    25fe:	e8 ea 09 00 00       	callq  2fed <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::from_address(void*)>
    2603:	48 89 43 28          	mov    %rax,0x28(%rbx)
    2607:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    260b:	c6 40 34 00          	movb   $0x0,0x34(%rax)
    260f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2613:	48 83 c0 10          	add    $0x10,%rax
    2617:	48 89 c7             	mov    %rax,%rdi
    261a:	e8 f1 08 00 00       	callq  2f10 <Generator<unsigned long>::promise_type::initial_suspend()>
    261f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2623:	48 83 c0 35          	add    $0x35,%rax
    2627:	48 89 c7             	mov    %rax,%rdi
    262a:	e8 41 07 00 00       	callq  2d70 <std::__n4861::suspend_always::await_ready() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    262f:	83 f0 01             	xor    $0x1,%eax
    2632:	84 c0                	test   %al,%al
    2634:	75 04                	jne    263a <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0xe1>
    2636:	eb 31                	jmp    2669 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x110>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 7)
    2638:	0f 0b                	ud2    
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 12)
    263a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    263e:	66 c7 40 22 02 00    	movw   $0x2,0x22(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 12)
}
    2644:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2648:	48 8d 50 35          	lea    0x35(%rax),%rdx
    264c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2650:	48 8b 40 28          	mov    0x28(%rax),%rax
    2654:	48 89 c6             	mov    %rax,%rsi
    2657:	48 89 d7             	mov    %rdx,%rdi
    265a:	e8 25 07 00 00       	callq  2d84 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 12)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    265f:	e9 68 03 00 00       	jmpq   29cc <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x473>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
    2664:	e9 2f 03 00 00       	jmpq   2998 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x43f>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 14)
    2669:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    266d:	c6 40 34 01          	movb   $0x1,0x34(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 14)
}
    2671:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2675:	48 83 c0 35          	add    $0x35,%rax
    2679:	48 89 c7             	mov    %rax,%rdi
    267c:	e8 17 07 00 00       	callq  2d98 <std::__n4861::suspend_always::await_resume() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 14)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2681:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2685:	8b 40 30             	mov    0x30(%rax),%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:76 (discriminator 14)
  if (n == 0)
    2688:	85 c0                	test   %eax,%eax
    268a:	75 15                	jne    26a1 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x148>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:78
    co_return;
    268c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2690:	48 83 c0 10          	add    $0x10,%rax
    2694:	48 89 c7             	mov    %rax,%rdi
    2697:	e8 e8 07 00 00       	callq  2e84 <Generator<unsigned long>::promise_type::return_void()>
    269c:	e9 89 02 00 00       	jmpq   292a <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x3d1>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    26a1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    26a5:	8b 40 30             	mov    0x30(%rax),%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:81
  if (n > 94)
    26a8:	83 f8 5e             	cmp    $0x5e,%eax
    26ab:	76 38                	jbe    26e5 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x18c>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:83
    throw std::runtime_error("斐波那契序列过大，元素将会溢出");
    26ad:	bf 10 00 00 00       	mov    $0x10,%edi
    26b2:	e8 59 fb ff ff       	callq  2210 <__cxa_allocate_exception@plt>
    26b7:	48 89 c3             	mov    %rax,%rbx
    26ba:	48 8d 35 47 19 00 00 	lea    0x1947(%rip),%rsi        # 4008 <_IO_stdin_used+0x8>
    26c1:	48 89 df             	mov    %rbx,%rdi
    26c4:	e8 27 fb ff ff       	callq  21f0 <std::runtime_error::runtime_error(char const*)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:83 (discriminator 2)
    26c9:	48 8b 05 e8 38 00 00 	mov    0x38e8(%rip),%rax        # 5fb8 <std::runtime_error::~runtime_error()@GLIBCXX_3.4>
    26d0:	48 89 c2             	mov    %rax,%rdx
    26d3:	48 8b 05 16 39 00 00 	mov    0x3916(%rip),%rax        # 5ff0 <typeinfo for std::runtime_error@GLIBCXX_3.4>
    26da:	48 89 c6             	mov    %rax,%rsi
    26dd:	48 89 df             	mov    %rbx,%rdi
    26e0:	e8 fb fb ff ff       	callq  22e0 <__cxa_throw@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    26e5:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    26e9:	c7 40 4c 00 00 00 00 	movl   $0x0,0x4c(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:86
  co_yield 0;
    26f0:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    26f4:	48 83 c0 10          	add    $0x10,%rax
    26f8:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
    26fc:	48 83 c2 4c          	add    $0x4c,%rdx
    2700:	48 89 d6             	mov    %rdx,%rsi
    2703:	48 89 c7             	mov    %rax,%rdi
    2706:	e8 9b 07 00 00       	callq  2ea6 <std::__n4861::suspend_always Generator<unsigned long>::promise_type::yield_value<int>(int&&)>
    270b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    270f:	48 83 c0 48          	add    $0x48,%rax
    2713:	48 89 c7             	mov    %rax,%rdi
    2716:	e8 55 06 00 00       	callq  2d70 <std::__n4861::suspend_always::await_ready() const>
    271b:	83 f0 01             	xor    $0x1,%eax
    271e:	84 c0                	test   %al,%al
    2720:	74 2f                	je     2751 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x1f8>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:86 (discriminator 1)
    2722:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2726:	66 c7 40 22 04 00    	movw   $0x4,0x22(%rax)
    272c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2730:	48 8d 50 48          	lea    0x48(%rax),%rdx
    2734:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2738:	48 8b 40 28          	mov    0x28(%rax),%rax
    273c:	48 89 c6             	mov    %rax,%rsi
    273f:	48 89 d7             	mov    %rdx,%rdi
    2742:	e8 3d 06 00 00       	callq  2d84 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>
    2747:	e9 80 02 00 00       	jmpq   29cc <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x473>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:86
    274c:	e9 47 02 00 00       	jmpq   2998 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x43f>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:86 (discriminator 2)
    2751:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2755:	48 83 c0 48          	add    $0x48,%rax
    2759:	48 89 c7             	mov    %rax,%rdi
    275c:	e8 37 06 00 00       	callq  2d98 <std::__n4861::suspend_always::await_resume() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 2)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2761:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2765:	8b 40 30             	mov    0x30(%rax),%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:88 (discriminator 2)
  if (n == 1)
    2768:	83 f8 01             	cmp    $0x1,%eax
    276b:	75 15                	jne    2782 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x229>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:78
    co_return;
    276d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2771:	48 83 c0 10          	add    $0x10,%rax
    2775:	48 89 c7             	mov    %rax,%rdi
    2778:	e8 07 07 00 00       	callq  2e84 <Generator<unsigned long>::promise_type::return_void()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:90
    co_return;
    277d:	e9 a8 01 00 00       	jmpq   292a <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x3d1>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    2782:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2786:	c7 40 54 01 00 00 00 	movl   $0x1,0x54(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:93
  co_yield 1;
    278d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2791:	48 83 c0 10          	add    $0x10,%rax
    2795:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
    2799:	48 83 c2 54          	add    $0x54,%rdx
    279d:	48 89 d6             	mov    %rdx,%rsi
    27a0:	48 89 c7             	mov    %rax,%rdi
    27a3:	e8 fe 06 00 00       	callq  2ea6 <std::__n4861::suspend_always Generator<unsigned long>::promise_type::yield_value<int>(int&&)>
    27a8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27ac:	48 83 c0 50          	add    $0x50,%rax
    27b0:	48 89 c7             	mov    %rax,%rdi
    27b3:	e8 b8 05 00 00       	callq  2d70 <std::__n4861::suspend_always::await_ready() const>
    27b8:	83 f0 01             	xor    $0x1,%eax
    27bb:	84 c0                	test   %al,%al
    27bd:	74 2f                	je     27ee <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x295>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:93 (discriminator 1)
    27bf:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27c3:	66 c7 40 22 06 00    	movw   $0x6,0x22(%rax)
    27c9:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27cd:	48 8d 50 50          	lea    0x50(%rax),%rdx
    27d1:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27d5:	48 8b 40 28          	mov    0x28(%rax),%rax
    27d9:	48 89 c6             	mov    %rax,%rsi
    27dc:	48 89 d7             	mov    %rdx,%rdi
    27df:	e8 a0 05 00 00       	callq  2d84 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>
    27e4:	e9 e3 01 00 00       	jmpq   29cc <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x473>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:93
    27e9:	e9 aa 01 00 00       	jmpq   2998 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x43f>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:93 (discriminator 2)
    27ee:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    27f2:	48 83 c0 50          	add    $0x50,%rax
    27f6:	48 89 c7             	mov    %rax,%rdi
    27f9:	e8 9a 05 00 00       	callq  2d98 <std::__n4861::suspend_always::await_resume() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 2)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    27fe:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2802:	8b 40 30             	mov    0x30(%rax),%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:95 (discriminator 2)
  if (n == 2)
    2805:	83 f8 02             	cmp    $0x2,%eax
    2808:	75 15                	jne    281f <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x2c6>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:78
    co_return;
    280a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    280e:	48 83 c0 10          	add    $0x10,%rax
    2812:	48 89 c7             	mov    %rax,%rdi
    2815:	e8 6a 06 00 00       	callq  2e84 <Generator<unsigned long>::promise_type::return_void()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:97
    co_return;
    281a:	e9 0b 01 00 00       	jmpq   292a <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x3d1>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:100
  uint64_t a = 0;
    281f:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2823:	48 c7 40 38 00 00 00 	movq   $0x0,0x38(%rax)
    282a:	00 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:101
  uint64_t b = 1;
    282b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    282f:	48 c7 40 40 01 00 00 	movq   $0x1,0x40(%rax)
    2836:	00 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:103
  for (unsigned i = 2; i < n; i++)
    2837:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    283b:	c7 40 58 02 00 00 00 	movl   $0x2,0x58(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 2)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2842:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2846:	8b 50 58             	mov    0x58(%rax),%edx
    2849:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    284d:	8b 40 30             	mov    0x30(%rax),%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:103 (discriminator 2)
  for (unsigned i = 2; i < n; i++)
    2850:	39 c2                	cmp    %eax,%edx
    2852:	0f 83 c2 00 00 00    	jae    291a <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x3c1>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2858:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    285c:	48 8b 50 38          	mov    0x38(%rax),%rdx
    2860:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2864:	48 8b 40 40          	mov    0x40(%rax),%rax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:105
    uint64_t s = a + b;
    2868:	48 01 c2             	add    %rax,%rdx
    286b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    286f:	48 89 50 60          	mov    %rdx,0x60(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:106
    co_yield s;
    2873:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2877:	48 83 c0 10          	add    $0x10,%rax
    287b:	48 8b 55 d8          	mov    -0x28(%rbp),%rdx
    287f:	48 83 c2 60          	add    $0x60,%rdx
    2883:	48 89 d6             	mov    %rdx,%rsi
    2886:	48 89 c7             	mov    %rax,%rdi
    2889:	e8 4e 06 00 00       	callq  2edc <std::__n4861::suspend_always Generator<unsigned long>::promise_type::yield_value<unsigned long&>(unsigned long&)>
    288e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2892:	48 83 c0 68          	add    $0x68,%rax
    2896:	48 89 c7             	mov    %rax,%rdi
    2899:	e8 d2 04 00 00       	callq  2d70 <std::__n4861::suspend_always::await_ready() const>
    289e:	83 f0 01             	xor    $0x1,%eax
    28a1:	84 c0                	test   %al,%al
    28a3:	74 2f                	je     28d4 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x37b>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:106 (discriminator 1)
    28a5:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28a9:	66 c7 40 22 08 00    	movw   $0x8,0x22(%rax)
    28af:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28b3:	48 8d 50 68          	lea    0x68(%rax),%rdx
    28b7:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28bb:	48 8b 40 28          	mov    0x28(%rax),%rax
    28bf:	48 89 c6             	mov    %rax,%rsi
    28c2:	48 89 d7             	mov    %rdx,%rdi
    28c5:	e8 ba 04 00 00       	callq  2d84 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>
    28ca:	e9 fd 00 00 00       	jmpq   29cc <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x473>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:106
    28cf:	e9 c4 00 00 00       	jmpq   2998 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x43f>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:106 (discriminator 2)
    28d4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28d8:	48 83 c0 68          	add    $0x68,%rax
    28dc:	48 89 c7             	mov    %rax,%rdi
    28df:	e8 b4 04 00 00       	callq  2d98 <std::__n4861::suspend_always::await_resume() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 2)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    28e4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28e8:	48 8b 50 40          	mov    0x40(%rax),%rdx
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:107 (discriminator 2)
    a = b;
    28ec:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28f0:	48 89 50 38          	mov    %rdx,0x38(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 2)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    28f4:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    28f8:	48 8b 50 60          	mov    0x60(%rax),%rdx
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:108 (discriminator 2)
    b = s;
    28fc:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2900:	48 89 50 40          	mov    %rdx,0x40(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 2)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2904:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2908:	8b 40 58             	mov    0x58(%rax),%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:103 (discriminator 2)
  for (unsigned i = 2; i < n; i++)
    290b:	8d 50 01             	lea    0x1(%rax),%edx
    290e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2912:	89 50 58             	mov    %edx,0x58(%rax)
    2915:	e9 28 ff ff ff       	jmpq   2842 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x2e9>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:78
    co_return;
    291a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    291e:	48 83 c0 10          	add    $0x10,%rax
    2922:	48 89 c7             	mov    %rax,%rdi
    2925:	e8 5a 05 00 00       	callq  2e84 <Generator<unsigned long>::promise_type::return_void()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    292a:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    292e:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
    2935:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2939:	48 83 c0 10          	add    $0x10,%rax
    293d:	48 89 c7             	mov    %rax,%rdi
    2940:	e8 41 06 00 00       	callq  2f86 <Generator<unsigned long>::promise_type::final_suspend()>
    2945:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2949:	48 83 c0 69          	add    $0x69,%rax
    294d:	48 89 c7             	mov    %rax,%rdi
    2950:	e8 1b 04 00 00       	callq  2d70 <std::__n4861::suspend_always::await_ready() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2955:	83 f0 01             	xor    $0x1,%eax
    2958:	84 c0                	test   %al,%al
    295a:	74 29                	je     2985 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x42c>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 16)
    295c:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2960:	66 c7 40 22 0a 00    	movw   $0xa,0x22(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 16)
}
    2966:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    296a:	48 8d 50 69          	lea    0x69(%rax),%rdx
    296e:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2972:	48 8b 40 28          	mov    0x28(%rax),%rax
    2976:	48 89 c6             	mov    %rax,%rsi
    2979:	48 89 d7             	mov    %rdx,%rdi
    297c:	e8 03 04 00 00       	callq  2d84 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 16)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2981:	eb 49                	jmp    29cc <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x473>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
    2983:	eb 13                	jmp    2998 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x43f>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    2985:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2989:	48 83 c0 69          	add    $0x69,%rax
    298d:	48 89 c7             	mov    %rax,%rdi
    2990:	e8 03 04 00 00       	callq  2d98 <std::__n4861::suspend_always::await_resume() const>
    2995:	eb 01                	jmp    2998 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x43f>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2997:	90                   	nop
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 3)
}
    2998:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    299c:	48 83 c0 10          	add    $0x10,%rax
    29a0:	48 89 c7             	mov    %rax,%rdi
    29a3:	e8 b8 04 00 00       	callq  2e60 <Generator<unsigned long>::promise_type::~promise_type()>
    29a8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    29ac:	0f b6 40 20          	movzbl 0x20(%rax),%eax
    29b0:	0f b6 c0             	movzbl %al,%eax
    29b3:	85 c0                	test   %eax,%eax
    29b5:	0f 84 91 00 00 00    	je     2a4c <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x4f3>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 5)
    29bb:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    29bf:	48 89 c7             	mov    %rax,%rdi
    29c2:	e8 79 f8 ff ff       	callq  2240 <operator delete(void*)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 5)
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    29c7:	e9 80 00 00 00       	jmpq   2a4c <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x4f3>
    29cc:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75 (discriminator 13)
    29d0:	eb 7a                	jmp    2a4c <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x4f3>
    29d2:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:83
    throw std::runtime_error("斐波那契序列过大，元素将会溢出");
    29d6:	49 89 c4             	mov    %rax,%r12
    29d9:	48 89 df             	mov    %rbx,%rdi
    29dc:	e8 3f f8 ff ff       	callq  2220 <__cxa_free_exception@plt>
    29e1:	4c 89 e0             	mov    %r12,%rax
    29e4:	eb 04                	jmp    29ea <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x491>
    29e6:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    29ea:	48 89 c7             	mov    %rax,%rdi
    29ed:	e8 0e f8 ff ff       	callq  2200 <__cxa_begin_catch@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    29f2:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    29f6:	0f b6 40 34          	movzbl 0x34(%rax),%eax
    29fa:	83 f0 01             	xor    $0x1,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    29fd:	84 c0                	test   %al,%al
    29ff:	74 05                	je     2a06 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x4ad>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 7)
    2a01:	e8 aa f8 ff ff       	callq  22b0 <__cxa_rethrow@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110 (discriminator 8)
    2a06:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2a0a:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
    2a11:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2a15:	66 c7 40 22 00 00    	movw   $0x0,0x22(%rax)
    2a1b:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    2a1f:	48 83 c0 10          	add    $0x10,%rax
    2a23:	48 89 c7             	mov    %rax,%rdi
    2a26:	e8 f5 04 00 00       	callq  2f20 <Generator<unsigned long>::promise_type::unhandled_exception()>
    2a2b:	e8 a0 f8 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2a30:	e9 f5 fe ff ff       	jmpq   292a <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x3d1>
    2a35:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
    2a39:	48 89 c3             	mov    %rax,%rbx
    2a3c:	e8 8f f8 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2a41:	48 89 d8             	mov    %rbx,%rax
    2a44:	48 89 c7             	mov    %rax,%rdi
    2a47:	e8 b4 f8 ff ff       	callq  2300 <_Unwind_Resume@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2a4c:	90                   	nop
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    2a4d:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2a51:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    2a58:	00 00 
    2a5a:	74 05                	je     2a61 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)+0x508>
    2a5c:	e8 2f f8 ff ff       	callq  2290 <__stack_chk_fail@plt>
    2a61:	48 83 c4 20          	add    $0x20,%rsp
    2a65:	5b                   	pop    %rbx
    2a66:	41 5c                	pop    %r12
    2a68:	5d                   	pop    %rbp
    2a69:	c3                   	retq   

0000000000002a6a <_Z18fibonacci_sequencej.destroy(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)>:
_Z31_Z18fibonacci_sequencej.destroyPZ18fibonacci_sequencejE29_Z18fibonacci_sequencej.frame():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
    2a6a:	f3 0f 1e fa          	endbr64 
    2a6e:	55                   	push   %rbp
    2a6f:	48 89 e5             	mov    %rsp,%rbp
    2a72:	48 83 ec 10          	sub    $0x10,%rsp
    2a76:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:75
Generator<uint64_t> fibonacci_sequence(unsigned n) {
    2a7a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2a7e:	0f b7 40 22          	movzwl 0x22(%rax),%eax
    2a82:	83 c8 01             	or     $0x1,%eax
    2a85:	89 c2                	mov    %eax,%edx
    2a87:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2a8b:	66 89 50 22          	mov    %dx,0x22(%rax)
    2a8f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2a93:	48 89 c7             	mov    %rax,%rdi
    2a96:	e8 be fa ff ff       	callq  2559 <_Z18fibonacci_sequencej.actor(fibonacci_sequence(unsigned int)::_Z18fibonacci_sequencej.frame*)>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:110
}
    2a9b:	c9                   	leaveq 
    2a9c:	c3                   	retq   

0000000000002a9d <run_coroutine()>:
_Z13run_coroutinev():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:112

int run_coroutine() {
    2a9d:	f3 0f 1e fa          	endbr64 
    2aa1:	55                   	push   %rbp
    2aa2:	48 89 e5             	mov    %rsp,%rbp
    2aa5:	41 54                	push   %r12
    2aa7:	53                   	push   %rbx
    2aa8:	48 83 ec 40          	sub    $0x40,%rsp
    2aac:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2ab3:	00 00 
    2ab5:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    2ab9:	31 c0                	xor    %eax,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:113
  int i = 1;
    2abb:	c7 45 bc 01 00 00 00 	movl   $0x1,-0x44(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:115
  try {
    auto gen = fibonacci_sequence(10);  //最大值94，避免 uint64_t 溢出
    2ac2:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2ac6:	be 0a 00 00 00       	mov    $0xa,%esi
    2acb:	48 89 c7             	mov    %rax,%rdi
    2ace:	e8 41 f9 ff ff       	callq  2414 <fibonacci_sequence(unsigned int)>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:117

    for (int j = 0; gen; j++)
    2ad3:	c7 45 b8 00 00 00 00 	movl   $0x0,-0x48(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:117 (discriminator 1)
    2ada:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2ade:	48 89 c7             	mov    %rax,%rdi
    2ae1:	e8 50 05 00 00       	callq  3036 <Generator<unsigned long>::operator bool()>
    2ae6:	84 c0                	test   %al,%al
    2ae8:	74 6a                	je     2b54 <run_coroutine()+0xb7>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:119
    {
      auto genRet = gen();
    2aea:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2aee:	48 89 c7             	mov    %rax,%rdi
    2af1:	e8 6e 05 00 00       	callq  3064 <Generator<unsigned long>::operator()()>
    2af6:	48 89 45 c0          	mov    %rax,-0x40(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:120
      std::cout << "fib(" << j << ")=" << genRet  << '\n';
    2afa:	48 8d 35 93 15 00 00 	lea    0x1593(%rip),%rsi        # 4094 <_IO_stdin_used+0x94>
    2b01:	48 8b 05 b8 34 00 00 	mov    0x34b8(%rip),%rax        # 5fc0 <std::cout@GLIBCXX_3.4>
    2b08:	48 89 c7             	mov    %rax,%rdi
    2b0b:	e8 40 f7 ff ff       	callq  2250 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:120 (discriminator 1)
    2b10:	48 89 c2             	mov    %rax,%rdx
    2b13:	8b 45 b8             	mov    -0x48(%rbp),%eax
    2b16:	89 c6                	mov    %eax,%esi
    2b18:	48 89 d7             	mov    %rdx,%rdi
    2b1b:	e8 d0 f7 ff ff       	callq  22f0 <std::ostream::operator<<(int)@plt>
    2b20:	48 8d 35 72 15 00 00 	lea    0x1572(%rip),%rsi        # 4099 <_IO_stdin_used+0x99>
    2b27:	48 89 c7             	mov    %rax,%rdi
    2b2a:	e8 21 f7 ff ff       	callq  2250 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:120 (discriminator 2)
    2b2f:	48 89 c2             	mov    %rax,%rdx
    2b32:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
    2b36:	48 89 c6             	mov    %rax,%rsi
    2b39:	48 89 d7             	mov    %rdx,%rdi
    2b3c:	e8 6f f6 ff ff       	callq  21b0 <std::ostream::operator<<(unsigned long)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:120 (discriminator 3)
    2b41:	be 0a 00 00 00       	mov    $0xa,%esi
    2b46:	48 89 c7             	mov    %rax,%rdi
    2b49:	e8 52 f7 ff ff       	callq  22a0 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:117 (discriminator 3)
    for (int j = 0; gen; j++)
    2b4e:	83 45 b8 01          	addl   $0x1,-0x48(%rbp)
    2b52:	eb 86                	jmp    2ada <run_coroutine()+0x3d>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:115
    auto gen = fibonacci_sequence(10);  //最大值94，避免 uint64_t 溢出
    2b54:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2b58:	48 89 c7             	mov    %rax,%rdi
    2b5b:	e8 6e 04 00 00       	callq  2fce <Generator<unsigned long>::~Generator()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:130
    std::cerr << "发生了异常：" << ex.what() << '\n';
  } catch (...)
  {
    std::cerr << "未知异常\n";
  }
  return 0;
    2b60:	b8 00 00 00 00       	mov    $0x0,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:131
}
    2b65:	48 8b 4d e8          	mov    -0x18(%rbp),%rcx
    2b69:	64 48 2b 0c 25 28 00 	sub    %fs:0x28,%rcx
    2b70:	00 00 
    2b72:	0f 84 e6 00 00 00    	je     2c5e <run_coroutine()+0x1c1>
    2b78:	e9 dc 00 00 00       	jmpq   2c59 <run_coroutine()+0x1bc>
    2b7d:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:115
    auto gen = fibonacci_sequence(10);  //最大值94，避免 uint64_t 溢出
    2b81:	49 89 c4             	mov    %rax,%r12
    2b84:	48 89 d3             	mov    %rdx,%rbx
    2b87:	48 8d 45 d0          	lea    -0x30(%rbp),%rax
    2b8b:	48 89 c7             	mov    %rax,%rdi
    2b8e:	e8 3b 04 00 00       	callq  2fce <Generator<unsigned long>::~Generator()>
    2b93:	4c 89 e0             	mov    %r12,%rax
    2b96:	48 89 da             	mov    %rbx,%rdx
    2b99:	eb 04                	jmp    2b9f <run_coroutine()+0x102>
    2b9b:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:123
  } catch (const std::exception& ex)
    2b9f:	48 83 fa 01          	cmp    $0x1,%rdx
    2ba3:	75 5e                	jne    2c03 <run_coroutine()+0x166>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:123 (discriminator 1)
    2ba5:	48 89 c7             	mov    %rax,%rdi
    2ba8:	e8 53 f6 ff ff       	callq  2200 <__cxa_begin_catch@plt>
    2bad:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:125 (discriminator 1)
    std::cerr << "发生了异常：" << ex.what() << '\n';
    2bb1:	48 8d 35 e4 14 00 00 	lea    0x14e4(%rip),%rsi        # 409c <_IO_stdin_used+0x9c>
    2bb8:	48 8b 05 29 34 00 00 	mov    0x3429(%rip),%rax        # 5fe8 <std::cerr@GLIBCXX_3.4>
    2bbf:	48 89 c7             	mov    %rax,%rdi
    2bc2:	e8 89 f6 ff ff       	callq  2250 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>
    2bc7:	48 89 c3             	mov    %rax,%rbx
    2bca:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    2bce:	48 8b 00             	mov    (%rax),%rax
    2bd1:	48 83 c0 10          	add    $0x10,%rax
    2bd5:	48 8b 10             	mov    (%rax),%rdx
    2bd8:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    2bdc:	48 89 c7             	mov    %rax,%rdi
    2bdf:	ff d2                	callq  *%rdx
    2be1:	48 89 c6             	mov    %rax,%rsi
    2be4:	48 89 df             	mov    %rbx,%rdi
    2be7:	e8 64 f6 ff ff       	callq  2250 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>
    2bec:	be 0a 00 00 00       	mov    $0xa,%esi
    2bf1:	48 89 c7             	mov    %rax,%rdi
    2bf4:	e8 a7 f6 ff ff       	callq  22a0 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:123
  } catch (const std::exception& ex)
    2bf9:	e8 d2 f6 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2bfe:	e9 5d ff ff ff       	jmpq   2b60 <run_coroutine()+0xc3>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:126
  } catch (...)
    2c03:	48 89 c7             	mov    %rax,%rdi
    2c06:	e8 f5 f5 ff ff       	callq  2200 <__cxa_begin_catch@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:128
    std::cerr << "未知异常\n";
    2c0b:	48 8d 35 9d 14 00 00 	lea    0x149d(%rip),%rsi        # 40af <_IO_stdin_used+0xaf>
    2c12:	48 8b 05 cf 33 00 00 	mov    0x33cf(%rip),%rax        # 5fe8 <std::cerr@GLIBCXX_3.4>
    2c19:	48 89 c7             	mov    %rax,%rdi
    2c1c:	e8 2f f6 ff ff       	callq  2250 <std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:126
  } catch (...)
    2c21:	e8 aa f6 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2c26:	e9 35 ff ff ff       	jmpq   2b60 <run_coroutine()+0xc3>
    2c2b:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:123
  } catch (const std::exception& ex)
    2c2f:	48 89 c3             	mov    %rax,%rbx
    2c32:	e8 99 f6 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2c37:	48 89 d8             	mov    %rbx,%rax
    2c3a:	48 89 c7             	mov    %rax,%rdi
    2c3d:	e8 be f6 ff ff       	callq  2300 <_Unwind_Resume@plt>
    2c42:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:126
  } catch (...)
    2c46:	48 89 c3             	mov    %rax,%rbx
    2c49:	e8 82 f6 ff ff       	callq  22d0 <__cxa_end_catch@plt>
    2c4e:	48 89 d8             	mov    %rbx,%rax
    2c51:	48 89 c7             	mov    %rax,%rdi
    2c54:	e8 a7 f6 ff ff       	callq  2300 <_Unwind_Resume@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:131
}
    2c59:	e8 32 f6 ff ff       	callq  2290 <__stack_chk_fail@plt>
    2c5e:	48 83 c4 40          	add    $0x40,%rsp
    2c62:	5b                   	pop    %rbx
    2c63:	41 5c                	pop    %r12
    2c65:	5d                   	pop    %rbp
    2c66:	c3                   	retq   

0000000000002c67 <main>:
main():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:134
//TEST(run_coroutine, 1) { run_coroutine(); }

int main(int argc, char** argv) {
    2c67:	f3 0f 1e fa          	endbr64 
    2c6b:	55                   	push   %rbp
    2c6c:	48 89 e5             	mov    %rsp,%rbp
    2c6f:	48 83 ec 10          	sub    $0x10,%rsp
    2c73:	89 7d fc             	mov    %edi,-0x4(%rbp)
    2c76:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:135
  run_coroutine();
    2c7a:	e8 1e fe ff ff       	callq  2a9d <run_coroutine()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:144
//    std::cerr << "init fail with " << iRet << std::endl;
//  }
//  testing::InitGoogleTest(&argc, argv);
//  iRet = RUN_ALL_TESTS();
//  return iRet;
    2c7f:	b8 00 00 00 00       	mov    $0x0,%eax
    2c84:	c9                   	leaveq 
    2c85:	c3                   	retq   

0000000000002c86 <__static_initialization_and_destruction_0(int, int)>:
_Z41__static_initialization_and_destruction_0ii():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:144
    2c86:	f3 0f 1e fa          	endbr64 
    2c8a:	55                   	push   %rbp
    2c8b:	48 89 e5             	mov    %rsp,%rbp
    2c8e:	48 83 ec 10          	sub    $0x10,%rsp
    2c92:	89 7d fc             	mov    %edi,-0x4(%rbp)
    2c95:	89 75 f8             	mov    %esi,-0x8(%rbp)
    2c98:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
    2c9c:	75 32                	jne    2cd0 <__static_initialization_and_destruction_0(int, int)+0x4a>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:144 (discriminator 1)
    2c9e:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
    2ca5:	75 29                	jne    2cd0 <__static_initialization_and_destruction_0(int, int)+0x4a>
/usr/include/c++/10/iostream:74
  extern wostream wclog;	/// Linked to standard error (buffered)
#endif
  //@}

  // For construction of filebuffers for cout, cin, cerr, clog et. al.
  static ios_base::Init __ioinit;
    2ca7:	48 8d 3d 8b 33 00 00 	lea    0x338b(%rip),%rdi        # 6039 <std::__ioinit>
    2cae:	e8 0d f6 ff ff       	callq  22c0 <std::ios_base::Init::Init()@plt>
    2cb3:	48 8d 15 4e 33 00 00 	lea    0x334e(%rip),%rdx        # 6008 <__dso_handle>
    2cba:	48 8d 35 78 33 00 00 	lea    0x3378(%rip),%rsi        # 6039 <std::__ioinit>
    2cc1:	48 8b 05 30 33 00 00 	mov    0x3330(%rip),%rax        # 5ff8 <std::ios_base::Init::~Init()@GLIBCXX_3.4>
    2cc8:	48 89 c7             	mov    %rax,%rdi
    2ccb:	e8 60 f5 ff ff       	callq  2230 <__cxa_atexit@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:144
    2cd0:	90                   	nop
    2cd1:	c9                   	leaveq 
    2cd2:	c3                   	retq   

0000000000002cd3 <_GLOBAL__sub_I_main.cpp>:
_GLOBAL__sub_I_main.cpp():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:144
    2cd3:	f3 0f 1e fa          	endbr64 
    2cd7:	55                   	push   %rbp
    2cd8:	48 89 e5             	mov    %rsp,%rbp
    2cdb:	be ff ff 00 00       	mov    $0xffff,%esi
    2ce0:	bf 01 00 00 00       	mov    $0x1,%edi
    2ce5:	e8 9c ff ff ff       	callq  2c86 <__static_initialization_and_destruction_0(int, int)>
    2cea:	5d                   	pop    %rbp
    2ceb:	c3                   	retq   

0000000000002cec <std::__n4861::coroutine_handle<void>::done() const>:
_ZNKSt7__n486116coroutine_handleIvE4doneEv():
/usr/include/c++/10/coroutine:121
      bool done() const noexcept { return __builtin_coro_done(_M_fr_ptr); }
    2cec:	f3 0f 1e fa          	endbr64 
    2cf0:	55                   	push   %rbp
    2cf1:	48 89 e5             	mov    %rsp,%rbp
    2cf4:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2cf8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2cfc:	48 8b 00             	mov    (%rax),%rax
    2cff:	48 8b 00             	mov    (%rax),%rax
    2d02:	48 85 c0             	test   %rax,%rax
    2d05:	0f 94 c0             	sete   %al
    2d08:	5d                   	pop    %rbp
    2d09:	c3                   	retq   

0000000000002d0a <std::__n4861::coroutine_handle<void>::operator()() const>:
_ZNKSt7__n486116coroutine_handleIvEclEv():
/usr/include/c++/10/coroutine:124
      void operator()() const { resume(); }
    2d0a:	f3 0f 1e fa          	endbr64 
    2d0e:	55                   	push   %rbp
    2d0f:	48 89 e5             	mov    %rsp,%rbp
    2d12:	48 83 ec 10          	sub    $0x10,%rsp
    2d16:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d1a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2d1e:	48 89 c7             	mov    %rax,%rdi
    2d21:	e8 04 00 00 00       	callq  2d2a <std::__n4861::coroutine_handle<void>::resume() const>
    2d26:	90                   	nop
    2d27:	c9                   	leaveq 
    2d28:	c3                   	retq   
    2d29:	90                   	nop

0000000000002d2a <std::__n4861::coroutine_handle<void>::resume() const>:
_ZNKSt7__n486116coroutine_handleIvE6resumeEv():
/usr/include/c++/10/coroutine:126
      void resume() const { __builtin_coro_resume(_M_fr_ptr); }
    2d2a:	f3 0f 1e fa          	endbr64 
    2d2e:	55                   	push   %rbp
    2d2f:	48 89 e5             	mov    %rsp,%rbp
    2d32:	48 83 ec 10          	sub    $0x10,%rsp
    2d36:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d3a:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2d3e:	48 8b 00             	mov    (%rax),%rax
    2d41:	48 8b 10             	mov    (%rax),%rdx
    2d44:	48 89 c7             	mov    %rax,%rdi
    2d47:	ff d2                	callq  *%rdx
    2d49:	90                   	nop
    2d4a:	c9                   	leaveq 
    2d4b:	c3                   	retq   

0000000000002d4c <std::__n4861::coroutine_handle<void>::destroy() const>:
_ZNKSt7__n486116coroutine_handleIvE7destroyEv():
/usr/include/c++/10/coroutine:128
      void destroy() const { __builtin_coro_destroy(_M_fr_ptr); }
    2d4c:	f3 0f 1e fa          	endbr64 
    2d50:	55                   	push   %rbp
    2d51:	48 89 e5             	mov    %rsp,%rbp
    2d54:	48 83 ec 10          	sub    $0x10,%rsp
    2d58:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d5c:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2d60:	48 8b 00             	mov    (%rax),%rax
    2d63:	48 8b 50 08          	mov    0x8(%rax),%rdx
    2d67:	48 89 c7             	mov    %rax,%rdi
    2d6a:	ff d2                	callq  *%rdx
    2d6c:	90                   	nop
    2d6d:	c9                   	leaveq 
    2d6e:	c3                   	retq   
    2d6f:	90                   	nop

0000000000002d70 <std::__n4861::suspend_always::await_ready() const>:
_ZNKSt7__n486114suspend_always11await_readyEv():
/usr/include/c++/10/coroutine:276

  // 17.12.5 Trivial awaitables
  /// [coroutine.trivial.awaitables]
  struct suspend_always
  {
    constexpr bool await_ready() const noexcept { return false; }
    2d70:	f3 0f 1e fa          	endbr64 
    2d74:	55                   	push   %rbp
    2d75:	48 89 e5             	mov    %rsp,%rbp
    2d78:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d7c:	b8 00 00 00 00       	mov    $0x0,%eax
    2d81:	5d                   	pop    %rbp
    2d82:	c3                   	retq   
    2d83:	90                   	nop

0000000000002d84 <std::__n4861::suspend_always::await_suspend(std::__n4861::coroutine_handle<void>) const>:
_ZNKSt7__n486114suspend_always13await_suspendENS_16coroutine_handleIvEE():
/usr/include/c++/10/coroutine:278

    constexpr void await_suspend(coroutine_handle<>) const noexcept {}
    2d84:	f3 0f 1e fa          	endbr64 
    2d88:	55                   	push   %rbp
    2d89:	48 89 e5             	mov    %rsp,%rbp
    2d8c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2d90:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    2d94:	90                   	nop
    2d95:	5d                   	pop    %rbp
    2d96:	c3                   	retq   
    2d97:	90                   	nop

0000000000002d98 <std::__n4861::suspend_always::await_resume() const>:
_ZNKSt7__n486114suspend_always12await_resumeEv():
/usr/include/c++/10/coroutine:280

    constexpr void await_resume() const noexcept {}
    2d98:	f3 0f 1e fa          	endbr64 
    2d9c:	55                   	push   %rbp
    2d9d:	48 89 e5             	mov    %rsp,%rbp
    2da0:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2da4:	90                   	nop
    2da5:	5d                   	pop    %rbp
    2da6:	c3                   	retq   
    2da7:	90                   	nop

0000000000002da8 <std::__exception_ptr::exception_ptr::exception_ptr(std::__exception_ptr::exception_ptr&&)>:
_ZNSt15__exception_ptr13exception_ptrC2EOS0_():
/usr/include/c++/10/bits/exception_ptr.h:106
#if __cplusplus >= 201103L
      exception_ptr(nullptr_t) noexcept
      : _M_exception_object(0)
      { }

      exception_ptr(exception_ptr&& __o) noexcept
    2da8:	f3 0f 1e fa          	endbr64 
    2dac:	55                   	push   %rbp
    2dad:	48 89 e5             	mov    %rsp,%rbp
    2db0:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2db4:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
/usr/include/c++/10/bits/exception_ptr.h:107
      : _M_exception_object(__o._M_exception_object)
    2db8:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    2dbc:	48 8b 10             	mov    (%rax),%rdx
    2dbf:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2dc3:	48 89 10             	mov    %rdx,(%rax)
/usr/include/c++/10/bits/exception_ptr.h:108
      { __o._M_exception_object = 0; }
    2dc6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    2dca:	48 c7 00 00 00 00 00 	movq   $0x0,(%rax)
    2dd1:	90                   	nop
    2dd2:	5d                   	pop    %rbp
    2dd3:	c3                   	retq   

0000000000002dd4 <std::__exception_ptr::exception_ptr::operator=(std::__exception_ptr::exception_ptr&&)>:
_ZNSt15__exception_ptr13exception_ptraSEOS0_():
/usr/include/c++/10/bits/exception_ptr.h:123
      exception_ptr& 
      operator=(const exception_ptr&) _GLIBCXX_USE_NOEXCEPT;

#if __cplusplus >= 201103L
      exception_ptr& 
      operator=(exception_ptr&& __o) noexcept
    2dd4:	f3 0f 1e fa          	endbr64 
    2dd8:	55                   	push   %rbp
    2dd9:	48 89 e5             	mov    %rsp,%rbp
    2ddc:	48 83 ec 20          	sub    $0x20,%rsp
    2de0:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2de4:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    2de8:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2def:	00 00 
    2df1:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    2df5:	31 c0                	xor    %eax,%eax
/usr/include/c++/10/bits/exception_ptr.h:125
      {
        exception_ptr(static_cast<exception_ptr&&>(__o)).swap(*this);
    2df7:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
    2dfb:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2dff:	48 89 d6             	mov    %rdx,%rsi
    2e02:	48 89 c7             	mov    %rax,%rdi
    2e05:	e8 9e ff ff ff       	callq  2da8 <std::__exception_ptr::exception_ptr::exception_ptr(std::__exception_ptr::exception_ptr&&)>
    2e0a:	48 8b 55 e8          	mov    -0x18(%rbp),%rdx
    2e0e:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2e12:	48 89 d6             	mov    %rdx,%rsi
    2e15:	48 89 c7             	mov    %rax,%rdi
    2e18:	e8 a3 f3 ff ff       	callq  21c0 <std::__exception_ptr::exception_ptr::swap(std::__exception_ptr::exception_ptr&)@plt>
    2e1d:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2e21:	48 89 c7             	mov    %rax,%rdi
    2e24:	e8 e7 f4 ff ff       	callq  2310 <std::__exception_ptr::exception_ptr::~exception_ptr()@plt>
/usr/include/c++/10/bits/exception_ptr.h:126
        return *this;
    2e29:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
/usr/include/c++/10/bits/exception_ptr.h:127
      }
    2e2d:	48 8b 4d f8          	mov    -0x8(%rbp),%rcx
    2e31:	64 48 2b 0c 25 28 00 	sub    %fs:0x28,%rcx
    2e38:	00 00 
    2e3a:	74 05                	je     2e41 <std::__exception_ptr::exception_ptr::operator=(std::__exception_ptr::exception_ptr&&)+0x6d>
    2e3c:	e8 4f f4 ff ff       	callq  2290 <__stack_chk_fail@plt>
    2e41:	c9                   	leaveq 
    2e42:	c3                   	retq   
    2e43:	90                   	nop

0000000000002e44 <std::__exception_ptr::exception_ptr::operator bool() const>:
_ZNKSt15__exception_ptr13exception_ptrcvbEv():
/usr/include/c++/10/bits/exception_ptr.h:145
	__attribute__ ((__pure__));
      operator __safe_bool() const _GLIBCXX_USE_NOEXCEPT;
#endif

#if __cplusplus >= 201103L
      explicit operator bool() const
    2e44:	f3 0f 1e fa          	endbr64 
    2e48:	55                   	push   %rbp
    2e49:	48 89 e5             	mov    %rsp,%rbp
    2e4c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/usr/include/c++/10/bits/exception_ptr.h:146
      { return _M_exception_object; }
    2e50:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2e54:	48 8b 00             	mov    (%rax),%rax
    2e57:	48 85 c0             	test   %rax,%rax
    2e5a:	0f 95 c0             	setne  %al
    2e5d:	5d                   	pop    %rbp
    2e5e:	c3                   	retq   
    2e5f:	90                   	nop

0000000000002e60 <Generator<unsigned long>::promise_type::~promise_type()>:
_ZN9GeneratorImE12promise_typeD2Ev():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:22
  struct promise_type {  // 必要
    2e60:	f3 0f 1e fa          	endbr64 
    2e64:	55                   	push   %rbp
    2e65:	48 89 e5             	mov    %rsp,%rbp
    2e68:	48 83 ec 10          	sub    $0x10,%rsp
    2e6c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2e70:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2e74:	48 83 c0 08          	add    $0x8,%rax
    2e78:	48 89 c7             	mov    %rax,%rdi
    2e7b:	e8 90 f4 ff ff       	callq  2310 <std::__exception_ptr::exception_ptr::~exception_ptr()@plt>
    2e80:	90                   	nop
    2e81:	c9                   	leaveq 
    2e82:	c3                   	retq   
    2e83:	90                   	nop

0000000000002e84 <Generator<unsigned long>::promise_type::return_void()>:
_ZN9GeneratorImE12promise_type11return_voidEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:39
    void return_void() {}
    2e84:	f3 0f 1e fa          	endbr64 
    2e88:	55                   	push   %rbp
    2e89:	48 89 e5             	mov    %rsp,%rbp
    2e8c:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2e90:	90                   	nop
    2e91:	5d                   	pop    %rbp
    2e92:	c3                   	retq   

0000000000002e93 <int&& std::forward<int>(std::remove_reference<int>::type&)>:
_ZSt7forwardIiEOT_RNSt16remove_referenceIS0_E4typeE():
/usr/include/c++/10/bits/move.h:76
   *
   *  This function is used to implement "perfect forwarding".
   */
  template<typename _Tp>
    constexpr _Tp&&
    forward(typename std::remove_reference<_Tp>::type& __t) noexcept
    2e93:	f3 0f 1e fa          	endbr64 
    2e97:	55                   	push   %rbp
    2e98:	48 89 e5             	mov    %rsp,%rbp
    2e9b:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/usr/include/c++/10/bits/move.h:77
    { return static_cast<_Tp&&>(__t); }
    2e9f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2ea3:	5d                   	pop    %rbp
    2ea4:	c3                   	retq   
    2ea5:	90                   	nop

0000000000002ea6 <std::__n4861::suspend_always Generator<unsigned long>::promise_type::yield_value<int>(int&&)>:
_ZN9GeneratorImE12promise_type11yield_valueIiEENSt7__n486114suspend_alwaysEOT_():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:35
    std::suspend_always yield_value(From&& from) {
    2ea6:	f3 0f 1e fa          	endbr64 
    2eaa:	55                   	push   %rbp
    2eab:	48 89 e5             	mov    %rsp,%rbp
    2eae:	53                   	push   %rbx
    2eaf:	48 83 ec 18          	sub    $0x18,%rsp
    2eb3:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2eb7:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:36
      value_ = std::forward<From>(from);  // 在承诺中缓存结果
    2ebb:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2ebf:	48 89 c7             	mov    %rax,%rdi
    2ec2:	e8 cc ff ff ff       	callq  2e93 <int&& std::forward<int>(std::remove_reference<int>::type&)>
    2ec7:	8b 00                	mov    (%rax),%eax
    2ec9:	48 63 d0             	movslq %eax,%rdx
    2ecc:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2ed0:	48 89 10             	mov    %rdx,(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:37
      return {};
    2ed3:	90                   	nop
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:38
    }
    2ed4:	89 d8                	mov    %ebx,%eax
    2ed6:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    2eda:	c9                   	leaveq 
    2edb:	c3                   	retq   

0000000000002edc <std::__n4861::suspend_always Generator<unsigned long>::promise_type::yield_value<unsigned long&>(unsigned long&)>:
_ZN9GeneratorImE12promise_type11yield_valueIRmEENSt7__n486114suspend_alwaysEOT_():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:35
    std::suspend_always yield_value(From&& from) {
    2edc:	f3 0f 1e fa          	endbr64 
    2ee0:	55                   	push   %rbp
    2ee1:	48 89 e5             	mov    %rsp,%rbp
    2ee4:	53                   	push   %rbx
    2ee5:	48 83 ec 18          	sub    $0x18,%rsp
    2ee9:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2eed:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:36
      value_ = std::forward<From>(from);  // 在承诺中缓存结果
    2ef1:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2ef5:	48 89 c7             	mov    %rax,%rdi
    2ef8:	e8 a4 01 00 00       	callq  30a1 <unsigned long& std::forward<unsigned long&>(std::remove_reference<unsigned long&>::type&)>
    2efd:	48 8b 10             	mov    (%rax),%rdx
    2f00:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2f04:	48 89 10             	mov    %rdx,(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:37
      return {};
    2f07:	90                   	nop
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:38
    }
    2f08:	89 d8                	mov    %ebx,%eax
    2f0a:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    2f0e:	c9                   	leaveq 
    2f0f:	c3                   	retq   

0000000000002f10 <Generator<unsigned long>::promise_type::initial_suspend()>:
_ZN9GeneratorImE12promise_type15initial_suspendEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:29
    std::suspend_always initial_suspend() { return {}; }
    2f10:	f3 0f 1e fa          	endbr64 
    2f14:	55                   	push   %rbp
    2f15:	48 89 e5             	mov    %rsp,%rbp
    2f18:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2f1c:	90                   	nop
    2f1d:	5d                   	pop    %rbp
    2f1e:	c3                   	retq   
    2f1f:	90                   	nop

0000000000002f20 <Generator<unsigned long>::promise_type::unhandled_exception()>:
_ZN9GeneratorImE12promise_type19unhandled_exceptionEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:31
    void unhandled_exception() {
    2f20:	f3 0f 1e fa          	endbr64 
    2f24:	55                   	push   %rbp
    2f25:	48 89 e5             	mov    %rsp,%rbp
    2f28:	48 83 ec 20          	sub    $0x20,%rsp
    2f2c:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2f30:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2f37:	00 00 
    2f39:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    2f3d:	31 c0                	xor    %eax,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:32
      exception_ = std::current_exception();
    2f3f:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2f43:	48 89 c7             	mov    %rax,%rdi
    2f46:	e8 35 f3 ff ff       	callq  2280 <std::current_exception()@plt>
    2f4b:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2f4f:	48 8d 50 08          	lea    0x8(%rax),%rdx
    2f53:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2f57:	48 89 c6             	mov    %rax,%rsi
    2f5a:	48 89 d7             	mov    %rdx,%rdi
    2f5d:	e8 72 fe ff ff       	callq  2dd4 <std::__exception_ptr::exception_ptr::operator=(std::__exception_ptr::exception_ptr&&)>
    2f62:	48 8d 45 f0          	lea    -0x10(%rbp),%rax
    2f66:	48 89 c7             	mov    %rax,%rdi
    2f69:	e8 a2 f3 ff ff       	callq  2310 <std::__exception_ptr::exception_ptr::~exception_ptr()@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:33
    }                                       // 保存异常
    2f6e:	90                   	nop
    2f6f:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2f73:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    2f7a:	00 00 
    2f7c:	74 05                	je     2f83 <Generator<unsigned long>::promise_type::unhandled_exception()+0x63>
    2f7e:	e8 0d f3 ff ff       	callq  2290 <__stack_chk_fail@plt>
    2f83:	c9                   	leaveq 
    2f84:	c3                   	retq   
    2f85:	90                   	nop

0000000000002f86 <Generator<unsigned long>::promise_type::final_suspend()>:
_ZN9GeneratorImE12promise_type13final_suspendEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:30
    std::suspend_always final_suspend() noexcept { return {}; }
    2f86:	f3 0f 1e fa          	endbr64 
    2f8a:	55                   	push   %rbp
    2f8b:	48 89 e5             	mov    %rsp,%rbp
    2f8e:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2f92:	90                   	nop
    2f93:	5d                   	pop    %rbp
    2f94:	c3                   	retq   
    2f95:	90                   	nop

0000000000002f96 <Generator<unsigned long>::promise_type::get_return_object()>:
_ZN9GeneratorImE12promise_type17get_return_objectEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:26
    Generator get_return_object() {
    2f96:	f3 0f 1e fa          	endbr64 
    2f9a:	55                   	push   %rbp
    2f9b:	48 89 e5             	mov    %rsp,%rbp
    2f9e:	48 83 ec 10          	sub    $0x10,%rsp
    2fa2:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2fa6:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:27
      return Generator(handle_type::from_promise(*this));
    2faa:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    2fae:	48 89 c7             	mov    %rax,%rdi
    2fb1:	e8 fd 00 00 00       	callq  30b3 <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::from_promise(Generator<unsigned long>::promise_type&)>
    2fb6:	48 89 c2             	mov    %rax,%rdx
    2fb9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2fbd:	48 89 d6             	mov    %rdx,%rsi
    2fc0:	48 89 c7             	mov    %rax,%rdi
    2fc3:	e8 38 01 00 00       	callq  3100 <Generator<unsigned long>::Generator(std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>)>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:28
    }
    2fc8:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2fcc:	c9                   	leaveq 
    2fcd:	c3                   	retq   

0000000000002fce <Generator<unsigned long>::~Generator()>:
_ZN9GeneratorImED2Ev():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:45
  ~Generator() { h_.destroy(); }
    2fce:	f3 0f 1e fa          	endbr64 
    2fd2:	55                   	push   %rbp
    2fd3:	48 89 e5             	mov    %rsp,%rbp
    2fd6:	48 83 ec 10          	sub    $0x10,%rsp
    2fda:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    2fde:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2fe2:	48 89 c7             	mov    %rax,%rdi
    2fe5:	e8 62 fd ff ff       	callq  2d4c <std::__n4861::coroutine_handle<void>::destroy() const>
    2fea:	90                   	nop
    2feb:	c9                   	leaveq 
    2fec:	c3                   	retq   

0000000000002fed <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::from_address(void*)>:
_ZNSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE12from_addressEPv():
/usr/include/c++/10/coroutine:200
    constexpr static coroutine_handle from_address(void* __a) noexcept
    2fed:	f3 0f 1e fa          	endbr64 
    2ff1:	55                   	push   %rbp
    2ff2:	48 89 e5             	mov    %rsp,%rbp
    2ff5:	48 83 ec 20          	sub    $0x20,%rsp
    2ff9:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2ffd:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    3004:	00 00 
    3006:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    300a:	31 c0                	xor    %eax,%eax
/usr/include/c++/10/coroutine:202
      coroutine_handle __self;
    300c:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
    3013:	00 
/usr/include/c++/10/coroutine:203
      __self._M_fr_ptr = __a;
    3014:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    3018:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
/usr/include/c++/10/coroutine:204
      return __self;
    301c:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
/usr/include/c++/10/coroutine:205
    }
    3020:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    3024:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    302b:	00 00 
    302d:	74 05                	je     3034 <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::from_address(void*)+0x47>
    302f:	e8 5c f2 ff ff       	callq  2290 <__stack_chk_fail@plt>
    3034:	c9                   	leaveq 
    3035:	c3                   	retq   

0000000000003036 <Generator<unsigned long>::operator bool()>:
_ZN9GeneratorImEcvbEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:46
  explicit operator bool() {
    3036:	f3 0f 1e fa          	endbr64 
    303a:	55                   	push   %rbp
    303b:	48 89 e5             	mov    %rsp,%rbp
    303e:	48 83 ec 10          	sub    $0x10,%rsp
    3042:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:47
    fill();  // 获知协程是结束了还是仍能通过 C++ getter （下文的 operator ()
    3046:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    304a:	48 89 c7             	mov    %rax,%rdi
    304d:	e8 d4 00 00 00       	callq  3126 <Generator<unsigned long>::fill()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:51
    return !h_.done();
    3052:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3056:	48 89 c7             	mov    %rax,%rdi
    3059:	e8 8e fc ff ff       	callq  2cec <std::__n4861::coroutine_handle<void>::done() const>
    305e:	83 f0 01             	xor    $0x1,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:52
  }
    3061:	c9                   	leaveq 
    3062:	c3                   	retq   
    3063:	90                   	nop

0000000000003064 <Generator<unsigned long>::operator()()>:
_ZN9GeneratorImEclEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:53
  T operator()() {
    3064:	f3 0f 1e fa          	endbr64 
    3068:	55                   	push   %rbp
    3069:	48 89 e5             	mov    %rsp,%rbp
    306c:	48 83 ec 10          	sub    $0x10,%rsp
    3070:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:54
    fill();
    3074:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3078:	48 89 c7             	mov    %rax,%rdi
    307b:	e8 a6 00 00 00       	callq  3126 <Generator<unsigned long>::fill()>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:55
    full_ = false;  // 我们将移动走先前缓存的结果来重新置空承诺
    3080:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3084:	c6 40 08 00          	movb   $0x0,0x8(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:56
    return std::move(h_.promise().value_);
    3088:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    308c:	48 89 c7             	mov    %rax,%rdi
    308f:	e8 58 01 00 00       	callq  31ec <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::promise() const>
    3094:	48 89 c7             	mov    %rax,%rdi
    3097:	e8 71 01 00 00       	callq  320d <std::remove_reference<unsigned long&>::type&& std::move<unsigned long&>(unsigned long&)>
    309c:	48 8b 00             	mov    (%rax),%rax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:57
  }
    309f:	c9                   	leaveq 
    30a0:	c3                   	retq   

00000000000030a1 <unsigned long& std::forward<unsigned long&>(std::remove_reference<unsigned long&>::type&)>:
_ZSt7forwardIRmEOT_RNSt16remove_referenceIS1_E4typeE():
/usr/include/c++/10/bits/move.h:76
    forward(typename std::remove_reference<_Tp>::type& __t) noexcept
    30a1:	f3 0f 1e fa          	endbr64 
    30a5:	55                   	push   %rbp
    30a6:	48 89 e5             	mov    %rsp,%rbp
    30a9:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/usr/include/c++/10/bits/move.h:77
    { return static_cast<_Tp&&>(__t); }
    30ad:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    30b1:	5d                   	pop    %rbp
    30b2:	c3                   	retq   

00000000000030b3 <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::from_promise(Generator<unsigned long>::promise_type&)>:
_ZNSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE12from_promiseERS3_():
/usr/include/c++/10/coroutine:185
      static coroutine_handle from_promise(_Promise& p)
    30b3:	f3 0f 1e fa          	endbr64 
    30b7:	55                   	push   %rbp
    30b8:	48 89 e5             	mov    %rsp,%rbp
    30bb:	48 83 ec 20          	sub    $0x20,%rsp
    30bf:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    30c3:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    30ca:	00 00 
    30cc:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    30d0:	31 c0                	xor    %eax,%eax
/usr/include/c++/10/coroutine:187
	coroutine_handle __self;
    30d2:	48 c7 45 f0 00 00 00 	movq   $0x0,-0x10(%rbp)
    30d9:	00 
/usr/include/c++/10/coroutine:189
	  = __builtin_coro_promise((char*) &p, __alignof(_Promise), true);
    30da:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    30de:	48 83 e8 10          	sub    $0x10,%rax
    30e2:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
/usr/include/c++/10/coroutine:190
	return __self;
    30e6:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
/usr/include/c++/10/coroutine:191
      }
    30ea:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    30ee:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    30f5:	00 00 
    30f7:	74 05                	je     30fe <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::from_promise(Generator<unsigned long>::promise_type&)+0x4b>
    30f9:	e8 92 f1 ff ff       	callq  2290 <__stack_chk_fail@plt>
    30fe:	c9                   	leaveq 
    30ff:	c3                   	retq   

0000000000003100 <Generator<unsigned long>::Generator(std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>)>:
_ZN9GeneratorImEC2ENSt7__n486116coroutine_handleINS0_12promise_typeEEE():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:44
  Generator(handle_type h) : h_(h) {}
    3100:	f3 0f 1e fa          	endbr64 
    3104:	55                   	push   %rbp
    3105:	48 89 e5             	mov    %rsp,%rbp
    3108:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    310c:	48 89 75 f0          	mov    %rsi,-0x10(%rbp)
    3110:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    3114:	48 8b 55 f0          	mov    -0x10(%rbp),%rdx
    3118:	48 89 10             	mov    %rdx,(%rax)
    311b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    311f:	c6 40 08 00          	movb   $0x0,0x8(%rax)
    3123:	90                   	nop
    3124:	5d                   	pop    %rbp
    3125:	c3                   	retq   

0000000000003126 <Generator<unsigned long>::fill()>:
_ZN9GeneratorImE4fillEv():
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:62
  void fill() {
    3126:	f3 0f 1e fa          	endbr64 
    312a:	55                   	push   %rbp
    312b:	48 89 e5             	mov    %rsp,%rbp
    312e:	53                   	push   %rbx
    312f:	48 83 ec 28          	sub    $0x28,%rsp
    3133:	48 89 7d d8          	mov    %rdi,-0x28(%rbp)
    3137:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    313e:	00 00 
    3140:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    3144:	31 c0                	xor    %eax,%eax
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:63
    if (!full_) {
    3146:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    314a:	0f b6 40 08          	movzbl 0x8(%rax),%eax
    314e:	83 f0 01             	xor    $0x1,%eax
    3151:	84 c0                	test   %al,%al
    3153:	74 7b                	je     31d0 <Generator<unsigned long>::fill()+0xaa>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:64
      h_();
    3155:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    3159:	48 89 c7             	mov    %rax,%rdi
    315c:	e8 a9 fb ff ff       	callq  2d0a <std::__n4861::coroutine_handle<void>::operator()() const>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:65
      if (h_.promise().exception_)
    3161:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    3165:	48 89 c7             	mov    %rax,%rdi
    3168:	e8 7f 00 00 00       	callq  31ec <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::promise() const>
    316d:	48 83 c0 08          	add    $0x8,%rax
    3171:	48 89 c7             	mov    %rax,%rdi
    3174:	e8 cb fc ff ff       	callq  2e44 <std::__exception_ptr::exception_ptr::operator bool() const>
    3179:	84 c0                	test   %al,%al
    317b:	74 2b                	je     31a8 <Generator<unsigned long>::fill()+0x82>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:68
        std::rethrow_exception(h_.promise().exception_);
    317d:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    3181:	48 89 c7             	mov    %rax,%rdi
    3184:	e8 63 00 00 00       	callq  31ec <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::promise() const>
    3189:	48 8d 50 08          	lea    0x8(%rax),%rdx
    318d:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    3191:	48 89 d6             	mov    %rdx,%rsi
    3194:	48 89 c7             	mov    %rax,%rdi
    3197:	e8 34 f0 ff ff       	callq  21d0 <std::__exception_ptr::exception_ptr::exception_ptr(std::__exception_ptr::exception_ptr const&)@plt>
    319c:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    31a0:	48 89 c7             	mov    %rax,%rdi
    31a3:	e8 c8 f0 ff ff       	callq  2270 <std::rethrow_exception(std::__exception_ptr::exception_ptr)@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:70
      full_ = true;
    31a8:	48 8b 45 d8          	mov    -0x28(%rbp),%rax
    31ac:	c6 40 08 01          	movb   $0x1,0x8(%rax)
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:72
  }
    31b0:	eb 1e                	jmp    31d0 <Generator<unsigned long>::fill()+0xaa>
    31b2:	f3 0f 1e fa          	endbr64 
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:68
        std::rethrow_exception(h_.promise().exception_);
    31b6:	48 89 c3             	mov    %rax,%rbx
    31b9:	48 8d 45 e0          	lea    -0x20(%rbp),%rax
    31bd:	48 89 c7             	mov    %rax,%rdi
    31c0:	e8 4b f1 ff ff       	callq  2310 <std::__exception_ptr::exception_ptr::~exception_ptr()@plt>
    31c5:	48 89 d8             	mov    %rbx,%rax
    31c8:	48 89 c7             	mov    %rax,%rdi
    31cb:	e8 30 f1 ff ff       	callq  2300 <_Unwind_Resume@plt>
/tmp/tmp.bOCVs3er07/src_cxx20/co_samples/sample_2/main.cpp:72
  }
    31d0:	90                   	nop
    31d1:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    31d5:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    31dc:	00 00 
    31de:	74 05                	je     31e5 <Generator<unsigned long>::fill()+0xbf>
    31e0:	e8 ab f0 ff ff       	callq  2290 <__stack_chk_fail@plt>
    31e5:	48 8b 5d f8          	mov    -0x8(%rbp),%rbx
    31e9:	c9                   	leaveq 
    31ea:	c3                   	retq   
    31eb:	90                   	nop

00000000000031ec <std::__n4861::coroutine_handle<Generator<unsigned long>::promise_type>::promise() const>:
_ZNKSt7__n486116coroutine_handleIN9GeneratorImE12promise_typeEE7promiseEv():
/usr/include/c++/10/coroutine:208
    _Promise& promise() const
    31ec:	f3 0f 1e fa          	endbr64 
    31f0:	55                   	push   %rbp
    31f1:	48 89 e5             	mov    %rsp,%rbp
    31f4:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
/usr/include/c++/10/coroutine:211
	= __builtin_coro_promise (this->_M_fr_ptr, __alignof(_Promise), false);
    31f8:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    31fc:	48 8b 00             	mov    (%rax),%rax
    31ff:	48 83 c0 10          	add    $0x10,%rax
    3203:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
/usr/include/c++/10/coroutine:212
      return *static_cast<_Promise*>(__t);
    3207:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
/usr/include/c++/10/coroutine:213
    }
    320b:	5d                   	pop    %rbp
    320c:	c3                   	retq   

000000000000320d <std::remove_reference<unsigned long&>::type&& std::move<unsigned long&>(unsigned long&)>:
_ZSt4moveIRmEONSt16remove_referenceIT_E4typeEOS2_():
/usr/include/c++/10/bits/move.h:101
   *  @param  __t  A thing of arbitrary type.
   *  @return The parameter cast to an rvalue-reference to allow moving it.
  */
  template<typename _Tp>
    constexpr typename std::remove_reference<_Tp>::type&&
    move(_Tp&& __t) noexcept
    320d:	f3 0f 1e fa          	endbr64 
    3211:	55                   	push   %rbp
    3212:	48 89 e5             	mov    %rsp,%rbp
    3215:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
/usr/include/c++/10/bits/move.h:102
    { return static_cast<typename std::remove_reference<_Tp>::type&&>(__t); }
    3219:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    321d:	5d                   	pop    %rbp
    321e:	c3                   	retq   
    321f:	90                   	nop

0000000000003220 <__libc_csu_init>:
__libc_csu_init():
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
__libc_csu_fini():
    3290:	f3 0f 1e fa          	endbr64 
    3294:	c3                   	retq   

Disassembly of section .fini:

0000000000003298 <_fini>:
_fini():
    3298:	f3 0f 1e fa          	endbr64 
    329c:	48 83 ec 08          	sub    $0x8,%rsp
    32a0:	48 83 c4 08          	add    $0x8,%rsp
    32a4:	c3                   	retq   
