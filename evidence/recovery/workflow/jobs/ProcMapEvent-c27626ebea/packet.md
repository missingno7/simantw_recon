# Recovery task _ProcMapEvent

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 434 bytes.

```asm
0000 enter 0xc, 0
0004 push si
0005 mov si, word ptr [bp + 6]
0008 mov es, word ptr [bp + 8]
000b mov ax, word ptr es:[si + 0xc]
000f sub ax, 0x102
0012 cmp ax, 0x16
0015 jbe 0xc23c
0017 jmp 0xc3d1
001a shl ax, 1
001c xchg bx, ax
001d jmp word ptr cs:[bx - 0x3dbc]
0022 dw offset 0xc272
0024 dw offset 0xc3d1
0026 dw offset 0xc3d1
0028 dw offset 0xc282
002a dw offset 0xc28a
002c dw offset 0xc29c
002e dw offset 0xc2a6
0030 dw offset 0xc2c0
0032 dw offset 0xc2ca
0034 dw offset 0xc2d4
0036 dw offset 0xc2d8
0038 dw offset 0xc2dc
003a dw offset 0xc2e0
003c dw offset 0xc31c
003e dw offset 0xc324
0040 dw offset 0xc386
0042 dw offset 0xc38e
0044 dw offset 0xc396
0046 dw offset 0xc39e
0048 dw offset 0xc3a6
004a dw offset 0xc3ae
004c dw offset 0xc3c4
004e dw offset 0xc3cc
0050 mov ax, es
0052 push ax
0053 push si
0054 nop 
0055 push cs
0056 call 0xe100 ; _MapAreaEvent
0059 add sp, 4
005c jmp 0xc3d1
005f nop 
0060 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MapToYard
0065 jmp 0xc3d1
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ClearMapScentButtons
006d push 1
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapPlane
0074 add sp, 2
0077 jmp 0xc3d1
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ClearMapScentButtons
007f push 2
0081 jmp 0xc291
0083 nop 
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ClearMapScentButtons
0089 push 3
008b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 142, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapPlane
0090 add sp, 2
0093 push 0x100
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_ToTop
009b jmp 0xc296
009d nop 
009e push 4
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapModeAnt
00a5 jmp 0xc2b2
00a7 nop 
00a8 push 5
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetMapModeAnt
00af jmp 0xc296
00b1 nop 
00b2 push 8
00b4 jmp 0xc2cc
00b6 push 6
00b8 jmp 0xc2cc
00ba push 7
00bc jmp 0xc2cc
00be cmp word ptr [0x1998], 0 ; _showTrails
00c3 jne 0xc30c
00c5 mov bx, 0x9bd2
00c8 mov es, word ptr [0xc1ea]
00cc mov word ptr [bp - 0xc], bx
00cf mov word ptr [bp - 0xa], es
00d2 cmp word ptr es:[bx], 0
00d6 je 0xc30c
00d8 mov word ptr es:[bx], 0
00dd nop 
00de push cs
00df call 0xcd3e ; _DrawMap
00e2 les bx, ptr [bp - 0xc]
00e5 mov word ptr es:[bx], 1
00ea cmp word ptr [0x1998], 1 ; _showTrails
00ef sbb ax, ax
00f1 neg ax
00f3 mov word ptr [0x1998], ax ; _showTrails
00f6 jmp 0xc3d1
00f9 nop 
00fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 253, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _OpenModeWindow
00ff jmp 0xc3d1
0102 push 0x11
0104 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0109 test ah, 0x80
010c je 0xc37e
010e push 0x10
0110 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0115 test ah, 0x80
0118 je 0xc370
011a lea ax, [bp - 8]
011d push ss
011e push ax
011f push 0x110
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0127 add sp, 6
012a mov ax, word ptr [bp - 4]
012d add ax, word ptr [bp - 8]
0130 cdq 
0131 sub ax, dx
0133 sar ax, 1
0135 mov es, word ptr [bp + 8]
0138 cmp word ptr es:[si + 8], ax
013c jl 0xc364
013e xor ax, ax
0140 jmp 0xc367
0142 mov ax, 1
0145 push ax
0146 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 329, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _AddSomeAnts
014b jmp 0xc296
014e push 1
0150 push 0x96
0153 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 342, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddFood
0158 jmp 0xc27b
015b nop 
015c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoMyAnt
0161 jmp 0xc3d1
0163 nop 
0164 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 359, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _OpenCasteWindow
0169 jmp 0xc3d1
016b nop 
016c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 367, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MysteryButton
0171 pop si
0172 leave 
0173 retf 
0174 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 375, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _OpenHistoryWindow
0179 pop si
017a leave 
017b retf 
017c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 383, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScoreDialog
0181 pop si
0182 leave 
0183 retf 
0184 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 391, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _OpenInfoWindow
0189 pop si
018a leave 
018b retf 
018c mov es, word ptr [0xc1ec]
0190 mov word ptr es:[0x9fb0], 1
0197 push 0x103
019a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 413, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoWinHelp
019f jmp 0xc296
01a2 nop 
01a3 push cs
01a4 call 0xdc1e ; _MapToolsMenu
01a7 pop si
01a8 leave 
01a9 retf 
01aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 429, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DrawCastePopUp
01af pop si
01b0 leave 
01b1 retf 
```

## Known declaration examples

- `extern void far AddFood(int a, int b);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far DoWinHelp(int mode);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern void far DrawMap(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern void far GotoMyAnt(void);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern void far MapToYard(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far OpenCasteWindow(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far OpenModeWindow(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_win_DrawPictureWindow-9fe716872a.c
- `extern void far win_ToTop(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DeinitMapFunctions', 'offset': 49562, 'source': 'src/recovered/DeinitMapFunctions.c', 'size': 1}
- {'symbol': '_InitMapFunctions', 'offset': 49564, 'source': 'src/recovered/wf_InitMapFunctions-70fb457ea5.c', 'size': 133}
- {'symbol': '_ProcMapRibbonEvent', 'offset': 50132, 'source': None, 'size': 626}
- {'symbol': '_OpenMapWindow', 'offset': 50758, 'source': 'src/recovered/OpenMapWindow.c', 'size': 12}
