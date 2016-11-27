include a1.inc

	real_const$1	dd	1.500000e+000
	real_const$2	dd	2.700000e+000
	real_const$3	dd	1.500000e+000
	real_const$4	dd	2.700000e+000
	string_const$1	db 	0ah, "$"
	string_const$2	db 	0ah, "$"
	string_const$3	db 	0ah, "$"
	string_const$4	db 	0ah, "$"

include a2.inc

f$f proc
	@@result	equ dword ptr ss:[ebp+14]
	@@p$p1	equ dword ptr ss:[ebp+10]
	@@p$p2	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	mov	eax,@@p$p1
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_float
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,@@p$p1
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	call	f$print_float
	push	0
	push	offset string_const$2
	call	f$print_string
	mov	eax,@@p$p2
	add	eax,dword ptr 0
	push	dword ptr ss:[eax]
	call	f$print_float
	push	0
	push	offset string_const$3
	call	f$print_string
	mov	eax,@@p$p2
	add	eax,dword ptr 4
	push	dword ptr ss:[eax]
	call	f$print_float
	push	0
	push	offset string_const$4
	call	f$print_string

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	8
f$f endp

f$main proc
	@@result	equ dword ptr ss:[ebp+22]
	@@l$p	equ dword ptr ss:[ebp+12]
	@@l$q	equ dword ptr ss:[ebp+4]
	sub	esp,16
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 12
	add	eax,dword ptr 0
	mov	ebx,real_const$1
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 12
	add	eax,dword ptr 4
	mov	ebx,real_const$2
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 0
	push	eax
	push	real_const$3
	pop	float32
	fld	float32
	fchs
	fstp	float32
	mov	ebx,float32
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 4
	add	eax,dword ptr 4
	push	eax
	push	real_const$4
	pop	float32
	fld	float32
	fchs
	fstp	float32
	mov	ebx,float32
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	call	f$f

@@lbl_exit:
	pop	ebp
	add	esp,16
	ret	0
f$main endp

include b.inc