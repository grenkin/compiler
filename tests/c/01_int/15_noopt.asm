include a1.inc

	string_const$1	db 	0ah, "$"

include a2.inc

f$compare proc
	@@result	equ dword ptr ss:[ebp+14]
	@@p$a	equ dword ptr ss:[ebp+10]
	@@p$b	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	@@p$b
	push	@@p$a
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	call	f$print_int
	push	@@p$b
	push	@@p$a
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setle	cl
	push	ecx
	call	f$print_int
	push	@@p$b
	push	@@p$a
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	push	ecx
	call	f$print_int
	push	@@p$b
	push	@@p$a
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setge	cl
	push	ecx
	call	f$print_int
	push	@@p$b
	push	@@p$a
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	sete	cl
	push	ecx
	call	f$print_int
	push	@@p$b
	push	@@p$a
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setne	cl
	push	ecx
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	8
f$compare endp

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 1
	push	dword ptr 1
	call	f$compare
	push	dword ptr 1
	push	dword ptr 2
	call	f$compare
	push	dword ptr 2
	push	dword ptr 1
	call	f$compare
	push	dword ptr 1
	push	dword ptr 1
	pop	eax
	neg	eax
	push	eax
	call	f$compare
	push	dword ptr 1
	pop	eax
	neg	eax
	push	eax
	push	dword ptr 1
	call	f$compare
	push	dword ptr 1
	pop	eax
	neg	eax
	push	eax
	push	dword ptr 1
	pop	eax
	neg	eax
	push	eax
	call	f$compare
	push	dword ptr 1
	pop	eax
	neg	eax
	push	eax
	push	dword ptr 2
	pop	eax
	neg	eax
	push	eax
	call	f$compare
	push	dword ptr 2
	pop	eax
	neg	eax
	push	eax
	push	dword ptr 1
	pop	eax
	neg	eax
	push	eax
	call	f$compare

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc