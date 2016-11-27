include a1.inc


include a2.inc

f$fact proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$n	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	push	@@p$n
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$1
	push	dword ptr 1
	pop	eax
	mov	@@result,eax
	jmp	@@lbl_exit
	jmp	lbl$2
lbl$1:
	sub	esp,dword ptr 4
	push	dword ptr 1
	push	@@p$n
	pop	eax
	pop	ebx
	sub	eax,ebx
	push	eax
	call	f$fact
	push	@@p$n
	pop	eax
	pop	ebx
	imul	eax,ebx
	push	eax
	pop	eax
	mov	@@result,eax
	jmp	@@lbl_exit
lbl$2:

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	4
f$fact endp

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	sub	esp,dword ptr 4
	push	dword ptr 5
	call	f$fact
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc