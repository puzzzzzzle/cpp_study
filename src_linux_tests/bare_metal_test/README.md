# bare_metal_test —— 32 位保护模式裸机最小内核

本目录是一个**最小可运行的裸机内核示例**，用来替代 `bzImage`，通过
`qemu -kernel` 直接加载执行，从而直观理解「上电 → BIOS → 加载内核 → 接管 CPU」
这条链路中，内核本身是如何被加载、如何初始化、如何输出、如何停机的。

## 它和真实内核的关系

```
物理机：   上电 → BIOS/UEFI → GRUB → bzImage → init
QEMU：    qemu 进程 → SeaBIOS（固件）→ -kernel kernel.bin → kmain
```

本工程用我们自己的 `kernel.bin` **完全替代了 `bzImage` 的角色**：
SeaBIOS 不关心它是 Linux 还是裸机程序，只认 Multiboot 头。

## 启动流程

```
qemu-system-i386 -kernel build/kernel.bin
        │
        ▼ SeaBIOS 固件（QEMU 自带，等价物理机 BIOS）
        │  识别 Multiboot 头 (0x1BADB002)
        │  把 kernel.bin 加载到 0x100000，切到 32 位保护模式
        ▼  跳到 _start（boot/entry.asm）
_start: 设 esp = stack_top → 清 BSS → call kmain
        ▼
kmain(): gdt_init() → screen_clear() → screen_puts(...)
        ▼
    "Hello from bare metal kernel!" 输出到 VGA(0xB8000) 和 serial(COM1)
        ▼
    cli; hlt   ← 停机，CPU 不再跑飞
```

> 注：使用 Multiboot 约定时，**切保护模式由加载器（SeaBIOS/GRUB）代劳**，
> 我们的程序拿到控制权时已经在 32 位保护模式。

## 目录结构

```
bare_metal_test/
├── Makefile          # 32 位 freestanding 编译 + 链接
├── link.ld           # 1MB 加载地址、multiboot 头在前、导出 BSS 符号
├── run.sh            # qemu-system-i386 -kernel build/kernel.bin -nographic
├── boot/
│   └── entry.asm     # Multiboot 头 + _start（设栈、清 BSS、调用 kmain）
└── kernel/
    ├── types.h       # 裸机定宽类型（u8/u16/u32，不依赖系统 stdint.h）
    ├── gdt.h / gdt.c # GDT 表（代码段/数据段 + 刷新段寄存器）
    ├── screen.h / screen.c # VGA 文本模式输出 + COM1 serial 输出
    └── kernel.c      # kmain 主体
```

## 构建与运行

前置依赖：`nasm`、`gcc`、`ld`、`qemu-system-i386`（均为常见发行版包）。

```bash
make          # 编译链接，生成 build/kernel.bin
./run.sh      # 启动 QEMU，加载 kernel.bin

# 或一步到位：
make run
```

运行后预期输出（串口 & VGA）：

```
SeaBIOS (version ...)
iPXE ...                       ← 网卡 ROM，无害
Booting from ROM..
Hello from bare metal kernel!
32-bit protected mode, loaded by QEMU -kernel
```

`run.sh` 使用 `-nographic`，把 serial（COM1）接到当前终端，因此无需图形界面
即可看到打印内容。QEMU 在 `hlt` 后会一直常驻，`Ctrl-A x` 可退出。

## 关键技术点

| 主题 | 说明 |
|---|---|
| Multiboot 头 | 二进制开头放 `0x1BADB002` 魔数 + 校验和，让 QEMU/GRUB 识别为内核 |
| freestanding | `-ffreestanding -nostdlib`，没有 libc，不调 `printf`/`memset` |
| BSS 清零 | C 未初始化全局变量需入口代码手动清 0，否则乱码 |
| 栈 | Multiboot 加载后栈不稳，入口手动设 `esp = stack_top`（预留 16KB BSS） |
| VGA 文本模式 | 写 `0xB8000` 起始内存，每字符 2 字节（ASCII + 属性），最简屏幕输出 |
| serial 输出 | 写 COM1 端口 `0x3F8`，配合 `-nographic` 在终端验证 |
| GDT | 建 0=空 / 1=代码段 / 2=数据段 三个描述符，加载后刷新段寄存器 |

## 进一步可扩展方向

- 开启 64 位长模式（long mode）：建页表、切 CR0.PE / CR4.PAE / EFER.LME
- 实现键盘中断（IDT + PIC 初始化）
- 用 `-drive` + 自写 boot sector 替代 `-kernel`，完整走 SeaBIOS→GRUB 流程
- 接管 multiboot info（ebx），解析内存映射（e820）
