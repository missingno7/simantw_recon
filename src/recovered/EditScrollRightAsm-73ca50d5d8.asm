; Move each row rightward and fill the new leftmost word of each row.
.186
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _EditScrollRightAsm
_EditScrollRightAsm PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    cld
    mov bx, ds
    mov ax, [bp+10h]
    mul WORD PTR [bp+0Eh]
    dec ax
    mov cx, ax
    mov dx, ax
    les di, [bp+6]
    lds si, [bp+6]
    inc si
    rep movsb
    mov ds, bx
    mov cx, dx
    les di, [bp+0Ah]
    lds si, [bp+0Ah]
    inc si
    inc si
    rep movsw
    mov ds, bx
    mov bx, [bp+10h]
    mov cx, [bp+0Eh]
    mov ax, 0FFFFh
    les di, [bp+6]
    add di, bx
    dec di
    dec di
edit_right_fill:
    mov WORD PTR es:[di], ax
    add di, bx
    loop edit_right_fill
    pop es
    pop ds
    popa
    pop bp
    retf
_EditScrollRightAsm ENDP
_TEXT ENDS
END
