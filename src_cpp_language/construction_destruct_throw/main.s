
a.out:     file format elf64-x86-64


Disassembly of section .interp:

0000000000400318 <.interp>:
  400318:	2f                   	(bad)
  400319:	6c                   	insb   (%dx),%es:(%rdi)
  40031a:	69 62 36 34 2f 6c 64 	imul   $0x646c2f34,0x36(%rdx),%esp
  400321:	2d 6c 69 6e 75       	sub    $0x756e696c,%eax
  400326:	78 2d                	js     400355 <_init-0xcab>
  400328:	78 38                	js     400362 <_init-0xc9e>
  40032a:	36 2d 36 34 2e 73    	ss sub $0x732e3436,%eax
  400330:	6f                   	outsl  %ds:(%rsi),(%dx)
  400331:	2e 32 00             	cs xor (%rax),%al

Disassembly of section .note.gnu.property:

0000000000400338 <.note.gnu.property>:
  400338:	04 00                	add    $0x0,%al
  40033a:	00 00                	add    %al,(%rax)
  40033c:	30 00                	xor    %al,(%rax)
  40033e:	00 00                	add    %al,(%rax)
  400340:	05 00 00 00 47       	add    $0x47000000,%eax
  400345:	4e 55                	rex.WRX push %rbp
  400347:	00 02                	add    %al,(%rdx)
  400349:	80 00 c0             	addb   $0xc0,(%rax)
  40034c:	04 00                	add    $0x0,%al
  40034e:	00 00                	add    %al,(%rax)
  400350:	01 00                	add    %eax,(%rax)
  400352:	00 00                	add    %al,(%rax)
  400354:	00 00                	add    %al,(%rax)
  400356:	00 00                	add    %al,(%rax)
  400358:	01 00                	add    %eax,(%rax)
  40035a:	01 c0                	add    %eax,%eax
  40035c:	04 00                	add    $0x0,%al
  40035e:	00 00                	add    %al,(%rax)
  400360:	01 00                	add    %eax,(%rax)
  400362:	00 00                	add    %al,(%rax)
  400364:	00 00                	add    %al,(%rax)
  400366:	00 00                	add    %al,(%rax)
  400368:	02 00                	add    (%rax),%al
  40036a:	01 c0                	add    %eax,%eax
  40036c:	04 00                	add    $0x0,%al
	...

Disassembly of section .note.gnu.build-id:

0000000000400378 <.note.gnu.build-id>:
  400378:	04 00                	add    $0x0,%al
  40037a:	00 00                	add    %al,(%rax)
  40037c:	14 00                	adc    $0x0,%al
  40037e:	00 00                	add    %al,(%rax)
  400380:	03 00                	add    (%rax),%eax
  400382:	00 00                	add    %al,(%rax)
  400384:	47                   	rex.RXB
  400385:	4e 55                	rex.WRX push %rbp
  400387:	00 97 01 ad 80 9d    	add    %dl,-0x627f52ff(%rdi)
  40038d:	9a                   	(bad)
  40038e:	a2 67 c7 69 10 75 d5 	movabs %al,0x67ddd5751069c767
  400395:	dd 67 
  400397:	ae                   	scas   %es:(%rdi),%al
  400398:	00 04 69             	add    %al,(%rcx,%rbp,2)
  40039b:	8e                   	.byte 0x8e

Disassembly of section .note.ABI-tag:

000000000040039c <.note.ABI-tag>:
  40039c:	04 00                	add    $0x0,%al
  40039e:	00 00                	add    %al,(%rax)
  4003a0:	10 00                	adc    %al,(%rax)
  4003a2:	00 00                	add    %al,(%rax)
  4003a4:	01 00                	add    %eax,(%rax)
  4003a6:	00 00                	add    %al,(%rax)
  4003a8:	47                   	rex.RXB
  4003a9:	4e 55                	rex.WRX push %rbp
  4003ab:	00 00                	add    %al,(%rax)
  4003ad:	00 00                	add    %al,(%rax)
  4003af:	00 04 00             	add    %al,(%rax,%rax,1)
  4003b2:	00 00                	add    %al,(%rax)
  4003b4:	04 00                	add    $0x0,%al
  4003b6:	00 00                	add    %al,(%rax)
  4003b8:	00 00                	add    %al,(%rax)
	...

Disassembly of section .gnu.hash:

00000000004003c0 <.gnu.hash>:
  4003c0:	02 00                	add    (%rax),%al
  4003c2:	00 00                	add    %al,(%rax)
  4003c4:	0d 00 00 00 01       	or     $0x1000000,%eax
  4003c9:	00 00                	add    %al,(%rax)
  4003cb:	00 06                	add    %al,(%rsi)
  4003cd:	00 00                	add    %al,(%rax)
  4003cf:	00 80 01 00 00 20    	add    %al,0x20000001(%rax)
  4003d5:	00 00                	add    %al,(%rax)
  4003d7:	01 0d 00 00 00 00    	add    %ecx,0x0(%rip)        # 4003dd <_init-0xc23>
  4003dd:	00 00                	add    %al,(%rax)
  4003df:	00 c8                	add    %cl,%al
  4003e1:	81 0a d2 79 49 6b    	orl    $0x6b4979d2,(%rdx)
  4003e7:	b6                   	.byte 0xb6

Disassembly of section .dynsym:

00000000004003e8 <.dynsym>:
	...
  400400:	ff 00                	incl   (%rax)
  400402:	00 00                	add    %al,(%rax)
  400404:	12 00                	adc    (%rax),%al
	...
  400416:	00 00                	add    %al,(%rax)
  400418:	78 00                	js     40041a <_init-0xbe6>
  40041a:	00 00                	add    %al,(%rax)
  40041c:	12 00                	adc    (%rax),%al
	...
  40042e:	00 00                	add    %al,(%rax)
  400430:	8a 00                	mov    (%rax),%al
  400432:	00 00                	add    %al,(%rax)
  400434:	12 00                	adc    (%rax),%al
	...
  400446:	00 00                	add    %al,(%rax)
  400448:	ed                   	in     (%dx),%eax
  400449:	00 00                	add    %al,(%rax)
  40044b:	00 12                	add    %dl,(%rdx)
	...
  40045d:	00 00                	add    %al,(%rax)
  40045f:	00 dc                	add    %bl,%ah
  400461:	00 00                	add    %al,(%rax)
  400463:	00 12                	add    %dl,(%rdx)
	...
  400475:	00 00                	add    %al,(%rax)
  400477:	00 d7                	add    %dl,%bh
  400479:	00 00                	add    %al,(%rax)
  40047b:	00 12                	add    %dl,(%rdx)
	...
  40048d:	00 00                	add    %al,(%rax)
  40048f:	00 b8 00 00 00 12    	add    %bh,0x12000000(%rax)
	...
  4004a5:	00 00                	add    %al,(%rax)
  4004a7:	00 46 00             	add    %al,0x0(%rsi)
  4004aa:	00 00                	add    %al,(%rax)
  4004ac:	12 00                	adc    (%rax),%al
	...
  4004be:	00 00                	add    %al,(%rax)
  4004c0:	10 00                	adc    %al,(%rax)
  4004c2:	00 00                	add    %al,(%rax)
  4004c4:	20 00                	and    %al,(%rax)
	...
  4004d6:	00 00                	add    %al,(%rax)
  4004d8:	c8 00 00 00          	enter  $0x0,$0x0
  4004dc:	12 00                	adc    (%rax),%al
	...
  4004ee:	00 00                	add    %al,(%rax)
  4004f0:	01 00                	add    %eax,(%rax)
  4004f2:	00 00                	add    %al,(%rax)
  4004f4:	20 00                	and    %al,(%rax)
	...
  400506:	00 00                	add    %al,(%rax)
  400508:	2c 00                	sub    $0x0,%al
  40050a:	00 00                	add    %al,(%rax)
  40050c:	20 00                	and    %al,(%rax)
	...
  40051e:	00 00                	add    %al,(%rax)
  400520:	52                   	push   %rdx
  400521:	00 00                	add    %al,(%rax)
  400523:	00 21                	add    %ah,(%rcx)
  400525:	00 16                	add    %dl,(%rsi)
  400527:	00 70 3d             	add    %dh,0x3d(%rax)
  40052a:	40 00 00             	rex add %al,(%rax)
  40052d:	00 00                	add    %al,(%rax)
  40052f:	00 58 00             	add    %bl,0x0(%rax)
  400532:	00 00                	add    %al,(%rax)
  400534:	00 00                	add    %al,(%rax)
  400536:	00 00                	add    %al,(%rax)
  400538:	a3 00 00 00 12 00 00 	movabs %eax,0x9000000012000000
  40053f:	00 90 
  400541:	10 40 00             	adc    %al,0x0(%rax)
	...

Disassembly of section .dynstr:

0000000000400550 <.dynstr>:
  400550:	00 5f 5f             	add    %bl,0x5f(%rdi)
  400553:	67 6d                	insl   (%dx),%es:(%edi)
  400555:	6f                   	outsl  %ds:(%rsi),(%dx)
  400556:	6e                   	outsb  %ds:(%rsi),(%dx)
  400557:	5f                   	pop    %rdi
  400558:	73 74                	jae    4005ce <_init-0xa32>
  40055a:	61                   	(bad)
  40055b:	72 74                	jb     4005d1 <_init-0xa2f>
  40055d:	5f                   	pop    %rdi
  40055e:	5f                   	pop    %rdi
  40055f:	00 5f 49             	add    %bl,0x49(%rdi)
  400562:	54                   	push   %rsp
  400563:	4d 5f                	rex.WRB pop %r15
  400565:	64 65 72 65          	fs gs jb 4005ce <_init-0xa32>
  400569:	67 69 73 74 65 72 54 	imul   $0x4d547265,0x74(%ebx),%esi
  400570:	4d 
  400571:	43 6c                	rex.XB insb (%dx),%es:(%rdi)
  400573:	6f                   	outsl  %ds:(%rsi),(%dx)
  400574:	6e                   	outsb  %ds:(%rsi),(%dx)
  400575:	65 54                	gs push %rsp
  400577:	61                   	(bad)
  400578:	62 6c 65 00 5f       	(bad)
  40057d:	49 54                	rex.WB push %r12
  40057f:	4d 5f                	rex.WRB pop %r15
  400581:	72 65                	jb     4005e8 <_init-0xa18>
  400583:	67 69 73 74 65 72 54 	imul   $0x4d547265,0x74(%ebx),%esi
  40058a:	4d 
  40058b:	43 6c                	rex.XB insb (%dx),%es:(%rdi)
  40058d:	6f                   	outsl  %ds:(%rsi),(%dx)
  40058e:	6e                   	outsb  %ds:(%rsi),(%dx)
  40058f:	65 54                	gs push %rsp
  400591:	61                   	(bad)
  400592:	62 6c 65 00 5f       	(bad)
  400597:	5f                   	pop    %rdi
  400598:	63 78 61             	movsxd 0x61(%rax),%edi
  40059b:	5f                   	pop    %rdi
  40059c:	74 68                	je     400606 <_init-0x9fa>
  40059e:	72 6f                	jb     40060f <_init-0x9f1>
  4005a0:	77 00                	ja     4005a2 <_init-0xa5e>
  4005a2:	5f                   	pop    %rdi
  4005a3:	5a                   	pop    %rdx
  4005a4:	54                   	push   %rsp
  4005a5:	56                   	push   %rsi
  4005a6:	4e 31 30             	rex.WRX xor %r14,(%rax)
  4005a9:	5f                   	pop    %rdi
  4005aa:	5f                   	pop    %rdi
  4005ab:	63 78 78             	movsxd 0x78(%rax),%edi
  4005ae:	61                   	(bad)
  4005af:	62 69 76 31 31       	(bad)
  4005b4:	37                   	(bad)
  4005b5:	5f                   	pop    %rdi
  4005b6:	5f                   	pop    %rdi
  4005b7:	63 6c 61 73          	movsxd 0x73(%rcx,%riz,2),%ebp
  4005bb:	73 5f                	jae    40061c <_init-0x9e4>
  4005bd:	74 79                	je     400638 <_init-0x9c8>
  4005bf:	70 65                	jo     400626 <_init-0x9da>
  4005c1:	5f                   	pop    %rdi
  4005c2:	69 6e 66 6f 45 00 5f 	imul   $0x5f00456f,0x66(%rsi),%ebp
  4005c9:	5f                   	pop    %rdi
  4005ca:	63 78 61             	movsxd 0x61(%rax),%edi
  4005cd:	5f                   	pop    %rdi
  4005ce:	62 65 67 69 6e       	(bad)
  4005d3:	5f                   	pop    %rdi
  4005d4:	63 61 74             	movsxd 0x74(%rcx),%esp
  4005d7:	63 68 00             	movsxd 0x0(%rax),%ebp
  4005da:	5f                   	pop    %rdi
  4005db:	5f                   	pop    %rdi
  4005dc:	63 78 61             	movsxd 0x61(%rax),%edi
  4005df:	5f                   	pop    %rdi
  4005e0:	61                   	(bad)
  4005e1:	6c                   	insb   (%dx),%es:(%rdi)
  4005e2:	6c                   	insb   (%dx),%es:(%rdi)
  4005e3:	6f                   	outsl  %ds:(%rsi),(%dx)
  4005e4:	63 61 74             	movsxd 0x74(%rcx),%esp
  4005e7:	65 5f                	gs pop %rdi
  4005e9:	65 78 63             	gs js  40064f <_init-0x9b1>
  4005ec:	65 70 74             	gs jo  400663 <_init-0x99d>
  4005ef:	69 6f 6e 00 5f 5f 67 	imul   $0x675f5f00,0x6e(%rdi),%ebp
  4005f6:	78 78                	js     400670 <_init-0x990>
  4005f8:	5f                   	pop    %rdi
  4005f9:	70 65                	jo     400660 <_init-0x9a0>
  4005fb:	72 73                	jb     400670 <_init-0x990>
  4005fd:	6f                   	outsl  %ds:(%rsi),(%dx)
  4005fe:	6e                   	outsb  %ds:(%rsi),(%dx)
  4005ff:	61                   	(bad)
  400600:	6c                   	insb   (%dx),%es:(%rdi)
  400601:	69 74 79 5f 76 30 00 	imul   $0x5f003076,0x5f(%rcx,%rdi,2),%esi
  400608:	5f 
  400609:	5f                   	pop    %rdi
  40060a:	63 78 61             	movsxd 0x61(%rax),%edi
  40060d:	5f                   	pop    %rdi
  40060e:	65 6e                	outsb  %gs:(%rsi),(%dx)
  400610:	64 5f                	fs pop %rdi
  400612:	63 61 74             	movsxd 0x74(%rcx),%esp
  400615:	63 68 00             	movsxd 0x0(%rax),%ebp
  400618:	5f                   	pop    %rdi
  400619:	55                   	push   %rbp
  40061a:	6e                   	outsb  %ds:(%rsi),(%dx)
  40061b:	77 69                	ja     400686 <_init-0x97a>
  40061d:	6e                   	outsb  %ds:(%rsi),(%dx)
  40061e:	64 5f                	fs pop %rdi
  400620:	52                   	push   %rdx
  400621:	65 73 75             	gs jae 400699 <_init-0x967>
  400624:	6d                   	insl   (%dx),%es:(%rdi)
  400625:	65 00 70 75          	add    %dh,%gs:0x75(%rax)
  400629:	74 73                	je     40069e <_init-0x962>
  40062b:	00 5f 5f             	add    %bl,0x5f(%rdi)
  40062e:	73 74                	jae    4006a4 <_init-0x95c>
  400630:	61                   	(bad)
  400631:	63 6b 5f             	movsxd 0x5f(%rbx),%ebp
  400634:	63 68 6b             	movsxd 0x6b(%rax),%ebp
  400637:	5f                   	pop    %rdi
  400638:	66 61                	data16 (bad)
  40063a:	69 6c 00 5f 5f 6c 69 	imul   $0x62696c5f,0x5f(%rax,%rax,1),%ebp
  400641:	62 
  400642:	63 5f 73             	movsxd 0x73(%rdi),%ebx
  400645:	74 61                	je     4006a8 <_init-0x958>
  400647:	72 74                	jb     4006bd <_init-0x943>
  400649:	5f                   	pop    %rdi
  40064a:	6d                   	insl   (%dx),%es:(%rdi)
  40064b:	61                   	(bad)
  40064c:	69 6e 00 70 72 69 6e 	imul   $0x6e697270,0x0(%rsi),%ebp
  400653:	74 66                	je     4006bb <_init-0x945>
  400655:	00 6c 69 62          	add    %ch,0x62(%rcx,%rbp,2)
  400659:	73 74                	jae    4006cf <_init-0x931>
  40065b:	64 63 2b             	movsxd %fs:(%rbx),%ebp
  40065e:	2b 2e                	sub    (%rsi),%ebp
  400660:	73 6f                	jae    4006d1 <_init-0x92f>
  400662:	2e 36 00 6c 69 62    	cs ss add %ch,0x62(%rcx,%rbp,2)
  400668:	6d                   	insl   (%dx),%es:(%rdi)
  400669:	2e 73 6f             	jae,pn 4006db <_init-0x925>
  40066c:	2e 36 00 6c 69 62    	cs ss add %ch,0x62(%rcx,%rbp,2)
  400672:	67 63 63 5f          	movsxd 0x5f(%ebx),%esp
  400676:	73 2e                	jae    4006a6 <_init-0x95a>
  400678:	73 6f                	jae    4006e9 <_init-0x917>
  40067a:	2e 31 00             	cs xor %eax,(%rax)
  40067d:	6c                   	insb   (%dx),%es:(%rdi)
  40067e:	69 62 63 2e 73 6f 2e 	imul   $0x2e6f732e,0x63(%rdx),%esp
  400685:	36 00 47 43          	ss add %al,0x43(%rdi)
  400689:	43 5f                	rex.XB pop %r15
  40068b:	33 2e                	xor    (%rsi),%ebp
  40068d:	30 00                	xor    %al,(%rax)
  40068f:	43 58                	rex.XB pop %r8
  400691:	58                   	pop    %rax
  400692:	41                   	rex.B
  400693:	42                   	rex.X
  400694:	49 5f                	rex.WB pop %r15
  400696:	31 2e                	xor    %ebp,(%rsi)
  400698:	33 00                	xor    (%rax),%eax
  40069a:	47                   	rex.RXB
  40069b:	4c                   	rex.WR
  40069c:	49                   	rex.WB
  40069d:	42                   	rex.X
  40069e:	43 5f                	rex.XB pop %r15
  4006a0:	32 2e                	xor    (%rsi),%ch
  4006a2:	34 00                	xor    $0x0,%al
  4006a4:	47                   	rex.RXB
  4006a5:	4c                   	rex.WR
  4006a6:	49                   	rex.WB
  4006a7:	42                   	rex.X
  4006a8:	43 5f                	rex.XB pop %r15
  4006aa:	32 2e                	xor    (%rsi),%ch
  4006ac:	33 34 00             	xor    (%rax,%rax,1),%esi
  4006af:	47                   	rex.RXB
  4006b0:	4c                   	rex.WR
  4006b1:	49                   	rex.WB
  4006b2:	42                   	rex.X
  4006b3:	43 5f                	rex.XB pop %r15
  4006b5:	32 2e                	xor    (%rsi),%ch
  4006b7:	32 2e                	xor    (%rsi),%ch
  4006b9:	35                   	.byte 0x35
	...

Disassembly of section .gnu.version:

00000000004006bc <.gnu.version>:
  4006bc:	00 00                	add    %al,(%rax)
  4006be:	02 00                	add    (%rax),%al
  4006c0:	03 00                	add    (%rax),%eax
  4006c2:	03 00                	add    (%rax),%eax
  4006c4:	04 00                	add    $0x0,%al
  4006c6:	05 00 02 00 03       	add    $0x3000200,%eax
  4006cb:	00 03                	add    %al,(%rbx)
  4006cd:	00 01                	add    %al,(%rcx)
  4006cf:	00 06                	add    %al,(%rsi)
  4006d1:	00 01                	add    %al,(%rcx)
  4006d3:	00 01                	add    %al,(%rcx)
  4006d5:	00 03                	add    %al,(%rbx)
  4006d7:	00 03                	add    %al,(%rbx)
	...

Disassembly of section .gnu.version_r:

00000000004006e0 <.gnu.version_r>:
  4006e0:	01 00                	add    %eax,(%rax)
  4006e2:	01 00                	add    %eax,(%rax)
  4006e4:	1f                   	(bad)
  4006e5:	01 00                	add    %eax,(%rax)
  4006e7:	00 10                	add    %dl,(%rax)
  4006e9:	00 00                	add    %al,(%rax)
  4006eb:	00 20                	add    %ah,(%rax)
  4006ed:	00 00                	add    %al,(%rax)
  4006ef:	00 50 26             	add    %dl,0x26(%rax)
  4006f2:	79 0b                	jns    4006ff <_init-0x901>
  4006f4:	00 00                	add    %al,(%rax)
  4006f6:	06                   	(bad)
  4006f7:	00 37                	add    %dh,(%rdi)
  4006f9:	01 00                	add    %eax,(%rax)
  4006fb:	00 00                	add    %al,(%rax)
  4006fd:	00 00                	add    %al,(%rax)
  4006ff:	00 01                	add    %al,(%rcx)
  400701:	00 01                	add    %al,(%rcx)
  400703:	00 06                	add    %al,(%rsi)
  400705:	01 00                	add    %eax,(%rax)
  400707:	00 10                	add    %dl,(%rax)
  400709:	00 00                	add    %al,(%rax)
  40070b:	00 20                	add    %ah,(%rax)
  40070d:	00 00                	add    %al,(%rax)
  40070f:	00 d3                	add    %dl,%bl
  400711:	af                   	scas   %es:(%rdi),%eax
  400712:	6b 05 00 00 03 00 3f 	imul   $0x3f,0x30000(%rip),%eax        # 430719 <_end+0x2c6b9>
  400719:	01 00                	add    %eax,(%rax)
  40071b:	00 00                	add    %al,(%rax)
  40071d:	00 00                	add    %al,(%rax)
  40071f:	00 01                	add    %al,(%rcx)
  400721:	00 03                	add    %al,(%rbx)
  400723:	00 2d 01 00 00 10    	add    %ch,0x10000001(%rip)        # 1040072a <_end+0xfffc6ca>
  400729:	00 00                	add    %al,(%rax)
  40072b:	00 00                	add    %al,(%rax)
  40072d:	00 00                	add    %al,(%rax)
  40072f:	00 14 69             	add    %dl,(%rcx,%rbp,2)
  400732:	69 0d 00 00 05 00 4a 	imul   $0x14a,0x50000(%rip),%ecx        # 45073c <_end+0x4c6dc>
  400739:	01 00 00 
  40073c:	10 00                	adc    %al,(%rax)
  40073e:	00 00                	add    %al,(%rax)
  400740:	b4 91                	mov    $0x91,%ah
  400742:	96                   	xchg   %eax,%esi
  400743:	06                   	(bad)
  400744:	00 00                	add    %al,(%rax)
  400746:	04 00                	add    $0x0,%al
  400748:	54                   	push   %rsp
  400749:	01 00                	add    %eax,(%rax)
  40074b:	00 10                	add    %dl,(%rax)
  40074d:	00 00                	add    %al,(%rax)
  40074f:	00 75 1a             	add    %dh,0x1a(%rbp)
  400752:	69 09 00 00 02 00    	imul   $0x20000,(%rcx),%ecx
  400758:	5f                   	pop    %rdi
  400759:	01 00                	add    %eax,(%rax)
  40075b:	00 00                	add    %al,(%rax)
  40075d:	00 00                	add    %al,(%rax)
	...

