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
    ######################################################################
    # I was playing around with build support for cmsis dap 
    # (compilnig openocd with #./configure --enable-cmsis-dap && make)
    # but I couldn't get the hidapi dependencies to build reliably.
    # perhaps we can revisit this in the future
    ######################################################################
    # git clone git://github.com/Dashlane/hidapi.git
    # pushd hidapi > /dev/null
    # ./bootstrap
    # ./configure --enable-static --disable-shared
    # make clean && make
    # export HIDAPI_LIBS="-L$HIDAPI_DIR/mac/.libs/ -lhidapi"
    # export PKG_CONFIG_PATH="$HIDAPI_DIR/mac/pc/"
    # popd > /dev/null
    ######################################################################
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

    make
    if [ $? -ne 0 ]; then
        echo "Error installing openocd"
        exit 1
    fi
    ln -s /usr/local/openocd/src/openocd /usr/local/bin/openocd
    echo "export PATH=$PATH:/usr/local/openocd/tcl/" >> ~/.bashrc
    popd > /dev/null # leave /usr/local/openocd
fi
popd > /dev/null # leave /usr/local