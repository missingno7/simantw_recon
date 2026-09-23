# Recovery task _SetUpPalette

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 565 bytes.

```asm
0000 enter 0x4a, 0
0004 push di
0005 push si
0006 cmp word ptr [0xcd78], 0 ; _rootWnd
000b jne 0x46ae
000d jmp 0x48cf
0010 push 0
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 66}}]
0017 mov si, ax
0019 mov es, word ptr [0xbec6]
001d cmp word ptr es:[0x32], 0
0023 jne 0x46c6
0025 jmp 0x4872
0028 push si
0029 push 0xc
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
0030 cmp ax, 8
0033 jl 0x46d6
0035 jmp 0x4872
0038 push si
0039 push 0xe
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
0040 cmp ax, 8
0043 jl 0x46e6
0045 jmp 0x4872
0048 mov word ptr [bp - 6], 4
004d cmp word ptr [bp + 6], 0
0051 jne 0x46f4
0053 jmp 0x4806
0056 push si
0057 push 8
0059 push 2
005b lea ax, [bp - 6]
005e push ss
005f push ax
0060 push 0
0062 push 0
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
0069 or ax, ax
006b jne 0x470e
006d jmp 0x47a8
0070 mov word ptr [bp - 4], 4
0075 push si
0076 push 8
0078 push 2
007a lea ax, [bp - 4]
007d push ss
007e push ax
007f push 0
0081 push 0
0083 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
0088 or ax, ax
008a jne 0x472d
008c jmp 0x47bd
008f mov <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0092 mov ds, ax
0094 mov ax, 0x8c40
0097 mov cx, ds
0099 or cx, ax
009b je 0x479a
009d mov byte ptr [bp - 0x4a], 0
00a1 mov byte ptr [bp - 0x49], 0x10
00a5 mov word ptr [bp - 4], 0
00aa mov word ptr [bp - 2], si
00ad mov bx, word ptr [bp - 4]
00b0 shl bx, 2
00b3 mov al, byte ptr [bx - 0x73be]
00b7 sub ah, ah
00b9 mov dx, ax
00bb mov al, byte ptr [bx - 0x73bf]
00bf mov di, dx
00c1 sub dx, dx
00c3 mov ah, al
00c5 sub al, al
00c7 mov cx, ax
00c9 mov al, byte ptr [bx - 0x73c0]
00cd sub ah, ah
00cf or cx, ax
00d1 mov ax, di
00d3 mov di, bx
00d5 mov word ptr [bp + di - 0x48], cx
00d8 mov word ptr [bp + di - 0x46], ax
00db inc word ptr [bp - 4]
00de cmp word ptr [bp - 4], 0x10
00e2 jl 0x474b
00e4 push ss
00e5 pop ds
00e6 push si
00e7 push 4
00e9 push 0x42
00eb lea ax, [bp - 0x4a]
00ee push ss
00ef push ax
00f0 push 0
00f2 push 0
00f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
00f9 jmp 0x47bd
00fb nop 
00fc push ss
00fd pop ds
00fe push si
00ff push 4
0101 push 0
0103 push 0
0105 push 0
0107 jmp 0x478e
0109 nop 
010a push si
010b push 0x26
010d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
0112 test ah, 1
0115 je 0x47bd
0117 push si
0118 push 2
011a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 373}}]
011f mov word ptr [bp - 6], 0
0124 mov word ptr [bp - 2], si
0127 mov es, word ptr [0xbec8]
012b mov bx, word ptr [bp - 6]
012e shl bx, 1
0130 push word ptr es:[bx - 0x7380]
0135 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 310, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 180}}]
013a mov bx, word ptr [bp - 6]
013d shl bx, 2
0140 mov word ptr [bx - 0x359c], ax
0144 mov word ptr [bx - 0x359a], dx
0148 inc word ptr [bp - 6]
014b cmp word ptr [bp - 6], 0x13
014f jl 0x47c5
0151 push 0x13
0153 push <resolved loader operand; see bindings> ; [{'operand_offset': 340, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0156 push 0x8c80
0159 push <resolved loader operand; see bindings> ; [{'operand_offset': 346, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
015c push 0x8ca6
015f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 352, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 181}}]
0164 jmp 0x48a2
0167 nop 
0168 push si
0169 push 8
016b push 2
016d lea ax, [bp - 6]
0170 push ss
0171 push ax
0172 push 0
0174 push 0
0176 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 375, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
017b or ax, ax
017d je 0x484e
017f mov word ptr [bp - 4], 4
0184 push si
0185 push 8
0187 push 2
0189 lea ax, [bp - 4]
018c push ss
018d push ax
018e push 0
0190 push 0
0192 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
0197 or ax, ax
0199 je 0x4863
019b push si
019c push 4
019e push 0
01a0 push 0
01a2 push 0
01a4 push 0
01a6 push 0
01a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 425, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
01ad jmp 0x4863
01af nop 
01b0 push si
01b1 push 0x26
01b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 436, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 80}}]
01b8 test ah, 1
01bb je 0x4863
01bd push si
01be push 1
01c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 449, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 373}}]
01c5 push 0x13
01c7 push <resolved loader operand; see bindings> ; [{'operand_offset': 456, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01ca push 0x8c80
01cd push ds
01ce push 0xca64
01d1 jmp 0x47fd
01d3 nop 
01d4 mov word ptr [bp - 8], 4
01d9 push si
01da push 8
01dc push 2
01de lea ax, [bp - 8]
01e1 push ss
01e2 push ax
01e3 push 0
01e5 push 0
01e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 488, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
01ec mov word ptr [bp - 8], 5
01f1 push si
01f2 push 8
01f4 push 2
01f6 lea ax, [bp - 8]
01f9 push ss
01fa push ax
01fb push 0
01fd push 0
01ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 512, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 38}}]
0204 nop 
0205 push cs
0206 call 0x493e ; _InitPalette
0209 push si
020a push word ptr [0x85a] ; _paletteH
020e push 0
0210 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 529, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 282}}]
0215 mov di, ax
0217 push word ptr [0x85a] ; _paletteH
021b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 540, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 150}}]
0220 push si
0221 push di
0222 push 0
0224 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 549, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 282}}]
0229 push 0
022b push si
022c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 557, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 68}}]
0231 pop si
0232 pop di
0233 leave 
0234 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void InitPalette(void);` — src/recovered/wf_PaintStuff-4a441706dd.c
- `extern int near paletteH;` — src/recovered/ClosePalette.c
- `extern int near paletteH[];` — src/recovered/SetDebugFlag.c
- `extern int near paletteH[];` — src/recovered/mem_Debugging.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': 'WINMAIN', 'offset': 16346, 'source': None, 'size': 1546}
- {'symbol': '_SetDevicePalette', 'offset': 17892, 'source': None, 'size': 185}
- {'symbol': '_MyPow', 'offset': 18644, 'source': 'src/recovered/MyPow.c', 'size': 105}
- {'symbol': '_InitPalette', 'offset': 18750, 'source': None, 'size': 718}