Disassembly of section .rela.dyn:

0000000000400760 <.rela.dyn>:
  400760:	c8 3f 40 00          	enter  $0x403f,$0x0
  400764:	00 00                	add    %al,(%rax)
  400766:	00 00                	add    %al,(%rax)
  400768:	06                   	(bad)
  400769:	00 00                	add    %al,(%rax)
  40076b:	00 04 00             	add    %al,(%rax,%rax,1)
	...
  400776:	00 00                	add    %al,(%rax)
  400778:	d0 3f                	sarb   $1,(%rdi)
  40077a:	40 00 00             	rex add %al,(%rax)
  40077d:	00 00                	add    %al,(%rax)
  40077f:	00 06                	add    %al,(%rsi)
  400781:	00 00                	add    %al,(%rax)
  400783:	00 09                	add    %cl,(%rcx)
	...
  40078d:	00 00                	add    %al,(%rax)
  40078f:	00 d8                	add    %bl,%al
  400791:	3f                   	(bad)
  400792:	40 00 00             	rex add %al,(%rax)
  400795:	00 00                	add    %al,(%rax)
  400797:	00 06                	add    %al,(%rsi)
  400799:	00 00                	add    %al,(%rax)
  40079b:	00 0b                	add    %cl,(%rbx)
	...
  4007a5:	00 00                	add    %al,(%rax)
  4007a7:	00 e0                	add    %ah,%al
  4007a9:	3f                   	(bad)
  4007aa:	40 00 00             	rex add %al,(%rax)
  4007ad:	00 00                	add    %al,(%rax)
  4007af:	00 06                	add    %al,(%rsi)
  4007b1:	00 00                	add    %al,(%rax)
  4007b3:	00 0c 00             	add    %cl,(%rax,%rax,1)
	...
  4007be:	00 00                	add    %al,(%rax)
  4007c0:	70 3d                	jo     4007ff <_init-0x801>
  4007c2:	40 00 00             	rex add %al,(%rax)
  4007c5:	00 00                	add    %al,(%rax)
  4007c7:	00 05 00 00 00 0d    	add    %al,0xd000000(%rip)        # d4007cd <_end+0xcffc76d>
	...

Disassembly of section .rela.plt:

00000000004007d8 <.rela.plt>:
  4007d8:	00 40 40             	add    %al,0x40(%rax)
  4007db:	00 00                	add    %al,(%rax)
  4007dd:	00 00                	add    %al,(%rax)
  4007df:	00 07                	add    %al,(%rdi)
  4007e1:	00 00                	add    %al,(%rax)
  4007e3:	00 01                	add    %al,(%rcx)
	...
  4007ed:	00 00                	add    %al,(%rax)
  4007ef:	00 08                	add    %cl,(%rax)
  4007f1:	40                   	rex
  4007f2:	40 00 00             	rex add %al,(%rax)
  4007f5:	00 00                	add    %al,(%rax)
  4007f7:	00 07                	add    %al,(%rdi)
  4007f9:	00 00                	add    %al,(%rax)
  4007fb:	00 02                	add    %al,(%rdx)
	...
  400805:	00 00                	add    %al,(%rax)
  400807:	00 10                	add    %dl,(%rax)
  400809:	40                   	rex
  40080a:	40 00 00             	rex add %al,(%rax)
  40080d:	00 00                	add    %al,(%rax)
  40080f:	00 07                	add    %al,(%rdi)
  400811:	00 00                	add    %al,(%rax)
  400813:	00 03                	add    %al,(%rbx)
	...
  40081d:	00 00                	add    %al,(%rax)
  40081f:	00 18                	add    %bl,(%rax)
  400821:	40                   	rex
  400822:	40 00 00             	rex add %al,(%rax)
  400825:	00 00                	add    %al,(%rax)
  400827:	00 07                	add    %al,(%rdi)
  400829:	00 00                	add    %al,(%rax)
  40082b:	00 05 00 00 00 00    	add    %al,0x0(%rip)        # 400831 <_init-0x7cf>
  400831:	00 00                	add    %al,(%rax)
  400833:	00 00                	add    %al,(%rax)
  400835:	00 00                	add    %al,(%rax)
  400837:	00 20                	add    %ah,(%rax)
  400839:	40                   	rex
  40083a:	40 00 00             	rex add %al,(%rax)
  40083d:	00 00                	add    %al,(%rax)
  40083f:	00 07                	add    %al,(%rdi)
  400841:	00 00                	add    %al,(%rax)
  400843:	00 06                	add    %al,(%rsi)
	...
  40084d:	00 00                	add    %al,(%rax)
  40084f:	00 28                	add    %ch,(%rax)
  400851:	40                   	rex
  400852:	40 00 00             	rex add %al,(%rax)
  400855:	00 00                	add    %al,(%rax)
  400857:	00 07                	add    %al,(%rdi)
  400859:	00 00                	add    %al,(%rax)
  40085b:	00 07                	add    %al,(%rdi)
	...
  400865:	00 00                	add    %al,(%rax)
  400867:	00 30                	add    %dh,(%rax)
  400869:	40                   	rex
  40086a:	40 00 00             	rex add %al,(%rax)
  40086d:	00 00                	add    %al,(%rax)
  40086f:	00 07                	add    %al,(%rdi)
  400871:	00 00                	add    %al,(%rax)
  400873:	00 0e                	add    %cl,(%rsi)
	...
  40087d:	00 00                	add    %al,(%rax)
  40087f:	00 38                	add    %bh,(%rax)
  400881:	40                   	rex
  400882:	40 00 00             	rex add %al,(%rax)
  400885:	00 00                	add    %al,(%rax)
  400887:	00 07                	add    %al,(%rdi)
  400889:	00 00                	add    %al,(%rax)
  40088b:	00 08                	add    %cl,(%rax)
	...
  400895:	00 00                	add    %al,(%rax)
  400897:	00 40 40             	add    %al,0x40(%rax)
  40089a:	40 00 00             	rex add %al,(%rax)
  40089d:	00 00                	add    %al,(%rax)
  40089f:	00 07                	add    %al,(%rdi)
  4008a1:	00 00                	add    %al,(%rax)
  4008a3:	00 0a                	add    %cl,(%rdx)
	...

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

