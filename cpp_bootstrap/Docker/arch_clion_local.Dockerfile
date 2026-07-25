# Build and run:
# environment variable neededs：
#       export DOCKER_BUILDKIT=1
#       export COMPOSE_DOCKER_CLI_BUILD=1
#   docker build -t arch_clion_local:0.1 -f arch_clion_local.Dockerfile .
#   docker run -it --name cb arch_clion_local:0.1 /bin/bash
#   docker start -ia cb
FROM archlinux:latest

# 使用镜像
RUN mv /etc/pacman.d/mirrorlist /etc/pacman.d/mirrorlist_old \
    && echo 'Server = http://mirrors.aliyun.com/archlinux/$repo/os/$arch' > /etc/pacman.d/mirrorlist \
    && cat /etc/pacman.d/mirrorlist_old >> /etc/pacman.d/mirrorlist

# 更新包数据库并安装基本工具
RUN pacman -Syyu --noconfirm \
    && pacman -S --noconfirm \
    \
    tzdata \
    \
    base-devel \
    gcc \
    clang \
    cmake \
    ninja \
    nasm \
    autoconf \
    automake \
    gdb \
    \
    flex \
    bison \
    elfutils \
    bc \
    pahole \
    busybox \
    cpio \
    qemu-full \
    ovmf \
    \
    boost \
    gtest \
    opencv \
    fcgi \
    spawn-fcgi \
    libssh2 \
    openssl \
    simde \
    \
    dos2unix \
    rsync \
    tar \
    git \
    curl \
    zip \
    unzip \
    vim \
    lrzsz \
    less \
    vi \
    \
    python \
    python-pip \
    pybind11 \
    python-opencv \
    \
    lua \
    luarocks \
    \
    rocksdb \
    leveldb \
    \
    rapidjson \
    protobuf \
    capnproto \
    flatbuffers \
    spdlog \
    \
    poco \
    libuv \
    asio \
    zsh \
    \
    xorg-xauth \
    \
    && pacman -Scc --noconfirm

# 安装 Rust
RUN curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh -s -- -y --default-toolchain beta

# 安装 libunifex, 当前版本多线程编译有问题
RUN cd /tmp \
    && git clone https://github.com/facebookexperimental/libunifex.git \
    && cd libunifex \
    && cmake -G Ninja -H. -Bbuild -DCMAKE_CXX_STANDARD:STRING=23 -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_TESTING=OFF -DUNIFEX_BUILD_EXAMPLES=OFF \
    && cd build \
    && ninja -j 1 \
    && ninja install \
    && cd /tmp && rm -rf libunifex

# 安装 kcp
RUN cd /tmp \
    && git clone https://github.com/skywind3000/kcp.git \
    && cd kcp \
    && mkdir build \
    && cd build \
    && cmake .. -DCMAKE_INSTALL_PREFIX=/usr \
    && make -j `cat /proc/cpuinfo |grep "cores"|uniq|awk '{print $4}'` \
    && make install \
    && cd /tmp && rm -rf kcp

# 安装 libcpr 类似python requests的c++库
RUN cd /tmp \
    && git clone https://github.com/libcpr/cpr.git \
    && cd cpr \
    && git checkout 1.11.0 \
    && mkdir build \
    && cd build \
    && cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCPR_USE_SYSTEM_CURL=ON \
    && make -j `cat /proc/cpuinfo |grep "cores"|uniq|awk '{print $4}'` \
    && sudo make install \
    && cd /tmp && rm -rf cpr

# 安装 google benchmark
RUN cd /tmp \
    && git clone https://github.com/google/benchmark.git \
    && cd benchmark \
    && mkdir build \
    && cd build \
    && cmake .. -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr \
    && make -j `cat /proc/cpuinfo |grep "cores"|uniq|awk '{print $4}'`\
    && make install \
    && cd /tmp && rm -rf benchmark


# 安装 entt (header only)
RUN cd /tmp \
    && git clone https://github.com/skypjack/entt.git \
    && cd entt \
    && cp -vr src/entt /usr/include/ \
    && cd /tmp && rm -rf entt

# 安装 Microsoft proxy (header only)
RUN cd /tmp \
    && git clone https://github.com/microsoft/proxy.git \
    && cd proxy \
    && cp -vr include/proxy /usr/include/ \
    && cd /tmp && rm -rf proxy


# 配置bash
RUN echo '. "$HOME/.cargo/env"' >> /root/.bashrc \
    && echo "alias ll='ls -lh --color=auto'" >> /root/.bashrc


CMD ["/bin/bash"]