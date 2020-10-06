#!/bin/bash
#bash script to install and build the st-link utility on ubuntu 18.04
git clone https://github.com/texane/stlink
pushd stlink
git checkout master
cmake . 
make
popd
mv ./stlink /usr/local/
ln -s /usr/local/stlink/bin/st-flash /usr/local/bin/st-flash
ln -s /usr/local/stlink/bin/st-util /usr/local/bin/st-util
ln -s /usr/local/stlink/bin/st-info /usr/local/bin/st-info
cp ./config/udev/rules.d/49-stlinkv* /etc/udev/rules.d/
udevadm control --reload-rules && udevadm trigger
lsusb