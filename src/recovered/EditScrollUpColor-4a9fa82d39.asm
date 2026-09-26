; Faithful instruction-level reconstruction of the masked member.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
EXTRN __AHINCR:ABS
PUBLIC _EditScrollUpColor
_EditScrollUpColor PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    cld
    mov ax, WORD PTR [bp + 12h]
    dec ax
    mul WORD PTR [bp + 16h]
    mov bx, ax
    mov ax, WORD PTR [bp + 14h]
    mul WORD PTR [bp + 18h]
    shl ax, 2
    add ax, 1Fh
    shr ax, 5
    shl ax, 2
    mov cx, ax
    mul bx
    mov bx, dx
    xchg cx, ax
    mul WORD PTR [bp + 16h]
    mov dx, bx
    shr cx, 1
    mov bx, ds
    les di, [bp + 6]
    lds si, [bp + 6]
    add si, ax
    cmp dx, 0
    jne L_0049
    mov dx, cx
    shl dx, 1
    add ax, dx
    jae L_006E
    xor dx, dx
L_0049:
    inc dx
L_004A:
    lodsw
    stosw
    cmp si, 0
    jne L_0058
    mov ax, ds
    add ax, OFFSET __AHINCR
    mov ds, ax
L_0058:
    cmp di, 0
    jne L_0064
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
L_0064:
    loop L_004A
    mov cx, 8000h
    dec dx
    jne L_004A
    jmp SHORT L_0070
L_006E:
    rep movsw
L_0070:
    std
    mov ds, bx
    mov ax, WORD PTR [bp + 12h]
    dec ax
    mul WORD PTR [bp + 14h]
    mov cx, ax
    les di, [bp + 0Ah]
    add di, cx
    add di, WORD PTR [bp + 14h]
    dec di
    lds si, [bp + 0Ah]
    add si, cx
    dec si
    rep movsb
    mov ds, bx
    mov cx, ax
    les di, [bp + 0Eh]
    add di, cx
    add di, WORD PTR [bp + 14h]
    dec di
    add di, cx
    add di, WORD PTR [bp + 14h]
    dec di
    lds si, [bp + 0Eh]
    add si, cx
    dec si
    add si, cx
    dec si
    rep movsw
    cld
    mov ds, bx
    mov cx, WORD PTR [bp + 14h]
    mov ax, 0FFFFh
    les di, [bp + 0Ah]
    rep stosb
    mov cx, WORD PTR [bp + 14h]
    les di, [bp + 0Eh]
    rep stosw
    pop es
    pop ds
    popa
    pop bp
    retf
_EditScrollUpColor ENDP
_TEXT ENDS
END
