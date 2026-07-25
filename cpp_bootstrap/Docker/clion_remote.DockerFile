# CLion remote docker environment (How to build docker container, run and stop it)
#
# Build and run:
# environment variable neededs锛?
#       export DOCKER_BUILDKIT=1
#       export COMPOSE_DOCKER_CLI_BUILD=1

#   docker build -t clion_remote:0.1 -f clion_remote.DockerFile .
#    docker run -d --cap-add sys_ptrace -v /data:/data -p 30022:22 --name cb clion_remote:0.1
#
# stop:
#   docker stop clion_remote_env
#
# ssh credentials (test user):
#   user@password

FROM clion_local:0.1

# 设置环境变量，避免交互式提示
ENV DEBIAN_FRONTEND=noninteractive

# 创建用户并设置密码
RUN set -e && \
    useradd -m user && \
    echo "user:password" | chpasswd && \
    usermod -s /bin/bash user

# 创建必要的目录并生成 SSH 主机密钥
RUN mkdir -p /var/run/sshd /etc/ssh && \
    chmod 0700 /etc/ssh && \
    [ ! -f /etc/ssh/ssh_host_rsa_key ] && ssh-keygen -t rsa -f /etc/ssh/ssh_host_rsa_key -N "" || true && \
    [ ! -f /etc/ssh/ssh_host_dsa_key ] && ssh-keygen -t dsa -f /etc/ssh/ssh_host_dsa_key -N "" || true && \
    chmod 0600 /etc/ssh/ssh_host_rsa_key /etc/ssh/ssh_host_dsa_key

# 配置 SSH
RUN echo "PermitRootLogin yes" >> /etc/ssh/sshd_config && \
    echo "LogLevel DEBUG2" >> /etc/ssh/sshd_config && \
    echo "PasswordAuthentication yes" >> /etc/ssh/sshd_config && \
    sed -i 's/.*session.*required.*pam_loginuid.so.*/session optional pam_loginuid.so/g' /etc/pam.d/sshd && \
    echo 'LANG="en_US.UTF-8"' > /etc/default/locale

# 暴露 SSH 端口
EXPOSE 22

# 启动 SSH 服务
CMD ["/usr/sbin/sshd", "-D"]