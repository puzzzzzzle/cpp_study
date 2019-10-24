#### 通用依赖
- 使用conan 获取
```
mkdir build & cd build

# libgo packaged by khalidzhang
conan remote add khalid https://api.bintray.com/conan/puzzzzzzle1/khalidzhang 
conan install libgo/v3.1-stable@tao/test -r khalid

# other libs
conan install .. --build missing -r=conan-center
cmake .. 
make -j8
```

