/* Linker script for STM32F429ZI with Micrium OS support */

ENTRY(Reset_Handler)

MEMORY
{
  FLASH   (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K
  RAM     (xrw) : ORIGIN = 0x20000000, LENGTH = 256K    /* SRAM1 + SRAM2 */
  CCMRAM  (xrw) : ORIGIN = 0x10000000, LENGTH = 64K     /* For fast-access task stacks */
}

_estack = ORIGIN(RAM) + LENGTH(RAM);   /* Main stack top */
_Min_Heap_Size = 0x200;  /* 512 B heap */
_Min_Stack_Size = 0x800; /* 2 KB main stack */

SECTIONS
{
  .isr_vector :
  {
    KEEP(*(.isr_vector))
  } > FLASH

  .text :
  {
    . = ALIGN(4);
    *(.text)           /* Application code */
    *(.text*)          
    *(.rodata)         /* Read-only data */
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

  /* Heap and main stack section */
  ._user_heap_stack :
  {
    . = ALIGN(8);
    _end = .;
    PROVIDE(end = .);
    . = . + _Min_Heap_Size;
    _heap_end = .;
    . = . + _Min_Stack_Size;
    _estack_region = .;
  } > RAM

  /* Optional CCMRAM section for fast task stacks */
  .ccmram (NOLOAD) :
  {
    . = ALIGN(4);
    _sccmram = .;
    *(.ccmram)
    *(.ccmram*)
    . = ALIGN(4);
    _eccmram = .;
  } > CCMRAM

  .ARM.attributes 0 : { *(.ARM.attributes) }
}