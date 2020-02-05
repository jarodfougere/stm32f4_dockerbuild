################################################################################
## THIS MODULE CONFIGURES THE BUILD PIPELINE FOR THE TARGET SYSTEM
## 
## IN CASES WHERE THE TARGET SYSTEM IS AN EXTERNAL PROCESSOR OR AN 
## ARCHITECTURE THAT DOES NOT MATCH THAT OF THE SYSTEM PERFORMING THE 
## COMPILATION, THIS MODULE SHALL SET THE APPROPRIATE CONFIGURATION
##
## AUTHOR:  CARL MATTATAL
## LICENSE: RIMOT.IO INCORPORATED
################################################################################
if(NOT DEFINED TARGET_SYSTEM_MODULE_INCLUDED)
set(TARGET_SYSTEM_MODULE_INCLUDED true)
if(DEFINED PROJECT_BUILD_TARGET)
if(DEFINED CMAKE_SYSTEM_NAME)
if(${CMAKE_SYSTEM_NAME} STREQUAL "GENERIC")
message("target system: ${CMAKE_SYSTEM_NAME}")
add_compile_definitions(MCU_TARGET)

## Device select
if(DEFINED STM32_FAMILY)
message("processor family:    ${STM32_FAMILY}")
add_compile_definitions(${STM32_FAMILY})
if(DEFINED STM32_FAMILY_MPN)
message("processor mpn:     ${STM32_FAMILY_MPN}")
add_compile_definitions(${STM32_FAMILY_MPN})
else()
message(FATAL_ERROR "STM32_FAMILY_MPN DEFINITION NOT PROVIDED")
endif()
else()
message(FATAL_ERROR "STM32_FAMILY DEFINITION NOT PROVIDED")
endif()

## TOOLCHAIN SELECT ##
if(DEFINED BUILD_TOOLCHAIN)
message("selected toolchain: ${BUILD_TOOLCHAIN}")
if(${BUILD_TOOLCHAIN} STREQUAL "IAR")

#IAR OPTIONS 
add_compile_options(--dlib_config_normal)
set(LINKER_SCRIPT ${PROJECT_SRC_DIR}/Device/Linker/IAR/linker.icf)
set(CMAKE_C_LINK_FLAGS  "--semihosting --config ${LINKER_SCRIPT}")
set(CMAKE_CXX_LINK_FLAGS "--semihosting --config ${LINKER_SCRIPT}")
FILE(GLOB ASM_SOURCES "${PROJECT_SRC_DIR}/Device/Startup/IAR/*.s" )
target_sources(${PROJECT_BUILD_TARGET} PUBLIC ${ASM_SOURCES})

elseif(${BUILD_TOOLCHAIN} STREQUAL "ARM-GCC")
message("ARM-GCC BUILD TOOLCHAIN HAS BEEN SELECTED BUT CARL HASN'T ADDED THE CONFIGURATION TO target_system.cmake YET!!")
else()
message("UNSUPPORTED OPTION FOR BUILD_TOOLCHAIN")
endif()
endif()
else()
message("THE TARGET SYSTEM IS NOT SUPPORTED BY target_system.cmake MODULE")
endif()            
else()
message("CMAKE_SYSTEM_NAME IS NOT DEFINED")
endif()
else()
message(FATAL_ERROR "PROJECT HAS NOT DEFINED >PROJECT_BUILD_TARGET<")
endif()
endif()


