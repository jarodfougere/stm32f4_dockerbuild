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
while getopts ":o:m:s:b:" opt; do
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


pushd $BUILD_DIR > /dev/null
cmake -S ../$SOURCE_CODE_DIR -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="$HSE_VALUE" -DHAL_DRIVER_CONFIG="ENABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOUTPUT_DIR_NAME=${OUTPUT_DIR}
popd > /dev/null
cmake --build $BUILD_DIR
build_success = $?
if [ $build_success -eq 0 ]; then
    # If the cmake script output
    if [ -f "${BUILD_DIR}/compile_commands.json" ]; then
        cp ${BUILD_DIR}/compile_commands.json ${BASE_DIR}/compile_commands.json
    fi
fi
