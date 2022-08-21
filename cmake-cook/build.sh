#!/bin/bash
if [ -d "build" ];then
    rm -rf build
fi;
mkdir build
cd build
cmake ..
make -j8
echo "*****运行结果*****"
./hello-01