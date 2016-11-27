include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 4
	push	dword ptr 1
	pop	eax
	pop	ebx
	mov	cl,bl
	shl	eax,cl
	push	eax
	call	f$print_int
	push	dword ptr 2
	push	dword ptr 16
	pop	eax
	pop	ebx
	mov	cl,bl
	shr	eax,cl
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc