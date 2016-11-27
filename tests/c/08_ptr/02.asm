include a1.inc


include a2.inc

f$f proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$a	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,@@p$a
	push	dword ptr ss:[eax]
	call	f$print_int
	mov	ebx,dword ptr 1
	mov	eax,@@p$a
	mov	dword ptr ss:[eax],ebx
	mov	eax,@@p$a
	push	dword ptr ss:[eax]
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	4
f$f endp

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,dword ptr 3
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	call	f$f
	push	@@l$x
	call	f$print_int

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc