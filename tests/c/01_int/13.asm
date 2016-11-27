include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 4
	sub	eax,dword ptr 5
	imul	eax,dword ptr 6
	push	eax
	mov	eax,dword ptr 1
	add	eax,dword ptr 2
	imul	eax,dword ptr 3
	pop	ebx
	sub	eax,ebx
	push	eax
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc