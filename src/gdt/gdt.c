#include "gdt.h"

extern void install_gdt(uint32_t ptr);

gdt_entry gdt_entries[GDT_ENTRIES];
gdt_table *_gdt_table = (gdt_table *)GDT_ADDR;

void register_gdt(void)
{
    _gdt_table->base = (uint32_t) &gdt_entries;
    _gdt_table->limit = (GDT_ENTRIES * sizeof(gdt_entries)) - 1;
    // __asm__ __volatile__("lgdtl (%0)" : : "r" (&gdt_entries));
    install_gdt((uint32_t)_gdt_table);
}

void create_gdt_entry(int idx, uint32_t seg_limit, uint32_t base, uint8_t access, uint8_t attribs_high)
{
    gdt_entry new_entry;
    
    new_entry.seg_limit_low = low_16(seg_limit);
    new_entry.base_low = low_16(base);
    new_entry.base_mid = low_8(high_16(base));
    new_entry.access = access;
    new_entry.attribs_high = (seg_limit >> 16) & 0x0F;
    new_entry.attribs_high |= ((attribs_high << 4) & 0xF0);
    new_entry.base_high = high_8(high_16(base));

    gdt_entries[idx] = new_entry;
}

void init_gdt(void)
{
    // create gdt entries
    create_gdt_entry(0, 0, 0, 0, 0);// null entry
    create_gdt_entry(1, SS_LIMIT_MAX, KERNEL_CODE_BASE, SS_ACCESS_KERNEL_CODE, SS_ATTRIB_KERNEL_CODE);// kcode
    create_gdt_entry(2, SS_LIMIT_MAX, KERNEL_DATA_BASE, SS_ACCESS_KERNEL_DATA, SS_ATTRIB_KERNEL_DATA);// kdata
    create_gdt_entry(3, SS_LIMIT_MAX, KERNEL_STACK_BASE, SS_ACCESS_KERNEL_STACK, SS_ATTRIB_KERNEL_STACK);// kstack
    create_gdt_entry(4, SS_LIMIT_MAX, USER_CODE_BASE, SS_ACCESS_USER_CODE, SS_ATTRIB_USER_CODE);// ucode
    create_gdt_entry(5, SS_LIMIT_MAX, USER_DATA_BASE, SS_ACCESS_USER_DATA, SS_ATTRIB_USER_DATA);// udata
    create_gdt_entry(6, SS_LIMIT_MAX, USER_STACK_BASE, SS_ACCESS_USER_STACK, SS_ATTRIB_USER_STACK);// ustack

    // register gdt
    register_gdt();

}