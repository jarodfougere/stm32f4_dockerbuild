#!/bin/bash
#
# BASH SCRIPT TO INITIATE CMAKE BUILD OF THE PROJECT

OUTPUT_DIR="bin"
BUILD_TYPE="Debug"
REBUILD=0

HSE_VALUE=8000000 # units in HZ

# Supported command line arguments
# o : output directory name (default is bin)
#
# m : build configuration (default is debug)
#
# m : clean rebuild (CMake cache gets deleted)
while getopts ":o:m:r" opt; do
    case ${opt} in
    o)  
        OUTPUT_DIR=$OPTARG
        ;;
    m) 
        BUILD_TYPE=$OPTARG
        ;;
    r)
        REBUILD=1
        ;;
    \?) 
        echo "Unsupported CLI option in build.sh. Usage : \"\$[bash] build.sh [-o output_dir_name] [-m build_configuration]\""
        ;;
    esac
done

if [[ "$REBUILD" == 1 ]]; then
    if [ -d "objects" ]; then
        rm -r objects
        echo "rebuilding"
    fi
fi
mkdir objects

if [ -d "$OUTPUT_DIR" ]; then
    echo "I need to put something here so bash doesnt hate me" > /dev/null
else
    mkdir $OUTPUT_DIR
fi

pushd objects > /dev/null
cmake -S ../Source_Code -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="$HSE_VALUE" -DHAL_DRIVER_CONFIG="DISABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOUTPUT_DIR_NAME=${OUTPUT_DIR}
popd > /dev/null
cmake --build objects

