cmake_minimum_required(VERSION 3.16.0)
cmake_policy(SET CMP0069 NEW)
set(PROJECT_NAME aetheraBoard)
set(PROJECT_BUILD_TARGET ${PROJECT_NAME}_TARGET)
project(${PROJECT_NAME} VERSION 1.0.0)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)
enable_language(C ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

file(GLOB all_SRCS
    "${CMAKE_SOURCE_DIR}/*.c"
    "${CMAKE_SOURCE_DIR}/*/*.c"
    "${CMAKE_SOURCE_DIR}/*/*/*.c"
    "${CMAKE_SOURCE_DIR}/*/*/*/*.c"
)

add_executable(${PROJECT_BUILD_TARGET} ${all_SRCS})

target_include_directories(${PROJECT_BUILD_TARGET} PUBLIC
    ${CMAKE_SOURCE_DIR}/Application/Core/Inc
    ${CMAKE_SOURCE_DIR}/Application/Port/Inc
    ${CMAKE_SOURCE_DIR}/Application/Port/
    ${CMAKE_SOURCE_DIR}/Drivers/
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Core/Include
    ${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/*/Include
    ${CMAKE_SOURCE_DIR}/Drivers/Peripherals/
    ${CMAKE_SOURCE_DIR}/Drivers/Peripherals/Inc/
    ${CMAKE_SOURCE_DIR}/Middleware/
    ${CMAKE_SOURCE_DIR}/Middleware/Inc
)

set_target_properties(${PROJECT_BUILD_TARGET} PROPERTIES 
C_STANDARD 99

# ADD MORE PROPERTIES AS NEEDED. FOR REFERENCE:
# https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties
)

set(C_STANDARD_REQUIRED TRUE)

include(${CMAKE_MODULE_PATH}/Build/build.cmake)
include(${CMAKE_MODULE_PATH}/Build/target.cmake)
include(${CMAKE_MODULE_PATH}/Testing/testing.cmake)


get_cmake_property(_variableNames VARIABLES)
file(REMOVE CMakeVars.config)
file(TOUCH CMakeVars.config)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    file(APPEND CMakeVars.config "${_variableName}=${${_variableName}}\n")
endforeach()


#file(REMOVE CMakeCompileDefs.out)
#file(TOUCH CMakeCompileDefs.out)
#list(SORT _compile_defs)
#foreach(define ${_compile_defs})
#    file(APPEND CMakeCompileDefs.out "${define}=${${_variableName}}\n")
#endforeach()


get_cmake_property(target_compile_definition ${PROJECT_BUILD_TARGET} COMPILE_DEFINITIONS)
get_target_property(interface_compile_definitions ${PROJECT_BUILD_TARGET}
INTERFACE_COMPILE_DEFINITIONS)

message("target_compile_definitions = ${target_compile_definitions}")
message("interface_compile_definitions = ${interface_compile_definitions}")
message("cmake build type == ${CMAKE_BUILD_TYPE}")
