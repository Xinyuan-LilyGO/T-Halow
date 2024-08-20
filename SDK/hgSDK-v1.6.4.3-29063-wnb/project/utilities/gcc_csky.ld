/*
 * Copyright (C) 2017 C-SKY Microsystems Co., Ltd. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     gcc_csky.ld
 * @brief    csky linker file
 * @version  V1.0
 * @date     02. June 2017
 ******************************************************************************/
 
SRAM0_LAST_ADDR = 0x20007fff;        /* ×îºóµÄSRAM0µØÖ·*/
 
MEMORY
{
	I-SRAM : ORIGIN = 0x0        , LENGTH = 0x80000   /* I-SRAM  128KB */
	D-SRAM : ORIGIN = 0x20000000 , LENGTH = 0x80000   /* D-SRAM  512KB */
	O-SRAM : ORIGIN = 0x50000000 , LENGTH = 0x800000   /* off-chip SRAM 8MB */
	/*SRAM   : ORIGIN = 0x20000000 , LENGTH = 0xb0000*/   /* on-chip SRAM 128KB */
	SRAM   : ORIGIN = 0x20001000 , LENGTH = 0xaf000    /* on-chip SRAM 124KB */
}

__heap_size = 0x11000;

PROVIDE (__ram_end  = 0x200b0000);
PROVIDE (__heap_end = 0x200b0000);

REGION_ALIAS("REGION_TEXT",    SRAM);
REGION_ALIAS("REGION_RODATA",  SRAM);
REGION_ALIAS("REGION_DATA",    SRAM);
REGION_ALIAS("REGION_BSS",     SRAM);
REGION_ALIAS("REGION_INIT",    SRAM);

