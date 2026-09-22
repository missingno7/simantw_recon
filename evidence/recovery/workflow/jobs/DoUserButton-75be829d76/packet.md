# Recovery task _DoUserButton

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 994 bytes.

```asm
0000 enter 0x34, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov ax, si
000b cmp ah, 0x22
000e jne 0x4da
0010 mov ax, 0x12
0013 jmp 0x4dd
0015 nop 
0016 mov ax, 0x22
0019 mov di, ax
001b mov word ptr [bp - 6], ds
001e push 0x11
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0025 test ah, 0x80
0028 jne 0x4f1
002a jmp 0x650
002d mov es, word ptr [0xbe6e]
0031 mov ax, word ptr es:[0x9c28]
0035 mov word ptr [bp - 4], ax
0038 lea ax, [bp - 0x14]
003b push ss
003c push ax
003d push si
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetObjRect
0043 add sp, 6
0046 push 0
0048 push word ptr [bp - 0x14]
004b push 0x2400
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0053 add sp, 6
0056 push word ptr [0xbcee]
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MySetCapture
005f add sp, 2
0062 mov bx, word ptr [bp + 8]
0065 shl bx, 1
0067 mov word ptr [bp - 0x2a], bx
006a add bx, di
006c mov es, word ptr [bp - 6]
006f mov word ptr [bp - 0x28], bx
0072 mov word ptr [bp - 0x26], es
0075 mov ax, word ptr es:[bx]
0078 add ax, 0x2402
007b push ax
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; __win_SetProxItem
0081 add sp, 2
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldInit
0089 push 1
008b nop 
008c push cs
008d call 0x4e34 ; _SetPause
0090 add sp, 2
0093 mov word ptr [bp - 8], di
0096 lea ax, [bp - 0x24]
0099 push ss
009a push ax
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetEvent
00a0 add sp, 4
00a3 or ax, ax
00a5 je 0x55a
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _ButtonHeldEnd
00ac push word ptr [bp - 4]
00af nop 
00b0 push cs
00b1 call 0x4e34 ; _SetPause
00b4 add sp, 2
00b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 186, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _MyReleaseCapture
00bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_GetProxEvent
00c1 mov di, ax
00c3 push 0x2400
00c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; __win_SetProxItem
00cb add sp, 2
00ce push word ptr [0xbcee]
00d2 lea ax, [bp - 0x14]
00d5 push ss
00d6 push ax
00d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 216, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 32}}]
00dc push 0x2400
00df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 226, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
00e4 add sp, 2
00e7 mov ax, word ptr [bp - 0x1c]
00ea mov word ptr [bp - 0xc], ax
00ed mov ax, word ptr [bp - 0x1a]
00f0 mov word ptr [bp - 0xa], ax
00f3 push word ptr [0xbcee]
00f7 lea ax, [bp - 0xc]
00fa push ss
00fb push ax
00fc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 253, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 28}}]
0101 lea ax, [bp - 0x14]
0104 push ss
0105 push ax
0106 push word ptr [bp - 0xa]
0109 push word ptr [bp - 0xc]
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 269, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 76}}]
0111 or ax, ax
0113 jne 0x5dc
0115 jmp 0x8a2
0118 lea ax, [di - 0x2402]
011c mov word ptr [bp - 0x2c], ax
011f les bx, ptr [bp - 0x28]
0122 mov word ptr es:[bx], ax
0125 push 0x10
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 296, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
012c test ah, 0x80
012f je 0x60a
0131 les bx, ptr [bp - 0x28]
0134 push word ptr es:[bx]
0137 push word ptr [bp + 6]
013a nop 
013b push cs
013c call 0x36a ; _SetUserButton
013f add sp, 4
0142 jmp 0x8a2
0145 nop 
0146 mov word ptr [bp - 2], di
0149 mov ax, word ptr [bp - 0x2c]
014c mov bx, word ptr [bp - 0x2a]
014f mov word ptr [bx + 0x22], ax
0153 mov word ptr [bx + 0x12], ax
0157 les bx, ptr [bp - 0x28]
015a push word ptr es:[bx]
015d push word ptr [bp + 6]
0160 nop 
0161 push cs
0162 call 0x36a ; _SetUserButton
0165 add sp, 4
0168 cmp byte ptr [bp + 7], 0x22
016c jne 0x642
016e les bx, ptr [bp - 0x28]
0171 push word ptr es:[bx]
0174 mov ax, word ptr [bp + 6]
0177 add ax, 0xfb
017a push ax
017b jmp 0x5fe
017d nop 
017e les bx, ptr [bp - 0x28]
0181 push word ptr es:[bx]
0184 mov ax, word ptr [bp + 6]
0187 sub ax, 0xfb
018a jmp 0x63e
018c mov es, word ptr [bp - 6]
018f mov bx, word ptr [bp + 8]
0192 shl bx, 1
0194 add bx, di
0196 mov ax, word ptr es:[bx]
0199 cmp ax, 0xf
019c jbe 0x665
019e jmp 0x8a2
01a1 shl ax, 1
01a3 xchg bx, ax
01a4 jmp word ptr cs:[bx + 0x66e]
01a9 nop 
01aa dw offset 0x68e
01ac dw offset 0x696
01ae dw offset 0x69e
01b0 dw offset 0x6a6
01b2 dw offset 0x6ae
01b4 dw offset 0x6f8
01b6 dw offset 0x712
01b8 dw offset 0x78c
01ba dw offset 0x7bc
01bc dw offset 0x7c6
01be dw offset 0x7e2
01c0 dw offset 0x7f6
01c2 dw offset 0x80a
01c4 dw offset 0x81e
01c6 dw offset 0x832
01c8 dw offset 0x860
01ca nop 
01cb push cs
01cc call 0xffffbc7a
01cf jmp 0x8a2
01d2 nop 
01d3 push cs
01d4 call 0xffffbbec
01d7 jmp 0x8a2
01da nop 
01db push cs
01dc call 0xffff8a6a
01df jmp 0x8a2
01e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 485, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _OpenInfoWindow
01e7 jmp 0x8a2
01ea mov bx, 0x1998
01ed mov es, word ptr [0xbe74]
01f1 mov word ptr [bp - 0x30], bx
01f4 mov word ptr [bp - 0x2e], es
01f7 cmp word ptr es:[bx], 0
01fb jne 0x6e6
01fd mov bx, 0x9bd2
0200 mov es, word ptr [0xbe76]
0204 mov word ptr [bp - 0x34], bx
0207 mov word ptr [bp - 0x32], es
020a cmp word ptr es:[bx], 0
020e je 0x6e6
0210 mov word ptr es:[bx], 0
0215 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 536, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawMap
021a les bx, ptr [bp - 0x34]
021d mov word ptr es:[bx], 1
0222 les bx, ptr [bp - 0x30]
0225 cmp word ptr es:[bx], 1
0229 sbb ax, ax
022b neg ax
022d mov word ptr es:[bx], ax
0230 jmp 0x8a2
0233 nop 
0234 mov es, word ptr [0xbe6e]
0238 xor byte ptr es:[0x9c28], 1
023e push word ptr es:[0x9c28]
0243 nop 
0244 push cs
0245 call 0x4e34 ; _SetPause
0248 add sp, 2
024b jmp 0x8a2
024e mov <resolved loader operand; see bindings> ; [{'operand_offset': 591, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0251 mov es, ax
0253 cmp word ptr es:[0x8614], 3
0259 jne 0x728
025b mov word ptr es:[0x8614], 0
0262 jmp 0x72d
0264 inc word ptr es:[0x8614]
0269 nop 
026a push cs
026b call 0x4c24 ; _SetMenuEntries
026e mov es, word ptr [0xbe78]
0272 mov ax, word ptr es:[0x8614]
0276 or ax, ax
0278 je 0x74a
027a dec ax
027b je 0x762
027d dec ax
027e je 0x770
0280 dec ax
0281 je 0x77e
0283 jmp 0x8a2
0286 push 1
0288 push 0
028a push 0xb4
028d push ds
028e push 0x14b
0291 nop 
0292 push cs
0293 call 0xffff92c0
0296 add sp, 0xa
0299 pop si
029a pop di
029b leave 
029c retf 
029d nop 
029e push 1
02a0 push 0
02a2 push 0xb4
02a5 push ds
02a6 push 0x160
02a9 jmp 0x755
02ab nop 
02ac push 1
02ae push 0
02b0 push 0xb4
02b3 push ds
02b4 push 0x177
02b7 jmp 0x755
02b9 nop 
02ba push 1
02bc push 0
02be push 0xb4
02c1 push ds
02c2 push 0x18c
02c5 jmp 0x755
02c7 nop 
02c8 mov es, word ptr [0xbe70]
02cc cmp word ptr es:[0x85f4], 1
02d2 sbb ax, ax
02d4 neg ax
02d6 mov word ptr es:[0x85f4], ax
02da nop 
02db push cs
02dc call 0x4c24 ; _SetMenuEntries
02df mov es, word ptr [0xbe70]
02e3 cmp word ptr es:[0x85f4], 0
02e9 je 0x7b2
02eb jmp 0x8a2
02ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 753, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _StopSong
02f3 pop si
02f4 pop di
02f5 leave 
02f6 retf 
02f7 nop 
02f8 nop 
02f9 push cs
02fa call 0xffffb0bc
02fd pop si
02fe pop di
02ff leave 
0300 retf 
0301 nop 
0302 mov es, word ptr [0xbe70]
0306 cmp word ptr es:[0x85f6], 1
030c sbb ax, ax
030e neg ax
0310 mov word ptr es:[0x85f6], ax
0314 nop 
0315 push cs
0316 call 0x4c24 ; _SetMenuEntries
0319 pop si
031a pop di
031b leave 
031c retf 
031d nop 
031e mov es, word ptr [0xbe70]
0322 cmp word ptr es:[0x85fc], 1
0328 sbb ax, ax
032a neg ax
032c mov word ptr es:[0x85fc], ax
0330 jmp 0x7d8
0332 mov es, word ptr [0xbe70]
0336 cmp word ptr es:[0x85f2], 1
033c sbb ax, ax
033e neg ax
0340 mov word ptr es:[0x85f2], ax
0344 jmp 0x7d8
0346 mov es, word ptr [0xbe70]
034a cmp word ptr es:[0x85f8], 1
0350 sbb ax, ax
0352 neg ax
0354 mov word ptr es:[0x85f8], ax
0358 jmp 0x7d8
035a mov es, word ptr [0xbe70]
035e cmp word ptr es:[0x85fa], 1
0364 sbb ax, ax
0366 neg ax
0368 mov word ptr es:[0x85fa], ax
036c jmp 0x7d8
036e push word ptr [0xcd78] ; _rootWnd
0372 push 0
0374 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 885, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 12}}]
0379 push 1
037b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 894, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _SaveGame
0380 add sp, 2
0383 push word ptr [0xcd78] ; _rootWnd
0387 push 0
0389 push 0x11
038b push word ptr [0x42]
038f push word ptr [0x40] ; _lpTimerFunc
0393 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 916, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 10}}]
0398 pop si
0399 pop di
039a leave 
039b retf 
039c push 0x1900
039f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 930, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
03a4 add sp, 2
03a7 or ax, ax
03a9 je 0x874
03ab nop 
03ac push cs
03ad call 0xffff972a
03b0 push 0
03b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 949, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
03b7 add sp, 2
03ba or ax, ax
03bc jne 0x88b
03be push ax
03bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 962, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
03c4 add sp, 2
03c7 push word ptr [0xbca6] ; _win_hwnd
03cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 972, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
03d0 push word ptr [0xbca6] ; _win_hwnd
03d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 981, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
03d9 nop 
03da push cs
03db call 0xffffa764
03de pop si
03df pop di
03e0 leave 
03e1 retf 
```

