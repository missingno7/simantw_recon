; Shared glyph rendering module: the three procedures use one DGROUP stride word.
.186
EXTRN _bHelp:BYTE
_DATA SEGMENT WORD PUBLIC 'DATA'
CopyCharGlyphStride DW 0
_DATA ENDS
DGROUP GROUP _DATA
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT, DS:DGROUP
PUBLIC _CopyChar, _CopyCharRep, _MoveTextToBalloon
_CopyChar PROC FAR
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
    mov WORD PTR DS:[CopyCharGlyphStride], ax
    add di, 2
    mov ax, [bp+0Ah]
    add di, ax
    mov ax, [bp+0Ch]
    mov dx, WORD PTR DS:[CopyCharGlyphStride]
    shl ax, 1
    mul dl
    add di, ax
    mov dx, WORD PTR DS:[CopyCharGlyphStride]
    sub dx, 1
    lds si, [bp+6]
    mov bx, 10h
    cld
copy_char_row:
    movsb
    add di, dx
    dec bx
    jne copy_char_row
    pop es
    pop ds
    popa
    pop bp
    retf
_CopyChar ENDP

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
    mov WORD PTR DS:[CopyCharGlyphStride], ax
    add di, 2
    mov ax, [bp+0Ah]
    add di, ax
    mov ax, [bp+0Ch]
    mov dx, WORD PTR DS:[CopyCharGlyphStride]
    shl ax, 1
    mul dl
    add di, ax
    mov dx, WORD PTR DS:[CopyCharGlyphStride]
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
    mov WORD PTR DS:[CopyCharGlyphStride], ax
    add di, 2
    mov ax, [bp+0Eh]
    add di, ax
    mov ax, [bp+10h]
    mov dx, WORD PTR DS:[CopyCharGlyphStride]
    shl ax, 1
    mul dl
    add di, ax
    mov dx, WORD PTR DS:[CopyCharGlyphStride]
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
