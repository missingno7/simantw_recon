; LZSS pack/unpack routines share the historical SIMTWO code and selector modules.
.186
EXTRN _Encode:NEAR
EXTRN _GetStrategy:NEAR
EXTRN _pack_threshold:WORD
EXTRN _read:FAR
EXTRN _open:FAR
EXTRN _close:FAR
EXTRN _unpackHandle:DWORD
EXTRN rsrvptrs:BYTE
PUBLIC _PackWriteByte, _PackReadByte, _PackFileToFile, _PackMemoryToMemory
PUBLIC _UnpackInit, _Unpack, _UnpackSetBuf, _UnpackFileOpen
PUBLIC _UnpackFileRead, _UnpackFileClose
PACK SEGMENT WORD PUBLIC 'FAR_DATA'
    EXTRN _pack_buf:BYTE, _match_position:WORD, _match_length:WORD
PACK ENDS
_DATA SEGMENT WORD PUBLIC 'DATA'
UnpackPackBufferOffset EQU _pack_threshold-4
UnpackPackBufferSegment EQU _pack_threshold-2
UnpackInputOffset EQU _pack_threshold+2
UnpackInputSegment EQU _pack_threshold+4
UnpackReadCount EQU _pack_threshold+6
UnpackRingPointer EQU _pack_threshold+8
UnpackStateCC EQU _pack_threshold+0Ah
UnpackStateCE EQU _pack_threshold+0Ch
UnpackStateD0 EQU _pack_threshold+0Eh
UnpackCopyRemaining EQU _pack_threshold+10h
UnpackMode EQU _pack_threshold+12h
UnpackBufferCapacity EQU _pack_threshold+114h
UnpackBufferOffset EQU _pack_threshold+116h
UnpackBufferSegment EQU _pack_threshold+118h
_DATA ENDS
_BSS SEGMENT WORD PUBLIC 'BSS'
PackFileInputOffset DW ?
PackFileInputSegment DW ?
PackReadProc DD ?
PackBlockLimit DW ?
PackReadState DW ?
PackReadCount DW ?
PackReadBufferOffset DW ?
PackReadBufferSegment DW ?
PackWriteProc DD ?
PackReadNextOffset DW ?
PackReadNextSegment DW ?
PackFileState DW ?
PackWriteCount DW ?
PackSourceOffset DW ?
PackSourceSegment DW ?
PackOutputOffset DW ?
PackOutputSegment DW ?
PackWriteBufferOffset DW ?
PackWriteBufferSegment DW ?
_BSS ENDS
DGROUP GROUP _DATA, _BSS
SIMTWO_MODULE SEGMENT BYTE PUBLIC 'CODE'
ASSUME CS:SIMTWO_MODULE, DS:DGROUP, SS:DGROUP

_PackWriteByte PROC FAR
    push bp
    mov bp, sp
    mov al, BYTE PTR [bp + 6]
    les bx, DWORD PTR [PackOutputOffset]
    mov byte ptr es:[bx], al
    inc word ptr [PackOutputOffset]
    mov ax, word ptr [PackBlockLimit]
    inc word ptr [PackWriteCount]
    cmp word ptr [PackWriteCount], ax
    jb PackWriteByte_003C
    push word ptr [PackWriteCount]
    mov ax, word ptr [PackWriteBufferOffset]
    mov dx, word ptr [PackWriteBufferSegment]
    mov word ptr [PackOutputOffset], ax
    mov word ptr [PackOutputSegment], dx
    push dx
    push ax
    call DWORD PTR [PackWriteProc]
    mov word ptr [PackWriteCount], 0
PackWriteByte_003C:
    mov sp, bp
    pop bp
    retf
_PackWriteByte ENDP
PackByteOutputCallback LABEL BYTE
ORG 69h
_PackReadByte PROC FAR
PackReadByte_0000:
    cmp word ptr [PackReadCount], 0
    jne PackReadByte_0035
    mov ax, word ptr [PackReadNextOffset]
    mov dx, word ptr [PackReadNextSegment]
    mov word ptr [PackReadBufferOffset], ax
    mov word ptr [PackReadBufferSegment], dx
    mov cx, word ptr [PackBlockLimit]
    mov word ptr [PackReadCount], cx
    push cx
    push dx
    push ax
    call DWORD PTR [PackReadProc]
    add sp, 6
    mov word ptr [PackReadCount], ax
    cmp ax, WORD PTR 0FFFFh
    je PackReadByte_0047
    or ax, ax
    jne PackReadByte_0000
    jmp SHORT PackReadByte_0047
PackReadByte_0035:
    dec word ptr [PackReadCount]
    les bx, DWORD PTR [PackReadBufferOffset]
    inc word ptr [PackReadBufferOffset]
    mov al, byte ptr es:[bx]
    sub ah, ah
    retf
PackReadByte_0047:
    mov word ptr [PackReadCount], 0
    mov ax, 0FFFFh
    retf
_PackReadByte ENDP

