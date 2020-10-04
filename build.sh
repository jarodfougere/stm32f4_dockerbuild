#!/bin/bash

rm -r objects
mkdir objects
pushd objects
cmake -S ../ -DCMAKE_TOOLCHAIN_FILE="cmake/arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="8000000" -DHAL_DRIVER_CONFIG="DISABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi"
popd
cmake --build objects
## IF YOU DON'T WANT TO REBUILD EVERY TIME, YOU WILL HAVE TO MODIFY THE SCRIPT 