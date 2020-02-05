################################################################################
## THIS MODULE CONFIGURES THE SOURCE MODULES AND INCLUDE DIRECTORIES FOR THE
## BUILD PIPELINE
##
## AUTHOR:  CARL MATTATAL
## LICENSE: RIMOT.IO INCORPORATED
################################################################################

if(DEFINED PROJECT_BUILD_TARGET)

    #recursively include all the headers because im a lazy POS
    MACRO(HEADER_DIRECTORIES return_list start_dir)
        FILE(GLOB_RECURSE new_list ${start_dir}/*.h)
        SET(dir_list "")
        FOREACH(file_path ${new_list})
            GET_FILENAME_COMPONENT(dir_path ${file_path} PATH)
            SET(dir_list ${dir_list} ${dir_path})
        ENDFOREACH()
        LIST(REMOVE_DUPLICATES dir_list)
        SET(${return_list} ${dir_list})
    ENDMACRO()              

    message(STATUS "--------------------------------------------------------------------------------------------------------")
    #this is a very lazy way to get every single C and H file in the project
    file(GLOB_RECURSE PROJECT_SOURCES "${PROJECT_SOURCE_DIR}/*.c")
    message(STATUS "Added the following source modules to the project:")
    FOREACH(src ${PROJECT_SOURCES})
        message(STATUS "${src}")
    ENDFOREACH()
    message(STATUS "--------------------------------------------------------------------------------------------------------")



    HEADER_DIRECTORIES(PROJ_HEADERS ${PROJECT_SOURCE_DIR})
    message(STATUS "Added the following include directories to the project:")
    FOREACH(dir ${PROJ_HEADERS})
        message(STATUS "${dir}")
    ENDFOREACH()
    message(STATUS "----------------------------------------------------")

    add_executable(${PROJECT_BUILD_TARGET} ${PROJECT_SOURCES})
    #target_include_directories(${PROJECT_BUILD_TARGET} PUBLIC ${PROJECT_HDRS})
    include_directories(${PROJECT_BUILD_TARGET} ${PROJ_HEADERS})

else()
    message(FATAL_ERROR 
    "SOMETHING WENT WRONG WITH THE CMAKE PIPELINE.\n
    >PROJECT_BUILD_TARGET< IS NOT DEFINED DESPITE 
    INCLUSION OF project_sources.cmake IN THE BUILD
    PROCESS")
endif()

