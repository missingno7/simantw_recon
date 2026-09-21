# Recovery task _DrawMapCursor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 185 bytes.

```asm
0000 push 0x100
0003 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0008 add sp, 2
000b or ax, ax
000d jne 0xc664
000f jmp 0xc70a
0012 cmp word ptr [0x1992], 0 ; _mapCursorState
0017 je 0xc66e
0019 jmp 0xc70a
001c nop 
001d push cs
001e call 0x8e50 ; _clip_Push
0021 push 0x100
0024 nop 
0025 push cs
0026 call 0x8e44 ; _clip_SetWin
0029 add sp, 2
002c mov es, word ptr [0xc1e2]
0030 mov ax, word ptr es:[0x8096]
0034 mov es, word ptr [0xc1f0]
0038 mov cx, ax
003a imul word ptr es:[0x7d30]
003f mov es, word ptr [0xc1f2]
0043 add ax, word ptr es:[0x8112]
0048 mov es, word ptr [0xc1f4]
004c mov word ptr es:[0x72b0], ax
0050 mov dx, ax
0052 mov ax, cx
0054 mov bx, dx
0056 imul word ptr [0xcd7a] ; _editHeight
005a add bx, ax
005c mov word ptr es:[0x72b4], bx
0061 mov es, word ptr [0xc1e4]
0065 mov ax, word ptr es:[0x807c]
0069 mov es, word ptr [0xc1f0]
006d mov cx, ax
006f imul word ptr es:[0x7d2e]
0074 mov es, word ptr [0xc1f2]
0078 add ax, word ptr es:[0x8110]
007d mov es, word ptr [0xc1f6]
0081 add ax, word ptr es:[0x9bc6]
0086 mov es, word ptr [0xc1f4]
008a mov word ptr es:[0x72ae], ax
008e mov dx, ax
0090 mov ax, cx
0092 mov bx, dx
0094 imul word ptr [0xcc80] ; _editWidth
0098 add bx, ax
009a mov word ptr es:[0x72b2], bx
009f push 2
00a1 push es
00a2 push 0x72ae
00a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
00aa add sp, 6
00ad mov word ptr [0x1992], 1 ; _mapCursorState
00b3 nop 
00b4 push cs
00b5 call 0x8e4e ; _clip_Pop
00b8 retf 
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
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ProcMapRibbonEvent', 'offset': 50132, 'source': None, 'size': None}
- {'symbol': '_OpenMapWindow', 'offset': 50758, 'source': 'src/recovered/OpenMapWindow.c', 'size': 12}
- {'symbol': '_EraseMapCursor', 'offset': 50956, 'source': None, 'size': 66}
- {'symbol': '_ToggleMapCursor', 'offset': 51022, 'source': None, 'size': 261}
