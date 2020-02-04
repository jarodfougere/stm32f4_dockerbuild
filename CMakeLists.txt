cmake_minimum_required(VERSION 3.16.0)
cmake_policy(SET CMP0069 NEW)
project(aetheraBoard VERSION 1.0.0)
enable_language(C ASM)



#configure build type
set(CMAKE_BUILD_TYPE DEBUG)
if(CMAKE_BUILD_TYPE STREQUAL RELEASE)
    set (EXECUTABLE_OUTPUT_PATH ${aetheraBoard_SOURCE_DIR}/Binaries/Release)
elseif(CMAKE_BUILD_TYPE STREQUAL DEBUG)
    set (EXECUTABLE_OUTPUT_PATH ${aetheraBoard_SOURCE_DIR}/Binaries/Debug)
else()
    set (EXECUTABLE_OUTPUT_PATH ${aetheraBoard_SOURCE_DIR}/Binaries/)
endif()

#set cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)



#if COMPILING FOR TARGET PROCESSOR
set(CMAKE_SYSTEM_NAME GENERIC)
set(CMAKE_C_COMPILER_ARCHITECTURE_ID ARM)

#IAR DOESNT EXIST ON LINUX ANYWAY
set(EMBEDDED_WORKBENCH_ROOT_DIR "C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.4/arm")

#SET(CPU_FLAGS "--cpu ARM9E") #update with correct value for target processo

# Set up the CMake variables for compiler and assembler
# (The reason for both C and CXX variables is that CMake
# treats C and C++ tools individually)
set(CMAKE_C_COMPILER "${EMBEDDED_WORKBENCH_ROOT_DIR}/bin/iccarm.exe" "${CPU_FLAGS} --dlib_config normal")
set(CMAKE_CXX_COMPILER "${EMBEDDED_WORKBENCH_ROOT_DIR}/bin/iccarm.exe" "${CPU_FLAGS} --dlib_config normal")
set(CMAKE_ASM_COMPILER "${EMBEDDED_WORKBENCH_ROOT_DIR}/bin/iasmarm.exe" "${CPU_FLAGS}")

# Set up the CMake variables for the linker
set(LINKER_SCRIPT "${EMBEDDED_WORKBENCH_ROOT_DIR}/config/linker/ST/str91xFx44.icf")
set(CMAKE_C_LINK_FLAGS "--semihosting --config ${LINKER_SCRIPT}")
set(CMAKE_CXX_LINK_FLAGS "--semihosting --config ${LINKER_SCRIPT}")
### END CMAKE_TOOLCHAIN_FILE


include(${CMAKE_MODULE_PATH}/Compiler/IAR-C.cmake)
#ELSE
#WE ARE COMPILING FOR THE LOCAL SYSTEM

#ENDIF



#simple inc/src/build project structure
include_directories(
        ${aetheraBoard_SOURCE_DIR}/Application/Core/Inc
        ${aetheraBoard_SOURCE_DIR}/Application/Port/Inc
        ${aetheraBoard_SOURCE_DIR}/Application/Port/
        ${aetheraBoard_SOURCE_DIR}/Drivers/
        ${aetheraBoard_SOURCE_DIR}/Drivers/CMSIS/Core/Include
        ${aetheraBoard_SOURCE_DIR}/Drivers/CMSIS/Device/ST/*/Include
        ${aetheraBoard_SOURCE_DIR}/Drivers/Peripherals/
        ${aetheraBoard_SOURCE_DIR}/Drivers/Peripherals/Inc/
        ${aetheraBoard_SOURCE_DIR}/Middleware/
        ${aetheraBoard_SOURCE_DIR}/Middleware/Inc
)

#grab all the headers and source files
file(GLOB all_SRCS
        "${aetheraBoard_SOURCE_DIR}/*.c"
        "${aetheraBoard_SOURCE_DIR}/*/*.c"
        "${aetheraBoard_SOURCE_DIR}/*/*/*.c"
        "${aetheraBoard_SOURCE_DIR}/*/*/*/*.c"
)

#create the executable
add_executable(aetheraBoard ${all_SRCS})


##TEST
include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)