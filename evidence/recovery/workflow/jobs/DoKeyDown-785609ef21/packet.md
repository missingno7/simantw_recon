# Recovery task _DoKeyDown

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 1385 bytes.

```asm
0000 enter 0x40, 0
0004 push di
0005 push si
0006 push word ptr [0xcd78] ; _rootWnd
000a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MyGetTopWindow
000f add sp, 2
0012 or ax, ax
0014 jne 0xea5
0016 jmp 0x1224
0019 test word ptr [bp + 0xc], 0x4000
001e je 0xeaf
0020 jmp 0x1224
0023 cmp word ptr [bp + 8], 0x2d
0027 je 0xebe
0029 cmp word ptr [bp + 8], 0x20
002d je 0xebe
002f jmp 0x1224
0032 push word ptr [0xcd78] ; _rootWnd
0036 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _MyGetTopWindow
003b add sp, 2
003e mov si, ax
0040 push si
0041 push ds
0042 push 0x1de
0045 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 70, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 25}}]
004a mov word ptr [bp - 2], ax
004d inc ax
004e jne 0xedf
0050 jmp 0x13f1
0053 lea ax, [bp - 0xa]
0056 push ss
0057 push ax
0058 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 17}}]
005d push si
005e lea ax, [bp - 0xa]
0061 push ss
0062 push ax
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 29}}]
0068 mov ax, word ptr [bp - 0xa]
006b mov word ptr [bp - 0x12], ax
006e mov ax, word ptr [bp - 8]
0071 mov word ptr [bp - 0x10], ax
0074 lea ax, [bp - 0xa]
0077 push ss
0078 push ax
0079 push word ptr [bp - 2]
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_FindObject
0081 add sp, 6
0084 mov word ptr [bp - 0xe], ax
0087 test byte ptr [bp - 0xe], 0xff
008b jne 0xf23
008d cmp word ptr [0x10], 0 ; _bHelp
0092 jne 0xf23
0094 jmp 0x13f1
0097 push 0x2d
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
009e and ax, 1
00a1 cmp ax, 1
00a4 cmc 
00a5 sbb ax, ax
00a7 and ax, 0x80
00aa push 0x14
00ac mov si, ax
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00b3 and ax, 1
00b6 cmp ax, 1
00b9 cmc 
00ba sbb ax, ax
00bc and ax, 0x40
00bf or si, ax
00c1 push 0x91
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00c9 and ax, 1
00cc cmp ax, 1
00cf cmc 
00d0 sbb ax, ax
00d2 and ax, 0x10
00d5 or si, ax
00d7 push 0x90
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 219, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00df and ax, 1
00e2 cmp ax, 1
00e5 cmc 
00e6 sbb ax, ax
00e8 and ax, 0x20
00eb or si, ax
00ed push 0x10
00ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 240, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
00f4 and ax, 0x8000
00f7 cmp ax, 1
00fa cmc 
00fb sbb ax, ax
00fd and ax, 3
0100 or si, ax
0102 push 0x11
0104 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0109 and ax, 0x8000
010c cmp ax, 1
010f cmc 
0110 sbb ax, ax
0112 and ax, 4
0115 or si, ax
0117 mov word ptr [bp - 0x18], si
011a cmp word ptr [bp + 8], 0x2d
011e je 0xfb5
0120 cmp word ptr [bp + 8], 0x20
0124 je 0xfb5
0126 jmp 0x10bf
0129 test byte ptr [bp - 0xe], 0xff
012d jne 0xfbe
012f jmp 0x10bf
0132 cmp word ptr [0x10], 0 ; _bHelp
0137 je 0xfc8
0139 jmp 0x10bf
013c push word ptr [bp - 0xe]
013f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 322, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_ObjAddr
0144 add sp, 2
0147 mov es, dx
0149 mov bx, ax
014b mov si, bx
014d mov word ptr [bp - 4], es
0150 test byte ptr es:[bx + 0x24], 2
0155 jne 0xfe6
0157 jmp 0x10bf
015a test byte ptr es:[si + 0x24], 8
015f je 0x1028
0161 test byte ptr es:[si + 0x24], 0x20
0166 je 0x100a
0168 push word ptr [bp - 0xe]
016b mov al, byte ptr es:[si + 0x20]
016f sub ah, ah
0171 push ax
0172 push word ptr [bp - 2]
0175 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 376, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetGroupSelectedObj
017a jmp 0x10bc
017d nop 
017e mov al, byte ptr es:[si + 0x24]
0182 and ax, 4
0185 cmp ax, 1
0188 sbb ax, ax
018a neg ax
018c push ax
018d push word ptr [bp - 0xe]
0190 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0195 add sp, 4
0198 jmp 0x10bf
019b nop 
019c test byte ptr es:[si + 0x25], 8
01a1 jne 0x1032
01a3 jmp 0x10bf
01a6 mov al, byte ptr es:[si + 0x24]
01aa and ax, 4
01ad shr al, 2
01b0 push ax
01b1 push ds
01b2 push 0x1e4
01b5 mov di, es
01b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 442, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
01bc add sp, 6
01bf mov es, di
01c1 mov al, byte ptr es:[si + 0x24]
01c5 and ax, 4
01c8 cmp ax, 1
01cb sbb ax, ax
01cd neg ax
01cf push ax
01d0 push word ptr [bp - 0xe]
01d3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 470, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
01d8 add sp, 4
01db push 5
01dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 480, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitHundredths
01e2 add sp, 2
01e5 mov es, di
01e7 mov al, byte ptr es:[si + 0x24]
01eb and ax, 4
01ee shr al, 2
01f1 push ax
01f2 push ds
01f3 push 0x201
01f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 505, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
01fb add sp, 6
01fe mov es, di
0200 mov al, byte ptr es:[si + 0x24]
0204 and ax, 4
0207 cmp ax, 1
020a sbb ax, ax
020c neg ax
020e push ax
020f push word ptr [bp - 0xe]
0212 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 533, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0217 add sp, 4
021a mov es, di
021c mov al, byte ptr es:[si + 0x24]
0220 and ax, 4
0223 shr al, 2
0226 push ax
0227 push ds
0228 push 0x224
022b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 558, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
0230 add sp, 6
0233 lea ax, [bp - 0x2c]
0236 push ss
0237 push ax
0238 push 0
023a push 0x100
023d push 0x100
0240 push 1
0242 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 579, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0247 or ax, ax
0249 jne 0x10da
024b jmp 0x11aa
024e cmp word ptr [bp - 0x28], 0x2d
0252 je 0x10ef
0254 cmp word ptr [bp - 0x28], 0x20
0258 je 0x10ef
025a cmp word ptr [bp - 0x28], 0x2e
025e je 0x10ef
0260 jmp 0x11aa
0263 cmp word ptr [bp - 0x28], 0x2d
0267 je 0x1100
0269 cmp word ptr [bp - 0x28], 0x20
026d je 0x1100
026f xor si, si
0271 jmp 0x1103
0273 nop 
0274 mov si, 0x2000
0277 push 1
0279 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 634, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
027e push 0x20
0280 mov word ptr [bp - 0x2e], ax
0283 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 644, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0288 push 0x2d
028a mov di, ax
028c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 653, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0291 mov cx, di
0293 mov dh, byte ptr [bp - 0x2d]
0296 or dh, ch
0298 or dh, ah
029a and dx, 0x8000
029e cmp dx, 1
02a1 sbb ax, ax
02a3 inc ax
02a4 push 2
02a6 mov di, ax
02a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 681, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
02ad push 0x2e
02af mov word ptr [bp - 0x30], ax
02b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 691, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
02b7 mov ch, byte ptr [bp - 0x2f]
02ba or ch, ah
02bc and cx, 0x8000
02c0 cmp cx, 1
02c3 cmc 
02c4 sbb ax, ax
02c6 and ax, 2
02c9 or di, ax
02cb mov word ptr [bp - 0x32], di
02ce cmp word ptr [bp - 0x28], 0x2e
02d2 jne 0x1166
02d4 mov ax, 0x4000
02d7 jmp 0x1168
02d9 nop 
02da xor ax, ax
02dc or ax, di
02de or ax, si
02e0 mov word ptr [bp - 0x14], ax
02e3 mov al, byte ptr [bp - 0x14]
02e6 mov byte ptr [0xcc70], al ; _mouse_state
02e9 push word ptr [bp + 8]
02ec push 2
02ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 751, 'type': 3, 'target': {'kind': 'import', 'module': 'KEYBOARD', 'ordinal': 131}}]
02f3 mov byte ptr [bp - 0x1a], al
02f6 push word ptr [bp + 8]
02f9 push 0
02fb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 764, 'type': 3, 'target': {'kind': 'import', 'module': 'KEYBOARD', 'ordinal': 131}}]
0300 mov byte ptr [bp - 0x19], al
0303 sub sp, 0x10
0306 lea si, [bp - 0x1a]
0309 mov di, sp
030b push ss
030c pop es
030d mov cx, 8
0310 rep movsw word ptr es:[di], word ptr [si]
0312 nop 
0313 push cs
0314 call 0xbc2 ; _DoEvent
0317 add sp, 0x10
031a pop si
031b pop di
031c leave 
031d retf 
031e cmp word ptr [bp + 8], 0x2d
0322 je 0x11ba
0324 cmp word ptr [bp + 8], 0x20
0328 je 0x11ba
032a xor si, si
032c jmp 0x11bd
032e mov si, 0x200
0331 push 1
0333 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 820, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0338 push 0x20
033a mov word ptr [bp - 0x34], ax
033d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 830, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0342 push 0x2d
0344 mov di, ax
0346 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 839, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
034b mov cx, di
034d mov dh, byte ptr [bp - 0x33]
0350 or dh, ch
0352 or dh, ah
0354 and dx, 0x8000
0358 cmp dx, 1
035b sbb ax, ax
035d inc ax
035e push 2
0360 mov di, ax
0362 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 867, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0367 push 0x2e
0369 mov word ptr [bp - 0x36], ax
036c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 877, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 106}}]
0371 mov ch, byte ptr [bp - 0x35]
0374 or ch, ah
0376 and cx, 0x8000
037a cmp cx, 1
037d cmc 
037e sbb ax, ax
0380 and ax, 2
0383 or di, ax
0385 mov word ptr [bp - 0x38], di
0388 cmp word ptr [bp + 8], 0x2e
038c je 0x121d
038e jmp 0x1166
0391 mov ax, 0x800
0394 jmp 0x1168
0397 nop 
0398 push word ptr [bp + 0xc]
039b push word ptr [bp + 0xa]
039e push word ptr [bp + 8]
03a1 push word ptr [bp + 6]
03a4 nop 
03a5 push cs
03a6 call 0xde6 ; _HelpKeyDown
03a9 add sp, 8
03ac or ax, ax
03ae je 0x123f
03b0 jmp 0x13f1
03b3 push word ptr [bp + 8]
03b6 nop 
03b7 push cs
03b8 call 0x8562 ; _YellowCommandKey
03bb add sp, 2
03be or ax, ax
03c0 je 0x1251
03c2 jmp 0x13f1
03c5 cmp word ptr [bp + 8], 0x25
03c9 jne 0x125a
03cb jmp 0x13b2
03ce cmp word ptr [bp + 8], 0x26
03d2 jne 0x1263
03d4 jmp 0x13b2
03d7 cmp word ptr [bp + 8], 0x27
03db jne 0x126c
03dd jmp 0x13b2
03e0 cmp word ptr [bp + 8], 0x28
03e4 jne 0x1275
03e6 jmp 0x13b2
03e9 cmp word ptr [bp + 8], 0xd
03ed jne 0x1286
03ef mov word ptr [0x1da], ax
03f2 mov word ptr [0x1dc], ax
03f5 pop si
03f6 pop di
03f7 leave 
03f8 retf 
03f9 nop 
03fa mov si, word ptr [bp + 8]
03fd cmp si, 0x41
0400 jge 0x1291
0402 jmp 0x13f1
0405 cmp si, 0x5a
0408 jle 0x1299
040a jmp 0x13f1
040d push 0x10
040f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1040, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0414 test ah, 0x80
0417 jne 0x12a8
0419 jmp 0x1390
041c push si
041d push 2
041f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1056, 'type': 3, 'target': {'kind': 'import', 'module': 'KEYBOARD', 'ordinal': 131}}]
0424 mov bx, ax
0426 test byte ptr [bx - 0x52cd], 2
042b je 0x12c6
042d push si
042e push 2
0430 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1073, 'type': 3, 'target': {'kind': 'import', 'module': 'KEYBOARD', 'ordinal': 131}}]
0435 sub al, 0x20
0437 jmp 0x12ce
0439 nop 
043a push si
043b push 2
043d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1086, 'type': 3, 'target': {'kind': 'import', 'module': 'KEYBOARD', 'ordinal': 131}}]
0442 mov bx, word ptr [0x1da]
0446 mov byte ptr [bx - 0x35a0], al
044a mov di, bx
044c inc di
044d cmp di, 4
0450 jne 0x12e0
0452 xor di, di
0454 cmp word ptr [0x1dc], 4
0459 jge 0x12eb
045b inc word ptr [0x1dc]
045f mov word ptr [0x1da], di
0463 cmp word ptr [0x1dc], 4
0468 je 0x12f9
046a jmp 0x13f1
046d xor cx, cx
046f mov <resolved loader operand; see bindings> ; [{'operand_offset': 1136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0472 mov es, ax
0474 cmp byte ptr es:[0x83bc], cl
0479 je 0x1376
047b mov si, 0x83bc
047e mov bx, di
0480 and bx, 3
0483 mov al, byte ptr [bx - 0x35a0]
0487 not al
0489 mov byte ptr [bp - 0x3a], al
048c mov bx, di
048e inc bl
0490 and bx, 3
0493 mov al, byte ptr [bx - 0x35a0]
0497 not al
0499 mov byte ptr [bp - 0x3c], al
049c mov bx, di
049e sub bl, 0xfe
04a1 and bx, 3
04a4 mov al, byte ptr [bx - 0x35a0]
04a8 not al
04aa mov byte ptr [bp - 0x3e], al
04ad mov bx, di
04af dec bl
04b1 and bx, 3
04b4 mov al, byte ptr [bx - 0x35a0]
04b8 not al
04ba mov byte ptr [bp - 0x40], al
04bd mov al, byte ptr es:[si]
04c0 cmp byte ptr [bp - 0x3a], al
04c3 jne 0x136c
04c5 mov al, byte ptr es:[si + 1]
04c9 cmp byte ptr [bp - 0x3c], al
04cc jne 0x136c
04ce mov al, byte ptr es:[si + 2]
04d2 cmp byte ptr [bp - 0x3e], al
04d5 jne 0x136c
04d7 mov al, byte ptr es:[si + 3]
04db cmp byte ptr [bp - 0x40], al
04de je 0x1376
04e0 inc cx
04e1 add si, 4
04e4 cmp byte ptr es:[si], 0
04e8 jne 0x1349
04ea mov bx, cx
04ec shl bx, 2
04ef cmp byte ptr es:[bx - 0x7c44], 0
04f5 je 0x13f1
04f7 push cx
04f8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1275, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CheatKeys
04fd add sp, 2
0500 pop si
0501 pop di
0502 leave 
0503 retf 
0504 push si
0505 push 2
0507 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1288, 'type': 3, 'target': {'kind': 'import', 'module': 'KEYBOARD', 'ordinal': 131}}]
050c mov bx, ax
050e test byte ptr [bx - 0x52cd], 1
0513 jne 0x13a4
0515 jmp 0x12c6
0518 push si
0519 push 2
051b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1308, 'type': 3, 'target': {'kind': 'import', 'module': 'KEYBOARD', 'ordinal': 131}}]
0520 add al, 0x20
0522 jmp 0x12ce
0525 nop 
0526 lea ax, [bp - 4]
0529 push ss
052a push ax
052b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1324, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 17}}]
0530 mov ax, word ptr [bp + 8]
0533 sub ax, 0x25
0536 je 0x13d0
0538 dec ax
0539 je 0x13d6
053b dec ax
053c je 0x13dc
053e dec ax
053f je 0x13e2
0541 jmp 0x13e6
0543 nop 
0544 sub word ptr [bp - 4], 8
0548 jmp 0x13e6
054a sub word ptr [bp - 2], 8
054e jmp 0x13e6
0550 add word ptr [bp - 4], 8
0554 jmp 0x13e6
0556 add word ptr [bp - 2], 8
055a push word ptr [bp - 4]
055d push word ptr [bp - 2]
0560 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1377, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 70}}]
0565 pop si
0566 pop di
0567 leave 
0568 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern int far bHelp;` — src/recovered/wf_tu_antedit_A998_DrawYardCursor_3_scaffold-c71c8e4e09.c
- `extern int far bHelp;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near bHelp;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern struct WinBitmapObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far win_SetGroupSelectedObj(int group, int selected, int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far win_SetGroupSelectedObj(int group, int selected, int object);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_UpdateUserButtons-609b2b7960.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoEvent', 'offset': 3010, 'source': None, 'size': 548}
- {'symbol': '_HelpKeyDown', 'offset': 3558, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 166}
- {'symbol': '_DoMouse', 'offset': 5110, 'source': None, 'size': 1077}
- {'symbol': '_DoNextWindow', 'offset': 6188, 'source': 'src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c', 'size': 74}
