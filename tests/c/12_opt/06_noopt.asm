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
	pop	eax
	push	dword ptr ss:[eax]
	dec	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	dword ptr 2
	add	esp,dword ptr 4

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc