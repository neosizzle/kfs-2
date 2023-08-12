global install_gdt:

install_gdt :
	; load gdt
	mov eax, [esp + 4]
	lgdt [eax]

	; set segment registers
	mov ax, 0x10 ; data segment offset
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax 

	mov ax, 0x18 ; stack segment offset
	mov ss, ax 

	; long jump
	jmp 0x08:flush_cs  ; specify cs when jumping to flush_cs, far jump


flush_cs :
	ret