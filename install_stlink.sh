#!/bin/bash
apt-get update
apt-get install libusb-1.0.0-dev
UTILS_DIR="utils"
if [ -d "$UTISL_DIRS" ]; then
	echo " I such at bash scripting so I don't know how to negate a conditional" > /dev/null
else
	mkdir "$UTILS_DIR"
fi
pushd $UTILS_DIR
git clone https://github.com/texane/stlink
pushd stlink
cmake . && make
if [[ $? == 0 ]]; then
	echo "Error building stlink tools! Exiting"
	exit -1
fi
cp ./bin/st-* /usr/local/bin
cp ./config/udev/rules.d/49-stlinkv* /etc/udev/rules.d
udevadm control --reload-rules && udevadm trigger
popd # leave stlink directory
popd # leave utils directory


