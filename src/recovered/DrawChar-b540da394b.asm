; Draw a character by shifting source words into the destination bitmap and merging edge masks.
.8086
EXTRN _source_bitmap_width:WORD
EXTRN _dest_bitmap_width:WORD
EXTRN _font_MakeImage:NEAR
_DATA SEGMENT WORD PUBLIC 'DATA'
DrawSourceSelector DW 0
DrawDestinationSelector DW 0
    ORG 0Ah
DrawByteStride DW 0
_DATA ENDS
DGROUP GROUP _DATA
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE, DS:DGROUP
PUBLIC _DrawChar
_DrawChar PROC FAR
    push bp
    mov bp, sp
    add bp, 6
    push es
    push ds
    push si
    push di
    mov ax, SEG _source_bitmap_width
    mov ds, ax
    mov cx, 3
    mov bx, [bp+0Ch]
    mov al, bl
    and al, 7
    mov si, bx
    shr si, cl
    mov dx, [bp+0Eh]
    mov ah, dl
    and ah, 7
    mov di, dx
    shr di, cl
    mov bx, ax
    les ax, [bp]
    mov WORD PTR DS:[DrawSourceSelector], es
    add si, ax
    les ax, [bp+4]
    mov WORD PTR DS:[DrawDestinationSelector], es
    add di, ax
    mov cx, bx
    mov bx, [bp+8]
    mov bp, [bp+0Ah]
    mov dx, bx
    shr dx, 1
    shr dx, 1
    shr dx, 1
    mov WORD PTR DS:[DrawByteStride], dx
char_words:
    push si
    push di
    mov dx, WORD PTR DS:[DrawByteStride]
    mov es, WORD PTR DS:[DrawDestinationSelector]
    mov ds, WORD PTR DS:[DrawSourceSelector]
    or dx, dx
    je char_partial_word
char_word_loop:
    lodsw
    xchg ah, al
    shl ax, cl
    xor al, al
    xchg cl, ch
    shr ax, cl
    xchg cl, ch
    xchg ah, al
    or WORD PTR es:[di], ax
    inc di
    dec si
    dec dx
    jne char_word_loop
char_partial_word:
    mov ax, bx
    and ax, WORD PTR 7
    je char_next_row
    mov dx, bx
    mov bx, OFFSET _font_MakeImage+586
    xlat CS:[BX]
    mov bx, dx
    xor dx, dx
    mov dh, al
    lodsw
    xchg ah, al
    shl ax, cl
    xor al, al
    xchg cl, ch
    and ax, dx
    shr ax, cl
    xchg cl, ch
    xchg ah, al
    or WORD PTR es:[di], ax
char_next_row:
    pop di
    pop si
    dec bp
    je char_return
    mov ax, SEG _source_bitmap_width
    mov ds, ax
    add si, WORD PTR DS:[_source_bitmap_width]
    add di, WORD PTR DS:[_dest_bitmap_width]
    jmp SHORT char_words
char_return:
    pop di
    pop si
    pop ds
    pop es
    pop bp
    retf
_DrawChar ENDP
SIMTWO_MODULE ENDS
END

