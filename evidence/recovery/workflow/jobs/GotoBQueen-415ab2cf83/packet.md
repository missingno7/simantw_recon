# Recovery task _GotoBQueen

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 205 bytes.

```asm
0000 enter 6, 0
0004 push si
0005 cmp word ptr [0xcc84], 0x60 ; _MeType
000a je 0xaac5
000c jmp 0xab76
000f mov si, word ptr [0xce80] ; _MePlane
0013 mov ax, word ptr [0xcd88] ; _MeLocX
0016 mov word ptr [bp - 6], ax
0019 mov ax, word ptr [0xce7e] ; _MeLocY
001c mov word ptr [bp - 4], ax
001f push 0x100
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0027 add sp, 2
002a or ax, ax
002c je 0xaafa
002e push word ptr [0xbca8]
0032 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0037 add sp, 2
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EraseMapCursor
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0044 cmp word ptr [0xcc76], si ; _MapPlane
0048 jne 0xab28
004a or si, si
004c jle 0xab28
004e push word ptr [bp - 4]
0051 push word ptr [bp - 6]
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _CenterEdit
0059 add sp, 4
005c or ax, ax
005e je 0xab1b
0060 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0065 mov es, word ptr [0xc0f6]
0069 mov word ptr es:[0x72f0], 0
0070 jmp 0xab4e
0072 mov word ptr [bp - 2], si
0075 push word ptr [bp - 4]
0078 push word ptr [bp - 6]
007b push si
007c nop 
007d push cs
007e call 0xa386 ; _SetMapPlaneLocation
0081 add sp, 6
0084 push 0x100
0087 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
008c add sp, 2
008f or ax, ax
0091 je 0xab4e
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 150, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
0098 push 0x100
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
00a0 add sp, 2
00a3 or ax, ax
00a5 je 0xab80
00a7 push word ptr [0xbca8]
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00b0 add sp, 2
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 182, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMapCursor
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
00bd pop si
00be leave 
00bf retf 
00c0 push 0x60
00c2 nop 
00c3 push cs
00c4 call 0xa912 ; _GotoQueen
00c7 add sp, 2
00ca pop si
00cb leave 
00cc retf 
```

## Known declaration examples

- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far DrawMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far EraseMapCursor(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far GotoQueen(int value);` — src/recovered/GotoRQueen.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DoDebugWin-501185d015.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern void far SetMapPlaneLocation(int plane, int x, int y);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GotoSpider', 'offset': 43076, 'source': None, 'size': 205}
- {'symbol': '_GotoQueen', 'offset': 43282, 'source': None, 'size': 420}
- {'symbol': '_GotoRQueen', 'offset': 43908, 'source': 'src/recovered/GotoRQueen.c', 'size': 12}
- {'symbol': '_XferPatch', 'offset': 43920, 'source': None, 'size': 385}
