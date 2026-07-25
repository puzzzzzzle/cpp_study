# 简单字符设备驱动（Simple Char Device Driver）

一个最小化的 Linux 字符设备驱动示例，用于在自编 Linux 内核上学习和验证内核模块开发流程。

## 文件结构

```
simple_char_device/
├── simple_char_driver.c   # 驱动源码
├── Makefile               # 编译脚本（指向自编内核源码树）
└── README.md              # 本文档
```

## 硬件/内核环境

- **运行内核**: 自编 Linux v7.0-rc7（位于 `../linux_build/linux/`）
- **运行平台**: QEMU 虚拟机（i440FX，磁盘镜像模式）
- **根文件系统**: Alpine Linux（qcow2 磁盘镜像）

## 编译

Makefile 的 `KDIR` 已指向自编内核源码树，直接 `make` 即可：

```bash
cd /data/srcs/StudyRepos/cpp_study/src_linux_driver/simple_char_device
make
```

产物：`simple_char_driver.ko`

> 如果宿主机内核版本与自编内核不一致，不能直接用宿主机的 `/lib/modules/$(uname -r)/build` 编译，否则 insmod 会因 `vermagic` 不匹配而拒绝加载。Makefile 已配置为指向自编内核源码树。

## 拷贝到磁盘镜像

## 在 QEMU 中加载与测试

### 1. 启动 QEMU


### 2. 加载模块

```bash
insmod /root/simple_char_driver.ko
```

加载后 `/dev/simple_char_device` 自动创建，无需手动 `mknod`。

```bash
ls -l /dev/simple_char_device
# crw------- 1 root root 247, 0 ...
```

### 3. 测试

```bash
echo "Hello, World!" > /dev/simple_char_device
cat /dev/simple_char_device
# Hello, World!
```

### 4. 卸载模块

```bash
rmmod simple_char_driver
```

卸载后 `/dev/simple_char_device` 自动删除。

## 驱动功能说明

| 操作 | 行为 |
|---|---|
| `open` | 打印 `opened`，返回 0 |
| `read` | 从内部 1024 字节缓冲区读取，`ppos` 自动推进 |
| `write` | 写入内部缓冲区，空间不足返回 `-ENOSPC` |
| `release` | 打印 `closed` |

> 模块使用 **GPL** 授权，因为 `class_create` / `device_create` / `class_destroy` / `device_destroy` 是内核的 GPL-only 导出符号。若使用 MIT/BSD 等非 GPL 协议，`modpost` 阶段会报错拒绝链接。

## 手动创建设备节点（备用）

如果未启用 `class_create`/`device_create` 自动创建，或需兼容旧版驱动，可手动操作：

```bash
# 加载模块
insmod /root/simple_char_driver.ko

# 从 dmesg 或 /proc/devices 获取 major 号
dmesg | grep "simple_char_device" | tail -1
# simple_char_device: registered with major number 247

# 或者直接查 proc 文件系统
cat /proc/devices | grep simple_char_device
# 247 simple_char_device

# 手动创建设备节点
mknod /dev/simple_char_device c 247 0

# 测试
echo "Hello" > /dev/simple_char_device
cat /dev/simple_char_device

# 卸载时需手动删除节点
rmmod simple_char_driver
rm /dev/simple_char_device
```