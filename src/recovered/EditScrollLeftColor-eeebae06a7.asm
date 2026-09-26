; Faithful instruction-level reconstruction of the masked member.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
EXTRN __AHINCR:ABS
PUBLIC _EditScrollLeftColor
_EditScrollLeftColor PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    std
    mov ax, WORD PTR [bp + 12h]
    mul WORD PTR [bp + 16h]
    mov bx, ax
    mov ax, WORD PTR [bp + 14h]
    mul WORD PTR [bp + 18h]
    shl ax, 2
    add ax, 1Fh
    shr ax, 5
    shl ax, 2
    mul bx
    mov bx, ax
    sub bx, 2
    jae L_002B
    dec dx
L_002B:
    les di, [bp + 6]
    add di, bx
    jae L_0039
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
L_0039:
    cmp dx, 0
    je L_0049
    mov ax, es
    mov cx, dx
L_0042:
    add ax, OFFSET __AHINCR
    loop L_0042
    mov es, ax
L_0049:
    mov ax, WORD PTR [bp + 18h]
    shr ax, 1
    sub bx, ax
    jae L_0053
    dec dx
L_0053:
    push ds
    lds si, [bp + 6]
    add si, bx
    jae L_0062
    mov ax, ds
    add ax, OFFSET __AHINCR
    mov ds, ax
L_0062:
    cmp dx, 0
    je L_0072
    mov ax, ds
    mov cx, dx
L_006B:
    add ax, OFFSET __AHINCR
    loop L_006B
    mov ds, ax
L_0072:
    shr bx, 1
    mov cx, bx
    cmp dx, 0
    je L_00A0
    inc dx
L_007C:
    lodsw
    stosw
    cmp si, -2
    jne L_008A
    mov ax, ds
    sub ax, OFFSET __AHINCR
    mov ds, ax
L_008A:
    cmp di, -2
    jne L_0096
    mov ax, es
    sub ax, OFFSET __AHINCR
    mov es, ax
L_0096:
    loop L_007C
    mov cx, 8000h
    dec dx
    jne L_007C
    jmp SHORT L_00A2
L_00A0:
    rep movsw
L_00A2:
    pop ds
    push ds
    mov ax, WORD PTR [bp + 14h]
    mul WORD PTR [bp + 12h]
    dec ax
    mov dx, ax
    les di, [bp + 0Ah]
    add di, ax
    dec ax
    lds si, [bp + 0Ah]
    add si, ax
    mov cx, ax
    rep movsb
    pop ds
    push ds
    mov cx, dx
    dec cx
    shl dx, 1
    les di, [bp + 0Eh]
    add di, dx
    dec dx
    dec dx
    lds si, [bp + 0Eh]
    add si, dx
    rep movsw
    pop ds
    mov bx, WORD PTR [bp + 14h]
    mov dx, bx
    shl dx, 1
    mov cx, WORD PTR [bp + 12h]
    mov ax, 0FFFFh
    les di, [bp + 0Ah]
    lds si, [bp + 0Eh]
L_00E5:
    mov es:[di], al
    mov WORD PTR [si], ax
    add di, bx
    add si, dx
    loop L_00E5
    pop es
    pop ds
    popa
    pop bp
    retf
_EditScrollLeftColor ENDP
_TEXT ENDS
END
