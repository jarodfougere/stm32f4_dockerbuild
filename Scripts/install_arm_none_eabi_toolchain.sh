#!/bin/bash
# bash script to install armgcc freestanding toolchain on ubuntu 18.04

declare -a required_packages=("wget" "gcc" "make" "nano" "git" "libusb-1.0.0-dev" "udev" "build-essential" "findutils")
UPDATED=0
for pkg in ${required_packages[@]}; do
    echo "checking if $pkg is installed..."
    which $pkg
    if [ $? -ne 0 ]; then
        if [ $UPDATED -eq 0 ]; then
            apt-get update
            UPDATED=1
        fi
        echo "  ok"
        echo ""
        apt-get install -y $pkg
    fi
done
wget -qO- https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2 | tar -xj
mv ./gcc-arm-none-eabi-9-2019-q4-major /opt/
for executable in /opt/gcc-arm-none-eabi-9-2019-q4-major/bin/*; do
    ln -s $executable /usr/local/bin/`basename $executable`
done
