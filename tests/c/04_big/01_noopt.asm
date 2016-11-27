include a1.inc

	string_const$1	db 	020h, "$"

include a2.inc

f$main proc
	@@result	equ dword ptr ss:[ebp+54]
	@@l$i	equ dword ptr ss:[ebp+48]
	@@l$n	equ dword ptr ss:[ebp+44]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,48
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 44
	push	eax
	push	dword ptr 10
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 48
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$1:
	push	@@l$i
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	@@l$i
	push	dword ptr 10
	pop	eax
	pop	ebx
	sub	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 48
	push	eax
	pop	eax
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	@@l$n
	push	@@l$i
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$2
	jmp	lbl$1
lbl$2:
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	dword ptr 0
	push	dword ptr 1
	push	@@l$n
	pop	eax
	pop	ebx
	sub	eax,ebx
	push	eax
	call	f$quicksort
	mov	eax,ebp
	add	eax,dword ptr 48
	push	eax
	push	dword ptr 0
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$3:
	push	@@l$i
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 48
	push	eax
	pop	eax
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	@@l$n
	push	@@l$i
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$4
	jmp	lbl$3
lbl$4:

@@lbl_exit:
	pop	ebp
	add	esp,48
	ret	0
f$main endp

f$partition proc
	@@result	equ dword ptr ss:[ebp+30]
	@@p$a	equ dword ptr ss:[ebp+26]
	@@p$l	equ dword ptr ss:[ebp+22]
	@@p$r	equ dword ptr ss:[ebp+18]
	@@l$i	equ dword ptr ss:[ebp+12]
	@@l$j	equ dword ptr ss:[ebp+8]
	@@l$x	equ dword ptr ss:[ebp+4]
	sub	esp,12
	push	ebp
	mov	ebp,esp

	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	push	@@p$l
	push	@@p$a
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
	add	eax,dword ptr 12
	push	eax
	push	dword ptr 1
	push	@@p$l
	pop	eax
	pop	ebx
	sub	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	push	dword ptr 1
	push	@@p$r
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
lbl$5:
	push	dword ptr 1
	pop	eax
	test	eax,eax
	jz	lbl$6
lbl$7:
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	pop	eax
	push	dword ptr ss:[eax]
	dec	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	@@l$x
	push	@@l$j
	push	@@p$a
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$8
	jmp	lbl$7
lbl$8:
lbl$9:
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	pop	eax
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	push	@@l$x
	push	@@l$i
	push	@@p$a
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$10
	jmp	lbl$9
lbl$10:
	push	@@l$j
	push	@@l$i
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$11
	push	@@l$i
	push	@@p$a
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	push	@@l$j
	push	@@p$a
	pop	eax
	pop	ebx
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	call	f$swapint
	jmp	lbl$12
lbl$11:
	push	@@l$j
	pop	eax
	mov	@@result,eax
	jmp	@@lbl_exit
lbl$12:
	jmp	lbl$5
lbl$6:

@@lbl_exit:
	pop	ebp
	add	esp,12
	ret	12
f$partition endp

f$quicksort proc
	@@result	equ dword ptr ss:[ebp+22]
	@@p$a	equ dword ptr ss:[ebp+18]
	@@p$l	equ dword ptr ss:[ebp+14]
	@@p$r	equ dword ptr ss:[ebp+10]
	@@l$q	equ dword ptr ss:[ebp+4]
	sub	esp,4
	push	ebp
	mov	ebp,esp

	push	@@p$r
	push	@@p$l
	pop	eax
	pop	ebx
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	push	ecx
	pop	eax
	test	eax,eax
	jz	lbl$13
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	sub	esp,dword ptr 4
	push	@@p$a
	push	@@p$l
	push	@@p$r
	call	f$partition
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@p$a
	push	@@p$l
	push	@@l$q
	call	f$quicksort
	push	@@p$a
	push	dword ptr 1
	push	@@l$q
	pop	eax
	pop	ebx
	add	eax,ebx
	push	eax
	push	@@p$r
	call	f$quicksort
lbl$13:

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	12
f$quicksort endp

f$swapint proc
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
	push	@@p$a
	pop	eax
	push	dword ptr ss:[eax]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@p$a
	push	@@p$b
	pop	eax
	push	dword ptr ss:[eax]
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4
	push	@@p$b
	push	@@l$tmp
	pop	ebx
	pop	eax
	mov	dword ptr ss:[eax],ebx
	push	ebx
	add	esp,dword ptr 4

@@lbl_exit:
	pop	ebp
	add	esp,4
	ret	8
f$swapint endp

include b.inc