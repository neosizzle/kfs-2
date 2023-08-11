#ifndef __GDT__H__
#define __GDT__H__

#define GDT_ADDR  0x00000800

/**
 * Definition of every gdt entry (Segment descriptor)
*/
typedef struct __attribute__((packed)) gdt_entry {

} gdt_entry;

/**
 * The GDT table itself
*/
typedef struct __attribute__((packed)) gdt_table {
	// uint16_t limit; // how many entries this table has?
	// uint32_t base; // address of the first entry
} gdt_table;

// array of gdt entries
extern gdt_entry gdt_entries[7];
extern gdt_table _gdt_table;

void init_gdt(void);

#endif  //!__GDT__H__