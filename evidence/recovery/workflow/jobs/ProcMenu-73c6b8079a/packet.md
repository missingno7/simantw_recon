# Recovery task _ProcMenu

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 1186 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov es, word ptr [bp + 8]
000c push word ptr es:[si + 0xc]
0010 push ds
0011 push 0x920
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0019 add sp, 6
001c mov es, word ptr [bp + 8]
001f mov al, byte ptr es:[si + 0xc]
0023 sub ah, ah
0025 mov word ptr [bp - 2], ax
0028 dec ax
0029 cmp ax, 0x45
002c jbe 0x4ff3
002e jmp 0x5088
0031 shl ax, 1
0033 xchg bx, ax
0034 jmp word ptr cs:[bx + 0x4ffc]
0039 nop 
003a dw offset 0x509e
003c dw offset 0x5088
003e dw offset 0x50a6
0040 dw offset 0x50c0
0042 dw offset 0x50c0
0044 dw offset 0x50c0
0046 dw offset 0x5088
0048 dw offset 0x50c0
004a dw offset 0x5088
004c dw offset 0x5088
004e dw offset 0x5088
0050 dw offset 0x5088
0052 dw offset 0x5088
0054 dw offset 0x5088
0056 dw offset 0x5088
0058 dw offset 0x5088
005a dw offset 0x50ce
005c dw offset 0x50d6
005e dw offset 0x50de
0060 dw offset 0x50e6
0062 dw offset 0x50ee
0064 dw offset 0x50f6
0066 dw offset 0x50fe
0068 dw offset 0x5106
006a dw offset 0x5088
006c dw offset 0x5088
006e dw offset 0x5088
0070 dw offset 0x5088
0072 dw offset 0x5088
0074 dw offset 0x5088
0076 dw offset 0x5088
0078 dw offset 0x5088
007a dw offset 0x511e
007c dw offset 0x511e
007e dw offset 0x511e
0080 dw offset 0x511e
0082 dw offset 0x5088
0084 dw offset 0x519a
0086 dw offset 0x51ac
0088 dw offset 0x51b0
008a dw offset 0x5088
008c dw offset 0x5088
008e dw offset 0x5088
0090 dw offset 0x5088
0092 dw offset 0x5088
0094 dw offset 0x5088
0096 dw offset 0x5088
0098 dw offset 0x5088
009a dw offset 0x5088
009c dw offset 0x51b4
009e dw offset 0x5088
00a0 dw offset 0x5088
00a2 dw offset 0x5088
00a4 dw offset 0x5088
00a6 dw offset 0x5088
00a8 dw offset 0x5088
00aa dw offset 0x5088
00ac dw offset 0x5088
00ae dw offset 0x5088
00b0 dw offset 0x5088
00b2 dw offset 0x5088
00b4 dw offset 0x5088
00b6 dw offset 0x5088
00b8 dw offset 0x5088
00ba dw offset 0x524a
00bc dw offset 0x5088
00be dw offset 0x539c
00c0 dw offset 0x53a0
00c2 dw offset 0x53a6
00c4 dw offset 0x53ac
00c6 cmp word ptr [bp - 2], 0x31
00ca jge 0x5091
00cc jmp 0x5451
00cf cmp word ptr [bp - 2], 0x36
00d3 jle 0x509a
00d5 jmp 0x5451
00d8 jmp 0x51b9
00db nop 
00dc nop 
00dd push cs
00de call 0xcf3a ; _AboutDialog
00e1 jmp 0x5451
00e4 push 0x7e
00e6 push 0x2711
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
00ee add sp, 4
00f1 push 0
00f3 nop 
00f4 push cs
00f5 call 0xd6dc ; _NewGame
00f8 add sp, 2
00fb jmp 0x5451
00fe mov ax, word ptr [bp - 2]
0101 mov es, word ptr [0xbed8]
0105 mov word ptr es:[0x38], ax
0109 jmp 0x5451
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 271, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _OpenEditWindow
0111 jmp 0x5451
0114 nop 
0115 push cs
0116 call 0x9b2a ; _OpenMapYard
0119 jmp 0x5451
011c nop 
011d push cs
011e call 0xbc7a ; _OpenModeWindow
0121 jmp 0x5451
0124 nop 
0125 push cs
0126 call 0xbbec ; _OpenCasteWindow
0129 jmp 0x5451
012c nop 
012d push cs
012e call 0x8a6a ; _OpenHistoryWindow
0131 jmp 0x5451
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _OpenInfoWindow
0139 jmp 0x5451
013c nop 
013d push cs
013e call 0x5caa ; _ScoreDialog
0141 jmp 0x5451
0144 push word ptr [0xcd78] ; _rootWnd
0148 push <resolved loader operand; see bindings> ; [{'operand_offset': 329, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
014b push 0x76ac
014e push 3
0150 push 0
0152 push 0
0154 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 171}}]
0159 jmp 0x5451
015c mov cx, word ptr [bp - 2]
015f sub cx, 0x21
0162 cmp cx, word ptr [0xce82] ; _YardMode
0166 je 0x5133
0168 push cx
0169 nop 
016a push cs
016b call 0x9f94 ; _SetYardMode
016e add sp, 2
0171 cmp word ptr [0xcc76], 0 ; _MapPlane
0176 je 0x5144
0178 push 0
017a nop 
017b push cs
017c call 0xa5ca ; _SetMapPlane
017f add sp, 2
0182 push 0x1900
0185 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 392, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
018a add sp, 2
018d or ax, ax
018f jne 0x5158
0191 nop 
0192 push cs
0193 call 0x9918 ; _MapToYard
0196 push 0x2200
0199 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 412, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
019e add sp, 2
01a1 or ax, ax
01a3 je 0x518d
01a5 push 0x2300
01a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 427, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_IsWinOpen
01ad add sp, 2
01b0 or ax, ax
01b2 jne 0x518d
01b4 push 0x2300
01b7 push 0x2200
01ba lcall <resolved loader operand; see bindings> ; [{'operand_offset': 445, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Swap
01bf add sp, 4
01c2 push word ptr [0xbcec]
01c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 455, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
01cb push word ptr [0xbcd8]
01cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 464, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
01d4 jmp 0x5451
01d7 nop 
01d8 push 1
01da nop 
01db push cs
01dc call 0xa5ca ; _SetMapPlane
01df add sp, 2
01e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 485, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _MakeEditOpen
01e7 jmp 0x5451
01ea push 2
01ec jmp 0x519c
01ee push 3
01f0 jmp 0x519c
01f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 501, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _StopSong
01f7 mov es, word ptr [0xbece]
01fb mov bx, word ptr [bp - 2]
01fe shl bx, 1
0200 cmp word ptr es:[bx - 0x7a70], 1
0206 sbb ax, ax
0208 neg ax
020a mov word ptr es:[bx - 0x7a70], ax
020f mov si, 0x43
0212 mov ax, si
0214 mov es, word ptr [0xbeca]
0218 sub ax, word ptr es:[0x8614]
021d cmp ax, 0x43
0220 jne 0x51ea
0222 mov ax, 0x10
0225 jmp 0x51ed
0227 nop 
0228 mov ax, 0x20
022b push ax
022c push si
022d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 560, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
0232 add sp, 4
0235 inc si
0236 cmp si, 0x46
0239 jle 0x51d4
023b mov es, word ptr [0xbecc]
023f cmp word ptr es:[0x9c28], 0
0245 je 0x520e
0247 mov ax, 0x900
024a jmp 0x5211
024c mov ax, 0x911
024f push ds
0250 push ax
0251 push 0x41
0253 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 598, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuOptionText
0258 add sp, 6
025b mov di, 0x31
025e mov si, 0x85f2
0261 mov es, word ptr [0xbece]
0265 cmp word ptr es:[si], 1
0269 sbb ax, ax
026b and ax, 0x10
026e add ax, 0x10
0271 push ax
0272 push di
0273 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 630, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
0278 add sp, 4
027b add si, 2
027e inc di
027f cmp di, 0x36
0282 jle 0x5223
0284 jmp 0x542c
0287 nop 
0288 mov es, word ptr [0xbecc]
028c xor byte ptr es:[0x9c28], 1
0292 mov di, word ptr es:[0x9c28]
0297 or di, di
0299 jne 0x527d
029b mov es, word ptr [0xbed4]
029f cmp word ptr es:[0x7c22], 0xa
02a5 jne 0x5270
02a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 682, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndLifeTransferMode
02ac jmp 0x527d
02ae cmp word ptr es:[0x7c22], 0xb
02b4 jne 0x527d
02b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 697, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndTargetMode
02bb mov es, word ptr [0xbecc]
02bf mov word ptr es:[0x9c28], di
02c4 or di, di
02c6 je 0x52f8
02c8 mov es, word ptr [0xbed4]
02cc cmp word ptr es:[0x7c22], -1
02d2 jne 0x52b0
02d4 push 1
02d6 push -1
02d8 push -2
02da mov es, word ptr [0xbed6]
02de les bx, ptr es:[0x737a]
02e3 push word ptr es:[bx + 0xa]
02e7 push word ptr es:[bx + 8]
02eb jmp 0x5302
02ed nop 
02ee mov <resolved loader operand; see bindings> ; [{'operand_offset': 751, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
02f1 mov es, ax
02f3 cmp word ptr es:[0x7c22], 0xa
02f9 jne 0x52d6
02fb push 1
02fd push -1
02ff push -2
0301 mov es, word ptr [0xbed6]
0305 les bx, ptr es:[0x737a]
030a push word ptr es:[bx + 0xe]
030e push word ptr es:[bx + 0xc]
0312 jmp 0x5302
0314 cmp word ptr es:[0x7c22], 0xb
031a jne 0x530a
031c push 1
031e push -1
0320 push -2
0322 mov es, word ptr [0xbed6]
0326 les bx, ptr es:[0x737a]
032b push word ptr es:[bx + 0x46]
032f push word ptr es:[bx + 0x44]
0333 jmp 0x5302
0335 nop 
0336 push 1
0338 push -1
033a push -2
033c push 0
033e push 0
0340 nop 
0341 push cs
0342 call 0x92c0 ; _EditMessage
0345 add sp, 0xa
0348 push 0
034a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 845, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_SetWin
034f add sp, 2
0352 push di
0353 push 0xf
0355 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 856, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
035a add sp, 4
035d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 864, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
0362 mov si, 0x43
0365 mov ax, si
0367 mov es, word ptr [0xbeca]
036b sub ax, word ptr es:[0x8614]
0370 cmp ax, 0x43
0373 jne 0x533c
0375 mov ax, 0x10
0378 jmp 0x533f
037a mov ax, 0x20
037d push ax
037e push si
037f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 898, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
0384 add sp, 4
0387 inc si
0388 cmp si, 0x46
038b jle 0x5327
038d mov es, word ptr [0xbecc]
0391 cmp word ptr es:[0x9c28], 0
0397 je 0x5360
0399 mov ax, 0x900
039c jmp 0x5363
039e mov ax, 0x911
03a1 push ds
03a2 push ax
03a3 push 0x41
03a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 936, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuOptionText
03aa add sp, 6
03ad mov di, 0x31
03b0 mov si, 0x85f2
03b3 mov es, word ptr [0xbece]
03b7 cmp word ptr es:[si], 1
03bb sbb ax, ax
03bd and ax, 0x10
03c0 add ax, 0x10
03c3 push ax
03c4 push di
03c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 968, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
03ca add sp, 4
03cd add si, 2
03d0 inc di
03d1 cmp di, 0x36
03d4 jle 0x5375
03d6 jmp 0x542c
03d9 nop 
03da xor bx, bx
03dc jmp 0x53af
03de mov bx, 1
03e1 jmp 0x53af
03e3 nop 
03e4 mov bx, 2
03e7 jmp 0x53af
03e9 nop 
03ea mov bx, 3
03ed mov es, word ptr [0xbeca]
03f1 mov word ptr es:[0x8614], bx
03f6 mov si, 0x43
03f9 mov ax, si
03fb mov es, word ptr [0xbeca]
03ff sub ax, word ptr es:[0x8614]
0404 cmp ax, 0x43
0407 jne 0x53d0
0409 mov ax, 0x10
040c jmp 0x53d3
040e mov ax, 0x20
0411 push ax
0412 push si
0413 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1046, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
0418 add sp, 4
041b inc si
041c cmp si, 0x46
041f jle 0x53bb
0421 mov es, word ptr [0xbecc]
0425 cmp word ptr es:[0x9c28], 0
042b je 0x53f4
042d mov ax, 0x900
0430 jmp 0x53f7
0432 mov ax, 0x911
0435 push ds
0436 push ax
0437 push 0x41
0439 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1084, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuOptionText
043e add sp, 6
0441 mov di, 0x31
0444 mov si, 0x85f2
0447 mov es, word ptr [0xbece]
044b cmp word ptr es:[si], 1
044f sbb ax, ax
0451 and ax, 0x10
0454 add ax, 0x10
0457 push ax
0458 push di
0459 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
045e add sp, 4
0461 add si, 2
0464 inc di
0465 cmp di, 0x36
0468 jle 0x5409
046a nop 
046b push cs
046c call 0x23a ; _UpdateUserButtons
046f mov es, word ptr [0xbece]
0473 mov ax, word ptr es:[0x85f4]
0477 mov es, word ptr [0xbed0]
047b mov word ptr es:[0xaf6], ax
047f mov es, word ptr [0xbece]
0483 mov ax, word ptr es:[0x85f6]
0487 mov es, word ptr [0xbed2]
048b mov word ptr es:[0xaf8], ax
048f push word ptr [bp - 2]
0492 push ds
0493 push 0x934
0496 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
049b add sp, 6
049e pop si
049f pop di
04a0 leave 
04a1 retf 
```

## Known declaration examples

- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c
- `extern void far EditMessage(long position, int a, int b, int mode);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far EditMessage(int first,int second,int width,int fourth,int fifth);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far EndTargetMode(void);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near MapPlane;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern void far MapToYard(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far OpenCasteWindow(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far OpenEditWindow(void);` — src/recovered/DoTab.c
- `extern void far OpenEditWindow(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far OpenMapYard(void);` — src/recovered/DoTab.c
- `extern void far OpenModeWindow(void);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern void far SetMapPlane(int plane);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far SetMenuItemState(int item, int state);` — src/recovered/wf_SetMenuEntries-c937b84870.c
- `extern void far SetMenuOptionText(int item, char far *text);` — src/recovered/wf_SetMenuEntries-c937b84870.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far SetYardMode(int mode);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far UpdateUserButtons(void);` — src/recovered/wf_SetMenuEntries-c937b84870.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_YardToMap-2e5b0deea5.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern void far clip_Off(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern void clip_SetWin(int window);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far clip_SetWin(int window);` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_ClearMapScentButtons-11d8f7b573.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_DrawAnimYardMessage-cbcb9b80e9.c
- `extern int far win_IsWinOpen(int window);` — src/recovered/wf_MagnifyMenu-51f69a1a04.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_UpdateUserButtons-609b2b7960.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_Swap(int first, int second);` — src/recovered/wf_YardToMap-2e5b0deea5.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_UpdateUserButtons'], 'segment': 1, 'target_offset': 570, 'caller_offsets': [1132]}
- {'callee_names': ['_ScoreDialog'], 'segment': 1, 'target_offset': 23722, 'caller_offsets': [318]}
- {'callee_names': ['_OpenHistoryWindow'], 'segment': 1, 'target_offset': 35434, 'caller_offsets': [302]}
- {'callee_names': ['_EditMessage'], 'segment': 1, 'target_offset': 37568, 'caller_offsets': [834]}
- {'callee_names': ['_MapToYard'], 'segment': 1, 'target_offset': 39192, 'caller_offsets': [403]}
- {'callee_names': ['_OpenMapYard'], 'segment': 1, 'target_offset': 39722, 'caller_offsets': [278]}
- {'callee_names': ['_SetYardMode'], 'segment': 1, 'target_offset': 40852, 'caller_offsets': [363]}
- {'callee_names': ['_SetMapPlane'], 'segment': 1, 'target_offset': 42442, 'caller_offsets': [380, 476]}
- {'callee_names': ['_OpenCasteWindow'], 'segment': 1, 'target_offset': 48108, 'caller_offsets': [294]}
- {'callee_names': ['_OpenModeWindow'], 'segment': 1, 'target_offset': 48250, 'caller_offsets': [286]}
- {'callee_names': ['_AboutDialog'], 'segment': 1, 'target_offset': 53050, 'caller_offsets': [222]}
- {'callee_names': ['_NewGame'], 'segment': 1, 'target_offset': 55004, 'caller_offsets': [245]}

## Neighbors

- {'symbol': '_SetPause', 'offset': 20020, 'source': None, 'size': 369}
- {'symbol': '_ProcMenuHelp', 'offset': 20390, 'source': 'src/recovered/ProcMenuHelp.c', 'size': 27}
- {'symbol': '_InitApplicationWindows', 'offset': 21604, 'source': 'src/recovered/wf_InitApplicationWindows-84f4e064cb.c', 'size': 197}
- {'symbol': '_InitApplicationStuff', 'offset': 21802, 'source': 'src/initapp.c', 'size': 6}
