cmake_minimum_required(VERSION 3.0.0)
project(aetheraBoard VERSION 1.0.0)

#spit exe out in same dir as cmakelists
set (EXECUTABLE_OUTPUT_PATH ${aetheraBoard_SOURCE_DIR})

#simple inc/src/build project structure
include_directories(
        ${aetheraBoard_SOURCE_DIR}/Application/Core/Inc
        ${aetheraBoard_SOURCE_DIR}/Application/Port/Inc
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