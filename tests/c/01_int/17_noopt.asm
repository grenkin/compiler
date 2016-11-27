include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	push	dword ptr 5
	pop	eax
	pop	ebx
	and	eax,ebx
	push	eax
	call	f$print_int
	push	dword ptr 5
	push	dword ptr 0
	pop	eax
	pop	ebx
	and	eax,ebx
	push	eax
	call	f$print_int
	push	dword ptr 0
	push	dword ptr 5
	pop	eax
	pop	ebx
	or	eax,ebx
	push	eax
	call	f$print_int
	push	dword ptr 5
	push	dword ptr 0
	pop	eax
	pop	ebx
	or	eax,ebx
	push	eax
	call	f$print_int
	push	dword ptr 0
	push	dword ptr 5
	pop	eax
	pop	ebx
	xor	eax,ebx
	push	eax
	call	f$print_int
	push	dword ptr 5
	push	dword ptr 0
	pop	eax
	pop	ebx
	xor	eax,ebx
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc