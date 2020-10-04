add_library(USB_DEVICE_LIB STATIC)
add_subdirectory(Class/CDC)
add_subdirectory(Core)
target_link_libraries(USB_DEVICE_LIB PUBLIC HAL_DRIVER_LIB)
