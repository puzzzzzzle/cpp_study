#!/bin/sh

conan remote add khalid https://api.bintray.com/conan/puzzzzzzle1/khalidzhang
conan install libgo/v3.1-stable@tao/test -r khalid
conan install libco/v1.0@libco/tao -r khalid