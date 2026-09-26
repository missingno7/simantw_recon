; Shared clipped-line and pixel-line module; its private state occupies DGROUP offsets 1D78h-1D8Bh.
.8086
EXTRN __AHINCR:ABS
_DATA SEGMENT WORD PUBLIC 'DATA'
ClipXMax DW 0
ClipYMax DW 0
ClipDeltaX DW 0
ClipDeltaY DW 0
ClipXSign DB 0
ClipYSign DB 0
ClipOutCode DW 0
PlotPixel DW 0
PlotDestSegment DW 0
PlotDestOffset DW 0
PlotStride DW 0
_DATA ENDS
DGROUP GROUP _DATA
_TEXT SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:_TEXT, DS:DGROUP
PUBLIC _os_ClipLine, _PlotLine, _PlotMonoLine
_os_ClipLine PROC NEAR
    push ax
    mov DS:[ClipOutCode], 0
L_os_ClipLine_007:
    xor al, al
    cmp si, 0
    jl L_os_ClipLine_021
    cmp si, DS:[ClipYMax]
    jg L_os_ClipLine_030
    cmp di, 0
    jl L_os_ClipLine_03F
    cmp di, DS:[ClipXMax]
    jg L_os_ClipLine_043
    jmp SHORT L_os_ClipLine_045
L_os_ClipLine_021:
    or al, 8
    cmp di, 0
    jl L_os_ClipLine_03F
    cmp di, DS:[ClipXMax]
    jg L_os_ClipLine_043
    jmp SHORT L_os_ClipLine_045
L_os_ClipLine_030:
    or al, 4
    cmp di, 0
    jl L_os_ClipLine_03F
    cmp di, DS:[ClipXMax]
    jg L_os_ClipLine_043
    jmp SHORT L_os_ClipLine_045
L_os_ClipLine_03F:
    or al, 1
    jmp SHORT L_os_ClipLine_045
L_os_ClipLine_043:
    or al, 2
L_os_ClipLine_045:
    mov ah, al
    xchg si, dx
    xchg di, bx
    xor al, al
    cmp si, 0
    jl L_os_ClipLine_065
    cmp si, DS:[ClipYMax]
    jg L_os_ClipLine_074
    cmp di, 0
    jl L_os_ClipLine_083
    cmp di, DS:[ClipXMax]
    jg L_os_ClipLine_087
    jmp SHORT L_os_ClipLine_089
L_os_ClipLine_065:
    or al, 8
    cmp di, 0
    jl L_os_ClipLine_083
    cmp di, DS:[ClipXMax]
    jg L_os_ClipLine_087
    jmp SHORT L_os_ClipLine_089
L_os_ClipLine_074:
    or al, 4
    cmp di, 0
    jl L_os_ClipLine_083
    cmp di, DS:[ClipXMax]
    jg L_os_ClipLine_087
    jmp SHORT L_os_ClipLine_089
L_os_ClipLine_083:
    or al, 1
    jmp SHORT L_os_ClipLine_089
L_os_ClipLine_087:
    or al, 2
L_os_ClipLine_089:
    xchg si, dx
    xchg di, bx
    test ah, al
    jne L_os_ClipLine_0D9
    or ax, ax
    je L_os_ClipLine_0CB
    cmp di, bx
    jl L_os_ClipLine_0A4
    xchg si, dx
    xchg di, bx
    xchg ah, al
    xor DS:[ClipOutCode], 1
L_os_ClipLine_0A4:
    test ah, 1
    jne L_os_ClipLine_0DC
    test al, 2
    jne L_os_ClipLine_10B
    cmp si, dx
    jl L_os_ClipLine_0BC
    xchg si, dx
    xchg di, bx
    xchg ah, al
    xor DS:[ClipOutCode], 1
L_os_ClipLine_0BC:
    test ah, 8
    jne L_os_ClipLine_13B
    test al, 4
    je L_os_ClipLine_0C8
    jmp NEAR PTR L_os_ClipLine_16A
L_os_ClipLine_0C8:
    jmp NEAR PTR L_os_ClipLine_007
L_os_ClipLine_0CB:
    cmp DS:[ClipOutCode], 0
    je L_os_ClipLine_0D6
    xchg si, dx
    xchg di, bx
L_os_ClipLine_0D6:
    clc
    pop ax
    ret
L_os_ClipLine_0D9:
    stc
    pop ax
    ret
L_os_ClipLine_0DC:
    push dx
    push bx
    push di
    push si
L_os_ClipLine_0E0:
    mov ax, si
    mov cx, di
    add ax, dx
    add cx, bx
    sar ax, 1
    sar cx, 1
    cmp cx, 0
    je L_os_ClipLine_100
    jg L_os_ClipLine_0FA
    mov si, ax
    mov di, cx
    inc di
    jmp SHORT L_os_ClipLine_0E0
L_os_ClipLine_0FA:
    mov bx, cx
    mov dx, ax
    jmp SHORT L_os_ClipLine_0E0
L_os_ClipLine_100:
    pop si
    pop di
    pop bx
    pop dx
    mov si, ax
    mov di, cx
    jmp NEAR PTR L_os_ClipLine_007
L_os_ClipLine_10B:
    push dx
    push bx
    push di
    push si
L_os_ClipLine_10F:
    mov ax, si
    mov cx, di
    add ax, dx
    add cx, bx
    sar ax, 1
    sar cx, 1
    cmp cx, DS:[ClipXMax]
    je L_os_ClipLine_130
    jg L_os_ClipLine_12A
    mov si, ax
    mov di, cx
    inc di
    jmp SHORT L_os_ClipLine_10F
L_os_ClipLine_12A:
    mov bx, cx
    mov dx, ax
    jmp SHORT L_os_ClipLine_10F
L_os_ClipLine_130:
    pop si
    pop di
    pop bx
    pop dx
    mov dx, ax
    mov bx, cx
    jmp NEAR PTR L_os_ClipLine_007
L_os_ClipLine_13B:
    push dx
    push bx
    push di
    push si
L_os_ClipLine_13F:
    mov ax, si
    mov cx, di
    add ax, dx
    add cx, bx
    sar ax, 1
    sar cx, 1
    cmp ax, WORD PTR 0
    je L_os_ClipLine_15F
    jg L_os_ClipLine_159
    mov si, ax
    inc si
    mov di, cx
    jmp SHORT L_os_ClipLine_13F
L_os_ClipLine_159:
    mov bx, cx
    mov dx, ax
    jmp SHORT L_os_ClipLine_13F
L_os_ClipLine_15F:
    pop si
    pop di
    pop bx
    pop dx
    mov si, ax
    mov di, cx
    jmp NEAR PTR L_os_ClipLine_007
L_os_ClipLine_16A:
    push dx
    push bx
    push di
    push si
L_os_ClipLine_16E:
    mov ax, si
    mov cx, di
    add ax, dx
    add cx, bx
    sar ax, 1
    sar cx, 1
    cmp ax, DS:[ClipYMax]
    je L_os_ClipLine_18F
    jg L_os_ClipLine_189
    mov si, ax
    inc si
    mov di, cx
    jmp SHORT L_os_ClipLine_16E
L_os_ClipLine_189:
    mov bx, cx
    mov dx, ax
    jmp SHORT L_os_ClipLine_16E
L_os_ClipLine_18F:
    pop si
    pop di
    pop bx
    pop dx
    mov dx, ax
    mov bx, cx
    jmp NEAR PTR L_os_ClipLine_007
