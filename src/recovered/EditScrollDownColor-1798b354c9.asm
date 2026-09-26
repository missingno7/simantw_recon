; Faithful instruction-level reconstruction of the masked member.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
EXTRN __AHINCR:ABS
PUBLIC _EditScrollDownColor
_EditScrollDownColor PROC FAR
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
    mov cx, ax
    mul WORD PTR [bp + 16h]
    push ax
    mov ax, cx
    mul bx
    mov bx, ax
    sub bx, 2
    jae L_0033
    dec dx
L_0033:
    les di, [bp + 6]
    add di, bx
    jae L_0041
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
L_0041:
    cmp dx, 0
    je L_0051
    mov ax, es
    mov cx, dx
L_004A:
    add ax, OFFSET __AHINCR
    loop L_004A
    mov es, ax
L_0051:
    pop ax
    sub bx, ax
    jae L_0057
    dec dx
L_0057:
    push ds
    lds si, [bp + 6]
    add si, bx
    jae L_0066
    mov ax, ds
    add ax, OFFSET __AHINCR
    mov ds, ax
L_0066:
    cmp dx, 0
    je L_0076
    mov ax, ds
    mov cx, dx
L_006F:
    add ax, OFFSET __AHINCR
    loop L_006F
    mov ds, ax
L_0076:
    shr bx, 1
    mov cx, bx
    cmp dx, 0
    jne L_0087
    mov ax, es
    mov bx, ds
    cmp ax, bx
    je L_00AC
L_0087:
    inc dx
L_0088:
    lodsw
    stosw
    cmp si, -2
    jne L_0096
    mov ax, ds
    sub ax, OFFSET __AHINCR
    mov ds, ax
L_0096:
    cmp di, -2
    jne L_00A2
    mov ax, es
    sub ax, OFFSET __AHINCR
    mov es, ax
L_00A2:
    loop L_0088
    mov cx, 8000h
    dec dx
    jne L_0088
    jmp SHORT L_00AE
L_00AC:
    rep movsw
L_00AE:
    cld
    pop ds
    push ds
    mov ax, WORD PTR [bp + 12h]
    dec ax
    mul WORD PTR [bp + 14h]
    mov cx, ax
    mov dx, WORD PTR [bp + 14h]
    les di, [bp + 0Ah]
    lds si, [bp + 0Ah]
    add si, dx
    rep movsb
    pop ds
    push ds
    mov cx, ax
    les di, [bp + 0Eh]
    lds si, [bp + 0Eh]
    add si, dx
    add si, dx
    rep movsw
    pop ds
    mov bx, ax
    mov ax, 0FFFFh
    les di, [bp + 0Ah]
    add di, bx
    mov cx, dx
    rep stosb
    les di, [bp + 0Eh]
    add di, bx
    add di, bx
    mov cx, dx
    rep stosw
    pop es
    pop ds
    popa
    pop bp
    retf
_EditScrollDownColor ENDP
_TEXT ENDS
END
