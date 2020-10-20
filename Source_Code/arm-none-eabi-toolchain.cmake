# CMAKE TOOLCHAIN FILE FOR arm-none-eabi-gcc
# AUTHOR: Carl Mattatall (cmattatall2@gmail.com) 

macro(listToOptionString list_string)
    string(REPLACE ";" "\ " list_as_string "${${list_string}}")
    set(${list_string} ${list_as_string})
endmacro(listToOptionString list)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)
set(CMAKE_CROSSCOMPILING ON)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

if(MINGW OR CYGWIN OR WIN32)
    set(UTIL_SEARCH_CMD where)
elseif(UNIX OR APPLE)
    set(UTIL_SEARCH_CMD which)
endif()

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)
set(CMAKE_DEBUGGER arm-none-eabi-gdb)
set(CMAKE_DEBUGGER arm-none-eabi-gdb)
set(CMAKE_CPPFILT arm-none-eabi-c++filt)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# find additional toolchain executables
find_program(ARM_SIZE_EXECUTABLE arm-none-eabi-size REQUIRED) 
find_program(ARM_OBJCOPY_EXECUTABLE arm-none-eabi-objcopy REQUIRED) 
find_program(ARM_OBJDUMP_EXECUTABLE arm-none-eabi-objdump REQUIRED)
find_program(ARM_GDB_EXECUTABLE arm-none-eabi-gdb) # note that this one is not required

#@todo SHOULD PROBABLY BE PROVIDING ARCH OPTIONS VIA A FILE
set(arch_options 
    "-mlittle-endian" 
    "-mthumb" 
    "-mcpu=cortex-m4" 
    "-mfloat-abi=hard" 
    "-mfpu=fpv4-sp-d16"
    )
listToOptionString(arch_options)

set(warning_options "-Wall -Wextra")

set(platform_options 
    "-mthumb-interwork" 
    # emit instructions that support both ARM and THUMB ISA 

    "-ffreestanding"    
    # Do not assume libc symbol existence when linking

    "-ffunction-sections" 
    # generate separate ELF sections for each function in a translation unit
    # THIS LETS US PLACE VECTOR TABLE 
    #using __attribute__(section("name"))

    "-fdata-sections"      
    # generate separate ELF sections for each variable in a translation unit
    
    "--specs=nosys.specs"
    # Don't use newlib or libc calls to generate startup code
    # startup assembly is explicitly provided as a translation unit
    )
listToOptionString(platform_options)

set(CMAKE_C_FLAGS_INIT 
    "${warning_options} ${platform_options} ${arch_options}" 
     CACHE INTERNAL "Initial options for C compiler.")

set(CMAKE_CXX_FLAGS_INIT 
    "${warning_options} ${platform_options} ${arch_options} -fno-rtti -fno-exceptions" 
     CACHE INTERNAL "Base C++ compiler flags")

set(CMAKE_EXE_LINKER_FLAGS_INIT 
    "-Wl,--gc-sections" 
    CACHE INTERNAL "Initial options for executable linker.")
