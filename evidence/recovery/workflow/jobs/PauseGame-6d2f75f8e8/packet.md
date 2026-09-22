# Recovery task _PauseGame

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 369 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 or di, di
000a jne 0x4cef
000c mov <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000f mov es, ax
0011 cmp word ptr es:[0x7c22], 0xa
0017 jne 0x4ce2
0019 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndLifeTransferMode
001e jmp 0x4cef
0020 cmp word ptr es:[0x7c22], 0xb
0026 jne 0x4cef
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndTargetMode
002d mov es, word ptr [0xbecc]
0031 mov word ptr es:[0x9c28], di
0036 or di, di
0038 je 0x4d6a
003a mov es, word ptr [0xbed4]
003e cmp word ptr es:[0x7c22], -1
0044 jne 0x4d22
0046 push 1
0048 push -1
004a push -2
004c mov es, word ptr [0xbed6]
0050 les bx, ptr es:[0x737a]
0055 push word ptr es:[bx + 0xa]
0059 push word ptr es:[bx + 8]
005d jmp 0x4d74
005f nop 
0060 mov <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0063 mov es, ax
0065 cmp word ptr es:[0x7c22], 0xa
006b jne 0x4d48
006d push 1
006f push -1
0071 push -2
0073 mov es, word ptr [0xbed6]
0077 les bx, ptr es:[0x737a]
007c push word ptr es:[bx + 0xe]
0080 push word ptr es:[bx + 0xc]
0084 jmp 0x4d74
0086 cmp word ptr es:[0x7c22], 0xb
008c jne 0x4d7c
008e push 1
0090 push -1
0092 push -2
0094 mov es, word ptr [0xbed6]
0098 les bx, ptr es:[0x737a]
009d push word ptr es:[bx + 0x46]
00a1 push word ptr es:[bx + 0x44]
00a5 jmp 0x4d74
00a7 nop 
00a8 push 1
00aa push -1
00ac push -2
00ae push 0
00b0 push 0
00b2 nop 
00b3 push cs
00b4 call 0x92c0 ; _EditMessage
00b7 add sp, 0xa
00ba push 0
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
00c1 add sp, 2
00c4 push di
00c5 push 0xf
00c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 202, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
00cc add sp, 4
00cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 210, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
00d4 mov si, 0x43
00d7 mov ax, si
00d9 mov es, word ptr [0xbeca]
00dd sub ax, word ptr es:[0x8614]
00e2 cmp ax, 0x43
00e5 jne 0x4dae
00e7 mov ax, 0x10
00ea jmp 0x4db1
00ec mov ax, 0x20
00ef push ax
00f0 push si
00f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 244, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
00f6 add sp, 4
00f9 inc si
00fa cmp si, 0x46
00fd jle 0x4d99
00ff mov es, word ptr [0xbecc]
0103 cmp word ptr es:[0x9c28], 0
0109 je 0x4dd2
010b mov ax, 0x900
010e jmp 0x4dd5
0110 mov ax, 0x911
0113 push ds
0114 push ax
0115 push 0x41
0117 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuOptionText
011c add sp, 6
011f mov di, 0x31
0122 mov si, 0x85f2
0125 mov es, word ptr [0xbece]
0129 cmp word ptr es:[si], 1
012d sbb ax, ax
012f and ax, 0x10
0132 add ax, 0x10
0135 push ax
0136 push di
0137 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 314, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
013c add sp, 4
013f add si, 2
0142 inc di
0143 cmp di, 0x36
0146 jle 0x4de7
0148 nop 
0149 push cs
014a call 0x23a ; _UpdateUserButtons
014d mov es, word ptr [0xbece]
0151 mov ax, word ptr es:[0x85f4]
0155 mov es, word ptr [0xbed0]
0159 mov word ptr es:[0xaf6], ax
015d mov es, word ptr [0xbece]
0161 mov ax, word ptr es:[0x85f6]
0165 mov es, word ptr [0xbed2]
0169 mov word ptr es:[0xaf8], ax
016d pop si
016e pop di
016f leave 
0170 retf 
```

## Known declaration examples

- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far EndTargetMode(void);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far SetMenuItemState(int item, int state);` — src/recovered/wf_SetMenuEntries-c937b84870.c
- `extern void far SetMenuOptionText(int item, char far *text);` — src/recovered/wf_SetMenuEntries-c937b84870.c
- `extern void far UpdateUserButtons(void);` — src/recovered/wf_SetMenuEntries-c937b84870.c
- `extern void far clip_Off(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_UpdateUserButtons-609b2b7960.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClosePalette', 'offset': 19468, 'source': 'src/recovered/ClosePalette.c', 'size': 23}
- {'symbol': '_SetMenuEntries', 'offset': 19492, 'source': 'src/recovered/wf_SetMenuEntries-c937b84870.c', 'size': 158}
- {'symbol': '_SetPause', 'offset': 20020, 'source': None, 'size': 369}
- {'symbol': '_ProcMenuHelp', 'offset': 20390, 'source': 'src/recovered/ProcMenuHelp.c', 'size': 27}
