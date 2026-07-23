# Linux 内核小版本 Debug 构建与 QEMU 调试指南

> 适用场景：在**无 KVM** 环境下，用 QEMU 软件模拟 x86_64 运行自定义编译的 Linux 内核。
> 核心目标：编译体积小、带完整调试信息的内核，配合 BusyBox initramfs 启动，并支持 GDB 断点调试。

---

## 1. 前置依赖

本流程基于 Arch Linux 环境，依赖均已包含在对应 Dockerfile 中。

```bash
sudo pacman -S --needed \
    base-devel gcc clang cmake ninja gdb nasm \
    flex bison elfutils bc pahole busybox cpio qemu-full ovmf
```

必需组件说明：

| 包 | 作用 |
|---|---|
| `flex` / `bison` | 编译内核的词法/语法分析器生成 |
| `elfutils` | ELF 处理，内核模块依赖 |
| `bc` | 编译时数学计算 |
| `pahole` | 可选，生成 BTF 调试信息 |
| `busybox` | 最小化用户态工具集 |
| `cpio` | 打包 initramfs |
| `qemu-full` | QEMU 全架构模拟器 |
| `ovmf` | UEFI 固件（可选）|

---

## 2. 目录约定

export L_BASE_DIR=/data/srcs/StudyRepos/cpp_study/src_linux_tests/linux_build 

---

## 3. 编译 Linux 内核（Debug 小版本）

### 3.1 清理并生成默认配置

```bash
cd ${L_BASE_DIR}/linux
make ARCH=x86_64 distclean
make ARCH=x86_64 defconfig
```

### 3.2 开启调试选项

```bash
./scripts/config \
    --enable CONFIG_DEBUG_INFO \
    --enable CONFIG_DEBUG_INFO_DWARF5 \
    --enable CONFIG_DEBUG_KERNEL \
    --enable CONFIG_KALLSYMS \
    --enable CONFIG_KALLSYMS_ALL \
    --enable CONFIG_GDB_SCRIPTS \
    --enable CONFIG_DEBUG_FS \
    --enable CONFIG_MAGIC_SYSRQ \
    --enable CONFIG_PROVE_LOCKING \
    --enable CONFIG_DEBUG_BUGVERBOSE

# 如需 BTF 调试信息（需要 pahole）
# ./scripts/config --enable CONFIG_DEBUG_INFO_BTF

# 关闭 KASLR，方便 GDB 定位符号
./scripts/config --disable CONFIG_RANDOMIZE_BASE

# 检查更新配置
make ARCH=x86_64 olddefconfig
```

### 3.4 编译

```bash
cd ${L_BASE_DIR}/linux
make ARCH=x86_64 -j$(nproc)
```

产物：

| 文件 | 说明 |
|---|---|
| `arch/x86/boot/bzImage` | 启动用压缩内核镜像 |
| `vmlinux` | 带完整符号表的 ELF，用于 GDB 调试 |

---

## 4. 构建 BusyBox initramfs

### 4.1 下载并配置 BusyBox

```bash
cd /data/srcs/StudyRepos
git clone https://git.busybox.net/busybox.git
cd busybox
```

#### 配置

BusyBox 没有 `scripts/config` 工具，直接编辑 `.config`：

```bash
cd ${L_BASE_DIR}
make defconfig

# 开启静态编译和调试信息
sed -i 's/^# CONFIG_STATIC is not set$/CONFIG_STATIC=y/' .config
sed -i 's/^# CONFIG_DEBUG is not set$/CONFIG_DEBUG=y/' .config
sed -i 's/^CONFIG_TC=y$/# CONFIG_TC is not set/' .config

# 同步配置（对新增/缺失项自动使用默认值）
make oldconfig
```


### 4.2 编译安装

```bash
cd ${L_BASE_DIR}/busybox
make -j$(nproc)
make install
```

安装目录默认为 `_install`。

### 4.3 构建 initramfs 目录结构

