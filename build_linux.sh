#!/bin/bash
# BASH SCRIPT TO INITIATE CMAKE BUILD OF THE PROJECT

myInvocation="$(printf %q "$BASH_SOURCE")$((($#)) && printf ' %q' "$@")"
echo "build script invoked command : \"$myInvocation\""

OUTPUT_DIR="bin"
BUILD_TYPE="Debug"
SOURCE_CODE_DIR="Source_Code"
BUILD_DIR="objects"
HSE_VALUE=8000000 # units in HZ

BASE_DIR=$(pwd)
DESIRED_PATH=$BASE_DIR
echo "BASE_DIR = $BASE_DIR"
while getopts ":o:m:s:b:p:" opt; do
    case ${opt} in
    o)  
        OUTPUT_DIR=$OPTARG
        ;;
    m) 
        BUILD_TYPE=$OPTARG
        ;;
    s)  
        SOURCE_CODE_DIR=$OPTARG
        ;;
    b)
        BUILD_DIR=$OPTARG
        ;;
    p)
        DESIRED_PATH=$OPTARG
        ;;
    \?) 
        echo "Unsupported CLI option ${opt} with value ${OPTARG}"
        ;;
    esac
done

if [ -d "$BUILD_DIR" ]; then
    echo "gotta put something here" > /dev/null
else
    mkdir $BUILD_DIR
fi

if [ -d "$OUTPUT_DIR" ]; then
    echo "I need to put something here so bash doesnt hate me" > /dev/null
else
    mkdir $OUTPUT_DIR
fi

echo ""
echo "DESIRED_PATH = $DESIRED_PATH"
echo ""

if [ -d "$DESIRED_PATH" ]; then
    echo "I need to put something here so bash doesnt hate me" > /dev/null
else
    mkdir -p $DESIRED_PATH
fi
cp -r ./* $DESIRED_PATH
# we are doing these shenanigans because cmake can't omit 
# compile command jsons that use relative paths
pushd $DESIRED_PATH

cmake -B $BUILD_DIR -S $SOURCE_CODE_DIR -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="$HSE_VALUE" -DHAL_DRIVER_CONFIG="ENABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOUTPUT_DIR_NAME=${OUTPUT_DIR}
cmake --build $BUILD_DIR
if [ $? -eq 0 ]; then
    if [ "$EUID" -eq 0 ]; then
        # running as root. likely from a docker container
        echo "blah" > /dev/null
    fi
fi

popd