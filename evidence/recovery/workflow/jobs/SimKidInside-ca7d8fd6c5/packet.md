# Recovery task _SimKidInside

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 2036 bytes.

```asm
0000 enter 0x22, 0
0004 push di
0005 push si
0006 cmp word ptr [0xac5a], 1 ; _ForSaleState
000b jne 0x20c6
000d jmp 0x28a6
0010 mov bx, 0x8a86
0013 mov es, word ptr [0xc50e]
0017 mov word ptr [bp - 0xa], bx
001a mov word ptr [bp - 8], es
001d cmp word ptr es:[bx], 0x1e
0021 jge 0x2114
0023 mov bx, word ptr es:[bx]
0026 mov al, byte ptr [bx + 0x2380]
002a cwde 
002b mov bx, 0x8a84
002e mov es, word ptr [0xc50c]
0032 mov word ptr [bp - 0xe], bx
0035 mov word ptr [bp - 0xc], es
0038 inc word ptr es:[bx]
003b cmp ax, word ptr es:[bx]
003e jge 0x2114
0040 mov word ptr es:[bx], 0
0045 push 3
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004c add sp, 2
004f or ax, ax
0051 je 0x211a
0053 dec ax
0054 je 0x2126
0056 dec ax
0057 je 0x2132
0059 mov di, word ptr [bp - 6]
005c jmp 0x2140
005e mov di, word ptr [bp - 6]
0061 jmp 0x2252
0064 les bx, ptr [bp - 0xa]
0067 mov bx, word ptr es:[bx]
006a mov di, word ptr [bx + 0x2534]
006e jmp 0x213c
0070 les bx, ptr [bp - 0xa]
0073 mov bx, word ptr es:[bx]
0076 mov di, word ptr [bx + 0x254a]
007a jmp 0x213c
007c les bx, ptr [bp - 0xa]
007f mov bx, word ptr es:[bx]
0082 mov di, word ptr [bx + 0x2560]
0086 and di, 0xff
008a les bx, ptr [bp - 0xa]
008d mov word ptr es:[bx], di
0090 mov ax, di
0092 cmp ax, 0x21
0095 jne 0x2150
0097 jmp 0x2224
009a jbe 0x2155
009c jmp 0x2252
009f sub al, 6
00a1 je 0x216c
00a3 dec al
00a5 je 0x219e
00a7 sub al, 7
00a9 je 0x21d0
00ab sub al, 2
00ad jne 0x2168
00af jmp 0x2212
00b2 jmp 0x2252
00b5 nop 
00b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 185, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00bb add ax, 0x12c
00be adc dx, 0
00c1 mov es, word ptr [0xc4f6]
00c5 mov word ptr es:[0x7d4a], ax
00c9 mov word ptr es:[0x7d4c], dx
00ce mov es, word ptr [0xc504]
00d2 mov word ptr es:[0x99da], 1
00d9 mov es, word ptr [0xc52a]
00dd mov word ptr es:[0x72f2], 0x15
00e4 jmp 0x2252
00e7 nop 
00e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 235, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00ed add ax, 0x12c
00f0 adc dx, 0
00f3 mov es, word ptr [0xc4f6]
00f7 mov word ptr es:[0x7d4a], ax
00fb mov word ptr es:[0x7d4c], dx
0100 mov es, word ptr [0xc504]
0104 mov word ptr es:[0x99da], 1
010b mov es, word ptr [0xc52a]
010f mov word ptr es:[0x72f2], 0x16
0116 jmp 0x2252
0119 nop 
011a push 3
011c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0121 add sp, 2
0124 mov si, ax
0126 add si, 0xf
0129 cmp si, 0x16
012c jg 0x2252
012e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0133 add ax, 0x12c
0136 adc dx, 0
0139 mov es, word ptr [0xc4f6]
013d mov word ptr es:[0x7d4a], ax
0141 mov word ptr es:[0x7d4c], dx
0146 mov es, word ptr [0xc504]
014a mov word ptr es:[0x99da], 1
0151 mov es, word ptr [0xc52a]
0155 mov word ptr es:[0x72f2], si
015a jmp 0x2252
015c push 2
015e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 353, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0163 add sp, 2
0166 mov si, ax
0168 add si, 0x12
016b jmp 0x21df
016d nop 
016e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 369, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0173 add ax, 0x12c
0176 adc dx, 0
0179 mov es, word ptr [0xc4f6]
017d mov word ptr es:[0x7d4a], ax
0181 mov word ptr es:[0x7d4c], dx
0186 mov es, word ptr [0xc504]
018a mov word ptr es:[0x99da], 1
0191 mov es, word ptr [0xc52a]
0195 mov word ptr es:[0x72f2], 0x14
019c les bx, ptr [bp - 0xa]
019f cmp word ptr es:[bx], 0x1e
01a3 jl 0x225e
01a5 jmp 0x2506
01a8 mov ax, word ptr es:[bx]
01ab cmp ax, 0x15
01ae jbe 0x2269
01b0 jmp 0x2550
01b3 shl ax, 1
01b5 xchg bx, ax
01b6 jmp word ptr cs:[bx + 0x2272]
01bb nop 
01bc dw offset 0x229e
01be dw offset 0x22c4
01c0 dw offset 0x22e4
01c2 dw offset 0x2304
01c4 dw offset 0x2324
01c6 dw offset 0x2346
01c8 dw offset 0x2368
01ca dw offset 0x238a
01cc dw offset 0x23ac
01ce dw offset 0x23ce
01d0 dw offset 0x23f0
01d2 dw offset 0x2412
01d4 dw offset 0x2434
01d6 dw offset 0x2456
01d8 dw offset 0x2478
01da dw offset 0x249a
01dc dw offset 0x2550
01de dw offset 0x2550
01e0 dw offset 0x2550
01e2 dw offset 0x2550
01e4 dw offset 0x24bc
01e6 dw offset 0x24e4
01e8 mov es, word ptr [0xc50c]
01ec mov bx, word ptr es:[0x8a84]
01f1 mov di, word ptr [bx + 0x2396]
01f5 and di, 0xff
01f9 mov al, byte ptr [bx + 0x239a]
01fd sub ah, ah
01ff mov word ptr [bp - 2], ax
0202 mov al, byte ptr [bx + 0x239e]
0206 sub ah, ah
0208 mov word ptr [bp - 4], ax
020b jmp 0x2550
020e mov es, word ptr [0xc50c]
0212 mov bx, word ptr es:[0x8a84]
0217 mov di, word ptr [bx + 0x23a2]
021b and di, 0xff
021f mov al, byte ptr [bx + 0x23a6]
0223 sub ah, ah
0225 mov word ptr [bp - 2], ax
0228 mov al, byte ptr [bx + 0x23aa]
022c jmp 0x22bc
022e mov es, word ptr [0xc50c]
0232 mov bx, word ptr es:[0x8a84]
0237 mov di, word ptr [bx + 0x23ae]
023b and di, 0xff
023f mov al, byte ptr [bx + 0x23c2]
0243 sub ah, ah
0245 mov word ptr [bp - 2], ax
0248 mov al, byte ptr [bx + 0x23d6]
024c jmp 0x22bc
024e mov es, word ptr [0xc50c]
0252 mov bx, word ptr es:[0x8a84]
0257 mov di, word ptr [bx + 0x23ea]
025b and di, 0xff
025f mov al, byte ptr [bx + 0x23fe]
0263 sub ah, ah
0265 mov word ptr [bp - 2], ax
0268 mov al, byte ptr [bx + 0x2412]
026c jmp 0x22bc
026e mov es, word ptr [0xc50c]
0272 mov bx, word ptr es:[0x8a84]
0277 mov di, word ptr [bx + 0x2426]
027b and di, 0xff
027f mov al, byte ptr [bx + 0x242a]
0283 sub ah, ah
0285 mov word ptr [bp - 2], ax
0288 mov al, byte ptr [bx + 0x242e]
028c jmp 0x22bc
028f nop 
0290 mov es, word ptr [0xc50c]
0294 mov bx, word ptr es:[0x8a84]
0299 mov di, word ptr [bx + 0x2432]
029d and di, 0xff
02a1 mov al, byte ptr [bx + 0x2436]
02a5 sub ah, ah
02a7 mov word ptr [bp - 2], ax
02aa mov al, byte ptr [bx + 0x243a]
02ae jmp 0x22bc
02b1 nop 
02b2 mov es, word ptr [0xc50c]
02b6 mov bx, word ptr es:[0x8a84]
02bb mov di, word ptr [bx + 0x243e]
02bf and di, 0xff
02c3 mov al, byte ptr [bx + 0x244a]
02c7 sub ah, ah
02c9 mov word ptr [bp - 2], ax
02cc mov al, byte ptr [bx + 0x2456]
02d0 jmp 0x22bc
02d3 nop 
02d4 mov es, word ptr [0xc50c]
02d8 mov bx, word ptr es:[0x8a84]
02dd mov di, word ptr [bx + 0x2462]
02e1 and di, 0xff
02e5 mov al, byte ptr [bx + 0x246e]
02e9 sub ah, ah
02eb mov word ptr [bp - 2], ax
02ee mov al, byte ptr [bx + 0x247a]
02f2 jmp 0x22bc
02f5 nop 
02f6 mov es, word ptr [0xc50c]
02fa mov bx, word ptr es:[0x8a84]
02ff mov di, word ptr [bx + 0x2486]
0303 and di, 0xff
0307 mov al, byte ptr [bx + 0x248c]
030b sub ah, ah
030d mov word ptr [bp - 2], ax
0310 mov al, byte ptr [bx + 0x2492]
0314 jmp 0x22bc
0317 nop 
0318 mov es, word ptr [0xc50c]
031c mov bx, word ptr es:[0x8a84]
0321 mov di, word ptr [bx + 0x2498]
0325 and di, 0xff
0329 mov al, byte ptr [bx + 0x249e]
032d sub ah, ah
032f mov word ptr [bp - 2], ax
0332 mov al, byte ptr [bx + 0x24a4]
0336 jmp 0x22bc
0339 nop 
033a mov es, word ptr [0xc50c]
033e mov bx, word ptr es:[0x8a84]
0343 mov di, word ptr [bx + 0x24aa]
0347 and di, 0xff
034b mov al, byte ptr [bx + 0x24ae]
034f sub ah, ah
0351 mov word ptr [bp - 2], ax
0354 mov al, byte ptr [bx + 0x24b2]
0358 jmp 0x22bc
035b nop 
035c mov es, word ptr [0xc50c]
0360 mov bx, word ptr es:[0x8a84]
0365 mov di, word ptr [bx + 0x24b6]
0369 and di, 0xff
036d mov al, byte ptr [bx + 0x24ba]
0371 sub ah, ah
0373 mov word ptr [bp - 2], ax
0376 mov al, byte ptr [bx + 0x24be]
037a jmp 0x22bc
037d nop 
037e mov es, word ptr [0xc50c]
0382 mov bx, word ptr es:[0x8a84]
0387 mov di, word ptr [bx + 0x24c2]
038b and di, 0xff
038f mov al, byte ptr [bx + 0x24c8]
0393 sub ah, ah
0395 mov word ptr [bp - 2], ax
0398 mov al, byte ptr [bx + 0x24ce]
039c jmp 0x22bc
039f nop 
03a0 mov es, word ptr [0xc50c]
03a4 mov bx, word ptr es:[0x8a84]
03a9 mov di, word ptr [bx + 0x24d4]
03ad and di, 0xff
03b1 mov al, byte ptr [bx + 0x24da]
03b5 sub ah, ah
03b7 mov word ptr [bp - 2], ax
03ba mov al, byte ptr [bx + 0x24e0]
03be jmp 0x22bc
03c1 nop 
03c2 mov es, word ptr [0xc50c]
03c6 mov bx, word ptr es:[0x8a84]
03cb mov di, word ptr [bx + 0x24e6]
03cf and di, 0xff
03d3 mov al, byte ptr [bx + 0x24ea]
03d7 sub ah, ah
03d9 mov word ptr [bp - 2], ax
03dc mov al, byte ptr [bx + 0x24ee]
03e0 jmp 0x22bc
03e3 nop 
03e4 mov es, word ptr [0xc50c]
03e8 mov bx, word ptr es:[0x8a84]
03ed mov di, word ptr [bx + 0x24f2]
03f1 and di, 0xff
03f5 mov al, byte ptr [bx + 0x24f6]
03f9 sub ah, ah
03fb mov word ptr [bp - 2], ax
03fe mov al, byte ptr [bx + 0x24fa]
0402 jmp 0x22bc
0405 nop 
0406 mov es, word ptr [0xc50c]
040a mov bx, word ptr es:[0x8a84]
040f mov ax, bx
0411 shl bx, 1
0413 mov di, word ptr [bx + 0x24fe]
0417 mov bx, ax
0419 mov cl, byte ptr [bx + 0x250e]
041d sub ch, ch
041f mov word ptr [bp - 2], cx
0422 mov cl, byte ptr [bx + 0x2516]
0426 sub ch, ch
0428 mov word ptr [bp - 4], cx
042b jmp 0x2550
042d nop 
042e mov es, word ptr [0xc50c]
0432 mov bx, word ptr es:[0x8a84]
0437 mov ax, bx
0439 shl bx, 1
043b mov di, word ptr [bx + 0x251e]
043f mov bx, ax
0441 mov cl, byte ptr [bx + 0x2528]
0445 sub ch, ch
0447 mov word ptr [bp - 2], cx
044a mov cl, byte ptr [bx + 0x252e]
044e jmp 0x24dc
0450 cmp word ptr es:[bx], 0x27
0454 jge 0x2550
0456 mov si, word ptr es:[bx]
0459 sub si, 0x1e
045c mov bx, si
045e mov di, word ptr [bx + si + 0x2576]
0462 mov al, byte ptr [si + 0x2588]
0466 sub ah, ah
0468 mov word ptr [bp - 2], ax
046b mov al, byte ptr [si + 0x2592]
046f mov word ptr [bp - 4], ax
0472 mov al, byte ptr [si + 0x259c]
0476 push ax
0477 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
047c add sp, 2
047f or ax, ax
0481 jne 0x2550
0483 mov al, byte ptr [si + 0x25a6]
0487 sub ah, ah
0489 les bx, ptr [bp - 0xa]
048c mov word ptr es:[bx], ax
048f mov es, word ptr [0xc50c]
0493 mov word ptr es:[0x8a84], 0
049a mov word ptr [0xac74], 0 ; _BoyHere
04a0 les bx, ptr [bp - 0xa]
04a3 cmp word ptr es:[bx], 0x26
04a7 jne 0x256d
04a9 mov ax, 1
04ac mov es, word ptr [0xc500]
04b0 mov word ptr es:[0x8a72], ax
04b4 mov word ptr [0xac74], ax ; _BoyHere
04b7 mov es, word ptr [bp - 8]
04ba cmp word ptr es:[bx], 0x14
04be jne 0x2588
04c0 mov es, word ptr [0xc50c]
04c4 cmp word ptr es:[0x8a84], 2
04ca jle 0x2588
04cc mov word ptr [0xac74], 1 ; _BoyHere
04d2 mov es, word ptr [bp - 8]
04d5 cmp word ptr es:[bx], 0x15
04d9 jne 0x25a3
04db mov es, word ptr [0xc50c]
04df cmp word ptr es:[0x8a84], 3
04e5 jge 0x25a3
04e7 mov word ptr [0xac74], 1 ; _BoyHere
04ed mov ax, word ptr [bp - 2]
04f0 mov word ptr [0xac76], ax ; _BoyX
04f3 mov ax, word ptr [bp - 4]
04f6 mov word ptr [0xac78], ax ; _BoyY
04f9 mov word ptr [0xac7a], di ; _BoyFrame
04fd mov es, word ptr [0xc546]
0501 cmp word ptr es:[0x8610], 0
0507 jne 0x263c
0509 cmp word ptr [0xce82], 2 ; _YardMode
050e jge 0x263c
0510 mov bx, 0x8a84
0513 mov es, word ptr [0xc50c]
0517 mov word ptr [bp - 0xe], bx
051a mov word ptr [bp - 0xc], es
051d cmp word ptr es:[bx], 3
0521 jne 0x25e8
0523 les bx, ptr [bp - 0xa]
0526 cmp word ptr es:[bx], 0x14
052a jne 0x25e8
052c cmp di, 0x384
0530 je 0x262e
0532 les bx, ptr [bp - 0xe]
0535 cmp word ptr es:[bx], 1
0539 jne 0x2600
053b les bx, ptr [bp - 0xa]
053e cmp word ptr es:[bx], 0x15
0542 jne 0x2600
0544 cmp di, 0x387
0548 je 0x262e
054a les bx, ptr [bp - 0xe]
054d cmp word ptr es:[bx], 6
0551 jne 0x2617
0553 les bx, ptr [bp - 0xa]
0556 cmp word ptr es:[bx], 0x14
055a jne 0x2617
055c cmp di, 6
055f je 0x262e
0561 les bx, ptr [bp - 0xe]
0564 cmp word ptr es:[bx], 3
0568 jne 0x263c
056a les bx, ptr [bp - 0xa]
056d cmp word ptr es:[bx], 0x15
0571 jne 0x263c
0573 cmp di, 1
0576 jne 0x263c
0578 push 0
057a push 0
057c push 0x18
057e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1409, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0583 add sp, 6
0586 mov ax, word ptr [0xac78] ; _BoyY
0589 add ax, word ptr [0xac76] ; _BoyX
058d sub ax, 0xc8
0590 mov word ptr [bp - 0x10], ax
0593 mov cx, 0x1c
0596 cdq 
0597 idiv cx
0599 mov es, word ptr [0xc506]
059d mov word ptr es:[0x78b0], ax
05a1 mov es, word ptr [0xc514]
05a5 mov word ptr es:[0x8a7e], 0
05ac mov es, word ptr [0xc516]
05b0 cmp word ptr es:[0x8a82], 1
05b6 sbb ax, ax
05b8 neg ax
05ba mov word ptr es:[0x8a82], ax
05be mov es, word ptr [0xc548]
05c2 mov bx, word ptr es:[0x7a60]
05c7 mov word ptr [bp - 0x12], bx
05ca shl bx, 4
05cd add bx, word ptr es:[0x7a62]
05d2 mov ax, word ptr [0xac78] ; _BoyY
05d5 sub ax, 0x26
05d8 mov word ptr [bp - 0x14], ax
05db mov cx, 0xa
05de cdq 
05df idiv cx
05e1 mov es, word ptr [0xc508]
05e5 mov word ptr es:[0x78d2], ax
05e9 mov es, word ptr [0xc548]
05ed cmp ax, word ptr es:[0x7a62]
05f2 je 0x26ad
05f4 jmp 0x28a6
05f7 mov ax, word ptr [bp - 0x12]
05fa mov es, word ptr [0xc506]
05fe cmp word ptr es:[0x78b0], ax
0603 je 0x26be
0605 jmp 0x28a6
0608 or bx, bx
060a jne 0x26c5
060c jmp 0x28a6
060f cmp bx, 1
0612 jne 0x26cd
0614 jmp 0x28a6
0617 cmp bx, 0x10
061a jne 0x26d5
061c jmp 0x28a6
061f cmp bx, 0x20
0622 jne 0x26dd
0624 jmp 0x28a6
0627 cmp word ptr [0xac7a], 0 ; _BoyFrame
062c jl 0x2702
062e cmp word ptr [0xac7a], 0xc ; _BoyFrame
0633 jge 0x2702
0635 mov bx, word ptr [0xac7a] ; _BoyFrame
0639 mov al, byte ptr [bx + 0x25b0]
063d sub ah, ah
063f mov es, word ptr [0xc500]
0643 mov word ptr es:[0x8a72], ax
0647 jmp 0x270d
0649 nop 
064a nop 
064b nop 
064c mov es, word ptr [0xc500]
0650 mov word ptr es:[0x8a72], 2
0657 mov es, word ptr [0xc514]
065b mov word ptr es:[0x8a7e], 1
0662 mov ax, word ptr [bp - 0x14]
0665 cdq 
0666 idiv cx
0668 mov bx, 0x7a58
066b mov es, word ptr [0xc51a]
066f mov word ptr [bp - 0x18], bx
0672 mov word ptr [bp - 0x16], es
0675 mov word ptr es:[bx], dx
0678 mov ax, word ptr [bp - 0x10]
067b mov cx, 0x1c
067e mov si, dx
0680 cdq 
0681 idiv cx
0683 mov di, 0x7a4e
0686 mov es, word ptr [0xc518]
068a mov word ptr [bp - 0x1c], di
068d mov word ptr [bp - 0x1a], es
0690 mov word ptr es:[di], dx
0693 shl dl, 2
0696 add dl, 6
0699 and dx, 0x7f
069c mov word ptr es:[di], dx
069f lea ax, [si + 1]
06a2 mov cx, ax
06a4 shl ax, 1
06a6 add ax, cx
06a8 shl ax, 1
06aa and ax, 0x3f
06ad mov es, word ptr [bp - 0x16]
06b0 mov word ptr es:[bx], ax
06b3 mov es, word ptr [0xc500]
06b7 test byte ptr es:[0x8a72], 1
06bd je 0x2790
06bf mov es, word ptr [0xc516]
06c3 cmp word ptr es:[0x8a82], 0
06c9 je 0x278a
06cb mov es, word ptr [bp - 0x16]
06ce add word ptr es:[bx], 6
06d2 jmp 0x27a9
06d4 les bx, ptr [bp - 0x18]
06d7 jmp 0x27a5
06d9 nop 
06da mov es, word ptr [0xc516]
06de cmp word ptr es:[0x8a82], 0
06e4 je 0x27a2
06e6 les bx, ptr [bp - 0x1c]
06e9 jmp 0x2784
06eb nop 
06ec les bx, ptr [bp - 0x1c]
06ef sub word ptr es:[bx], 6
06f3 les bx, ptr [bp - 0x18]
06f6 push word ptr es:[bx]
06f9 les bx, ptr [bp - 0x1c]
06fc push word ptr es:[bx]
06ff nop 
0700 push cs
0701 call 0x3386 ; _FootFall
0704 add sp, 4
0707 push 0x7e
0709 push 0
070b push 9
070d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1808, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0712 add sp, 6
0715 mov word ptr [bp - 2], 0
071a mov ax, word ptr [0xac84] ; _RpopT
071d add ax, word ptr [0xac82] ; _BpopT
0721 shl ax, 3
0724 or ax, ax
0726 jg 0x27e1
0728 jmp 0x2880
072b mov ax, 0x9b6a
072e mov <resolved loader operand; see bindings> ; [{'operand_offset': 1839, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0731 mov word ptr [bp - 0x20], ax
0734 mov word ptr [bp - 0x1e], cx
0737 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1850, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand128
073c mov si, ax
073e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1857, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
0743 mov di, ax
0745 mov bx, si
0747 shl bx, 6
074a add bx, di
074c add bx, 0x68e8
0750 mov word ptr [bp - 0x22], bx
0753 cmp byte ptr [bx], 0
0756 je 0x2852
0758 push di
0759 push si
075a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1885, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
075f add sp, 4
0762 les bx, ptr [bp - 0x20]
0765 mov word ptr es:[bx], ax
0768 or ax, ax
076a jl 0x2852
076c mov bx, word ptr es:[bx]
076f mov es, word ptr [0xc54a]
0773 mov al, byte ptr es:[bx + 0x2f62]
0778 and ax, 0x80
077b push ax
077c push di
077d push si
077e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1921, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _DeadAntHere
0783 add sp, 6
0786 xor al, al
0788 les bx, ptr [bp - 0x20]
078b mov bx, word ptr es:[bx]
078e mov es, word ptr [0xc54a]
0792 mov byte ptr es:[bx + 0x2f62], al
0797 mov bx, word ptr [bp - 0x22]
079a mov byte ptr [bx], al
079c mov ax, word ptr [0xac7c] ; _SpidX
079f sar ax, 4
07a2 cmp ax, si
07a4 jne 0x286b
07a6 mov ax, word ptr [0xac7e] ; _SpidY
07a9 sar ax, 4
07ac cmp ax, di
07ae jne 0x286b
07b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1971, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _KillSpider
07b5 mov ax, word ptr [0xac84] ; _RpopT
07b8 add ax, word ptr [0xac82] ; _BpopT
07bc shl ax, 3
07bf inc word ptr [bp - 2]
07c2 cmp ax, word ptr [bp - 2]
07c5 jle 0x2880
07c7 jmp 0x27ed
07ca mov es, word ptr [0xc53e]
07ce cmp word ptr es:[0x80b4], 2
07d4 jne 0x28a6
07d6 cmp word ptr [0xce80], 1 ; _MePlane
07db jne 0x28a6
07dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2016, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
07e2 or ax, ax
07e4 jne 0x28a6
07e6 push 9
07e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2027, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
07ed add sp, 2
07f0 pop si
07f1 pop di
07f2 leave 
07f3 retf 
```

## Known declaration examples

- `extern int near BoyFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near BoyHere;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near BoyX;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near BoyY;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near BpopT;` — src/recovered/DecEatB.c
- `extern int near BpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far FindInAList(int x, int y);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int near ForSaleState;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near ForSaleState;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern unsigned long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near RpopT;` — src/recovered/DecEatR.c
- `extern int near RpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand64(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int near YardMode;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsValidYard', 'offset': 8306, 'source': 'src/recovered/IsValidYard.c', 'size': 36}
- {'symbol': '_InitGrassMap', 'offset': 8342, 'source': 'src/recovered/InitGrassMap.c', 'size': 32}
- {'symbol': '_SimBird', 'offset': 10410, 'source': None, 'size': 633}
- {'symbol': '_SimCat', 'offset': 11044, 'source': None, 'size': 663}
