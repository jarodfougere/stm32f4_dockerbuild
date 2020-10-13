#!/bin/bash
#
# BASH SCRIPT TO INITIATE CMAKE BUILD OF THE PROJECT

myInvocation="$(printf %q "$BASH_SOURCE")$((($#)) && printf ' %q' "$@")"
echo "calling command = $myInvocation"

OUTPUT_DIR="bin"
BUILD_TYPE="Debug"

HSE_VALUE=8000000 # units in HZ

# Supported command line arguments
# o : output directory name (default is bin)
#
# m : build configuration (default is debug)
#
# m : clean rebuild (CMake cache gets deleted)
while getopts ":o:m:" opt; do
    case ${opt} in
    o)  
        OUTPUT_DIR=$OPTARG
        ;;
    m) 
        BUILD_TYPE=$OPTARG
        ;;
    \?) 
        echo "Unsupported CLI option ${opt} with value ${OPTARG}"
        ;;
    esac
done

if [ -d "objects" ]; then
    echo "gotta put something here" > /dev/null
else
    mkdir objects
fi

if [ -d "$OUTPUT_DIR" ]; then
    echo "I need to put something here so bash doesnt hate me" > /dev/null
else
    mkdir $OUTPUT_DIR
fi

current_dir="Source_Code"
pushd objects > /dev/null
cmake -S ../$current_dir -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="$HSE_VALUE" -DHAL_DRIVER_CONFIG="ENABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOUTPUT_DIR_NAME=${OUTPUT_DIR}
popd > /dev/null
cmake --build objects

