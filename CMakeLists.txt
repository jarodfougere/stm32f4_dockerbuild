



cmake_minimum_required(VERSION 3.16.0)
cmake_policy(SET CMP0069 NEW)
project(aetheraBoard VERSION 1.0.0)
enable_language(C ASM)

#configure build target
set(CMAKE_BUILD_TARGET MY_SYSTEM)


####################################
####                            ####
####   CONFIGURE BUILD TYPE     ####
####                            ####
####################################

if(CMAKE_BUILD_TYPE STREQUAL RELEASE)

    set (EXECUTABLE_OUTPUT_PATH ${aetheraBoard_SOURCE_DIR}/Binaries/Release)

elseif(CMAKE_BUILD_TYPE STREQUAL DEBUG)

    set (EXECUTABLE_OUTPUT_PATH ${aetheraBoard_SOURCE_DIR}/Binaries/Debug)

else()

    set (EXECUTABLE_OUTPUT_PATH ${aetheraBoard_SOURCE_DIR}/Binaries/)

endif()

#set cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

##########################################
####                                  ####
####      CONFIGURE  BUILD TARGET     ####
####                                  ####
##########################################

if(${CMAKE_BUILD_TARGET} STREQUAL MY_SYSTEM)

    ######################################################
    ####                                              ####
    ####  THIS IS WHERE WE SETUP LOCAL COMPILATION    ####
    ####                                              ####
    ######################################################

    message("USER HAS CONFIGURED CMAKE_BUILD_TARGET == MY_SYSTEM")


elseif(${CMAKE_BUILD_TARGET} STREQUAL TARGET_PROCESSOR)

    ######################################################
    ####                                              ####
    #### THIS IS WHERE WE INCLUDE THE IAR CMAKE STUFF ####
    ####                                              ####
    ######################################################

    message("USER HAS CONFIGURED CMAKE_BUILD_TARGET == TARGET_PROCESSOR")
    include(${CMAKE_MODULE_PATH}/Compiler/IAR/IAR-FindBinUtils.cmake)
    include(${CMAKE_MODULE_PATH}/Compiler/IAR/IAR.cmake)

else()

###########################################################
####                                                   ####
#### USER HAS NOT CONFIGURED SUFFICIENT BUILD SETTINGS ####
####                                                   ####
###########################################################

    message(FATAL_ERROR "PLEASE SELECT EITHER >LOCAL< OR >PROCESSOR< AS CMAKE_BUILD_TARGET")
endif()



#################################################
#####                                      ######
#####       SETUP INCLUDE DIRECTORIES      ######
#####                                      ######
#################################################

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


#################################################
#####                                      ######
#####         SETUP SOURCE MODULES         ######
#####                                      ######
#################################################

#grab all the headers and source files
file(GLOB all_SRCS
    "${aetheraBoard_SOURCE_DIR}/*.c"
    "${aetheraBoard_SOURCE_DIR}/*/*.c"
    "${aetheraBoard_SOURCE_DIR}/*/*/*.c"
    "${aetheraBoard_SOURCE_DIR}/*/*/*/*.c"
)

#create the executable
add_executable(aetheraBoard ${all_SRCS})

####################################################
####                                            ####
####                    TESTING                 ####
####                                            ####
####################################################


include(CTest)
enable_testing()
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

####################################################
####                                            ####
#### THIS PRINTS TO THE CONSOLE EVERY SINGLE    ####
#### CACHED VARIABLE CONFIGURED IN THE PIPELINE ####
####                                            ####
####################################################
get_cmake_property(_variableNames VARIABLES)
file(REMOVE CMakeVars.config)
file(TOUCH CMakeVars.config)
list (SORT _variableNames)
foreach (_variableName ${_variableNames})
    file(APPEND CMakeVars.config "${_variableName}=${${_variableName}}\n")
endforeach()