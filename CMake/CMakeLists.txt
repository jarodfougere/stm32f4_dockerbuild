################################################################################
##        TOP-LEVEL CMAKE PIPELINE FILE                                       ##
##                                                                            ##
##        I'VE ATTEMPTED TO MAKE IT SUFFICIENTLY ABSTRACT AS TO               ##
##        FACILITATE FUTURE USE.                                              ##
##                                                                            ##
##        AUTHOR:  CARL MATTATALL                                             ##
##        LICENSE: RIMOT.IO INCORPORATED                                      ##
################################################################################
set(PROJECT_ROOT ${CMAKE_SOURCE_DIR}/..)
set(USER_SRC_DIR ${PROJECT_ROOT}/Sources)

cmake_minimum_required(VERSION 3.16.0)
project(firmware VERSION 1.0.0 LANGUAGES C ASM)
set(PROJECT_TARGET ${CMAKE_PROJECT_NAME})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY  ${PROJECT_ROOT}/Binaries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${PROJECT_ROOT}/Binaries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${PROJECT_ROOT}/Binaries)
add_executable(${PROJECT_TARGET})
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

if(DEFINED PROCESSOR_MPN)
    message("We are cross compiling for processor: ${PROCESSOR_MPN}")

    if(CMAKE_HOST_SYSTEM_NAME STREQUAL WINDOWS)
        set(TOOLCHAIN_EXT ".exe")
    endif()

    # Set toolchain paths
    set(TOOLCHAIN arm-none-eabi)
    if(NOT DEFINED TOOLCHAIN_PREFIX)
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)

            set(TOOLCHAIN_PREFIX "/usr")

        elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)

            set(TOOLCHAIN_PREFIX "/usr/local")

        elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)

            message(STATUS "Please specify the TOOLCHAIN_PREFIX !\n For
            example: -DTOOLCHAIN_PREFIX=\"C:/Program Files/GNU Tools ARM
            Embedded\" ")

        else()

            set(TOOLCHAIN_PREFIX "/usr")
            message(STATUS "No TOOLCHAIN_PREFIX specified, using default:  
            ${TOOLCHAIN_PREFIX}")

        endif()

    endif()

    set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)
    set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/include)
    set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PREFIX}/${TOOLCHAIN}/lib)
    set(TOOLCHAIN_TARGET_SUFFIX ".elf" )

    ############################################################################
    #                       Object build options                               #
    ############################################################################
    # -O0                   No optimizations, reduce compilation time and make #
    #                       debugging produce the expected results.            #
    #                                                                          #
    # -mthumb               Generate thumb instructions.                       #
    #                                                                          #
    # -fno-builtin          Do not use built-in functions provided by GCC.     #
    #                                                                          #
    # -Wall                 Print all standard warnings, for ALL use Wextra    #
    #                                                                          #
    # -ffunction-sections   Place each function item into its own section in   #
    #                       the output file.                                   #
    #                                                                          #
    # -fdata-sections       Place each data item into its own section in the   #
    #                       output file.                                       #
    #                                                                          #
    # -fomit-frame-pointer  Omit the frame pointer in functions that           #
    #                        don’t need one.                                   #
    #                                                                          #
    # -mabi=aapcs           Defines enums to be a variable sized type.         #
    ############################################################################

    set(OBJECT_GEN_FLAGS "${OBJECT_GEN_FLAGS} -O0 -mthumb -fno-builtin -Wall -ffunction-sections")
    set(OBJECT_GEN_FLAGS "${OBJECT_GEN_FLAGS} -fdata-sections")
    set(OBJECT_GEN_FLAGS "${OBJECT_GEN_FLAGS} -fomit-frame-pointer")
    set(OBJECT_GEN_FLAGS "${OBJECT_GEN_FLAGS} -mabi=aapcs")

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OBJECT_GEN_FLAGS}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ARCH_FLAGS}")

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OBJECT_GEN_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ARCH_FLAGS}")

    set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} ${OBJECT_GEN_FLAGS}")
    set(CMAKE_ASM_FLAGS "${CMAKE_ASM_FLAGS} -x assembler-with-cpp")

    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_PROCESSOR ARM)
    set(CMAKE_CROSSCOMPILING 1)
    set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

    ############################################################################
    # -Wl,--gc-sections     Perform the dead code elimination.                 #
    #                                                                          #
    # --specs=nosys.specs   No syscalls, provide empty implementations for the #
    #                       POSIX system calls.                                #
    ############################################################################

    set(LINK_FLAGS "${LINK_FLAGS} -Wl,--gc-sections")
    set(LINK_FLAGS "${LINK_FLAGS} --specs=nosys.specs")
    set(LINK_FLAGS "${LINK_FLAGS} -mthumb")
    set(LINK_FLAGS "${LINK_FLAGS} -mabi=aapcs")
    set(LINK_FLAGS "${LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map")
    set(CMAKE_EXE_LINKER_FLAGS ${LINK_FLAGS})

    set(
        CMAKE_C_COMPILER 
        ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT}
        CACHE INTERNAL "C Compiler"
        )

    set(
        CMAKE_CXX_COMPILER 
        ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-g++${TOOLCHAIN_EXT} 
        CACHE INTERNAL "C++ Compiler"
        )

    set(
        CMAKE_ASM_COMPILER 
        ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT} 
        CACHE INTERNAL "ASM Compiler"
        )

    set(CMAKE_SYSROOT ${TOOLCHAIN_PREFIX}/${TOOLCHAIN})

    set(
            CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PREFIX}/${TOOLCHAIN} 
            ${CMAKE_PREFIX_PATH}
        )

    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

    set(CMAKE_OBJCOPY ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objcopy${TOOLCHAIN_EXT})
    set(CMAKE_OBJDUMP ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objdump${TOOLCHAIN_EXT})
    set(CMAKE_SIZE ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-size${TOOLCHAIN_EXT})

    #---------------------------------------------------------------------------
    # Prints the section sizes
    #---------------------------------------------------------------------------
    function(print_section_sizes TARGET)
        add_custom_command(TARGET ${TARGET} POST_BUILD 
        COMMAND ${CMAKE_SIZE} 
        ${TARGET})
    endfunction()

    #---------------------------------------------------------------------------
    # Creates output in hex format
    #---------------------------------------------------------------------------
    function(create_hex_output TARGET)
        add_custom_target(${TARGET}.hex ALL DEPENDS ${TARGET} 
        COMMAND ${CMAKE_OBJCOPY} -Oihex ${TARGET} ${TARGET}.hex)
    endfunction()

    #---------------------------------------------------------------------------
    # Creates output in binary format
    #---------------------------------------------------------------------------
    function(create_bin_output TARGET)
        add_custom_target(${TARGET}.bin ALL DEPENDS ${TARGET} 
        COMMAND ${CMAKE_OBJCOPY} -Obinary ${TARGET} ${TARGET}.bin)
    endfunction()

    #---------------------------------------------------------------------------
    # Set Debugger tools
    #---------------------------------------------------------------------------
    set(GDB_BIN ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gdb${TOOLCHAIN_EXT})
    if(NOT OPENOCD_BIN)

        if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)

            set(
                OPENOCD_BIN 
                "/usr/bin/openocd" 
                CACHE STRING "OpenOCD executable"
                )

        elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)

            set(
                OPENOCD_BIN 
                "/usr/local/bin/openocd" 
                CACHE STRING "OpenOCD executable"
                )

        elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)

            set(
                OPENOCD_BIN 
                "C:/openocd/bin/openocd.exe" 
                CACHE STRING "OpenOCD executable"
                )

        endif()

    endif()

    target_compile_definitions(${PROJECT_TARGET} PUBLIC MCU_APP)
    target_compile_definitions(${PROJECT_TARGET} PUBLIC ${PROCESSOR_MPN})
    target_compile_definitions(${PROJECT_TARGET} PUBLIC USE_HAL_DRIVER)

endif()


message("USER_SRC_DIR = ${USER_SRC_DIR}")


#CORE APPLICATION
message("Detecting .c files...")
file(GLOB_RECURSE SOURCE_MODULES "${USER_SRC_DIR}/Application/*.c" "${USER_SRC_DIR}/Middleware/*.c")
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

