#### 通用依赖
- 使用conan 获取
- 一些conan-center中没有的库打包到jfrog上了
- 第一次运行conan时请使用运行一次：
- ```
    # run one times at one machine
    conan remote add khalid https://api.bintray.com/conan/puzzzzzzle1/khalidzhang 
    conan install libgo/v3.1-stable@tao/test -r khalid
    conan install libco/v1.0@libco/tao -r khalid
    ```
- 删除cmake文件后请运行一次
-  ```
    mkdir build 
    cd build
    # other libs
    conan install .. --build missing -r=conan-center
    cmake .. 
    make -j8
    ```
- conan安装： pip3 install conan
    - 最好是python3,python2版本的有bug