# Recovery task _DrawCastePopUp

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 814 bytes.

```asm
0000 enter 0x5a, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbef6]
000a mov ax, word ptr es:[0x9c28]
000e mov word ptr [bp - 0x1a], ax
0011 push 1
0013 nop 
0014 push cs
0015 call 0x4e34 ; _SetPause
0018 add sp, 2
001b mov es, word ptr [0xbef8]
001f mov word ptr es:[0x9fb0], 1
0026 mov word ptr [bp - 2], 2
002b mov ax, word ptr [0xcf24]
002e or ax, word ptr [0xcf22]
0032 je 0x5e42
0034 push word ptr [0xcd78] ; _rootWnd
0038 lea ax, [bp - 0x22]
003b push ss
003c push ax
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 33}}]
0042 lea ax, [bp - 0x2a]
0045 push ss
0046 push ax
0047 push 0x2201
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
004f add sp, 6
0052 push 0x1700
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
005a add sp, 2
005d mov ax, word ptr [0xcef6]
0060 mov dx, word ptr [0xcef8]
0064 mov si, ax
0066 mov word ptr [bp - 2], dx
0069 push 0
006b mov es, dx
006d mov ax, word ptr es:[si]
0070 sub ax, word ptr es:[si + 4]
0074 push 7
0076 mov si, ax
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
007d shl ax, 1
007f sub si, ax
0081 mov ax, word ptr [bp - 0x26]
0084 cmp ax, word ptr [bp - 0x1e]
0087 jle 0x5e2a
0089 mov ax, word ptr [bp - 0x1e]
008c add si, ax
008e push si
008f push 0x1700
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0097 add sp, 6
009a push 0x1700
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
00a2 jmp 0x5e4a
00a4 push 0x1700
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
00ac add sp, 2
00af push word ptr [0xbcd4]
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 182, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
00b8 add sp, 2
00bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldInit
00c0 lea ax, [bp - 0x32]
00c3 push ss
00c4 push ax
00c5 push 0x1702
00c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 203, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
00cd add sp, 6
00d0 push 2
00d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
00d7 add sp, 2
00da mov word ptr [bp - 4], 0
00df mov si, 0x30
00e2 push si
00e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 230, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_CharWidth
00e8 add sp, 2
00eb mov di, ax
00ed cmp di, word ptr [bp - 4]
00f0 jle 0x5e93
00f2 mov word ptr [bp - 4], di
00f5 inc si
00f6 cmp si, 0x39
00f9 jle 0x5e80
00fb mov ax, word ptr [bp - 4]
00fe shl ax, 2
0101 add ax, word ptr [bp - 0x32]
0104 add ax, 2
0107 mov word ptr [bp - 0x12], ax
010a sub ax, word ptr [bp - 0x2e]
010d neg ax
010f mov word ptr [bp - 0x16], ax
0112 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 277, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
0117 mov di, ax
0119 mov cx, ax
011b shl ax, 1
011d add ax, cx
011f shl ax, 2
0122 sub ax, word ptr [bp - 0x2c]
0125 neg ax
0127 sub ax, word ptr [bp - 0x30]
012a add ax, 3
012d mov cx, 5
0130 mov bx, ax
0132 cdq 
0133 idiv cx
0135 mov word ptr [bp - 0x18], dx
0138 mov word ptr [bp - 0x14], 0
013d mov ax, bx
013f cdq 
0140 idiv cx
0142 mov word ptr [bp - 0xc], ax
0145 mov word ptr [bp - 0xa], di
0148 mov ax, word ptr [bp - 0x30]
014b mov word ptr [bp - 0xe], ax
014e mov si, 1
0151 mov word ptr [bp - 2], 2
0156 mov word ptr [bp - 0x10], di
0159 mov bx, word ptr [bp - 2]
015c mov word ptr [bp - 8], si
015f mov di, si
0161 mov dx, word ptr [bp - 6]
0164 cmp word ptr [bx - 0x536c], di
0168 jle 0x5f0c
016a mov di, word ptr [bx - 0x536c]
016e cmp word ptr [bx - 0x5360], di
0172 jle 0x5f16
0174 mov di, word ptr [bx - 0x5360]
0178 add bx, 2
017b cmp bx, 0xc
017e jl 0x5f02
0180 mov word ptr [bp - 8], di
0183 push word ptr [0xbcd4]
0187 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 394, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
018c add sp, 2
018f xor si, si
0191 mov ax, word ptr [bp - 0x10]
0194 shl ax, 1
0196 add ax, word ptr [bp - 0xc]
0199 mov word ptr [bp - 0x52], ax
019c mov di, word ptr [bp - 0xe]
019f mov ax, word ptr [bp - 0x18]
01a2 add word ptr [bp - 0x14], ax
01a5 cmp word ptr [bp - 0x14], 5
01a9 jle 0x5f4e
01ab inc di
01ac sub word ptr [bp - 0x14], 5
01b0 cmp si, 0xa
01b3 jne 0x5f54
01b5 dec di
01b6 mov ax, word ptr [bp - 8]
01b9 cdq 
01ba push dx
01bb push ax
01bc mov cx, ax
01be mov ax, word ptr [bp - 0x16]
01c1 mov bx, dx
01c3 cdq 
01c4 push dx
01c5 push ax
01c6 mov word ptr [bp - 0x56], ax
01c9 mov word ptr [bp - 0x54], dx
01cc mov ax, word ptr [si - 0x536c]
01d0 cdq 
01d1 push dx
01d2 push ax
01d3 mov word ptr [bp - 0x5a], cx
01d6 mov word ptr [bp - 0x58], bx
01d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 476, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
01de push dx
01df push ax
01e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 483, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
01e5 mov word ptr [bp - 2], ax
01e8 push word ptr [bp - 0x58]
01eb push word ptr [bp - 0x5a]
01ee push word ptr [bp - 0x54]
01f1 push word ptr [bp - 0x56]
01f4 mov ax, word ptr [si - 0x5360]
01f8 cdq 
01f9 push dx
01fa push ax
01fb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 510, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0200 push dx
0201 push ax
0202 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 517, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0207 mov word ptr [bp - 4], ax
020a push 0x1703
020d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 528, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
0212 add sp, 2
0215 push word ptr [si - 0x536c]
0219 push ds
021a push 0x95f
021d lea ax, [bp - 0x50]
0220 push ss
0221 push ax
0222 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 549, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
0227 add sp, 0xa
022a lea ax, [bp - 0x50]
022d push ss
022e push ax
022f push di
0230 push word ptr [bp - 0x32]
0233 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 566, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_PrintStr
0238 add sp, 8
023b or si, si
023d je 0x6006
023f cmp word ptr [bp - 2], 0
0243 je 0x6006
0245 push word ptr [0xcf4e] ; __foreColor
0249 mov ax, word ptr [bp - 0xa]
024c add ax, di
024e sub ax, 3
0251 push ax
0252 mov ax, word ptr [bp - 0x12]
0255 add ax, word ptr [bp - 2]
0258 push ax
0259 lea ax, [di + 1]
025c push ax
025d push word ptr [bp - 0x12]
0260 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 611, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
0265 add sp, 0xa
0268 push 0x1704
026b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 622, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetColorFromObjNum
0270 add sp, 2
0273 push word ptr [si - 0x5360]
0277 push ds
0278 push 0x962
027b lea ax, [bp - 0x50]
027e push ss
027f push ax
0280 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 643, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
0285 add sp, 0xa
0288 lea ax, [bp - 0x50]
028b push ss
028c push ax
028d mov ax, word ptr [bp - 0xa]
0290 add ax, di
0292 push ax
0293 push word ptr [bp - 0x32]
0296 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 665, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_PrintStr
029b add sp, 8
029e or si, si
02a0 je 0x606e
02a2 cmp word ptr [bp - 4], 0
02a6 je 0x606e
02a8 push word ptr [0xcf4e] ; __foreColor
02ac mov ax, word ptr [bp - 0xa]
02af shl ax, 1
02b1 add ax, di
02b3 sub ax, 3
02b6 push ax
02b7 mov ax, word ptr [bp - 0x12]
02ba add ax, word ptr [bp - 4]
02bd push ax
02be mov ax, word ptr [bp - 0xa]
02c1 add ax, di
02c3 inc ax
02c4 push ax
02c5 push word ptr [bp - 0x12]
02c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 715, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
02cd add sp, 0xa
02d0 add di, word ptr [bp - 0x52]
02d3 add si, 2
02d6 cmp si, 0xc
02d9 jge 0x607c
02db jmp 0x5f3d
02de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 737, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
02e3 push 0
02e5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 744, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
02ea add sp, 2
02ed lcall <resolved loader operand; see bindings> ; [{'operand_offset': 752, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldInit
02f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 757, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
02f7 push 0x1700
02fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 765, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
02ff add sp, 2
0302 or ax, ax
0304 je 0x60ad
0306 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 777, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeld
030b or ax, ax
030d jne 0x6090
030f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 786, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
0314 push 0x1700
0317 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 794, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
031c add sp, 2
031f push word ptr [bp - 0x1a]
0322 nop 
0323 push cs
0324 call 0x4e34 ; _SetPause
0327 add sp, 2
032a pop si
032b pop di
032c leave 
032d retf 
```

## Known declaration examples

- `extern int far ButtonHeld(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far ButtonHeldInit(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far SetPause(int pause);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int far _font_CharWidth(int character, unsigned int lo, unsigned int hi);` — src/recovered/font_CharWidth.c
- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern void far font_PrintStr(int x, int y, char far *string);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Close(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern int far win_Events(void);` — src/recovered/wf_myDelay-ac936e115a.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int object, int x, int y);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_SetColorFromObjNum(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawScoreWindow', 'offset': 23242, 'source': None, 'size': 480}
- {'symbol': '_ScoreDialog', 'offset': 23722, 'source': None, 'size': 244}
- {'symbol': '_SetDefaultWindPrompt', 'offset': 24780, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 141}
- {'symbol': '_PictStrnDialog', 'offset': 24922, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 155}
