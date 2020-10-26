file(GLOB_RECURSE sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.c" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.S" )


# Configure output files
set(elf_file ${firmware_name}.elf)
set(bin_file ${firmware_name}.bin)
set(hex_file ${firmware_name}.hex)
set(map_file ${firmware_name}.map)
set(lss_file ${firmware_name}.lss)
add_executable(${elf_file})
target_sources(${elf_file} PUBLIC ${sources})
target_link_libraries(${elf_file} PUBLIC HAL_DRIVER_LIB)
target_link_libraries(${elf_file} PUBLIC USB_CLASS_LIB)
target_link_libraries(${elf_file} PUBLIC USB_DEVICE_LIB)
target_link_libraries(${elf_file} PUBLIC RTOS_LIB)
target_link_libraries(${elf_file} PUBLIC -T ${LINKER_SCRIPT})

target_include_directories(${elf_file} PUBLIC ${include_dirs})
target_include_directories(HAL_DRIVER_LIB PUBLIC ${include_dirs})
target_include_directories(USB_DEVICE_LIB PUBLIC ${include_dirs})
target_include_directories(RTOS_LIB PUBLIC ${include_dirs})


# POST BUILD TASKS
set(out_dir ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_custom_target(${firmware_name} ALL DEPENDS ${elf_file})
add_custom_command( TARGET ${firmware_name}
                    POST_BUILD
                    DEPENDS ${elf_file}
                    COMMENT "Built executable ${elf_file} with the following size:"
                    COMMAND ${CMAKE_SIZE} -B ${out_dir}/${elf_file}
                    )

add_custom_command( TARGET ${firmware_name}
                    POST_BUILD
                    DEPENDS ${elf_file}
                    COMMENT "Producing a hex output using ${CMAKE_OBJCOPY}"
                    COMMAND ${CMAKE_OBJCOPY} -O ihex -I elf32-little ${out_dir}/${elf_file} ${out_dir}/${hex_file}
                    )

add_custom_command( TARGET ${firmware_name}
                    POST_BUILD
                    DEPENDS ${elf_file}
                    COMMENT "Producing a binary output using ${CMAKE_OBJCOPY}"
                    COMMAND ${CMAKE_OBJCOPY} -O binary -I elf32-little ${out_dir}/${elf_file} ${out_dir}/${bin_file}
                    )

add_custom_command( TARGET ${firmware_name}
                    POST_BUILD
                    DEPENDS ${elf_file}
                    COMMENT "Generating lss file from ${elf_file} using ${CMAKE_OBJDUMP}"
                    COMMAND ${CMAKE_OBJDUMP} -x ${out_dir}/${elf_file} > ${out_dir}/${lss_file}
                    )

