include_guard(GLOBAL)

if(NOT DEFINED LINKER_SCRIPT)
    message(FATAL_ERROR "No linker script defined. Please provide a linker script for the cmake configuration eg: -DmyLinkerScript.ld")
else()
    message("Using Linker script: ${LINKER_SCRIPT}")
endif()

set(ARCH_FLAGS "-march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16")




