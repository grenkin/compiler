include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,dword ptr 1
	push	eax
	call	f$print_int
	mov	eax,dword ptr 2
	imul	eax,dword ptr 2
	push	eax
	call	f$print_int
	mov	eax,dword ptr 3
	imul	eax,dword ptr 5
	push	eax
	call	f$print_int
	mov	eax,dword ptr 3
	mov	ebx,dword ptr 5
	cdq
	idiv	ebx
	push	eax
	call	f$print_int
	mov	eax,dword ptr 5
	mov	ebx,dword ptr 3
	cdq
	idiv	ebx
	push	eax
	call	f$print_int
	mov	eax,dword ptr 1000
	mov	ebx,dword ptr 10
	cdq
	idiv	ebx
	push	eax
	call	f$print_int
	mov	eax,dword ptr 5
	mov	ebx,dword ptr 3
	cdq
	idiv	ebx
	push	edx
	call	f$print_int
	mov	eax,dword ptr 3
	mov	ebx,dword ptr 5
	cdq
	idiv	ebx
	push	edx
	call	f$print_int
	mov	eax,dword ptr 12
	mov	ebx,dword ptr 7
	cdq
	idiv	ebx
	push	edx
	call	f$print_int
	mov	eax,dword ptr 1000
	mov	ebx,dword ptr 10
	cdq
	idiv	ebx
	push	edx
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	0
f$main endp

include b.inc