```bash
cd ${L_BASE_DIR}/busybox/_install

mkdir -p bin sbin etc proc sys usr/bin usr/sbin dev tmp mnt

# 创建基本设备节点
sudo mknod dev/console c 5 1
sudo mknod dev/null c 1 3
sudo mknod dev/tty c 5 0
sudo mknod dev/ttyS0 c 4 64
sudo mknod dev/ram0 b 1 0
sudo mknod dev/random c 1 8
sudo mknod dev/urandom c 1 9
```

### 4.4 创建 init 脚本

```bash
cat > init << 'EOF'
#!/bin/sh

# 挂载伪文件系统
mount -t proc none /proc
mount -t sysfs none /sys
mount -t devtmpfs none /dev 2>/dev/null || true
mount -t tmpfs none /tmp

# 如果 devtmpfs 没有自动创建关键终端设备，则手动创建
[ -c /dev/console ] || mknod -m 600 /dev/console c 5 1
[ -c /dev/null ]    || mknod -m 666 /dev/null c 1 3
[ -c /dev/tty ]     || mknod -m 666 /dev/tty c 5 0
[ -c /dev/ttyS0 ]   || mknod -m 666 /dev/ttyS0 c 4 64

# 设置主机名
hostname tinylinux

# 基本网络（可选）
ifconfig lo 127.0.0.1 up 2>/dev/null || true

echo "=== Linux $(uname -r) started ==="

# 启动交互式 shell，并通过 setsid + cttyhack 获取 /dev/console 作为控制终端
# 这样可以避免 "can't access tty; job control turned off" 警告
exec setsid cttyhack sh -l
EOF

chmod +x init
```

### 4.5 打包 initramfs

```bash
cd ${L_BASE_DIR}/busybox/_install

find . -print0 | cpio --null -ov --format=newc | gzip -9 > ${L_BASE_DIR}/initramfs.cpio.gz
```

---

## 5. QEMU 无 KVM 启动

### 5.1 基础启动命令

```bash
cd ${L_BASE_DIR}/linux

qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd ${L_BASE_DIR}/initramfs.cpio.gz \
    -append "console=ttyS0 nokaslr" \
    -serial stdio \
    -display none \
    -m 8192M \
    -smp 8
```

参数说明：

| 参数 | 含义 | 与 GRUB2 的对应关系 |
|---|---|---|
| `-kernel arch/x86/boot/bzImage` | 指定启动用压缩内核镜像路径 | 类似 GRUB2 的 `linux /boot/vmlinuz ...` 命令 |
| `-initrd *.cpio.gz` | 指定 initramfs（cpio.gz 格式），内核启动早期挂载 | 类似 GRUB2 的 `initrd /boot/initramfs.img` 命令 |
| `-append "..."` | 传递给内核的启动参数 | 类似 GRUB2 `linux ... ro console=ttyS0 quiet` 行中的参数部分 |
| `-append "console=ttyS0"` | 内核日志和 shell 输出重定向到第一个串口 | 与 GRUB2 的 `console=ttyS0` 作用相同 |
| `-append "nokaslr"` | 关闭内核地址空间布局随机化，便于 GDB 打断点 | 与 GRUB2 的 `nokaslr` 作用相同 |
| `-append "quiet"` | 减少启动日志输出 | 与 GRUB2 的 `quiet` 作用相同 |
| `-serial stdio` | 把 QEMU 模拟的第一个串口重定向到当前终端的 stdin/stdout | GRUB2 在实机上直接操作硬件串口，无此 QEMU 特有桥接 |
| `-display none` | 关闭 QEMU 的图形显示窗口，只用串口 | QEMU 特有选项；真机 GRUB2 无此概念 |
| `-m 512M` | 给虚拟机分配 512MB 内存 | 对应实机物理内存；也可用 `mem=512M` 限制内核可见内存 |
| `-smp 1` | 只模拟 1 个 CPU 核心 | GRUB2 环境通常不指定；`maxcpus=1` 可限制内核使用核心数 |

补充说明：

- `-kernel` 和 `-initrd` 是 QEMU 直接加载内核/ramdisk 的便捷方式，省去了模拟完整 BIOS/UEFI → bootloader → 内核 的流程。在真机 GRUB2 环境中，等价流程由 `linux` + `initrd` 两行命令完成。
- `-append` 里的所有字符串会被 QEMU 原样传给内核作为 **内核命令行参数（kernel command line）**，与 GRUB2 的 `linux` 行参数完全一致。
- `-serial stdio` 是 QEMU 特有的：QEMU 把模拟串口桥接到当前终端。GRUB2 在真机上通常直接操作硬件串口，不需要这个。

### 5.2 常用 QEMU 扩展启动

**带磁盘镜像启动：**

```bash
qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd ${L_BASE_DIR}/initramfs.cpio.gz \
    -hda disk.img \
    -append "console=ttyS0 nokaslr root=/dev/sda1 rw" \
    -serial stdio -display none \
    -m 8192M \
    -smp 8
```

新增参数说明：

| 参数 | 含义 | 与 GRUB2 的对应关系 |
|---|---|---|
| `-hda disk.img` | 把 `disk.img` 作为第一个 IDE/SATA 硬盘挂给虚拟机 | 类似 GRUB2 在实机上看到的第一块硬盘（如 `/dev/sda`）|
| `-append "root=/dev/sda1"` | 指定根文件系统所在设备 | 与 GRUB2 `linux ... root=/dev/sda1` 作用相同 |
| `-append "rw"` | 以读写方式挂载根文件系统 | 与 GRUB2 `linux ... rw` 作用相同 |

**带网络（用户模式 NAT）：**

```bash
qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd ${L_BASE_DIR}/initramfs.cpio.gz \
    -append "console=ttyS0 nokaslr ip=dhcp" \
    -serial stdio -display none \
    -m 8192M \
    -smp 8 \
    -nic user
```

```bash
qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd ${L_BASE_DIR}/initramfs.cpio.gz \
    -append "console=ttyS0 nokaslr ip=dhcp" \
    -serial pty -display none \
    -m 8192M \
    -smp 8 \
    -nic user
```

新增参数说明：

| 参数 | 含义 | 与 GRUB2 的对应关系 |
|---|---|---|
| `-nic user` | 启用 QEMU 用户模式网络栈（NAT，虚拟机可访问外网，宿主机不可主动访问虚拟机）| QEMU 特有；GRUB2 不处理网络，网络由内核/用户态接管 |
| `-append "ip=dhcp"` | 告诉 initramfs/networking 通过 DHCP 获取 IP | 与 GRUB2 `linux ... ip=dhcp` 作用相同 |

---

## 6. GDB 远程调试

### 6.1 启动 QEMU 并暂停在第一条指令

```bash
cd ${L_BASE_DIR}/linux

qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd ${L_BASE_DIR}/initramfs.cpio.gz \
    -append "console=ttyS0 nokaslr" \
    -serial stdio -display none  \
    -m 8192M \
    -smp 8 \
    -S -s
```

| 参数 | 含义 | 与 GRUB2 的对应关系 |
|---|---|---|
| `-S` | 启动时暂停 CPU，等待 GDB 连接 | QEMU 特有调试选项；GRUB2 无此功能 |
| `-s` | 开启 GDB stub server，监听 `localhost:1234` | QEMU 特有调试选项；GRUB2 无此功能 |

补充说明：

- `-S`（大写）是让虚拟机在第一条指令处暂停，必须配合 GDB `target remote :1234` 后 `continue` 才会继续启动。
- `-s`（小写）等价于 `-gdb tcp::1234`，开启 TCP 1234 端口的 GDB server。
- GRUB2 本身不是虚拟机监控器，不具备这些调试接口；在真机调试通常依赖 JTAG、KDB/kgdb 或 QEMU 虚拟化环境。

### 6.2 连接 GDB

在另一个终端执行：

```bash
cd ${L_BASE_DIR}/linux

# 使用系统 gdb
gdb ./vmlinux

# 或使用内核自带的 Python GDB 脚本
gdb -iex "add-auto-load-safe-path $(pwd)" ./vmlinux
```

在 GDB 中：

```gdb
(gdb) target remote :1234

# 在 start_kernel 打断点
(gdb) break start_kernel
(gdb) continue

# 常用命令
(gdb) info registers
(gdb) bt
(gdb) list
(gdb) step
(gdb) next
(gdb) print init_task
```

### 6.3 加载内核 GDB 脚本

Linux 源码编译后会生成辅助 GDB 的 Python 脚本 `vmlinux-gdb.py`。使用以下命令加载：

```bash
gdb ./vmlinux
```

启动时会自动加载当前目录下的 `vmlinux-gdb.py`，即可使用 Linux 专用命令：

```gdb
(gdb) lx-symbols
(gdb) lx-dmesg
(gdb) lx-ps
(gdb) lx-modules
```

---

## 7. 使用 Alpine Linux rootfs（替代 BusyBox）

相比 BusyBox，Alpine Linux minirootfs 自带完整的 `apk` 包管理器，可以直接 `apk add curl gcc git ...` 安装依赖，无需手动交叉编译。Alpine 使用 musl libc，和自编译内核完全兼容。

架构示意：

```
┌──────────────────────────────────────┐
│         自编译 Linux 内核              │
│         (本指南第 3 章的 bzImage)      │
├──────────────────────────────────────┤
│     Alpine Linux minirootfs           │
│   (apk 包管理 / musl libc / ...)      │
└──────────────────────────────────────┘
```

### 7.1 内核必需选项

以下选项必须编译进内核（`=y`），不能编译为模块（`=m`），否则 Alpine 启动会因缺少驱动而失败。

```bash
cd ${L_BASE_DIR}/linux

# ---- 基础文件系统支持 ----
./scripts/config \
    --enable CONFIG_DEVTMPFS \
    --enable CONFIG_DEVTMPFS_MOUNT \
    --enable CONFIG_TMPFS \
    --enable CONFIG_PROC_FS \
    --enable CONFIG_SYSFS

# ---- 磁盘与块设备 ----
./scripts/config \
    --enable CONFIG_BLK_DEV_SD \
    --enable CONFIG_BLK_DEV_LOOP \
    --enable CONFIG_ATA \
    --enable CONFIG_ATA_PIIX

# ---- 文件系统 ----
./scripts/config \
    --enable CONFIG_EXT4_FS \
    --enable CONFIG_OVERLAY_FS

# ---- VirtIO 驱动（QEMU 必需）----
./scripts/config \
    --enable CONFIG_VIRTIO_PCI \
    --enable CONFIG_VIRTIO_BLK \
    --enable CONFIG_VIRTIO_NET \
    --enable CONFIG_VIRTIO_MMIO

# ---- 网络协议栈（apk 下载包依赖）----
./scripts/config \
    --enable CONFIG_NET \
    --enable CONFIG_INET \
    --enable CONFIG_PACKET \
    --enable CONFIG_UNIX

# ---- 控制台支持 ----
./scripts/config \
    --enable CONFIG_TTY \
    --enable CONFIG_SERIAL_8250 \
    --enable CONFIG_SERIAL_8250_CONSOLE

./scripts/config --enable CONFIG_VT --enable CONFIG_VT_CONSOLE

make ARCH=x86_64 olddefconfig
```

各选项说明：

