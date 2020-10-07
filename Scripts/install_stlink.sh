#!/bin/bash
#bash script to install and build the st-link utility on ubuntu 18.04

function cleanup()
{   
    popd > /dev/null
    while (( $? == 0 )); do popd > /dev/null; done
    rm -rf tmp
}
trap cleanup EXIT

declare -a required_packages=("wget" "gcc" "make" "nano" "git" "libusb-1.0.0-dev" "udev" "build-essential")
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

which st-flash
if [ $? -eq 0 ]; then
    echo ""
    echo "================================"
    echo "st-flash is already installed"
    echo "running st-flash --version: "
    st-flash --version
    echo "================================"
    exit 0
fi

git clone https://github.com/texane/stlink
mv ./stlink /usr/local/
pushd /usr/local/stlink
git checkout master
which cmake
if [ $? -ne 0 ]; then
    ./install_cmake.sh
fi
cmake . 
if [ $? -ne 0 ]; then
    echo "Error configuring the stlink build pipeline!"
    exit 1
fi
make
if [ $? -ne 0 ]; then
    echo "Error building stlink from source"
    exit 1
fi
popd 
ln -s /usr/local/stlink/bin/st-flash /usr/local/bin/st-flash
ln -s /usr/local/stlink/bin/st-util /usr/local/bin/st-util
ln -s /usr/local/stlink/bin/st-info /usr/local/bin/st-info
cp ./config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
udevadm control --reload-rules && udevadm trigger
lsusb