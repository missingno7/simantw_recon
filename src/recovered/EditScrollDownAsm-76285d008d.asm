; Copy the rows upward and clear the newly opened bottom rows.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _EditScrollDownAsm
_EditScrollDownAsm PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    cld
    push ds
    mov ax, [bp+0Eh]
    dec ax
    mul WORD PTR [bp+10h]
    mov cx, ax
    mov dx, [bp+10h]
    les di, [bp+6]
    lds si, [bp+6]
    add si, dx
    rep movsb
    pop ds
    push ds
    mov cx, ax
    les di, [bp+0Ah]
    lds si, [bp+0Ah]
    add si, dx
    add si, dx
    rep movsw
    pop ds
    les di, [bp+0Ah]
    add di, ax
    add di, ax
    mov ax, 0FFFFh
    shl dx, 1
    sub di, dx
    mov cx, dx
    rep stosw
    pop es
    pop ds
    popa
    pop bp
    retf
_EditScrollDownAsm ENDP
_TEXT ENDS
END