| 配置项 | 类别 | 说明 |
|---|---|---|
| `CONFIG_DEVTMPFS=y` | 设备管理 | 内核自动管理 `/dev` 设备节点，Alpine 的 init（OpenRC）依赖此特性 |
| `CONFIG_DEVTMPFS_MOUNT=y` | 设备管理 | 内核启动时自动挂载 devtmpfs 到 `/dev`，避免手动挂载 |
| `CONFIG_TMPFS=y` | 文件系统 | 内存文件系统，供 `/tmp`、`/run` 等临时目录使用 |
| `CONFIG_PROC_FS=y` | 文件系统 | `/proc` 伪文件系统，几乎所有用户态工具依赖 |
| `CONFIG_SYSFS=y` | 文件系统 | `/sys` 伪文件系统，设备模型、驱动绑定依赖 |
| `CONFIG_BLK_DEV_SD=y` | 块设备 | SCSI 磁盘驱动，QEMU 中 `-hda` 模拟的硬盘在 libata 下依赖此驱动 |
| `CONFIG_BLK_DEV_LOOP=y` | 块设备 | loop 设备支持，某些容器/镜像场景需要 |
| `CONFIG_ATA=y` | 块设备 | ATA 子系统总开关，IDE/SATA 驱动依赖此选项。`defconfig` 默认为 `m`，必须改成 `y` |
| `CONFIG_ATA_PIIX=y` | 块设备 | Intel PIIX IDE 控制器驱动，QEMU 默认 i440FX 机型 `-hda` 走此控制器 |
| `CONFIG_EXT4_FS=y` | 文件系统 | ext4 文件系统，磁盘镜像最常用格式 |
| `CONFIG_OVERLAY_FS=y` | 文件系统 | Overlay 文件系统，Docker/容器场景常用 |
| `CONFIG_VIRTIO_PCI=y` | VirtIO | VirtIO PCI 传输层，QEMU virtio 设备的总线基础 |
| `CONFIG_VIRTIO_BLK=y` | VirtIO | VirtIO 块设备驱动，QEMU 高性能磁盘访问 |
| `CONFIG_VIRTIO_NET=y` | VirtIO | VirtIO 网卡驱动，QEMU 高性能网络 |
| `CONFIG_VIRTIO_MMIO=y` | VirtIO | VirtIO MMIO 传输（某些嵌入式/轻量场景使用）|
| `CONFIG_NET=y` | 网络 | 网络子系统总开关 |
| `CONFIG_INET=y` | 网络 | TCP/IP 协议栈，`apk` 下载包通过 HTTPS 依赖 |
| `CONFIG_PACKET=y` | 网络 | AF_PACKET 套接字，DHCP 客户端（udhcpc）依赖 |
| `CONFIG_UNIX=y` | 网络 | Unix domain socket，大量用户态 IPC 依赖 |
| `CONFIG_TTY=y` | 控制台 | TTY 子系统，交互式 shell 依赖 |
| `CONFIG_SERIAL_8250=y` | 控制台 | 8250/16550 串口驱动，QEMU `-serial stdio` 依赖 |
| `CONFIG_SERIAL_8250_CONSOLE=y` | 控制台 | 串口控制台支持，`console=ttyS0` 依赖 |

> **注意**：这些选项在 `defconfig` 基础上通常**已经默认开启**。如果启动 Alpine 出现问题，对照上表逐项检查即可。v6.1+ 内核的 `defconfig` 已将 `CONFIG_VIRTIO_BLK` 等关键驱动默认编译进内核。

### 7.2 获取 Alpine minirootfs 并定制启动脚本

