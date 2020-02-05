################################################################################
## THIS MODULE SETS THE OUTPUT DIRECTORY FOR THE COMPLETED BINARY
## 
## IF THE USER/PROJECT HAS NOT SPECIFIED A BUILD TYPE, 
## THE BINARY WILL BE PLACED INTO THE BUILD DIRECTORY 
## BUT NOT INTO A SPECIFIED >BUILD-TYPE< FOLDER
##
## AUTHOR:  CARL MATTATAL
## LICENSE: RIMOT.IO INCORPORATED
################################################################################
if(NOT DEFINED PROJECT_BUILD_TYPE_MODULE_INCLUDED)
set(PROJECT_BUILD_TYPE_MODULE_INCLUDED true)

    if(DEFINED PROJECT_ROOT_DIR)
        add_compile_definitions(${${CMAKE_BUILD_TYPE}})
        message("added ${CMAKE_BUILD_TYPE} to project compilation definitions")
        if(CMAKE_BUILD_TYPE STREQUAL "RELEASE")
            set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Release)
        elseif(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
            set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/Debug)
        else()
            message("USER HSA NOT PICKED A CMAKE VARIANT. CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")

            set (EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
        endif()
        else()
        message(FATAL_ERROR 
        "THE PROJECT DOES NOT HAVE A CMAKE PIPELINE DEFINITION FOR 
        >PROJECT_ROOT_DIR<")
    endif()
endif()