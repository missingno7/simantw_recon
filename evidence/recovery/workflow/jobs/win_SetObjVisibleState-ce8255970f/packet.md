# Recovery task _win_SetObjVisibleState

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 344 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0xc32e ; _win_ObjAddr
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov si, bx
0017 mov word ptr [bp - 2], es
001a mov al, byte ptr es:[bx + 0x24]
001e and ax, 1
0021 cmp ax, word ptr [bp + 8]
0024 jne 0xf2e5
0026 jmp 0xf410
0029 mov al, byte ptr es:[si + 0x24]
002d xor al, byte ptr [bp + 8]
0030 and ax, 1
0033 xor word ptr es:[si + 0x24], ax
0037 push word ptr [bp + 6]
003a nop 
003b push cs
003c call 0xc256 ; _win_IsWinOpen
003f add sp, 2
0042 or ax, ax
0044 jne 0xf305
0046 jmp 0xf410
0049 mov es, word ptr [bp - 2]
004c test byte ptr es:[si + 0x24], 1
0051 jne 0xf312
0053 jmp 0xf3ae
0056 test byte ptr es:[si + 0x24], 4
005b jne 0xf31c
005d jmp 0xf3ae
0060 xor di, di
0062 cmp word ptr [0xcf52], di ; _clipDC
0066 jne 0xf33b
0068 mov bx, word ptr [bp + 6]
006b sar bx, 8
006e shl bx, 1
0070 push word ptr [bx - 0x435a]
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
0079 add sp, 2
007c mov di, 1
007f mov es, word ptr [bp - 2]
0082 mov al, byte ptr es:[si + 0x21]
0086 cwde 
0087 cmp ax, 0x11
008a je 0xf36a
008c jbe 0xf34d
008e jmp 0xf407
0091 dec al
0093 je 0xf35c
0095 sub al, 4
0097 je 0xf36a
0099 sub al, 8
009b je 0xf374
009d jmp 0xf407
00a0 push es
00a1 push si
00a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 165, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
00a7 add sp, 4
00aa jmp 0xf407
00ad nop 
00ae push es
00af push si
00b0 nop 
00b1 push cs
00b2 call 0xbb44 ; _win_DrawObject
00b5 jmp 0xf363
00b7 nop 
00b8 mov al, byte ptr [0xce97] ; _monoPat
00bb and ax, 0x7f
00be push ax
00bf push word ptr [0xce8a] ; __backColor
00c3 push word ptr [0xcf4e] ; __foreColor
00c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 202, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
00cc add sp, 6
00cf mov es, word ptr [bp - 2]
00d2 mov al, byte ptr es:[si + 0x24]
00d6 and ax, 4
00d9 cmp ax, 1
00dc sbb bx, bx
00de and bx, 2
00e1 add bx, 2
00e4 push word ptr es:[bx + si + 0x26]
00e8 push es
00e9 push si
00ea nop 
00eb push cs
00ec call 0xbe30 ; _win_DrawBitMapAtObj
00ef jmp 0xf404
00f1 nop 
00f2 xor di, di
00f4 cmp word ptr [0xcf52], di ; _clipDC
00f8 jne 0xf3cd
00fa mov bx, word ptr [bp + 6]
00fd sar bx, 8
0100 shl bx, 1
0102 push word ptr [bx - 0x435a]
0106 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
010b add sp, 2
010e mov di, 1
0111 mov es, word ptr [bp - 2]
0114 mov al, byte ptr es:[si + 0x21]
0118 cwde 
0119 sub ax, 0xd
011c jne 0xf407
011e mov al, byte ptr [0xce97] ; _monoPat
0121 and ax, 0x7f
0124 push ax
0125 push word ptr [0xce8a] ; __backColor
0129 push word ptr [0xcf4e] ; __foreColor
012d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 304, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
0132 add sp, 6
0135 mov es, word ptr [bp - 2]
0138 push word ptr es:[si + 0x2a]
013c push word ptr es:[si + 2]
0140 push word ptr es:[si]
0143 nop 
0144 push cs
0145 call 0xbd5a ; _win_DrawBitMap
0148 add sp, 6
014b or di, di
014d je 0xf410
014f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 338, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0154 pop si
0155 pop di
0156 leave 
0157 retf 
```

## Known declaration examples

- `extern void far GRectInv(struct WinRect far *rect);` — src/recovered/wf_win_ObjInv-18e2e84ce2.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_win_SetColorFromObj-7570e08dca.c
- `extern void far MSClipEnd(void);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipEnd(void);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern void far MSClipStart(int window);` — src/recovered/EraseMiniMapCursor.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far MSClipStart(int window);` — src/recovered/wf_UpdateYardMessage-77b8db79c0.c
- `extern int near _backColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near _backColor;` — src/recovered/wf_GRectFillOutline-24e4a6aa35.c
- `extern int near _backColor;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern unsigned int near _foreColor;` — src/recovered/GCheckerBox.c
- `extern int near _foreColor;` — src/recovered/GRectChecker.c
- `extern int near _foreColor;` — src/recovered/wf_GBoxFillOutline-d99ffce56d.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_GPatBox-b326d1b571.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern unsigned char near monoPat;` — src/recovered/wf_GSetAttrib-bba4337448.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern char near monoPat;` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far win_DrawBitMap(unsigned int bitmapOffset, int bitmapArgument, int value);` — src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c
- `extern int far win_DrawBitMap(unsigned int bitmap, unsigned int bitmapMask, int bitmapNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern struct WinBitmapObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_MakeGroupSelected', 'offset': 61876, 'source': None, 'size': 132}
- {'symbol': '_win_MakeGroupUnselected', 'offset': 62008, 'source': None, 'size': 132}
- {'symbol': '_win_MakeObjVisible', 'offset': 62484, 'source': 'src/recovered/win_MakeObjVisible.c', 'size': 15}
- {'symbol': '_win_MakeObjInvisible', 'offset': 62500, 'source': 'src/recovered/win_MakeObjInvisible.c', 'size': 15}
