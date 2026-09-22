# Recovery task _DoMouse

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 1077 bytes.

```asm
0000 enter 0x34, 0
0004 push di
0005 push si
0006 mov ax, word ptr [0xcd78] ; _rootWnd
0009 cmp word ptr [bp + 6], ax
000c jne 0x1407
000e jmp 0x1827
0011 push ax
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MyGetTopWindow
0017 add sp, 2
001a cmp ax, word ptr [bp + 6]
001d je 0x1420
001f mov ax, word ptr [0xcd76] ; _ribbonBarWnd
0022 cmp word ptr [bp + 6], ax
0025 je 0x1420
0027 jmp 0x1827
002a push word ptr [bp + 6]
002d push ds
002e push 0x240
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 25}}]
0036 mov word ptr [bp - 2], ax
0039 inc ax
003a jne 0x1435
003c jmp 0x1827
003f push word ptr [bp - 2]
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_WinAddr
0047 add sp, 2
004a mov si, ax
004c mov word ptr [bp - 4], dx
004f cmp word ptr [bp + 8], 0x201
0054 jne 0x1464
0056 mov es, dx
0058 test byte ptr es:[si + 0x1c], 1
005d je 0x1464
005f push word ptr [bp - 2]
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Close
0067 add sp, 2
006a pop si
006b pop di
006c leave 
006d retf 
006e mov ax, word ptr [bp + 0xc]
0071 mov word ptr [bp - 0xa], ax
0074 mov ax, word ptr [bp + 0xe]
0077 mov word ptr [bp - 8], ax
007a lea ax, [bp - 0xa]
007d push ss
007e push ax
007f push word ptr [bp - 2]
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FindObject
0087 add sp, 6
008a mov di, ax
008c test di, 0xff
0090 jne 0x1492
0092 cmp word ptr [0x10], 0 ; _bHelp
0097 jne 0x1492
0099 jmp 0x1827
009c push di
009d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_ObjAddr
00a2 add sp, 2
00a5 mov si, ax
00a7 mov word ptr [bp - 4], dx
00aa push 0x2d
00ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00b1 and ax, 1
00b4 cmp ax, 1
00b7 cmc 
00b8 sbb ax, ax
00ba and ax, 0x80
00bd push 0x14
00bf mov word ptr [bp - 0x1c], ax
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 195, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00c7 push 0x91
00ca mov word ptr [bp - 0x1e], ax
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00d2 push 0x90
00d5 mov word ptr [bp - 0x20], ax
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00dd push 0x10
00df mov word ptr [bp - 0x22], ax
00e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 227, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00e7 push 0x11
00e9 mov word ptr [bp - 0x24], ax
00ec lcall <resolved loader operand; see bindings> ; [{'operand_offset': 237, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00f1 and ax, 0x8000
00f4 cmp ax, 1
00f7 cmc 
00f8 sbb ax, ax
00fa and ax, 4
00fd mov cl, byte ptr [bp - 0x1e]
0100 and cx, 1
0103 cmp cx, 1
0106 cmc 
0107 sbb cx, cx
0109 and cx, 0x40
010c or cx, word ptr [bp - 0x1c]
010f mov dl, byte ptr [bp - 0x20]
0112 and dx, 1
0115 cmp dx, 1
0118 cmc 
0119 sbb dx, dx
011b and dx, 0x10
011e or cx, dx
0120 mov dl, byte ptr [bp - 0x22]
0123 and dx, 1
0126 cmp dx, 1
0129 cmc 
012a sbb dx, dx
012c and dx, 0x20
012f or cx, dx
0131 mov dh, byte ptr [bp - 0x23]
0134 and dx, 0x8000
0138 cmp dx, 1
013b cmc 
013c sbb dx, dx
013e and dx, 3
0141 or cx, dx
0143 or cx, ax
0145 mov word ptr [bp - 0x18], cx
0148 cmp word ptr [0x10], 0 ; _bHelp
014d je 0x1548
014f jmp 0x1641
0152 cmp word ptr [bp + 8], 0x201
0157 je 0x1552
0159 jmp 0x1641
015c push 0x11
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 351, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0163 test ah, 0x80
0166 je 0x1561
0168 jmp 0x1641
016b mov es, word ptr [bp - 4]
016e test byte ptr es:[si + 0x24], 2
0173 jne 0x156e
0175 jmp 0x1641
0178 test byte ptr es:[si + 0x24], 8
017d je 0x15ac
017f test byte ptr es:[si + 0x24], 0x20
0184 je 0x1590
0186 push di
0187 mov al, byte ptr es:[si + 0x20]
018b sub ah, ah
018d push ax
018e push word ptr [bp - 2]
0191 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 404, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetGroupSelectedObj
0196 jmp 0x163e
0199 nop 
019a mov al, byte ptr es:[si + 0x24]
019e and ax, 4
01a1 cmp ax, 1
01a4 sbb ax, ax
01a6 neg ax
01a8 push ax
01a9 push di
01aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 429, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
01af add sp, 4
01b2 jmp 0x1641
01b5 nop 
01b6 test byte ptr es:[si + 0x25], 8
01bb jne 0x15b6
01bd jmp 0x1641
01c0 mov al, byte ptr es:[si + 0x24]
01c4 and ax, 4
01c7 shr al, 2
01ca push ax
01cb push ds
01cc push 0x246
01cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 466, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
01d4 add sp, 6
01d7 mov es, word ptr [bp - 4]
01da mov al, byte ptr es:[si + 0x24]
01de and ax, 4
01e1 cmp ax, 1
01e4 sbb ax, ax
01e6 neg ax
01e8 push ax
01e9 push di
01ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 493, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
01ef add sp, 4
01f2 push 5
01f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 503, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitHundredths
01f9 add sp, 2
01fc mov es, word ptr [bp - 4]
01ff mov al, byte ptr es:[si + 0x24]
0203 and ax, 4
0206 shr al, 2
0209 push ax
020a push ds
020b push 0x261
020e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 529, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0213 add sp, 6
0216 mov es, word ptr [bp - 4]
0219 mov al, byte ptr es:[si + 0x24]
021d and ax, 4
0220 cmp ax, 1
0223 sbb ax, ax
0225 neg ax
0227 push ax
0228 push di
0229 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 556, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
022e add sp, 4
0231 mov es, word ptr [bp - 4]
0234 mov al, byte ptr es:[si + 0x24]
0238 and ax, 4
023b shr al, 2
023e push ax
023f push ds
0240 push 0x282
0243 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 582, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0248 add sp, 6
024b mov es, word ptr [bp - 4]
024e test byte ptr es:[si + 0x24], 0x10
0253 je 0x166c
0255 mov es, word ptr [0xbe88]
0259 mov ax, word ptr es:[0xbe10]
025d xor ax, di
025f mov word ptr [bp - 0x26], ax
0262 test ah, 0xff
0265 jne 0x166c
0267 test byte ptr [bp - 0x26], 0xff
026b je 0x166c
026d push di
026e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 625, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; __win_SetProxItem
0273 add sp, 2
0276 mov word ptr [bp - 0xe], di
0279 mov ax, word ptr [bp - 0xa]
027c mov word ptr [bp - 0x12], ax
027f mov ax, word ptr [bp - 8]
0282 mov word ptr [bp - 0x10], ax
0285 mov ax, word ptr [bp + 8]
0288 sub ax, 0x201
028b cmp ax, 5
028e jbe 0x1689
0290 jmp 0x1827
0293 shl ax, 1
0295 xchg bx, ax
0296 jmp word ptr cs:[bx + 0x1692]
029b nop 
029c dw offset 0x169e
029e dw offset 0x1712
02a0 dw offset 0x1786
02a2 dw offset 0x169e
02a4 dw offset 0x1712
02a6 dw offset 0x1786
02a8 push 1
02aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 683, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
02af push 0x20
02b1 mov word ptr [bp - 0x28], ax
02b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 693, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
02b9 push 0x2d
02bb mov si, ax
02bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 702, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
02c2 mov cx, si
02c4 mov dh, byte ptr [bp - 0x27]
02c7 or dh, ch
02c9 or dh, ah
02cb and dx, 0x8000
02cf cmp dx, 1
02d2 sbb ax, ax
02d4 inc ax
02d5 push 2
02d7 mov si, ax
02d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 730, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
02de push 0x2e
02e0 mov di, ax
02e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 739, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
02e7 mov cx, di
02e9 or ch, ah
02eb and cx, 0x8000
02ef cmp cx, 1
02f2 cmc 
02f3 sbb ax, ax
02f5 and ax, 2
02f8 or si, ax
02fa mov word ptr [bp - 0x2a], si
02fd cmp word ptr [bp + 8], 0x201
0302 jne 0x1700
0304 mov ax, 0x200
0307 jmp 0x1703
0309 nop 
030a mov ax, 0x800
030d or ax, si
030f mov word ptr [bp - 0x14], ax
0312 mov al, byte ptr [bp - 0x14]
0315 mov byte ptr [0xcc70], al ; _mouse_state
0318 jmp 0x1810
031b nop 
031c push 1
031e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 799, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0323 push 0x20
0325 mov word ptr [bp - 0x2c], ax
0328 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 809, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
032d push 0x2d
032f mov si, ax
0331 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 818, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0336 mov cx, si
0338 mov dh, byte ptr [bp - 0x2b]
033b or dh, ch
033d or dh, ah
033f and dx, 0x8000
0343 cmp dx, 1
0346 sbb ax, ax
0348 inc ax
0349 push 2
034b mov si, ax
034d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 846, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0352 push 0x2e
0354 mov di, ax
0356 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 855, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
035b mov cx, di
035d or ch, ah
035f and cx, 0x8000
0363 cmp cx, 1
0366 cmc 
0367 sbb ax, ax
0369 and ax, 2
036c or si, ax
036e mov word ptr [bp - 0x2e], si
0371 cmp word ptr [bp + 8], 0x202
0376 jne 0x1774
0378 mov ax, 0x400
037b jmp 0x1777
037d nop 
037e mov ax, 0x1000
0381 or ax, si
0383 mov word ptr [bp - 0x14], ax
0386 mov al, byte ptr [bp - 0x14]
0389 mov byte ptr [0xcc70], al ; _mouse_state
038c pop si
038d pop di
038e leave 
038f retf 
0390 push 1
0392 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 915, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0397 push 0x20
0399 mov word ptr [bp - 0x30], ax
039c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 925, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
03a1 push 0x2d
03a3 mov di, ax
03a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 934, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
03aa mov cx, di
03ac mov dh, byte ptr [bp - 0x2f]
03af or dh, ch
03b1 or dh, ah
03b3 and dx, 0x8000
03b7 cmp dx, 1
03ba sbb ax, ax
03bc inc ax
03bd push 2
03bf mov di, ax
03c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 962, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
03c6 push 0x2e
03c8 mov word ptr [bp - 0x32], ax
03cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 972, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
03d0 mov ch, byte ptr [bp - 0x31]
03d3 or ch, ah
03d5 and cx, 0x8000
03d9 cmp cx, 1
03dc cmc 
03dd sbb ax, ax
03df and ax, 2
03e2 or di, ax
03e4 mov word ptr [bp - 0x34], di
03e7 cmp word ptr [bp + 8], 0x203
03ec jne 0x17ea
03ee mov ax, 0x2000
03f1 jmp 0x17ed
03f3 nop 
03f4 mov ax, 0x4000
03f7 or ax, di
03f9 mov word ptr [bp - 0x14], ax
03fc mov al, byte ptr [bp - 0x14]
03ff mov byte ptr [0xcc70], al ; _mouse_state
0402 mov es, word ptr [bp - 4]
0405 cmp byte ptr es:[si + 0x21], 5
040a je 0x1827
040c cmp byte ptr es:[si + 0x21], 0x11
0411 je 0x1827
0413 cmp byte ptr es:[si + 0x21], 0xd
0418 je 0x1827
041a sub sp, 0x10
041d lea si, [bp - 0x1a]
0420 mov di, sp
0422 push ss
0423 pop es
0424 mov cx, 8
0427 rep movsw word ptr es:[di], word ptr [si]
0429 nop 
042a push cs
042b call 0xbc2 ; _DoEvent
042e add sp, 0x10
0431 pop si
0432 pop di
0433 leave 
0434 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern int near bHelp;` — src/recovered/wf_HelpKeyDown-18eb3b2e99.c
- `extern int near ribbonBarWnd;` — src/recovered/wf_RedrawWindows-14f4bb1c45.c
- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern struct WinBitmapObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far * far win_ObjAddr(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_ClearBookmarks-ffba50efd3.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_DoUserButtonUpdate-cf874c4e35.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_HelpKeyDown', 'offset': 3558, 'source': 'src/recovered/wf_HelpKeyDown-18eb3b2e99.c', 'size': 166}
- {'symbol': '_DoKeyDown', 'offset': 3724, 'source': None, 'size': 1385}
- {'symbol': '_DoNextWindow', 'offset': 6188, 'source': 'src/recovered/wf_DoNextWindow-2eb2851645.c', 'size': 74}
- {'symbol': '_DoMenuEntry', 'offset': 6262, 'source': None, 'size': 503}
