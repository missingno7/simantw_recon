# Recovery task _SetMapPlaneLocation

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 419 bytes.

```asm
0000 enter 6, 0
0004 push si
0005 mov si, word ptr [bp + 6]
0008 or si, si
000a je 0xa3b2
000c mov es, word ptr [0xc0ec]
0010 push word ptr es:[0x9b6c]
0015 mov es, word ptr [0xc0ee]
0019 push word ptr es:[0x7292]
001e push 0
0020 push 0
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvalEuMap
0027 add sp, 8
002a jmp 0xa3b8
002c mov ax, word ptr [0xcc76] ; _MapPlane
002f mov word ptr [0xcc78], ax ; _OldMapPlane
0032 mov word ptr [0xcc76], si ; _MapPlane
0036 mov ax, si
0038 dec ax
0039 jne 0xa3c6
003b mov ax, 0x80
003e jmp 0xa3c9
0040 mov ax, 0x40
0043 mov es, word ptr [0xc0ee]
0047 sub ax, word ptr es:[0x7292]
004c mov es, word ptr [0xc0f0]
0050 mov word ptr es:[0x769a], ax
0054 or si, si
0056 je 0xa40c
0058 push word ptr [bp + 0xa]
005b push word ptr [bp + 8]
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _CenterEdit
0063 add sp, 4
0066 or ax, ax
0068 je 0xa3f5
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
006f push 0x100
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
0077 add sp, 2
007a or ax, ax
007c je 0xa426
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
0083 jmp 0xa426
0085 nop 
0086 mov es, word ptr [0xc0f2]
008a mov ax, word ptr es:[0x7a60]
008e mov dx, word ptr es:[0x7a62]
0093 mov es, word ptr [0xc0f4]
0097 mov word ptr es:[0x789e], ax
009b mov word ptr es:[0x78a0], dx
00a0 push word ptr [0xcc76] ; _MapPlane
00a4 nop 
00a5 push cs
00a6 call 0x9e82 ; _SetMapModeAnt
00a9 add sp, 2
00ac xor ax, ax
00ae mov word ptr [bp - 6], ax
00b1 mov word ptr [bp - 4], ax
00b4 mov word ptr [bp - 2], ax
00b7 mov ax, word ptr [0xcc76] ; _MapPlane
00ba or ax, ax
00bc je 0xa450
00be dec ax
00bf je 0xa45e
00c1 dec ax
00c2 je 0xa478
00c4 dec ax
00c5 je 0xa492
00c7 jmp 0xa4aa
00c9 nop 
00ca cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
00cf jne 0xa4aa
00d1 mov word ptr [bp - 4], 0x105
00d6 jmp 0xa4aa
00d8 cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
00dd je 0xa46c
00df mov word ptr [bp - 6], 0x2205
00e4 jmp 0xa4aa
00e6 mov word ptr [bp - 2], 8
00eb mov word ptr [bp - 4], 0x106
00f0 jmp 0xa4aa
00f2 cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
00f7 je 0xa486
00f9 mov word ptr [bp - 6], 0x2203
00fe jmp 0xa4aa
0100 mov word ptr [bp - 2], 9
0105 mov word ptr [bp - 4], 0x107
010a jmp 0xa4aa
010c cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
0111 je 0xa4a0
0113 mov word ptr [bp - 6], 0x2204
0118 jmp 0xa4aa
011a mov word ptr [bp - 2], 0xa
011f mov word ptr [bp - 4], 0x108
0124 cmp word ptr [bp - 2], 0
0128 je 0xa4ca
012a push 0
012c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 303, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0131 add sp, 2
0134 push word ptr [bp - 2]
0137 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
013c add sp, 2
013f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 322, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
0144 cmp word ptr [bp - 6], 0
0148 je 0xa4ea
014a push 0
014c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 335, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0151 add sp, 2
0154 push word ptr [bp - 6]
0157 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 346, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
015c add sp, 2
015f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 354, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
0164 cmp word ptr [bp - 4], 0
0168 je 0xa526
016a push 0x100
016d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
0172 add sp, 2
0175 push word ptr [bp - 4]
0178 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 379, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjSelected
017d add sp, 2
0180 cmp word ptr [0xcd76], 0 ; _ribbonBarWnd
0185 je 0xa514
0187 push 2
0189 push 0x2300
018c jmp 0xa519
018e push 2
0190 push 0x100
0193 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 406, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeGroupUnselected
0198 add sp, 4
019b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 414, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
01a0 pop si
01a1 leave 
01a2 retf 
```

## Known declaration examples

- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far CenterEdit(int x, int y);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far InvalEuMap(int left, int top, int right, int bottom);` — src/recovered/wf_tu_simant_6A38_SetAlarmDropState_2_scaffold-bb12a76f6c.c
- `extern void far InvalEuMap(int a, int b, int columns, int rows);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far UpdateEdit(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far clip_Off(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near ribbonBarWnd;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far win_MakeGroupUnselected(int id1, int id2);` — src/recovered/wf_SetMapModeAnt-f674ac382e.c
- `extern void far win_MakeObjSelected(int object);` — src/recovered/wf_SetMapModeAnt-f674ac382e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetMapModeAnt', 'offset': 40578, 'source': 'src/recovered/wf_SetMapModeAnt-f674ac382e.c', 'size': 274}
- {'symbol': '_SetYardMode', 'offset': 40852, 'source': None, 'size': 1009}
- {'symbol': '_GotoMapPoint', 'offset': 42282, 'source': 'src/recovered/wf_GotoMapPoint-52cd2a4427.c', 'size': 160}
- {'symbol': '_SetMapPlane', 'offset': 42442, 'source': None, 'size': 277}
