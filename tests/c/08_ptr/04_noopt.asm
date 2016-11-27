include a1.inc


include a2.inc

f$f proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$a	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	push	@@p$a
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 5
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	4
f$f endp

f$main proc
	@@result	equ dword ptr ss:[ebp+18]
	@@l$a	equ dword ptr ss:[ebp+4]
	sub	esp,12
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	call	f$f
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,12
	ret	0
f$main endp

include b.inc