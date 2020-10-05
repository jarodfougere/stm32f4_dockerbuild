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

OUTPUT_DIR="bin"
BUILD_TYPE="Debug"

# Supported command line arguments
# o : output directory name (default is bin)
#
# m : build configuration (default is debug)
while getopts ":o:om" opt; do
    case ${opt} in
    o)  
        echo "option o was provided"
        OUTPUT_DIR=${OPTARG}
        echo "using OUTPUT_DIR=$OUTPUT_DIR"
        ;;
    m) 
        echo "option m was provided"
        BUILD_TYPE=${OPTARG}
        echo "using BUILD_TYPE=$BUILD_TYPE"
        ;;
    \?) 
        echo "Unsupported CLI option in build.sh. Usage : \"\$[bash] build.sh [-o output_dir_name] [-m build_configuration]\""
        ;;
    esac
done
pushd objects > /dev/null
cmake -S ../Source_Code -DCMAKE_TOOLCHAIN_FILE="arm-none-eabi-toolchain.cmake" -DDEVICE_MPN="STM32F411xE"  -DHSE_VALUE="8000000" -DHAL_DRIVER_CONFIG="DISABLED" -DCMAKE_SYSROOT="arm-none-eabi-9-2019-q4-major/arm-none-eabi" -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DOUTPUT_DIR_NAME=${OUTPUT_DIR}
popd > /dev/null
cmake --build objects
rm -r objects