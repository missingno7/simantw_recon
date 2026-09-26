; Copy one glyph column into the destination bitmap, stepping by its row stride.
.186
EXTRN _bHelp:BYTE
_DATA SEGMENT WORD PUBLIC 'DATA'
CopyCharGlyphStride DW 0
_DATA ENDS
DGROUP GROUP _DATA
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT, DS:DGROUP
PUBLIC _CopyChar
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
_TEXT ENDS
END
