; Whole-module MASM 5.x test: tree initialization, insertion, and deletion share PACK.
.186
EXTRN _unpackHandle:DWORD
PACK SEGMENT WORD PUBLIC 'FAR_DATA'
    EXTRN _pack_buf:BYTE, _match_position:WORD, _match_length:WORD
PACK ENDS
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE
PUBLIC _InitTree, _InsertNode, _DeleteNode
_InitTree PROC FAR
    push di
    ASSUME ES:NOTHING
    mov es, WORD PTR _unpackHandle+2
    ASSUME ES:PACK
    mov ax, 1000h
    mov cx, 100h
    lea di, WORD PTR [_pack_buf+5016h]
    rep stosw
    lea di, WORD PTR [_pack_buf+5216h]
    mov cx, 1000h
    rep stosw
    pop di
    retf
_InitTree ENDP
_InsertNode PROC FAR
    push bp
    mov bp, sp
    sub sp, 2
    push di
    push si
    push ds
    ASSUME DS:NOTHING
    mov ds, WORD PTR _unpackHandle+2
    ASSUME DS:PACK
    mov word ptr [bp - 2], 1
    mov di, 0
    mov dx, word ptr [bp + 6]
    add di, dx
    mov cl, byte ptr [di + _pack_buf]
    xor ch, ch
    add cx, 1001h
    mov bx, dx
    shl bx, 1
    mov word ptr [bx + _pack_buf+3014h], 1000h
    mov word ptr [bx + _pack_buf+1012h], 1000h
    mov WORD PTR _match_length, 0
L_InsertNode_003A:
    mov bx, cx
    shl bx, 1
    cmp word ptr [bp - 2], 0
    jl L_InsertNode_0065
    cmp word ptr [bx + _pack_buf+3014h], 1000h
    je L_InsertNode_0056
    mov cx, word ptr [bx + _pack_buf+3014h]
    mov bx, cx
    shl bx, 1
    jmp SHORT L_InsertNode_0086
L_InsertNode_0056:
    mov word ptr [bx + _pack_buf+3014h], dx
    mov bx, dx
    shl bx, 1
    mov word ptr [bx + _pack_buf+5216h], cx
    jmp NEAR PTR L_InsertNode_0113
L_InsertNode_0065:
    cmp word ptr [bx + _pack_buf+1012h], 1000h
    je L_InsertNode_0077
    mov cx, word ptr [bx + _pack_buf+1012h]
    mov bx, cx
    shl bx, 1
    jmp SHORT L_InsertNode_0086
L_InsertNode_0077:
    mov word ptr [bx + _pack_buf+1012h], dx
    mov bx, dx
    shl bx, 1
    mov word ptr [bx + _pack_buf+5216h], cx
    jmp NEAR PTR L_InsertNode_0113
L_InsertNode_0086:
    mov bx, 1
    mov si, 0
    add si, cx
L_InsertNode_008E:
    xor dh, dh
    mov dl, byte ptr [bx + di + _pack_buf]
    xor ah, ah
    mov al, byte ptr [bx + si + _pack_buf]
    sub dx, ax
    jne L_InsertNode_00A4
    inc bx
    cmp bx, 12h
    jl L_InsertNode_008E
L_InsertNode_00A4:
    mov word ptr [bp - 2], dx
    cmp bx, WORD PTR _match_length
    jle L_InsertNode_00BA
    mov WORD PTR _match_position, cx
    mov WORD PTR _match_length, bx
    cmp bx, 12h
    jge L_InsertNode_00C0
L_InsertNode_00BA:
    mov dx, word ptr [bp + 6]
    jmp NEAR PTR L_InsertNode_003A
