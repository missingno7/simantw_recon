# Recovery task _drawHistGraph

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 777 bytes.

```asm
0000 enter 0x40, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov es, word ptr [0xc084]
000d mov bx, di
000f shl bx, 1
0011 mov bx, word ptr es:[bx - 0x71f0]
0016 shl bx, 1
0018 push word ptr es:[bx - 0x71b4]
001d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 32, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0022 add sp, 2
0025 mov word ptr [bp - 0x1c], ax
0028 lea ax, [bp - 0x24]
002b push ss
002c push ax
002d push 0x150e
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0035 add sp, 6
0038 mov ax, word ptr [bp - 0x20]
003b sub ax, word ptr [bp - 0x24]
003e sub ax, 0x40
0041 mov word ptr [bp - 0x1a], ax
0044 sub word ptr [bp - 0x1e], 8
0048 mov ax, word ptr [bp - 0x1e]
004b add word ptr [bp - 0x22], 8
004f sub ax, word ptr [bp - 0x22]
0052 mov word ptr [bp - 0xa], ax
0055 mov es, word ptr [0xc0b8]
0059 mov ax, di
005b and ax, 1
005e mov cx, ax
0060 shl ax, 2
0063 add ax, cx
0065 mov cx, di
0067 sar cx, 1
0069 add ax, cx
006b mov di, ax
006d mov bx, di
006f shl bx, 2
0072 mov ax, word ptr es:[bx - 0x798e]
0077 mov dx, word ptr es:[bx - 0x798c]
007c mov word ptr [bp - 0x18], ax
007f mov word ptr [bp - 0x16], dx
0082 mov es, word ptr [0xc0ba]
0086 mov ax, word ptr es:[bx - 0x7966]
008b mov dx, word ptr es:[bx - 0x7964]
0090 mov word ptr [bp - 4], ax
0093 mov word ptr [bp - 2], dx
0096 mov es, word ptr [0xc0a4]
009a mov ax, word ptr es:[0x9e6e]
009e mov word ptr [bp - 0x3a], ax
00a1 mov es, word ptr [0xc0a6]
00a5 sub al, byte ptr es:[0x8670]
00aa and ax, 0x3f
00ad mov word ptr [bp - 0xe], ax
00b0 xor ax, ax
00b2 mov word ptr [bp - 8], ax
00b5 mov word ptr [bp - 0x12], ax
00b8 mov word ptr [bp + 6], di
00bb cmp word ptr es:[0x8670], ax
00c0 jle 0x8fb8
00c2 mov ax, word ptr es:[0x8670]
00c6 mov word ptr [bp - 6], ax
00c9 mov bx, word ptr [bp - 0xe]
00cc mov cx, word ptr [bp - 4]
00cf mov di, word ptr [bp - 8]
00d2 mov es, word ptr [bp - 0x16]
00d5 mov ds, dx
00d7 mov si, word ptr [bp - 0x18]
00da mov ax, bx
00dc shl ax, 1
00de mov word ptr [bp - 0x3c], ax
00e1 add si, ax
00e3 cmp word ptr es:[si], di
00e6 jle 0x8f68
00e8 mov si, word ptr [bp - 0x18]
00eb add si, ax
00ed mov di, word ptr es:[si]
00f0 mov si, ax
00f2 add si, cx
00f4 cmp word ptr [si], di
00f6 jle 0x8f76
00f8 mov si, ax
00fa add si, cx
00fc mov di, word ptr [si]
00fe mov al, bl
0100 inc al
0102 and ax, 0x3f
0105 mov bx, ax
0107 dec word ptr [bp - 6]
010a jne 0x8f4f
010c push ss
010d pop ds
010e mov cx, 1
0111 mov bx, cx
0113 mov word ptr [bp - 0x10], cx
0116 or di, di
0118 jle 0x8fd4
011a cmp word ptr [bp - 0xa], di
011d jle 0x8fac
011f mov word ptr [bp - 0x14], bx
0122 mov dx, di
0124 mov bx, word ptr [bp - 0xa]
0127 mov word ptr [bp - 8], di
012a inc cx
012b add dx, di
012d cmp dx, bx
012f jl 0x8fa2
0131 mov bx, word ptr [bp - 0x14]
0134 cmp cx, 1
0137 jle 0x8fbe
0139 dec cx
013a mov word ptr [bp - 0x10], cx
013d jmp 0x8fd4
013f nop 
0140 mov di, word ptr [bp - 8]
0143 jmp 0x8f86
0145 nop 
0146 mov word ptr [bp - 0x10], cx
0149 cmp word ptr [bp - 0xa], di
014c jge 0x8fd4
014e mov word ptr [bp - 8], di
0151 mov ax, di
0153 inc bx
0154 cdq 
0155 idiv bx
0157 cmp ax, word ptr [bp - 0xa]
015a jg 0x8fc9
015c mov al, byte ptr [bp - 0x3a]
015f and ax, 0x3f
0162 mov word ptr [bp - 0xe], ax
0165 mov ax, word ptr [bp - 0x24]
0168 mov word ptr [bp - 4], ax
016b cmp bx, 1
016e jne 0x8ffc
0170 mov si, word ptr [bp - 0x3a]
0173 shl si, 1
0175 mov es, word ptr [bp - 0x16]
0178 add si, word ptr [bp - 0x18]
017b mov ax, word ptr es:[si]
017e imul word ptr [bp - 0x10]
0181 jmp 0x900d
0183 nop 
0184 mov si, word ptr [bp - 0x3a]
0187 shl si, 1
0189 mov es, word ptr [bp - 0x16]
018c add si, word ptr [bp - 0x18]
018f mov ax, word ptr es:[si]
0192 cdq 
0193 idiv bx
0195 sub ax, word ptr [bp - 0x1e]
0198 neg ax
019a mov word ptr [bp - 0xa], ax
019d mov word ptr [bp - 0x14], bx
01a0 mov ax, word ptr [bp - 4]
01a3 mov word ptr [bp - 6], ax
01a6 mov ax, word ptr [bp - 0xa]
01a9 mov word ptr [bp - 8], ax
01ac mov ax, word ptr [bp - 0x1a]
01af mov word ptr [bp - 2], ax
01b2 mov word ptr [bp - 0xc], 0x3f
01b7 mov di, word ptr [bp - 0xe]
01ba mov ax, di
01bc inc al
01be and ax, 0x3f
01c1 mov di, ax
01c3 mov ax, word ptr [bp - 2]
01c6 cdq 
01c7 and dx, 0x3f
01ca add ax, dx
01cc sar ax, 6
01cf add ax, word ptr [bp - 0x24]
01d2 add ax, word ptr [bp + 0xa]
01d5 mov word ptr [bp - 4], ax
01d8 mov es, word ptr [bp - 0x16]
01db cmp word ptr [bp - 0x14], 1
01df jne 0x906a
01e1 mov bx, word ptr [bp - 0x18]
01e4 mov ax, di
01e6 shl ax, 1
01e8 add bx, ax
01ea mov ax, word ptr es:[bx]
01ed imul word ptr [bp - 0x10]
01f0 jmp 0x907a
01f2 mov bx, word ptr [bp - 0x18]
01f5 mov ax, di
01f7 shl ax, 1
01f9 add bx, ax
01fb mov ax, word ptr es:[bx]
01fe cdq 
01ff idiv word ptr [bp - 0x14]
0202 mov si, word ptr [bp - 0x1e]
0205 sub si, ax
0207 push word ptr [bp - 0x1c]
020a push si
020b push word ptr [bp - 4]
020e push word ptr [bp - 8]
0211 push word ptr [bp - 6]
0214 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 535, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GLine
0219 add sp, 0xa
021c mov ax, word ptr [bp - 4]
021f mov word ptr [bp - 6], ax
0222 mov word ptr [bp - 8], si
0225 mov ax, word ptr [bp - 0x1a]
0228 add word ptr [bp - 2], ax
022b dec word ptr [bp - 0xc]
022e jne 0x9032
0230 mov word ptr [bp - 0xa], si
0233 mov word ptr [bp - 0xe], di
0236 cmp word ptr [bp + 8], 0
023a jne 0x90d2
023c mov es, word ptr [0xc0bc]
0240 les bx, ptr es:[0x72e8]
0245 mov di, word ptr [bp + 6]
0248 shl di, 2
024b mov ax, word ptr es:[bx + di]
024e mov dx, word ptr es:[bx + di + 2]
0252 mov si, ax
0254 mov word ptr [bp - 6], dx
0257 jmp 0x90f5
0259 nop 
025a mov bx, di
025c shl bx, 1
025e les si, ptr [bp - 0x18]
0261 push word ptr es:[bx + si]
0264 push ds
0265 push 0x14fe
0268 lea ax, [bp - 0x38]
026b push ss
026c push ax
026d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 624, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
0272 add sp, 0xa
0275 lea ax, [bp - 0x38]
0278 mov si, ax
027a mov word ptr [bp - 6], ss
027d push word ptr [bp - 0x1c]
0280 push 0
0282 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 645, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0287 add sp, 2
028a push ax
028b push word ptr [bp - 0x1c]
028e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 657, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
0293 add sp, 6
0296 push 3
0298 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 667, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
029d add sp, 2
02a0 mov ax, word ptr [bp - 6]
02a3 push ax
02a4 push si
02a5 mov di, ax
02a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 682, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
02ac mov cx, ax
02ae cdq 
02af sub ax, dx
02b1 sar ax, 1
02b3 sub ax, word ptr [bp - 0xa]
02b6 neg ax
02b8 push ax
02b9 push word ptr [bp - 4]
02bc mov word ptr [bp - 0x3e], ax
02bf mov word ptr [bp - 0x40], cx
02c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 709, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_PrintStr
02c7 add sp, 8
02ca mov ax, di
02cc push ax
02cd push si
02ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 721, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_StringWidth
02d3 add sp, 4
02d6 mov di, ax
02d8 push 1
02da mov ax, word ptr [bp - 0x3e]
02dd add ax, word ptr [bp - 0x40]
02e0 inc ax
02e1 push ax
02e2 add di, word ptr [bp - 4]
02e5 lea ax, [di + 1]
02e8 push ax
02e9 mov ax, word ptr [bp - 0x3e]
02ec dec ax
02ed push ax
02ee mov ax, word ptr [bp - 4]
02f1 dec ax
02f2 push ax
02f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 758, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxOutline
02f8 add sp, 0xa
02fb push 0
02fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 768, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0302 add sp, 2
0305 pop si
0306 pop di
0307 leave 
0308 retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far ConvColor(int color);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_StringWidth(int first, int second);` — src/recovered/win_StringSize.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClearHistory', 'offset': 36092, 'source': None, 'size': 299}
- {'symbol': '_win_DrawHistoryWindow', 'offset': 36392, 'source': None, 'size': 80}
- {'symbol': '_HistUpdate', 'offset': 37250, 'source': None, 'size': 317}
- {'symbol': '_EditMessage', 'offset': 37568, 'source': None, 'size': 351}
