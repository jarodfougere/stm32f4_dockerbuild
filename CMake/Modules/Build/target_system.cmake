################################################################################
## THIS MODULE CONFIGURES THE BUILD PIPELINE FOR THE TARGET SYSTEM
## 
## IN CASES WHERE THE TARGET SYSTEM IS AN EXTERNAL PROCESSOR OR AN 
## ARCHITECTURE THAT DOES NOT MATCH THAT OF THE SYSTEM PERFORMING THE 
## COMPILATION, THIS MODULE SHALL SET THE APPROPRIATE CONFIGURATION
##
## AUTHOR:  CARL MATTATAL
## LICENSE: RIMOT.IO INCORPORATED
################################################################################

if(DEFINED PROJECT_BUILD_TARGET)

    ####    !!! DEVELOPER NOTE: !!!
    ####
    ####    TARGET_BINARY IS A DEFINITION PASSED IN 
    ####    BY THE CALL TO THE CMAKE TASK AS CONFIGURED BY THE USER 
    ####
    ####    YOU WILL NOT FIND MEANINGFUL DEFINITION FOR THE VARIABLE
    ####    IN ANY OF THE BUILD MODULES, ONLY REFERENCES TO ITS EXISTENCE
    ############################################################################

    TARGET_COMPILE_DEFINITIONS(${PROJECT_BUILD_TARGET} PUBLIC ${TARGET_BINARY})
    if(DEFINED TARGET_BINARY)
        if(${TARGET_BINARY} STREQUAL HOST_SYSTEM)
            message("USER HAS CONFIGURED TARGET_BINARY == HOST_SYSTEM")

        elseif(${TARGET_BINARY} STREQUAL TARGET_SYSTEM)
            message("USER HAS CONFIGURED TARGET_BINARY == TARGET_SYSTEM")
            include(${CMAKE_MODULE_PATH}/Compiler/IAR/IAR-FindBinUtils.cmake)
            include(${CMAKE_MODULE_PATH}/Compiler/IAR/IAR.cmake)
        else()
            message(FATAL_ERROR 
            "PLEASE SELECT EITHER >LOCAL< OR >PROCESSOR< AS TARGET_BINARY")
        endif()
    endif() # END OF IF(DEFINED TARGET_BINARY)
else()
    message(FATAL_ERROR "PROJECT HAS NOT DEFINED >PROJECT_BUILD_TARGET<")
endif()