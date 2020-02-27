message("[INFO]    entering toolchain-iar.cmake")
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PREFIX}/bin)

foreach(lang "C" "ASM" "CXX")
    foreach(tool CMAKE_${lang}_COMPILER)
        set(${tool} ${TOOLCHAIN_BIN_DIR}/${${tool}})
        message("tool = ${${tool}}")

    endforeach()
endforeach()

#set(CMAKE_C_COMPILER ${TOOLCHAIN_PREFIX}/bin/${CMAKE_C_COMPILER})
#set(CMAKE_ASM_COMPILER ${TOOLCHAIN_PREFIX}/bin/${CMAKE_ASM_COMPILER})
#set(CMAKE_CXX_COMPILER ${TOOLCHAIN_PREFIX}/bin/${CMAKE_CXX_COMPILER})

message("[INFO]    exiting toolchain-iar.cmake")
