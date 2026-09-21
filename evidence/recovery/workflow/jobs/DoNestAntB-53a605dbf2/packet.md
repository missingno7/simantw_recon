# Recovery task _DoNestAntB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 1909 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov cx, word ptr [bp + 0xa]
0009 mov ax, cx
000b and ax, 0x78
000e sar ax, 3
0011 mov word ptr [bp - 2], ax
0014 test cl, 0x80
0017 je 0x2dca
0019 jmp 0x335c
001c mov bx, 0x9b6a
001f mov es, word ptr [0xc350]
0023 mov word ptr [bp - 8], bx
0026 mov word ptr [bp - 6], es
0029 mov bx, word ptr es:[bx]
002c mov es, word ptr [0xc352]
0030 mov al, byte ptr es:[bx + 0x3b22]
0035 sub ah, ah
0037 mov si, ax
0039 mov bx, si
003b shl bx, 1
003d mov es, word ptr [0xc354]
0041 inc word ptr es:[bx + 0x786a]
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand256
004b or ax, ax
004d jne 0x2e3e
004f cmp si, 9
0052 je 0x2e3e
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
0059 cmp ax, word ptr [0xac86] ; _HealthB
005d jle 0x2e3e
005f xor al, al
0061 les bx, ptr [bp - 8]
0064 mov bx, word ptr es:[bx]
0067 mov es, word ptr [0xc352]
006b mov byte ptr es:[bx + 0x3d18], al
0070 mov si, word ptr [bp + 6]
0073 shl si, 6
0076 mov bx, word ptr [bp + 8]
0079 mov byte ptr [bx + si - 0x7718], al
007d mov es, word ptr [0xc356]
0081 add word ptr es:[0x9b26], 1
0087 adc word ptr es:[0x9b28], 0
008d jmp 0x351f
0090 mov ax, si
0092 cmp ax, 0x11
0095 ja 0x2e72
0097 shl ax, 1
0099 xchg bx, ax
009a jmp word ptr cs:[bx + 0x2e4e]
009f nop 
00a0 dw offset 0x2f22
00a2 dw offset 0x2f8a
00a4 dw offset 0x2fcf
00a6 dw offset 0x2fa2
00a8 dw offset 0x2fb4
00aa dw offset 0x2fcf
00ac dw offset 0x2fc8
00ae dw offset 0x2fcf
00b0 dw offset 0x3064
00b2 dw offset 0x3076
00b4 dw offset 0x308a
00b6 dw offset 0x2fcf
00b8 dw offset 0x2fcf
00ba dw offset 0x3098
00bc dw offset 0x31ac
00be dw offset 0x2fcf
00c0 dw offset 0x2fcf
00c2 dw offset 0x32b6
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
00c9 or ax, ax
00cb jne 0x2e95
00cd push word ptr [bp - 2]
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
00d5 add sp, 2
00d8 les bx, ptr [bp - 8]
00db mov bx, word ptr es:[bx]
00de mov es, word ptr [0xc352]
00e2 mov byte ptr es:[bx + 0x3b22], al
00e7 mov di, word ptr [bp + 6]
00ea mov bx, di
00ec shl bx, 6
00ef add bx, word ptr [bp + 8]
00f2 mov word ptr [bp - 0xa], bx
00f5 mov al, byte ptr [bx - 0x7718]
00f9 sub ah, ah
00fb mov si, ax
00fd push si
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 257, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0103 add sp, 2
0106 dec ax
0107 jne 0x2ec1
0109 cmp word ptr [0xce98], 0 ; _MeColor
010e je 0x2ec1
0110 jmp 0x2f74
0113 cmp si, 0x87
0117 jg 0x2eca
0119 jmp 0x302f
011c cmp si, 0xe8
0120 jl 0x2ed3
0122 jmp 0x302f
0125 push si
0126 push word ptr [bp + 8]
0129 push di
012a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 301, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
012f add sp, 6
0132 mov word ptr [bp - 2], ax
0135 or ax, ax
0137 jge 0x2eea
0139 jmp 0x302f
013c push word ptr [bp + 0xa]
013f push si
0140 call 0x26f4 ; _GetWinner
0143 add sp, 4
0146 mov es, word ptr [0xc352]
014a mov bx, word ptr [bp - 2]
014d mov byte ptr es:[bx + 0x3f0e], al
0152 and al, 0x80
0154 add al, 0x70
0156 mov byte ptr es:[bx + 0x3d18], al
015b mov si, word ptr [bp - 0xa]
015e mov byte ptr [si - 0x7718], al
0162 mov byte ptr es:[bx + 0x3b22], 0xa
0168 mov word ptr [bp - 4], 1
016d mov si, word ptr [bp - 4]
0170 jmp 0x3031
0173 nop 
0174 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 375, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
0179 or ax, ax
017b jne 0x2f45
017d push word ptr [bp - 2]
0180 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 387, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
0185 add sp, 2
0188 les bx, ptr [bp - 8]
018b mov bx, word ptr es:[bx]
018e mov es, word ptr [0xc352]
0192 mov byte ptr es:[bx + 0x3b22], al
0197 mov di, word ptr [bp + 6]
019a mov bx, di
019c shl bx, 6
019f add bx, word ptr [bp + 8]
01a2 mov word ptr [bp - 0xa], bx
01a5 mov al, byte ptr [bx - 0x7718]
01a9 sub ah, ah
01ab mov si, ax
01ad push si
01ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 433, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
01b3 add sp, 2
01b6 dec ax
01b7 je 0x2f6a
01b9 jmp 0x2ec1
01bc cmp word ptr [0xce98], 0 ; _MeColor
01c1 jne 0x2f74
01c3 jmp 0x2ec1
01c6 les bx, ptr [bp - 8]
01c9 push word ptr es:[bx]
01cc push 2
01ce nop 
01cf push cs
01d0 call 0x823e ; _YellowFight
01d3 add sp, 4
01d6 mov si, 1
01d9 jmp 0x3031
01dc push word ptr [bp - 2]
01df push word ptr [bp + 0xa]
01e2 push word ptr [bp + 8]
01e5 push word ptr [bp + 6]
01e8 nop 
01e9 push cs
01ea call 0x44a8 ; _DoNestingB
01ed add sp, 8
01f0 jmp 0x351f
01f3 nop 
01f4 push word ptr [bp + 0xa]
01f7 push word ptr [bp + 8]
01fa push word ptr [bp + 6]
01fd nop 
01fe push cs
01ff call 0x492a ; _DoFoodInB
0202 jmp 0x351c
0205 nop 
0206 push word ptr [bp - 2]
0209 push word ptr [bp + 0xa]
020c push word ptr [bp + 8]
020f push word ptr [bp + 6]
0212 nop 
0213 push cs
0214 call 0x4bd0 ; _DoDigInB
0217 jmp 0x2f9b
0219 nop 
021a cmp word ptr [0xce80], 2 ; _MePlane
021f je 0x2fe0
0221 push word ptr [bp + 0xa]
0224 push word ptr [bp + 8]
0227 push word ptr [bp + 6]
022a nop 
022b push cs
022c call 0x4eb0 ; _DoDigOutB
022f jmp 0x351c
0232 mov di, word ptr [bp + 6]
0235 mov bx, di
0237 shl bx, 6
023a add bx, word ptr [bp + 8]
023d mov word ptr [bp - 0xa], bx
0240 mov al, byte ptr [bx - 0x7718]
0244 sub ah, ah
0246 mov si, ax
0248 push si
0249 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 588, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
024e add sp, 2
0251 dec ax
0252 jne 0x300c
0254 cmp word ptr [0xce98], 0 ; _MeColor
0259 je 0x300c
025b jmp 0x2f74
025e cmp si, 0x87
0262 jle 0x302f
0264 cmp si, 0xe8
0268 jge 0x302f
026a push si
026b push word ptr [bp + 8]
026e push di
026f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 626, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0274 add sp, 6
0277 mov word ptr [bp - 2], ax
027a or ax, ax
027c jl 0x302f
027e jmp 0x2eea
0281 xor si, si
0283 dec si
0284 jne 0x3037
0286 jmp 0x351f
0289 mov al, byte ptr [bp + 0xa]
028c and ax, 7
028f push ax
0290 push word ptr [bp + 8]
0293 push di
0294 nop 
0295 push cs
0296 call 0x439e ; _TryMoveDirB
0299 add sp, 6
029c or ax, ax
029e je 0x3051
02a0 jmp 0x351f
02a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 678, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
02a8 push ax
02a9 push word ptr [bp + 8]
02ac push di
02ad nop 
02ae push cs
02af call 0x439e ; _TryMoveDirB
02b2 jmp 0x351c
02b5 nop 
02b6 push word ptr [bp + 8]
02b9 push word ptr [bp + 6]
02bc nop 
02bd push cs
02be call 0x3ca0 ; _SimEggB
02c1 add sp, 4
02c4 jmp 0x351f
02c7 nop 
02c8 push word ptr [bp + 0xa]
02cb push word ptr [bp - 2]
02ce push word ptr [bp + 8]
02d1 push word ptr [bp + 6]
02d4 nop 
02d5 push cs
02d6 call 0x3dc2 ; _SimQueenB
02d9 jmp 0x2f9b
02dc push word ptr [bp + 8]
02df push word ptr [bp + 6]
02e2 nop 
02e3 push cs
02e4 call 0x3a54 ; _DoNestFightB
02e7 jmp 0x306f
02e9 nop 
02ea mov bx, word ptr [bp + 6]
02ed shl bx, 6
02f0 add bx, word ptr [bp + 8]
02f3 mov word ptr [bp - 0xa], bx
02f6 mov si, word ptr [bx - 0x7718]
02fa and si, 0xff
02fe push si
02ff lcall <resolved loader operand; see bindings> ; [{'operand_offset': 770, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0304 add sp, 2
0307 dec ax
0308 jne 0x30d4
030a cmp word ptr [0xce98], 0 ; _MeColor
030f je 0x30d4
0311 les bx, ptr [bp - 8]
0314 push word ptr es:[bx]
0317 push 2
0319 nop 
031a push cs
031b call 0x823e ; _YellowFight
031e add sp, 4
0321 mov si, 1
0324 jmp 0x312a
0326 cmp si, 0x87
032a jle 0x3128
032c cmp si, 0xe8
0330 jge 0x3128
0332 push si
0333 push word ptr [bp + 8]
0336 push word ptr [bp + 6]
0339 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 828, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
033e add sp, 6
0341 mov di, ax
0343 or di, di
0345 jl 0x3128
0347 push word ptr [bp + 0xa]
034a push si
034b call 0x26f4 ; _GetWinner
034e add sp, 4
0351 mov es, word ptr [0xc352]
0355 mov byte ptr es:[di + 0x3f0e], al
035a and al, 0x80
035c add al, 0x70
035e mov byte ptr es:[di + 0x3d18], al
0363 mov bx, word ptr [bp - 0xa]
0366 mov byte ptr [bx - 0x7718], al
036a mov byte ptr es:[di + 0x3b22], 0xa
0370 mov word ptr [bp - 2], 1
0375 mov si, word ptr [bp - 2]
0378 jmp 0x312a
037a xor si, si
037c dec si
037d jne 0x3130
037f jmp 0x351f
0382 les bx, ptr [bp - 8]
0385 mov bx, word ptr es:[bx]
0388 mov es, word ptr [0xc352]
038c mov al, byte ptr es:[bx + 0x3d18]
0391 mov bx, word ptr [bp - 0xa]
0394 mov byte ptr [bx - 0x7718], al
0398 push 0x14
039a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 925, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
039f add sp, 2
03a2 or ax, ax
03a4 jne 0x318c
03a6 les bx, ptr [bp - 8]
03a9 mov si, word ptr es:[bx]
03ac mov es, word ptr [0xc352]
03b0 mov al, byte ptr es:[si + 0x3d18]
03b5 sub ah, ah
03b7 mov di, ax
03b9 mov si, ax
03bb and si, 0x78
03be sar si, 3
03c1 push di
03c2 push si
03c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 966, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
03c8 add sp, 4
03cb les bx, ptr [bp - 8]
03ce mov bx, word ptr es:[bx]
03d1 mov es, word ptr [0xc352]
03d5 mov byte ptr es:[bx + 0x3b22], al
03da jmp 0x351f
03dd nop 
03de mov es, word ptr [0xc358]
03e2 cmp word ptr es:[0x85fc], 1
03e8 je 0x319b
03ea jmp 0x351f
03ed push 2
03ef push word ptr [bp + 8]
03f2 push word ptr [bp + 6]
03f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1016, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _RestBalloons
03fa jmp 0x351c
03fd nop 
03fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1025, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
0403 or ax, ax
0405 jne 0x31cf
0407 push word ptr [bp - 2]
040a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1037, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
040f add sp, 2
0412 les bx, ptr [bp - 8]
0415 mov bx, word ptr es:[bx]
0418 mov es, word ptr [0xc352]
041c mov byte ptr es:[bx + 0x3b22], al
0421 mov di, word ptr [bp + 6]
0424 mov bx, di
0426 shl bx, 6
0429 add bx, word ptr [bp + 8]
042c mov word ptr [bp - 0xa], bx
042f mov al, byte ptr [bx - 0x7718]
0433 sub ah, ah
0435 mov si, ax
0437 push si
0438 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1083, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
043d add sp, 2
0440 dec ax
0441 jne 0x320e
0443 cmp word ptr [0xce98], 0 ; _MeColor
0448 je 0x320e
044a les bx, ptr [bp - 8]
044d push word ptr es:[bx]
0450 push 2
0452 nop 
0453 push cs
0454 call 0x823e ; _YellowFight
0457 add sp, 4
045a mov si, 1
045d jmp 0x3266
045f nop 
0460 cmp si, 0x87
0464 jle 0x3264
0466 cmp si, 0xe8
046a jge 0x3264
046c push si
046d push word ptr [bp + 8]
0470 push di
0471 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0476 add sp, 6
0479 mov word ptr [bp - 2], ax
047c or ax, ax
047e jl 0x3264
0480 push word ptr [bp + 0xa]
0483 push si
0484 call 0x26f4 ; _GetWinner
0487 add sp, 4
048a mov es, word ptr [0xc352]
048e mov bx, word ptr [bp - 2]
0491 mov byte ptr es:[bx + 0x3f0e], al
0496 and al, 0x80
0498 add al, 0x70
049a mov byte ptr es:[bx + 0x3d18], al
049f mov si, word ptr [bp - 0xa]
04a2 mov byte ptr [si - 0x7718], al
04a6 mov byte ptr es:[bx + 0x3b22], 0xa
04ac mov word ptr [bp - 4], 1
04b1 mov si, word ptr [bp - 4]
04b4 jmp 0x3266
04b6 xor si, si
04b8 dec si
04b9 je 0x3292
04bb mov al, byte ptr [bp + 0xa]
04be and ax, 7
04c1 push ax
04c2 push word ptr [bp + 8]
04c5 push di
04c6 nop 
04c7 push cs
04c8 call 0x439e ; _TryMoveDirB
04cb add sp, 6
04ce or ax, ax
04d0 jne 0x3292
04d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1237, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
04d7 push ax
04d8 push word ptr [bp + 8]
04db push di
04dc nop 
04dd push cs
04de call 0x439e ; _TryMoveDirB
04e1 add sp, 6
04e4 mov es, word ptr [0xc35a]
04e8 cmp word ptr es:[0x7c44], 0x64
04ee jg 0x32a1
04f0 jmp 0x351f
04f3 les bx, ptr [bp - 8]
04f6 mov bx, word ptr es:[bx]
04f9 mov es, word ptr [0xc352]
04fd mov byte ptr es:[bx + 0x3b22], 0xf
0503 pop si
0504 pop di
0505 leave 
0506 retf 
0507 nop 
0508 mov si, word ptr [bp + 0xa]
050b mov di, word ptr [bp + 6]
050e mov bx, di
0510 shl bx, 6
0513 add bx, word ptr [bp + 8]
0516 mov word ptr [bp - 0xa], bx
0519 cmp byte ptr [bx + 0x48e8], 0x14
051e jae 0x32e2
0520 mov ax, si
0522 and ax, 0x78
0525 sar ax, 3
0528 push ax
0529 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1324, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
052e add sp, 2
0531 jmp 0x3179
0534 push 3
0536 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1337, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
053b add sp, 2
053e mov cx, si
0540 add al, cl
0542 dec al
0544 and ax, 7
0547 mov word ptr [bp - 2], ax
054a and cx, 0xf8
054e or ax, cx
0550 mov si, ax
0552 les bx, ptr [bp - 8]
0555 mov bx, word ptr es:[bx]
0558 mov es, word ptr [0xc352]
055c mov byte ptr es:[bx + 0x3d18], al
0561 mov bx, word ptr [bp - 0xa]
0564 mov byte ptr [bx - 0x7718], al
0568 push 0x64
056a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1389, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
056f add sp, 2
0572 or ax, ax
0574 je 0x3327
0576 jmp 0x351f
0579 xor al, al
057b mov bx, word ptr [bp - 0xa]
057e mov byte ptr [bx - 0x7718], al
0582 les bx, ptr [bp - 8]
0585 mov bx, word ptr es:[bx]
0588 mov es, word ptr [0xc352]
058c mov byte ptr es:[bx + 0x3d18], al
0591 mov ax, si
0593 test al, 0x80
0595 jne 0x3348
0597 jmp 0x2e2b
059a mov es, word ptr [0xc35c]
059e add word ptr es:[0x9fc6], 1
05a4 adc word ptr es:[0x9fc8], 0
05aa pop si
05ab pop di
05ac leave 
05ad retf 
05ae mov bx, 0x9b6a
05b1 mov es, word ptr [0xc350]
05b5 mov word ptr [bp - 8], bx
05b8 mov word ptr [bp - 6], es
05bb mov bx, word ptr es:[bx]
05be mov es, word ptr [0xc352]
05c2 mov si, word ptr es:[bx + 0x3b22]
05c7 and si, 0xff
05cb mov es, word ptr [0xc35e]
05cf mov bx, si
05d1 shl bx, 1
05d3 inc word ptr es:[bx + 0x7be4]
05d8 cmp cx, 0xef
05dc jle 0x338f
05de jmp 0x308a
05e1 mov word ptr [bp - 4], si
05e4 mov bx, word ptr [bp + 6]
05e7 shl bx, 6
05ea add bx, word ptr [bp + 8]
05ed mov word ptr [bp - 0xa], bx
05f0 mov si, word ptr [bx - 0x7718]
05f4 and si, 0xff
05f8 push si
05f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1532, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
05fe add sp, 2
0601 dec ax
0602 jne 0x33ca
0604 cmp word ptr [0xce98], 0 ; _MeColor
0609 jne 0x33ca
060b les bx, ptr [bp - 8]
060e push word ptr es:[bx]
0611 push 2
0613 nop 
0614 push cs
0615 call 0x823e ; _YellowFight
0618 jmp 0x306f
061b nop 
061c or si, si
061e jg 0x33d1
0620 jmp 0x34a0
0623 cmp si, 0x68
0626 jl 0x33d9
0628 jmp 0x34a0
062b push si
062c push word ptr [bp + 8]
062f push word ptr [bp + 6]
0632 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1589, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0637 add sp, 6
063a mov di, ax
063c or di, di
063e jge 0x33f1
0640 jmp 0x34a0
0643 cmp si, 0x5f
0646 jle 0x3418
0648 xor al, al
064a mov es, word ptr [0xc352]
064e mov byte ptr es:[di + 0x3d18], al
0653 mov cl, byte ptr es:[di + 0x392c]
0658 mov bl, byte ptr es:[di + 0x3736]
065d sub bh, bh
065f shl bx, 6
0662 sub ch, ch
0664 add bx, cx
0666 mov byte ptr [bx - 0x7718], al
066a cmp si, 8
066d jge 0x345a
066f les bx, ptr [bp - 8]
0672 mov bx, word ptr es:[bx]
0675 mov es, word ptr [0xc352]
0679 mov byte ptr es:[bx + 0x3b22], 3
067f or byte ptr es:[bx + 0x3d18], 8
0685 mov al, byte ptr es:[bx + 0x3d18]
068a mov bx, word ptr [bp - 0xa]
068d mov byte ptr [bx - 0x7718], al
0691 mov byte ptr es:[di + 0x3d18], 0
0697 mov es, word ptr [0xc360]
069b add word ptr es:[0x7c1e], 1
06a1 adc word ptr es:[0x7c20], 0
06a7 pop si
06a8 pop di
06a9 leave 
06aa retf 
06ab nop 
06ac push word ptr [bp + 0xa]
06af mov es, word ptr [0xc352]
06b3 mov al, byte ptr es:[di + 0x3d18]
06b8 sub ah, ah
06ba push ax
06bb call 0x26f4 ; _GetWinner
06be add sp, 4
06c1 mov si, ax
06c3 les bx, ptr [bp - 8]
06c6 mov bx, word ptr es:[bx]
06c9 mov es, word ptr [0xc352]
06cd mov byte ptr es:[bx + 0x3d18], 0
06d3 mov byte ptr es:[di + 0x3f0e], al
06d8 and al, 0x80
06da add al, 0x70
06dc mov byte ptr es:[di + 0x3d18], al
06e1 mov bx, word ptr [bp - 0xa]
06e4 mov byte ptr [bx - 0x7718], al
06e8 mov byte ptr es:[di + 0x3b22], 0xa
06ee pop si
06ef pop di
06f0 leave 
06f1 retf 
06f2 mov ax, word ptr [bp - 4]
06f5 sub ax, 7
06f8 je 0x350e
06fa push 8
06fc push word ptr [bp + 8]
06ff push word ptr [bp + 6]
0702 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1797, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirB
0707 add sp, 6
070a mov si, ax
070c or si, si
070e jne 0x34c8
0710 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1811, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0715 mov si, ax
0717 jmp 0x34c9
0719 nop 
071a dec si
071b push si
071c push word ptr [bp + 8]
071f push word ptr [bp + 6]
0722 nop 
0723 push cs
0724 call 0x439e ; _TryMoveDirB
0727 add sp, 6
072a or ax, ax
072c jne 0x351f
072e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1841, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0733 push ax
0734 push word ptr [bp + 8]
0737 push word ptr [bp + 6]
073a nop 
073b push cs
073c call 0x439e ; _TryMoveDirB
073f add sp, 6
0742 or ax, ax
0744 jne 0x351f
0746 les bx, ptr [bp - 8]
0749 mov bx, word ptr es:[bx]
074c mov es, word ptr [0xc352]
0750 mov al, byte ptr es:[bx + 0x3d18]
0755 mov bx, word ptr [bp - 0xa]
0758 mov byte ptr [bx - 0x7718], al
075c pop si
075d pop di
075e leave 
075f retf 
0760 push word ptr [bp + 0xa]
0763 push word ptr [bp + 8]
0766 push word ptr [bp + 6]
0769 nop 
076a push cs
076b call 0x3524 ; _RaidInB
076e add sp, 6
0771 pop si
0772 pop di
0773 leave 
0774 retf 
```

## Known declaration examples

- `extern void far DoDigOutB(int x, int y, int attacker);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int far GetExitDirB(int x, int y, int limit);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far GetNewModeB(int mode);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int near HealthB;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_5-2079c82816.c
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
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int far TryMoveDirB(int x, int y, int dir);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern void far YellowFight(int kind, int index);` — src/recovered/wf_DoRandR-fc777553ef.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsItFood', 'offset': 11546, 'source': 'src/recovered/wf_IsItFood-c02f58780a.c', 'size': 51}
- {'symbol': '_DoAntSimB', 'offset': 11598, 'source': 'src/recovered/wf_DoAntSimB-84a2084e1a.c', 'size': 95}
- {'symbol': '_RaidInB', 'offset': 13604, 'source': None, 'size': 235}
- {'symbol': '_RaidOutB', 'offset': 13840, 'source': 'src/recovered/wf_RaidOutB-794c50ee5a.c', 'size': 110}