Disassembly of section .rodata:

0000000000402000 <_IO_stdin_used>:
  402000:	01 00                	add    %eax,(%rax)
  402002:	02 00                	add    (%rax),%al
  402004:	43 6f                	rex.XB outsl %ds:(%rsi),(%dx)
  402006:	6e                   	outsb  %ds:(%rsi),(%dx)
  402007:	73 74                	jae    40207d <__GNU_EH_FRAME_HDR+0xd>
  402009:	72 75                	jb     402080 <__GNU_EH_FRAME_HDR+0x10>
  40200b:	63 74 69 6e          	movsxd 0x6e(%rcx,%rbp,2),%esi
  40200f:	67 20 6f 62          	and    %ch,0x62(%edi)
  402013:	6a 65                	push   $0x65
  402015:	63 74 20 25          	movsxd 0x25(%rax,%riz,1),%esi
  402019:	64 0a 00             	or     %fs:(%rax),%al
  40201c:	44                   	rex.R
  40201d:	65 73 74             	gs jae 402094 <__GNU_EH_FRAME_HDR+0x24>
  402020:	72 75                	jb     402097 <__GNU_EH_FRAME_HDR+0x27>
  402022:	63 74 69 6e          	movsxd 0x6e(%rcx,%rbp,2),%esi
  402026:	67 20 6f 62          	and    %ch,0x62(%edi)
  40202a:	6a 65                	push   $0x65
  40202c:	63 74 20 25          	movsxd 0x25(%rax,%riz,1),%esi
  402030:	64 0a 00             	or     %fs:(%rax),%al
  402033:	63 61 74             	movsxd 0x74(%rcx),%esp
  402036:	63 68 20             	movsxd 0x20(%rax),%ebp
  402039:	65 78 63             	gs js  40209f <__GNU_EH_FRAME_HDR+0x2f>
  40203c:	65 70 74             	gs jo  4020b3 <__GNU_EH_FRAME_HDR+0x43>
  40203f:	69 6f 6e 00 00 00 00 	imul   $0x0,0x6e(%rdi),%ebp
	...

0000000000402048 <_ZTI13TestException>:
  402048:	80 3d 40 00 00 00 00 	cmpb   $0x0,0x40(%rip)        # 40208f <__GNU_EH_FRAME_HDR+0x1f>
  40204f:	00 60 20             	add    %ah,0x20(%rax)
  402052:	40 00 00             	rex add %al,(%rax)
	...

0000000000402060 <_ZTS13TestException>:
  402060:	31 33                	xor    %esi,(%rbx)
  402062:	54                   	push   %rsp
  402063:	65 73 74             	gs jae 4020da <__GNU_EH_FRAME_HDR+0x6a>
  402066:	45 78 63             	rex.RB js 4020cc <__GNU_EH_FRAME_HDR+0x5c>
  402069:	65 70 74             	gs jo  4020e0 <__GNU_EH_FRAME_HDR+0x70>
  40206c:	69                   	.byte 0x69
  40206d:	6f                   	outsl  %ds:(%rsi),(%dx)
  40206e:	6e                   	outsb  %ds:(%rsi),(%dx)
	...

Disassembly of section .eh_frame_hdr:

0000000000402070 <__GNU_EH_FRAME_HDR>:
  402070:	01 1b                	add    %ebx,(%rbx)
  402072:	03 3b                	add    (%rbx),%edi
  402074:	44 00 00             	add    %r8b,(%rax)
  402077:	00 07                	add    %al,(%rdi)
  402079:	00 00                	add    %al,(%rax)
  40207b:	00 b0 ef ff ff 88    	add    %dh,-0x77000011(%rax)
  402081:	00 00                	add    %al,(%rax)
  402083:	00 50 f0             	add    %dl,-0x10(%rax)
  402086:	ff                   	(bad)
  402087:	ff 60 00             	jmp    *0x0(%rax)
  40208a:	00 00                	add    %al,(%rax)
  40208c:	80 f0 ff             	xor    $0xff,%al
  40208f:	ff 74 00 00          	push   0x0(%rax,%rax,1)
  402093:	00 36                	add    %dh,(%rsi)
  402095:	f1                   	int1
  402096:	ff                   	(bad)
  402097:	ff 14 01             	call   *(%rcx,%rax,1)
  40209a:	00 00                	add    %al,(%rax)
  40209c:	5c                   	pop    %rsp
  40209d:	f2 ff                	repnz (bad)
  40209f:	ff                   	(bad)
  4020a0:	3c 01                	cmp    $0x1,%al
  4020a2:	00 00                	add    %al,(%rax)
  4020a4:	b6 f2                	mov    $0xf2,%dh
  4020a6:	ff                   	(bad)
  4020a7:	ff b0 00 00 00 10    	push   0x10000000(%rax)
  4020ad:	f3 ff                	repz (bad)
  4020af:	ff f0                	push   %rax
  4020b1:	00 00                	add    %al,(%rax)
	...

Disassembly of section .eh_frame:

