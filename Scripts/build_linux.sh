#!/bin/bash
# BASH SCRIPT TO INITIATE CMAKE BUILD OF THE PROJECT INSIDE THE DOCKER CONTAINER

OUTPUT_DIR="bin"
BUILD_TYPE="Debug"
SOURCE_CODE_DIR="Source_Code"
BUILD_DIR="objects"
HSE_VALUE=8000000 # units in HZ
BASE_DIR=$(pwd)
VERBOSE_MAKEFILE=0

# these are used for testing the build system
scriptName = $(basename $BASH_SOURCE)
myInvocation="$(printf %q "$BASH_SOURCE")$((($#)) && printf ' %q' "$@")"
#echo "\n$scriptName was invoked with : $myInvocation\n"

while getopts ":o:m:s:b:v" opt; do

    case ${opt} in
    o)  
        OUTPUT_DIR="${OPTARG}"
        ;;
    m) 
        BUILD_TYPE="${OPTARG}"
        ;;
    s)  
        SOURCE_CODE_DIR="${OPTARG}"
        ;;
    b)
        BUILD_DIR="${OPTARG}"
        ;;
    v)
        VERBOSE_MAKEFILE=1
        ;;
    \?) 
        echo "Unsupported CLI option ${opt} with value ${OPTARG}"
        ;;
    esac
done


if [ -d "$BUILD_DIR" ]; then
    echo "gotta put something here" > /dev/null
else
    mkdir "$BUILD_DIR"
fi

if [ -d "$OUTPUT_DIR" ]; then
    echo "I need to put something here so bash doesnt hate me" > /dev/null
else
    mkdir "$OUTPUT_DIR"
fi

cmake -B "$BUILD_DIR" -S "$SOURCE_CODE_DIR" -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="$HSE_VALUE" -DHAL_DRIVER_CONFIG="ENABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" -DOUTPUT_DIR_NAME="$OUTPUT_DIR" -DCMAKE_VERBOSE_MAKEFILE="$VERBOSE_MAKEFILE"
if [ "$?" -ne 0 ]; then
    echo "Error configuring cmake build pipeline, exiting..."
    exit 1
else
    cmake --build "$BUILD_DIR"
fi