include a1.inc

	string_const$1	db 	074h, 065h, 073h, 074h, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	0
	push	offset string_const$1
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc