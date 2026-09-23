# Recovery task _UpdateListBox

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 461 bytes.

```asm
0000 enter 0x108, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 push 0x194
000c push 0xb
000e push 0
0010 push 0
0012 push 0
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
0019 mov bx, 0x94a0
001c mov <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
001f mov word ptr [bp - 0x106], bx
0023 mov word ptr [bp - 0x104], ax
0027 mov dx, ax
0029 mov di, bx
002b lea si, [bp - 0x102]
002f mov es, ax
0031 push ds
0032 mov cx, 0xffff
0035 xor ax, ax
0037 repne scasb al, byte ptr es:[di]
0039 not cx
003b sub di, cx
003d xchg si, di
003f push ds
0040 push es
0041 pop ds
0042 pop es
0043 shr cx, 1
0045 rep movsw word ptr es:[di], word ptr [si]
0047 adc cx, cx
0049 rep movsb byte ptr es:[di], byte ptr [si]
004b pop ds
004c mov ax, word ptr [bp + 8]
004f xor ax, 0xc010
0052 je 0x8edd
0054 mov bx, 0x9f10
0057 mov <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
005a mov di, bx
005c lea si, [bp - 0x102]
0060 mov es, ax
0062 push ds
0063 mov cx, 0xffff
0066 xor ax, ax
0068 repne scasb al, byte ptr es:[di]
006a not cx
006c sub di, cx
006e mov bx, cx
0070 xchg si, di
0072 push ds
0073 push es
0074 pop ds
0075 pop es
0076 mov cx, 0xffff
0079 repne scasb al, byte ptr es:[di]
007b dec di
007c mov cx, bx
007e shr cx, 1
0080 rep movsw word ptr es:[di], word ptr [si]
0082 adc cx, cx
0084 rep movsb byte ptr es:[di], byte ptr [si]
0086 pop ds
0087 push word ptr [bp + 6]
008a lea ax, [bp - 0x102]
008e push ss
008f push ax
0090 push 0x194
0093 push 0x193
0096 push word ptr [bp + 8]
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 100}}]
009e push 0x3a
00a0 push word ptr [bp - 0x104]
00a4 push word ptr [bp - 0x106]
00a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 171, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
00ad add sp, 6
00b0 or dx, ax
00b2 jne 0x8f21
00b4 push word ptr [bp + 6]
00b7 push <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ba push 0x9f10
00bd push 0x194
00c0 push 0x193
00c3 push word ptr [bp + 8]
00c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 100}}]
00cb push word ptr [bp + 6]
00ce push 0x194
00d1 push 0x40a
00d4 push 0
00d6 lea ax, [bp - 0x102]
00da push ss
00db push ax
00dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
00e1 push word ptr [bp + 6]
00e4 push 0x194
00e7 push 0x40c
00ea push 0
00ec push 0
00ee push 0
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 241, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
00f5 mov di, ax
00f7 or di, di
00f9 jle 0x8fc4
00fb cmp byte ptr [bp - 0x102], 0x5b
0100 je 0x8fc4
0102 push word ptr [bp + 6]
0105 push 0x194
0108 push 0xb
010a push 0
010c push 0
010e push 0
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
0115 lea ax, [di - 1]
0118 mov word ptr [bp - 0x108], ax
011c mov si, word ptr [bp + 6]
011f mov word ptr [bp - 2], di
0122 push si
0123 push 0x194
0126 push 0x40a
0129 push word ptr [bp - 0x108]
012d lea ax, [bp - 0x102]
0131 push ss
0132 push ax
0133 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 308, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
0138 cmp byte ptr [bp - 0x102], 0x5b
013d jne 0x8fbd
013f push si
0140 push 0x194
0143 push 0x403
0146 push word ptr [bp - 0x108]
014a push 0
014c push 0
014e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
0153 push si
0154 push 0x194
0157 push 0x402
015a push 0
015c lea ax, [bp - 0x102]
0160 push ss
0161 push ax
0162 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 355, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
0167 cmp byte ptr [bp - 0x102], 0x5b
016c je 0x8f78
016e push word ptr [bp + 6]
0171 push 0x194
0174 push 0xb
0176 push 1
0178 push 0
017a push 0
017c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 381, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 101}}]
0181 push word ptr [bp + 6]
0184 push 0x194
0187 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 392, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 91}}]
018c push ax
018d push 0
018f push 0
0191 push 1
0193 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 404, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0198 push ds
0199 push 0x16cc
019c push word ptr [bp - 0x104]
01a0 push word ptr [bp - 0x106]
01a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strstr
01a9 add sp, 8
01ac or dx, ax
01ae je 0x900e
01b0 les bx, ptr [bp - 0x106]
01b4 mov byte ptr es:[bx], 0
01b8 push word ptr [bp + 6]
01bb push 0x191
01be push <resolved loader operand; see bindings> ; [{'operand_offset': 447, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01c1 push 0x9f10
01c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 453, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 92}}]
01c9 pop si
01ca pop di
01cb leave 
01cc retf 
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

- {'symbol': '_clip_ToRect', 'offset': 36434, 'source': 'src/recovered/clip_ToRect.c', 'size': 1}
- {'symbol': '_clip_ToObj', 'offset': 36436, 'source': 'src/recovered/clip_ToObj.c', 'size': 1}
- {'symbol': '_SeparateFile', 'offset': 36900, 'source': 'src/recovered/wf_SeparateFile-7ddbb3ac46.c', 'size': 184}
- {'symbol': '_ChangeDirectory', 'offset': 37084, 'source': None, 'size': 364}
