#!/bin/bash
# BASH SCRIPT TO INITIATE CMAKE BUILD OF THE PROJECT

myInvocation="$(printf %q "$BASH_SOURCE")$((($#)) && printf ' %q' "$@")"
#echo "build script invoked command : \"$myInvocation\""

OUTPUT_DIR="bin"
BUILD_TYPE="Debug"
SOURCE_CODE_DIR="Source_Code"
BUILD_DIR="objects"
HSE_VALUE=8000000 # units in HZ
DOCKERBUILD=0
BASE_DIR=$(pwd)
DESIRED_PATH=$BASE_DIR
while getopts ":o:m:s:b:p:d" opt; do
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
    d)
        DOCKERBUILD=1
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

if [ -d "$DESIRED_PATH" ]; then
    echo "I need to put something here so bash doesnt hate me" > /dev/null
else
    mkdir -p $DESIRED_PATH
fi

if [ "$DOCKERBUILD" -ne 0 ]; then
    echo "Copying built files to desired path in docker container..."
    cp -r ./* $DESIRED_PATH
fi

# we are doing these shenanigans because cmake can't omit 
# compile command jsons that use relative paths

pushd $DESIRED_PATH > /dev/null
cmake -B $BUILD_DIR -S $SOURCE_CODE_DIR -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="$HSE_VALUE" -DHAL_DRIVER_CONFIG="ENABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOUTPUT_DIR_NAME=${OUTPUT_DIR}
cmake --build $BUILD_DIR
popd > /dev/null