# STM32F4 DOCKER BUILD SYSTEM

## Table of Contents
- [Description](#description)
- [Dependencies](#dependencies)
- [Build](#build)
- [Todo](#todo)

## Description

    Example code has been provided for an STM32F411 Discovery board application 
    within an FreeRTOS V2 framework running as a USB 2.0 CDC class device.

## Dependencies

docker https://www.docker.com/products/docker-desktop
python3 https://realpython.com/installing-python/
openocd https://github.com/xpack-dev-tools/openocd-xpack/releases

## Build

    python3 ./build.py

## Debug

    Openocd + arm-none-eabi-gdb support has been integrated into vscode
    (OpenOCD and arm-none-eabi toolchain will still need to be installed)

    Install scripts (builds from source) have also been provided
    for texane's STlink utility as a fallback

## TODO

    -   SVD Descriptor files to view 
        Possible candidate at https://github.com/posborne/cmsis-svd.git 
    -   Improvements to CMake toolchain selection
    -   Support for windows filepaths that have spaces in the names
        (This has been a PITA since day 1)
    -   Automation of vscode tasks (just provide some gui support rather than CLI)
    -   Add support to prevent unecessary rebuild of object files inside container
        (This is a bit harder than one would think since the CMake build cache
        is handled internally by the cmake executable and not by the proj cache)
    -   Continuous Integration and pipeline
    -   Testing and TDD with CMake
    -   Automated testing as part of CI

