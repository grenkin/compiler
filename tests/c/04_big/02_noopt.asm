include a1.inc

	g$X	dd	1 dup (0)
	g$m	dd	1 dup (0)
	real_const$1	dd	6.500000e+000
	real_const$2	dd	3.500000e+000

include a2.inc

f$abs proc
	@@result	equ dword ptr ss:[ebp+10]
	@@p$x	equ dword ptr ss:[ebp+6]
	sub	esp,0
	push	ebp
	mov	ebp,esp

	push	dword ptr 0
	push	@@p$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setge	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$1
	push	@@p$x
	pop	eax
	mov	@@result,eax
	jmp	@@lbl_exit
	jmp	lbl$2
lbl$1:
	push	@@p$x
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	pop	eax
	mov	@@result,eax
	jmp	@@lbl_exit
lbl$2:
	push	@@p$x
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	push	@@p$x
	push	dword ptr 0
	push	@@p$x
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setge	cl
	push	ecx
	pop	eax
	pop	ebx
	pop	ecx
	test	eax,eax
	jz	lbl$3
	push	ebx
	jmp	lbl$4
lbl$3:
	push	ecx
lbl$4:
	pop	eax
	mov	@@result,eax
	jmp	@@lbl_exit

@@lbl_exit:
	pop	ebp
	add	esp,0
	ret	4
f$abs endp

f$main proc
	@@result	equ dword ptr ss:[ebp+78]
	@@l$i	equ dword ptr ss:[ebp+72]
	@@l$j	equ dword ptr ss:[ebp+68]
	@@l$k	equ dword ptr ss:[ebp+64]
	@@l$n	equ dword ptr ss:[ebp+60]
	@@l$p	equ dword ptr ss:[ebp+56]
	@@l$res	equ dword ptr ss:[ebp+52]
	@@l$x	equ dword ptr ss:[ebp+28]
	@@l$y	equ dword ptr ss:[ebp+4]
	sub	esp,72
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 60
	push	eax
	push	dword ptr 5
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 0
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 0
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 0
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 1
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 1
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 10
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 2
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 2
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 2
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 5
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 3
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 3
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 3
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 2
	pop	eax
	neg	eax
	push	eax
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 4
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	real_const$1
	pop	float32
	fld	float32
	fchs
	fstp	float32
	push	float32
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 5
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 5
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	dword ptr 5
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	dword ptr 7
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	0
	push	offset g$X
	push	real_const$2
	pop	ebx
	pop	eax
	mov	dword ptr [eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 52
	push	eax
	push	dword ptr 0
	fild	dword ptr ss:[esp]
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 64
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$5:
	mov	eax,ebp
	add	eax,dword ptr 56
	push	eax
	push	@@l$k
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 68
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$7:
	push	@@l$k
	push	@@l$j
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setne	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$9
	mov	eax,ebp
	add	eax,dword ptr 56
	push	eax
	push	@@l$j
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	push	@@l$k
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fsub
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	push	@@l$j
	mov	eax,ebp
	add	eax,dword ptr 28
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	push	g$X
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fsub
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fdiv
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	push	@@l$p
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fmul
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$9:
	mov	eax,ebp
	add	eax,dword ptr 68
	push	eax
	pop	eax
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	dword ptr 1
	push	@@l$n
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	push	@@l$j
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$8
	jmp	lbl$7
lbl$8:
	mov	eax,ebp
	add	eax,dword ptr 52
	push	eax
	push	@@l$p
	push	@@l$res
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fld	dword ptr ss:[esp]
	add	esp,dword ptr 4
	fadd
	sub	esp,dword ptr 4
	fstp	dword ptr ss:[esp]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 64
	push	eax
	pop	eax
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	dword ptr 1
	push	@@l$n
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	push	@@l$k
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$6
	jmp	lbl$5
lbl$6:
	push	@@l$res
	call	f$print_float

@@lbl_exit:
	pop	ebp
	add	esp,72
	ret	0
f$main endp

include b.inc