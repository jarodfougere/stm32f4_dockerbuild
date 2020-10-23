# TOP LEVEL CMAKE PROJECT FILE FOR AN STM32F411 BUILD PROJECT
# AUTHOR : CARL MATTATALL (cmattatall2@gmail.com)
#
#
# @todo REFINE DETECTION, SCOPE, AND INCLUSION OF INCLUDE DIRECTORIES
#       right now, any subdirectory with a .h file in it is being
#       added to the include paths of the compilation of EVERY source file.
#       (This was partly done so I could get the whole build system up and
#        running quickly)

cmake_minimum_required(VERSION 3.17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED DEVICE_MPN)
    message(FATAL_ERROR "Please define DEVICE_MPN before continuing")
else()
    add_compile_definitions(${DEVICE_MPN})
endif(NOT DEFINED DEVICE_MPN)

if(NOT DEFINED HSE_VALUE)
    message(FATAL_ERROR "Please define HSE_VALUE before continuing")
else()
    add_compile_definitions("HSE_VALUE=${HSE_VALUE}")
endif(NOT DEFINED HSE_VALUE)

if(NOT DEFINED HAL_DRIVER_CONFIG)
    message(FATAL_ERROR "Please define HAL_DRIVER_CONFIG before continuing")
elseif(HAL_DRIVER_CONFIG STREQUAL "ENABLED")
    add_compile_definitions(USE_HAL_DRIVER)
elseif(HAL_DRIVER_CONFIG STREQUAL "DISABLED")
else()
    message(FATAL_ERROR "Invalid option >${HAL_DRIVER_CONFIG}< provided for HAL_DRIVER_CONFIG. Valid options are \"DISABLED\" and \"ENABLED\"")
endif(NOT DEFINED HAL_DRIVER_CONFIG)

message(STATUS "Using toolchain file: ${CMAKE_TOOLCHAIN_FILE}")

project(low_power_sensor_card 
        VERSION 1 
        DESCRIPTION "Generic firmware project for STM32F411-disco" 
        LANGUAGES C CXX ASM)
set(firmware_name ${CMAKE_PROJECT_NAME})

if(NOT DEFINED OUTPUT_DIR_NAME)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
    message("OUTPUT_DIR_NAME not defined. Using ${CMAKE_BINARY_DIR}/../bin by default")
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../${OUTPUT_DIR_NAME})
endif(NOT DEFINED OUTPUT_DIR_NAME)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    message("CMAKE_BUILD_TYPE WAS NOT SPECIFIED. USING DEFAULT MODE : >${CMAKE_BUILD_TYPE}<")
endif(NOT DEFINED CMAKE_BUILD_TYPE)

set(ACCEPTED_BUILD_TYPES Release Debug RelWithDebInfo MinSizeRel)
list(FIND ACCEPTED_BUILD_TYPES ${CMAKE_BUILD_TYPE} IS_BUILD_TYPE_ACCEPTED)
if(${IS_BUILD_TYPE_ACCEPTED} EQUAL -1)
  message("CMAKE_BUILD_TYPE of \"${CMAKE_BUILD_TYPE}\" is invalid. Valid types are:")
    foreach(build_type ${ACCEPTED_BUILD_TYPES})
        message("-\t${build_type}")
    endforeach(build_type ${ACCEPTED_BUILD_TYPES})
    message("")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    message("USING DEFAULT CMAKE_BUILD_TYPE : \"${CMAKE_BUILD_TYPE}\"")
else()
    if(CMAKE_BUILD_TYPE MATCHES Debug)
        add_compile_options("-g3")
        add_compile_options("-ggdb")
        add_compile_options("-Og")
    elseif(CMAKE_BUILD_TYPE MATCHES Release)
        add_compile_options("-O3")
    elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
        add_compile_options("-O2")
        add_compile_options("-g")
    elseif(CMAKE_BUILD_TYPE MATCHES MinSizeRel)
        add_compile_options("-Os")
    endif()
    message("Building ${CMAKE_PROJECT_NAME} in \"${CMAKE_BUILD_TYPE}\" configuration")
endif()

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

# @todo LET CALLER PROVIDED LINKER SCRIPT VIA SOME TYPE OF CLI ARGUMENT
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Linker/STM32F411VETx_FLASH.ld)
add_subdirectory(Firmware)
add_subdirectory(Drivers)
add_subdirectory(Middlewares)
add_subdirectory(USB_Device)
