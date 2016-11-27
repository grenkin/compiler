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
	mov	ebx,dword ptr 10
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 48
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$1:
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	mov	eax,dword ptr 10
	sub	eax,@@l$i
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 48
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	mov	eax,@@l$i
	mov	ebx,@@l$n
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$2
	jmp	lbl$1
lbl$2:
	mov	eax,ebp
	add	eax,dword ptr 4
	push	eax
	mov	eax,@@l$n
	dec	eax
	push	dword ptr 0
	push	eax
	call	f$quicksort
	mov	eax,ebp
	add	eax,dword ptr 48
	mov	ebx,dword ptr 0
	mov	dword ptr ss:[eax],ebx
lbl$3:
	mov	eax,ebp
	add	eax,dword ptr 4
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	dword ptr ss:[eax]
	call	f$print_int
	push	0
	push	offset string_const$1
	call	f$print_string
	mov	eax,ebp
	add	eax,dword ptr 48
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	mov	eax,@@l$i
	mov	ebx,@@l$n
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
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
	mov	eax,@@p$a
	mov	ebx,@@p$l
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	ebx,dword ptr ss:[eax]
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 12
	push	eax
	mov	eax,@@p$l
	dec	eax
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
	mov	eax,ebp
	add	eax,dword ptr 8
	push	eax
	mov	eax,@@p$r
	inc	eax
	mov	ebx,eax
	pop	eax
	mov	dword ptr ss:[eax],ebx
lbl$5:
	mov	eax,dword ptr 1
	test	eax,eax
	jz	lbl$6
lbl$7:
	mov	eax,ebp
	add	eax,dword ptr 8
	push	dword ptr ss:[eax]
	dec	dword ptr ss:[eax]
	add	esp,dword ptr 4
	mov	eax,@@p$a
	mov	ebx,@@l$j
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	eax,dword ptr ss:[eax]
	mov	ebx,@@l$x
	xor	ecx,ecx
	cmp	eax,ebx
	setg	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$8
	jmp	lbl$7
lbl$8:
lbl$9:
	mov	eax,ebp
	add	eax,dword ptr 12
	push	dword ptr ss:[eax]
	inc	dword ptr ss:[eax]
	add	esp,dword ptr 4
	mov	eax,@@p$a
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	mov	eax,dword ptr ss:[eax]
	mov	ebx,@@l$x
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$10
	jmp	lbl$9
lbl$10:
	mov	eax,@@l$i
	mov	ebx,@@l$j
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
	test	eax,eax
	jz	lbl$11
	mov	eax,@@p$a
	mov	ebx,@@l$i
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	mov	eax,@@p$a
	mov	ebx,@@l$j
	imul	ebx,dword ptr 4
	add	eax,ebx
	push	eax
	call	f$swapint
	jmp	lbl$12
lbl$11:
	mov	eax,@@l$j
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

	mov	eax,@@p$l
	mov	ebx,@@p$r
	xor	ecx,ecx
	cmp	eax,ebx
	setl	cl
	mov	eax,ecx
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
	push	@@p$a
	push	@@p$l
	push	@@l$q
	call	f$quicksort
	mov	eax,@@l$q
	inc	eax
	push	@@p$a
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
f$swapint endp

include b.inc