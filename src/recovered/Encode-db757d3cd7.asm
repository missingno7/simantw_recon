; Faithful MASM instruction reconstruction of _Encode.
.186
EXTRN _DeleteNode:NEAR
EXTRN _InitTree:NEAR
EXTRN _InsertNode:NEAR
EXTRN _PackReadByte:NEAR
EXTRN _PackWriteByte:NEAR
EXTRN _pack_threshold:WORD
PACK SEGMENT WORD PUBLIC 'FAR_DATA'
    EXTRN _pack_buf:BYTE, _match_position:WORD, _match_length:WORD
PACK ENDS
_DATA SEGMENT WORD PUBLIC 'DATA'
_DATA ENDS
CONST SEGMENT WORD PUBLIC 'CONST'
PackBufferSelector DW SEG PACK
PackMatchPositionSelector DW SEG PACK
PackMatchLengthSelector DW SEG PACK
CONST ENDS
DGROUP GROUP _DATA, CONST
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE, DS:DGROUP, ES:PACK
PUBLIC _Encode
_Encode PROC FAR
    push bp
    mov bp, sp
    sub sp, 2Ah
    push di
    push si
    nop
    push cs
    call NEAR PTR _InitTree
    mov BYTE PTR [bp - 26h], 0
    mov BYTE PTR [bp - 1], 1
    mov word ptr [bp - 0Ah], 1
    mov word ptr [bp - 0Ch], 0FEEh
    sub ax, ax
    mov word ptr [bp - 10h], ax
    mov word ptr [bp - 14h], ax
    mov word ptr [bp - 4], ax
    jmp SHORT L_003C
L_002C:
    mov es, word ptr [PackBufferSelector]
    mov bx, word ptr [bp - 4]
    mov byte ptr es:[bx + _pack_buf], 20h
    inc word ptr [bp - 4]
L_003C:
    cmp word ptr [bp - 4], 0FEEh
    jl L_002C
    sub si, si
L_0045:
    push cs
    call NEAR PTR _PackReadByte
    mov word ptr [bp - 12h], ax
    inc ax
    je L_0061
    mov al, [bp - 12h]
    mov es, word ptr [PackBufferSelector]
    mov byte ptr es:[si + 0FF2h], al
    inc si
    cmp si, 12h
    jl L_0045
L_0061:
    or si, si
    jne L_0068
    jmp NEAR PTR L_0218
L_0068:
    mov word ptr [bp - 8], si
    mov di, 1
L_006E:
    mov ax, 0FEEh
    sub ax, di
    push ax
    nop
    push cs
    call NEAR PTR _InsertNode
    pop bx
    inc di
    cmp di, 12h
    jle L_006E
    mov ax, 0FEEh
    push ax
    nop
    push cs
    call NEAR PTR _InsertNode
    pop bx
L_008A:
    mov ax, word ptr [bp - 8]
    mov bx, 2
    mov es, word ptr [PackMatchPositionSelector]
    mov word ptr [bp - 2Ah], bx
    mov word ptr [bp - 28h], es
    cmp word ptr es:[bx], ax
    jle L_00A2
    mov word ptr es:[bx], ax
L_00A2:
    mov ax, word ptr [bp - 0Eh]
    cmp word ptr [bp - 12h], ax
    jne L_00BA
    inc word ptr [bp - 10h]
    cmp word ptr [bp - 10h], 0Fh
    jle L_00C5
    mov word ptr [bp - 10h], 0Fh
    jmp SHORT L_00C5
L_00BA:
    mov ax, word ptr [bp - 12h]
    mov word ptr [bp - 0Eh], ax
    mov word ptr [bp - 10h], 0
L_00C5:
    mov ax, word ptr [bp - 10h]
    add ax, word ptr _pack_threshold
    les bx, [bp - 2Ah]
    cmp ax, word ptr es:[bx]
    jl L_00F4
    mov word ptr es:[bx], 1
    mov al, [bp - 1]
    or [bp - 26h], al
    mov di, word ptr [bp - 0Ah]
    mov es, word ptr [PackBufferSelector]
    mov bx, word ptr [bp - 0Ch]
    mov al, byte ptr es:[bx + _pack_buf]
    mov [bp + di - 26h], al
    inc di
    jmp SHORT L_011F
