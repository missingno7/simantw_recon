# Recovery task _win_SetObjSelectedStateI

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 331 bytes.

```asm
0000 enter 4, 0
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
0016 call 0xc32e ; _win_ObjAddr
0019 add sp, 2
001c mov si, ax
001e mov word ptr [bp - 2], dx
0021 push word ptr [bp + 6]
0024 nop 
0025 push cs
0026 call 0xc256 ; _win_IsWinOpen
0029 add sp, 2
002c or ax, ax
002e jne 0xed3b
0030 jmp 0xee2e
0033 mov bx, word ptr [bp + 8]
0036 mov es, word ptr [bp - 2]
0039 mov al, byte ptr es:[si + 0x24]
003d and ax, 4
0040 shr al, 2
0043 cmp ax, bx
0045 je 0xedb6
0047 mov al, byte ptr es:[si + 0x24]
004b shl bx, 2
004e xor al, bl
0050 and ax, 4
0053 xor word ptr es:[si + 0x24], ax
0057 test byte ptr es:[si + 0x24], 1
005c jne 0xed69
005e jmp 0xee44
0061 xor di, di
0063 cmp word ptr [0xcf52], di ; _clipDC
0067 jne 0xed88
0069 mov bx, word ptr [bp + 6]
006c sar bx, 8
006f shl bx, 1
0071 push word ptr [bx - 0x435a]
0075 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 120, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
007a add sp, 2
007d mov di, 1
0080 mov es, word ptr [bp - 2]
0083 mov al, byte ptr es:[si + 0x21]
0087 cwde 
0088 cmp ax, 0x11
008b je 0xedac
008d ja 0xed9f
008f sub al, 5
0091 je 0xedac
0093 sub al, 8
0095 je 0xede9
0097 push es
0098 push si
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GRectInv
009e add sp, 4
00a1 jmp 0xee23
00a3 nop 
00a4 push es
00a5 push si
00a6 nop 
00a7 push cs
00a8 call 0xbb44 ; _win_DrawObject
00ab jmp 0xeda6
00ad nop 
00ae test byte ptr es:[si + 0x24], 1
00b3 jne 0xedc0
00b5 jmp 0xee44
00b8 xor di, di
00ba cmp word ptr [0xcf52], di ; _clipDC
00be jne 0xeddf
00c0 mov bx, word ptr [bp + 6]
00c3 sar bx, 8
00c6 shl bx, 1
00c8 push word ptr [bx - 0x435a]
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipStart
00d1 add sp, 2
00d4 mov di, 1
00d7 mov es, word ptr [bp - 2]
00da cmp byte ptr es:[si + 0x21], 0xd
00df jne 0xee23
00e1 mov al, byte ptr [0xce97] ; _monoPat
00e4 and ax, 0x7f
00e7 push ax
00e8 push word ptr [0xce8a] ; __backColor
00ec push word ptr [0xcf4e] ; __foreColor
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
00f5 add sp, 6
00f8 mov es, word ptr [bp - 2]
00fb mov al, byte ptr es:[si + 0x24]
00ff and ax, 4
0102 cmp ax, 1
0105 sbb bx, bx
0107 and bx, 2
010a add bx, 2
010d push word ptr es:[bx + si + 0x26]
0111 push es
0112 push si
0113 nop 
0114 push cs
0115 call 0xbe30 ; _win_DrawBitMapAtObj
0118 add sp, 6
011b or di, di
011d je 0xee44
011f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 290, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MSClipEnd
0124 jmp 0xee44
0126 mov es, word ptr [bp - 2]
0129 mov al, byte ptr es:[si + 0x24]
012d mov cx, word ptr [bp + 8]
0130 shl cx, 2
0133 xor al, cl
0135 and ax, 4
0138 xor word ptr es:[si + 0x24], ax
013c push word ptr [bp + 6]
013f nop 
0140 push cs
0141 call 0xe3a4 ; _win_UnlockWin
0144 add sp, 2
0147 pop si
0148 pop di
0149 leave 
014a retf 
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
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_OpenMapYard-118a20a584.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern struct WinBitmapObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_MakeGroupSelectable', 'offset': 60428, 'source': None, 'size': 125}
- {'symbol': '_win_MakeGroupUnselectable', 'offset': 60554, 'source': None, 'size': 125}
- {'symbol': '_win_SetObjSelectedState', 'offset': 61012, 'source': None, 'size': 195}
- {'symbol': '_win_MakeObjSelected', 'offset': 61208, 'source': None, 'size': 194}