ENTRY(Reset_Handler)
SECTIONS
{
  .text : AT(ADDR(.text)){
  . = ALIGN(0x4) ;
  KEEP(*startup.o(.vectors))
  KEEP(*(SYS_PARAM))
  KEEP(*(DSLEEP_PARAM))
  KEEP(*libgcc.a:*_muldi3.o(.text))
  KEEP(*dsleep.o(.text* .rodata* .data*))
  KEEP(*sysctrl.o(.text* .rodata* .data*))
  KEEP(*lmac_hw.o(.text* .rodata* .data*))
  KEEP(*hgrf_s1gv3_parameter.o(.rodata* .data*))
  KEEP(*(.dsleep_text))
  KEEP(*(.dsleep_data))
  __dsleep_end__ = .;
  __stext = . ;
  *(.text)
  *(.text*)
  *(.text.*)
  *(NON_DSLEEP)
  *(.gnu.warning)
  *(.stub)
  *(.gnu.linkonce.t*)
  *(.glue_7t)
  *(.glue_7)
  *(.jcr)
  KEEP (*(.init))
  KEEP (*(.fini))
  . = ALIGN (4) ;
  PROVIDE(__ctbp = .);
  *(.call_table_data)
  *(.call_table_text)
  . = ALIGN(0x10) ;
  __etext = . ;
 } > REGION_TEXT
 .rodata : AT(LOADADDR(.text) + SIZEOF(.text)){
  . = ALIGN(0x4) ;
  __srodata = .;
  *(.rdata)
  *(.rdata*)
  *(.rdata1)
  *(.rdata.*)
  *(.rodata)
  *(.rodata1)
  *(.rodata*)
  *(.rodata.*)
  *(.rodata.str1.4)
  KEEP (*crtbegin.o(.ctors))
  KEEP (*crtbegin?.o(.ctors))
  KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
  KEEP (*(SORT(.ctors.*)))
  KEEP (*(.ctors))
  KEEP (*crtbegin.o(.dtors))
  KEEP (*crtbegin?.o(.dtors))
  KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
  KEEP (*(SORT(.dtors.*)))
  KEEP (*(.dtors))
  . = ALIGN(0x4) ;
  __erodata = .;
 } > REGION_RODATA
 .init : AT(LOADADDR(.rodata) + SIZEOF(.rodata)){
  __sinit = .;
  . = ALIGN(0x4) ;
  *(INIT.TXT)
  *(INIT.DAT)
  . = ALIGN(0x4) ;
  __einit = .;
 } > REGION_INIT
 .data : AT(LOADADDR(.init) + SIZEOF(.init)){
  . = ALIGN(0x4) ;
  __sdata = . ;
  __data_start__ = . ;
  data_start = . ;
  *(.got.plt)
  *(.got)
  *(.gnu.linkonce.r*)
  *(.data)
  *(.data*)
  *(.data1)
  *(.data.*)
  *(.gnu.linkonce.d*)
  *(.data1)
  *(.gcc_except_table)
  *(.gcc_except_table*)
  __start_init_call = .;
  *(.initcall.init)
  __stop_init_call = .;
  __start_cmd = .;
  *(.bootloaddata.cmd)
  . = ALIGN(4) ;
  __stop_cmd = .;
  *(.sdata)
  *(.sdata.*)
  *(.gnu.linkonce.s.*)
  *(__libc_atexit)
  *(__libc_subinit)
  *(__libc_subfreeres)
  *(.note.ABI-tag)
  . = ALIGN(0x4) ;
  __edata = .;
  __data_end__ = .;
 } > REGION_DATA
 .no_init (NOLOAD) : {
    *(.stack);
    *(.no_init);
 } > REGION_BSS
 .bss : {
  . = ALIGN(0x4) ;
  __sbss = ALIGN(0x4) ;
  __bss_start__ = . ;
  *(EXCLUDE_FILE (*sysctrl.o ) .bss*)
  *(.dynsbss)
  *(.sbss)
  *(.sbss.*)
  *(.scommon)
  *(.dynbss)
  *(.bss)
  *(.bss.*)
  *(COMMON)
  . = ALIGN(0x4) ;
  __ebss = . ;
  __end = . ;
  end = . ;
  __bss_end__ = .;
 } > REGION_BSS
 ._user_heap : {
  . = ALIGN(0x4) ;
  __heap_start = .;
 } > REGION_BSS
  
 .eh_frame : ONLY_IF_RO { KEEP (*(.eh_frame)) } > REGION_BSS
 .gcc_except_table : ONLY_IF_RO { *(.gcc_except_table .gcc_except_table.*) } > REGION_BSS
 .eh_frame : ONLY_IF_RW { KEEP (*(.eh_frame)) }
 .gcc_except_table : ONLY_IF_RW { *(.gcc_except_table .gcc_except_table.*) }
 .eh_frame_hdr : { *(.eh_frame_hdr) }
 .preinit_array :
 {
  PROVIDE_HIDDEN (__preinit_array_start = .);
  KEEP (*(.preinit_array))
  PROVIDE_HIDDEN (__preinit_array_end = .);
 }
 .init_array :
 {
  PROVIDE_HIDDEN (__init_array_start = .);
  KEEP (*(SORT(.init_array.*)))
  KEEP (*(.init_array))
  PROVIDE_HIDDEN (__init_array_end = .);
 }
 .fini_array :
 {
  PROVIDE_HIDDEN (__fini_array_start = .);
  KEEP (*(.fini_array))
  KEEP (*(SORT(.fini_array.*)))
  PROVIDE_HIDDEN (__fini_array_end = .);
 }
 .junk 0 : { *(.rel*) *(.rela*) }
 .stab 0 : { *(.stab) }
 .stabstr 0 : { *(.stabstr) }
 .stab.excl 0 : { *(.stab.excl) }
 .stab.exclstr 0 : { *(.stab.exclstr) }
 .stab.index 0 : { *(.stab.index) }
 .stab.indexstr 0 : { *(.stab.indexstr) }
 .comment 0 : { *(.comment) }
 .debug 0 : { *(.debug) }
 .line 0 : { *(.line) }
 .debug_srcinfo 0 : { *(.debug_srcinfo) }
 .debug_sfnames 0 : { *(.debug_sfnames) }
 .debug_aranges 0 : { *(.debug_aranges) }
 .debug_pubnames 0 : { *(.debug_pubnames) }
 .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
 .debug_abbrev 0 : { *(.debug_abbrev) }
 .debug_line 0 : { *(.debug_line) }
 .debug_frame 0 : { *(.debug_frame) }
 .debug_str 0 : { *(.debug_str) }
 .debug_loc 0 : { *(.debug_loc) }
 .debug_macinfo 0 : { *(.debug_macinfo) }
 .debug_weaknames 0 : { *(.debug_weaknames) }
 .debug_funcnames 0 : { *(.debug_funcnames) }
 .debug_typenames 0 : { *(.debug_typenames) }
 .debug_varnames 0 : { *(.debug_varnames) }
 .debug_pubtypes 0 : { *(.debug_pubtypes) }
 .debug_ranges 0 : { *(.debug_ranges) }
 .gnu.attributes 0 : { KEEP (*(.gnu.attributes)) }
 /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}
ASSERT(__dsleep_end__ <= SRAM0_LAST_ADDR, "dsleep code size + RW size exceeds SRAM0.");