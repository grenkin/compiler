include a1.inc

	real_const$1	dd	3.141593e+000

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+10]
	@@l$pi	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,real_const$1
	mov	dword ptr ss:[eax],ebx
	push	dword ptr 1000000
	push	@@l$pi
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fimul	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	call	f$print_float

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	0
f$main endp

include b.inc