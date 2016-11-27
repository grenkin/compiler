include a1.inc

	real_const$1	dd	1.000000e+000

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,real_const$1
	mov	dword ptr ss:[eax],ebx
	push	ebx
	call	f$print_float
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fiadd	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_float
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fiadd	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_float
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fiadd	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_float
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fiadd	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_float
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fiadd	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_float
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fiadd	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_float
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 1
	push	@@l$x
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fiadd	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	@@l$x
	call	f$print_float

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc