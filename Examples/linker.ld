MEMORY
{
    FLASH_MEMORY (rx)  : ORIGIN = 0x08000000, LENGTH = 128K
    SRAM_MEMORY (xrw)  : ORIGIN = 0x20000000, LENGTH = 20K
}

SECTIONS
{
    .text :
    {   
        *(.vector_table) /* vector table */
        *(.text)         /* code seg */
    } > FLASH_MEMORY

    .data :
    {
        *(.data)
    }   > SRAM_MEMORY
}