L_InsertNode_00C0:
    mov bx, cx
    shl bx, 1
    mov si, word ptr [bp + 6]
    mov dx, si
    add si, si
    mov ax, word ptr [bx + _pack_buf+5216h]
    mov word ptr [si + _pack_buf+5216h], ax
    mov ax, word ptr [bx + _pack_buf+1012h]
    mov word ptr [si + _pack_buf+1012h], ax
    mov ax, word ptr [bx + _pack_buf+3014h]
    mov word ptr [si + _pack_buf+3014h], ax
    mov si, word ptr [bx + _pack_buf+1012h]
    add si, si
    mov word ptr [si + _pack_buf+5216h], dx
    mov si, word ptr [bx + _pack_buf+3014h]
    add si, si
    mov word ptr [si + _pack_buf+5216h], dx
    mov si, word ptr [bx + _pack_buf+5216h]
    add si, si
    cmp cx, word ptr [si + _pack_buf+3014h]
    jne L_InsertNode_0109
    mov word ptr [si + _pack_buf+3014h], dx
    jmp SHORT L_InsertNode_010D
L_InsertNode_0109:
    mov word ptr [si + _pack_buf+1012h], dx
L_InsertNode_010D:
    mov word ptr [bx + _pack_buf+5216h], 1000h
L_InsertNode_0113:
    pop ds
    pop si
    pop di
    mov sp, bp
    pop bp
    retf
_InsertNode ENDP
_DeleteNode PROC FAR
    push bp
    mov bp, sp
    sub sp, 2
    push si
    push di
    push ds
    ASSUME DS:NOTHING
    mov ds, WORD PTR _unpackHandle+2
    ASSUME DS:PACK
    mov bx, word ptr [bp + 6]
    shl bx, 1
    mov ax, 1000h
    cmp word ptr [bx + _pack_buf+5216h], ax
    jne L_DeleteNode_001E
    jmp NEAR PTR L_DeleteNode_00B6
L_DeleteNode_001E:
    cmp word ptr [bx + _pack_buf+3014h], ax
    jne L_DeleteNode_002E
    mov cx, word ptr [bx + _pack_buf+1012h]
    mov si, cx
    add si, si
    jmp SHORT L_DeleteNode_0094
L_DeleteNode_002E:
    cmp word ptr [bx + _pack_buf+1012h], ax
    jne L_DeleteNode_003E
    mov cx, word ptr [bx + _pack_buf+3014h]
    mov si, cx
    add si, si
    jmp SHORT L_DeleteNode_0094
L_DeleteNode_003E:
    mov cx, word ptr [bx + _pack_buf+1012h]
    mov si, cx
    shl si, 1
    cmp word ptr [si + _pack_buf+3014h], 1000h
    je L_DeleteNode_0086
L_DeleteNode_004E:
    mov si, word ptr [si + _pack_buf+3014h]
    add si, si
    cmp word ptr [si + _pack_buf+3014h], 1000h
    jne L_DeleteNode_004E
    mov dx, word ptr [si + _pack_buf+1012h]
    mov di, word ptr [si + _pack_buf+5216h]
    mov cx, di
    shl di, 1
    mov word ptr [di + _pack_buf+3014h], dx
    mov di, dx
    shl di, 1
    mov word ptr [di + _pack_buf+5216h], cx
    mov di, word ptr [bx + _pack_buf+1012h]
    mov word ptr [si + _pack_buf+1012h], di
    mov cx, si
    shr cx, 1
    shl di, 1
    mov word ptr [di + _pack_buf+5216h], cx
L_DeleteNode_0086:
    mov di, word ptr [bx + _pack_buf+3014h]
    mov word ptr [si + _pack_buf+3014h], di
    add di, di
    mov word ptr [di + _pack_buf+5216h], cx
L_DeleteNode_0094:
    mov di, word ptr [bx + _pack_buf+5216h]
    mov word ptr [si + _pack_buf+5216h], di
    add di, di
    mov dx, bx
    shr dx, 1
    cmp word ptr [di + _pack_buf+3014h], dx
    jne L_DeleteNode_00AE
    mov word ptr [di + _pack_buf+3014h], cx
    jmp SHORT L_DeleteNode_00B2
L_DeleteNode_00AE:
    mov word ptr [di + _pack_buf+1012h], cx
L_DeleteNode_00B2:
    mov word ptr [bx + _pack_buf+5216h], ax
L_DeleteNode_00B6:
    pop ds
    pop di
    pop si
    mov sp, bp
    pop bp
    retf
_DeleteNode ENDP
SIMTWO_MODULE ENDS
END
