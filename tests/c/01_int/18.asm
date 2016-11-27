include a1.inc

	string_const$1	db 	0ah, "$"
	string_const$2	db 	0ah, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 85
	and	eax,dword ptr 77
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,dword ptr 85
	or	eax,dword ptr 77
	push	eax
	call	f$print_int
	push	0
	push	offset string_const$2
	call	f$print_string
	mov	eax,dword ptr 85
	xor	eax,dword ptr 77
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc