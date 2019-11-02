/* Program Entry, set to mark it as "used" and avoid gcc warnings */
ENTRY(Startup_ResetHandler)

/* Memory Spaces Definitions */
MEMORY
{
	SRAM     (RWX) : ORIGIN = 0x20000000, LENGTH = 96K
	SRAM2    (RWX) : ORIGIN = 0x10000000, LENGTH = 32K
	FLASH    (RX)  : ORIGIN = 0x08000000, LENGTH = 512K
}

/* code/data sections */
SECTIONS
{
    /* basic memory layout: SRAM */
	__sram_size     = LENGTH(SRAM);
	__sram_addr     = ORIGIN(SRAM);

    /* basic memory layout: SRAM2 */
	__sram2_size     = LENGTH(SRAM2);
	__sram2_addr     = ORIGIN(SRAM2);

	/* basic memory layout: FLASH */
	__flash_size    = LENGTH(FLASH);
	__flash_addr    = ORIGIN(FLASH);

    /*
     * FLASH MEMORY AREA
     */
     
    /* code */
    .flash_code : 
    {
        /* flash code starts here */
        __flash_code_addr = ABSOLUTE(.);

        /* exception & interrupt vectors */
        __flash_vectors = ABSOLUTE(.);
        /* make sure that these stay in the output file */
        KEEP(*(.flash_vectors))

        /* Program code */
        *(.text)                    
        *(.text.*)                  
        *(.stub .gnu.linkonce.t.*)
        *(.glue_7)         /* glue arm to thumb code */
        *(.glue_7t)        /* glue thumb to arm code */  
        /* read-only data */
        *(.rodata .rodata.*)        
        /* align code to 4 bytes */
        . = ALIGN(4); 
    } > FLASH
    
    /* flash data */
    .flash_data :
    {
        *(.flash_data)
        *(.flash_data.*)
        . = ALIGN(4); 
    } > FLASH
    
    /* needed for 64 bit division */
	.ARM.exidx : 
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > FLASH
	
	.ARM.extab : { 
        *(.ARM.extab* .gnu.linkonce.armextab.*) 
    } > FLASH
    
    /* flash code ends here */
    __flash_code_size = . - __flash_code_addr;
    /* all data/code to be initialized from flash will go here */ 
    __flash_sram_init_src_addr = .;

    
    /*
     * SRAM MEMORY AREA
     */

    /* SRAM memory (uninitialized data) */
    .bss (NOLOAD) : ALIGN(4)
    {
        *(.bss)       
        *(.bss.*)
        *(COMMON)
    } > SRAM

    /* code in sram memory */
    .ram_code ALIGN(4) :
    {
        /* start of the ram_code section address */
        __ram_code_addr = ABSOLUTE(.);
        /* ram code */
        *(.ram_code)       
        *(.ram_code.*)
        /* size of the ram code section */
        __ram_code_size = ABSOLUTE(.) - __ram_code_addr;
    } > SRAM AT > FLASH

    /* initialized data in sram memory */
    .data ALIGN(4) : 
    {
        /* start of the data section address */
        __data_addr = ABSOLUTE(.);
        /* data memory */             
        *(.data)                    
        *(.data.*)
		/* put a memory guard here */
        *(.mem_guard)
        KEEP(*(.mem_guard))
        /* data section size */
        __data_size = ABSOLUTE(.) - __data_addr;
    } > SRAM AT > FLASH


    /*
     * SRAM2 MEMORY AREA
     */
     
    /* sram2 memory (uninitialized data) */
    .bss2 (NOLOAD) : ALIGN(4)
    {
        *(.bss2)       
        *(.bss2.*)
    } > SRAM2

    /* sram2 memory (initialized data) */
    .data2 ALIGN(4) : 
    {
        /* start of the data section address */
        __data2_addr = ABSOLUTE(.);
        *(.data2)
        *(.data2.*)
        /* data section size */
        __data2_size = ABSOLUTE(.) - __data2_addr;
    } > SRAM2 AT > FLASH

    /* bss start-end */
    __bss_addr = ADDR(.bss);
    __bss_size = SIZEOF(.bss);
    /* bss2 start-end */
    __bss2_addr = ADDR(.bss2);
    __bss2_size = SIZEOF(.bss2);

    /* stack pointer */
    __stack = ORIGIN(SRAM) + LENGTH(SRAM);
	
    /* complete flash image size */
    __flash_image_size = __flash_code_size + __ram_code_size + __data_size;

    /* sanity check */
    ASSERT(__flash_image_size <= LENGTH(FLASH), 
        "FLASH MEMORY LIMIT EXCEEDED")
} 
