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
kmain(): gdt_init() → screen_clear() → screen_puts(...) → echo 循环
        ▼
    "Hello from bare metal kernel!" 输出到 VGA(0xB8000) 和 serial(COM1)
        ▼
    echo 循环：com_getc() 读 COM1 字符 → 回显（回车换行 / 退格处理）
        ▼
    输入 "quit"/"exit" 回车 → 打印 "bye." → cli; hlt 停机
    其它输入 → 持续 echo
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
    ├── vga.h / vga.c # VGA 文本模式输出（仅写 0xB8000 帧缓冲）
    ├── com.h / com.c # COM1 串口 IO（仅管 0x3F8 端口 + inb/outb）
    ├── screen.h / screen.c # 组合层：screen_puts 同时写 VGA 与 COM
    └── kernel.c      # kmain 主体：echo 循环 + quit/exit 停机
```

## 构建与运行

前置依赖：`nasm`、`gcc`、`ld`、`qemu-system-i386`（均为常见发行版包）。

```bash
make          # 编译链接，生成 build/kernel.bin
./run.sh      # 启动 QEMU，加载 kernel.bin（-nographic，只看串口）

# 或一步到位：
make run

# 观察 VGA 文本模式输出（开图形窗口，串口仍接终端可交互）：
./run_vga.sh
```

`run.sh` 与 `run_vga.sh` 的区别：

| | `run.sh` | `run_vga.sh` |
|---|---|---|
| 显示方式 | `-nographic`：关图形窗口，COM1 接终端 | 默认图形窗口，显示 VGA(0xB8000) |
| 你能看到什么 | 仅串口输出（COM1） | VGA 黑底白字画面 + 终端串口交互 |
| 输入来源 | 键盘经串口 COM1 | 键盘经串口 COM1（不变） |
| 退出 | 输入 `quit`/`exit`，QEMU 自动退出 | 同左（`isa-debug-exit`） |

> 注：无论哪种方式，`screen_puts` 都**同时写 VGA 与 COM1**；`-nographic` 只是
> 把图形窗口关了，所以 `run.sh` 下你只能观察到串口这一路。

运行后预期输出（串口 & VGA）：

```
SeaBIOS (version ...)
iPXE ...                       ← 网卡 ROM，无害
Booting from ROM..
Hello from bare metal kernel!
32-bit protected mode, loaded by QEMU -kernel
echo mode: type something, it will be echoed back.
echo> 
```

进入 echo 模式后，在终端输入的字符会原样回显；回车换行后重新打印
`echo>` 提示符。注意：这是**回显模式**，不解析命令（输入 `ls` 只会回显 `ls`，
不会执行它）。

输入整行内容匹配 `quit` 或 `exit`（回车提交）时，内核打印 `bye.` 并停机
（`cli; hlt`），此后不再响应任何输入；用 `Ctrl-A x` 退出 QEMU。大小写敏感，
且需整行精确匹配（如 `quit!`、`Quit` 不会被识别）。

`run.sh` 使用 `-nographic`，把 serial（COM1）接到当前终端，因此无需图形界面
即可看到打印内容并交互。QEMU 在 echo 循环中会一直常驻，`Ctrl-A x` 可退出。

## 关键技术点

| 主题 | 说明 |
|---|---|
| Multiboot 头 | 二进制开头放 `0x1BADB002` 魔数 + 校验和，让 QEMU/GRUB 识别为内核 |
| freestanding | `-ffreestanding -nostdlib`，没有 libc，不调 `printf`/`memset` |
| BSS 清零 | C 未初始化全局变量需入口代码手动清 0，否则乱码 |
| 栈 | Multiboot 加载后栈不稳，入口手动设 `esp = stack_top`（预留 16KB BSS） |
| VGA 文本模式 | `vga.c` 写 `0xB8000` 起始内存，每字符 2 字节（ASCII + 属性），最简屏幕输出 |
| COM1 串口 IO | `com.c` 数据端口 `0x3F8`：写字符（`outb`）+ 读字符（`inb`）；LSR(`0x3F8+5`) 的 bit5=发送空 / bit0=数据就绪 |
| echo + 退出 | `kmain` 行缓冲：从 COM1 读字符回显，整行匹配 `quit`/`exit` 则停机（`cli;hlt`），无 libc 下自写 `str_eq` 比较 |
| GDT | 建 0=空 / 1=代码段 / 2=数据段 三个描述符，加载后刷新段寄存器 |

## 进一步可扩展方向

- 开启 64 位长模式（long mode）：建页表、切 CR0.PE / CR4.PAE / EFER.LME
- 实现键盘中断（IDT + PIC 初始化）
- 用 `-drive` + 自写 boot sector 替代 `-kernel`，完整走 SeaBIOS→GRUB 流程
- 接管 multiboot info（ebx），解析内存映射（e820）
