set(_compiler_id_pp_test "defined(__IAR_SYSTEMS_ICC__) || defined(__IAR_SYSTEMS_ICC)")

set(_compiler_id_version_compute "
# if defined(__VER__) && defined(__ICCARM__)
#  define @PREFIX@COMPILER_VERSION_MAJOR @MACRO_DEC@((__VER__) / 1000000)
#  define @PREFIX@COMPILER_VERSION_MINOR @MACRO_DEC@(((__VER__) / 1000) % 1000)
#  define @PREFIX@COMPILER_VERSION_PATCH @MACRO_DEC@((__VER__) % 1000)
#  define @PREFIX@COMPILER_VERSION_INTERNAL @MACRO_DEC@(__IAR_SYSTEMS_ICC__)
# elif defined(__VER__) && (defined(__ICCAVR__) || defined(__ICCRX__) || defined(__ICCRH850__) || defined(__ICCRL78__) || defined(__ICC430__) || defined(__ICCRISCV__) || defined(__ICCV850__) || defined(__ICC8051__))
#  define @PREFIX@COMPILER_VERSION_MAJOR @MACRO_DEC@((__VER__) / 100)
#  define @PREFIX@COMPILER_VERSION_MINOR @MACRO_DEC@((__VER__) - (((__VER__) / 100)*100))
#  define @PREFIX@COMPILER_VERSION_PATCH @MACRO_DEC@(__SUBVERSION__)
#  define @PREFIX@COMPILER_VERSION_INTERNAL @MACRO_DEC@(__IAR_SYSTEMS_ICC__)
# endif")