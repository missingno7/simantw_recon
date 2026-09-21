# Recovery task _DrawMiniMapCursor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 155 bytes.

```asm
0000 mov es, word ptr [0xc22e]
0004 mov ax, word ptr es:[0x9be2]
0008 mov es, word ptr [0xc224]
000c mov cx, ax
000e imul word ptr es:[0x7d30]
0013 mov es, word ptr [0xc232]
0017 add ax, word ptr es:[0x7ef8]
001c mov es, word ptr [0xc234]
0020 mov word ptr es:[0x78e2], ax
0024 mov dx, ax
0026 mov ax, cx
0028 mov bx, dx
002a imul word ptr [0xcd7a] ; _editHeight
002e add bx, ax
0030 mov word ptr es:[0x78e6], bx
0035 mov es, word ptr [0xc230]
0039 mov ax, word ptr es:[0x9b88]
003d mov es, word ptr [0xc224]
0041 mov cx, ax
0043 imul word ptr es:[0x7d2e]
0048 mov es, word ptr [0xc236]
004c add ax, word ptr es:[0xa0b0]
0051 mov es, word ptr [0xc232]
0055 add ax, word ptr es:[0x7ef6]
005a mov es, word ptr [0xc234]
005e mov word ptr es:[0x78e0], ax
0062 mov dx, ax
0064 mov ax, cx
0066 mov bx, dx
0068 imul word ptr [0xcc80] ; _editWidth
006c add bx, ax
006e mov word ptr es:[0x78e4], bx
0073 push word ptr [0xbcce]
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 122, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
007c add sp, 2
007f push 1
0081 push <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0084 push 0x78e0
0087 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
008c add sp, 6
008f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0094 mov word ptr [0x1a34], 1 ; _mmapCursorState
009a retf 
```

## Known declaration examples

- `extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int near mmapCursorState;` — src/recovered/EraseMiniMapCursor.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Mini_MakeTable', 'offset': 58114, 'source': 'src/recovered/wf_Mini_MakeTable-a03e1a6138.c', 'size': 114}
- {'symbol': '_OpenMiniMapWin', 'offset': 58228, 'source': None, 'size': 1254}
- {'symbol': '_EraseMiniMapCursor', 'offset': 59638, 'source': 'src/recovered/EraseMiniMapCursor.c', 'size': 40}
- {'symbol': '_ToggleMiniMapCursor', 'offset': 59678, 'source': None, 'size': 203}
