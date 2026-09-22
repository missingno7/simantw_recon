# Recovery task _GetMyRandDirs

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 536 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov di, 0xffff
0009 push word ptr [bp + 0x16]
000c push word ptr [bp + 0x14]
000f push word ptr [bp + 0x12]
0012 push word ptr [bp + 0x10]
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
001a add sp, 8
001d mov word ptr [bp - 0xc], ax
0020 or ax, ax
0022 jg 0x894f
0024 jmp 0x8b3a
0027 mov word ptr [bp - 0xa], 0xfffe
002c mov es, word ptr [0xc3ae]
0030 cmp word ptr es:[0x9bc4], 2
0036 jne 0x8966
0038 mov ax, 1
003b jmp 0x8968
003d nop 
003e xor ax, ax
0040 mov word ptr [bp - 4], ax
0043 xor si, si
0045 mov es, word ptr [0xc3c4]
0049 mov al, byte ptr es:[si + 8]
004e cwde 
004f add ax, word ptr [bp + 0x12]
0052 mov word ptr [bp - 2], ax
0055 mov es, word ptr [0xc3ca]
0059 mov al, byte ptr es:[si]
005e cwde 
005f add ax, word ptr [bp + 0x10]
0062 mov word ptr [bp - 6], ax
0065 mov es, word ptr [0xc3c6]
0069 cmp ax, word ptr es:[0xa0d6]
006e jne 0x89a6
0070 mov ax, word ptr [bp - 2]
0073 mov es, word ptr [0xc3c8]
0077 cmp word ptr es:[0xa0da], ax
007c je 0x89e2
007e push word ptr [bp - 4]
0081 mov es, word ptr [0xc3bc]
0085 push word ptr es:[0x80d2]
008a mov es, word ptr [0xc3b8]
008e push word ptr es:[0x80c6]
0093 mov es, word ptr [0xc3be]
0097 push word ptr es:[0x9be0]
009c push word ptr [bp - 2]
009f push word ptr [bp - 6]
00a2 push word ptr [bp + 0xe]
00a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _TileCanBeMovedOn
00aa add sp, 0xe
00ad or ax, ax
00af je 0x89e2
00b1 mov word ptr [bp - 0xa], si
00b4 mov byte ptr [bp + si - 0x14], 1
00b8 jmp 0x89e6
00ba mov byte ptr [bp + si - 0x14], 0
00be inc si
00bf cmp si, 8
00c2 jl 0x896d
00c4 mov di, word ptr [bp - 0xa]
00c7 or di, di
00c9 jge 0x89f6
00cb jmp 0x8b3a
00ce mov word ptr [bp - 0xa], 0xffff
00d3 les bx, ptr [bp + 0xa]
00d6 mov di, word ptr es:[bx]
00d9 mov bx, di
00db les si, ptr [bp + 6]
00de cmp word ptr es:[si], 0
00e2 je 0x8a0f
00e4 jmp 0x8a9a
00e7 xor dx, dx
00e9 cmp byte ptr [bp + di - 0x14], 0
00ed jne 0x8a40
00ef mov si, bx
00f1 cmp byte ptr [bp + si - 0x14], 0
00f5 jne 0x8a6c
00f7 mov ax, di
00f9 inc al
00fb and ax, 7
00fe mov di, ax
0100 mov al, bl
0102 dec al
0104 and ax, 7
0107 mov bx, ax
0109 inc dx
010a cmp dx, 8
010d jl 0x8a11
010f mov di, word ptr [bp - 0xa]
0112 mov ax, di
0114 pop si
0115 pop di
0116 leave 
0117 retf 
0118 mov word ptr [bp - 8], di
011b push word ptr [bp + 0x16]
011e push word ptr [bp + 0x14]
0121 push word ptr [bp + 0x12]
0124 push word ptr [bp + 0x10]
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
012c add sp, 8
012f dec ax
0130 les bx, ptr [bp + 0xa]
0133 mov word ptr es:[bx], ax
0136 les bx, ptr [bp + 6]
0139 mov word ptr es:[bx], 1
013e mov ax, di
0140 pop si
0141 pop di
0142 leave 
0143 retf 
0144 mov word ptr [bp - 2], bx
0147 mov di, bx
0149 push word ptr [bp + 0x16]
014c push word ptr [bp + 0x14]
014f push word ptr [bp + 0x12]
0152 push word ptr [bp + 0x10]
0155 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 344, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
015a add sp, 8
015d dec ax
015e les bx, ptr [bp + 0xa]
0161 mov word ptr es:[bx], ax
0164 les bx, ptr [bp + 6]
0167 mov word ptr es:[bx], 0xffff
016c mov ax, di
016e pop si
016f pop di
0170 leave 
0171 retf 
0172 mov word ptr [bp - 2], bx
0175 mov word ptr [bp - 8], di
0178 mov word ptr [bp - 6], 0
017d mov bx, word ptr [bp + 6]
0180 cmp word ptr es:[bx], 0
0184 jle 0x8aba
0186 mov si, word ptr [bp - 8]
0189 cmp byte ptr [bp + si - 0x14], 0
018d je 0x8ac3
018f jmp 0x8ae6
0191 nop 
0192 mov si, word ptr [bp - 2]
0195 cmp byte ptr [bp + si - 0x14], 0
0199 jne 0x8ae6
019b mov al, byte ptr [bp - 8]
019e inc al
01a0 and ax, 7
01a3 mov word ptr [bp - 8], ax
01a6 mov al, byte ptr [bp - 2]
01a9 dec al
01ab and ax, 7
01ae mov word ptr [bp - 2], ax
01b1 inc word ptr [bp - 6]
01b4 cmp word ptr [bp - 6], 8
01b8 jl 0x8aa5
01ba jmp 0x8a37
01bd nop 
01be push word ptr [bp + 0x16]
01c1 push word ptr [bp + 0x14]
01c4 mov es, word ptr [0xc3c4]
01c8 mov di, si
01ca mov al, byte ptr es:[di + 8]
01cf cwde 
01d0 add ax, word ptr [bp + 0x12]
01d3 push ax
01d4 mov es, word ptr [0xc3ca]
01d8 mov al, byte ptr es:[di]
01dd cwde 
01de add ax, word ptr [bp + 0x10]
01e1 push ax
01e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 485, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
01e7 add sp, 8
01ea cmp ax, word ptr [bp - 0xc]
01ed jg 0x8b3a
01ef push word ptr [bp + 0x16]
01f2 push word ptr [bp + 0x14]
01f5 push word ptr [bp + 0x12]
01f8 push word ptr [bp + 0x10]
01fb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 510, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
0200 add sp, 8
0203 dec ax
0204 les bx, ptr [bp + 0xa]
0207 mov word ptr es:[bx], ax
020a les bx, ptr [bp + 6]
020d mov word ptr es:[bx], 0
0212 mov ax, di
0214 pop si
0215 pop di
0216 leave 
0217 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetMyDis', 'offset': 34434, 'source': None, 'size': 421}
- {'symbol': '_GetMyBestDirs', 'offset': 34856, 'source': None, 'size': 256}
- {'symbol': '_CheckMyBestDirs', 'offset': 35648, 'source': None, 'size': 169}
- {'symbol': '_GetMyNextRandDirs', 'offset': 35818, 'source': None, 'size': 244}
