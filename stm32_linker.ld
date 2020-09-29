ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx):ORIGIN =0x08000000, LENGTH =64K
    SRAM(rwx):ORIGIN =0x20000000, LENGTH =20K
}

SECTIONS
{
    .text :
    {
        *(.isr_vector)
        *(.text)
        *(.rodata)
        . = ALIGN(4); /*align to the nex word boundary (32-bit is a word)*/
        end_of_text = .;     /* store the updated loaaction counter value into a symbol*/
    }> FLASH
    
    /*unitialized data*/
    .data :
    {
        start_of_data = 0x20000000; 
        *(.data)
        . = ALIGN(4);
        end_of_data = .;
    }>SRAM AT>FLASH

    /*initialized data*/
    .bss :
    {
        start_of_bss = .;
        *(.bss)
        *(COMMON)
        . = ALIGN(4);
        end_of_bss = .;
    }>SRAM
}