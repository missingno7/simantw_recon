# Recovery task _ProcHistoryEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 245 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 les si, ptr [bp + 6]
0009 mov ax, word ptr es:[si + 0xc]
000d mov word ptr [bp - 2], ax
0010 sub ax, 0x150d
0013 je 0x8ab4
0015 dec ax
0016 je 0x8abe
0018 cmp word ptr es:[si + 0xc], 0x1503
001e jae 0x8a99
0020 jmp 0x8b67
0023 cmp word ptr es:[si + 0xc], 0x150c
0029 jbe 0x8aa4
002b jmp 0x8b67
002e push word ptr [bp - 2]
0031 nop 
0032 push cs
0033 call 0x8b6c ; _ToggleHistButton
0036 add sp, 2
0039 pop si
003a pop di
003b leave 
003c retf 
003d nop 
003e push 0x150f
0041 nop 
0042 push cs
0043 call 0x5aac ; _DoWinHelp
0046 jmp 0x8aac
0048 push 0x1500
004b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0050 add sp, 2
0053 push word ptr [0xbcd0]
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
005c add sp, 2
005f push 0
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
0066 add sp, 2
0069 push ax
006a push 0x150e
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
0072 add sp, 4
0075 xor di, di
0077 mov si, 0x8e54
007a mov es, word ptr [0xc084]
007e mov ax, word ptr es:[si]
0081 mov word ptr [bp - 4], ax
0084 cmp ax, 0x8000
0087 je 0x8b0b
0089 push di
008a push 1
008c push ax
008d nop 
008e push cs
008f call 0x8e78 ; _drawHistGraph
0092 add sp, 6
0095 inc di
0096 add si, 2
0099 cmp si, 0x8e5c
009d jb 0x8af0
009f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 162, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _StillDown
00a4 or ax, ax
00a6 jne 0x8b15
00a8 push ax
00a9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ConvColor
00ae add sp, 2
00b1 push ax
00b2 push 0x150e
00b5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FillObjRect
00ba add sp, 4
00bd xor di, di
00bf mov si, 0x8e54
00c2 mov es, word ptr [0xc084]
00c6 mov ax, word ptr es:[si]
00c9 mov word ptr [bp - 6], ax
00cc cmp ax, 0x8000
00cf je 0x8b53
00d1 push di
00d2 push 0
00d4 push ax
00d5 nop 
00d6 push cs
00d7 call 0x8e78 ; _drawHistGraph
00da add sp, 6
00dd inc di
00de add si, 2
00e1 cmp si, 0x8e5c
00e5 jb 0x8b38
00e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 234, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 239, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00f1 pop si
00f2 pop di
00f3 leave 
00f4 retf 
```

## Known declaration examples

- `extern int far ConvColor(int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far ConvColor(int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern int far ConvColor(int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far DoWinHelp(int mode);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far StillDown(void);` — src/recovered/myButton.c
- `extern int far StillDown(void);` — src/recovered/wf_DialogWaitInit-b15a65c440.c
- `extern void far clip_Off(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far win_FillObjRect(int object, int color);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_YellowHelp', 'offset': 35372, 'source': 'src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c', 'size': 62}
- {'symbol': '_OpenHistoryWindow', 'offset': 35434, 'source': 'src/recovered/OpenHistoryWindow.c', 'size': 12}
- {'symbol': '_ToggleHistButton', 'offset': 35692, 'source': None, 'size': 400}
- {'symbol': '_ClearHistory', 'offset': 36092, 'source': None, 'size': 299}
