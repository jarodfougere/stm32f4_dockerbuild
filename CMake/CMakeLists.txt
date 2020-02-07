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
#CMAKE KIT CAN HAVE A TOOLCHAIN FILE CONFIGURED
message("configuring using cmake kit : ${SELECTED_CMAKE_KIT}")
if(DEFINED CMAKE_TOOLCHAIN_FILE)
    include(${CMAKE_TOOLCHAIN_FILE})
    #include(${USER_MODULE_DIR}/Build/target_system.cmake)
endif()
project(firmware VERSION 1.0.0)
enable_language(C ASM)


set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

MACRO(PROJECT_INC_DIRS return_list start_dir extension)
    FILE(GLOB_RECURSE new_list ${start_dir}/*.${extension})
    SET(dir_list "")
    FOREACH(file_path ${new_list})
        GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
        SET(dir_list ${dir_list} ${dir_path})
    ENDFOREACH()
    LIST(REMOVE_DUPLICATES dir_list)
    SET(${return_list} ${dir_list})
ENDMACRO() 

## CHECK DIRECTORY EXISTENCE AND CREATE IF NOT ##
message("-------------------------------------------------------")
message("validating project directories")
            #vscode workspace passes in these 2 params
foreach(proj_dir "${USER_SRC_DIR}" "${USER_BIN_DIR}") 
    if(NOT EXISTS ${proj_dir})
        file(MAKE_DIRECTORY ${proj_dir})
        message("directory : ${proj_dir} not found in project. Now creating")
    else()
        message("directory : ${proj_dir} exists in project")
    endif()
endforeach()

message("-------------------------------------------------------")
get_property(languages GLOBAL PROPERTY ENABLED_LANGUAGES)
message("detecting and setting up the project compilation structure...")
set(PROJECT_SOURCES "")
set(PROJECT_INC_DIRS "")
foreach(lang ${languages})
    message("detected enabled language : ${lang}")
    if(${lang} STREQUAL "C")
        set(header_extension "h")
        set(lang_extension "c")
    elseif(${lang} STREQUAL "CXX")
        set(header_extension "hpp")
        set(lang_extension "cpp")
    elseif(${lang} STREQUAL "ASM")
        #concept of headers doesnt exist in asm
        set(lang_extension asm)
    else()
        string(TOLOWER ${lang} lang_extension)
        set(header_extension ${lang_extension})
        message("no file extension was provided for language = ${lang}. using .${lang_extension} as a default guess.")
        message("no header or linking extension was provided for language = ${lang}. using .${header_extension} as a default guess.")
    endif()
        message("searching for .${lang_extension} files...")
        FILE(GLOB_RECURSE new_sources ${USER_SRC_DIR}/*.${lang_extension})
        FOREACH(src ${new_sources})
            message(STATUS "found : ${src}")
        ENDFOREACH()
        SET(PROJECT_SOURCES ${PROJECT_SOURCES} ${new_sources})

        message("searching for .${header_extension} include paths...")
        FILE(GLOB_RECURSE new_headers ${USER_SRC_DIR}/*.${header_extension})
        SET(new_directories "")
        FOREACH(header_file ${new_headers})
            GET_FILENAME_COMPONENT(new_dir ${header_file} PATH)
            SET(PROJECT_INC_DIRS ${PROJECT_INC_DIRS} ${new_dir})
        ENDFOREACH()
        LIST(REMOVE_DUPLICATES PROJECT_INC_DIRS)
        FOREACH(dir ${PROJECT_INC_DIRS})
            message("included : ${dir}")
        endforeach()
endforeach()
add_executable(${CMAKE_PROJECT_NAME} ${PROJECT_SOURCES})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_INC_DIRS})
set(ARCHIVE_OUTPUT_DIRECTORY  ${USER_BIN_DIR})
set(LIBRARY_OUTPUT_DIRECTORY  ${USER_BIN_DIR})
set(RUNTIME_OUTPUT_DIRECTORY  ${USER_BIN_DIR})
message("-------------------------------------------------------")

