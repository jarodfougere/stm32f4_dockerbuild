# CMAKE TOOLCHAIN FILE FOR arm-none-eabi-gcc
# AUTHOR: Carl Mattatall (cmattatall2@gmail.com) 
#
# @todo 
#  - functions for changing output formats (conv the elf to bin, hex, etc) 
#  - functions for dissassembly
#  - functions for displaying section names
#  - function for generating linker map file
#  - function for launching gdb
#  - function for adding tests (still kinda iffy if this should go in toolchain)

set(CMAKE_SYSTEM_NAME Generic) # 'Generic' is used for embedded systems
set(CMAKE_CROSSCOMPILING ON)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

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

# @todo HAVE USER PROVIDE TARGET OPTIONS IN THE FORM OF A FILE?
# see https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html 
set(target_options "-mlittle-endian -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16")
set(shared_options "${target_options} -Wall  -mthumb-interwork -ffreestanding -ffunction-sections -fdata-sections --specs=nosys.specs")
set(CMAKE_C_FLAGS_INIT "${shared_options}" CACHE INTERNAL "Initial options for C compiler.")
set(CMAKE_CXX_FLAGS_INIT "${shared_options} -fno-rtti -fno-exceptions" CACHE INTERNAL "Base C++ compiler flags")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections" CACHE INTERNAL "Initial options for executable linker.")
