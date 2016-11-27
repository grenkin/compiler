include a1.inc


include a2.inc

f$f proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$x	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,@@p$x
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	4
f$f endp

f$main proc
	@@result	equ dword ptr ss:[ebp+26]
	@@l$a	equ dword ptr ss:[ebp+4]
	sub	esp,20
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 3
	mov	dword ptr ss:[eax],ebx
	sub	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	call	f$f
	add	esp,dword ptr 4

@@lbl_exit:
	pop	ebp
	add	esp,20
	ret	0
f$main endp

include b.inc