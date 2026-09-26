; LZSS unpacker state from the reviewed merge evidence.
.186
EXTRN _read:FAR
EXTRN _Unpack:NEAR
EXTRN _unpackHandle:DWORD
EXTRN _pack_threshold:WORD
PACK SEGMENT WORD PUBLIC 'FAR_DATA'
    EXTRN _pack_buf:BYTE
PACK ENDS
_DATA SEGMENT WORD PUBLIC 'DATA'
UnpackInputOffset EQU _pack_threshold+2
UnpackInputSegment EQU _pack_threshold+4
UnpackReadCount EQU _pack_threshold+6
UnpackBufferCapacity EQU _pack_threshold+114h
UnpackBufferOffset EQU _pack_threshold+116h
_DATA ENDS
DGROUP GROUP _DATA
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE, DS:DGROUP
_UnpackFileRead PROC FAR
    push bp
    mov bp, sp
    sub sp, 2
    xor ax, ax
    mov word ptr [bp - 2], ax
    cmp word ptr [UnpackReadCount], ax
    jg L_0036
L_0011:
    push word ptr [UnpackBufferCapacity]
    les bx, DWORD PTR [UnpackBufferOffset]
    mov word ptr [UnpackInputOffset], bx
    mov word ptr [UnpackInputSegment], es
    push es
    push bx
    push word ptr _unpackHandle
    call FAR PTR _read
    add sp, 8
    and ax, ax
    jle L_005C
    mov word ptr [UnpackReadCount], ax
L_0036:
    mov ax, word ptr [bp + 0Ah]
    sub ax, word ptr [bp - 2]
    push ax
    push word ptr [bp + 8]
    mov ax, word ptr [bp + 6]
    add ax, word ptr [bp - 2]
    push ax
    nop
    push cs
    call NEAR PTR _Unpack
    add sp, 6
    add word ptr [bp - 2], ax
    mov ax, word ptr [bp + 0Ah]
    cmp word ptr [bp - 2], ax
    jne L_0011
    jmp SHORT L_005F
L_005C:
    mov ax, word ptr [bp - 2]
L_005F:
    mov sp, bp
    pop bp
    retf
_UnpackFileRead ENDP
SIMTWO_MODULE ENDS
END