PackReadCallback LABEL BYTE
ORG 100h
PackWriteCallback LABEL BYTE
ORG 124h
_PackFileToFile PROC FAR
    push bp
    mov bp, sp
    mov ax, 400h
    push ax
    sub ax, ax
    push ax
    push ax
    push ax
    push ax
    push cs
    call NEAR PTR _GetStrategy+0A16Ch
    mov sp, bp
    mov word ptr [PackReadProc], OFFSET PackReadCallback
    mov word ptr [PackReadProc+2], SEG _GetStrategy
    mov word ptr [PackWriteProc], OFFSET PackWriteCallback
    mov word ptr [PackWriteProc+2], SEG _GetStrategy
    mov ax, word ptr [bp + 6]
    mov word ptr [PackReadState], ax
    mov ax, word ptr [bp + 8]
    mov word ptr [PackFileState], ax
    mov ax, word ptr [bp + 0Ah]
    mov dx, word ptr [bp + 0Ch]
    mov word ptr [PackFileInputOffset], ax
    mov word ptr [PackFileInputSegment], dx
    push cs
    call NEAR PTR _Encode
    push cs
    call NEAR PTR _GetStrategy+0A1E2h
    mov ax, word ptr [PackSourceOffset]
    mov dx, word ptr [PackSourceSegment]
    mov sp, bp
    pop bp
    retf
_PackFileToFile ENDP
PackMemoryReadCallback LABEL BYTE
ORG 17Fh
PackMemoryWriteCallback LABEL BYTE
ORG 1BCh
_PackMemoryToMemory PROC FAR
    push bp
    mov bp, sp
    push word ptr [bp + 0Eh]
    push word ptr [bp + 0Ch]
    push word ptr [bp + 0Ah]
    push word ptr [bp + 8]
    push word ptr [bp + 6]
    push cs
    call NEAR PTR _GetStrategy+0A16Ch
    mov sp, bp
    mov ax, word ptr [bp + 0Eh]
    sub dx, dx
    mov word ptr [PackFileInputOffset], ax
    mov word ptr [PackFileInputSegment], dx
    mov word ptr [PackReadCount], ax
    mov word ptr [PackReadProc], OFFSET PackMemoryReadCallback
    mov word ptr [PackReadProc+2], SEG _GetStrategy
    mov word ptr [PackWriteProc], OFFSET PackMemoryWriteCallback
    mov word ptr [PackWriteProc+2], SEG _GetStrategy
    push cs
    call NEAR PTR _Encode
    mov ax, word ptr [PackSourceOffset]
    mov dx, word ptr [PackSourceSegment]
    mov sp, bp
    pop bp
    retf
_PackMemoryToMemory ENDP
ORG 429h
_UnpackInit PROC FAR
    push bp
    mov bp, sp
    push di
    mov cx, 0FEEh
    les di, DWORD PTR [UnpackPackBufferOffset]
    mov al, 20h
    rep stosb
    mov word ptr [UnpackRingPointer], 0FEEh
    mov word ptr [UnpackStateCC], 0
    mov word ptr [UnpackMode], 0
    mov ax, word ptr [bp + 6]
    mov dx, word ptr [bp + 8]
    mov word ptr [UnpackInputOffset], ax
    mov word ptr [UnpackInputSegment], dx
    mov ax, word ptr [bp + 0Ah]
    and ax, ax
    jns UnpackInit_0038
    mov ax, 7FFFh
UnpackInit_0038:
    mov word ptr [UnpackReadCount], ax
    pop di
    pop bp
    retf
_UnpackInit ENDP

_Unpack PROC FAR
    push bp
    mov bp, sp
    sub sp, 4
    push di
    push si
    mov word ptr [bp - 2], 0
    mov bx, word ptr [UnpackRingPointer]
    mov dx, word ptr [UnpackStateCE]
    mov cx, word ptr [UnpackStateD0]
    push ds
    mov ax, word ptr [UnpackPackBufferSegment]
    mov word ptr [bp - 4], ax
    mov ax, word ptr [UnpackStateCC]
    les di, [bp + 6]
    lds si, DWORD PTR [UnpackInputOffset]
    cmp word ptr ss:[UnpackMode], 0
    je Unpack_0060
    dec word ptr ss:[UnpackMode]
    je Unpack_0067
    dec word ptr ss:[UnpackMode]
    je Unpack_0075
    dec word ptr ss:[UnpackMode]
    je Unpack_009E
    dec word ptr ss:[UnpackMode]
    je Unpack_00A8
    mov ds, word ptr [bp - 4]
    ASSUME DS:PACK
    jmp NEAR PTR Unpack_00F0
Unpack_0054:
    mov di, 1
    jmp NEAR PTR Unpack_0111
Unpack_005A:
    mov di, 2
    jmp NEAR PTR Unpack_0111
Unpack_0060:
    shr ax, 1
    test ah, 1
    jne Unpack_0071
