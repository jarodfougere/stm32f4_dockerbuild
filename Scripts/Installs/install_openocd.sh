#!/bin/bash
# bash script to install openocd and utils on ubuntu 18.04

function cleanup()
{   
    popd > /dev/null
    while (( $? == 0 )); do popd > /dev/null; done
    rm -rf tmp
}
trap cleanup EXIT

declare -a required_packages=("wget" "gcc" "make" "nano" "git" "libusb-1.0.0-dev" "udev" "build-essential" "autotools-dev" "autoconf" "automake" "libtool" "libudev-dev" "texinfo" "libusb-1.0")
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

which openocd
if [ $? -eq 0 ]; then
    echo "openocd is already installed"
    exit 0
else
    pushd /usr/local > /dev/null
    git clone https://github.com/ntfreak/openocd
    pushd openocd > /dev/null
    ./bootstrap

    if [ "$?" -ne 0 ]; then
        echo "Error bootstrapping openocd"
        exit 1
    fi

    ./configure 
    if [ "$?" -ne 0 ]; then
        echo "Error configuring openocd!"
        exit 1
    fi
    make clean
    make -j$(nproc)
    make install -j$(nproc)
    if [ $? -ne 0 ]; then
        echo "Error installing openocd"
        exit 1
    fi
    popd > /dev/null # leave /usr/local/openocd
fi
popd > /dev/null # leave /usr/local