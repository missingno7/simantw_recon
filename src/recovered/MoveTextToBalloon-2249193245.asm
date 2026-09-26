; Copy packed glyph rows into a text balloon with the destination stride.
.186
EXTRN _bHelp:BYTE
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT
PUBLIC _MoveTextToBalloon
_MoveTextToBalloon PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    mov ax, SEG _bHelp
    mov ds, ax
    les di, [bp+0Ah]
    mov ax, es:[di]
    add di, 2
    shr ax, 3
    mov WORD PTR DS:[1D70h], ax
    add di, 2
    mov ax, [bp+0Eh]
    add di, ax
    mov ax, [bp+10h]
    mov dx, WORD PTR DS:[1D70h]
    shl ax, 1
    mul dl
    add di, ax
    mov dx, WORD PTR DS:[1D70h]
    lds si, [bp+6]
    mov cx, [si]
    add cx, 7
    shr cx, 3
    add si, 2
    mov bx, [si]
    add si, 2
    shl dx, 1
    sub dx, cx
    lds si, [si]
    cld
move_balloon_row:
    push cx
move_balloon_byte:
    lodsb
    xor al, 0FFh
    stosb
    loop move_balloon_byte
    pop cx
    add di, dx
    dec bx
    jne move_balloon_row
    pop es
    pop ds
    popa
    pop bp
    retf
_MoveTextToBalloon ENDP
_TEXT ENDS
END
