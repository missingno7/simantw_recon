# Recovery task _win_ClearObjToEOL

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 290 bytes.

```asm
0000 enter 0x16, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0xe3a8 ; _win_LockWin
000e add sp, 2
0011 push word ptr [bp + 6]
0014 nop 
0015 push cs
0016 call 0xe3a8 ; _win_LockWin
0019 add sp, 2
001c mov bl, byte ptr [bp + 6]
001f sub bh, bh
0021 mov word ptr [bp - 0x16], bx
0024 shl bx, 2
0027 mov si, word ptr [bp + 6]
002a sar si, 8
002d shl si, 2
0030 add si, 0xce9a
0034 mov word ptr [bp - 0x14], si
0037 les si, ptr [si]
0039 mov ax, word ptr es:[bx + si + 0x2c]
003d mov dx, word ptr es:[bx + si + 0x2e]
0041 push ds
0042 lea di, [bp - 0x12]
0045 mov si, ax
0047 push ss
0048 pop es
0049 mov ds, dx
004b movsw word ptr es:[di], word ptr [si]
004c movsw word ptr es:[di], word ptr [si]
004d movsw word ptr es:[di], word ptr [si]
004e movsw word ptr es:[di], word ptr [si]
004f pop ds
0050 cmp word ptr [0xbd0a], 0 ; _ribbonBarHeight
0055 je 0xd7ef
0057 inc word ptr [bp - 0xe]
005a inc word ptr [bp - 0xc]
005d push word ptr [bp + 6]
0060 nop 
0061 push cs
0062 call 0xe3a4 ; _win_UnlockWin
0065 add sp, 2
0068 mov ax, word ptr [bp - 0x16]
006b mov bx, word ptr [bp - 0x14]
006e les bx, ptr [bx]
0070 mov si, bx
0072 mov word ptr [bp - 8], es
0075 cmp word ptr es:[bx + 0xc], ax
0079 jg 0xd819
007b push ds
007c push 0xbd12
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
0084 add sp, 4
0087 mov es, word ptr [bp - 8]
008a mov bx, word ptr [bp - 0x16]
008d shl bx, 2
0090 add bx, si
0092 les bx, ptr es:[bx + 0x2c]
0096 mov al, byte ptr es:[bx + 0x26]
009a cwde 
009b mov cx, ax
009d test byte ptr [0xcc7e], 1 ; _displayType
00a2 je 0xd84a
00a4 mov es, word ptr [0xc6d6]
00a8 mov bx, cx
00aa shl bx, 1
00ac add bx, ax
00ae shl bx, 1
00b0 mov al, byte ptr es:[bx + 0x78ef]
00b5 jmp 0xd85b
00b7 nop 
00b8 mov es, word ptr [0xc6d6]
00bc mov bx, ax
00be shl bx, 1
00c0 add bx, ax
00c2 shl bx, 1
00c4 mov al, byte ptr es:[bx + 0x78ee]
00c9 cwde 
00ca mov cx, ax
00cc mov al, cl
00ce mov ah, cl
00d0 mov cx, ax
00d2 mov es, word ptr [0xc6da]
00d6 mov di, word ptr es:[0x7694]
00db mov word ptr [bp - 6], cx
00de cmp di, word ptr [bp - 0x10]
00e1 jge 0xd878
00e3 mov di, word ptr [bp - 0x10]
00e6 cmp word ptr [bp - 0xc], di
00e9 jle 0xd8a5
00eb mov word ptr [bp - 4], di
00ee mov ax, word ptr es:[0x7692]
00f2 mov word ptr [bp - 2], ax
00f5 cmp ax, word ptr [bp - 0x12]
00f8 jl 0xd8a5
00fa mov ax, word ptr [bp - 0xe]
00fd cmp word ptr [bp - 2], ax
0100 jge 0xd8a5
0102 push cx
0103 push word ptr [bp - 0xc]
0106 push ax
0107 push di
0108 push word ptr [bp - 2]
010b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 270, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GBoxFill
0110 add sp, 0xa
0113 push word ptr [bp + 6]
0116 nop 
0117 push cs
0118 call 0xe3a4 ; _win_UnlockWin
011b add sp, 2
011e pop si
011f pop di
0120 leave 
0121 retf 
```

## Known declaration examples

- `extern void GBoxFill(int,int,int,int,int);` — src/recovered/GRectFill.c
- `extern void far GBoxFill(int left, int top, int right, int bottom, int color);` — src/recovered/GTextBox.c
- `extern void far GBoxFill(int x1, int y1, int x2, int y2, int color);` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_CenterStrAtObj', 'offset': 54842, 'source': 'src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c', 'size': 160}
- {'symbol': '_win_PrintfAtObj', 'offset': 55002, 'source': 'src/recovered/wf_win_PrintfAtObj-9e4b836702.c', 'size': 183}
- {'symbol': '_win_ObjFormatPrint', 'offset': 55476, 'source': None, 'size': 552}
- {'symbol': '_win_DrawHBar', 'offset': 56028, 'source': None, 'size': 192}
