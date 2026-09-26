; Faithful instruction-level reconstruction of the masked member.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
EXTRN __AHINCR:ABS
PUBLIC _EditScrollRightColor
_EditScrollRightColor PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    cld
    mov ax, WORD PTR [bp + 12h]
    mul WORD PTR [bp + 16h]
    mov bx, ax
    mov ax, WORD PTR [bp + 14h]
    mul WORD PTR [bp + 18h]
    shl ax, 2
    add ax, 1Fh
    shr ax, 5
    shl ax, 2
    shr ax, 1
    mul bx
    mov cx, ax
    mov ax, WORD PTR [bp + 18h]
    shr ax, 1
    shr ax, 1
    sub cx, ax
    shl ax, 1
    mov bx, ds
    les di, [bp + 6]
    lds si, [bp + 6]
    add si, ax
    cmp dx, 0
    jne L_0049
    test cx, 8000h
    jne L_004E
    jmp SHORT L_0073
L_0049:
    shl dx, 1
    inc dx
    jmp SHORT L_004F
L_004E:
    inc dx
L_004F:
    lodsw
    stosw
    cmp si, 0
    jne L_005D
    mov ax, ds
    add ax, OFFSET __AHINCR
    mov ds, ax
L_005D:
    cmp di, 0
    jne L_0069
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
L_0069:
    loop L_004F
    mov cx, 8000h
    dec dx
    jne L_004F
    jmp SHORT L_0075
L_0073:
    rep movsw
L_0075:
    mov ds, bx
    mov ax, WORD PTR [bp + 14h]
    mul WORD PTR [bp + 12h]
    dec ax
    mov cx, ax
    mov dx, ax
    les di, [bp + 0Ah]
    lds si, [bp + 0Ah]
    inc si
    rep movsb
    mov ds, bx
    mov cx, dx
    les di, [bp + 0Eh]
    lds si, [bp + 0Eh]
    inc si
    inc si
    rep movsw
    mov ds, bx
    mov bx, WORD PTR [bp + 14h]
    mov dx, bx
    shl dx, 1
    mov cx, WORD PTR [bp + 12h]
    mov ax, 0FFFFh
    les di, [bp + 0Ah]
    add di, bx
    dec di
    lds si, [bp + 0Eh]
    add si, dx
    dec si
    dec si
L_00B5:
    mov es:[di], al
    mov WORD PTR [si], ax
    add di, bx
    add si, dx
    loop L_00B5
    pop es
    pop ds
    popa
    pop bp
    retf
_EditScrollRightColor ENDP
_TEXT ENDS
END
