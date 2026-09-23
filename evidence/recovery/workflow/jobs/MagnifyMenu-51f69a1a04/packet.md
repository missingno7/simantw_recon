# Recovery task _MagnifyMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 471 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 0xa]
0009 cmp dx, 1
000c jg 0x6b6c
000e mov di, word ptr [bp + 6]
0011 mov bx, di
0013 shl bx, 6
0016 add bx, word ptr [bp + 8]
0019 mov bl, byte ptr [bx + 0x68e8]
001d jmp 0x6b91
001f nop 
0020 cmp dx, 2
0023 jne 0x6b82
0025 mov di, word ptr [bp + 6]
0028 mov bx, di
002a shl bx, 6
002d add bx, word ptr [bp + 8]
0030 mov bl, byte ptr [bx - 0x7718]
0034 jmp 0x6b91
0036 mov di, word ptr [bp + 6]
0039 mov bx, di
003b shl bx, 6
003e add bx, word ptr [bp + 8]
0041 mov bl, byte ptr [bx - 0x6718]
0045 sub bh, bh
0047 or bx, bx
0049 jne 0x6b9e
004b mov ax, 0xffff
004e pop si
004f pop di
0050 leave 
0051 retf 
0052 mov word ptr [bp - 6], bx
0055 mov si, word ptr [bp + 8]
0058 mov ax, di
005a mov es, word ptr [0xc248]
005e sub ax, word ptr es:[0x7d2e]
0063 inc ax
0064 imul word ptr [0x143a] ; _tileWidth
0068 mov es, word ptr [0xc24a]
006c add ax, word ptr es:[0x9b08]
0071 mov word ptr [bp - 2], ax
0074 mov ax, si
0076 mov es, word ptr [0xc248]
007a sub ax, word ptr es:[0x7d30]
007f dec ax
0080 imul word ptr [0x143c] ; _tileHeight
0084 mov es, word ptr [0xc24a]
0088 add ax, word ptr es:[0x9b0a]
008d mov word ptr [bp - 4], ax
0090 push word ptr [0xcd78] ; _rootWnd
0094 lea ax, [bp - 0x1a]
0097 push ss
0098 push ax
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 32}}]
009e lea ax, [bp - 0x12]
00a1 push ss
00a2 push ax
00a3 push 0x1d00
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
00ab add sp, 6
00ae mov ax, word ptr [bp - 2]
00b1 mov word ptr [bp - 0xa], ax
00b4 mov ax, word ptr [bp - 4]
00b7 mov word ptr [bp - 8], ax
00ba push word ptr [0xbca6] ; _win_hwnd
00be lea ax, [bp - 0xa]
00c1 push ss
00c2 push ax
00c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 196, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 28}}]
00c8 mov ax, word ptr [bp - 0xc]
00cb sub ax, word ptr [bp - 0x10]
00ce add ax, word ptr [bp - 8]
00d1 cmp ax, word ptr [bp - 0x14]
00d4 jle 0x6c36
00d6 mov ax, word ptr [bp - 0x18]
00d9 mov cx, word ptr [bp - 0x10]
00dc sub cx, word ptr [bp - 0xc]
00df add word ptr [bp - 8], cx
00e2 cmp word ptr [bp - 8], ax
00e5 jge 0x6c36
00e7 mov word ptr [bp - 8], ax
00ea mov ax, word ptr [bp - 0xe]
00ed sub ax, word ptr [bp - 0x12]
00f0 add ax, word ptr [bp - 0xa]
00f3 cmp ax, word ptr [bp - 0x16]
00f6 jle 0x6c58
00f8 mov ax, word ptr [bp - 0x1a]
00fb mov cx, word ptr [bp - 0x12]
00fe sub cx, word ptr [bp - 0xe]
0101 add word ptr [bp - 0xa], cx
0104 cmp word ptr [bp - 0xa], ax
0107 jge 0x6c58
0109 mov word ptr [bp - 0xa], ax
010c push word ptr [0xcd78] ; _rootWnd
0110 lea ax, [bp - 0xa]
0113 push ss
0114 push ax
0115 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 278, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
011a mov word ptr [0xcb6c], di
011e mov word ptr [0xcb6e], si
0122 mov ax, word ptr [bp + 0xa]
0125 mov word ptr [0xcb70], ax
0128 push word ptr [bp - 8]
012b push word ptr [bp - 0xa]
012e push 0x1d00
0131 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 308, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0136 add sp, 6
0139 push word ptr [0xbce0]
013d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
0142 add sp, 2
0145 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 328, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
014a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 333, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldInit
014f push 0x1d00
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0157 add sp, 2
015a or ax, ax
015c je 0x6d02
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 353, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeld
0163 or ax, ax
0165 je 0x6d02
0167 push 0x1d00
016a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 365, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinInFront
016f add sp, 2
0172 or ax, ax
0174 jne 0x6cf3
0176 push word ptr [0xbce0]
017a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 379, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
017f push word ptr [0xbce0]
0183 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 390, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0188 add sp, 2
018b push 0x1d00
018e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 401, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_DrawWindow
0193 add sp, 2
0196 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 409, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
019b push word ptr [0xbce0]
019f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 418, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
01a4 add sp, 2
01a7 push 0x1d00
01aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 429, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01af add sp, 2
01b2 or ax, ax
01b4 jne 0x6caa
01b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 441, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldEnd
01bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 446, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
01c0 push 0x1d00
01c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 454, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
01c8 add sp, 2
01cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 462, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UpdateAllWindows
01d0 mov ax, word ptr [bp - 6]
01d3 pop si
01d4 pop di
01d5 leave 
01d6 retf 
```

## Known declaration examples

- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far MyReleaseCapture(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int far MySetCapture(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far UpdateAllWindows(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int near tileHeight;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near tileWidth;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far win_Close(int objectNumber);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_DrawWindow(int objectNumber);` — src/recovered/wf_PaintStuff-4a441706dd.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern void far win_Open(int flags);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd[];` — src/recovered/wf_DoScenario-496dc7a0ac.c
- `extern int near win_hwnd[];` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EditToolsMenu', 'offset': 26566, 'source': None, 'size': 506}
- {'symbol': '_win_DrawExamineWindow', 'offset': 27072, 'source': None, 'size': 395}
- {'symbol': '_AntMenu', 'offset': 27940, 'source': None, 'size': 232}
- {'symbol': '_SetExpTool', 'offset': 28172, 'source': 'src/recovered/SetExpTool.c', 'size': 16}