下载页面：[alpinelinux.org/downloads](https://alpinelinux.org/downloads/) → **Mini root filesystem**

```bash
# 下载并解压 minirootfs（版本按需修改）
ALPINE_VER=3.21.3
wget https://dl-cdn.alpinelinux.org/alpine/v3.21/releases/x86_64/alpine-minirootfs-${ALPINE_VER}-x86_64.tar.gz

mkdir -p ${L_BASE_DIR}/alpine-rootfs
cd ${L_BASE_DIR}/alpine-rootfs
tar xzf ../alpine-minirootfs-${ALPINE_VER}-x86_64.tar.gz

# ======== 定制 initramfs 启动流程 ========

# 1. 内核挂载 initramfs 后默认执行 /init，Alpine 的 init 在 /sbin/init
ln -sf /sbin/init init

# 2. 重写 /etc/inittab：去掉 OpenRC，配置串口+Vt 两套终端
#    原因：minirootfs 不含 OpenRC，会反复报 can't run '/sbin/openrc'
#          tty1~6 需要内核 CONFIG_VT=y，串口 ttyS0 需要 CONFIG_SERIAL_8250=y
sudo tee etc/inittab << 'INITTAB'
::sysinit:/bin/mount -t proc none /proc
::sysinit:/bin/mount -t sysfs none /sys
::sysinit:/bin/mount -t devtmpfs none /dev 2>/dev/null
::sysinit:/bin/mount -t tmpfs none /tmp
::sysinit:/bin/mount -t tmpfs none /run
::sysinit:/sbin/ip link set lo up
::sysinit:/sbin/ip link set eth0 up
::sysinit:/sbin/udhcpc -b -i eth0
::sysinit:echo "=== Alpine (kernel $(uname -r)) ==="
# serial console (QEMU -serial stdio / -display none)
ttyS0::respawn:/sbin/getty -n -l /bin/sh -L ttyS0 115200 vt100
# virtual terminals (QEMU 图形窗口内 Ctrl+Alt+F1~F6 切换, 需要 CONFIG_VT=y)
tty1::respawn:/sbin/getty -n -l /bin/sh 38400 tty1
tty2::respawn:/sbin/getty -n -l /bin/sh 38400 tty2
tty3::respawn:/sbin/getty -n -l /bin/sh 38400 tty3
::ctrlaltdel:/sbin/reboot
::shutdown:/bin/umount -a -r
INITTAB

find . -print0 | cpio --null -ov --format=newc | gzip -9 > ${L_BASE_DIR}/alpine-initramfs.cpio.gz

```

定制说明：

| 行 | 含义 |
|---|---|
| `::sysinit:/bin/mount ...` | 手动挂载 `/proc`、`/sys`、`/tmp`、`/run`（替代 OpenRC）|
| `::sysinit:/bin/mount -t devtmpfs ...` | 挂载 devtmpfs 到 `/dev`，`2>/dev/null` 静默 `Resource busy`（`CONFIG_DEVTMPFS_MOUNT=y` 已在磁盘模式自动挂载过，initramfs 模式需要手动挂）|
| `::sysinit:/sbin/ip link set ...` | 启用 `lo`（回环）和 `eth0` 网卡 |
| `::sysinit:/sbin/udhcpc ...` | 后台运行 DHCP 客户端获取 IP，`-b` 表示 lease 失败也继续守护 |
| `ttyS0::respawn:...` | 串口 shell：`-n` 跳过 login，`-l /bin/sh` 直接进 root shell |
| `tty1~3::respawn:...` | Vt shell（图形窗口内 `Ctrl+Alt+F1~F3` 切换），需 `CONFIG_VT=y` |
| `::shutdown:/bin/umount -a -r` | 关机时卸载所有文件系统 |

> **关于 tty 数量**：只配了 3 个 VT（tty1~3），足以覆盖多数调试场景。如需全部 6 个，按相同格式补上即可。VT 终端只在 QEMU 图形模式下生效（去掉 `-display none`），串口模式（`-serial stdio`）下 `/dev/tty1~3` 存在但不影响串口行为。

### 7.3 可选：预装软件包

```bash
# 配置 DNS（chroot 内联网下载需要）
echo 'nameserver 8.8.8.8' | sudo tee ${L_BASE_DIR}/alpine-rootfs/etc/resolv.conf

# chroot 进入 Alpine 环境
sudo chroot ${L_BASE_DIR}/alpine-rootfs /bin/sh

# 在 chroot 内操作：
apk update
apk add curl git gcc g++ make musl-dev  # 按需安装
# ... 装完退出
exit

# 清理 DNS（后续 QEMU 内 dhcp 会自动获取）
sudo rm ${L_BASE_DIR}/alpine-rootfs/etc/resolv.conf
```

### 7.4 启动方式

#### 方式一：initramfs（临时、重启丢失改动）

```bash
cd ${L_BASE_DIR}/alpine-rootfs
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ${L_BASE_DIR}/alpine-initramfs.cpio.gz

cd ${L_BASE_DIR}/linux
qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd ${L_BASE_DIR}/alpine-initramfs.cpio.gz \
    -append "console=ttyS0 nokaslr" \
    -serial stdio -display none \
    -m 8192M -smp 8 \
    -nic user
```

**带图形窗口（VT 终端，需内核 `CONFIG_VT=y`）：**

```bash
cd ${L_BASE_DIR}/linux
qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd ${L_BASE_DIR}/alpine-initramfs.cpio.gz \
    -append "console=ttyS0 console=tty0 nokaslr" \
    -serial stdio \
    -m 8192M -smp 8 \
    -nic user
```
##### vnc 图形(远程)
```
qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -initrd ${L_BASE_DIR}/alpine-initramfs.cpio.gz \
    -append "console=ttyS0 console=tty0 nokaslr" \
    -serial stdio \
    -vnc :0 \
    -m 8192M -smp 8 \
    -nic user 
```
关键差异：

| 参数 | 串口模式（上） | 图形模式（下） |
|---|---|---|
| `-display` | `-display none`（无窗口）| 省略，默认 `gtk` 打开图形窗口 |
| `console=` | `console=ttyS0` | `console=ttyS0 console=tty0`，日志同时输出到串口和 VT |
| 交互方式 | 在当前终端直接操作 | 串口照用 + QEMU 窗口内 `Ctrl+Alt+F1~F3` 切换 VT shell |
| 退出方式 | `Ctrl+A X` 或 `poweroff` | 关闭窗口或 `Ctrl+A X` |

> **提示**：VT 模式下如果弹出 QEMU 图形窗口后黑屏无内容，不用慌——shell 是通过 `Ctrl+Alt+F1`（或 F2/F3）切换出来的，图形窗口默认显示的是 `/dev/tty0`，可能需要按键激活。

#### 方式二：磁盘镜像（持久化、推荐开发用）

```bash
# 创建 4G 磁盘镜像并格式化
# 1. 用 raw 创建、格式化、拷贝（和文档里原来的步骤一样）
qemu-img create -f raw ${L_BASE_DIR}/alpine-disk.raw 4G
sudo mkfs.ext4 ${L_BASE_DIR}/alpine-disk.raw
mkdir -p /tmp/mnt-alpine
sudo mount -o loop ${L_BASE_DIR}/alpine-disk.raw /tmp/mnt-alpine
sudo cp -a ${L_BASE_DIR}/alpine-rootfs/* /tmp/mnt-alpine/
sudo umount /tmp/mnt-alpine

# 2. 转成 qcow2（thin provisioning）
qemu-img convert -f raw -O qcow2 ${L_BASE_DIR}/alpine-disk.raw ${L_BASE_DIR}/alpine-disk.qcow2

# 3. 删掉 raw（可选）
rm ${L_BASE_DIR}/alpine-disk.raw
rmdir /tmp/mnt-alpine 

# 启动（改动持久化）
cd ${L_BASE_DIR}/linux
qemu-system-x86_64 \
    -kernel arch/x86/boot/bzImage \
    -hda ${L_BASE_DIR}/alpine-disk.qcow2 \
    -append "console=ttyS0 nokaslr root=/dev/sda rw" \
    -serial stdio -display none \
    -m 8192M -smp 8 \
    -nic user
```

启动后即可在 Alpine 环境中使用 `apk add <package>` 安装任意依赖。
