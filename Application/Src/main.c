/*

COMPILE
arm-none-eabi-gcc -c -fno-common -O0 -g -mcpu=cortex-m3 -mthumb -Wall -Wextra -o main.o example.c

DUMP (debug)
arm-none-eabi-objdump -x main.o

LINK 
arm-none-eabi-ld -nostartfiles -T linker.ld -O ihex -o main.hex main.o

CONVERT ELF TO BIN
arm-none-eabi-objcopy.exe -O binary main.elf main.bin

CONVERT BINARY TO HEX

arm-none-eabi-objcopy -O binary main.elf main.bin 
arm-none-eabi-objcopy -O ihex main.elf main.hex 
arm-none-eabi-size main.o

*/


#include <stdint.h>

void main(void)
{

    while(1)
    {
        
    }
}



