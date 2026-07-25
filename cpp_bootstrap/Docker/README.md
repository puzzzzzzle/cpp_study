# docker build 依赖

~~ 使用了 docker plus 插件， 需要添加以下环境变量 ~~ 已经不再使用这种方式了, 忽略
```shell
export DOCKER_BUILDKIT=1 &&export COMPOSE_DOCKER_CLI_BUILD=1
```
不想添加的话， 可以直接用 `base_libs.DockerFile` 内容， 替换 `INCLUDE+ base_libs.DockerFile`