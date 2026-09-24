# Recovery task _win_Open

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 1385 bytes.

```asm
0000 enter 0x20, 0
0004 push di
0005 push si
0006 sub ax, ax
0008 mov word ptr [bp - 0x10], ax
000b mov word ptr [bp - 0x12], ax
000e xor si, si
0010 mov word ptr [bp - 0x1e], si
0013 mov word ptr [bp - 0x1c], si
0016 push word ptr [bp + 6]
0019 nop 
001a push cs
001b call 0xe3a6 ; _win_LockWinHigh
001e add sp, 2
0021 mov bx, word ptr [bp + 6]
0024 sar bx, 8
0027 shl bx, 2
002a mov ax, word ptr [bx - 0x3166]
002e mov dx, word ptr [bx - 0x3164]
0032 mov word ptr [bp - 8], ax
0035 mov word ptr [bp - 6], dx
0038 mov es, dx
003a mov bx, ax
003c mov ax, word ptr [bp + 8]
003f mov word ptr es:[bx + 0x10], ax
0043 mov ax, word ptr [bp + 0xa]
0046 mov word ptr es:[bx + 0x12], ax
004a mov ax, word ptr [bp + 0xc]
004d mov word ptr es:[bx + 0x14], ax
0051 mov ax, word ptr [bp + 0xe]
0054 mov word ptr es:[bx + 0x16], ax
0058 push word ptr [bp + 6]
005b nop 
005c push cs
005d call 0xe6e2 ; _win_Recalc
0060 add sp, 2
0063 mov bx, word ptr [bp + 6]
0066 sar bx, 8
0069 shl bx, 2
006c mov ax, word ptr [bx - 0x3166]
0070 mov dx, word ptr [bx - 0x3164]
0074 mov word ptr [bp - 8], ax
0077 mov word ptr [bp - 6], dx
007a mov es, dx
007c mov bx, ax
007e or byte ptr es:[bx + 0x1d], 2
0083 les bx, ptr es:[bx + 0x2c]
0087 cmp word ptr es:[bx + 0x18], 5
008c je 0xcac2
008e mov ax, word ptr [0xbd0a] ; _ribbonBarHeight
0091 mov word ptr [bp - 0x1c], ax
0094 les bx, ptr [bp - 8]
0097 test byte ptr es:[bx + 0x1c], 4
009c je 0xcaf2
009e mov word ptr [bp - 0x12], si
00a1 mov word ptr [bp - 0x10], 0xc8
00a6 push 4
00a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
00ad mov si, ax
00af sub si, 0x12
00b2 cmp word ptr [0xbd0a], 0 ; _ribbonBarHeight
00b7 je 0xcafe
00b9 sub si, 2
00bc mov word ptr [bp - 0x1e], 0xfffc
00c1 jmp 0xcafe
00c3 nop 
00c4 cmp word ptr [0xbd0a], si ; _ribbonBarHeight
00c8 je 0xcafe
00ca mov si, 0xfffc
00cd mov word ptr [bp - 0x1e], si
00d0 les bx, ptr [bp - 8]
00d3 test byte ptr es:[bx + 0x1c], 8
00d8 je 0xcb3a
00da or byte ptr [bp - 0x10], 0x34
00de push 0x20
00e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
00e5 shl ax, 1
00e7 push 2
00e9 mov di, ax
00eb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
00f0 add di, ax
00f2 add word ptr [bp - 0x1e], di
00f5 push 0x21
00f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 248, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
00fc shl ax, 1
00fe push 3
0100 mov di, ax
0102 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 259, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0107 add di, ax
0109 jmp 0xcb8d
010b nop 
010c test byte ptr es:[bx + 0x1c], 4
0111 je 0xcb5e
0113 or byte ptr [bp - 0x10], 0x80
0117 push 5
0119 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 282, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
011e shl ax, 1
0120 add word ptr [bp - 0x1e], ax
0123 push 6
0125 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 294, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
012a shl ax, 1
012c add si, ax
012e jmp 0xcb8f
0130 or byte ptr [bp - 0x10], 0x40
0134 push 5
0136 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
013b push 7
013d mov di, ax
013f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0144 add di, ax
0146 shl di, 1
0148 add word ptr [bp - 0x1e], di
014b push 6
014d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 334, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
0152 push 8
0154 mov di, ax
0156 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 179}}]
015b add di, ax
015d shl di, 1
015f add si, di
0161 mov word ptr [bp - 0x20], si
0164 mov bx, word ptr [bp + 6]
0167 sar bx, 8
016a shl bx, 1
016c cmp word ptr [bx - 0x435a], 0
0171 jne 0xcba4
0173 jmp 0xccf6
0176 mov bx, word ptr [bp + 6]
0179 sar bx, 8
017c shl bx, 1
017e push word ptr [bx - 0x435a]
0182 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 387, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 49}}]
0187 or ax, ax
0189 je 0xcbce
018b mov bx, word ptr [bp + 6]
018e sar bx, 8
0191 shl bx, 1
0193 push word ptr [bx - 0x435a]
0197 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 408, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
019c jmp 0xcf3d
019f nop 
01a0 mov si, word ptr [bp - 8]
01a3 mov es, word ptr [bp - 6]
01a6 les bx, ptr es:[si + 0x2c]
01aa cmp word ptr es:[bx + 0x18], 5
01af jne 0xcbe2
01b1 jmp 0xcc94
01b4 mov es, word ptr [bp - 6]
01b7 les bx, ptr es:[si + 0x2c]
01bb cmp word ptr es:[bx + 0x18], 0
01c0 je 0xcc03
01c2 mov ax, word ptr [bp + 6]
01c5 mov es, word ptr [bp - 6]
01c8 les bx, ptr es:[si + 0x2c]
01cc cmp word ptr es:[bx + 0x10], ax
01d0 je 0xcc03
01d2 jmp 0xcc94
01d5 mov es, word ptr [bp - 6]
01d8 les bx, ptr es:[si + 0x2c]
01dc cmp word ptr es:[bx + 0x1a], 0
01e1 je 0xcc21
01e3 mov ax, word ptr [bp + 6]
01e6 mov es, word ptr [bp - 6]
01e9 les bx, ptr es:[si + 0x2c]
01ed cmp word ptr es:[bx + 0x12], ax
01f1 jne 0xcc94
01f3 mov es, word ptr [bp - 6]
01f6 les bx, ptr es:[si + 0x2c]
01fa cmp word ptr es:[bx + 0x1c], 0
01ff je 0xcc3f
0201 mov ax, word ptr [bp + 6]
0204 mov es, word ptr [bp - 6]
0207 les bx, ptr es:[si + 0x2c]
020b cmp word ptr es:[bx + 0x14], ax
020f jne 0xcc94
0211 mov es, word ptr [bp - 6]
0214 les bx, ptr es:[si + 0x2c]
0218 cmp word ptr es:[bx + 0x1e], 0
021d je 0xcc5d
021f mov ax, word ptr [bp + 6]
0222 mov es, word ptr [bp - 6]
0225 les bx, ptr es:[si + 0x2c]
0229 cmp word ptr es:[bx + 0x16], ax
022d jne 0xcc94
022f mov bx, word ptr [bp + 6]
0232 sar bx, 8
0235 shl bx, 1
0237 push word ptr [bx - 0x435a]
023b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 572, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
0240 mov bx, word ptr [bp + 6]
0243 sar bx, 8
0246 shl bx, 1
0248 push word ptr [bx - 0x435a]
024c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 589, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 272}}]
0251 or ax, ax
0253 je 0xccdf
0255 mov bx, word ptr [bp + 6]
0258 sar bx, 8
025b shl bx, 1
025d push word ptr [bx - 0x435a]
0261 push 3
0263 jmp 0xcced
0265 nop 
0266 mov bx, word ptr [bp + 6]
0269 sar bx, 8
026c shl bx, 1
026e push word ptr [bx - 0x435a]
0272 push 0
0274 mov es, word ptr [bp - 6]
0277 push word ptr es:[si]
027a mov ax, word ptr es:[si + 2]
027e mov cx, ax
0280 sub ax, word ptr [bp - 0x1c]
0283 push ax
0284 mov ax, word ptr es:[si + 4]
0288 sub ax, word ptr es:[si]
028b add ax, word ptr [bp - 0x1e]
028e push ax
028f sub cx, word ptr es:[si + 6]
0293 neg cx
0295 add cx, word ptr [bp - 0x20]
0298 push cx
0299 push 0x20
029b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 668, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 232}}]
02a0 mov bx, word ptr [bp + 6]
02a3 sar bx, 8
02a6 shl bx, 1
02a8 push word ptr [bx - 0x435a]
02ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 685, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
02b1 mov bx, word ptr [bp + 6]
02b4 sar bx, 8
02b7 shl bx, 1
02b9 push word ptr [bx - 0x435a]
02bd push 1
02bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 704, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 42}}]
02c4 jmp 0xcf2c
02c7 nop 
02c8 les si, ptr [bp - 8]
02cb test byte ptr es:[si + 0x1c], 0x10
02d0 je 0xcd04
02d2 or byte ptr [bp - 0x10], 0xca
02d6 test byte ptr es:[si + 0x1c], 0x80
02db je 0xcd0f
02dd or byte ptr [bp - 0xf], 1
02e1 test byte ptr es:[si + 0x1d], 1
02e6 je 0xcd1a
02e8 or byte ptr [bp - 0x10], 0xc9
02ec or byte ptr [bp - 0xf], 0x44
02f0 xor ax, ax
02f2 cdq 
02f3 mov bx, ax
02f5 mov word ptr [bp - 0x18], dx
02f8 mov word ptr [bp - 0x16], ax
02fb xor cx, cx
02fd mov word ptr [bp - 0x14], ax
0300 cmp word ptr es:[si + 0xc], ax
0304 jle 0xcd68
0306 mov word ptr [bp - 0x1a], bx
0309 lea ax, [si + 0x2c]
030c mov word ptr [bp - 0xe], ax
030f mov word ptr [bp - 0xc], es
0312 mov word ptr [bp - 0xa], cx
0315 mov si, cx
0317 mov di, ax
0319 mov cx, word ptr [bp - 0x16]
031c mov es, word ptr [bp - 0xc]
031f les bx, ptr es:[di]
0322 mov word ptr [bp - 4], bx
0325 mov word ptr [bp - 2], es
0328 mov al, byte ptr es:[bx + 0x21]
032c cwde 
032d sub ax, 0xc
0330 je 0xcd94
0332 sub ax, 6
0335 je 0xcd9e
0337 jmp 0xcde2
0339 nop 
033a mov cx, word ptr [bp - 0x16]
033d mov ax, word ptr [bp - 0x18]
0340 or ax, bx
0342 je 0xcd81
0344 mov es, word ptr [bp - 0x18]
0347 mov ax, word ptr es:[bx]
034a mov dx, word ptr es:[bx + 2]
034e mov cx, ax
0350 mov word ptr [bp - 0x14], dx
0353 mov ax, word ptr [bp - 0x14]
0356 or ax, cx
0358 je 0xcdfa
035a mov ax, word ptr [bp - 0x14]
035d mov word ptr [bp - 4], cx
0360 mov word ptr [bp - 2], ax
0363 jmp 0xce02
0365 nop 
0366 mov ax, bx
0368 mov dx, word ptr [bp - 2]
036b add ax, 0x2a
036e jmp 0xcdd9
0370 mov es, word ptr [bp - 2]
0373 mov ax, word ptr es:[bx + 0x2a]
0377 mov dx, word ptr es:[bx + 0x2c]
037b mov word ptr [bp - 0x1a], ax
037e mov word ptr [bp - 0x18], dx
0381 or dx, ax
0383 jne 0xcdde
0385 push 0x25
0387 mov ax, bx
0389 mov dx, es
038b add ax, 0x2e
038e mov word ptr [bp - 0x16], ax
0391 mov word ptr [bp - 0x14], dx
0394 push dx
0395 push ax
0396 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 921, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strchr
039b add sp, 6
039e or dx, ax
03a0 jne 0xcdd6
03a2 mov cx, word ptr [bp - 0x16]
03a5 jmp 0xcdde
03a7 nop 
03a8 xor ax, ax
03aa cdq 
03ab mov cx, ax
03ad mov word ptr [bp - 0x14], dx
03b0 or byte ptr [bp - 0x10], 0xc0
03b4 add di, 4
03b7 inc si
03b8 les bx, ptr [bp - 8]
03bb cmp word ptr es:[bx + 0xc], si
03bf jle 0xcdf2
03c1 jmp 0xcd4a
03c4 mov si, bx
03c6 mov bx, word ptr [bp - 0x1a]
03c9 jmp 0xcd6b
03cc mov word ptr [bp - 4], 0xbd84
03d1 mov word ptr [bp - 2], ds
03d4 push ds
03d5 push 0xbd93
03d8 push word ptr [bp - 2]
03db push word ptr [bp - 4]
03de push word ptr [bp - 0x10]
03e1 push word ptr [bp - 0x12]
03e4 mov es, word ptr [bp - 6]
03e7 push word ptr es:[si]
03ea mov ax, word ptr es:[si + 2]
03ee mov cx, ax
03f0 sub ax, word ptr [bp - 0x1c]
03f3 push ax
03f4 mov ax, word ptr es:[si + 4]
03f8 sub ax, word ptr es:[si]
03fb add ax, word ptr [bp - 0x1e]
03fe push ax
03ff sub cx, word ptr es:[si + 6]
0403 neg cx
0405 add cx, word ptr [bp - 0x20]
0408 push cx
0409 push word ptr [0xcd78] ; _rootWnd
040d push 0
040f push word ptr [0xcc7c] ; _hInst
0413 push 0
0415 push 0
0417 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1048, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 41}}]
041c mov bx, word ptr [bp + 6]
041f sar bx, 8
0422 shl bx, 1
0424 mov word ptr [bx - 0x435a], ax
0428 mov bx, word ptr [bp + 6]
042b sar bx, 8
042e shl bx, 1
0430 push word ptr [bx - 0x435a]
0434 push ds
0435 push 0xbda1
0438 push word ptr [bp + 6]
043b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1084, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 26}}]
0440 test word ptr [bp - 0x10], 8
0445 je 0xcef1
0447 mov bx, word ptr [bp + 6]
044a sar bx, 8
044d shl bx, 1
044f push word ptr [bx - 0x435a]
0453 push 0
0455 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1110, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 156}}]
045a mov si, ax
045c push si
045d push si
045e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1119, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 263}}]
0463 sub ax, 3
0466 push ax
0467 push 0x400
046a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1131, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 412}}]
046f push si
0470 push si
0471 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1138, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 263}}]
0476 sub ax, 2
0479 push ax
047a push 0x400
047d push 0xf060
0480 push ds
0481 push 0xbda7
0484 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1157, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 410}}]
0489 push si
048a push 0xf130
048d push 0
048f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1168, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 412}}]
0494 push si
0495 push si
0496 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1175, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 263}}]
049b dec ax
049c push ax
049d push 0x400
04a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1185, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 412}}]
04a5 push si
04a6 push 0x800
04a9 push 0
04ab push 0
04ad push 0
04af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1200, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 411}}]
04b4 push si
04b5 push 0
04b7 push 0xf040
04ba push ds
04bb push 0xbdb6
04be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1215, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 411}}]
04c3 mov bx, word ptr [bp + 6]
04c6 sar bx, 8
04c9 shl bx, 1
04cb push word ptr [bx - 0x435a]
04cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1232, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 45}}]
04d4 mov bx, word ptr [bp + 6]
04d7 sar bx, 8
04da shl bx, 1
04dc push word ptr [bx - 0x435a]
04e0 push 5
04e2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1251, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 42}}]
04e7 mov bx, word ptr [bp + 6]
04ea sar bx, 8
04ed shl bx, 1
04ef push word ptr [bx - 0x435a]
04f3 push 0
04f5 push 0
04f7 push 1
04f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1274, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
04fe mov bx, word ptr [bp + 6]
0501 sar bx, 8
0504 shl bx, 1
0506 push word ptr [bx - 0x435a]
050a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1291, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
050f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _clip_Off
0514 push word ptr [bp + 6]
0517 nop 
0518 push cs
0519 call 0xe3a4 ; _win_UnlockWin
051c add sp, 2
051f lea ax, [bp - 0x12]
0522 push ss
0523 push ax
0524 push 0
0526 push 0x200
0529 push 0x209
052c push 1
052e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1327, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0533 or ax, ax
0535 jne 0xcf4d
0537 lea ax, [bp - 0x12]
053a push ss
053b push ax
053c push 0
053e push 0x100
0541 push 0x108
0544 push 1
0546 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1351, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
054b or ax, ax
054d jne 0xcf4d
054f lea ax, [bp - 0x12]
0552 push ss
0553 push ax
0554 push 0
0556 push 0x21
0558 push 0x21
055a push 1
055c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1373, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
0561 or ax, ax
0563 jne 0xcf4d
0565 pop si
0566 pop di
0567 leave 
0568 retf 
```

## Known declaration examples

- `extern void far clip_Off(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int near hInst;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern int near ribbonBarHeight;` — src/recovered/wf_win_GetObjRect-1895b30cfd.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern void far win_Recalc(int window);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_win_UnlockWin'], 'segment': 7, 'target_offset': 58276, 'caller_offsets': [1305]}
- {'callee_names': ['_win_LockWinHigh'], 'segment': 7, 'target_offset': 58278, 'caller_offsets': [27]}
- {'callee_names': ['_win_Recalc'], 'segment': 7, 'target_offset': 59106, 'caller_offsets': [93]}

## Neighbors

- {'symbol': '_win_LoadWindow', 'offset': 50786, 'source': None, 'size': 419}
- {'symbol': '_win_LoadAllWindows', 'offset': 51206, 'source': None, 'size': 552}
- {'symbol': '_win_Close', 'offset': 53144, 'source': None, 'size': 168}
- {'symbol': '_win_Events', 'offset': 53312, 'source': None, 'size': 112}
