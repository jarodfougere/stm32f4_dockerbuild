set(CMAKE_SYSTEM_NAME Generic) # 'Generic' is used for embedded systems
set(CMAKE_CROSSCOMPILING ON)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

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
find_program(ARM_GDB_EXECUTABLE arm-none-eabi-gdb) 


set(shared_options "-Wall -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffreestanding -ffunction-sections -fdata-sections --specs=nosys.specs")
set(CMAKE_C_FLAGS_INIT "${shared_options}" CACHE INTERNAL "Initial options for C compiler.")
set(CMAKE_CXX_FLAGS_INIT "${shared_options}" CACHE INTERNAL "Initial options for C++ compiler.")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections" CACHE INTERNAL "Initial options for executable linker.")