00000000004020b8 <.eh_frame>:
  4020b8:	14 00                	adc    $0x0,%al
  4020ba:	00 00                	add    %al,(%rax)
  4020bc:	00 00                	add    %al,(%rax)
  4020be:	00 00                	add    %al,(%rax)
  4020c0:	01 7a 52             	add    %edi,0x52(%rdx)
  4020c3:	00 01                	add    %al,(%rcx)
  4020c5:	78 10                	js     4020d7 <__GNU_EH_FRAME_HDR+0x67>
  4020c7:	01 1b                	add    %ebx,(%rbx)
  4020c9:	0c 07                	or     $0x7,%al
  4020cb:	08 90 01 00 00 10    	or     %dl,0x10000001(%rax)
  4020d1:	00 00                	add    %al,(%rax)
  4020d3:	00 1c 00             	add    %bl,(%rax,%rax,1)
  4020d6:	00 00                	add    %al,(%rax)
  4020d8:	e8 ef ff ff 26       	call   274020cc <_end+0x26ffe06c>
  4020dd:	00 00                	add    %al,(%rax)
  4020df:	00 00                	add    %al,(%rax)
  4020e1:	44 07                	rex.R (bad)
  4020e3:	10 10                	adc    %dl,(%rax)
  4020e5:	00 00                	add    %al,(%rax)
  4020e7:	00 30                	add    %dh,(%rax)
  4020e9:	00 00                	add    %al,(%rax)
  4020eb:	00 04 f0             	add    %al,(%rax,%rsi,8)
  4020ee:	ff                   	(bad)
  4020ef:	ff 05 00 00 00 00    	incl   0x0(%rip)        # 4020f5 <__GNU_EH_FRAME_HDR+0x85>
  4020f5:	00 00                	add    %al,(%rax)
  4020f7:	00 24 00             	add    %ah,(%rax,%rax,1)
  4020fa:	00 00                	add    %al,(%rax)
  4020fc:	44 00 00             	add    %r8b,(%rax)
  4020ff:	00 20                	add    %ah,(%rax)
  402101:	ef                   	out    %eax,(%dx)
  402102:	ff                   	(bad)
  402103:	ff a0 00 00 00 00    	jmp    *0x0(%rax)
  402109:	0e                   	(bad)
  40210a:	10 46 0e             	adc    %al,0xe(%rsi)
  40210d:	18 4a 0f             	sbb    %cl,0xf(%rdx)
  402110:	0b 77 08             	or     0x8(%rdi),%esi
  402113:	80 00 3f             	addb   $0x3f,(%rax)
  402116:	1a 3b                	sbb    (%rbx),%bh
  402118:	2a 33                	sub    (%rbx),%dh
  40211a:	24 22                	and    $0x22,%al
  40211c:	00 00                	add    %al,(%rax)
  40211e:	00 00                	add    %al,(%rax)
  402120:	1c 00                	sbb    $0x0,%al
  402122:	00 00                	add    %al,(%rax)
  402124:	6c                   	insb   (%dx),%es:(%rdi)
  402125:	00 00                	add    %al,(%rax)
  402127:	00 fe                	add    %bh,%dh
  402129:	f1                   	int1
  40212a:	ff                   	(bad)
  40212b:	ff 59 00             	lcall  *0x0(%rcx)
  40212e:	00 00                	add    %al,(%rax)
  402130:	00 41 0e             	add    %al,0xe(%rcx)
  402133:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  402139:	02 54 0c 07          	add    0x7(%rsp,%rcx,1),%dl
  40213d:	08 00                	or     %al,(%rax)
  40213f:	00 1c 00             	add    %bl,(%rax,%rax,1)
  402142:	00 00                	add    %al,(%rax)
  402144:	00 00                	add    %al,(%rax)
  402146:	00 00                	add    %al,(%rax)
  402148:	01 7a 50             	add    %edi,0x50(%rdx)
  40214b:	4c 52                	rex.WR push %rdx
  40214d:	00 01                	add    %al,(%rcx)
  40214f:	78 10                	js     402161 <__GNU_EH_FRAME_HDR+0xf1>
  402151:	07                   	(bad)
  402152:	03 90 10 40 00 03    	add    0x3004010(%rax),%edx
  402158:	1b 0c 07             	sbb    (%rdi,%rax,1),%ecx
  40215b:	08 90 01 00 00 20    	or     %dl,0x20000001(%rax)
  402161:	00 00                	add    %al,(%rax)
  402163:	00 24 00             	add    %ah,(%rax,%rax,1)
  402166:	00 00                	add    %al,(%rax)
  402168:	18 f2                	sbb    %dh,%dl
  40216a:	ff                   	(bad)
  40216b:	ff 26                	jmp    *(%rsi)
  40216d:	00 00                	add    %al,(%rax)
  40216f:	00 04 d8             	add    %al,(%rax,%rbx,8)
  402172:	21 40 00             	and    %eax,0x0(%rax)
  402175:	41 0e                	rex.B (bad)
  402177:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  40217d:	61                   	(bad)
  40217e:	0c 07                	or     $0x7,%al
  402180:	08 00                	or     %al,(%rax)
  402182:	00 00                	add    %al,(%rax)
  402184:	24 00                	and    $0x0,%al
  402186:	00 00                	add    %al,(%rax)
  402188:	48 00 00             	rex.W add %al,(%rax)
  40218b:	00 1a                	add    %bl,(%rdx)
  40218d:	f0 ff                	lock (bad)
  40218f:	ff 26                	jmp    *(%rsi)
  402191:	01 00                	add    %eax,(%rax)
  402193:	00 04 dc             	add    %al,(%rsp,%rbx,8)
  402196:	21 40 00             	and    %eax,0x0(%rax)
  402199:	41 0e                	rex.B (bad)
  40219b:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  4021a1:	45 83 03 03          	rex.RB addl $0x3,(%r11)
  4021a5:	1c 01                	sbb    $0x1,%al
  4021a7:	0c 07                	or     $0x7,%al
  4021a9:	08 00                	or     %al,(%rax)
  4021ab:	00 24 00             	add    %ah,(%rax,%rax,1)
  4021ae:	00 00                	add    %al,(%rax)
  4021b0:	70 00                	jo     4021b2 <__GNU_EH_FRAME_HDR+0x142>
  4021b2:	00 00                	add    %al,(%rax)
  4021b4:	18 f1                	sbb    %dh,%cl
  4021b6:	ff                   	(bad)
  4021b7:	ff 59 00             	lcall  *0x0(%rcx)
  4021ba:	00 00                	add    %al,(%rax)
  4021bc:	04 00                	add    $0x0,%al
  4021be:	22 40 00             	and    0x0(%rax),%al
  4021c1:	41 0e                	rex.B (bad)
  4021c3:	10 86 02 43 0d 06    	adc    %al,0x60d4302(%rsi)
  4021c9:	45 83 03 02          	rex.RB addl $0x2,(%r11)
  4021cd:	4f 0c 07             	rex.WRXB or $0x7,%al
  4021d0:	08 00                	or     %al,(%rax)
  4021d2:	00 00                	add    %al,(%rax)
  4021d4:	00 00                	add    %al,(%rax)
	...

Disassembly of section .gcc_except_table:

00000000004021d8 <.gcc_except_table>:
  4021d8:	ff                   	(bad)
  4021d9:	ff 01                	incl   (%rcx)
  4021db:	00 ff                	add    %bh,%bh
  4021dd:	ff 01                	incl   (%rcx)
  4021df:	1d 24 05 00 00       	sbb    $0x524,%eax
  4021e4:	35 05 ed 01 00       	xor    $0x1ed05,%eax
  4021e9:	46 05 dc 01 00 57    	rex.RX add $0x570001dc,%eax
  4021ef:	05 cb 01 00 68       	add    $0x680001cb,%eax
  4021f4:	05 ba 01 00 96       	add    $0x960001ba,%eax
  4021f9:	02 05 00 00 00 00    	add    0x0(%rip),%al        # 4021ff <__GNU_EH_FRAME_HDR+0x18f>
  4021ff:	00 ff                	add    %bh,%bh
  402201:	03 19                	add    (%rcx),%ebx
  402203:	01 10                	add    %edx,(%rax)
  402205:	09 05 15 01 1e 05    	or     %eax,0x51e0115(%rip)        # 55e2320 <_end+0x51de2c0>
  40220b:	00 00                	add    %al,(%rax)
  40220d:	34 05                	xor    $0x5,%al
  40220f:	40 00 4e 05          	rex add %cl,0x5(%rsi)
  402213:	00 00                	add    %al,(%rax)
  402215:	01 00                	add    %eax,(%rax)
  402217:	00 48 20             	add    %cl,0x20(%rax)
  40221a:	40                   	rex
	...

Disassembly of section .init_array:

0000000000403d60 <.init_array>:
  403d60:	a0                   	.byte 0xa0
  403d61:	11 40 00             	adc    %eax,0x0(%rax)
  403d64:	00 00                	add    %al,(%rax)
	...

Disassembly of section .fini_array:

