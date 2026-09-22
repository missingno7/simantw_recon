# Recovery task _ScoreDialog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 244 bytes.

```asm
0000 enter 0x20, 0
0004 push di
0005 push si
0006 lea ax, [bp - 0x10]
0009 push ss
000a push ax
000b nop 
000c push cs
000d call 0x5530 ; _CalcScore
0010 add sp, 4
0013 mov es, word ptr [0xbeee]
0017 mov word ptr es:[0x7898], ax
001b mov word ptr es:[0x789a], dx
0020 push 0x1800
0023 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
0028 add sp, 2
002b xor di, di
002d lea si, [bp - 0x10]
0030 push word ptr [si]
0032 lea ax, [di + 0x1802]
0036 push ax
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
003c add sp, 4
003f inc di
0040 add si, 2
0043 lea ax, [bp - 8]
0046 cmp si, ax
0048 jb 0x5cda
004a mov es, word ptr [0xbef4]
004e les bx, ptr es:[0x737a]
0053 push word ptr es:[bx + 0x3a]
0057 push word ptr es:[bx + 0x38]
005b push 0x180c
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjFormatStr
0063 add sp, 6
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
006b push 0x1800
006e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 113, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0073 add sp, 2
0076 push word ptr [0xbcd6]
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
007f add sp, 2
0082 mov word ptr [bp - 0x14], 0
0087 push 0
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_SetFont
008e add sp, 2
0091 nop 
0092 push cs
0093 call 0x9b9a ; _DialogClearWaitInit
0096 push 0x1800
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
009e add sp, 2
00a1 or ax, ax
00a3 je 0x5d85
00a5 nop 
00a6 push cs
00a7 call 0x9b6c ; _DialogClearWait
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Events
00af or ax, ax
00b1 jne 0x5d66
00b3 nop 
00b4 push cs
00b5 call 0x9c66 ; _DialogAbort
00b8 or ax, ax
00ba je 0x5d76
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
00c1 push 0x1800
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
00c9 add sp, 2
00cc push 0x1800
00cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00d4 add sp, 2
00d7 or ax, ax
00d9 jne 0x5d4f
00db nop 
00dc push cs
00dd call 0x9cd4 ; _DialogDone
00e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 227, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FlushEvents
00e5 push 0x1800
00e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 235, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
00ed add sp, 2
00f0 pop si
00f1 pop di
00f2 leave 
00f3 retf 
```

## Known declaration examples

- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far font_SetFont(int font);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int far win_Events(void);` — src/recovered/wf_myDelay-ac936e115a.c
- `extern void far win_FlushEvents(void);` — src/recovered/ButtonHeldEnd.c
- `extern void far win_FlushEvents(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern void far win_Open(int flags);` — src/recovered/OpenMapWindow.c
- `extern void far win_Open(int window);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far win_SetObjFormatStr(int object, char far *text);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoWinHelp', 'offset': 23212, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 30}
- {'symbol': '_win_DrawScoreWindow', 'offset': 23242, 'source': None, 'size': 480}
- {'symbol': '_DrawCastePopUp', 'offset': 23966, 'source': None, 'size': 814}
- {'symbol': '_SetDefaultWindPrompt', 'offset': 24780, 'source': 'src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c', 'size': 141}
