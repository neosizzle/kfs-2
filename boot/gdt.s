global init_gdt
init_gdt:
	lgdt [ gdt_descriptor ] ; call to bios
	mov ax, DATA_SEG ; 5. update the segment registers
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

	mov ax, STACK_SEG ; 5. update the stack segment
	mov ss, ax

	jmp CODE_SEG:flush_cs  ; specify cs when jumping to flush_cs, far jump
	
	ret

; Define some handy constants for the GDT segment descriptor offsets , which
; are what segment registers must contain when in protected mode. For example ,
; when we set DS = 0 x10 in PM , the CPU knows that we mean it to use the
; segment described at offset 0 x10 ( i.e. 16 bytes ) in our GDT , which in our
; case is the DATA segment (0 x0 -> NULL ; 0x08 -> CODE ; 0 x10 -> DATA )
CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start
STACK_SEG equ gdt_stack - gdt_start


flush_cs:

