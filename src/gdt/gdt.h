#ifndef __GDT__H__
#define __GDT__H__
#include "types.h"

/**
 * https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
 * Access flags for kernel code is 1010 1 00 1
 * '' data is 0010 1 00 1
 * 
 * for the user, the DPL is set to 11 instead
*/
#define SS_ACCESS_KERNEL_CODE 0x9A
#define SS_ACCESS_KERNEL_DATA 0x92
#define SS_ACCESS_KERNEL_STACK 0x92
#define SS_ACCESS_USER_CODE 0xFA
#define SS_ACCESS_USER_DATA 0xF2
#define SS_ACCESS_USER_STACK 0xF2

/**
 * Set to 0xCF is D/B needs to be 0
 * Attribute flags for kernel 
 * 
 * G = 0, D/B = 0 or 1?, L , AVL = 0, LIMIT = 1111
*/
#define SS_ATTRIB_KERNEL_CODE 0xC
#define SS_ATTRIB_KERNEL_DATA 0xC
#define SS_ATTRIB_KERNEL_STACK 0xC
#define SS_ATTRIB_USER_CODE 0xC
#define SS_ATTRIB_USER_DATA 0xC
#define SS_ATTRIB_USER_STACK 0xC

#define SS_LIMIT_MAX 0xFFFFF
#define GDT_ADDR 0x00000800
#define GDT_ENTRIES 7

#define KERNEL_CODE_BASE 0x00000000
#define KERNEL_DATA_BASE 0x02000000
#define KERNEL_STACK_BASE 0x04000000
#define USER_CODE_BASE 0x06000000
#define USER_DATA_BASE 0x08000000
#define USER_STACK_BASE 0x0A000000

/**
 * Definition of every gdt entry (Segment descriptor)
*/
typedef struct __attribute__((packed)) gdt_entry {
	uint16_t seg_limit_low;// segment limit low (16 bits)
	uint16_t base_low;// base address low (16 bits)
	uint8_t base_mid;// base address mid (8 bits)
	uint8_t access;// types + attributes_low (8 bits)
	uint8_t attribs_high; // seg limit high + attributes high (8 bits)
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
extern gdt_entry gdt_entries[GDT_ENTRIES];
extern gdt_table *_gdt_table;

void init_gdt(void);

#endif  //!__GDT__H__