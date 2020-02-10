if(DEFINED IAR_MODULE_INCLUDED)
    return()
else()
    set(IAR_MODULE_INCLUDED 1)
endif()


IF(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_SYSTEM_PROCESSOR arm)
    set(CMAKE_CROSSCOMPILING 1)
    set(CMAKE_TRY_COMPILE_CONFIGURATION STATIC_LIBRARY)

    set(CMAKE_ASM_COMPILER "iasmarm.exe")
    set(CMAKE_C_COMPILER "iccarm.exe")
    set(CMAKE_CXX_COMPILER "iccarm.exe")
    set(CMAKE_LINKER "ilinkarm.exe")
    set(CMAKE_MAKE_PROGRAM "mingw32-make.exe")
    set(CMAKE_EXE_LINKER_FLAGS "--specs=nosys.specs" CACHE INTERNAL "")

    set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
    set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
    set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

else()
    message(FATAL_ERROR "IAR Embedded Workbench for Arm Compiler toolchain only exists on WINDOWS")
endif()