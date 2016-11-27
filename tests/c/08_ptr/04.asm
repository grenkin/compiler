include a1.inc


include a2.inc

f$f proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$a	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,@@p$a
	mov	ebx,dword ptr 0
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr 5
	mov	dword ptr ss:[eax],ebx

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
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 0
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