; Move each row's contents leftward and fill the new right edge with FFFFh.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _EditScrollLeftAsm
_EditScrollLeftAsm PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    std
    push ds
    mov ax, [bp+10h]
    mul WORD PTR [bp+0Eh]
    dec ax
    mov dx, ax
    les di, [bp+6]
    add di, ax
    dec ax
    lds si, [bp+6]
    add si, ax
    mov cx, ax
    rep movsb
    pop ds
    push ds
    mov cx, dx
    dec cx
    shl dx, 1
    les di, [bp+0Ah]
    add di, dx
    dec dx
    dec dx
    lds si, [bp+0Ah]
    add si, dx
    rep movsw
    pop ds
    mov bx, [bp+10h]
    shl bx, 1
    mov cx, [bp+0Eh]
    mov ax, 0FFFFh
    les di, [bp+0Ah]
edit_left_fill:
    mov WORD PTR es:[di], ax
    add di, bx
    loop edit_left_fill
    pop es
    pop ds
    popa
    pop bp
    retf
_EditScrollLeftAsm ENDP
_TEXT ENDS
END
