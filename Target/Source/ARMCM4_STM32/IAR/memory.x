/*-Specials-*/
define symbol __ICFEDIT_intvec_start__ = 0x08000000;
/*-Memory Regions-*/
define symbol __ICFEDIT_region_ROM_start__    = 0x08000000;
define symbol __ICFEDIT_region_ROM_end__      = 0x0800BFFF;
define symbol __ICFEDIT_region_RAM_start__    = 0x20000000;
define symbol __ICFEDIT_region_RAM_end__      = 0x20005FFF;
define symbol __ICFEDIT_region_CCMRAM_start__ = 0x10000000;
define symbol __ICFEDIT_region_CCMRAM_end__   = 0x1000FFFF;
/*-Sizes-*/
define symbol __ICFEDIT_size_cstack__   = 0x800;
define symbol __ICFEDIT_size_heap__     = 0x800;
/**** End of ICF editor section. ###ICF###*/


define memory mem with size = 4G;
define region ROM_region      = mem:[from __ICFEDIT_region_ROM_start__   to __ICFEDIT_region_ROM_end__];
define region RAM_region      = mem:[from __ICFEDIT_region_RAM_start__   to __ICFEDIT_region_RAM_end__];
define region CCMRAM_region   = mem:[from __ICFEDIT_region_CCMRAM_start__   to __ICFEDIT_region_CCMRAM_end__];

define block CSTACK    with alignment = 8, size = __ICFEDIT_size_cstack__   { };
define block HEAP      with alignment = 8, size = __ICFEDIT_size_heap__     { };

initialize by copy { readwrite };
do not initialize  { section .noinit };

place at address mem:__ICFEDIT_intvec_start__ { readonly section .intvec };

place in ROM_region   { readonly };
place in RAM_region   { readwrite,
                        block CSTACK, block HEAP };

