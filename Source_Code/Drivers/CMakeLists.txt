file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/STM32F4xx_HAL_Driver/Src/*.c")
add_library(HAL_DRIVER_LIB STATIC)
target_sources(HAL_DRIVER_LIB PUBLIC ${sources})
target_link_libraries(HAL_DRIVER_LIB PUBLIC USB_CLASS_LIB)