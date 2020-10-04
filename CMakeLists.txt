# TOP LEVEL CMAKE PROJECT FILE FOR AN STM32F411 BUILD PROJECT
# AUTHOR : CARL MATTATALL (cmattatall2@gmail.com)

cmake_minimum_required(VERSION 3.17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    message("CMAKE_BUILD_TYPE WAS NOT SPECIFIED. USING DEFAULT MODE : >${CMAKE_BUILD_TYPE}<")
endif(NOT CMAKE_BUILD_TYPE)

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
    # do nothing
else()
    message(FATAL_ERROR "Invalid option >${HAL_DRIVER_CONFIG}< provided for HAL_DRIVER_CONFIG. Valid options are \"DISABLED\" and \"ENABLED\"")
endif(NOT DEFINED HAL_DRIVER_CONFIG)

project(low_power_sensor_card 
        VERSION 1 
        DESCRIPTION "Firmware for the Rimot low power sensor card" 
        LANGUAGES C ASM)
        ########################################################
        #           ASM MUST BE EXPLICITLY ENABLED
        #
        ########################################################
        # ALSO, since UNIX systems are case sensitive, 
        # .S is the extension for asm in CMAKE. NOT .s
        #       !!!!NOTE THE CAPITALIZATION!!!!!
        ######################################################### 
        #
        # so if the startup file is called startup_stm32f411xe.s, 
        # gcc will silently ignore it and the bootstrap sequence 
        # for the mcu will fail.
        ######################################################### 

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/carl_utils.cmake)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(opt_level -O0)
else()
  set(opt_level -Os)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Linker/STM32F411VETx_FLASH.ld)

set(firmware_name ${CMAKE_PROJECT_NAME})


file(GLOB_RECURSE hacky_global_header_files "${CMAKE_SOURCE_DIR}/*.h")
foreach(hdr ${hacky_global_header_files})
    get_filename_component(hdr_dir ${hdr} DIRECTORY)
    list(APPEND hacky_global_include_dirs ${hdr_dir})
endforeach(hdr ${hacky_global_header_files})
list(REMOVE_DUPLICATES hacky_global_include_dirs)

include_directories(${hacky_global_include_dirs})

add_subdirectory(Firmware)
add_subdirectory(Drivers)
add_subdirectory(Middlewares/ST/STM32_USB_Device_Library)
add_subdirectory(USB_Device)
