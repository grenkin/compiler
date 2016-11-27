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
	mov	ebx,dword ptr 1
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 2
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	call	f$swap
	push	@@l$x
	call	f$print_int
	push	@@l$y
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,8
	ret	0
f$main endp

f$swap proc
	@@result	equ dword ptr ss:[ebp+18]
	@@p$a	equ dword ptr ss:[ebp+14]
	@@p$b	equ dword ptr ss:[ebp+10]
	@@l$tmp	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@p$a
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,@@p$b
	mov	ebx,dword ptr ss:[eax]
	mov	eax,@@p$a
	mov	dword ptr ss:[eax],ebx
	mov	ebx,@@l$tmp
	mov	eax,@@p$b
	mov	dword ptr ss:[eax],ebx

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	8
f$swap endp

include b.inc