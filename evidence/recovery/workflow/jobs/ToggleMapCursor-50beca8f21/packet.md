# Recovery task _ToggleMapCursor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 261 bytes.

```asm
0000 cmp word ptr [0x1992], 0 ; _mapCursorState
0005 je 0xc79a
0007 push 0x100
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
000f add sp, 2
0012 or ax, ax
0014 jne 0xc767
0016 jmp 0xc852
0019 cmp word ptr [0x1992], 1 ; _mapCursorState
001e je 0xc771
0020 jmp 0xc852
0023 nop 
0024 push cs
0025 call 0x8e50 ; _clip_Push
0028 push 0x100
002b nop 
002c push cs
002d call 0x8e44 ; _clip_SetWin
0030 add sp, 2
0033 push 2
0035 push <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0038 push 0x72ae
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
0040 add sp, 6
0043 mov word ptr [0x1992], 0 ; _mapCursorState
0049 jmp 0xc84d
004c push 0x100
004f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 82, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0054 add sp, 2
0057 or ax, ax
0059 jne 0xc7ac
005b jmp 0xc852
005e cmp word ptr [0x1992], 0 ; _mapCursorState
0063 je 0xc7b6
0065 jmp 0xc852
0068 nop 
0069 push cs
006a call 0x8e50 ; _clip_Push
006d push 0x100
0070 nop 
0071 push cs
0072 call 0x8e44 ; _clip_SetWin
0075 add sp, 2
0078 mov es, word ptr [0xc1e2]
007c mov ax, word ptr es:[0x8096]
0080 mov es, word ptr [0xc1f0]
0084 mov cx, ax
0086 imul word ptr es:[0x7d30]
008b mov es, word ptr [0xc1f2]
008f add ax, word ptr es:[0x8112]
0094 mov es, word ptr [0xc1f4]
0098 mov word ptr es:[0x72b0], ax
009c mov dx, ax
009e mov ax, cx
00a0 mov bx, dx
00a2 imul word ptr [0xcd7a] ; _editHeight
00a6 add bx, ax
00a8 mov word ptr es:[0x72b4], bx
00ad mov es, word ptr [0xc1e4]
00b1 mov ax, word ptr es:[0x807c]
00b5 mov es, word ptr [0xc1f0]
00b9 mov cx, ax
00bb imul word ptr es:[0x7d2e]
00c0 mov es, word ptr [0xc1f2]
00c4 add ax, word ptr es:[0x8110]
00c9 mov es, word ptr [0xc1f6]
00cd add ax, word ptr es:[0x9bc6]
00d2 mov es, word ptr [0xc1f4]
00d6 mov word ptr es:[0x72ae], ax
00da mov dx, ax
00dc mov ax, cx
00de mov bx, dx
00e0 imul word ptr [0xcc80] ; _editWidth
00e4 add bx, ax
00e6 mov word ptr es:[0x72b2], bx
00eb push 2
00ed push es
00ee push 0x72ae
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
00f6 add sp, 6
00f9 mov word ptr [0x1992], 1 ; _mapCursorState
00ff nop 
0100 push cs
0101 call 0x8e4e ; _clip_Pop
0104 retf 
```

## Known declaration examples

- `extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);` — src/recovered/EraseMiniMapCursor.c
- `extern void far clip_Pop(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Pop(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void far clip_Push(void);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_Push(void);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editHeight;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawMapCursor', 'offset': 50770, 'source': None, 'size': 185}
- {'symbol': '_EraseMapCursor', 'offset': 50956, 'source': None, 'size': 66}
- {'symbol': '_DrawMapData', 'offset': 52064, 'source': None, 'size': 397}
- {'symbol': '_AllocateMapBuffer', 'offset': 52462, 'source': None, 'size': 79}