## Known declaration examples

- `extern void far DrawMap(void);` — src/recovered/wf_GotoMapPoint-52cd2a4427.c
- `extern void far DrawMap(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern void far SetPause(int pause);` — src/recovered/wf_ProcEditEvent-1e056fd3ba.c
- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern void far win_GetObjRect(int object, struct ScentRect far *rect);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_InitTriVars-e97b7c6f72.c
- `extern void far win_GetObjRect(int object, struct WinRect far *rect);` — src/recovered/wf_win_DrawPictureWindow-9fe716872a.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/MakeEditOpen.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern void far win_Open(int window);` — src/recovered/MakeEditOpen.c
- `extern void far win_Open(int flags);` — src/recovered/OpenEditWindow.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c
- `extern int near win_hwnd[];` — src/recovered/EraseMiniMapCursor.c
- `extern int near win_hwnd;` — src/recovered/InvalidUpdateEdit.c
- `extern int near win_hwnd[];` — src/recovered/wf_CenterAnt-5b585d8f15.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateUserButtons', 'offset': 570, 'source': 'src/recovered/wf_UpdateUserButtons-609b2b7960.c', 'size': 303}
- {'symbol': '_SetUserButton', 'offset': 874, 'source': None, 'size': 345}
- {'symbol': '_DoBookMark', 'offset': 2214, 'source': None, 'size': 513}
- {'symbol': '_ClearBookmarks', 'offset': 2728, 'source': 'src/recovered/wf_ClearBookmarks-ffba50efd3.c', 'size': 125}
