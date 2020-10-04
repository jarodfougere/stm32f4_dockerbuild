file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.c")
target_sources(USB_DEVICE_LIB PUBLIC ${sources})