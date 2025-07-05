/* Linker script for STM32F429ZI with Micrium OS support (ARM GNU 10.3.1) */

ENTRY(Reset_Handler)

MEMORY
{
  FLASH   (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
  RAM     (xrw) : ORIGIN = 0x20000000, LENGTH = 192K  /* Main SRAM */
  CCMRAM  (xrw) : ORIGIN = 0x10000000, LENGTH = 64K   /* Core Coupled Memory */
}

_estack = ORIGIN(RAM) + LENGTH(RAM); /* Initial stack pointer */
_Min_Heap_Size = 0x2000;  /* 8 KB heap  */
_Min_Stack_Size = 0x1000; /* 4 KB stack */

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)           /* All program code */
    *(.text*)          
    *(.rodata)         /* Read-only data (const) */
    *(.rodata*)        
    *(.glue_7)
    *(.glue_7t)
    KEEP(*(.init))
    KEEP(*(.fini))
    . = ALIGN(4);
  } > FLASH

  .ARM.extab : { *(.ARM.extab* .gnu.linkonce.armextab.*) } > FLASH
  .ARM.exidx : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) } > FLASH

  .preinit_array     :
  {
    KEEP(*(.preinit_array))
  } > FLASH
  .init_array :
  {
    KEEP(*(SORT(.init_array.*)))
    KEEP(*(.init_array))
  } > FLASH
  .fini_array :
  {
    KEEP(*(SORT(.fini_array.*)))
    KEEP(*(.fini_array))
  } > FLASH

  .data :
  {
    . = ALIGN(4);
    _sdata = .;
    *(.data)
    *(.data*)
    . = ALIGN(4);
    _edata = .;
  } > RAM AT > FLASH

  .bss :
  {
    . = ALIGN(4);
    _sbss = .;
    __bss_start__ = _sbss;
    *(.bss)
    *(.bss*)
    *(COMMON)
    . = ALIGN(4);
    _ebss = .;
    __bss_end__ = _ebss;
  } > RAM

  /* Micrium OS Heap and User Stack Section */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    _end = .;
    PROVIDE(end = .);
    . = . + _Min_Heap_Size;
    _heap_end = .;
    . = . + _Min_Stack_Size;
    _estack_region = .;
  } >RAM

  /* CCM RAM Section (Optional for Micrium task stacks or buffers) */
  .ccmram (NOLOAD) :
  {
    . = ALIGN(4);
    _sccmram = .;
    *(.ccmram)
    *(.ccmram*)
    . = ALIGN(4);
    _eccmram = .;
  } >CCMRAM

  /* .ARM.attributes section for GCC */
  .ARM.attributes 0 : { *(.ARM.attributes) }
}