Unpack_0067:
    dec word ptr ss:[UnpackReadCount]
    js Unpack_0054
    lodsb
    mov ah, 0FFh
Unpack_0071:
    test al, 1
    je Unpack_009E
Unpack_0075:
    dec word ptr ss:[UnpackReadCount]
    js Unpack_005A
    mov dl, [si]
    inc si
    mov byte ptr es:[di], dl
    inc di
    mov ds, word ptr [bp - 4]
    ASSUME DS:PACK
    mov [bx + _pack_buf], dl
    mov ds, word ptr ss:[UnpackInputSegment]
    ASSUME DS:NOTHING
    inc bx
    and bx, 0FFFh
    inc word ptr [bp - 2]
    dec word ptr [bp + 0Ah]
    je Unpack_010E
    jmp SHORT Unpack_0060
Unpack_009E:
    dec word ptr ss:[UnpackReadCount]
    js Unpack_0104
    mov cl, [si]
    inc si
Unpack_00A8:
    dec word ptr ss:[UnpackReadCount]
    js Unpack_00FF
    mov dl, [si]
    inc si
    mov ch, dl
    shr ch, 1
    shr ch, 1
    shr ch, 1
    shr ch, 1
    and dl, 0Fh
    add dl, byte ptr ss:[_pack_threshold]
    xor dh, dh
    mov word ptr ss:[UnpackCopyRemaining], dx
    mov ds, word ptr [bp - 4]
    ASSUME DS:PACK
Unpack_00CE:
    xchg bx, cx
    mov dl, [bx + _pack_buf]
    inc bx
    and bx, 0FFFh
    mov byte ptr es:[di], dl
    inc di
    xchg bx, cx
    mov [bx + _pack_buf], dl
    inc bx
    and bx, 0FFFh
    inc word ptr [bp - 2]
    dec word ptr [bp + 0Ah]
    je Unpack_0109
Unpack_00F0:
    dec word ptr ss:[UnpackCopyRemaining]
    jns Unpack_00CE
    mov ds, word ptr ss:[UnpackInputSegment]
    ASSUME DS:NOTHING
    jmp NEAR PTR Unpack_0060
Unpack_00FF:
    mov di, 4
    jmp SHORT Unpack_0111
Unpack_0104:
    mov di, 3
    jmp SHORT Unpack_0111
Unpack_0109:
    mov di, 5
    jmp SHORT Unpack_0111
Unpack_010E:
    mov di, 0
Unpack_0111:
    pop ds
    mov word ptr [UnpackMode], di
    mov word ptr [UnpackStateCC], ax
    mov word ptr [UnpackRingPointer], bx
    mov word ptr [UnpackInputOffset], si
    mov word ptr [UnpackStateCE], dx
    mov word ptr [UnpackStateD0], cx
    mov ax, word ptr [bp - 2]
    pop si
    pop di
    mov sp, bp
    pop bp
    retf
_Unpack ENDP

_UnpackSetBuf PROC FAR
    push bp
    mov bp, sp
    les bx, [bp + 6]
    mov word ptr [UnpackBufferOffset], bx
    mov word ptr [UnpackBufferSegment], es
    mov ax, word ptr [bp + 0Ah]
    mov word ptr [UnpackBufferCapacity], ax
    pop bp
    retf
_UnpackSetBuf ENDP

_UnpackFileOpen PROC FAR
    push bp
    mov bp, sp
    les bx, [bp + 6]
    mov ax, 8000h
    push ax
    push es
    push bx
    call FAR PTR _open
    add sp, 6
    mov word ptr _unpackHandle, ax
    and ax, ax
    jg UnpackFileOpen_0020
    mov ax, 0
    jmp SHORT UnpackFileOpen_0037
UnpackFileOpen_0020:
    mov ax, word ptr [UnpackBufferOffset]
    mov dx, word ptr [UnpackBufferSegment]
    xor bx, bx
    push bx
    push dx
    push ax
    nop
    push cs
    call NEAR PTR _UnpackInit
    add sp, 6
    mov ax, 1
UnpackFileOpen_0037:
    pop bp
    retf
_UnpackFileOpen ENDP

_UnpackFileRead PROC FAR
    push bp
    mov bp, sp
    sub sp, 2
    xor ax, ax
    mov word ptr [bp - 2], ax
    cmp word ptr [UnpackReadCount], ax
    jg UnpackFileRead_0036
UnpackFileRead_0011:
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
    jle UnpackFileRead_005C
    mov word ptr [UnpackReadCount], ax
UnpackFileRead_0036:
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
    jne UnpackFileRead_0011
    jmp SHORT UnpackFileRead_005F
UnpackFileRead_005C:
    mov ax, word ptr [bp - 2]
UnpackFileRead_005F:
    mov sp, bp
    pop bp
    retf
_UnpackFileRead ENDP
_UnpackFileClose PROC FAR
    push word ptr _unpackHandle
    call FAR PTR _close
    pop ax
    retf
_UnpackFileClose ENDP
SIMTWO_MODULE ENDS
END
