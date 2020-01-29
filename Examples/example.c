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

/* work out end of RAM address as initial stack pointer */
#define SRAM_SIZE       48*1024     // STM32F103RB has 48 Kbye of RAM
#define SRAM_BASE       0x2000000UL
#define SRAM_END        (SRAM_BASE + SRAM_SIZE)
#define FLASH_BASE      0x08000000UL



union vectTableEntry
{
    unsigned long (*isr)(void);
    unsigned long *initialStackPointer;
};



int main(void);



/* vector table */
const unsigned long *vector_table[] 
#if defined(ICCARM)
@ FLASH_BASE
#elif defined(__GNUC__)
__attribute__((section(".vector_table")))
#endif
=
{
    (unsigned long*)SRAM_END,
    (unsigned long*)main,
};


#if 0
int main(void)
{
    uint32_t x;
    while (1)
    {   
        for(x = 0; x < 20; x++) 
        {
            uint32_t y;
            for( y = 0; y < 50; y++)
            {
                y += x;
            }
        }
    }
}

#endif