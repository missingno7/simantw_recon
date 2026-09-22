# Recovery task _DrawControlLevels

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 538 bytes.

```asm
0000 enter 0x2e, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 push 4
000b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 14, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0010 add sp, 2
0013 lea ax, [bp - 0x24]
0016 push ss
0017 push ax
0018 mov cx, di
001a mov dl, 0xc
001c mov dh, ch
001e push dx
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0024 add sp, 6
0027 mov ax, word ptr [bp - 0x20]
002a sub ax, word ptr [bp - 0x24]
002d mov cx, 5
0030 cdq 
0031 idiv cx
0033 mov si, ax
0035 mov ax, word ptr [bp - 0x1e]
0038 sub ax, word ptr [bp - 0x22]
003b mov word ptr [bp - 0x10], ax
003e cmp di, 0x1200
0042 jne 0xc848
0044 mov ax, 0x9c74
0047 mov <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004a mov cx, ax
004c mov word ptr [bp - 0x1a], dx
004f mov word ptr [bp - 0x16], 0x159a
0054 mov word ptr [bp - 0x14], ds
0057 mov <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
005a mov es, ax
005c mov ax, word ptr es:[0x9e74]
0060 cdq 
0061 mov bx, ax
0063 mov ax, word ptr es:[0x9e72]
0067 mov di, dx
0069 cdq 
006a add ax, bx
006c adc dx, di
006e mov bx, ax
0070 mov ax, word ptr es:[0x9e70]
0074 mov di, dx
0076 cdq 
0077 add bx, ax
0079 adc di, dx
007b mov word ptr [bp - 0xe], bx
007e mov word ptr [bp - 0xc], di
0081 jmp 0xc865
0083 nop 
0084 mov ax, 0x9b64
0087 mov <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
008a mov cx, ax
008c mov word ptr [bp - 0x1a], dx
008f mov word ptr [bp - 0x16], 0x1596
0094 mov word ptr [bp - 0x14], ds
0097 mov ax, word ptr [0xac94] ; _CastePopB
009a cdq 
009b mov word ptr [bp - 0xe], ax
009e mov word ptr [bp - 0xc], dx
00a1 xor ax, ax
00a3 mov word ptr [bp - 8], ax
00a6 mov word ptr [bp - 0xa], ax
00a9 mov ax, si
00ab shl ax, 1
00ad mov word ptr [bp - 0x12], ax
00b0 mov ax, word ptr [bp - 0x1a]
00b3 mov word ptr [bp - 6], cx
00b6 mov word ptr [bp - 4], ax
00b9 mov word ptr [bp - 0x18], si
00bc mov word ptr [bp - 0x1c], cx
00bf mov si, cx
00c1 mov di, word ptr [bp - 8]
00c4 mov ah, byte ptr [bp + 7]
00c7 sub al, al
00c9 add ax, di
00cb add ax, 9
00ce mov word ptr [bp - 2], ax
00d1 cmp word ptr [bp + 0xa], 0
00d5 je 0xc8be
00d7 push 0
00d9 push -1
00db mov ax, 0x64
00de mov es, word ptr [bp - 4]
00e1 mul word ptr es:[si]
00e4 add ax, 0x3fff
00e7 adc dx, 0
00ea push dx
00eb push ax
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00f1 push dx
00f2 push ax
00f3 push ds
00f4 push 0x15cb
00f7 jmp 0xc8e8
00f9 nop 
00fa push 0
00fc push -1
00fe push word ptr [bp - 0xc]
0101 push word ptr [bp - 0xe]
0104 mov es, word ptr [bp - 4]
0107 push 0
0109 push word ptr es:[si]
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0111 add ax, 0x3fff
0114 adc dx, 0
0117 push dx
0118 push ax
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 284, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
011e push dx
011f push ax
0120 push ds
0121 push 0x15d2
0124 push word ptr [bp - 2]
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_PrintfAtObj
012c add sp, 0xa
012f push word ptr [bp - 2]
0132 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 309, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_ClearObjToEOL
0137 add sp, 2
013a mov ax, word ptr [bp - 0x24]
013d add ax, word ptr [bp - 0xa]
0140 mov word ptr [bp - 0x2c], ax
0143 add ax, word ptr [bp - 0x18]
0146 dec ax
0147 mov word ptr [bp - 0x28], ax
014a mov ax, word ptr [bp - 0x1e]
014d dec ax
014e mov word ptr [bp - 0x26], ax
0151 push -1
0153 push 1
0155 mov cx, ax
0157 mov ax, word ptr [bp - 0x10]
015a cdq 
015b push dx
015c push ax
015d mov es, word ptr [bp - 4]
0160 push 0
0162 push word ptr es:[si]
0165 mov word ptr [bp - 0x2e], cx
0168 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 363, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
016d push dx
016e push ax
016f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 370, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0174 add ax, word ptr [bp - 0x2e]
0177 mov word ptr [bp - 0x2a], ax
017a inc ax
017b cmp ax, word ptr [bp - 0x2e]
017e jge 0xc990
0180 les bx, ptr [bp - 0x16]
0183 mov al, byte ptr es:[bx + di]
0186 cwde 
0187 push ax
0188 lea ax, [bp - 0x2c]
018b push ss
018c push ax
018d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 400, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
0192 add sp, 6
0195 push 0
0197 push 0xf
0199 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 412, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
019e add sp, 2
01a1 push ax
01a2 push 0xf
01a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
01a9 add sp, 2
01ac push ax
01ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 432, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
01b2 add sp, 6
01b5 inc word ptr [bp - 0x28]
01b8 inc word ptr [bp - 0x26]
01bb push 1
01bd lea ax, [bp - 0x2c]
01c0 push ss
01c1 push ax
01c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 453, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectOutline
01c7 add sp, 6
01ca jmp 0xc996
01cc mov ax, word ptr [bp - 0x1e]
01cf mov word ptr [bp - 0x2a], ax
01d2 mov ax, word ptr [bp - 0x2a]
01d5 dec ax
01d6 mov word ptr [bp - 0x26], ax
01d9 mov ax, word ptr [bp - 0x22]
01dc dec ax
01dd mov word ptr [bp - 0x2a], ax
01e0 push 0
01e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 485, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
01e7 add sp, 2
01ea or al, 0x40
01ec push ax
01ed lea ax, [bp - 0x2c]
01f0 push ss
01f1 push ax
01f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 501, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectFill
01f7 add sp, 6
01fa mov ax, word ptr [bp - 0x12]
01fd add word ptr [bp - 0xa], ax
0200 add si, 2
0203 inc di
0204 cmp di, 3
0207 jge 0xc9d0
0209 jmp 0xc888
020c push 0
020e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 529, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0213 add sp, 2
0216 pop si
0217 pop di
0218 leave 
0219 retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far GRectFill(struct BitmapObject far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern void far GRectFill(void far *object, int color);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far GRectOutline(int first, int second, int third);` — src/recovered/win_RectOutline.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far win_PrintfAtObj(int object, long message);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawCasteWindow', 'offset': 50774, 'source': None, 'size': 216}
- {'symbol': '_win_CasteControlClosed', 'offset': 50990, 'source': None, 'size': 149}
- {'symbol': '_cvtLevels2IdealCaste', 'offset': 51678, 'source': 'src/recovered/wf_cvtLevels2IdealCaste-f8fed91c5a.c', 'size': 156}
- {'symbol': '_GetTriLatDist', 'offset': 51834, 'source': None, 'size': 299}
