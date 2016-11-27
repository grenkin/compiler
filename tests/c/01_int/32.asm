include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+14]
	@@l$x	equ dword ptr ss:[ebp+8]
	@@l$y	equ dword ptr ss:[ebp+4]
	sub	esp,8
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	mov	eax,@@l$x
	test	eax,eax
	jnz	lbl$1
	mov	eax,dword ptr 3
	test	eax,eax
	jnz	lbl$1
	push	dword ptr 0
	jmp	lbl$2
lbl$1:
	push	dword ptr 1
lbl$2:
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_int
	mov	eax,dword ptr 0
	test	eax,eax
	jnz	lbl$3
	mov	eax,dword ptr 0
	test	eax,eax
	jnz	lbl$3
	push	dword ptr 0
	jmp	lbl$4
lbl$3:
	push	dword ptr 1
lbl$4:
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,8
	ret	0
f$main endp

include b.inc