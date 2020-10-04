#!/bin/bash
version=3.18
build=1
mkdir temp # create and enter temporary folder
pushd temp > /dev/null
wget https://cmake.org/files/v$version/cmake-$version.$build.tar.gz
tar -xzvf cmake-$version.$build.tar.gz
pushd cmake-$version.$build/ > /dev/null #enter cmake folder and build the stuff
./bootstrap
make -j$(nproc)
make install
popd > /dev/null # leave cmake folder (now we're in tmp)
popd > /dev/null # leave tmp folder back into start dir  of parent shell
rm -r temp
echo "=============================================="
echo "FINISHED INSTALLING CMAKE"
echo "cmake version == $(cmake --version)"
echo "=============================================="
