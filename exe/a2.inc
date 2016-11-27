.code

f$print_string proc
	@@p$s equ [ebp+6]
	push	ebp
	mov	ebp,esp

	mov	ax,0900h
	mov	dx,@@p$s
	int	21h

	mov	esp,ebp
	pop	ebp
	ret	4
f$print_string endp

f$print_int proc
	@@p$num equ dword ptr [ebp+6]
	push	ebp
	mov	ebp,esp
	push	eax
	push	ebx
	push	ecx
	push	edx
	
	mov	ecx,@@p$num
	cmp	ecx,0
	jge	@@lbl1
	mov	dl,"-"
	mov	ah,02h
	int	21h
	neg	ecx
@@lbl1:
	mov	eax,ecx
	xor	ecx,ecx
	mov	ebx,10
@@lbl2:	xor	edx,edx
	idiv	ebx
	push	edx
	inc	ecx
	test	eax,eax
	jnz	@@lbl2
@@lbl3:	pop	eax
	;or	al,30h
	
	;int	29h
	mov	ah,02h
	mov	dl,al
        add     dl,30h
	int	21h
	loop	@@lbl3

	pop	edx
	pop	ecx
	pop	ebx
	pop	eax
	mov	esp,ebp
	pop	ebp
	ret	4
f$print_int endp

f$print_float proc
	@@p$num equ dword ptr [ebp+6]
	@@l$1 equ word ptr [ebp-14]
	@@l$2 equ word ptr [ebp-16]
	@@l$3 equ [ebp-16]
        push    ebp
        mov     ebp,esp
        push    eax
        push    ecx
        push    edx

	fld	@@p$num

        push    10
        push    0
        ftst
        fstsw   ax
        sahf
        jnc     @@of1
        mov     ah,02h
        mov     dl,'-'
        int     21h
        fchs
@@of1:  fld1
        fld     st(1)
        fprem
        fsub    st(2),st
        fxch    st(2)
        xor     ecx,ecx
@@of2:  fidiv   @@l$1
        fxch    st(1)
        fld     st(1)
        fprem
        fsub    st(2),st
        fimul   @@l$1
        fistp   @@l$2
        inc     ecx
        push    @@l$2
        fxch    st(1)
        ftst
        fstsw   ax
        sahf
        jnz     short @@of2
        mov     ah,02h
@@of3:  pop     dx
        add     dl,30h
        int     21h
        loop    @@of3
        fstp    st(0)
        fxch    st(1)
        ftst
        fstsw   ax
        sahf
        jz      short @@of5
        mov     ah,02h
        mov     dl,'.'
        int     21h
        mov     ecx,6
@@of4:  fimul   @@l$1
        fxch    st(1)
        fld     st(1)
        fprem
        fsub    st(2),st
        fxch    st(2)
        fistp   @@l$2
        mov     ah,02h
        mov     dl,@@l$3
        add     dl,30h
        int     21h
        fxch    st(1)
        ftst
        fstsw   ax
        sahf
        loopnz  @@of4
@@of5:  fstp    st(0)
        fstp    st(0)

        pop     edx
        pop     ecx
        pop     eax
        mov     esp,ebp
        pop	ebp
        ret     4
f$print_float endp
