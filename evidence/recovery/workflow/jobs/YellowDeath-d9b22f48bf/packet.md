# Recovery task _YellowDeath

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 1904 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 nop 
0007 push cs
0008 call 0 ; _StopSimulation
000b mov es, word ptr [0xbf2a]
000f mov ax, word ptr es:[0x7c22]
0013 mov word ptr [bp - 6], ax
0016 cmp ax, 0xa
0019 jne 0x7768
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndLifeTransferMode
0020 jmp 0x7773
0022 cmp word ptr [bp - 6], 0xb
0026 jne 0x7773
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EndTargetMode
002d push 6
002f nop 
0030 push cs
0031 call 0x96b0 ; _SetSimCursor
0034 add sp, 2
0037 push 1
0039 nop 
003a push cs
003b call 0x60cc ; _SetDefaultWindPrompt
003e add sp, 2
0041 mov bx, 0x9fe8
0044 mov es, word ptr [0xbf0c]
0048 mov word ptr [bp - 0xa], bx
004b mov word ptr [bp - 8], es
004e cmp word ptr es:[bx], 0
0052 jne 0x77fe
0054 test byte ptr [0xcc84], 8 ; _MeType
0059 je 0x77fe
005b mov es, word ptr [0xbf42]
005f mov si, word ptr es:[0x85f6]
0064 mov word ptr es:[0x85f6], 0
006b push word ptr [0xce7e] ; _MeLocY
006f push word ptr [0xcd88] ; _MeLocX
0073 push word ptr [0xce7e] ; _MeLocY
0077 push word ptr [0xcd88] ; _MeLocX
007b push word ptr [0xce80] ; _MePlane
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DropMyObject
0084 add sp, 0xa
0087 or ax, ax
0089 jne 0x77f5
008b mov es, word ptr [0xbf46]
008f mov bl, byte ptr [0xcc84] ; _MeType
0093 and bx, 0x78
0096 sar bx, 3
0099 mov al, byte ptr es:[bx + 0x94]
009e cwde 
009f shl ax, 3
00a2 mov cl, byte ptr [0xcc84] ; _MeType
00a6 and cx, 0x80
00aa or ax, cx
00ac mov word ptr [0xcc84], ax ; _MeType
00af mov es, word ptr [0xbf42]
00b3 mov word ptr es:[0x85f6], si
00b8 mov si, word ptr [bp + 6]
00bb nop 
00bc push cs
00bd call 0xa764 ; _GotoMyAnt
00c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 195, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DoEditAndMapUpdateDraw
00c5 cmp si, 7
00c8 jl 0x7832
00ca cmp si, 0xa
00cd jge 0x7832
00cf push si
00d0 push word ptr [0xcc84] ; _MeType
00d4 push word ptr [0xcf50] ; _MeDir
00d8 push word ptr [0xce7e] ; _MeLocY
00dc push word ptr [0xcd88] ; _MeLocX
00e0 push word ptr [0xce80] ; _MePlane
00e4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 231, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _AnimYellowInsane
00e9 add sp, 0xc
00ec push 0
00ee nop 
00ef push cs
00f0 call 0x96b0 ; _SetSimCursor
00f3 add sp, 2
00f6 mov ax, si
00f8 cmp ax, 0xa
00fb jbe 0x7846
00fd jmp 0x7ac4
0100 shl ax, 1
0102 xchg bx, ax
0103 jmp word ptr cs:[bx + 0x784e]
0108 dw offset 0x7864
010a dw offset 0x78a4
010c dw offset 0x78fe
010e dw offset 0x7912
0110 dw offset 0x794e
0112 dw offset 0x7970
0114 dw offset 0x799e
0116 dw offset 0x79d0
0118 dw offset 0x7a02
011a dw offset 0x7a48
011c dw offset 0x7a7a
011e push 0x7e
0120 push 5
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0127 add sp, 2
012a add ax, 0x4e27
012d push ax
012e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0133 add sp, 4
0136 mov es, word ptr [0xbf48]
013a cmp word ptr es:[0x9e7c], 1
0140 sbb di, di
0142 and di, 2
0145 add di, 0x272e
0149 mov es, word ptr [0xbf42]
014d cmp word ptr es:[0x85f8], 0
0153 jne 0x789e
0155 jmp 0x7ac4
0158 push 1
015a push di
015b jmp 0x7ab9
015e mov es, word ptr [0xbf42]
0162 cmp word ptr es:[0x85f8], 0
0168 je 0x78b5
016a nop 
016b push cs
016c call 0x673a ; _SpiderDialog
016f mov es, word ptr [0xbf4a]
0173 add word ptr es:[0x76a0], 1
0179 adc word ptr es:[0x76a2], 0
017f push 0x7e
0181 push 5
0183 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 390, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0188 add sp, 2
018b add ax, 0x4e27
018e push ax
018f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 402, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0194 add sp, 4
0197 push si
0198 push word ptr [0xcc84] ; _MeType
019c push word ptr [0xcf50] ; _MeDir
01a0 push word ptr [0xce7e] ; _MeLocY
01a4 push word ptr [0xcd88] ; _MeLocX
01a8 push word ptr [0xce80] ; _MePlane
01ac lcall <resolved loader operand; see bindings> ; [{'operand_offset': 431, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _AnimYellowFight
01b1 add sp, 0xc
01b4 jmp 0x7ac4
01b7 nop 
01b8 mov es, word ptr [0xbf42]
01bc cmp word ptr es:[0x85f8], 0
01c2 je 0x78b5
01c4 nop 
01c5 push cs
01c6 call 0x80a0 ; _LionDialog
01c9 jmp 0x78b5
01cb nop 
01cc push 0x7e
01ce push 0
01d0 push 1
01d2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 469, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
01d7 add sp, 6
01da mov es, word ptr [0xbf42]
01de cmp word ptr es:[0x85f8], 0
01e4 je 0x793b
01e6 push 1
01e8 push 0x272a
01eb push 0
01ed nop 
01ee push cs
01ef call 0x615a ; _PictStrnDialog
01f2 add sp, 6
01f5 mov es, word ptr [0xbf4c]
01f9 add word ptr es:[0x99e0], 1
01ff adc word ptr es:[0x99e2], 0
0205 jmp 0x7ac4
0208 push 0x7e
020a push 0
020c push 1
020e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 529, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0213 add sp, 6
0216 mov es, word ptr [0xbf42]
021a cmp word ptr es:[0x85f8], 0
0220 je 0x793b
0222 push 1
0224 push 0x272c
0227 jmp 0x7931
0229 nop 
022a push 0x7e
022c push 5
022e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 561, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0233 add sp, 2
0236 add ax, 0x4e27
0239 push ax
023a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 573, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
023f add sp, 4
0242 mov es, word ptr [0xbf42]
0246 cmp word ptr es:[0x85f8], 0
024c je 0x793b
024e push 1
0250 push 0x2732
0253 push 0x23c3
0256 jmp 0x7933
0258 push 0x7e
025a push 5
025c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 607, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0261 add sp, 2
0264 add ax, 0x4e27
0267 push ax
0268 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 619, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
026d add sp, 4
0270 mov es, word ptr [0xbf42]
0274 cmp word ptr es:[0x85f8], 0
027a jne 0x79c5
027c jmp 0x793b
027f push 1
0281 push 0x2734
0284 push 0x23c0
0287 jmp 0x7933
028a push 0x7e
028c push 5
028e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 657, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0293 add sp, 2
0296 add ax, 0x4e27
0299 push ax
029a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 669, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
029f add sp, 4
02a2 mov es, word ptr [0xbf42]
02a6 cmp word ptr es:[0x85f8], 0
02ac jne 0x79f7
02ae jmp 0x793b
02b1 push 1
02b3 push 0x2736
02b6 push 0x23be
02b9 jmp 0x7933
02bc push 0x7e
02be push 5
02c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 707, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
02c5 add sp, 2
02c8 add ax, 0x4e27
02cb push ax
02cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 719, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
02d1 add sp, 4
02d4 mov es, word ptr [0xbf42]
02d8 cmp word ptr es:[0x85f8], 0
02de je 0x7a36
02e0 push 1
02e2 push 0x2738
02e5 push 0x23c2
02e8 nop 
02e9 push cs
02ea call 0x615a ; _PictStrnDialog
02ed add sp, 6
02f0 mov es, word ptr [0xbf4e]
02f4 add word ptr es:[0x9b26], 1
02fa adc word ptr es:[0x9b28], 0
0300 jmp 0x7ac4
0302 push 0x7e
0304 push 5
0306 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 777, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
030b add sp, 2
030e add ax, 0x4e27
0311 push ax
0312 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 789, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0317 add sp, 4
031a mov es, word ptr [0xbf42]
031e cmp word ptr es:[0x85f8], 0
0324 jne 0x7a6f
0326 jmp 0x793b
0329 push 1
032b push 0x273a
032e push 0x23bf
0331 jmp 0x7933
0334 mov es, word ptr [0xbf4c]
0338 add word ptr es:[0x99e0], 1
033e adc word ptr es:[0x99e2], 0
0344 push 0xa
0346 push word ptr [0xcc84] ; _MeType
034a push word ptr [0xcf50] ; _MeDir
034e push word ptr [0xce7e] ; _MeLocY
0352 push word ptr [0xcd88] ; _MeLocX
0356 push word ptr [0xce80] ; _MePlane
035a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 861, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _AnimYellowFight
035f add sp, 0xc
0362 mov es, word ptr [0xbf42]
0366 cmp word ptr es:[0x85f8], 0
036c je 0x7ac4
036e push 1
0370 push 0x273d
0373 push 0x23c4
0376 nop 
0377 push cs
0378 call 0x615a ; _PictStrnDialog
037b add sp, 6
037e cmp si, 1
0381 jl 0x7adb
0383 cmp si, 2
0386 jg 0x7adb
0388 push 0
038a push 0x238c
038d nop 
038e push cs
038f call 0x8262 ; _YellowDialog
0392 add sp, 4
0395 nop 
0396 push cs
0397 call 0x9b60 ; _UpdateEverything
039a les bx, ptr [bp - 0xa]
039d cmp word ptr es:[bx], 0
03a1 jne 0x7b05
03a3 push word ptr [0xcf50] ; _MeDir
03a7 push word ptr [0xcc84] ; _MeType
03ab push word ptr [0xce7e] ; _MeLocY
03af push word ptr [0xcd88] ; _MeLocX
03b3 push word ptr [0xce80] ; _MePlane
03b7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 954, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
03bc add sp, 0xa
03bf push 6
03c1 nop 
03c2 push cs
03c3 call 0x96b0 ; _SetSimCursor
03c6 add sp, 2
03c9 push 1
03cb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 974, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UnRecruit
03d0 add sp, 2
03d3 mov es, word ptr [0xbf50]
03d7 cmp word ptr es:[0x75fa], 0
03dd je 0x7b5a
03df xor ax, ax
03e1 mov word ptr es:[0x75fa], ax
03e5 push ax
03e6 push 0x10
03e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1003, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
03ed add sp, 4
03f0 mov word ptr [0xac58], 0xffff ; _ELayerMode
03f6 mov es, word ptr [0xbf52]
03fa push word ptr es:[0x9b6c]
03ff mov es, word ptr [0xbf54]
0403 push word ptr es:[0x7292]
0408 push 0
040a push 0
040c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1039, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvalEuMap
0411 add sp, 8
0414 xor di, di
0416 mov es, word ptr [0xbf56]
041a mov si, word ptr es:[0x99d4]
041f mov word ptr [bp - 0xc], si
0422 or si, si
0424 jge 0x7b74
0426 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1063, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0429 mov ds, ax
042b jmp 0x7bc9
042d nop 
042e mov word ptr [bp - 4], di
0431 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1074, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0434 mov ds, ax
0436 mov cl, byte ptr [si + 0x3d18]
043a sub ch, ch
043c or cx, cx
043e je 0x7b8b
0440 cmp cx, 8
0443 jl 0x7b90
0445 dec si
0446 jns 0x7b7c
0448 jmp 0x7bc9
044a mov al, byte ptr [si + 0x392c]
044e sub ah, ah
0450 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0453 mov es, cx
0455 mov word ptr es:[0x9fee], ax
0459 mov bl, byte ptr [si + 0x3736]
045d sub bh, bh
045f mov <resolved loader operand; see bindings> ; [{'operand_offset': 1120, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0462 mov es, cx
0464 mov word ptr es:[0x9fec], bx
0469 shl bx, 6
046c add bx, ax
046e xor al, al
0470 mov byte ptr [si + 0x3d18], al
0474 mov byte ptr ss:[bx - 0x7718], al
0479 mov di, 1
047c mov word ptr ss:[0xce80], 2
0483 or di, di
0485 jne 0x7c34
0487 mov si, word ptr [bp - 0xc]
048a cmp si, di
048c jl 0x7c34
048e mov word ptr [bp - 4], di
0491 mov bl, byte ptr [si + 0x3d18]
0495 sub bh, bh
0497 or bx, bx
0499 je 0x7beb
049b cmp bx, 7
049e jle 0x7beb
04a0 cmp bx, 0x68
04a3 jl 0x7bf4
04a5 dec si
04a6 jns 0x7bd7
04a8 mov di, word ptr [bp - 4]
04ab jmp 0x7c34
04ad nop 
04ae mov al, byte ptr [si + 0x392c]
04b2 sub ah, ah
04b4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1205, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
04b7 mov es, cx
04b9 mov word ptr es:[0x9fee], ax
04bd mov cl, byte ptr [si + 0x3d18]
04c1 sub ch, ch
04c3 mov word ptr [bp - 2], cx
04c6 mov bl, byte ptr [si + 0x3736]
04ca sub bh, bh
04cc mov <resolved loader operand; see bindings> ; [{'operand_offset': 1229, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
04cf mov es, cx
04d1 mov word ptr es:[0x9fec], bx
04d6 shl bx, 6
04d9 add bx, ax
04db xor al, al
04dd mov byte ptr [si + 0x3d18], al
04e1 mov byte ptr ss:[bx - 0x7718], al
04e6 mov di, 2
04e9 mov word ptr ss:[0xce80], di
04ee or di, di
04f0 jne 0x7ca8
04f2 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1267, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
04f5 mov es, ax
04f7 mov si, word ptr es:[0x80f0]
04fc or si, si
04fe jl 0x7ca8
0500 mov word ptr [bp - 4], di
0503 mov bl, byte ptr [si + 0x2f62]
0507 sub bh, bh
0509 or bx, bx
050b je 0x7c5d
050d cmp bx, 7
0510 jle 0x7c5d
0512 cmp bx, 0x68
0515 jl 0x7c66
0517 dec si
0518 jns 0x7c49
051a mov di, word ptr [bp - 4]
051d jmp 0x7ca8
051f nop 
0520 mov al, byte ptr [si + 0x278e]
0524 sub ah, ah
0526 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1319, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0529 mov es, cx
052b mov word ptr es:[0x9fee], ax
052f mov cl, byte ptr [si + 0x2f62]
0533 sub ch, ch
0535 mov word ptr [bp - 2], cx
0538 mov bl, byte ptr [si + 0x23a4]
053c sub bh, bh
053e mov <resolved loader operand; see bindings> ; [{'operand_offset': 1343, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0541 mov es, cx
0543 mov word ptr es:[0x9fec], bx
0548 shl bx, 6
054b add bx, ax
054d xor al, al
054f mov byte ptr [si + 0x2f62], al
0553 mov byte ptr ss:[bx + 0x68e8], al
0558 mov di, 2
055b mov word ptr ss:[0xce80], 1
0562 or di, di
0564 jne 0x7d1c
0566 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1383, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0569 mov es, ax
056b mov si, word ptr es:[0x72cc]
0570 or si, si
0572 jl 0x7d1c
0574 mov word ptr [bp - 4], di
0577 mov bl, byte ptr [si + 0x46e6]
057b sub bh, bh
057d or bx, bx
057f je 0x7cd1
0581 cmp bx, 7
0584 jle 0x7cd1
0586 cmp bx, 0x68
0589 jl 0x7cda
058b dec si
058c jns 0x7cbd
058e mov di, word ptr [bp - 4]
0591 jmp 0x7d1c
0593 nop 
0594 mov al, byte ptr [si + 0x42fa]
0598 sub ah, ah
059a mov <resolved loader operand; see bindings> ; [{'operand_offset': 1435, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
059d mov es, cx
059f mov word ptr es:[0x9fee], ax
05a3 mov cl, byte ptr [si + 0x46e6]
05a7 sub ch, ch
05a9 mov word ptr [bp - 2], cx
05ac mov bl, byte ptr [si + 0x4104]
05b0 sub bh, bh
05b2 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1459, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
05b5 mov es, cx
05b7 mov word ptr es:[0x9fec], bx
05bc shl bx, 6
05bf add bx, ax
05c1 xor al, al
05c3 mov byte ptr [si + 0x46e6], al
05c7 mov byte ptr ss:[bx - 0x6718], al
05cc mov di, 2
05cf mov word ptr ss:[0xce80], 3
05d6 or di, di
05d8 jne 0x7d50
05da push ss
05db pop ds
05dc nop 
05dd push cs
05de call 0x34 ; _RestartSimulation
05e1 mov es, word ptr [0xbf0a]
05e5 mov ax, word ptr es:[0x80b4]
05e9 mov word ptr [bp - 0xe], ax
05ec cmp ax, 1
05ef jg 0x7d8e
05f1 mov es, word ptr [0xbf58]
05f5 mov word ptr es:[0x9dda], 1
05fc mov es, word ptr [0xbf5a]
0600 mov word ptr es:[0x9cea], di
0605 pop si
0606 pop di
0607 leave 
0608 retf 
0609 nop 
060a push ss
060b pop ds
060c dec di
060d je 0x7d58
060f jmp 0x7dda
0612 cmp word ptr [0xcc84], 0x60 ; _MeType
0617 jne 0x7d65
0619 mov word ptr [0xcc84], 0x10 ; _MeType
061f push 0
0621 push word ptr [0xcc84] ; _MeType
0625 mov es, word ptr [0xbf5c]
0629 push word ptr es:[0x9fee]
062e mov es, word ptr [0xbf5e]
0632 push word ptr es:[0x9fec]
0637 push word ptr [0xce80] ; _MePlane
063b nop 
063c push cs
063d call 0x739e ; _YellowBirth
0640 add sp, 0xa
0643 jmp 0x7ead
0646 nop 
0647 nop 
0648 cmp word ptr [bp - 0xe], 2
064c jne 0x7d52
064e cmp word ptr [0xac90], 2 ; _ColonyTotalBlack
0653 jge 0x7dc2
0655 mov ax, 1
0658 mov es, word ptr [0xbf58]
065c mov word ptr es:[0x9dda], ax
0660 push ax
0661 push 0x2748
0664 xor ax, ax
0666 mov es, word ptr [0xbf5a]
066a mov word ptr es:[0x9cea], ax
066e push ax
066f nop 
0670 push cs
0671 call 0x615a ; _PictStrnDialog
0674 add sp, 6
0677 pop si
0678 pop di
0679 leave 
067a retf 
067b nop 
067c push 1
067e push 0x274a
0681 push di
0682 nop 
0683 push cs
0684 call 0x615a ; _PictStrnDialog
0687 add sp, 6
068a nop 
068b push cs
068c call 0x7eb6 ; _SpecialXfer
068f pop si
0690 pop di
0691 leave 
0692 retf 
0693 nop 
0694 mov di, word ptr [bp - 2]
0697 les bx, ptr [bp - 0xa]
069a mov word ptr es:[bx], 0
069f mov ax, di
06a1 and ax, 0xf8
06a4 mov cx, ax
06a6 add ax, word ptr [0xcf50] ; _MeDir
06aa push ax
06ab push word ptr [0xcf50] ; _MeDir
06af push cx
06b0 mov es, word ptr [0xbf5c]
06b4 push word ptr es:[0x9fee]
06b9 mov es, word ptr [0xbf5e]
06bd push word ptr es:[0x9fec]
06c2 push word ptr [0xce80] ; _MePlane
06c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1737, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
06cb add sp, 0xc
06ce mov ax, word ptr [0xce80] ; _MePlane
06d1 mov es, word ptr [0xbf1a]
06d5 mov word ptr es:[0x9be0], ax
06d9 mov es, word ptr [0xbf5e]
06dd mov ax, word ptr es:[0x9fec]
06e1 mov word ptr [0xcd88], ax ; _MeLocX
06e4 mov es, word ptr [0xbf38]
06e8 mov word ptr es:[0xa0d6], ax
06ec mov es, word ptr [0xbf1c]
06f0 mov word ptr es:[0x80c6], ax
06f4 mov es, word ptr [0xbf5c]
06f8 mov ax, word ptr es:[0x9fee]
06fc mov word ptr [0xce7e], ax ; _MeLocY
06ff mov es, word ptr [0xbf3a]
0703 mov word ptr es:[0xa0da], ax
0707 mov es, word ptr [0xbf1e]
070b mov word ptr es:[0x80d2], ax
070f xor ax, ax
0711 mov es, word ptr [0xbf10]
0715 mov word ptr es:[0x9bc4], ax
0719 mov es, word ptr [0xbf22]
071d mov word ptr es:[0x7d24], ax
0721 mov es, word ptr [0xbf3c]
0725 mov word ptr es:[0x9fe2], ax
0729 mov es, word ptr [0xbf3e]
072d mov word ptr es:[0x80aa], ax
0731 mov es, word ptr [0xbf40]
0735 mov word ptr es:[0x9c7e], ax
0739 mov es, word ptr [0xbf20]
073d mov word ptr es:[0x72e4], 0xfffe
0744 push 0x64
0746 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1865, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyHealth
074b add sp, 2
074e nop 
074f push cs
0750 call 0xa764 ; _GotoMyAnt
0753 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1878, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DoEditAndMapUpdateDraw
0758 push 1
075a push 0x274b
075d push 0
075f nop 
0760 push cs
0761 call 0x615a ; _PictStrnDialog
0764 add sp, 6
0767 nop 
0768 push cs
0769 call 0x34 ; _RestartSimulation
076c pop si
076d pop di
076e leave 
076f retf 
```

## Known declaration examples

- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far ClearMyLife(int plane, int x, int y, int type, int dir);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near ColonyTotalBlack;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int near ELayerMode;` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int near ELayerMode;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near ELayerMode;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far EndTargetMode(void);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far GotoMyAnt(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far InvalEuMap(int left, int top, int right, int bottom);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far InvalEuMap(int a, int b, int columns, int rows);` — src/recovered/wf_tu_simant_9D04_SetMapPlane_1_scaffold-47a07d4d6a.c
- `extern void far InvalEuMap(int a, int b, int columns, int rows);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near MeDir;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeType;` — src/recovered/wf_DropMyObject-9eb45c4e42.c
- `extern int near MeType;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeType;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far RestartSimulation(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern void far SetMyHealth(int health);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far SetMyHealth(int health);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far SetMyLife(int plane, int x, int y, int type, int dir, int code);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far SetSimCursor(int cursor);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern void far StopSimulation(void);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far myBeginSong(unsigned int song, unsigned int priority);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far myBeginSong(unsigned int song, unsigned int mode);` — src/recovered/wf_tu_simtwo_0000_GstrB_9_scaffold-1d3fbf27a4.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_UpdateUserButtons-609b2b7960.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_StopSimulation'], 'segment': 1, 'target_offset': 0, 'caller_offsets': [8]}
- {'callee_names': ['_RestartSimulation'], 'segment': 1, 'target_offset': 52, 'caller_offsets': [1502, 1897]}
- {'callee_names': ['_SetDefaultWindPrompt'], 'segment': 1, 'target_offset': 24780, 'caller_offsets': [59]}
- {'callee_names': ['_PictStrnDialog'], 'segment': 1, 'target_offset': 24922, 'caller_offsets': [495, 746, 888, 1649, 1668, 1889]}
- {'callee_names': ['_SpiderDialog'], 'segment': 1, 'target_offset': 26426, 'caller_offsets': [364]}
- {'callee_names': ['_YellowBirth'], 'segment': 1, 'target_offset': 29598, 'caller_offsets': [1597]}
- {'callee_names': ['_SpecialXfer'], 'segment': 1, 'target_offset': 32438, 'caller_offsets': [1676]}
- {'callee_names': ['_LionDialog'], 'segment': 1, 'target_offset': 32928, 'caller_offsets': [454]}
- {'callee_names': ['_YellowDialog'], 'segment': 1, 'target_offset': 33378, 'caller_offsets': [911]}
- {'callee_names': ['_SetSimCursor'], 'segment': 1, 'target_offset': 38576, 'caller_offsets': [49, 240, 963]}
- {'callee_names': ['_UpdateEverything'], 'segment': 1, 'target_offset': 39776, 'caller_offsets': [919]}
- {'callee_names': ['_GotoMyAnt'], 'segment': 1, 'target_offset': 42852, 'caller_offsets': [189, 1872]}

## Neighbors

- {'symbol': '_SetGoalsY', 'offset': 29492, 'source': None, 'size': 105}
- {'symbol': '_YellowBirth', 'offset': 29598, 'source': None, 'size': 936}
- {'symbol': '_SpecialXfer', 'offset': 32438, 'source': None, 'size': 490}
- {'symbol': '_LionDialog', 'offset': 32928, 'source': None, 'size': 449}
