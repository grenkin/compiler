include a1.inc


include a2.inc

f$fact proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$n	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,@@p$n
	mov	ebx,dword ptr 0
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$1
	mov	eax,dword ptr 1
	mov	@@result,eax
	jmp	@@lbl_exit
	jmp	lbl$2
lbl$1:
	sub	esp,dword ptr 4
	mov	eax,@@p$n
	dec	eax
	push	eax
	call	f$fact
	mov	eax,@@p$n
	pop	ebx
	imul	eax,ebx
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