L_00F4:
    mov di, word ptr [bp - 0Ah]
    mov es, word ptr [PackMatchLengthSelector]
    mov al, byte ptr es:[_match_position]
    mov [bp + di - 26h], al
    mov cl, 4
    mov ax, word ptr es:[_match_position]
    sar ax, cl
    and al, 0F0h
    les bx, [bp - 2Ah]
    mov cl, byte ptr es:[bx]
    sub cl, byte ptr _pack_threshold
    dec cl
    or al, cl
    inc di
    mov [bp + di - 26h], al
    inc di
L_011F:
    shl BYTE PTR [bp - 1], 1
    cmp BYTE PTR [bp - 1], 0
    jne L_0151
    mov word ptr [bp - 4], 0
    mov word ptr [bp - 0Ah], di
    jmp SHORT L_0141
L_0132:
    mov si, word ptr [bp - 4]
    mov al, [bp + si - 26h]
    push ax
    push cs
    call NEAR PTR _PackWriteByte
    pop bx
    inc word ptr [bp - 4]
L_0141:
    cmp word ptr [bp - 4], di
    jl L_0132
    mov BYTE PTR [bp - 26h], 0
    mov BYTE PTR [bp - 1], 1
    mov di, 1
L_0151:
    les bx, [bp - 2Ah]
    mov ax, word ptr es:[bx]
    mov word ptr [bp - 6], ax
    mov word ptr [bp - 4], 0
    mov word ptr [bp - 0Ah], di
    mov si, word ptr [bp - 14h]
    mov di, word ptr [bp - 12h]
    jmp SHORT L_01AD
L_016A:
    push cs
    call NEAR PTR _PackReadByte
    mov di, ax
    cmp di, -1
    je L_01B5
    push si
    nop
    push cs
    call NEAR PTR _DeleteNode
    pop bx
    mov ax, di
    mov es, word ptr [PackBufferSelector]
    mov byte ptr es:[si + _pack_buf], al
    cmp si, 11h
    jge L_0191
    mov byte ptr es:[si + _pack_buf + 1000h], al
L_0191:
    lea ax, [si + 1]
    and ah, 0Fh
    mov si, ax
    mov ax, word ptr [bp - 0Ch]
    inc ax
    and ah, 0Fh
    mov word ptr [bp - 0Ch], ax
    push ax
    nop
    push cs
    call NEAR PTR _InsertNode
    pop bx
    inc word ptr [bp - 4]
L_01AD:
    mov ax, word ptr [bp - 6]
    cmp word ptr [bp - 4], ax
    jl L_016A
L_01B5:
    mov word ptr [bp - 12h], di
    mov word ptr [bp - 14h], si
    jmp SHORT L_01E6
L_01BD:
    push word ptr [bp - 14h]
    nop
    push cs
    call NEAR PTR _DeleteNode
    pop bx
    mov ax, word ptr [bp - 14h]
    inc ax
    and ah, 0Fh
    mov word ptr [bp - 14h], ax
    mov ax, word ptr [bp - 0Ch]
    inc ax
    and ah, 0Fh
    mov word ptr [bp - 0Ch], ax
    dec word ptr [bp - 8]
    je L_01E6
    push ax
    nop
    push cs
    call NEAR PTR _InsertNode
    pop bx
L_01E6:
    mov ax, word ptr [bp - 4]
    inc word ptr [bp - 4]
    cmp ax, word ptr [bp - 6]
    jl L_01BD
    cmp word ptr [bp - 8], 0
    jle L_01FA
    jmp NEAR PTR L_008A
L_01FA:
    mov di, word ptr [bp - 0Ah]
    cmp di, 1
    jle L_0214
    sub si, si
L_0204:
    cmp si, di
    jge L_0214
    mov al, [bp + si - 26h]
    push ax
    push cs
    call NEAR PTR _PackWriteByte
    pop bx
    inc si
    jmp SHORT L_0204
L_0214:
    push cs
    call NEAR PTR _PackWriteByte+40h
L_0218:
    pop si
    pop di
    mov sp, bp
    pop bp
    retf
_Encode ENDP
SIMTWO_MODULE ENDS
END
