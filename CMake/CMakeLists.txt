################################################################################
##        TOP-LEVEL CMAKE PIPELINE FILE                                       ##
##                                                                            ##
##        I'VE ATTEMPTED TO MAKE IT SUFFICIENTLY ABSTRACT AS TO               ##
##        FACILITATE FUTURE USE.                                              ##
##                                                                            ##
##        AUTHOR:  CARL MATTATALL                                             ##
##        LICENSE: RIMOT.IO INCORPORATED                                      ##
################################################################################

cmake_minimum_required(VERSION 3.16.0)
# THIS COMMAND TRIGGERS TOOLCHAIN READ
project(
    firmware
    VERSION 1.0.0
    LANGUAGES C ASM)
set(PROJECT_TARGET ${CMAKE_PROJECT_NAME})

#create the build target 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${USER_BIN_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${USER_BIN_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${USER_BIN_DIR})
add_executable(${PROJECT_TARGET})
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(DEFINED PROCESSOR_MPN)
    string(TOLOWER "${PROCESSOR_MPN}.cmake" PROCESSOR_CMAKE_MODULE)
    include(${USER_MODULE_DIR}/Target/${PROCESSOR_CMAKE_MODULE})
    set(CMAKE_C_FLAGS   "${OBJECT_GEN_FLAGS} ${CMAKE_C_FLAGS} ${ARCH_FLAGS}")
    set(CMAKE_CXX_FLAGS "${OBJECT_GEN_FLAGS} ${CMAKE_CXX_FLAGS} ${ARCH_FLAGS}")
    set(CMAKE_ASM_FLAGS "${OBJECT_GEN_FLAGS} ${CMAKE_ASM_FLAGS}")
    
endif()


## CHECK DIRECTORY EXISTENCE AND CREATE IF NOT ##
message("-------------------------------------------------------")
message("validating project directories")
foreach(proj_dir "${USER_SRC_DIR}" "${USER_BIN_DIR}")  
    if(NOT EXISTS ${proj_dir})
        file(MAKE_DIRECTORY ${proj_dir})
        message("directory : ${proj_dir} not found in project. Now creating")
    else()
        message("directory : ${proj_dir} exists in project")
    endif()
endforeach()


if(${CMAKE_CROSSCOMPILING} EQUAL 1)
    message("We are cross compiling for processor: ${PROCESSOR_MPN}")
    target_compile_definitions(${PROJECT_TARGET} PUBLIC MCU_APP)
    target_compile_definitions(${PROJECT_TARGET} PUBLIC ${PROCESSOR_MPN})
    target_compile_definitions(${PROJECT_TARGET} PUBLIC USE_HAL_DRIVER)
endif()

target_compile_options(${PROJECT_TARGET} PUBLIC -Wall)

#CORE APPLICATION
message("Detecting .c files...")
file(GLOB_RECURSE SOURCE_MODULES "${USER_SRC_DIR}/Application/*.c")
foreach(file ${SOURCE_MODULES})
    message("found source file  : ${file}")
    target_sources(${PROJECT_TARGET} PUBLIC ${file})
endforeach()

#PLATFORM DEPENDENT SOURCE MODULES
if(${CMAKE_CROSSCOMPILING} EQUAL 1)
    file(GLOB_RECURSE SOURCE_MODULES "${USER_SRC_DIR}/Device/*.c")
    foreach(file ${SOURCE_MODULES})
        message("found source file  : ${file}")
        target_sources(${PROJECT_TARGET} PUBLIC ${file})
    endforeach()
endif()
message("-------------------------------------------------------")
message("Detecting .h include directories...")
file(GLOB_RECURSE HEADER_FILES ${USER_SRC_DIR}/*.h)
foreach(file ${HEADER_FILES})
    set(file_dir "")
    get_filename_component(file_dir ${file} PATH)
    list(APPEND INC_DIRS ${file_dir})
    list(REMOVE_DUPLICATES INC_DIRS)
endforeach()
foreach(dir ${INC_DIRS})
    message("included directory : ${dir}")
endforeach()
target_include_directories(${PROJECT_TARGET} PUBLIC ${INC_DIRS})
message("-------------------------------------------------------")

set(CMAKE_EXECUTABLE_SUFFIX ${TOOLCHAIN_TARGET_SUFFIX})

