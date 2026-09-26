; Move overlapping text rows down and fill the exposed area with 0FFFFh words.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _EditMultipleScrollDownAsm
_EditMultipleScrollDownAsm PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    cld
    mov bx, ds
    les di, [bp + 6]
    mov ax, WORD PTR [bp+0Eh]
    mul WORD PTR [bp+10h]
    mov ax, WORD PTR [bp+0Eh]
    sub ax, WORD PTR [bp+14h]
    mul WORD PTR [bp+10h]
    test WORD PTR [bp+16h], 1
    je SHORT L0027
    add ax, WORD PTR [bp+12h]
    jmp SHORT L002A
L0027:
    sub ax, WORD PTR [bp+12h]
L002A:
    mov cx, ax
    mov dx, ax
    lds si, [bp + 6]
    add si, cx
    dec si
    rep movsb
    mov ds, bx
    mov ax, WORD PTR [bp+0Eh]
    mul WORD PTR [bp+10h]
    dec ax
    shl ax, 1
    les di, [bp+0Ah]
    add di, ax
    lds si, [bp+0Ah]
    add si, dx
    dec si
    add si, dx
    dec si
    mov ds, bx
    cmp WORD PTR [bp+14h], 0
    jmp SHORT L0086
    mov cx, ax
    les di, [bp + 6]
    mov ax, WORD PTR [bp+0Eh]
    mul WORD PTR [bp+10h]
    shl ax, 1
    dec ax
    dec ax
    add di, ax
    lds si, [bp + 6]
    add si, cx
    dec si
    add si, cx
    dec si
    rep movsw
    cld
    mov ds, bx
    mov ax, WORD PTR [bp+10h]
    mul WORD PTR [bp+14h]
    mov cx, ax
    les di, [bp+0Ah]
    mov ax, 0FFFFh
    rep stosw
L0086:
    cmp WORD PTR [bp+12h], 0
    je SHORT L00DF
    test WORD PTR [bp+16h], 1
    je SHORT L00C1
    mov dx, WORD PTR [bp+10h]
    shl dx, 1
    mov cx, WORD PTR [bp+0Eh]
    les di, [bp+0Ah]
    add di, WORD PTR [bp+10h]
    add di, WORD PTR [bp+10h]
    sub di, WORD PTR [bp+12h]
    sub di, WORD PTR [bp+12h]
    dec di
    dec di
    mov ax, 0FFFFh
L00AF:
    mov bx, WORD PTR [bp+12h]
    shl bx, 1
L00B4:
    mov WORD PTR es:[bx + di], ax
    dec bx
    dec bx
    jne SHORT L00B4
    add di, dx
    loop SHORT L00AF
    jmp SHORT L00DF
L00C1:
    mov dx, WORD PTR [bp+10h]
    shl dx, 1
    mov cx, WORD PTR [bp+0Eh]
    mov ax, 0FFFFh
    les di, [bp+0Ah]
L00CF:
    mov bx, WORD PTR [bp+12h]
    shl bx, 1
L00D4:
    mov WORD PTR es:[bx + di], ax
    dec bx
    dec bx
    jne SHORT L00D4
    add di, dx
    loop SHORT L00CF
L00DF:
    pop es
    pop ds
    popa
    pop bp
    retf
_EditMultipleScrollDownAsm ENDP
_TEXT ENDS
END
