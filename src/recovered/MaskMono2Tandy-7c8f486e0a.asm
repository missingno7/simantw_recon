; Clear the destination surface, then merge the selected Tandy mono pixels.
.186
_DATA SEGMENT WORD PUBLIC 'DATA'
TandyRowStride DB 0
TandyPixelStride DB 0
TandyRowCount DB 0
_DATA ENDS
DGROUP GROUP _DATA
_TEXT SEGMENT WORD PUBLIC 'CODE'
ASSUME CS:_TEXT, DS:DGROUP
PUBLIC _MaskMono2Tandy
_MaskMono2Tandy PROC FAR
    push bp
    mov bp, sp
    pusha
    push ds
    push es
    les di, [bp+0Ah]
    mov ax, es:[di]
    add ax, 7
    shr ax, 3
    mov ds:[TandyPixelStride], al
    mov ax, es:[di]
    shl ax, 2
    add ax, 1Fh
    shr ax, 5
    shl ax, 2
    mov ds:[TandyRowStride], al
    add di, 2
    mov ax, es:[di]
    mov ds:[TandyRowCount], al
    add di, 2
    mov bl, ds:[TandyRowStride]
    mul bl
    mov cx, ax
    mov ax, 0
    rep stosb
    mov bl, ds:[TandyPixelStride]
    xor bh, bh
    mov cl, 7
    mov dh, ds:[TandyRowCount]
    mov ch, ds:[TandyPixelStride]
    mov al, ds:[TandyRowStride]
    xor ah, ah
    sub di, ax
    dec di
    mov ah, ds:[TandyPixelStride]
    shl ah, 2
    add ah, ds:[TandyRowStride]
    lds si, [bp+6]
    add si, 4
mask_tandy_pixel:
    mov al, [si]
    shr al, cl
    and al, 1
    mov dl, [bx+si]
    shr dl, cl
    and dl, 1
    je mask_tandy_zero
    sub al, 1
    xor al, 0Fh
    and al, 0Fh
    jmp mask_tandy_merge
mask_tandy_zero:
    mov al, 0Dh
mask_tandy_merge:
    test cl, 1
    je mask_tandy_or
    shl al, 4
mask_tandy_store:
    inc di
mask_tandy_or:
    or es:[di], al
    dec cl
    jge mask_tandy_pixel
    mov cl, 7
    inc si
    dec ch
    jne mask_tandy_pixel
    add si, bx
    mov al, ah
    xor ah, ah
    sub di, ax
    mov ah, al
    mov ch, bl
    dec dh
    jne mask_tandy_pixel
    pop es
    pop ds
    popa
    pop bp
    retf
_MaskMono2Tandy ENDP
_TEXT ENDS
END
