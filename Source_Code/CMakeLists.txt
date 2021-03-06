# TOP LEVEL CMAKE PROJECT FILE FOR AN STM32F411 BUILD PROJECT
# AUTHOR : CARL MATTATALL (cmattatall2@gmail.com)
#
# @todo LET CALLER PROVIDED LINKER SCRIPT VIA SOME TYPE OF CLI ARGUMENT

cmake_minimum_required(VERSION 3.17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED DEVICE_MPN)
    message(FATAL_ERROR "Please define DEVICE_MPN before continuing")
else()
    add_compile_definitions("${DEVICE_MPN}")
endif(NOT DEFINED DEVICE_MPN)

if(NOT DEFINED HSE_VALUE)
    message(FATAL_ERROR "Please define HSE_VALUE before continuing")
else()
    add_compile_definitions("HSE_VALUE=${HSE_VALUE}")
endif(NOT DEFINED HSE_VALUE)

if(NOT DEFINED HAL_DRIVER_CONFIG)
    message(FATAL_ERROR "Please define HAL_DRIVER_CONFIG before continuing")
elseif(HAL_DRIVER_CONFIG STREQUAL "ENABLED")
    add_compile_definitions("USE_HAL_DRIVER")
elseif(HAL_DRIVER_CONFIG STREQUAL "DISABLED")
else()
    message(FATAL_ERROR "Invalid option >${HAL_DRIVER_CONFIG}< provided for HAL_DRIVER_CONFIG. Valid options are \"DISABLED\" and \"ENABLED\"")
endif(NOT DEFINED HAL_DRIVER_CONFIG)

project(low_power_sensor_card 
        VERSION 1 
        DESCRIPTION "Generic firmware project for STM32F411-discovery" 
        LANGUAGES C CXX ASM)
set(firmware_name ${CMAKE_PROJECT_NAME})

if(NOT DEFINED OUTPUT_DIR_NAME)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../bin/${CMAKE_BUILD_TYPE})
    message("OUTPUT_DIR_NAME not defined. Using ${CMAKE_BINARY_DIR}/../bin by default")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/../${OUTPUT_DIR_NAME}/${CMAKE_BUILD_TYPE})
    message("Using ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} as the output dir")
endif(NOT DEFINED OUTPUT_DIR_NAME)

if(DEFINED CMAKE_BUILD_TYPE)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_compile_options("-g3")
        add_compile_options("-ggdb")
        add_compile_options("-Og")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options("-O3")
    elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        add_compile_options("-O2")
        add_compile_options("-g")
    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        add_compile_options("-Os")
    else()
        message("CMAKE_BUILD_TYPE of \"${CMAKE_BUILD_TYPE}\" is invalid. Valid Types are : Debug, Release, RelWithDebInfo, MinSizeRel. Using Debug as a default")
        set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    endif()
else()
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    message("CMAKE_BUILD_TYPE WAS NOT SPECIFIED. USING DEFAULT MODE : >${CMAKE_BUILD_TYPE}<")
endif()
message("Building project with \"${CMAKE_BUILD_TYPE}\" configuration")

add_library(HAL_DRIVER_LIB STATIC)
add_library(USB_DEVICE_LIB STATIC)
add_library(RTOS_LIB STATIC)
add_library(USB_CLASS_LIB STATIC)

file(GLOB_RECURSE fw_headers "Firmware/Inc/*.h")
foreach(hdr ${fw_headers})
    get_filename_component(hdr_dir ${hdr} DIRECTORY)
    list(APPEND fw_include_dirs ${hdr_dir})
endforeach(hdr ${fw_headers})
list(REMOVE_DUPLICATES fw_include_dirs)

# This isn't very flexible but I didn't have much time to throw together
# the build system
include_directories("Drivers/CMSIS/Device/ST/STM32F4xx/Include"
                    "Drivers/CMSIS/Include"
                    "Drivers/STM32F4xx_HAL_Driver/Inc"
                    "Drivers/STM32F4xx_HAL_Driver/Inc/Legacy"
                    "Middlewares/ST/STM32_USB_Device_Library/Core/Inc"
                    "Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc"
                    "Middlewares/Third_Party/FreeRTOS/Source/include"
                    "Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F"
                    "Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2"
                    "USB_Device/App/Inc"
                    "USB_Device/Target/Inc"
                    "${fw_include_dirs}")

set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Linker/STM32F411VETx_FLASH.ld)
add_subdirectory(Firmware)
add_subdirectory(Drivers)
add_subdirectory(Middlewares)
add_subdirectory(USB_Device)

# This could be made much better but its fine for now
if(CMAKE_BUILD_TYPE STREQUAL Debug)
    target_sources(RTOS_LIB PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Compat/openocd_compat.c")
elseif(CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
    target_sources(RTOS_LIB PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Compat/openocd_compat.c")
endif()
