################################################################################
##        TOP-LEVEL CMAKE PIPELINE FILE                                       ##
##                                                                            ##
##        I'VE ATTEMPTED TO MAKE IT SUFFICIENTLY ABSTRACT AS TO               ##
##        FACILITATE FUTURE USE.                                              ##
##                                                                            ##
##        AUTHOR:  CARL MATTATALL                                             ##
##        LICENSE: RIMOT.IO INCORPORATED                                      ##
################################################################################

#user sets the project name
set(PROJECT_NAME aetheraBoard)

# TOP-LEVEL HEADER GUARD
if(DEFINED PROJECT_NAME)
    cmake_minimum_required(VERSION 3.16.0)
    set(C_STANDARD_REQUIRED TRUE)

    cmake_policy(SET CMP0069 NEW)  # NOT SURE IF I STILL NEED THIS OR NOT...

    set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/Modules/)

    project(${PROJECT_NAME} VERSION 1.0.0)
    enable_language(C ASM)

    set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

    #CMAKE BUILD MODULES (INCLUDE ORDER IS IMPORTANT)
    include(${CMAKE_MODULE_PATH}/Build/project_directories.cmake)
    include(${CMAKE_MODULE_PATH}/Build/project_sources.cmake)
    include(${CMAKE_MODULE_PATH}/Build/project_build_type.cmake)
    include(${CMAKE_MODULE_PATH}/Build/target_system.cmake)

    include(${CMAKE_MODULE_PATH}/Testing/testing.cmake)


    # ADD MORE PROPERTIES AS NEEDED. FOR REFERENCE:
    # https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#target-properties
    set_target_properties(${PROJECT_BUILD_TARGET} PROPERTIES 
    C_STANDARD 99   #this enforces ISO 1999 C LANGUAGE STANDARD

    # ADD PROPERTIES AS NEEDED: FORMAT : >prop1< >prop1 value<\n
    #                                    >prop2< >prop2 value<\m
    )
    




else()
    # YA DUN GOOFED
    message(FATAL_ERROR "USER HAS NOT PROVIDED A DEFINITION FOR >PROJECT_NAME<")
endif() # IFNDEF PROJECT_NAME #