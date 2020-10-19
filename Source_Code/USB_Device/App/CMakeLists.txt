file(GLOB_RECURSE sources "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.c")
target_sources(USB_CLASS_LIB PUBLIC ${sources})
target_link_libraries(USB_CLASS_LIB PUBLIC RTOS_LIB)
