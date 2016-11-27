include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,dword ptr 3
	sub	eax,dword ptr 5
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 9
	call	f$print_int
	push	@@l$x
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc