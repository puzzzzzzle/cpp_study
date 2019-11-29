#### 通用依赖
- 使用conan 获取
- 一些conan-center中没有的库打包到jfrog上了
```
# run one times at one machine
conan remote add khalid https://api.bintray.com/conan/puzzzzzzle1/khalidzhang 
conan install libgo/v3.1-stable@tao/test -r khalid
conan install libco/v1.0@libco/tao -r khalid
```

```
mkdir build 
cd build
# other libs
conan install .. --build missing -r=conan-center
cmake .. 
make -j8
cd -
```

