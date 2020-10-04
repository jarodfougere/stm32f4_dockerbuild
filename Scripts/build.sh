#!/bin/bash
#
# BASH SCRIPT TO INITIATE CMAKE BUILD OF THE PROJECT
#
if [ -d "objects" ]
then
    rm -r objects
fi
mkdir objects
if [ -d "Out" ]
then
    echo "I need to put something here so bash doesnt hate me" > /dev/null
else
    mkdir Out
fi
pushd objects > /dev/null
cmake -S ../Source_Code -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="8000000" -DHAL_DRIVER_CONFIG="DISABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi"
popd > /dev/null
cmake --build objects
rm -r objects