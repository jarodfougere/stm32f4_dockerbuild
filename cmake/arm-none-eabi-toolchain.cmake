set(CMAKE_SYSTEM_NAME Generic) # 'Generic' is used for embedded systems
set(CMAKE_CROSSCOMPILING ON)

set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

# tells CMake not to try to link executables during its interal checks
# things are not going to link properly without a linker script
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(CMAKE_OBJCOPY arm-none-eabi-objcopy)
set(CMAKE_OBJDUMP arm-none-eabi-objdump)
set(CMAKE_SIZE arm-none-eabi-size)
set(CMAKE_DEBUGGER arm-none-eabi-gdb)
set(CMAKE_DEBUGGER arm-none-eabi-gdb)
set(CMAKE_CPPFILT arm-none-eabi-c++filt)


#set(CORE_FLAGS "-mthumb -mcpu=cortex-m4 -mlittle-endian -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb-interwork --specs=nano.specs --specs=nosys.specs ${ADDITIONAL_CORE_FLAGS}")

# compiler: language specific flags
#set(CMAKE_C_FLAGS "${CORE_FLAGS} -fno-builtin -Wall -std=gnu99 -fdata-sections -ffunction-sections -g3 -gdwarf-2" CACHE INTERNAL "c compiler flags")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# find additional toolchain executables
find_program(ARM_SIZE_EXECUTABLE arm-none-eabi-size)
find_program(ARM_GDB_EXECUTABLE arm-none-eabi-gdb)
find_program(ARM_OBJCOPY_EXECUTABLE arm-none-eabi-objcopy)
find_program(ARM_OBJDUMP_EXECUTABLE arm-none-eabi-objdump)

set(CMAKE_SYSROOT ${TOOLCHAIN_SYSROOT})

message("cmake c compiler = ${CMAKE_C_COMPILER}")


set(shared_options "-Wall -mlittle-endian -mthumb -mcpu=cortex-m4 -mthumb-interwork -mfloat-abi=hard -mfpu=fpv4-sp-d16 -ffreestanding -ffunction-sections -fdata-sections --specs=nosys.specs")
set(CMAKE_C_FLAGS_INIT "${shared_options}" CACHE INTERNAL "Initial options for C compiler.")
set(CMAKE_CXX_FLAGS_INIT "${shared_options}" CACHE INTERNAL "Initial options for C++ compiler.")
set(CMAKE_EXE_LINKER_FLAGS_INIT "-Wl,--gc-sections" CACHE INTERNAL "Initial options for executable linker.")

#
#
#find_program(c_compiler_path ${CMAKE_C_COMPILER})
#get_filename_component(toolchain_bin_dir ${c_compiler_path} DIRECTORY)
#get_filename_component(toolchain_root ${toolchain_bin_dir} DIRECTORY)
#set(TOOLCHAIN_SYSROOT "${toolchain_root}/arm-none-eabi")
#message("toolchain_prefix = ${TOOLCHAIN_PREFIX}")
#set(CMAKE_SYSROOT ${TOOLCHAIN_SYSROOT})
#
#set(CFLAGS_BASE "-ffunction-sections -fdata-sections" CACHE STRING "base compilation flags")
#set(LFLAGS_BASE "-Wl,--relax,--gc-sections" CACHE STRING "base link flags")
#
#
#