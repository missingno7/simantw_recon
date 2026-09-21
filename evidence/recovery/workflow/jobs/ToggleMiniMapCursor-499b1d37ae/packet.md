# Recovery task _ToggleMiniMapCursor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 203 bytes.

```asm
0000 cmp word ptr [0x1a34], 0 ; _mmapCursorState
0005 je 0xe94e
0007 push word ptr [0xbcce]
000b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 14, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0010 add sp, 2
0013 push 1
0015 push <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0018 push 0x78e0
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
0020 add sp, 6
0023 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0028 mov word ptr [0x1a34], 0 ; _mmapCursorState
002e retf 
002f nop 
0030 mov es, word ptr [0xc22e]
0034 mov ax, word ptr es:[0x9be2]
0038 mov es, word ptr [0xc224]
003c mov cx, ax
003e imul word ptr es:[0x7d30]
0043 mov es, word ptr [0xc232]
0047 add ax, word ptr es:[0x7ef8]
004c mov es, word ptr [0xc234]
0050 mov word ptr es:[0x78e2], ax
0054 mov dx, ax
0056 mov ax, cx
0058 mov bx, dx
005a imul word ptr [0xcd7a] ; _editHeight
005e add bx, ax
0060 mov word ptr es:[0x78e6], bx
0065 mov es, word ptr [0xc230]
0069 mov ax, word ptr es:[0x9b88]
006d mov es, word ptr [0xc224]
0071 mov cx, ax
0073 imul word ptr es:[0x7d2e]
0078 mov es, word ptr [0xc236]
007c add ax, word ptr es:[0xa0b0]
0081 mov es, word ptr [0xc232]
0085 add ax, word ptr es:[0x7ef6]
008a mov es, word ptr [0xc234]
008e mov word ptr es:[0x78e0], ax
0092 mov dx, ax
0094 mov ax, cx
0096 mov bx, dx
0098 imul word ptr [0xcc80] ; _editWidth
009c add bx, ax
009e mov word ptr es:[0x78e4], bx
00a3 push word ptr [0xbcce]
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00ac add sp, 2
00af push 1
00b1 push <resolved loader operand; see bindings> ; [{'operand_offset': 178, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00b4 push 0x78e0
00b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInvOutline
00bc add sp, 6
00bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 194, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00c4 mov word ptr [0x1a34], 1 ; _mmapCursorState
00ca retf 
```

## Known declaration examples

- `extern void far GRectInvOutline(struct MiniMapRect far *rect, int color);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editHeight;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
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

- {'symbol': '_DrawMiniMapCursor', 'offset': 59482, 'source': None, 'size': 155}
- {'symbol': '_EraseMiniMapCursor', 'offset': 59638, 'source': 'src/recovered/EraseMiniMapCursor.c', 'size': 40}
