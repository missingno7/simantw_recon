# Recovery task _InitPalette

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 718 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 cmp word ptr [0x85a], 0 ; _paletteH
000b je 0x494e
000d jmp 0x4c08
0010 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 286}}]
0015 push ax
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 66}}]
001b mov word ptr [bp - 0x14], ax
001e push ax
001f push 0xc
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
0026 push word ptr [bp - 0x14]
0029 push 0xe
002b mov si, ax
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
0032 imul si
0034 cdq 
0035 mov word ptr [bp - 8], ax
0038 mov word ptr [bp - 6], dx
003b or dx, ax
003d jne 0x498a
003f mov word ptr [bp - 0xc], 1
0044 mov word ptr [bp - 0xa], 0
0049 jmp 0x49d9
004b nop 
004c mov ax, 1
004f cdq 
0050 mov word ptr [bp - 0x12], ax
0053 mov word ptr [bp - 0x10], dx
0056 mov word ptr [bp - 0xe], ax
0059 mov word ptr [bp - 0xc], dx
005c cmp word ptr [bp - 6], 0
0060 jne 0x49a5
0062 cmp word ptr [bp - 8], ax
0065 jb 0x49cd
0067 mov ax, word ptr [bp - 8]
006a mov dx, word ptr [bp - 6]
006d mov word ptr [bp - 4], ax
0070 mov word ptr [bp - 2], dx
0073 mov di, ax
0075 mov word ptr [bp - 0xa], dx
0078 neg di
007a neg di
007c adc word ptr [bp - 0xa], -1
0080 mov si, word ptr [bp - 0xa]
0083 shl word ptr [bp - 0x12], 1
0086 rcl word ptr [bp - 0x10]
0089 dec di
008a jne 0x49c1
008c dec si
008d jns 0x49c1
008f mov ax, word ptr [bp - 0x12]
0092 mov dx, word ptr [bp - 0x10]
0095 mov word ptr [bp - 0xc], ax
0098 mov word ptr [bp - 0xa], dx
009b cmp word ptr [bp - 0xa], 0
009f jne 0x49e8
00a1 cmp word ptr [bp - 0xc], 0x14
00a5 ja 0x49e8
00a7 jmp 0x4b7e
00aa push word ptr [bp - 0x14]
00ad push 0x26
00af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
00b4 test ah, 1
00b7 jne 0x49fa
00b9 jmp 0x4b7e
00bc sub word ptr [bp - 0xc], 0x14
00c0 sbb word ptr [bp - 0xa], 0
00c4 mov ax, word ptr [bp - 0xc]
00c7 mov cx, ax
00c9 add ax, 2
00cc shl ax, 2
00cf push ax
00d0 push 1
00d2 mov si, cx
00d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 215, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _calloc
00d9 add sp, 4
00dc mov es, dx
00de mov bx, ax
00e0 mov di, ax
00e2 mov word ptr [bp - 0xe], es
00e5 mov word ptr es:[bx], 0x300
00ea mov word ptr es:[bx + 2], si
00ee mov word ptr [bp - 2], 0
00f3 mov word ptr [bp - 0x10], di
00f6 or si, si
00f8 jle 0x4a78
00fa lea ax, [di + 4]
00fd mov si, ax
00ff mov ds, dx
0101 mov di, word ptr [bp - 2]
0104 mov <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0107 mov es, ax
0109 mov ax, di
010b mov cx, 0xf
010e cdq 
010f idiv cx
0111 mov bx, dx
0113 shl bx, 2
0116 mov al, byte ptr es:[bx - 0x73c0]
011b mov byte ptr [si], al
011d mov al, byte ptr es:[bx - 0x73bf]
0122 mov byte ptr [si + 1], al
0125 mov al, byte ptr es:[bx - 0x73be]
012a mov byte ptr [si + 2], al
012d mov byte ptr [si + 3], 4
0131 add si, 4
0134 inc di
0135 cmp word ptr [bp - 0xc], di
0138 jg 0x4a47
013a mov word ptr [bp - 2], 0
013f mov di, 0x8c7c
0142 mov ax, word ptr [bp - 0x10]
0145 mov dx, word ptr [bp - 0xe]
0148 add ax, 4
014b mov si, ax
014d mov word ptr [bp - 6], dx
0150 mov word ptr [bp - 4], 0x8c40
0155 mov cx, word ptr [bp - 4]
0158 mov <resolved loader operand; see bindings> ; [{'operand_offset': 345, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
015b mov es, ax
015d mov bx, cx
015f mov al, byte ptr es:[bx]
0162 mov ds, word ptr [bp - 6]
0165 mov byte ptr [si], al
0167 mov al, byte ptr es:[bx + 1]
016b mov byte ptr [si + 1], al
016e mov al, byte ptr es:[bx + 2]
0172 mov byte ptr [si + 2], al
0175 mov byte ptr [si + 3], 4
0179 mov al, byte ptr es:[di]
017c mov bx, word ptr [bp - 0xc]
017f sub bx, word ptr [bp - 2]
0182 shl bx, 2
0185 mov ds, word ptr [bp - 0xe]
0188 add bx, word ptr [bp - 0x10]
018b mov byte ptr [bx], al
018d mov al, byte ptr es:[di + 1]
0191 mov byte ptr [bx + 1], al
0194 mov al, byte ptr es:[di + 2]
0198 mov byte ptr [bx + 2], al
019b mov byte ptr [bx + 3], 4
019f sub di, 4
01a2 add si, 4
01a5 inc word ptr [bp - 2]
01a8 add cx, 4
01ab cmp cx, 0x8c80
01af jb 0x4a9b
01b1 push ss
01b2 pop ds
01b3 cmp word ptr [bp - 0xa], 0
01b7 jne 0x4b00
01b9 cmp word ptr [bp - 0xc], 0x20
01bd jae 0x4b00
01bf jmp 0x4bde
01c2 mov word ptr [bp - 2], 0
01c7 mov di, 0x8c3c
01ca mov ax, word ptr [bp - 0x10]
01cd mov dx, word ptr [bp - 0xe]
01d0 add ax, 0x44
01d3 mov si, ax
01d5 mov word ptr [bp - 6], dx
01d8 mov word ptr [bp - 4], 0x8c00
01dd mov cx, word ptr [bp - 4]
01e0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 481, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01e3 mov ds, ax
01e5 mov bx, cx
01e7 mov al, byte ptr [bx]
01e9 mov es, word ptr [bp - 6]
01ec mov byte ptr es:[si], al
01ef mov al, byte ptr [bx + 1]
01f2 mov byte ptr es:[si + 1], al
01f6 mov al, byte ptr [bx + 2]
01f9 mov byte ptr es:[si + 2], al
01fd mov byte ptr es:[si + 3], 4
0202 mov al, byte ptr [di]
0204 mov bx, word ptr [bp - 0xc]
0207 sub bx, word ptr [bp - 2]
020a shl bx, 2
020d mov es, word ptr [bp - 0xe]
0210 add bx, word ptr [bp - 0x10]
0213 mov byte ptr es:[bx - 0x40], al
0217 mov al, byte ptr [di + 1]
021a mov byte ptr es:[bx - 0x3f], al
021e mov al, byte ptr [di + 2]
0221 mov byte ptr es:[bx - 0x3e], al
0225 mov byte ptr es:[bx - 0x3d], 4
022a sub di, 4
022d add si, 4
0230 inc word ptr [bp - 2]
0233 add cx, 4
0236 cmp cx, 0x8c40
023a jb 0x4b23
023c push ss
023d pop ds
023e jmp 0x4bde
0240 push 0x48
0242 push 1
0244 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 583, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _calloc
0249 add sp, 4
024c mov es, dx
024e mov bx, ax
0250 mov di, ax
0252 mov word ptr [bp - 0xe], es
0255 mov word ptr es:[bx], 0x300
025a mov word ptr es:[bx + 2], 0x10
0260 lea ax, [bx + 4]
0263 mov si, ax
0265 mov word ptr [bp - 4], es
0268 mov word ptr [bp - 2], 0x8c40
026d mov word ptr [bp - 0x10], di
0270 mov di, word ptr [bp - 2]
0273 mov ds, word ptr [bp - 4]
0276 mov <resolved loader operand; see bindings> ; [{'operand_offset': 631, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0279 mov es, ax
027b mov al, byte ptr es:[di]
027e mov byte ptr [si], al
0280 mov al, byte ptr es:[di + 1]
0284 mov byte ptr [si + 1], al
0287 mov al, byte ptr es:[di + 2]
028b mov byte ptr [si + 2], al
028e mov byte ptr [si + 3], 4
0292 add si, 4
0295 add di, 4
0298 cmp di, 0x8c80
029c jb 0x4bb9
029e jmp 0x4b7a
02a0 push word ptr [bp - 0xe]
02a3 push word ptr [bp - 0x10]
02a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 679, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 360}}]
02ab mov word ptr [0x85a], ax ; _paletteH
02ae push word ptr [bp - 0xe]
02b1 push word ptr [bp - 0x10]
02b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 695, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _free
02b9 add sp, 4
02bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 701, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 286}}]
02c1 push ax
02c2 push word ptr [bp - 0x14]
02c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 710, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 68}}]
02ca pop si
02cb pop di
02cc leave 
02cd retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void free(void far *block);` — src/recovered/mem_free_wrapper.c
- `extern void far free(void far *block);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int near paletteH;` — src/recovered/ClosePalette.c
- `extern int near paletteH[];` — src/recovered/SetDebugFlag.c
- `extern int near paletteH[];` — src/recovered/mem_Debugging.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetUpPalette', 'offset': 18078, 'source': None, 'size': 565}
- {'symbol': '_MyPow', 'offset': 18644, 'source': 'src/recovered/MyPow.c', 'size': 105}
- {'symbol': '_ClosePalette', 'offset': 19468, 'source': 'src/recovered/ClosePalette.c', 'size': 23}
- {'symbol': '_SetMenuEntries', 'offset': 19492, 'source': 'src/recovered/wf_SetMenuEntries-c937b84870.c', 'size': 158}
