# Recovery task _GotoMapPoint

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 160 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push 0x100
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
000b mov sp, bp
000d or ax, ax
000f je 0xa550
0011 push word ptr [0xbca8]
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
001a mov sp, bp
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EraseMapCursor
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0026 mov ax, word ptr [0xcc76] ; _MapPlane
0029 cmp word ptr [bp + 6], ax
002c jne 0xa582
002e cmp word ptr [bp + 6], 0
0032 jle 0xa582
0034 push word ptr [bp + 0xa]
0037 push word ptr [bp + 8]
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _CenterEdit
003f mov sp, bp
0041 or ax, ax
0043 je 0xa574
0045 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
004a mov es, word ptr [0xc0f6]
004e mov word ptr es:[0x72f0], 0
0055 jmp 0xa5a5
0057 nop 
0058 push word ptr [bp + 0xa]
005b push word ptr [bp + 8]
005e push word ptr [bp + 6]
0061 nop 
0062 push cs
0063 call 0xa386 ; _SetMapPlaneLocation
0066 mov sp, bp
0068 push 0x100
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0070 mov sp, bp
0072 or ax, ax
0074 je 0xa5a5
0076 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
007b push 0x100
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0083 mov sp, bp
0085 or ax, ax
0087 je 0xa5c8
0089 push word ptr [0xbca8]
008d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0092 mov sp, bp
0094 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 151, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMapCursor
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
009e leave 
009f retf 
```

## Known declaration examples

- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far DrawMap(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawRibbonMessage-0779d6fc14.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawYard-bff77801c5.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetYardMode', 'offset': 40852, 'source': None, 'size': 1009}
- {'symbol': '_SetMapPlaneLocation', 'offset': 41862, 'source': None, 'size': 419}
- {'symbol': '_SetMapPlane', 'offset': 42442, 'source': None, 'size': 277}
- {'symbol': '_CenterAnt', 'offset': 42720, 'source': 'src/recovered/wf_CenterAnt-5b585d8f15.c', 'size': 132}
