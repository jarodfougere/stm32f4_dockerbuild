include_guard()
include(CTest)
enable_testing()
set(CPACK_MY_PROJECT_NAME ${PROJECT_BUILD_TARGET})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)