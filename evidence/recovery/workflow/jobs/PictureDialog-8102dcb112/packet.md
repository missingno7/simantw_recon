# Recovery task _PictureDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 535 bytes.

```asm
0000 enter 0x30, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xc]
0009 push 4
000b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 14, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0010 add sp, 2
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_FontHeight
0018 mov word ptr [bp - 2], ax
001b or di, di
001d je 0x62e9
001f push di
0020 lea ax, [bp - 0x10]
0023 push ss
0024 push ax
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
002a add sp, 6
002d or di, di
002f je 0x62f6
0031 mov ax, word ptr [bp - 0xe]
0034 add ax, 2
0037 jmp 0x62f8
0039 nop 
003a xor ax, ax
003c mov word ptr [bp - 8], ax
003f mov ax, word ptr [bp - 2]
0042 imul word ptr [bp + 0xa]
0045 add ax, word ptr [bp - 8]
0048 add ax, 8
004b mov word ptr [bp - 0xc], ax
004e mov word ptr [bp - 4], 0x32
0053 mov word ptr [bp - 6], 0
0058 cmp word ptr [bp + 0xa], 0
005c jle 0x634f
005e mov ax, word ptr [bp + 6]
0061 mov dx, word ptr [bp + 8]
0064 mov si, ax
0066 mov word ptr [bp - 8], dx
0069 mov ax, word ptr [bp + 0xa]
006c mov word ptr [bp - 2], ax
006f mov es, word ptr [bp - 8]
0072 push word ptr es:[si + 2]
0076 push word ptr es:[si]
0079 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_StringWidth
007e add sp, 4
0081 mov di, ax
0083 cmp di, word ptr [bp - 4]
0086 jle 0x6347
0088 mov word ptr [bp - 4], di
008b add si, 4
008e dec word ptr [bp - 2]
0091 jne 0x632b
0093 mov ax, word ptr [bp + 0xc]
0096 mov word ptr [0xcaba], ax
0099 mov ax, word ptr [bp + 0xa]
009c mov word ptr [0xcab8], ax
009f mov ax, word ptr [bp + 6]
00a2 mov dx, word ptr [bp + 8]
00a5 mov word ptr [0xcab4], ax
00a8 mov word ptr [0xcab6], dx
00ac mov es, word ptr [0xbefc]
00b0 push word ptr es:[0xcd78]
00b5 lea ax, [bp - 0x18]
00b8 push ss
00b9 push ax
00ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 33}}]
00bf mov ax, word ptr [bp - 4]
00c2 add ax, 8
00c5 mov cx, ax
00c7 sub ax, word ptr [bp - 0x14]
00ca neg ax
00cc sar ax, 1
00ce mov word ptr [bp - 0x20], ax
00d1 add ax, cx
00d3 mov word ptr [bp - 0x1c], ax
00d6 mov ax, word ptr [bp - 0x12]
00d9 sub ax, word ptr [bp - 0xc]
00dc sar ax, 1
00de mov word ptr [bp - 0x1e], ax
00e1 add ax, word ptr [bp - 0xc]
00e4 mov word ptr [bp - 0x1a], ax
00e7 push 0x1e00
00ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 237, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
00ef add sp, 2
00f2 push word ptr [bp - 0x1a]
00f5 push word ptr [bp - 0x1c]
00f8 push word ptr [bp - 0x1e]
00fb push word ptr [bp - 0x20]
00fe push 0x1e00
0101 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 260, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0106 add sp, 0xa
0109 push word ptr [0xbce2]
010d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 272, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0112 add sp, 2
0115 mov word ptr [bp - 2], ax
0118 push 0x1e00
011b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 286, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
0120 add sp, 2
0123 lea ax, [bp - 0x20]
0126 push ss
0127 push ax
0128 push 0x1e00
012b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 302, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0130 add sp, 6
0133 push 0xf
0135 nop 
0136 push cs
0137 call 0x9bfe ; _DialogWaitInit
013a add sp, 2
013d push 0x1e01
0140 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 323, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelectable
0145 add sp, 2
0148 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
014d nop 
014e push cs
014f call 0x9c98 ; _DialogAbortOrCont
0152 or ax, ax
0154 je 0x6415
0156 jmp 0x64aa
0159 mov si, word ptr [bp - 2]
015c lea ax, [bp - 0x30]
015f push ss
0160 push ax
0161 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 356, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetEvent
0166 add sp, 4
0169 or ax, ax
016b je 0x6430
016d cmp word ptr [bp - 0x24], 0x1e00
0172 jne 0x648b
0174 cmp word ptr [bp - 0x24], 0x1e00
0179 jne 0x6442
017b xor ax, ax
017d mov word ptr [bp - 0x24], ax
0180 push ax
0181 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 386, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 104}}]
0186 push 0x1e00
0189 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 396, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
018e add sp, 2
0191 or ax, ax
0193 jne 0x6482
0195 push word ptr [0xbce2]
0199 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
019e push word ptr [0xbce2]
01a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 421, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
01a7 add sp, 2
01aa push 0x1e00
01ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 432, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawWindow
01b2 add sp, 2
01b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 440, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
01ba push word ptr [0xbce2]
01be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 449, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
01c3 add sp, 2
01c6 nop 
01c7 push cs
01c8 call 0x9c98 ; _DialogAbortOrCont
01cb or ax, ax
01cd je 0x6418
01cf nop 
01d0 push cs
01d1 call 0x9cd4 ; _DialogDone
01d4 or si, si
01d6 je 0x64b0
01d8 push si
01d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 474, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
01de or ax, ax
01e0 je 0x64b0
01e2 push si
01e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 486, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
01e8 add sp, 2
01eb jmp 0x64b5
01ed nop 
01ee mov si, word ptr [bp - 2]
01f1 jmp 0x648b
01f3 nop 
01f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 503, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
01f9 push 0x1e00
01fc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 511, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
0201 add sp, 2
0204 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 519, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UpdateAllWindows
0209 push 0
020b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 526, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
0210 add sp, 2
0213 pop si
0214 pop di
0215 leave 
0216 retf 
```

## Known declaration examples

- `extern void far DialogDone(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far UpdateAllWindows(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_FontHeight(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far font_FontHeight(void);` — src/recovered/win_StringSize.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_StringWidth(int first, int second);` — src/recovered/win_StringSize.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far win_GetEvent(struct DialogEvent far *event);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int flags);` — src/recovered/OpenMapWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_11_scaffold-eb4b2d667c.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PictStrnDialog', 'offset': 24922, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 155}
- {'symbol': '_win_DrawPictureWindow', 'offset': 25078, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 198}
- {'symbol': '_win_DrawEndGameWindow', 'offset': 25812, 'source': None, 'size': 301}
- {'symbol': '_EndGameDialog', 'offset': 26114, 'source': None, 'size': 312}