_os_ClipLine ENDP
_PlotLine PROC FAR
    push bp
    mov bp, sp
    push bp
    push si
    push di
    push cx
    push bx
    push dx
    push es
    mov di, word ptr [bp + 6]
    mov si, word ptr [bp + 8]
    mov bx, word ptr [bp + 0ah]
    mov dx, word ptr [bp + 0ch]
    les ax, [bp + 10h]
    mov DS:[PlotDestOffset], ax
    mov DS:[PlotDestSegment], es
    mov ax, word ptr [bp + 18h]
    mov DS:[PlotStride], ax
    mov ax, word ptr [bp + 14h]
    mov DS:[ClipYMax], ax
    mov ax, word ptr [bp + 16h]
    mov DS:[ClipXMax], ax
    mov ax, word ptr [bp + 0eh]
    mov DS:[PlotPixel], ax
    dec DS:[ClipYMax]
    dec DS:[ClipXMax]
    call NEAR PTR _os_ClipLine
    jae L_PlotLine_04E
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
L_PlotLine_04E:
    inc DS:[ClipXMax]
    inc DS:[ClipYMax]
    xor ax, ax
    mov cx, dx
    sub cx, si
    jns L_PlotLine_061
    inc ax
    neg cx
L_PlotLine_061:
    mov DS:[ClipDeltaY], cx
    mov DS:[ClipYSign], al
    xor ax, ax
    mov cx, bx
    sub cx, di
    jns L_PlotLine_073
    inc ax
    neg cx
L_PlotLine_073:
    mov DS:[ClipDeltaX], cx
    mov DS:[ClipXSign], al
    xor ax, ax
    cmp cx, DS:[ClipDeltaY]
    je L_PlotLine_089
    jbe L_PlotLine_086
    jmp SHORT L_PlotLine_08E
L_PlotLine_086:
    jmp NEAR PTR L_PlotLine_13D
L_PlotLine_089:
    inc DS:[ClipDeltaX]
    dec ax
L_PlotLine_08E:
    mov bp, 1
    cmp DS:[ClipYSign], 0
    je L_PlotLine_09A
    neg bp
L_PlotLine_09A:
    cmp DS:[ClipXSign], 0
    je L_PlotLine_0A7
    xchg di, bx
    xchg si, dx
    neg bp
L_PlotLine_0A7:
    xor ax, ax
    mov dx, DS:[ClipDeltaY]
    mov cx, DS:[ClipDeltaX]
    div cx
    mov dx, ax
    mov cx, DS:[ClipDeltaX]
    or cx, cx
    je L_PlotLine_134
    mov ax, DS:[PlotPixel]
    mov bx, 0ffffh
    and ax, WORD PTR 0fh
L_PlotLine_0C6:
    push di
    push bx
    push cx
    push dx
    push di
    mov ax, DS:[PlotDestSegment]
    mov es, ax
    mov ax, DS:[ClipYMax]
    sub ax, si
    dec ax
    mul DS:[PlotStride]
    shr di, 1
    add ax, di
    mov bx, DS:[PlotDestOffset]
    add bx, ax
    jae L_PlotLine_0ED
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
L_PlotLine_0ED:
    cmp dx, 0
    je L_PlotLine_0FD
    mov ax, es
    mov cx, dx
L_PlotLine_0F6:
    add ax, OFFSET __AHINCR
    loop L_PlotLine_0F6
    mov es, ax
L_PlotLine_0FD:
    mov ax, DS:[PlotPixel]
    and ax, WORD PTR 0fh
    pop cx
    mov ch, byte ptr es:[bx]
    not cl
    and cl, 1
    shl cl, 1
    shl cl, 1
    ror ch, cl
    and ch, 0f0h
    or ch, al
    rol ch, cl
    mov byte ptr es:[bx], ch
    pop dx
    pop cx
    pop bx
    pop di
    inc di
    add bx, dx
    jb L_PlotLine_130
    loop L_PlotLine_0C6
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
L_PlotLine_130:
    add si, bp
    loop L_PlotLine_0C6
L_PlotLine_134:
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
L_PlotLine_13D:
    mov bp, 1
    cmp DS:[ClipXSign], 0
    je L_PlotLine_149
    neg bp
L_PlotLine_149:
    cmp DS:[ClipYSign], 0
    je L_PlotLine_156
    xchg di, bx
    xchg si, dx
    neg bp
L_PlotLine_156:
    xor ax, ax
    mov dx, DS:[ClipDeltaX]
    mov cx, DS:[ClipDeltaY]
    div cx
    mov dx, ax
    mov cx, DS:[ClipDeltaY]
    inc cx
    mov ax, DS:[PlotPixel]
    and ax, WORD PTR 0fh
    mov bx, 0ffffh
L_PlotLine_172:
    push di
    push bx
    push cx
    push dx
    push di
    mov ax, DS:[PlotDestSegment]
    mov es, ax
    mov ax, DS:[ClipYMax]
    sub ax, si
    dec ax
    mul DS:[PlotStride]
    shr di, 1
    add ax, di
    mov bx, DS:[PlotDestOffset]
    add bx, ax
    jae L_PlotLine_199
    mov ax, es
    add ax, OFFSET __AHINCR
    mov es, ax
L_PlotLine_199:
    cmp dx, 0
    je L_PlotLine_1A9
    mov ax, es
    mov cx, dx
L_PlotLine_1A2:
    add ax, OFFSET __AHINCR
    loop L_PlotLine_1A2
    mov es, ax
L_PlotLine_1A9:
    mov ax, DS:[PlotPixel]
    and ax, WORD PTR 0fh
    pop cx
    mov ch, byte ptr es:[bx]
    not cl
    and cl, 1
    shl cl, 1
    shl cl, 1
    ror ch, cl
    and ch, 0f0h
    or ch, al
    rol ch, cl
    mov byte ptr es:[bx], ch
    pop dx
    pop cx
    pop bx
    pop di
    inc si
    add bx, dx
    jb L_PlotLine_1DC
    loop L_PlotLine_172
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
L_PlotLine_1DC:
    add di, bp
    loop L_PlotLine_172
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
_PlotLine ENDP
_PlotMonoLine PROC FAR
    push bp
    mov bp, sp
    push bp
    push si
    push di
    push cx
    push bx
    push dx
    push es
    mov di, word ptr [bp + 6]
    mov si, word ptr [bp + 8]
    mov bx, word ptr [bp + 0ah]
    mov dx, word ptr [bp + 0ch]
    les ax, [bp + 10h]
    mov DS:[PlotDestOffset], ax
    mov ax, word ptr [bp + 18h]
    mov DS:[PlotStride], ax
    mov ax, word ptr [bp + 14h]
    mov DS:[ClipYMax], ax
    mov ax, word ptr [bp + 16h]
    mov DS:[ClipXMax], ax
    mov ax, word ptr [bp + 0eh]
    mov DS:[PlotPixel], ax
    dec DS:[ClipYMax]
    dec DS:[ClipXMax]
    call NEAR PTR _os_ClipLine
    jae L_PlotMonoLine_04A
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
L_PlotMonoLine_04A:
    inc DS:[ClipXMax]
    inc DS:[ClipYMax]
    xor ax, ax
    mov cx, dx
    sub cx, si
    jns L_PlotMonoLine_05D
    inc ax
    neg cx
L_PlotMonoLine_05D:
    mov DS:[ClipDeltaY], cx
    mov DS:[ClipYSign], al
    xor ax, ax
    mov cx, bx
    sub cx, di
    jns L_PlotMonoLine_06F
    inc ax
    neg cx
L_PlotMonoLine_06F:
    mov DS:[ClipDeltaX], cx
    mov DS:[ClipXSign], al
    xor ax, ax
    cmp cx, DS:[ClipDeltaY]
    je L_PlotMonoLine_085
    jbe L_PlotMonoLine_082
    jmp SHORT L_PlotMonoLine_08A
L_PlotMonoLine_082:
    jmp NEAR PTR L_PlotMonoLine_11E
L_PlotMonoLine_085:
    inc DS:[ClipDeltaX]
    dec ax
L_PlotMonoLine_08A:
    mov bp, 1
    cmp DS:[ClipYSign], 0
    je L_PlotMonoLine_096
    neg bp
L_PlotMonoLine_096:
    cmp DS:[ClipXSign], 0
    je L_PlotMonoLine_0A3
    xchg di, bx
    xchg si, dx
    neg bp
L_PlotMonoLine_0A3:
    xor ax, ax
    mov dx, DS:[ClipDeltaY]
    mov cx, DS:[ClipDeltaX]
    div cx
    mov dx, ax
    mov cx, DS:[ClipDeltaX]
    or cx, cx
    je L_PlotMonoLine_115
    mov ax, DS:[PlotPixel]
    mov bx, 0ffffh
    and ax, WORD PTR 0fh
L_PlotMonoLine_0C2:
    push di
    push bx
    push cx
    push dx
    mov cx, di
    mov ax, DS:[ClipYMax]
    sub ax, si
    dec ax
    mul DS:[PlotStride]
    shr di, 1
    shr di, 1
    shr di, 1
    add ax, di
    mov bx, DS:[PlotDestOffset]
    add bx, ax
    mov ax, DS:[PlotPixel]
    not ax
    and ax, WORD PTR 1
    and cx, 7
    xor cx, 7
    mov ch, byte ptr es:[bx]
    ror ch, cl
    and ch, 0feh
    or ch, al
    rol ch, cl
    mov byte ptr es:[bx], ch
    pop dx
    pop cx
    pop bx
    pop di
    inc di
    add bx, dx
    jb L_PlotMonoLine_111
    loop L_PlotMonoLine_0C2
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
L_PlotMonoLine_111:
    add si, bp
    loop L_PlotMonoLine_0C2
L_PlotMonoLine_115:
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
L_PlotMonoLine_11E:
    mov bp, 1
    cmp DS:[ClipXSign], 0
    je L_PlotMonoLine_12A
    neg bp
L_PlotMonoLine_12A:
    cmp DS:[ClipYSign], 0
    je L_PlotMonoLine_137
    xchg di, bx
    xchg si, dx
    neg bp
L_PlotMonoLine_137:
    xor ax, ax
    mov dx, DS:[ClipDeltaX]
    mov cx, DS:[ClipDeltaY]
    div cx
    mov dx, ax
    mov cx, DS:[ClipDeltaY]
    inc cx
    mov ax, DS:[PlotPixel]
    and ax, WORD PTR 0fh
    mov bx, 0ffffh
L_PlotMonoLine_153:
    push di
    push bx
    push cx
    push dx
    mov cx, di
    mov ax, DS:[ClipYMax]
    sub ax, si
    dec ax
    mul DS:[PlotStride]
    shr di, 1
    shr di, 1
    shr di, 1
    add ax, di
    mov bx, DS:[PlotDestOffset]
    add bx, ax
    mov ax, DS:[PlotPixel]
    not ax
    and ax, WORD PTR 1
    and cx, 7
    xor cx, 7
    mov ch, byte ptr es:[bx]
    ror ch, cl
    and ch, 0feh
    or ch, al
    rol ch, cl
    mov byte ptr es:[bx], ch
    pop dx
    pop cx
    pop bx
    pop di
    inc si
    add bx, dx
    jb L_PlotMonoLine_1A2
    loop L_PlotMonoLine_153
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
L_PlotMonoLine_1A2:
    add di, bp
    loop L_PlotMonoLine_153
    pop es
    pop dx
    pop bx
    pop cx
    pop di
    pop si
    pop bp
    pop bp
    retf
_PlotMonoLine ENDP
_TEXT ENDS
END
