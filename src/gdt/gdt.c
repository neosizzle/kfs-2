#include "gdt.h"

gdt_entry gdt_entries[7];
gdt_table _gdt_table;

void register_idt(void)
{
    _gdt_table.base = (uint32_t) &gdt_entries;
    _gdt_table.limit = (uint16_t) (7 * sizeof(gdt_entries) - 1);
    __asm__ __volatile__("lgdtl (%0)" : : "r" (&gdt_entries));
}

void init_gdt(void)
{
	
}