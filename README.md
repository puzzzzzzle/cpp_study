# personal_file_protector

#### 通用依赖
- STL 库
- posix（如：pthread）
- boost 库(...) cygwin : 包管理器中有 linux :apt 获取

- gtest 库   获取源码,直接cmake -DCMAKE_INSTALL_PREFIX=/usr ..
- openssl dev 库     cygwin : nasm(包管理器) perl(包管理器) 获取源码 ./Configure Cygwin-x86_64 no-asm --prefix=/usr   linux:直接apt获取
- yaml-cpp 0.6.0   github直接获取 编译 (注意是静态库,直接链接.a文件位置,eg; /usr/local/lib/libyaml-cpp.a)  动态库：cmake -DCMAKE_INSTALL_PREFIX=/usr -DBUILD_SHARED_LIBS=ON ..

- gui：qt5 qml qt quick

#### openssl使用的算法
- 编码 base64(测试用)
- 散列 md5 sha256
- 对称 AES > DES
- 非对称 RSA(暂时没用到)
####

### 各个模块
- [x]  src/change_rodata				：修改已编译动态链接库中的主密钥
- [x]  src/crypto_adaptor				：加密算法适配器
- [x]  src/file_coltroller				：文件管理器的逻辑实现
- [ ]  src/gui_qt						：qt实现的一个简单gui
- [ ]  src/main_controller				：主控，用于协调各个模快协作
- [x]  src/main_passwd				    ：主密钥的管理器
- [ ]  src/passwd_adaptor				：用户秘钥与文件秘钥的管理器
- [ ]  src/web_adaptor				    ：简单的网络实时解密浏览实现

