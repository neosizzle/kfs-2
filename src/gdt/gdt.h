#ifndef __GDT__H__
#define __GDT__H__
#include "types.h"

#define SS_ACCESS_KERNEL_CODE
#define SS_ACCESS_KERNEL_DATA
#define SS_ACCESS_KERNEL_STACK
#define SS_ACCESS_USER_CODE
#define SS_ACCESS_USER_DATA
#define SS_ACCESS_USER_STACK

#define GDT_ADDR  0x00000800


/**
 * Definition of every gdt entry (Segment descriptor)
*/
typedef struct __attribute__((packed)) gdt_entry {
	uint16_t seg_limit;// segment limit (16 bits)
	uint16_t base_low;// base address low (16 bits)
	uint8_t base_mid;// base address mid (8 bits)
	uint8_t access;// types + attributes_low (8 bits)
	uint8_t attribs_high; // seg limit + attributes high (8 bits)
	uint8_t base_high;// base high (8 bits)
} gdt_entry;

/**
 * The GDT table itself
*/
typedef struct __attribute__((packed)) gdt_table {
	uint16_t limit; // how many entries this table has?
	uint32_t base; // address of the first entry
} gdt_table;

// array of gdt entries
extern gdt_entry gdt_entries[7];
extern gdt_table _gdt_table;

void init_gdt(void);

#endif  //!__GDT__H__