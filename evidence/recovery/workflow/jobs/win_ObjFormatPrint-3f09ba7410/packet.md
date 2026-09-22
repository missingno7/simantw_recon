# Recovery task _win_ObjFormatPrint

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 552 bytes.

```asm
0000 enter 0x76, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0xe3a8 ; _win_LockWin
000e add sp, 2
0011 mov si, word ptr [bp + 6]
0014 mov bx, si
0016 sar bx, 8
0019 shl bx, 2
001c mov ax, word ptr [bx - 0x3166]
0020 mov dx, word ptr [bx - 0x3164]
0024 mov di, ax
0026 mov word ptr [bp - 6], dx
0029 mov es, dx
002b mov bx, ax
002d mov ax, si
002f sub ah, ah
0031 cmp word ptr es:[bx + 0xc], ax
0035 jg 0xd8f7
0037 push ds
0038 push 0xbd12
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0040 add sp, 4
0043 mov es, word ptr [bp - 6]
0046 mov bx, si
0048 sub bh, bh
004a shl bx, 2
004d add bx, di
004f les bx, ptr es:[bx + 0x2c]
0053 mov word ptr [bp - 4], bx
0056 mov word ptr [bp - 2], es
0059 test byte ptr es:[bx + 0x24], 1
005e jne 0xd917
0060 jmp 0xdacd
0063 lea cx, [bp + 8]
0066 push ss
0067 push cx
0068 mov dx, bx
006a mov bx, es
006c add dx, 0x2e
006f push bx
0070 push dx
0071 lea si, [bp - 0x76]
0074 push ss
0075 push si
0076 mov si, dx
0078 mov di, es
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _vsprintf
007f add sp, 0xc
0082 lea ax, [bp + 8]
0085 push ss
0086 push ax
0087 push di
0088 push si
0089 lea ax, [bp - 0x76]
008c push ss
008d push ax
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _vsprintf
0093 add sp, 0xc
0096 lea di, [bp - 0x76]
0099 mov ax, ss
009b mov es, ax
009d mov cx, 0xffff
00a0 xor ax, ax
00a2 repne scasb al, byte ptr es:[di]
00a4 not cx
00a6 mov word ptr [bp - 6], cx
00a9 les bx, ptr [bp - 4]
00ac mov ax, word ptr es:[bx + 0x2a]
00b0 mov dx, word ptr es:[bx + 0x2c]
00b4 mov si, ax
00b6 mov word ptr [bp - 8], dx
00b9 or dx, ax
00bb je 0xd9c2
00bd mov word ptr [bp - 0xa], si
00c0 mov es, word ptr [bp - 8]
00c3 mov ax, word ptr es:[si]
00c6 mov dx, word ptr es:[si + 2]
00ca mov bx, ax
00cc mov di, ax
00ce mov es, dx
00d0 mov cx, 0xffff
00d3 xor ax, ax
00d5 repne scasb al, byte ptr es:[di]
00d7 not cx
00d9 dec cx
00da add cx, 2
00dd cmp cx, word ptr [bp - 6]
00e0 jge 0xd9e9
00e2 push 1
00e4 mov ax, word ptr [bp - 6]
00e7 add ax, 4
00ea cdq 
00eb push dx
00ec push ax
00ed push word ptr [bp - 8]
00f0 push si
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _RallocRealloc
00f6 add sp, 0xa
00f9 mov si, ax
00fb mov word ptr [bp - 8], dx
00fe les bx, ptr [bp - 4]
0101 mov word ptr es:[bx + 0x2a], ax
0105 mov word ptr es:[bx + 0x2c], dx
0109 mov word ptr [bp - 0xa], si
010c jmp 0xd9e9
010e push ds
010f push 0xbe05
0112 push 1
0114 mov ax, cx
0116 add ax, 8
0119 cdq 
011a push dx
011b push ax
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Ralloc
0121 add sp, 0xa
0124 mov word ptr [bp - 0xa], ax
0127 mov word ptr [bp - 8], dx
012a les bx, ptr [bp - 4]
012d mov word ptr es:[bx + 0x2a], ax
0131 mov word ptr es:[bx + 0x2c], dx
0135 les bx, ptr [bp - 0xa]
0138 mov si, word ptr es:[bx]
013b mov cx, word ptr es:[bx + 2]
013f mov dx, cx
0141 push ds
0142 lea di, [bp - 0x76]
0145 mov cx, ss
0147 mov es, cx
0149 mov ds, dx
014b mov cx, 0xffff
014e xor ax, ax
0150 repne scasb al, byte ptr es:[di]
0152 not cx
0154 sub di, cx
0156 xchg si, di
0158 push ds
0159 push es
015a pop ds
015b pop es
015c shr cx, 1
015e rep movsw word ptr es:[di], word ptr [si]
0160 adc cx, cx
0162 rep movsb byte ptr es:[di], byte ptr [si]
0164 pop ds
0165 les bx, ptr [bp - 4]
0168 mov al, byte ptr es:[bx + 0x28]
016c cwde 
016d push ax
016e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 369, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0173 add sp, 2
0176 mov ax, word ptr [bp + 6]
0179 mov word ptr [bp - 6], ax
017c push ax
017d nop 
017e push cs
017f call 0xb4b2 ; _win_SetColorFromObjNum
0182 add sp, 2
0185 push word ptr [bp - 6]
0188 nop 
0189 push cs
018a call 0xe3a8 ; _win_LockWin
018d add sp, 2
0190 mov bl, byte ptr [bp - 6]
0193 sub bh, bh
0195 shl bx, 2
0198 mov si, word ptr [bp - 6]
019b sar si, 8
019e shl si, 2
01a1 les si, ptr [si - 0x3166]
01a5 mov ax, word ptr es:[bx + si + 0x2c]
01a9 mov dx, word ptr es:[bx + si + 0x2e]
01ad push ds
01ae lea di, [bp - 0x12]
01b1 mov si, ax
01b3 push ss
01b4 pop es
01b5 mov ds, dx
01b7 movsw word ptr es:[di], word ptr [si]
01b8 movsw word ptr es:[di], word ptr [si]
01b9 movsw word ptr es:[di], word ptr [si]
01ba movsw word ptr es:[di], word ptr [si]
01bb pop ds
01bc cmp word ptr [0xbd0a], 0 ; _ribbonBarHeight
01c1 je 0xda7d
01c3 inc word ptr [bp - 0xe]
01c6 inc word ptr [bp - 0xc]
01c9 push word ptr [bp - 6]
01cc nop 
01cd push cs
01ce call 0xe3a4 ; _win_UnlockWin
01d1 add sp, 2
01d4 push word ptr [0xcf52] ; _clipDC
01d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 473, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 30}}]
01dd push word ptr [0xcf52] ; _clipDC
01e1 push word ptr [bp - 0x12]
01e4 push word ptr [bp - 0x10]
01e7 push word ptr [bp - 0xe]
01ea push word ptr [bp - 0xc]
01ed lcall <resolved loader operand; see bindings> ; [{'operand_offset': 494, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 22}}]
01f2 lea ax, [bp - 0x76]
01f5 push ss
01f6 push ax
01f7 lea ax, [bp - 0x12]
01fa push ss
01fb push ax
01fc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 511, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_CenterStrInRectClear
0201 add sp, 8
0204 push word ptr [0xcf52] ; _clipDC
0208 push -1
020a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 523, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 39}}]
020f push 0
0211 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 532, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0216 add sp, 2
0219 push word ptr [bp + 6]
021c nop 
021d push cs
021e call 0xe3a4 ; _win_UnlockWin
0221 add sp, 2
0224 pop si
0225 pop di
0226 leave 
0227 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern int near clipDC;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far gr_CenterStrInRectClear(struct WinRect far *rect, char far *text);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far gr_CenterStrInRectClear(struct WinRect far *rect, char far *text);` — src/recovered/wf_win_PrintfAtObj-9e4b836702.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern int far vsprintf(char far *buffer, char far *format, char far *args);` — src/recovered/wf_win_PrintfAtObj-9e4b836702.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_PrintfAtObj', 'offset': 55002, 'source': 'src/recovered/wf_win_PrintfAtObj-9e4b836702.c', 'size': 183}
- {'symbol': '_win_ClearObjToEOL', 'offset': 55186, 'source': None, 'size': 290}
- {'symbol': '_win_DrawHBar', 'offset': 56028, 'source': None, 'size': 192}
- {'symbol': '_win_DrawVBar', 'offset': 56220, 'source': None, 'size': 194}
