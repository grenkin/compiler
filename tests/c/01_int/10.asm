include a1.inc


include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+18]
	@@l$a	equ dword ptr ss:[ebp+12]
	@@l$b	equ dword ptr ss:[ebp+8]
	@@l$c	equ dword ptr ss:[ebp+4]
	sub	esp,12
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 12
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	mov	ebx,dword ptr 1
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 2
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	mov	eax,@@l$a
	inc	eax
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$a
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	mov	eax,@@l$b
	add	eax,@@l$c
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$b
	call	f$print_int
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,dword ptr 5
	add	eax,@@l$c
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$c
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,12
	ret	0
f$main endp

include b.inc