0000000000403d68 <.fini_array>:
  403d68:	70 11                	jo     403d7b <_ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3+0xb>
  403d6a:	40 00 00             	rex add %al,(%rax)
  403d6d:	00 00                	add    %al,(%rax)
	...

Disassembly of section .data.rel.ro:

0000000000403d70 <_ZTVN10__cxxabiv117__class_type_infoE@CXXABI_1.3>:
	...

Disassembly of section .dynamic:

0000000000403dc8 <_DYNAMIC>:
  403dc8:	01 00                	add    %eax,(%rax)
  403dca:	00 00                	add    %al,(%rax)
  403dcc:	00 00                	add    %al,(%rax)
  403dce:	00 00                	add    %al,(%rax)
  403dd0:	06                   	(bad)
  403dd1:	01 00                	add    %eax,(%rax)
  403dd3:	00 00                	add    %al,(%rax)
  403dd5:	00 00                	add    %al,(%rax)
  403dd7:	00 01                	add    %al,(%rcx)
  403dd9:	00 00                	add    %al,(%rax)
  403ddb:	00 00                	add    %al,(%rax)
  403ddd:	00 00                	add    %al,(%rax)
  403ddf:	00 15 01 00 00 00    	add    %dl,0x1(%rip)        # 403de6 <_DYNAMIC+0x1e>
  403de5:	00 00                	add    %al,(%rax)
  403de7:	00 01                	add    %al,(%rcx)
  403de9:	00 00                	add    %al,(%rax)
  403deb:	00 00                	add    %al,(%rax)
  403ded:	00 00                	add    %al,(%rax)
  403def:	00 1f                	add    %bl,(%rdi)
  403df1:	01 00                	add    %eax,(%rax)
  403df3:	00 00                	add    %al,(%rax)
  403df5:	00 00                	add    %al,(%rax)
  403df7:	00 01                	add    %al,(%rcx)
  403df9:	00 00                	add    %al,(%rax)
  403dfb:	00 00                	add    %al,(%rax)
  403dfd:	00 00                	add    %al,(%rax)
  403dff:	00 2d 01 00 00 00    	add    %ch,0x1(%rip)        # 403e06 <_DYNAMIC+0x3e>
  403e05:	00 00                	add    %al,(%rax)
  403e07:	00 0c 00             	add    %cl,(%rax,%rax,1)
  403e0a:	00 00                	add    %al,(%rax)
  403e0c:	00 00                	add    %al,(%rax)
  403e0e:	00 00                	add    %al,(%rax)
  403e10:	00 10                	add    %dl,(%rax)
  403e12:	40 00 00             	rex add %al,(%rax)
  403e15:	00 00                	add    %al,(%rax)
  403e17:	00 0d 00 00 00 00    	add    %cl,0x0(%rip)        # 403e1d <_DYNAMIC+0x55>
  403e1d:	00 00                	add    %al,(%rax)
  403e1f:	00 a8 13 40 00 00    	add    %ch,0x4013(%rax)
  403e25:	00 00                	add    %al,(%rax)
  403e27:	00 19                	add    %bl,(%rcx)
  403e29:	00 00                	add    %al,(%rax)
  403e2b:	00 00                	add    %al,(%rax)
  403e2d:	00 00                	add    %al,(%rax)
  403e2f:	00 60 3d             	add    %ah,0x3d(%rax)
  403e32:	40 00 00             	rex add %al,(%rax)
  403e35:	00 00                	add    %al,(%rax)
  403e37:	00 1b                	add    %bl,(%rbx)
  403e39:	00 00                	add    %al,(%rax)
  403e3b:	00 00                	add    %al,(%rax)
  403e3d:	00 00                	add    %al,(%rax)
  403e3f:	00 08                	add    %cl,(%rax)
  403e41:	00 00                	add    %al,(%rax)
  403e43:	00 00                	add    %al,(%rax)
  403e45:	00 00                	add    %al,(%rax)
  403e47:	00 1a                	add    %bl,(%rdx)
  403e49:	00 00                	add    %al,(%rax)
  403e4b:	00 00                	add    %al,(%rax)
  403e4d:	00 00                	add    %al,(%rax)
  403e4f:	00 68 3d             	add    %ch,0x3d(%rax)
  403e52:	40 00 00             	rex add %al,(%rax)
  403e55:	00 00                	add    %al,(%rax)
  403e57:	00 1c 00             	add    %bl,(%rax,%rax,1)
  403e5a:	00 00                	add    %al,(%rax)
  403e5c:	00 00                	add    %al,(%rax)
  403e5e:	00 00                	add    %al,(%rax)
  403e60:	08 00                	or     %al,(%rax)
  403e62:	00 00                	add    %al,(%rax)
  403e64:	00 00                	add    %al,(%rax)
  403e66:	00 00                	add    %al,(%rax)
  403e68:	f5                   	cmc
  403e69:	fe                   	(bad)
  403e6a:	ff 6f 00             	ljmp   *0x0(%rdi)
  403e6d:	00 00                	add    %al,(%rax)
  403e6f:	00 c0                	add    %al,%al
  403e71:	03 40 00             	add    0x0(%rax),%eax
  403e74:	00 00                	add    %al,(%rax)
  403e76:	00 00                	add    %al,(%rax)
  403e78:	05 00 00 00 00       	add    $0x0,%eax
  403e7d:	00 00                	add    %al,(%rax)
  403e7f:	00 50 05             	add    %dl,0x5(%rax)
  403e82:	40 00 00             	rex add %al,(%rax)
  403e85:	00 00                	add    %al,(%rax)
  403e87:	00 06                	add    %al,(%rsi)
  403e89:	00 00                	add    %al,(%rax)
  403e8b:	00 00                	add    %al,(%rax)
  403e8d:	00 00                	add    %al,(%rax)
  403e8f:	00 e8                	add    %ch,%al
  403e91:	03 40 00             	add    0x0(%rax),%eax
  403e94:	00 00                	add    %al,(%rax)
  403e96:	00 00                	add    %al,(%rax)
  403e98:	0a 00                	or     (%rax),%al
  403e9a:	00 00                	add    %al,(%rax)
  403e9c:	00 00                	add    %al,(%rax)
  403e9e:	00 00                	add    %al,(%rax)
  403ea0:	6b 01 00             	imul   $0x0,(%rcx),%eax
  403ea3:	00 00                	add    %al,(%rax)
  403ea5:	00 00                	add    %al,(%rax)
  403ea7:	00 0b                	add    %cl,(%rbx)
  403ea9:	00 00                	add    %al,(%rax)
  403eab:	00 00                	add    %al,(%rax)
  403ead:	00 00                	add    %al,(%rax)
  403eaf:	00 18                	add    %bl,(%rax)
  403eb1:	00 00                	add    %al,(%rax)
  403eb3:	00 00                	add    %al,(%rax)
  403eb5:	00 00                	add    %al,(%rax)
  403eb7:	00 15 00 00 00 00    	add    %dl,0x0(%rip)        # 403ebd <_DYNAMIC+0xf5>
	...
  403ec5:	00 00                	add    %al,(%rax)
  403ec7:	00 03                	add    %al,(%rbx)
  403ec9:	00 00                	add    %al,(%rax)
  403ecb:	00 00                	add    %al,(%rax)
  403ecd:	00 00                	add    %al,(%rax)
  403ecf:	00 e8                	add    %ch,%al
  403ed1:	3f                   	(bad)
  403ed2:	40 00 00             	rex add %al,(%rax)
  403ed5:	00 00                	add    %al,(%rax)
  403ed7:	00 02                	add    %al,(%rdx)
  403ed9:	00 00                	add    %al,(%rax)
  403edb:	00 00                	add    %al,(%rax)
  403edd:	00 00                	add    %al,(%rax)
  403edf:	00 d8                	add    %bl,%al
  403ee1:	00 00                	add    %al,(%rax)
  403ee3:	00 00                	add    %al,(%rax)
  403ee5:	00 00                	add    %al,(%rax)
  403ee7:	00 14 00             	add    %dl,(%rax,%rax,1)
  403eea:	00 00                	add    %al,(%rax)
  403eec:	00 00                	add    %al,(%rax)
  403eee:	00 00                	add    %al,(%rax)
  403ef0:	07                   	(bad)
  403ef1:	00 00                	add    %al,(%rax)
  403ef3:	00 00                	add    %al,(%rax)
  403ef5:	00 00                	add    %al,(%rax)
  403ef7:	00 17                	add    %dl,(%rdi)
  403ef9:	00 00                	add    %al,(%rax)
  403efb:	00 00                	add    %al,(%rax)
  403efd:	00 00                	add    %al,(%rax)
  403eff:	00 d8                	add    %bl,%al
  403f01:	07                   	(bad)
  403f02:	40 00 00             	rex add %al,(%rax)
  403f05:	00 00                	add    %al,(%rax)
  403f07:	00 07                	add    %al,(%rdi)
  403f09:	00 00                	add    %al,(%rax)
  403f0b:	00 00                	add    %al,(%rax)
  403f0d:	00 00                	add    %al,(%rax)
  403f0f:	00 60 07             	add    %ah,0x7(%rax)
  403f12:	40 00 00             	rex add %al,(%rax)
  403f15:	00 00                	add    %al,(%rax)
  403f17:	00 08                	add    %cl,(%rax)
  403f19:	00 00                	add    %al,(%rax)
  403f1b:	00 00                	add    %al,(%rax)
  403f1d:	00 00                	add    %al,(%rax)
  403f1f:	00 78 00             	add    %bh,0x0(%rax)
  403f22:	00 00                	add    %al,(%rax)
  403f24:	00 00                	add    %al,(%rax)
  403f26:	00 00                	add    %al,(%rax)
  403f28:	09 00                	or     %eax,(%rax)
  403f2a:	00 00                	add    %al,(%rax)
  403f2c:	00 00                	add    %al,(%rax)
  403f2e:	00 00                	add    %al,(%rax)
  403f30:	18 00                	sbb    %al,(%rax)
  403f32:	00 00                	add    %al,(%rax)
  403f34:	00 00                	add    %al,(%rax)
  403f36:	00 00                	add    %al,(%rax)
  403f38:	fe                   	(bad)
  403f39:	ff                   	(bad)
  403f3a:	ff 6f 00             	ljmp   *0x0(%rdi)
  403f3d:	00 00                	add    %al,(%rax)
  403f3f:	00 e0                	add    %ah,%al
  403f41:	06                   	(bad)
  403f42:	40 00 00             	rex add %al,(%rax)
  403f45:	00 00                	add    %al,(%rax)
  403f47:	00 ff                	add    %bh,%bh
  403f49:	ff                   	(bad)
  403f4a:	ff 6f 00             	ljmp   *0x0(%rdi)
  403f4d:	00 00                	add    %al,(%rax)
  403f4f:	00 03                	add    %al,(%rbx)
  403f51:	00 00                	add    %al,(%rax)
  403f53:	00 00                	add    %al,(%rax)
  403f55:	00 00                	add    %al,(%rax)
  403f57:	00 f0                	add    %dh,%al
  403f59:	ff                   	(bad)
  403f5a:	ff 6f 00             	ljmp   *0x0(%rdi)
  403f5d:	00 00                	add    %al,(%rax)
  403f5f:	00 bc 06 40 00 00 00 	add    %bh,0x40(%rsi,%rax,1)
	...

Disassembly of section .got:

0000000000403fc8 <.got>:
	...

Disassembly of section .got.plt:

0000000000403fe8 <_GLOBAL_OFFSET_TABLE_>:
  403fe8:	c8 3d 40 00          	enter  $0x403d,$0x0
	...
  404000:	36 10 40 00          	ss adc %al,0x0(%rax)
  404004:	00 00                	add    %al,(%rax)
  404006:	00 00                	add    %al,(%rax)
  404008:	46 10 40 00          	rex.RX adc %r8b,0x0(%rax)
  40400c:	00 00                	add    %al,(%rax)
  40400e:	00 00                	add    %al,(%rax)
  404010:	56                   	push   %rsi
  404011:	10 40 00             	adc    %al,0x0(%rax)
  404014:	00 00                	add    %al,(%rax)
  404016:	00 00                	add    %al,(%rax)
  404018:	66 10 40 00          	data16 adc %al,0x0(%rax)
  40401c:	00 00                	add    %al,(%rax)
  40401e:	00 00                	add    %al,(%rax)
  404020:	76 10                	jbe    404032 <_GLOBAL_OFFSET_TABLE_+0x4a>
  404022:	40 00 00             	rex add %al,(%rax)
  404025:	00 00                	add    %al,(%rax)
  404027:	00 86 10 40 00 00    	add    %al,0x4010(%rsi)
  40402d:	00 00                	add    %al,(%rax)
  40402f:	00 96 10 40 00 00    	add    %dl,0x4010(%rsi)
  404035:	00 00                	add    %al,(%rax)
  404037:	00 a6 10 40 00 00    	add    %ah,0x4010(%rsi)
  40403d:	00 00                	add    %al,(%rax)
  40403f:	00 b6 10 40 00 00    	add    %dh,0x4010(%rsi)
  404045:	00 00                	add    %al,(%rax)
	...

Disassembly of section .data:

0000000000404048 <__data_start>:
	...

0000000000404050 <__dso_handle>:
	...

Disassembly of section .comment:

0000000000000000 <.comment>:
   0:	47                   	rex.RXB
   1:	43                   	rex.XB
   2:	43 3a 20             	rex.XB cmp (%r8),%spl
   5:	28 47 4e             	sub    %al,0x4e(%rdi)
   8:	55                   	push   %rbp
   9:	29 20                	sub    %esp,(%rax)
   b:	31 34 2e             	xor    %esi,(%rsi,%rbp,1)
   e:	32 2e                	xor    (%rsi),%ch
  10:	31 20                	xor    %esp,(%rax)
  12:	32 30                	xor    (%rax),%dh
  14:	32 34 30             	xor    (%rax,%rsi,1),%dh
  17:	38 30                	cmp    %dh,(%rax)
  19:	35 00 47 43 43       	xor    $0x43434700,%eax
  1e:	3a 20                	cmp    (%rax),%ah
  20:	28 47 4e             	sub    %al,0x4e(%rdi)
  23:	55                   	push   %rbp
  24:	29 20                	sub    %esp,(%rax)
  26:	31 34 2e             	xor    %esi,(%rsi,%rbp,1)
  29:	32 2e                	xor    (%rsi),%ch
  2b:	31 20                	xor    %esp,(%rax)
  2d:	32 30                	xor    (%rax),%dh
  2f:	32 34 30             	xor    (%rax,%rsi,1),%dh
  32:	39 31                	cmp    %esi,(%rcx)
  34:	30 00                	xor    %al,(%rax)
