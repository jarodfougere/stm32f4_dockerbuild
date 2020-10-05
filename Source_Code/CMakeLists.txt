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
else()
    message("Using CMAKE_BUILD_TYPE of \"${CMAKE_BUILD_TYPE}\"")
endif(NOT DEFINED CMAKE_BUILD_TYPE)

set(ACCEPTED_BUILD_TYPES Release Debug RelWithDebInfo MinSizeRel)
list(FIND ACCEPTED_BUILD_TYPES ${CMAKE_BUILD_TYPE} IS_BUILD_TYPE_ACCEPTED)
if(${IS_BUILD_TYPE_ACCEPTED} EQUAL -1)
  message("CMAKE_BUILD_TYPE of \"${CMAKE_BUILD_TYPE}\" is invalid. Valid types are:")
    foreach(build_type ${ACCEPTED_BUILD_TYPES})
        message("-  ${build_type}")
    endforeach(build_type ${ACCEPTED_BUILD_TYPES})
    message("")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
    message("USING DEFAULT CMAKE_BUILD_TYPE : \"${CMAKE_BUILD_TYPE}\"")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_options("-g -ggdb -O0")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    add_compile_options("-O2")
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
    add_compile_options("-Os -g")
elseif(CMAKE_BUILD_TYPE MATCHES MinSizeRel)
    add_compile_options("-Os")
endif()
message("Building ${CMAKE_PROJECT_NAME} in \"${CMAKE_BUILD_TYPE}\" configuration")


# @todo LET CALLER PROVIDED LINKER SCRIPT VIA SOME TYPE OF CLI ARGUMENT
set(LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/Linker/STM32F411VETx_FLASH.ld)


# @todo FIX LATER. THIS IS JUST A HACKY GLOBAL INCLUDE SO I CAN GET EVERYTHING WORKING
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
