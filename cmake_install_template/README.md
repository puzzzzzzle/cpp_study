- 测试cmake install 和 cpack
- 构建命令
```
cmake -DCMAKE_INSTALL_PREFIX=`pwd`/install .. # 避免安装到系统目录里去
make -j 8
cpack #单独打包某个平台: cpack -G TGZ  cpack -G RPM
make install # 或者 dpkg -i math-vec-1.0.0-Linux.deb
```
- 产物
```
➜  build git:(master) ✗ ll
total 116K
-rw-r--r-- 1 root root  15K Oct 11 15:48 CMakeCache.txt
drwxr-xr-x 7 root root 4.0K Oct 11 15:50 CMakeFiles
-rw-r--r-- 1 root root 4.9K Oct 11 15:48 cmake_install.cmake
-rw-r--r-- 1 root root 3.8K Oct 11 15:48 CPackConfig.cmake
drwxr-xr-x 3 root root 4.0K Oct 11 15:49 _CPack_Packages
-rw-r--r-- 1 root root 4.3K Oct 11 15:48 CPackSourceConfig.cmake
drwxr-xr-x 6 root root 4.0K Oct 11 15:50 install
-rw-r--r-- 1 root root  567 Oct 11 15:50 install_manifest.txt
-rw-r--r-- 1 root root 1.1K Oct 11 15:49 libmath_vec.a
-rw-r--r-- 1 root root 9.3K Oct 11 15:50 Makefile
-rw-r--r-- 1 root root 5.2K Oct 11 15:49 math-vec-1.0.0-Linux.deb
-rw-r--r-- 1 root root  13K Oct 11 15:49 math-vec-1.0.0-Linux.rpm
-rw-r--r-- 1 root root 4.5K Oct 11 15:49 math-vec-1.0.0-Linux.tar.gz
-rwxr-xr-x 1 root root  16K Oct 11 15:49 math_vec_tool

➜  build git:(master) ✗ tree install
install
├── bin
│   └── math_vec_tool
├── include
│   └── math_vec
│       └── math_vec.h
├── lib
│   ├── cmake
│   │   └── math_vec
│   │       ├── math_vecConfig.cmake
│   │       ├── math_vecConfigVersion.cmake
│   │       ├── math_vecTargets.cmake
│   │       └── math_vecTargets-noconfig.cmake
│   └── libmath_vec.a
└── share
    └── doc
        └── math_vec
            └── README.md

9 directories, 8 files

```