# Recovery task _CenterAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 132 bytes.

```asm
0000 push 0x100
0003 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0008 add sp, 2
000b or ax, ax
000d je 0xa705
000f push word ptr [0xbca8]
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0018 add sp, 2
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EraseMapCursor
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0025 mov es, word ptr [0xc100]
0029 mov word ptr es:[0x9fb0], 1
0030 mov ax, word ptr [0xcc76] ; _MapPlane
0033 cmp word ptr [0xce80], ax ; _MePlane
0037 je 0xa725
0039 push word ptr [0xce80] ; _MePlane
003d nop 
003e push cs
003f call 0xa5ca ; _SetMapPlane
0042 add sp, 2
0045 push word ptr [0xce7e] ; _MeLocY
0049 push word ptr [0xcd88] ; _MeLocX
004d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _CenterEdit
0052 add sp, 4
0055 or ax, ax
0057 je 0xa73e
0059 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
005e push 0x100
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0066 add sp, 2
0069 or ax, ax
006b je 0xa763
006d push word ptr [0xbca8]
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0076 add sp, 2
0079 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 124, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMapCursor
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0083 retf 
```

## Known declaration examples

- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near MapPlane;` — src/recovered/wf_FinishHorzStep-6510fd44a5.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawYard-bff77801c5.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GotoMapPoint', 'offset': 42282, 'source': None, 'size': 160}
- {'symbol': '_SetMapPlane', 'offset': 42442, 'source': None, 'size': 277}
- {'symbol': '_GotoMyAnt', 'offset': 42852, 'source': None, 'size': 224}
- {'symbol': '_GotoSpider', 'offset': 43076, 'source': None, 'size': 205}
