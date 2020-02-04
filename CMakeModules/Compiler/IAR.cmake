include_guard()

macro(__compiler_iar_ilink lang)
  set(CMAKE_EXECUTABLE_SUFFIX ".elf")
  if (${lang} STREQUAL "C" OR ${lang} STREQUAL "CXX")
    set(CMAKE_${lang}_COMPILE_OBJECT             "<CMAKE_${lang}_COMPILER> ${CMAKE_IAR_${lang}_FLAG} --silent <SOURCE> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT>")
    set(CMAKE_${lang}_CREATE_PREPROCESSED_SOURCE "<CMAKE_${lang}_COMPILER> ${CMAKE_IAR_${lang}_FLAG} --silent <SOURCE> <DEFINES> <INCLUDES> <FLAGS> --preprocess=cnl <PREPROCESSED_SOURCE>")
    set(CMAKE_${lang}_CREATE_ASSEMBLY_SOURCE     "<CMAKE_${lang}_COMPILER> ${CMAKE_IAR_${lang}_FLAG} --silent <SOURCE> <DEFINES> <INCLUDES> <FLAGS> -lAH <ASSEMBLY_SOURCE> -o <OBJECT>.dummy")

    set(CMAKE_${lang}_RESPONSE_FILE_LINK_FLAG "-f ")
    set(CMAKE_DEPFILE_FLAGS_${lang} "--dependencies=ns <DEPFILE>")

    string(APPEND CMAKE_${lang}_FLAGS_INIT " ")
    string(APPEND CMAKE_${lang}_FLAGS_DEBUG_INIT " -r")
    string(APPEND CMAKE_${lang}_FLAGS_MINSIZEREL_INIT " -Ohz -DNDEBUG")
    string(APPEND CMAKE_${lang}_FLAGS_RELEASE_INIT " -Oh -DNDEBUG")
    string(APPEND CMAKE_${lang}_FLAGS_RELWITHDEBINFO_INIT " -Oh -r -DNDEBUG")
  endif()

  if (${lang} STREQUAL "ASM")
    string(APPEND CMAKE_ASM_FLAGS_INIT " ")
    string(APPEND CMAKE_ASM_FLAGS_DEBUG_INIT " -r")
    string(APPEND CMAKE_ASM_FLAGS_MINSIZEREL_INIT " -DNDEBUG")
    string(APPEND CMAKE_ASM_FLAGS_RELEASE_INIT " -DNDEBUG")
    string(APPEND CMAKE_ASM_FLAGS_RELWITHDEBINFO_INIT " -r -DNDEBUG")
  endif()

  set(CMAKE_${lang}_LINK_EXECUTABLE "\"${CMAKE_IAR_LINKER}\" --silent <OBJECTS> <CMAKE_${lang}_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES> -o <TARGET>")
  set(CMAKE_${lang}_CREATE_STATIC_LIBRARY "\"${CMAKE_IAR_ARCHIVE}\" <TARGET> --create <LINK_FLAGS> <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_CREATE "\"${CMAKE_IAR_ARCHIVE}\" <TARGET> --create <LINK_FLAGS> <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_APPEND "\"${CMAKE_IAR_ARCHIVE}\" <TARGET> --replace <LINK_FLAGS> <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_FINISH "")

  set(CMAKE_LINKER "${CMAKE_IAR_LINKER}" CACHE FILEPATH "The IAR linker" FORCE)
  set(CMAKE_AR "${CMAKE_IAR_ARCHIVE}" CACHE FILEPATH "The IAR archiver" FORCE)
endmacro()

macro(__compiler_iar_xlink lang)
  set(CMAKE_EXECUTABLE_SUFFIX ".bin")
  if (${lang} STREQUAL "C" OR ${lang} STREQUAL "CXX")

    set(CMAKE_${lang}_COMPILE_OBJECT             "<CMAKE_${lang}_COMPILER> ${CMAKE_IAR_${lang}_FLAG} --silent <SOURCE> <DEFINES> <INCLUDES> <FLAGS> -o <OBJECT>")
    set(CMAKE_${lang}_CREATE_PREPROCESSED_SOURCE "<CMAKE_${lang}_COMPILER> ${CMAKE_IAR_${lang}_FLAG} --silent <SOURCE> <DEFINES> <INCLUDES> <FLAGS> --preprocess=cnl <PREPROCESSED_SOURCE>")
    set(CMAKE_${lang}_CREATE_ASSEMBLY_SOURCE     "<CMAKE_${lang}_COMPILER> ${CMAKE_IAR_${lang}_FLAG} --silent <SOURCE> <DEFINES> <INCLUDES> <FLAGS> -lAH <ASSEMBLY_SOURCE> -o <OBJECT>.dummy")

    set(CMAKE_${lang}_RESPONSE_FILE_LINK_FLAG "-f ")
    set(CMAKE_DEPFILE_FLAGS_${lang} "--dependencies=ns <DEPFILE>")

    string(APPEND CMAKE_${lang}_FLAGS_INIT " ")
    string(APPEND CMAKE_${lang}_FLAGS_DEBUG_INIT " -r")
    string(APPEND CMAKE_${lang}_FLAGS_MINSIZEREL_INIT " -Ohz -DNDEBUG")
    string(APPEND CMAKE_${lang}_FLAGS_RELEASE_INIT " -Oh -DNDEBUG")
    string(APPEND CMAKE_${lang}_FLAGS_RELWITHDEBINFO_INIT " -Oh -r -DNDEBUG")
  endif()

  if (${lang} STREQUAL "ASM")
    string(APPEND CMAKE_ASM_FLAGS_INIT " ")
    string(APPEND CMAKE_ASM_FLAGS_DEBUG_INIT " -r")
    string(APPEND CMAKE_ASM_FLAGS_MINSIZEREL_INIT " -DNDEBUG")
    string(APPEND CMAKE_ASM_FLAGS_RELEASE_INIT " -DNDEBUG")
    string(APPEND CMAKE_ASM_FLAGS_RELWITHDEBINFO_INIT " -r -DNDEBUG")
  endif()

  set(CMAKE_${lang}_LINK_EXECUTABLE "\"${CMAKE_IAR_LINKER}\" -S <OBJECTS> <CMAKE_${lang}_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES> -o <TARGET>")
  set(CMAKE_${lang}_CREATE_STATIC_LIBRARY "\"${CMAKE_IAR_AR}\" <TARGET> <LINK_FLAGS> <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_CREATE "\"${CMAKE_IAR_AR}\" <TARGET> <LINK_FLAGS> <OBJECTS>")
  set(CMAKE_${lang}_ARCHIVE_APPEND "")
  set(CMAKE_${lang}_ARCHIVE_FINISH "")

  set(CMAKE_LIBRARY_PATH_FLAG "-I")

  set(CMAKE_LINKER "${CMAKE_IAR_LINKER}" CACHE FILEPATH "The IAR linker" FORCE)
  set(CMAKE_AR "${CMAKE_IAR_AR}" CACHE FILEPATH "The IAR archiver" FORCE)
endmacro()