; Replicate each source byte across a glyph run in every destination row.
.186
EXTRN _bHelp:BYTE
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _CopyCharRep
_CopyCharRep PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    mov ax, SEG _bHelp
    mov ds, ax
    les di, [bp+0Eh]
    mov ax, es:[di]
    add di, 2
    shr ax, 3
    mov WORD PTR DS:[1D70h], ax
    add di, 2
    mov ax, [bp+0Ah]
    add di, ax
    mov ax, [bp+0Ch]
    mov dx, WORD PTR DS:[1D70h]
    shl ax, 1
    mul dl
    add di, ax
    mov dx, WORD PTR DS:[1D70h]
    mov cx, [bp+12h]
    sub dx, cx
    lds si, [bp+6]
    mov bx, 10h
    cld
copy_char_rep_row:
    push cx
    lodsb
    rep stosb
    pop cx
    add di, dx
    dec bx
    jne copy_char_rep_row
    pop es
    pop ds
    popa
    pop bp
    retf
_CopyCharRep ENDP
_TEXT ENDS
END
