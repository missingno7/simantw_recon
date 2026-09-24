# Recovery task OPENDLG

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 667 bytes.

```asm
0000 mov ax, ss
0002 enter 0x20e, 0
0006 push di
0007 push si
0008 push ds
0009 mov ds, ax
000b mov ax, word ptr [bp + 0xc]
000e sub ax, 0x110
0011 je 0x9262
0013 dec ax
0014 je 0x92a6
0016 jmp 0x94da
0019 nop 
001a mov si, word ptr [bp + 0xe]
001d push 0x4010
0020 push si
0021 nop 
0022 push cs
0023 call 0x8e56 ; _UpdateListBox
0026 add sp, 4
0029 push si
002a push 0x191
002d push <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0030 push 0x9f10
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 92}}]
0038 push si
0039 push 0x191
003c push 0x401
003f push 0
0041 push 0x7fff
0044 push 0
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
004b push si
004c push 0x191
004f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 91}}]
0054 push ax
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 22}}]
005a jmp 0x94da
005d nop 
005e mov ax, word ptr [bp + 0xa]
0061 dec ax
0062 jne 0x92af
0064 jmp 0x9348
0067 dec ax
0068 je 0x92ba
006a sub ax, 0x192
006d je 0x92c8
006f jmp 0x94da
0072 push word ptr [bp + 0xe]
0075 push 0
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 120, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 88}}]
007c jmp 0x94da
007f nop 
0080 mov ax, word ptr [bp + 8]
0083 dec ax
0084 je 0x92d4
0086 dec ax
0087 je 0x9348
0089 jmp 0x9342
008b nop 
008c push word ptr [bp + 0xe]
008f lea ax, [bp - 0x106]
0093 push ss
0094 push ax
0095 push 0x194
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 99}}]
009d or ax, ax
009f je 0x931c
00a1 mov bx, 0x9f10
00a4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00a7 mov di, bx
00a9 lea si, [bp - 0x106]
00ad mov es, ax
00af push ds
00b0 mov cx, 0xffff
00b3 xor ax, ax
00b5 repne scasb al, byte ptr es:[di]
00b7 not cx
00b9 sub di, cx
00bb mov bx, cx
00bd xchg si, di
00bf push ds
00c0 push es
00c1 pop ds
00c2 pop es
00c3 mov cx, 0xffff
00c6 repne scasb al, byte ptr es:[di]
00c8 dec di
00c9 mov cx, bx
00cb shr cx, 1
00cd rep movsw word ptr es:[di], word ptr [si]
00cf adc cx, cx
00d1 rep movsb byte ptr es:[di], byte ptr [si]
00d3 pop ds
00d4 push word ptr [bp + 0xe]
00d7 push 0x191
00da lea ax, [bp - 0x106]
00de push ss
00df push ax
00e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 92}}]
00e5 push word ptr [bp + 0xe]
00e8 push 0x191
00eb push 0x401
00ee push 0
00f0 push 0x7fff
00f3 push 0
00f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 246, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
00fa mov ax, 1
00fd jmp 0x94dc
0100 push word ptr [bp + 0xe]
0103 push 0x191
0106 mov ax, 0x93a0
0109 mov <resolved loader operand; see bindings> ; [{'operand_offset': 266, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
010c mov word ptr [bp - 0x20a], ax
0110 mov word ptr [bp - 0x208], cx
0114 push cx
0115 push ax
0116 push 0x80
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 93}}]
011e mov es, word ptr [0xc170]
0122 mov byte ptr es:[0x941f], 0
0128 push 0x2a
012a push word ptr [bp - 0x208]
012e push word ptr [bp - 0x20a]
0132 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 309, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
0137 add sp, 6
013a or dx, ax
013c jne 0x93a2
013e push 0x3f
0140 push word ptr [bp - 0x208]
0144 push word ptr [bp - 0x20a]
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
014d add sp, 6
0150 or dx, ax
0152 jne 0x93a2
0154 xor si, si
0156 jmp 0x94a7
0159 nop 
015a push word ptr [bp - 0x208]
015e push word ptr [bp - 0x20a]
0162 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 355, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
0167 mov bx, ax
0169 add bx, 0x93a0
016d mov es, word ptr [0xc170]
0171 mov si, bx
0173 mov word ptr [bp - 4], es
0176 cmp byte ptr es:[bx], 0x3a
017a je 0x93ef
017c cmp byte ptr es:[si], 0x5c
0180 je 0x93ef
0182 mov ax, si
0184 cmp ax, 0x93a0
0187 jbe 0x93ef
0189 push word ptr [bp - 0x208]
018d push word ptr [bp - 0x20a]
0191 push es
0192 push si
0193 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 404, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 473}}]
0198 mov es, dx
019a mov bx, ax
019c mov si, ax
019e mov word ptr [bp - 4], es
01a1 cmp byte ptr es:[bx], 0x3a
01a5 jne 0x93c4
01a7 mov es, word ptr [bp - 4]
01aa cmp byte ptr es:[si], 0x3a
01ae je 0x9418
01b0 cmp byte ptr es:[si], 0x5c
01b4 je 0x9418
01b6 push <resolved loader operand; see bindings> ; [{'operand_offset': 439, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01b9 push 0x9f10
01bc push word ptr [bp - 0x208]
01c0 push word ptr [bp - 0x20a]
01c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 453, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
01c9 mov byte ptr [bp - 0x206], 0
01ce jmp 0x9462
01d0 push <resolved loader operand; see bindings> ; [{'operand_offset': 465, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01d3 push 0x9f10
01d6 mov cx, es
01d8 mov word ptr [bp - 0x20e], si
01dc mov word ptr [bp - 0x20c], cx
01e0 inc si
01e1 push cx
01e2 push si
01e3 mov di, es
01e5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 486, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
01ea mov es, di
01ec mov al, byte ptr es:[si]
01ef mov byte ptr [bp - 1], al
01f2 lea ax, [bp - 0x206]
01f6 push ss
01f7 push ax
01f8 push word ptr [bp - 0x208]
01fc push word ptr [bp - 0x20a]
0200 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 513, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 88}}]
0205 mov al, byte ptr [bp - 1]
0208 mov es, di
020a mov byte ptr es:[si], al
020d mov si, word ptr [bp - 0x20e]
0211 sub si, 0x93a0
0215 mov byte ptr [bp + si - 0x205], 0
021a cmp byte ptr [bp - 0x206], 0
021f je 0x9496
0221 mov bx, 0x94a0
0224 mov <resolved loader operand; see bindings> ; [{'operand_offset': 549, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0227 push ds
0228 lea di, [bp - 0x206]
022c mov si, bx
022e mov cx, ss
0230 mov es, cx
0232 mov ds, ax
0234 mov cx, 0xffff
0237 xor ax, ax
0239 repne scasb al, byte ptr es:[di]
023b not cx
023d sub di, cx
023f xchg si, di
0241 push ds
0242 push es
0243 pop ds
0244 pop es
0245 shr cx, 1
0247 rep movsw word ptr es:[di], word ptr [si]
0249 adc cx, cx
024b rep movsb byte ptr es:[di], byte ptr [si]
024d pop ds
024e push 0x4010
0251 push word ptr [bp + 0xe]
0254 nop 
0255 push cs
0256 call 0x8e56 ; _UpdateListBox
0259 add sp, 4
025c mov si, 1
025f or si, si
0261 je 0x94ae
0263 jmp 0x9342
0266 les bx, ptr [bp - 0x20a]
026a cmp byte ptr es:[bx], 0
026e jne 0x94cc
0270 mov di, word ptr [bp + 0xe]
0273 push di
0274 push ds
0275 push 0x16cf
0278 push si
0279 push si
027a push 0x10
027c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 637, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
0281 jmp 0x9342
0284 mov di, word ptr [bp + 0xe]
0287 push di
0288 push 1
028a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 651, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 88}}]
028f jmp 0x9342
0292 xor ax, ax
0294 pop ds
0295 pop si
0296 pop di
0297 leave 
0298 retf 0xa
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SeparateFile', 'offset': 36900, 'source': 'src/recovered/wf_SeparateFile-7ddbb3ac46.c', 'size': 184}
- {'symbol': '_ChangeDirectory', 'offset': 37084, 'source': None, 'size': 364}
- {'symbol': 'SAVEASDLG', 'offset': 38116, 'source': None, 'size': 1083}
- {'symbol': '_FileSelect', 'offset': 39200, 'source': None, 'size': 970}
