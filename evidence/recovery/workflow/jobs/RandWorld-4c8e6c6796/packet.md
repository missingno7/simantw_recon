# Recovery task _RandWorld

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 1493 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 0xa]
0009 push 0
000b push word ptr [bp + 6]
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetSRandSeed
0013 add sp, 4
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _InitSpider
001b push word ptr [bp + 0xe]
001e push word ptr [bp + 0xc]
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeMap
0026 add sp, 4
0029 mov ax, word ptr [bp + 8]
002c sar ax, 2
002f add word ptr [bp + 8], ax
0032 mov ax, si
0034 sar ax, 2
0037 add si, ax
0039 xor ax, ax
003b mov word ptr [bp - 4], ax
003e mov word ptr [bp - 2], ax
0041 mov di, ax
0043 mov word ptr [bp + 0xa], si
0046 mov cx, si
0048 mov <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
004b mov es, ax
004d xor si, si
004f mov word ptr [bp - 2], di
0052 mov al, 0x2e
0054 mov bx, di
0056 add bx, si
0058 mov byte ptr [bx + 0x48e8], al
005c mov byte ptr [bx + 0x58e8], al
0060 xor al, al
0062 mov byte ptr es:[bx + 0x3a4], al
0067 mov byte ptr es:[bx + 0x13a4], al
006c mov byte ptr [bx - 0x7718], al
0070 mov byte ptr [bx - 0x6718], al
0074 mov byte ptr [bx + 0x68e8], al
0078 mov byte ptr [bx + 0x78e8], al
007c inc si
007d cmp si, 0x40
0080 jl 0x5b02
0082 add di, 0x40
0085 cmp di, 0x1000
0089 jl 0x5afd
008b xor si, si
008d mov di, word ptr [bp - 2]
0090 mov es, word ptr [0xc5b4]
0094 cmp word ptr es:[0x9b6e], 0
009a jne 0x5b60
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
00a1 add al, 0x1c
00a3 mov byte ptr [si + 0x48e8], al
00a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 170, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
00ac add al, 0x1c
00ae jmp 0x5b92
00b0 cmp word ptr [bp + 0xe], 3
00b4 jle 0x5b78
00b6 push 2
00b8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 187, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00bd add sp, 2
00c0 add al, 0x1c
00c2 mov byte ptr [si + 0x48e8], al
00c6 jmp 0x5b7d
00c8 mov byte ptr [si + 0x48e8], 0x1e
00cd cmp word ptr [bp + 0xe], 3
00d1 jle 0x5b90
00d3 push 2
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 216, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00da add sp, 2
00dd jmp 0x5b5c
00df nop 
00e0 mov al, 0x1e
00e2 mov byte ptr [si + 0x58e8], al
00e6 mov al, 0xff
00e8 mov es, word ptr [0xc5b6]
00ec mov byte ptr es:[si + 0x3a4], al
00f1 mov byte ptr es:[si + 0x13a4], al
00f6 add si, 0x40
00f9 cmp si, 0x1000
00fd jl 0x5b40
00ff xor di, di
0101 mov cx, word ptr [bp + 0xa]
0104 mov <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0107 mov ds, ax
0109 xor si, si
010b mov word ptr [bp - 2], di
010e xor al, al
0110 mov bx, di
0112 add bx, si
0114 mov byte ptr [bx + 0x5ad2], al
0118 mov byte ptr [bx + 0x52d2], al
011c mov byte ptr [bx + 0x62d2], al
0120 mov byte ptr [bx + 0x6ad2], al
0124 mov byte ptr [bx + 0x72d2], al
0128 mov byte ptr [bx + 0x7ad2], al
012c inc si
012d cmp si, 0x20
0130 jl 0x5bbe
0132 add di, 0x20
0135 cmp di, 0x800
0139 jl 0x5bb9
013b push ss
013c pop ds
013d mov word ptr [bp - 6], 0
0142 push 6
0144 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0149 add sp, 2
014c add ax, 7
014f mov word ptr [bp - 8], ax
0152 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 341, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
0157 sub ax, 0xf
015a neg ax
015c mov word ptr [bp - 0xa], ax
015f mov di, word ptr [bp + 8]
0162 or di, di
0164 jg 0x5c19
0166 jmp 0x5c9f
0169 dec di
016a push 0x80
016d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SGRand
0172 add sp, 2
0175 mov word ptr [bp - 2], ax
0178 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 379, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
017d mov si, ax
017f mov bx, word ptr [bp - 2]
0182 shl bx, 6
0185 add bx, si
0187 mov word ptr [bp - 0xc], bx
018a cmp byte ptr [bx + 0x28e8], 0x50
018f jae 0x5c98
0191 cmp byte ptr [bx + 0x68e8], 0
0196 je 0x5c54
0198 inc word ptr [bp - 6]
019b cmp word ptr [bp - 6], 0x32
019f jge 0x5c98
01a1 inc di
01a2 jmp 0x5c98
01a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
01a9 mov word ptr [bp - 4], ax
01ac cmp ax, word ptr [bp - 8]
01af jge 0x5c6a
01b1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 436, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01b6 add al, 0x10
01b8 jmp 0x5c91
01ba cmp word ptr [bp - 0xa], ax
01bd jle 0x5c78
01bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 450, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01c4 add al, 0x30
01c6 jmp 0x5c91
01c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 459, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
01cd or ax, ax
01cf je 0x5c8a
01d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01d6 add al, 0x20
01d8 jmp 0x5c91
01da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 477, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01df add al, 0x40
01e1 mov bx, word ptr [bp - 0xc]
01e4 mov byte ptr [bx + 0x68e8], al
01e8 or di, di
01ea jle 0x5c9f
01ec jmp 0x5c19
01ef mov word ptr [bp - 6], 0
01f4 push 6
01f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 505, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
01fb add sp, 2
01fe add ax, 7
0201 mov word ptr [bp - 8], ax
0204 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 519, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
0209 sub ax, 0xf
020c neg ax
020e mov word ptr [bp - 0xa], ax
0211 mov di, word ptr [bp + 0xa]
0214 or di, di
0216 jg 0x5ccb
0218 jmp 0x5d57
021b dec di
021c push 0x80
021f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 546, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SGRand
0224 add sp, 2
0227 sub ax, 0x7f
022a neg ax
022c mov word ptr [bp - 2], ax
022f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 562, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand64
0234 mov si, ax
0236 mov bx, word ptr [bp - 2]
0239 shl bx, 6
023c add bx, si
023e mov word ptr [bp - 0xc], bx
0241 cmp byte ptr [bx + 0x28e8], 0x50
0246 jae 0x5d50
0248 cmp byte ptr [bx + 0x68e8], 0
024d je 0x5d0c
024f inc word ptr [bp - 6]
0252 cmp word ptr [bp - 6], 0x32
0256 jge 0x5d50
0258 inc di
0259 jmp 0x5d50
025b nop 
025c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 607, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
0261 mov word ptr [bp - 4], ax
0264 cmp ax, word ptr [bp - 8]
0267 jge 0x5d22
0269 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 620, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
026e sub al, 0x70
0270 jmp 0x5d49
0272 cmp word ptr [bp - 0xa], ax
0275 jle 0x5d30
0277 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 634, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
027c sub al, 0x50
027e jmp 0x5d49
0280 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 643, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
0285 or ax, ax
0287 je 0x5d42
0289 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 652, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
028e sub al, 0x60
0290 jmp 0x5d49
0292 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 661, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0297 sub al, 0x40
0299 mov bx, word ptr [bp - 0xc]
029c mov byte ptr [bx + 0x68e8], al
02a0 or di, di
02a2 jle 0x5d57
02a4 jmp 0x5ccb
02a7 xor ax, ax
02a9 mov es, word ptr [0xc5b8]
02ad mov cx, 0x20
02b0 mov di, 0x8312
02b3 rep stosw word ptr es:[di], ax
02b5 mov es, word ptr [0xc5ba]
02b9 mov cx, 0x20
02bc mov di, 0x82d2
02bf rep stosw word ptr es:[di], ax
02c1 mov es, word ptr [0xc5bc]
02c5 cmp word ptr es:[0x80b4], 2
02cb jne 0x5d83
02cd cmp word ptr [bp + 8], 1
02d1 jl 0x5d8d
02d3 push 0x20
02d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 728, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleB
02da add sp, 2
02dd mov si, word ptr [bp + 0xa]
02e0 cmp si, 1
02e3 jl 0x5d9f
02e5 push 0x20
02e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 746, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleR
02ec add sp, 2
02ef mov es, word ptr [0xc5be]
02f3 sub ax, ax
02f5 mov word ptr es:[0x9de4], ax
02f9 mov word ptr es:[0x9de2], ax
02fd mov es, word ptr [0xc5c0]
0301 mov word ptr es:[0x9dde], ax
0305 mov word ptr es:[0x9ddc], ax
0309 mov es, word ptr [0xc5c2]
030d mov word ptr es:[0x811c], ax
0311 mov word ptr es:[0x811a], ax
0315 mov es, word ptr [0xc5c4]
0319 mov word ptr es:[0x8106], ax
031d mov word ptr es:[0x8104], ax
0321 mov es, word ptr [0xc5c6]
0325 mov word ptr es:[0x72c8], ax
0329 mov es, word ptr [0xc5c8]
032d mov word ptr es:[0x7a56], ax
0331 mov es, word ptr [0xc5ca]
0335 mov word ptr es:[0x9fd2], ax
0339 mov es, word ptr [0xc5cc]
033d mov word ptr es:[0x9fba], ax
0341 mov es, word ptr [0xc5ce]
0345 mov word ptr es:[0x7c90], ax
0349 mov es, word ptr [0xc5d0]
034d mov word ptr es:[0x7c48], ax
0351 mov es, word ptr [0xc5d2]
0355 mov word ptr es:[0x99d8], 0x40
035c cmp word ptr [bp + 8], 1
0360 jle 0x5e21
0362 mov ax, word ptr [bp + 8]
0365 shl ax, 4
0368 push ax
0369 nop 
036a push cs
036b call 0x62de ; _DigOutBNest
036e add sp, 2
0371 cmp si, 1
0374 jle 0x5e34
0376 mov ax, si
0378 shl ax, 4
037b push ax
037c nop 
037d push cs
037e call 0x63b8 ; _DigOutRNest
0381 add sp, 2
0384 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 903, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _BuildAntListA
0389 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 908, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearListB
038e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 913, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearListR
0393 xor ax, ax
0395 mov es, word ptr [0xc5d4]
0399 mov word ptr es:[0x78e8], ax
039d mov es, word ptr [0xc5d6]
03a1 mov word ptr es:[0x79dc], ax
03a5 mov cx, 0xffff
03a8 mov es, word ptr [0xc5d8]
03ac mov word ptr es:[0x8362], cx
03b1 mov word ptr es:[0x8364], cx
03b6 mov es, word ptr [0xc5da]
03ba mov word ptr es:[0x8366], cx
03bf mov word ptr es:[0x8368], cx
03c4 cmp si, ax
03c6 jg 0x5e7b
03c8 jmp 0x5f9c
03cb mov si, 0x20
03ce mov di, 1
03d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 980, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
03d6 add ax, 7
03d9 mov word ptr [bp - 2], ax
03dc cmp ax, di
03de jle 0x5eca
03e0 mov word ptr [bp - 4], di
03e3 push word ptr [bp - 4]
03e6 push si
03e7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1002, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
03ec add sp, 4
03ef push 3
03f1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1012, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
03f6 add sp, 2
03f9 mov di, ax
03fb dec di
03fc mov ax, di
03fe add ax, si
0400 cmp ax, 8
0403 jl 0x5ebc
0405 cmp ax, 0x38
0408 jg 0x5ebc
040a mov si, ax
040c mov ax, word ptr [bp - 2]
040f inc word ptr [bp - 4]
0412 cmp word ptr [bp - 4], ax
0415 jl 0x5e93
0417 mov di, word ptr [bp - 4]
041a mov word ptr [bp - 2], 2
041f push di
0420 push si
0421 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1060, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
0426 add sp, 4
0429 inc si
042a inc di
042b dec word ptr [bp - 2]
042e jne 0x5ecf
0430 push di
0431 push si
0432 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1077, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
0437 add sp, 4
043a mov es, word ptr [0xc5da]
043e mov word ptr es:[0x8366], si
0443 mov word ptr es:[0x8368], di
0448 push di
0449 lea ax, [si + 2]
044c push ax
044d mov si, ax
044f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
0454 add sp, 4
0457 mov es, word ptr [0xc5dc]
045b mov al, byte ptr es:[0xe]
045f cwde 
0460 mov cx, di
0462 add di, ax
0464 push di
0465 mov es, word ptr [0xc5de]
0469 mov al, byte ptr es:[6]
046d cwde 
046e mov dx, si
0470 add si, ax
0472 push si
0473 mov si, cx
0475 mov di, dx
0477 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
047c add sp, 4
047f mov es, word ptr [0xc5dc]
0483 mov al, byte ptr es:[0xe]
0487 cwde 
0488 shl ax, 1
048a mov cx, si
048c add si, ax
048e push si
048f mov es, word ptr [0xc5de]
0493 mov al, byte ptr es:[6]
0497 cwde 
0498 shl ax, 1
049a mov dx, di
049c add di, ax
049e push di
049f mov si, cx
04a1 mov di, dx
04a3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigTileR
04a8 add sp, 4
04ab push 0
04ad push 9
04af push 0xe2
04b2 push si
04b3 push di
04b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
04b9 add sp, 0xa
04bc push 0
04be push 9
04c0 push 0xea
04c3 mov es, word ptr [0xc5dc]
04c7 mov al, byte ptr es:[0xe]
04cb cwde 
04cc add si, ax
04ce push si
04cf mov es, word ptr [0xc5de]
04d3 mov al, byte ptr es:[6]
04d7 cwde 
04d8 add di, ax
04da push di
04db lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1246, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
04e0 add sp, 0xa
04e3 mov es, word ptr [0xc5d6]
04e7 inc word ptr es:[0x79dc]
04ec cmp word ptr [bp + 8], 0
04f0 jle 0x5fa7
04f2 nop 
04f3 push cs
04f4 call 0x65ce ; _PlaceBlackQueen
04f7 nop 
04f8 push cs
04f9 call 0x6492 ; _InitYelloAnt
04fc xor ax, ax
04fe mov es, word ptr [0xc5e0]
0502 mov word ptr es:[0x9ea4], ax
0506 mov es, word ptr [0xc5e2]
050a mov word ptr es:[0x72de], ax
050e mov es, word ptr [0xc5e4]
0512 mov word ptr es:[0x9e84], ax
0516 mov es, word ptr [0xc5bc]
051a cmp word ptr es:[0x80b4], 3
0520 je 0x5fdd
0522 push ax
0523 push -1
0525 nop 
0526 push cs
0527 call 0x6a58 ; _AddFood
052a add sp, 4
052d mov ax, 0x64
0530 mov word ptr [0xac86], ax ; _HealthB
0533 mov word ptr [0xac88], ax ; _HealthR
0536 mov es, word ptr [0xc5e6]
053a sub ax, ax
053c mov word ptr es:[0x9ea0], ax
0540 mov word ptr es:[0x9e9e], ax
0544 mov es, word ptr [0xc5e8]
0548 mov word ptr es:[0x79e4], ax
054c mov es, word ptr [0xc5ea]
0550 mov word ptr es:[0xa0e4], ax
0554 mov es, word ptr [0xc5ec]
0558 mov word ptr es:[0x75fc], ax
055c push ax
055d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1376, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ClearHistory
0562 add sp, 2
0565 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1384, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _CountAnts
056a mov es, word ptr [0xc5ee]
056e push word ptr es:[0x9b6c]
0573 mov es, word ptr [0xc5f0]
0577 push word ptr es:[0x7292]
057c push 0
057e push 0
0580 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1411, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvalEuMap
0585 add sp, 8
0588 mov ax, 0x40
058b mov es, word ptr [0xc5f2]
058f mov word ptr es:[0x7d2e], ax
0593 mov es, word ptr [0xc5f4]
0597 mov word ptr es:[0x9f2c], ax
059b mov ax, 0x20
059e mov es, word ptr [0xc5f2]
05a2 mov word ptr es:[0x7d30], ax
05a6 mov es, word ptr [0xc5f4]
05aa mov word ptr es:[0x9f2e], ax
05ae mov es, word ptr [0xc5f6]
05b2 mov word ptr es:[0x9fb2], ax
05b6 mov es, word ptr [0xc5f8]
05ba mov word ptr es:[0x72f6], ax
05be mov ax, 1
05c1 mov es, word ptr [0xc5f6]
05c5 mov word ptr es:[0x9fb4], ax
05c9 mov es, word ptr [0xc5f8]
05cd mov word ptr es:[0x72f8], ax
05d1 pop si
05d2 pop di
05d3 leave 
05d4 retf 
```

## Known declaration examples

- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far CountAnts(void);` — src/recovered/FullCount.c
- `extern void far DigTileR(int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int near HealthB;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int near HealthR;` — src/recovered/DecEatR.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PillFoodTile', 'offset': 23042, 'source': None, 'size': 110}
- {'symbol': '_InitSimVars', 'offset': 23152, 'source': 'src/recovered/InitSimVars.c', 'size': 63}
- {'symbol': '_RandYard', 'offset': 24710, 'source': None, 'size': 476}
- {'symbol': '_GenerateTutorial', 'offset': 25186, 'source': None, 'size': 124}
