; Move the byte and word portions toward the top, then clear the exposed row.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _EditScrollUpAsm
_EditScrollUpAsm PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    std
    mov bx, ds
    mov ax, [bp+0Eh]
    dec ax
    mul WORD PTR [bp+10h]
    mov cx, ax
    les di, [bp+6]
    add di, cx
    add di, [bp+10h]
    dec di
    lds si, [bp+6]
    add si, cx
    dec si
    rep movsb
    mov ds, bx
    mov cx, ax
    les di, [bp+0Ah]
    add di, cx
    add di, [bp+10h]
    dec di
    add di, cx
    add di, [bp+10h]
    dec di
    lds si, [bp+0Ah]
    add si, cx
    dec si
    add si, cx
    dec si
    rep movsw
    cld
    mov ds, bx
    mov cx, [bp+10h]
    mov ax, 0FFFFh
    mov cx, [bp+10h]
    les di, [bp+0Ah]
    rep stosw
    pop es
    pop ds
    popa
    pop bp
    retf
_EditScrollUpAsm ENDP
_TEXT ENDS
END
