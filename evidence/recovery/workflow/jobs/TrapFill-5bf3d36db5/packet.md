# Recovery task _TrapFill

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 495 bytes.

```asm
0000 enter 0x20, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xa]
0009 cmp di, -1
000c jne 0x529d
000e jmp 0x5368
0011 mov dx, word ptr [bp + 0xc]
0014 cmp dx, -1
0017 jne 0x52a8
0019 jmp 0x5368
001c test byte ptr [0xcc7e], 1 ; _displayType
0021 jne 0x52fe
0023 cmp dx, di
0025 jne 0x52e2
0027 push 0
0029 push 1
002b mov ax, di
002d and ax, 0xf
0030 mov cx, ax
0032 mov dx, 0x100
0035 push dx
0036 push cx
0037 mov di, ax
0039 mov word ptr [bp - 0x1a], dx
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 61}}]
0041 mov si, ax
0043 push word ptr [bp - 0x1a]
0046 push di
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 66}}]
004c mov word ptr [bp - 4], ax
004f mov word ptr [bp - 2], si
0052 mov di, si
0054 jmp 0x5312
0056 push 0
0058 push 1
005a push 0x100
005d push 8
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 61}}]
0064 mov di, ax
0066 push 0x100
0069 push 8
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 66}}]
0070 jmp 0x5312
0072 push 7
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 87}}]
0079 mov di, ax
007b push word ptr [bp + 0xa]
007e nop 
007f push cs
0080 call 0x1902 ; _CreateMonoSolidBrush
0083 add sp, 2
0086 mov si, ax
0088 push word ptr [0xcf52] ; _clipDC
008c push di
008d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 142, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
0092 mov word ptr [bp - 6], ax
0095 push word ptr [0xcf52] ; _clipDC
0099 push si
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 155, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
009f mov word ptr [bp - 8], ax
00a2 push word ptr [0xcf52] ; _clipDC
00a6 push word ptr [bp + 8]
00a9 push word ptr [bp + 6]
00ac push 4
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 36}}]
00b3 push word ptr [0xcf52] ; _clipDC
00b7 push word ptr [bp - 6]
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
00bf push word ptr [0xcf52] ; _clipDC
00c3 push word ptr [bp - 8]
00c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 45}}]
00cb push di
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 205, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
00d1 push si
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 69}}]
00d7 pop si
00d8 pop di
00d9 leave 
00da retf 
00db nop 
00dc les si, ptr [bp + 6]
00df mov ax, word ptr es:[si + 0xa]
00e3 mov word ptr [bp - 0x18], ax
00e6 mov cx, word ptr es:[si]
00e9 mov word ptr [bp - 4], cx
00ec mov dx, word ptr es:[si + 4]
00f0 mov word ptr [bp - 6], dx
00f3 mov bx, word ptr es:[si + 2]
00f7 mov word ptr [bp - 2], bx
00fa sub ax, bx
00fc cdq 
00fd push dx
00fe push ax
00ff sub cx, word ptr es:[si + 0xc]
0103 push cx
0104 push 0
0106 mov di, ax
0108 mov word ptr [bp - 0x20], di
010b mov word ptr [bp - 0x1e], dx
010e mov di, es
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0115 mov word ptr [bp - 0x12], ax
0118 mov word ptr [bp - 0x10], dx
011b push word ptr [bp - 0x1e]
011e push word ptr [bp - 0x20]
0121 mov ax, word ptr [bp - 6]
0124 mov es, di
0126 sub ax, word ptr es:[si + 8]
012a push ax
012b push 0
012d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 304, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0132 mov word ptr [bp - 0x16], ax
0135 mov word ptr [bp - 0x14], dx
0138 mov ax, word ptr [bp - 4]
013b mov word ptr [bp - 0xa], 0
0140 mov word ptr [bp - 8], ax
0143 mov ax, word ptr [bp - 6]
0146 mov word ptr [bp - 0xe], 0
014b mov word ptr [bp - 0xc], ax
014e mov di, word ptr [bp + 0xa]
0151 test byte ptr [0xcc7e], 1 ; _displayType
0156 je 0x53e7
0158 mov di, word ptr [bp + 0xc]
015b push di
015c push word ptr [bp + 0xc]
015f push di
0160 nop 
0161 push cs
0162 call 0x19b4 ; _GSetAttrib
0165 add sp, 6
0168 mov ax, word ptr [bp - 2]
016b cmp word ptr [bp - 0x18], ax
016e jle 0x5477
0170 mov si, ax
0172 mov word ptr [bp + 0xa], di
0175 cmp di, -1
0178 jne 0x541c
017a lea ax, [si + 1]
017d push ax
017e push word ptr [bp - 6]
0181 push si
0182 push word ptr [bp - 4]
0185 nop 
0186 push cs
0187 call 0x1966 ; _GInvBox
018a add sp, 8
018d jmp 0x5449
018f nop 
0190 cmp word ptr [bp + 0xc], di
0193 jne 0x5434
0195 push di
0196 lea ax, [si + 1]
0199 push ax
019a push word ptr [bp - 6]
019d push si
019e push word ptr [bp - 4]
01a1 nop 
01a2 push cs
01a3 call 0x19e6 ; _GBoxFill
01a6 jmp 0x5446
01a8 push 0x20
01aa lea ax, [si + 1]
01ad push ax
01ae push word ptr [bp - 6]
01b1 push si
01b2 push word ptr [bp - 4]
01b5 nop 
01b6 push cs
01b7 call 0x1ab2 ; _GPatBox
01ba add sp, 0xa
01bd mov ax, word ptr [bp - 0x12]
01c0 mov dx, word ptr [bp - 0x10]
01c3 sub word ptr [bp - 0xa], ax
01c6 sbb word ptr [bp - 8], dx
01c9 mov ax, word ptr [bp - 8]
01cc mov word ptr [bp - 4], ax
01cf mov ax, word ptr [bp - 0x16]
01d2 mov dx, word ptr [bp - 0x14]
01d5 sub word ptr [bp - 0xe], ax
01d8 sbb word ptr [bp - 0xc], dx
01db mov ax, word ptr [bp - 0xc]
01de mov word ptr [bp - 6], ax
01e1 lea ax, [si + 1]
01e4 mov si, ax
01e6 cmp si, word ptr [bp - 0x18]
01e9 jl 0x5401
01eb pop si
01ec pop di
01ed leave 
01ee retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern void GInvBox(int,int,int,int);` — src/recovered/GRectInv.c
- `extern void far GInvBox(int a, int b, int c, int d);` — src/recovered/wf_GInvOutline-07520ef33f.c
- `extern void far GInvBox(int x1, int y1, int x2, int y2);` — src/recovered/wf_GRectInvOutline-81f8c3e9d1.c
- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/GCheckerBox.c
- `extern void far GPatBox(int left, int top, int right, int bottom, int pattern);` — src/recovered/GRectChecker.c
- `extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern int near clipDC;` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_GPatBox-b326d1b571.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitMenu', 'offset': 20022, 'source': None, 'size': 790}
- {'symbol': '_ms_PopUpMenuResource', 'offset': 20812, 'source': None, 'size': 320}
- {'symbol': '_mem_Flush', 'offset': 21628, 'source': 'src/recovered/mem_Flush.c', 'size': 10}
- {'symbol': '_mem_Debugging', 'offset': 21638, 'source': 'src/recovered/mem_Debugging.c', 'size': 11}
