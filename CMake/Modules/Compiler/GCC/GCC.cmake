if(DEFINED GCC_MODULE_INCLUDED)
    return()
else()
    set(GCC_MODULE_INCLUDED 1)
endif()

if(MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif(UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif()

set(CMAKE_C_COMPILER gcc CACHE string("the C compiler"))
set(CMAKE_ASM_COMPILER gcc CACHE string("the asm compiler"))
set(CMAKE_CXX_COMPILER g++ CACHE string("the c++ compiler"))
set(CMAKE_OBJCOPY objcopy CACHE string("the object copy tool"))

execute_process(
    COMMAND ${UTIL_SEARCH_CMD} gcc
    OUTPUT_VARIABLE BINUTILS_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

get_filename_component(GCC_TOOLCHAIN_DIR ${BINUTILS_PATH} DIRECTORY)
set(CMAKE_OBJCOPY ${GCC_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}objcopy CACHE INTERNAL "toolchain objcopy tool")
set(CMAKE_SIZE_UTIL ${GCC_TOOLCHAIN_DIR}/${TOOLCHAIN_PREFIX}size CACHE INTERNAL "toolchain size tool")
set(CMAKE_CROSSCOMPILING 0)
set(CMAKE_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME})

IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(TOOLCHAIN_TARGET_SUFFIX .exe)
else()
    set(TOOLCHAIN_TARGET_SUFFIX .out)
endif()
