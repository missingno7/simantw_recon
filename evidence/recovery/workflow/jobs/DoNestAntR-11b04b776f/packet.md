# Recovery task _DoNestAntR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 1925 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xa]
0009 mov ax, di
000b and ax, 0x78
000e sar ax, 3
0011 mov word ptr [bp - 2], ax
0014 test di, 0x80
0018 jne 0x53c1
001a jmp 0x5920
001d mov es, word ptr [0xc384]
0021 mov bx, word ptr es:[0x9b6a]
0026 mov es, word ptr [0xc386]
002a mov al, byte ptr es:[bx + 0x44f0]
002f sub ah, ah
0031 mov si, ax
0033 mov bx, ax
0035 shl bx, 1
0037 mov es, word ptr [0xc388]
003b inc word ptr es:[bx + 0x7be4]
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand256
0045 or ax, ax
0047 jne 0x5432
0049 cmp si, 9
004c je 0x5432
004e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
0053 cmp ax, word ptr [0xac88] ; _HealthR
0057 jle 0x5432
0059 xor al, al
005b mov es, word ptr [0xc384]
005f mov bx, word ptr es:[0x9b6a]
0064 mov es, word ptr [0xc386]
0068 mov byte ptr es:[bx + 0x46e6], al
006d mov si, word ptr [bp + 6]
0070 shl si, 6
0073 mov bx, word ptr [bp + 8]
0076 mov byte ptr [bx + si - 0x6718], al
007a mov es, word ptr [0xc38a]
007e add word ptr es:[0x9fc6], 1
0084 adc word ptr es:[0x9fc8], 0
008a jmp 0x5b25
008d nop 
008e mov ax, si
0090 cmp ax, 0x11
0093 ja 0x5466
0095 shl ax, 1
0097 xchg bx, ax
0098 jmp word ptr cs:[bx + 0x5442]
009d nop 
009e dw offset 0x5548
00a0 dw offset 0x55c4
00a2 dw offset 0x5862
00a4 dw offset 0x55da
00a6 dw offset 0x55ea
00a8 dw offset 0x5862
00aa dw offset 0x5862
00ac dw offset 0x5862
00ae dw offset 0x55fc
00b0 dw offset 0x560e
00b2 dw offset 0x5620
00b4 dw offset 0x5862
00b6 dw offset 0x5862
00b8 dw offset 0x562e
00ba dw offset 0x574e
00bc dw offset 0x5862
00be dw offset 0x5862
00c0 dw offset 0x5874
00c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 197, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
00c7 or ax, ax
00c9 jne 0x548c
00cb push word ptr [bp - 2]
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 209, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
00d3 add sp, 2
00d6 mov es, word ptr [0xc384]
00da mov bx, word ptr es:[0x9b6a]
00df mov es, word ptr [0xc386]
00e3 mov byte ptr es:[bx + 0x44f0], al
00e8 mov di, word ptr [bp + 8]
00eb mov si, word ptr [bp + 6]
00ee mov bx, si
00f0 shl bx, 6
00f3 add bx, di
00f5 mov word ptr [bp - 8], bx
00f8 mov al, byte ptr [bx - 0x6718]
00fc sub ah, ah
00fe mov word ptr [bp - 2], ax
0101 cmp ax, 7
0104 jle 0x54fa
0106 cmp ax, 0x68
0109 jge 0x54fa
010b push ax
010c push di
010d push si
010e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 273, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0113 add sp, 6
0116 mov word ptr [bp - 6], ax
0119 or ax, ax
011b jl 0x5511
011d push word ptr [bp + 0xa]
0120 push word ptr [bp - 2]
0123 call 0x26f4 ; _GetWinner
0126 add sp, 4
0129 mov es, word ptr [0xc386]
012d mov bx, word ptr [bp - 6]
0130 mov byte ptr es:[bx + 0x48dc], al
0135 and al, 0x80
0137 add al, 0x70
0139 mov byte ptr es:[bx + 0x46e6], al
013e mov bx, word ptr [bp - 8]
0141 mov byte ptr [bx - 0x6718], al
0145 mov bx, word ptr [bp - 6]
0148 mov byte ptr es:[bx + 0x44f0], 0xa
014e mov word ptr [bp - 4], 1
0153 jmp 0x5516
0155 nop 
0156 push ax
0157 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 346, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
015c add sp, 2
015f or ax, ax
0161 je 0x5511
0163 cmp word ptr [0xce98], 0 ; _MeColor
0168 jne 0x5511
016a jmp 0x55ae
016d mov word ptr [bp - 4], 0
0172 cmp word ptr [bp - 4], 0
0176 je 0x551f
0178 jmp 0x5b25
017b mov al, byte ptr [bp + 0xa]
017e and ax, 7
0181 push ax
0182 push di
0183 push si
0184 nop 
0185 push cs
0186 call 0x6850 ; _TryMoveDirR
0189 add sp, 6
018c or ax, ax
018e je 0x5537
0190 jmp 0x5b25
0193 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 406, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0198 push ax
0199 push di
019a push si
019b nop 
019c push cs
019d call 0x6850 ; _TryMoveDirR
01a0 jmp 0x5b22
01a3 nop 
01a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
01a9 or ax, ax
01ab jne 0x556e
01ad push word ptr [bp - 2]
01b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 435, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
01b5 add sp, 2
01b8 mov es, word ptr [0xc384]
01bc mov bx, word ptr es:[0x9b6a]
01c1 mov es, word ptr [0xc386]
01c5 mov byte ptr es:[bx + 0x44f0], al
01ca mov di, word ptr [bp + 8]
01cd mov si, word ptr [bp + 6]
01d0 mov bx, si
01d2 shl bx, 6
01d5 add bx, di
01d7 mov word ptr [bp - 8], bx
01da mov al, byte ptr [bx - 0x6718]
01de sub ah, ah
01e0 mov word ptr [bp - 2], ax
01e3 cmp ax, 7
01e6 jle 0x5594
01e8 cmp ax, 0x68
01eb jge 0x5594
01ed jmp 0x54af
01f0 push ax
01f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 500, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
01f6 add sp, 2
01f9 or ax, ax
01fb jne 0x55a4
01fd jmp 0x5511
0200 cmp word ptr [0xce98], 0 ; _MeColor
0205 je 0x55ae
0207 jmp 0x5511
020a mov es, word ptr [0xc384]
020e push word ptr es:[0x9b6a]
0213 push 3
0215 nop 
0216 push cs
0217 call 0x823e ; _YellowFight
021a add sp, 4
021d jmp 0x54f2
0220 push word ptr [bp - 2]
0223 push di
0224 push word ptr [bp + 8]
0227 push word ptr [bp + 6]
022a nop 
022b push cs
022c call 0x690a ; _DoNestingR
022f add sp, 8
0232 jmp 0x5b25
0235 nop 
0236 push di
0237 push word ptr [bp + 8]
023a push word ptr [bp + 6]
023d nop 
023e push cs
023f call 0x6c8c ; _DoFoodInR
0242 jmp 0x5b22
0245 nop 
0246 push word ptr [bp - 2]
0249 push di
024a push word ptr [bp + 8]
024d push word ptr [bp + 6]
0250 nop 
0251 push cs
0252 call 0x6f0c ; _DoDigInR
0255 jmp 0x55d3
0257 nop 
0258 push word ptr [bp + 8]
025b push word ptr [bp + 6]
025e nop 
025f push cs
0260 call 0x62a6 ; _SimEggR
0263 add sp, 4
0266 jmp 0x5b25
0269 nop 
026a push di
026b push word ptr [bp - 2]
026e push word ptr [bp + 8]
0271 push word ptr [bp + 6]
0274 nop 
0275 push cs
0276 call 0x6386 ; _SimQueenR
0279 jmp 0x55d3
027b nop 
027c push word ptr [bp + 8]
027f push word ptr [bp + 6]
0282 nop 
0283 push cs
0284 call 0x6072 ; _DoNestFightR
0287 jmp 0x5607
0289 nop 
028a mov bx, word ptr [bp + 6]
028d shl bx, 6
0290 add bx, word ptr [bp + 8]
0293 mov word ptr [bp - 8], bx
0296 mov al, byte ptr [bx - 0x6718]
029a sub ah, ah
029c mov word ptr [bp - 2], ax
029f cmp ax, 7
02a2 jle 0x5696
02a4 cmp ax, 0x68
02a7 jge 0x5696
02a9 push ax
02aa push word ptr [bp + 8]
02ad push word ptr [bp + 6]
02b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 691, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
02b5 add sp, 6
02b8 mov si, ax
02ba or si, si
02bc jl 0x56c2
02be push di
02bf push word ptr [bp - 2]
02c2 call 0x26f4 ; _GetWinner
02c5 add sp, 4
02c8 mov es, word ptr [0xc386]
02cc mov byte ptr es:[si + 0x48dc], al
02d1 and al, 0x80
02d3 add al, 0x70
02d5 mov byte ptr es:[si + 0x46e6], al
02da mov bx, word ptr [bp - 8]
02dd mov byte ptr [bx - 0x6718], al
02e1 mov byte ptr es:[si + 0x44f0], 0xa
02e7 mov word ptr [bp - 4], 1
02ec mov si, word ptr [bp - 4]
02ef jmp 0x56c4
02f1 nop 
02f2 push ax
02f3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 758, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
02f8 add sp, 2
02fb or ax, ax
02fd je 0x56c2
02ff cmp word ptr [0xce98], 0 ; _MeColor
0304 jne 0x56c2
0306 mov es, word ptr [0xc384]
030a push word ptr es:[0x9b6a]
030f push 3
0311 nop 
0312 push cs
0313 call 0x823e ; _YellowFight
0316 add sp, 4
0319 mov si, 1
031c jmp 0x56c4
031e xor si, si
0320 or si, si
0322 je 0x56cb
0324 jmp 0x5b25
0327 mov es, word ptr [0xc384]
032b mov bx, word ptr es:[0x9b6a]
0330 mov es, word ptr [0xc386]
0334 mov al, byte ptr es:[bx + 0x46e6]
0339 mov bx, word ptr [bp - 8]
033c mov byte ptr [bx - 0x6718], al
0340 push 0x14
0342 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 837, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0347 add sp, 2
034a or ax, ax
034c jne 0x5730
034e mov es, word ptr [0xc384]
0352 mov bx, word ptr es:[0x9b6a]
0357 mov es, word ptr [0xc386]
035b mov al, byte ptr es:[bx + 0x46e6]
0360 sub ah, ah
0362 mov di, ax
0364 mov si, di
0366 and si, 0x78
0369 sar si, 3
036c push di
036d push si
036e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 881, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
0373 add sp, 4
0376 mov es, word ptr [0xc384]
037a mov bx, word ptr es:[0x9b6a]
037f mov es, word ptr [0xc386]
0383 mov byte ptr es:[bx + 0x44f0], al
0388 jmp 0x5b25
038b nop 
038c mov es, word ptr [0xc38c]
0390 cmp word ptr es:[0x85fc], si
0395 jne 0x573e
0397 jmp 0x5b25
039a push 3
039c push word ptr [bp + 8]
039f push word ptr [bp + 6]
03a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 933, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _RestBalloons
03a7 jmp 0x5b22
03aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 941, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
03af or ax, ax
03b1 jne 0x5774
03b3 push word ptr [bp - 2]
03b6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 953, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
03bb add sp, 2
03be mov es, word ptr [0xc384]
03c2 mov bx, word ptr es:[0x9b6a]
03c7 mov es, word ptr [0xc386]
03cb mov byte ptr es:[bx + 0x44f0], al
03d0 mov di, word ptr [bp + 8]
03d3 mov si, word ptr [bp + 6]
03d6 mov bx, si
03d8 shl bx, 6
03db add bx, di
03dd mov word ptr [bp - 8], bx
03e0 mov al, byte ptr [bx - 0x6718]
03e4 sub ah, ah
03e6 mov word ptr [bp - 2], ax
03e9 cmp ax, 7
03ec jle 0x57e2
03ee cmp ax, 0x68
03f1 jge 0x57e2
03f3 push ax
03f4 push di
03f5 push si
03f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1017, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
03fb add sp, 6
03fe mov word ptr [bp - 6], ax
0401 or ax, ax
0403 jl 0x580c
0405 push word ptr [bp + 0xa]
0408 push word ptr [bp - 2]
040b call 0x26f4 ; _GetWinner
040e add sp, 4
0411 mov es, word ptr [0xc386]
0415 mov bx, word ptr [bp - 6]
0418 mov byte ptr es:[bx + 0x48dc], al
041d and al, 0x80
041f add al, 0x70
0421 mov byte ptr es:[bx + 0x46e6], al
0426 mov bx, word ptr [bp - 8]
0429 mov byte ptr [bx - 0x6718], al
042d mov bx, word ptr [bp - 6]
0430 mov byte ptr es:[bx + 0x44f0], 0xa
0436 mov word ptr [bp - 4], 1
043b jmp 0x5811
043d nop 
043e push ax
043f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1090, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0444 add sp, 2
0447 or ax, ax
0449 je 0x580c
044b cmp word ptr [0xce98], 0 ; _MeColor
0450 jne 0x580c
0452 mov es, word ptr [0xc384]
0456 push word ptr es:[0x9b6a]
045b push 3
045d nop 
045e push cs
045f call 0x823e ; _YellowFight
0462 add sp, 4
0465 jmp 0x57da
0467 nop 
0468 mov word ptr [bp - 4], 0
046d cmp word ptr [bp - 4], 0
0471 jne 0x583c
0473 mov al, byte ptr [bp + 0xa]
0476 and ax, 7
0479 push ax
047a push di
047b push si
047c nop 
047d push cs
047e call 0x6850 ; _TryMoveDirR
0481 add sp, 6
0484 or ax, ax
0486 jne 0x583c
0488 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
048d push ax
048e push di
048f push si
0490 nop 
0491 push cs
0492 call 0x6850 ; _TryMoveDirR
0495 add sp, 6
0498 mov es, word ptr [0xc38e]
049c cmp word ptr es:[0x8078], 0x64
04a2 jg 0x584b
04a4 jmp 0x5b25
04a7 mov es, word ptr [0xc384]
04ab mov bx, word ptr es:[0x9b6a]
04b0 mov es, word ptr [0xc386]
04b4 mov byte ptr es:[bx + 0x44f0], 0xf
04ba jmp 0x5b25
04bd nop 
04be push word ptr [bp + 0xa]
04c1 push word ptr [bp + 8]
04c4 push word ptr [bp + 6]
04c7 nop 
04c8 push cs
04c9 call 0x722a ; _DoDigOutR
04cc jmp 0x5b22
04cf nop 
04d0 mov si, di
04d2 mov di, word ptr [bp + 6]
04d5 mov bx, di
04d7 shl bx, 6
04da add bx, word ptr [bp + 8]
04dd mov word ptr [bp - 8], bx
04e0 cmp byte ptr [bx + 0x58e8], 0x14
04e5 jae 0x58a0
04e7 mov ax, si
04e9 and ax, 0x78
04ec sar ax, 3
04ef push ax
04f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
04f5 add sp, 2
04f8 jmp 0x571a
04fb nop 
04fc push 3
04fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1281, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0503 add sp, 2
0506 mov cx, si
0508 add al, cl
050a dec al
050c and ax, 7
050f mov word ptr [bp - 2], ax
0512 and cx, 0xf8
0516 or ax, cx
0518 mov si, ax
051a mov es, word ptr [0xc384]
051e mov bx, word ptr es:[0x9b6a]
0523 mov es, word ptr [0xc386]
0527 mov byte ptr es:[bx + 0x46e6], al
052c mov bx, word ptr [bp - 8]
052f mov byte ptr [bx - 0x6718], al
0533 push 0x64
0535 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1336, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
053a add sp, 2
053d or ax, ax
053f je 0x58e8
0541 jmp 0x5b25
0544 xor al, al
0546 mov bx, word ptr [bp - 8]
0549 mov byte ptr [bx - 0x6718], al
054d mov es, word ptr [0xc384]
0551 mov bx, word ptr es:[0x9b6a]
0556 mov es, word ptr [0xc386]
055a mov byte ptr es:[bx + 0x46e6], al
055f mov ax, si
0561 test al, 0x80
0563 je 0x590c
0565 jmp 0x541e
0568 mov es, word ptr [0xc390]
056c add word ptr es:[0x9b26], 1
0572 adc word ptr es:[0x9b28], 0
0578 pop si
0579 pop di
057a leave 
057b retf 
057c mov es, word ptr [0xc384]
0580 mov bx, word ptr es:[0x9b6a]
0585 mov es, word ptr [0xc386]
0589 mov al, byte ptr es:[bx + 0x44f0]
058e sub ah, ah
0590 mov si, ax
0592 mov es, word ptr [0xc392]
0596 mov bx, si
0598 shl bx, 1
059a inc word ptr es:[bx + 0x786a]
059f cmp di, 8
05a2 jge 0x5978
05a4 xor al, al
05a6 mov es, word ptr [0xc384]
05aa mov bx, word ptr es:[0x9b6a]
05af mov es, word ptr [0xc386]
05b3 mov byte ptr es:[bx + 0x46e6], al
05b8 mov si, word ptr es:[bx + 0x4104]
05bd and si, 0xff
05c1 shl si, 6
05c4 mov bl, byte ptr es:[bx + 0x42fa]
05c9 sub bh, bh
05cb mov byte ptr [bx + si - 0x6718], al
05cf pop si
05d0 pop di
05d1 leave 
05d2 retf 
05d3 nop 
05d4 mov word ptr [bp - 4], si
05d7 cmp di, 0x6f
05da jle 0x5983
05dc jmp 0x5620
05df mov bx, word ptr [bp + 6]
05e2 shl bx, 6
05e5 add bx, word ptr [bp + 8]
05e8 mov word ptr [bp - 8], bx
05eb mov si, word ptr [bx - 0x6718]
05ef and si, 0xff
05f3 cmp si, 0x80
05f7 jg 0x59a0
05f9 jmp 0x5a6e
05fc cmp si, 0xe8
0600 jl 0x59a9
0602 jmp 0x5a6e
0605 push si
0606 push word ptr [bp + 8]
0609 push word ptr [bp + 6]
060c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1551, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
0611 add sp, 6
0614 mov di, ax
0616 or di, di
0618 jge 0x59c1
061a jmp 0x5a6e
061d mov <resolved loader operand; see bindings> ; [{'operand_offset': 1566, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0620 mov es, ax
0622 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1571, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0625 mov ds, ax
0627 cmp si, 0xdf
062b jle 0x59f0
062d xor al, al
062f mov byte ptr es:[di + 0x46e6], al
0634 mov cl, byte ptr es:[di + 0x42fa]
0639 sub ch, ch
063b mov bl, byte ptr es:[di + 0x4104]
0640 sub bh, bh
0642 shl bx, 6
0645 add bx, cx
0647 mov byte ptr ss:[bx - 0x6718], al
064c cmp si, 0x88
0650 jge 0x5a22
0652 mov bx, word ptr [0x9b6a]
0656 mov byte ptr es:[bx + 0x44f0], 3
065c or byte ptr es:[bx + 0x46e6], 8
0662 mov al, byte ptr es:[bx + 0x46e6]
0667 mov bx, word ptr [bp - 8]
066a add bx, 0x98e8
066e mov byte ptr ss:[bx], al
0671 mov byte ptr es:[di + 0x46e6], 0
0677 push ss
0678 pop ds
0679 pop si
067a pop di
067b leave 
067c retf 
067d nop 
067e push ss
067f pop ds
0680 push word ptr [bp + 0xa]
0683 mov es, word ptr [0xc386]
0687 mov al, byte ptr es:[di + 0x46e6]
068c sub ah, ah
068e push ax
068f call 0x26f4 ; _GetWinner
0692 add sp, 4
0695 mov si, ax
0697 mov es, word ptr [0xc384]
069b mov bx, word ptr es:[0x9b6a]
06a0 mov es, word ptr [0xc386]
06a4 mov byte ptr es:[bx + 0x46e6], 0
06aa mov byte ptr es:[di + 0x48dc], al
06af and al, 0x80
06b1 add al, 0x70
06b3 mov byte ptr es:[di + 0x46e6], al
06b8 mov bx, word ptr [bp - 8]
06bb mov byte ptr [bx - 0x6718], al
06bf mov byte ptr es:[di + 0x44f0], 0xa
06c5 pop si
06c6 pop di
06c7 leave 
06c8 retf 
06c9 nop 
06ca mov ax, word ptr [bp - 4]
06cd sub ax, 6
06d0 je 0x5adc
06d2 dec ax
06d3 jne 0x5a7c
06d5 jmp 0x5b14
06d8 push 8
06da push word ptr [bp + 8]
06dd push word ptr [bp + 6]
06e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1763, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirR
06e5 add sp, 6
06e8 mov si, ax
06ea or si, si
06ec je 0x5b0a
06ee dec si
06ef push si
06f0 push word ptr [bp + 8]
06f3 push word ptr [bp + 6]
06f6 nop 
06f7 push cs
06f8 call 0x6850 ; _TryMoveDirR
06fb add sp, 6
06fe or ax, ax
0700 jne 0x5b25
0702 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1797, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0707 push ax
0708 push word ptr [bp + 8]
070b push word ptr [bp + 6]
070e nop 
070f push cs
0710 call 0x6850 ; _TryMoveDirR
0713 add sp, 6
0716 or ax, ax
0718 jne 0x5b25
071a mov es, word ptr [0xc384]
071e mov bx, word ptr es:[0x9b6a]
0723 mov es, word ptr [0xc386]
0727 mov al, byte ptr es:[bx + 0x46e6]
072c mov bx, word ptr [bp - 8]
072f mov byte ptr [bx - 0x6718], al
0733 pop si
0734 pop di
0735 leave 
0736 retf 
0737 nop 
0738 cmp word ptr [0xce80], 3 ; _MePlane
073d jne 0x5af4
073f push word ptr [bp + 0xa]
0742 push word ptr [bp + 8]
0745 push word ptr [bp + 6]
0748 nop 
0749 push cs
074a call 0x5c16 ; _StayInR
074d jmp 0x5b22
074f nop 
0750 push 8
0752 push word ptr [bp + 8]
0755 push word ptr [bp + 6]
0758 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1883, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirR
075d add sp, 6
0760 mov si, ax
0762 or si, si
0764 jne 0x5a92
0766 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1897, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
076b mov si, ax
076d jmp 0x5a93
0770 push word ptr [bp + 0xa]
0773 push word ptr [bp + 8]
0776 push word ptr [bp + 6]
0779 nop 
077a push cs
077b call 0x5b2a ; _RaidInR
077e add sp, 6
0781 pop si
0782 pop di
0783 leave 
0784 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far FindInRList(int x, int y, int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far GetExitDirR(int x, int y, int limit);` — src/recovered/wf_RaidOutR-a39ba19d03.c
- `extern int far GetNewModeR(int mode);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near HealthR;` — src/recovered/DecEatR.c
- `extern int near HealthR;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near MeColor;` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand32(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand32(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far TryMoveDirR(int x, int y, int dir);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far TryMoveDirR(int x, int y, int dir);` — src/recovered/wf_RaidOutR-a39ba19d03.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetOutB', 'offset': 21002, 'source': None, 'size': 314}
- {'symbol': '_DoAntSimR', 'offset': 21316, 'source': 'src/recovered/wf_DoAntSimR-682e4ecadf.c', 'size': 95}
- {'symbol': '_RaidInR', 'offset': 23338, 'source': None, 'size': 235}
- {'symbol': '_StayInR', 'offset': 23574, 'source': None, 'size': 249}
