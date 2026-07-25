#!/bin/bash
# 拉起容器, 可以进入容器做一些修改, 等退出容器后, 可以选择更新镜像(镜像名&tag不变), 然后删除容器
IMAGE_NAME="arch_clion_local:0.1"
CONTAINER_NAME="arch_clion_local_container"

# 1. 启动容器并进入
docker run --name $CONTAINER_NAME -it $IMAGE_NAME /bin/bash

# 2. 退出后，询问是否更新镜像
read -p "是否用修改后的容器内容更新镜像（y/n）? " answer
if [[ "$answer" == "y" || "$answer" == "Y" ]]; then
    docker commit $CONTAINER_NAME $IMAGE_NAME
    echo "镜像 $IMAGE_NAME 已更新。"
else
    echo "未更新镜像。"
fi

# 3. 删除容器
docker rm $CONTAINER_NAME

echo "容器 $CONTAINER_NAME 已删除。"