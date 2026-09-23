# Recovery task _CopyMaskBitmap2

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 496 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 pushaw 
0004 push ds
0005 push es
0006 test word ptr [bp + 0x16], 0x8000
000b je 0xb12d
000d mov ax, word ptr [bp + 0x16]
0010 neg ax
0012 mov word ptr [0xbb08], ax
0015 mov ax, word ptr [bp + 0x14]
0018 mov word ptr [0xbb0a], ax
001b jmp 0xb15a
001d mov ax, word ptr [bp + 0x16]
0020 cmp ax, word ptr [bp + 0x10]
0023 jl 0xb138
0025 jmp 0xb2fb
0028 mov word ptr [0xbb08], 0
002e mov ax, word ptr [bp + 0x16]
0031 add ax, word ptr [bp + 0x14]
0034 cmp ax, word ptr [bp + 0x10]
0037 jle 0xb154
0039 mov ax, word ptr [bp + 0x10]
003c sub ax, word ptr [bp + 0x16]
003f mov word ptr [0xbb0a], ax
0042 jmp 0xb15a
0044 mov ax, word ptr [bp + 0x14]
0047 mov word ptr [0xbb0a], ax
004a test word ptr [bp + 0x18], 0x8000
004f je 0xb171
0051 mov ax, word ptr [bp + 0x18]
0054 neg ax
0056 mov word ptr [0xbb0c], ax
0059 mov ax, word ptr [bp + 0x12]
005c mov word ptr [0xbb0e], ax
005f jmp 0xb19e
0061 mov ax, word ptr [bp + 0x18]
0064 cmp ax, word ptr [bp + 0xe]
0067 jl 0xb17c
0069 jmp 0xb2fb
006c mov word ptr [0xbb0c], 0
0072 mov ax, word ptr [bp + 0x18]
0075 add ax, word ptr [bp + 0x12]
0078 cmp ax, word ptr [bp + 0xe]
007b jle 0xb198
007d mov ax, word ptr [bp + 0xe]
0080 sub ax, word ptr [bp + 0x18]
0083 mov word ptr [0xbb0e], ax
0086 jmp 0xb19e
0088 mov ax, word ptr [bp + 0x12]
008b mov word ptr [0xbb0e], ax
008e mov ax, word ptr [0xbb08]
0091 shr ax, 1
0093 mov word ptr [0xbb08], ax
0096 mov ax, word ptr [0xbb0a]
0099 shr ax, 1
009b mov word ptr [0xbb0a], ax
009e mov ax, word ptr [bp + 0x10]
00a1 shl ax, 2
00a4 add ax, 0x1f
00a7 shr ax, 5
00aa shl ax, 2
00ad mov word ptr [0xbb10], ax
00b0 mov ax, word ptr [bp + 0x14]
00b3 shl ax, 2
00b6 add ax, 0x1f
00b9 shr ax, 5
00bc shl ax, 2
00bf mov word ptr [0xbb12], ax
00c2 les di, ptr [bp + 0xa]
00c5 mov ax, word ptr [0xbb0c]
00c8 mul word ptr [0xbb12]
00cc add di, ax
00ce cmp dx, 0
00d1 je 0xb1ed
00d3 mov ax, es
00d5 add <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 114}}]
00d8 dec dx
00d9 jne 0xb1e5
00db mov es, ax
00dd mov ax, es
00df mov word ptr [0xbb1a], ax
00e2 mov word ptr [0xbb18], di
00e6 les di, ptr [bp + 6]
00e9 mov bx, word ptr [bp + 0x16]
00ec test bx, 0x8000
00f0 je 0xb20c
00f2 neg bx
00f4 shr bx, 1
00f6 neg bx
00f8 xor bx, bx
00fa jmp 0xb20e
00fc shr bx, 1
00fe mov ax, word ptr [bp + 0x18]
0101 add ax, word ptr [0xbb0c]
0105 mul word ptr [0xbb10]
0109 add ax, bx
010b add di, ax
010d cmp dx, 0
0110 je 0xb22c
0112 mov ax, es
0114 add <resolved loader operand; see bindings> ; [{'operand_offset': 277, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 114}}]
0117 dec dx
0118 jne 0xb224
011a mov es, ax
011c mov ax, es
011e mov word ptr [0xbb16], ax
0121 mov word ptr [0xbb14], di
0125 mov cx, word ptr [0xbb0c]
0129 mov bx, word ptr [0xbb08]
012d push word ptr [0xbb14]
0131 les di, ptr [0xbb18]
0135 mov ah, byte ptr es:[bx + di]
0138 mov al, 0xdd
013a test word ptr [bp + 0x16], 1
013f je 0xb254
0141 ror ax, 4
0144 les di, ptr [0xbb14]
0148 cmp ah, 0xdd
014b je 0xb287
014d xor dh, dh
014f mov dl, ah
0151 and dl, 0xf
0154 cmp dl, 0xd
0157 jne 0xb271
0159 or dh, 0xf
015c and ah, 0xf0
015f jmp 0xb281
0161 mov dl, ah
0163 and dl, 0xf0
0166 cmp dl, 0xd0
0169 jne 0xb281
016b or dh, 0xf0
016e and ah, 0xf
0171 and byte ptr es:[di], dh
0174 or byte ptr es:[di], ah
0177 cmp al, 0xdd
0179 je 0xb2b5
017b xor dh, dh
017d mov dl, al
017f and dl, 0xf
0182 cmp dl, 0xd
0185 jne 0xb29e
0187 or dh, 0xf
018a and al, 0xf0
018c jmp 0xb2ad
018e mov dl, al
0190 and dl, 0xf0
0193 cmp dl, 0xd0
0196 jne 0xb2ad
0198 or dh, 0xf0
019b and al, 0xf
019d and byte ptr es:[di + 1], dh
01a1 or byte ptr es:[di + 1], al
01a5 inc word ptr [0xbb14]
01a9 inc bx
01aa cmp bx, word ptr [0xbb0a]
01ae jl 0xb241
01b0 pop di
01b1 add di, word ptr [0xbb10]
01b5 jae 0xb2ce
01b7 mov ax, es
01b9 add <resolved loader operand; see bindings> ; [{'operand_offset': 442, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 114}}]
01bc mov es, ax
01be mov ax, es
01c0 mov word ptr [0xbb16], ax
01c3 mov word ptr [0xbb14], di
01c7 les di, ptr [0xbb18]
01cb add di, word ptr [0xbb12]
01cf jae 0xb2e8
01d1 mov ax, es
01d3 add <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 114}}]
01d6 mov es, ax
01d8 mov ax, es
01da mov word ptr [0xbb1a], ax
01dd mov word ptr [0xbb18], di
01e1 inc cx
01e2 cmp cx, word ptr [0xbb0e]
01e6 jge 0xb2fb
01e8 jmp 0xb239
01eb pop es
01ec pop ds
01ed popaw 
01ee pop bp
01ef retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawChar', 'offset': 45107, 'source': None, 'size': 188}
- {'symbol': '_ClearBuffer', 'offset': 45295, 'source': None, 'size': 32}
- {'symbol': '_gr_JustifyStrInRect', 'offset': 45824, 'source': None, 'size': 234}
- {'symbol': '_win_SetColorNum', 'offset': 46058, 'source': None, 'size': 87}
