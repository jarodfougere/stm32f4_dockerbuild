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

if(DEFINED PROJECT_ROOT_DIR)
    TARGET_COMPILE_DEFINITIONS(${PROJECT_BUILD_TARGET} 
        PUBLIC 
        # ADD DEFINITIONS AS NEEDED
    )

    if(CMAKE_BUILD_TYPE STREQUAL RELEASE)
        set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Binaries/Release)
    elseif(CMAKE_BUILD_TYPE STREQUAL DEBUG)
        set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Binaries/Debug)
    elseif(CMAKE_BUILD_TYPE STREQUAL DEV)

        #if 
        set (EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/Binaries/)
    endif()
    else()
    message(FATAL_ERROR 
    "THE PROJECT DOES NOT HAVE A CMAKE PIPELINE DEFINITION FOR 
    >PROJECT_ROOT_DIR<")
endif()