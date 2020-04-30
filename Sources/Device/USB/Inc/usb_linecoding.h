#ifndef __LINECODING_H
#define __LINECODING_H
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

    /***************************************************************************
     * @brief The table below describes the necessary structure and
     * bit fields to enumerate the USB peripheral as a CDC class dev 
     * (class sub descriptor) once the usb OTG peripheral has enumerated
     * as a base USB device AND the CDC class request descriptor packet
     * has been sent by the host.
     * 
     * |------------------------------------------------------------------|
     * |              USB CDC line coding structure and format            |
     * |--------+-------------+--------------+---------+------------------|
     * | Offset |    Field    | Size (bytes) |  Value  |  Description     |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Data terminal    |
     * |   0    |  dwDTERate  |       4      | number  | rate in bits per |
     * |        |             |              |         | second           |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Num Stop bits    |
     * |   4    | bCharFormat |       1      | number  | 0: 1 stop bit    |
     * |        |             |              |         | 1: 1.5 stop bits |
     * |        |             |              |         | 2: 2 stop bits   |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Parity:          |
     * |        |             |              |         | 0: None          |
     * |   5    | bParityType |      1       | number  | 1: Odd           |
     * |        |             |              |         | 2: Even          |
     * |        |             |              |         | 3: Mark          |
     * |        |             |              |         | 3: Space         |
     * |--------+-------------+--------------+---------+------------------|
     * |        |             |              |         | Num data bits    |
     * |   6    | bDataBits   |      1       | number  | Valid values are |
     * |        |             |              |         | 5, 6, 7, 8, 16   |
     * |--------+-------------+--------------+---------+------------------|
     **************************************************************************/

    typedef union
    {
        struct
        {
            uint32_t dwDTERate;
            uint8_t bCharFormat;
            uint8_t bParityType;
            uint8_t bDataBits;
        } fields;
        uint8_t bytes[8];
    } usbSerialLineCoding;

#ifdef __cplusplus
}
#endif
#endif /* __LINECODING_H */
