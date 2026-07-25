# CLion remote docker environment (How to build docker container, run and stop it)
#
# Build and run:
# environment variable neededs锛?
#       export DOCKER_BUILDKIT=1
#       export COMPOSE_DOCKER_CLI_BUILD=1

#   docker build -t arch_clion_remote:0.1 -f arch_clion_remote.DockerFile .
#   docker run -d --privileged -v /data:/data -v ~/.ssh:/root/.ssh:ro -v /var/run/docker.sock:/var/run/docker.sock  -p 30022:22 --name cb arch_clion_remote:0.1
#
# stop:
#   docker stop clion_remote_env
#
# ssh credentials (test user):
#   user@password

FROM arch_clion_local:0.1

RUN pacman -S --noconfirm openssh

# 创建用户并设置密码
RUN set -e && \
    useradd -m user && \
    echo "user:quyysfa93@FFqw1f2q3" | chpasswd && \
    echo "root:quyysfa93@FFqw1f2q3" | chpasswd && \
    usermod -s /bin/bash user && \
    ls -al /root && \
    echo "user ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers


# 创建必要的目录并生成 SSH 主机密钥
RUN mkdir -p /var/run/sshd /etc/ssh && \
    ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N "" && \
    ssh-keygen -t ecdsa -f /etc/ssh/ssh_host_ecdsa_key -N "" && \
    ssh-keygen -t ed25519 -f /etc/ssh/ssh_host_ed25519_key -N "" && \
    chmod 0700 /etc/ssh && chmod 0600 /etc/ssh/ssh_host_*


# 配置 SSH
RUN cp /etc/ssh/sshd_config /etc/ssh/sshd_config.orig && \
    sed -i 's/.*session.*required.*pam_loginuid.so.*/session optional pam_loginuid.so/g' /etc/pam.d/sshd && \
    echo 'LANG="en_US.UTF-8"' > /etc/default/locale
COPY sshd_config /etc/ssh/sshd_config


# 设置时区为东8区（中国标准时间 CST）
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime && \
    echo "Asia/Shanghai" > /etc/timezone

# 暴露 SSH 端口
EXPOSE 22

# 启动 SSH 服务
CMD ["/usr/sbin/sshd", "-D", "-e"]