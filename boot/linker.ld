OUTPUT_FORMAT(elf32-i386)
ENTRY(_entry)
SECTIONS
{
	. = 1M;  /* For physical address access */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}
	.data : { *(.data) }
	.bss : { *(.bss) }
}