# Recovery task _MoveSpider

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 3165 bytes.

```asm
0000 enter 0x32, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc43e]
000a mov ax, word ptr es:[0x77ac]
000e inc ax
000f and ah, 3
0012 mov word ptr es:[0x77ac], ax
0016 mov ax, word ptr [0xac7c] ; _SpidX
0019 sar ax, 4
001c mov di, ax
001e mov ax, word ptr [0xac7e] ; _SpidY
0021 sar ax, 4
0024 mov cx, ax
0026 mov bx, 0x9fe8
0029 mov es, word ptr [0xc454]
002d mov word ptr [bp - 0x12], bx
0030 mov word ptr [bp - 0x10], es
0033 cmp word ptr es:[bx], 1
0037 je 0x4740
0039 jmp 0x4938
003c mov bx, 0x729e
003f mov es, word ptr [0xc448]
0043 mov word ptr [bp - 0x16], bx
0046 mov word ptr [bp - 0x14], es
0049 cmp word ptr es:[bx], 2
004d jne 0x4756
004f jmp 0x4938
0052 cmp word ptr es:[bx], 3
0056 jne 0x475f
0058 jmp 0x4938
005b mov es, word ptr [0xc44a]
005f cmp word ptr es:[0x7d60], 7
0065 jne 0x47be
0067 nop 
0068 push cs
0069 call 0x53f6 ; _SFoundAnt
006c mov bx, 0x7a5e
006f mov es, word ptr [0xc44c]
0073 mov word ptr [bp - 0x1a], bx
0076 mov word ptr [bp - 0x18], es
0079 mov word ptr es:[bx], ax
007c cmp ax, 0xfffe
007f je 0x47cb
0081 les bx, ptr [bp - 0x16]
0084 mov word ptr es:[bx], 2
0089 les bx, ptr [bp - 0x1a]
008c cmp word ptr es:[bx], 0
0090 jl 0x47b0
0092 mov bx, word ptr es:[bx]
0095 mov es, word ptr [0xc456]
0099 mov al, byte ptr es:[bx + 0x2f62]
009e sub ah, ah
00a0 mov es, word ptr [0xc44e]
00a4 mov word ptr es:[0x80a8], ax
00a8 jmp 0x535d
00ab nop 
00ac mov es, word ptr [0xc44e]
00b0 mov word ptr es:[0x80a8], 0xff
00b7 jmp 0x535d
00ba cmp word ptr es:[0x7d60], 8
00c0 jne 0x47cb
00c2 nop 
00c3 push cs
00c4 call 0x5536 ; _SpiderScan
00c7 mov bx, 0x78ea
00ca mov es, word ptr [0xc452]
00ce mov word ptr [bp - 0x1e], bx
00d1 mov word ptr [bp - 0x1c], es
00d4 push word ptr es:[bx]
00d7 mov bx, 0x78b8
00da mov es, word ptr [0xc450]
00de mov word ptr [bp - 0x22], bx
00e1 mov word ptr [bp - 0x20], es
00e4 push word ptr es:[bx]
00e7 push word ptr [0xce7e] ; _MeLocY
00eb push word ptr [0xcd88] ; _MeLocX
00ef nop 
00f0 push cs
00f1 call 0x1122 ; _GetDis
00f4 add sp, 8
00f7 mov di, ax
00f9 cmp di, 1
00fc jge 0x4810
00fe mov es, word ptr [0xc43c]
0102 mov word ptr es:[0x7290], 2
0109 jmp 0x535d
010c les bx, ptr [bp - 0x1e]
010f push word ptr es:[bx]
0112 les bx, ptr [bp - 0x22]
0115 push word ptr es:[bx]
0118 push word ptr [0xce7e] ; _MeLocY
011c push word ptr [0xcd88] ; _MeLocX
0120 push 1
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _GetBestDir
0127 add sp, 0xa
012a mov si, ax
012c cmp si, -1
012f jne 0x4838
0131 jmp 0x535d
0134 cmp si, -2
0137 jne 0x4861
0139 les bx, ptr [bp - 0x1e]
013c push word ptr es:[bx]
013f les bx, ptr [bp - 0x22]
0142 push word ptr es:[bx]
0145 push word ptr [0xce7e] ; _MeLocY
0149 push word ptr [0xcd88] ; _MeLocX
014d nop 
014e push cs
014f call 0x10cc ; _GetDir
0152 add sp, 8
0155 mov si, ax
0157 dec si
0158 jns 0x4861
015a jmp 0x535d
015d mov <resolved loader operand; see bindings> ; [{'operand_offset': 350, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0160 mov es, ax
0162 mov bx, word ptr ss:[0xac80]
0167 shl bx, 3
016a add bx, si
016c mov al, byte ptr es:[bx + 0x24]
0171 cwde 
0172 mov word ptr ss:[0xac80], ax
0176 mov <resolved loader operand; see bindings> ; [{'operand_offset': 375, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0179 mov es, ax
017b cmp word ptr es:[0x9bc4], 0
0181 je 0x48d2
0183 cmp di, 2
0186 jle 0x48d2
0188 mov <resolved loader operand; see bindings> ; [{'operand_offset': 393, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
018b mov es, ax
018d mov bx, word ptr ss:[0xac80]
0192 mov al, byte ptr es:[bx - 0x7824]
0197 cwde 
0198 mov cx, ax
019a shl ax, 2
019d add ax, cx
019f add word ptr ss:[0xac7c], ax
01a4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 421, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01a7 mov es, ax
01a9 mov al, byte ptr es:[bx - 0x781c]
01ae cwde 
01af mov cx, ax
01b1 shl ax, 2
01b4 add ax, cx
01b6 add word ptr ss:[0xac7e], ax
01bb mov <resolved loader operand; see bindings> ; [{'operand_offset': 444, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01be mov ds, ax
01c0 mov ax, word ptr [0x7290]
01c3 add ax, 2
01c6 and ah, 3
01c9 mov word ptr [0x7290], ax
01cc jmp 0x4908
01ce mov <resolved loader operand; see bindings> ; [{'operand_offset': 463, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01d1 mov es, ax
01d3 mov bx, word ptr ss:[0xac80]
01d8 mov al, byte ptr es:[bx - 0x7824]
01dd cwde 
01de add word ptr ss:[0xac7c], ax
01e3 mov <resolved loader operand; see bindings> ; [{'operand_offset': 484, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01e6 mov es, ax
01e8 mov al, byte ptr es:[bx - 0x781c]
01ed cwde 
01ee add word ptr ss:[0xac7e], ax
01f3 mov <resolved loader operand; see bindings> ; [{'operand_offset': 500, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01f6 mov es, ax
01f8 mov ax, word ptr es:[0x7290]
01fc inc ax
01fd and ah, 3
0200 mov word ptr es:[0x7290], ax
0204 mov ax, word ptr ss:[0xac7c]
0208 sar ax, 4
020b mov word ptr ss:[0xcd88], ax
020f mov ax, word ptr ss:[0xac7e]
0213 sar ax, 4
0216 mov word ptr ss:[0xce7e], ax
021a mov <resolved loader operand; see bindings> ; [{'operand_offset': 539, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
021d mov es, ax
021f cmp word ptr es:[0x85f2], 0
0225 jne 0x492e
0227 jmp 0x4d62
022a push ss
022b pop ds
022c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 559, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoMyAnt
0231 jmp 0x535d
0234 mov bx, 0x9bd2
0237 mov es, word ptr [0xc446]
023b mov word ptr [bp - 0x26], bx
023e mov word ptr [bp - 0x24], es
0241 cmp word ptr es:[bx], 0
0245 jne 0x49c6
0247 mov es, word ptr [0xc444]
024b cmp word ptr es:[0x80b4], 0
0251 jne 0x495a
0253 jmp 0x535d
0256 push 0x12c
0259 nop 
025a push cs
025b call 0x158a ; _SRand1
025e add sp, 2
0261 or ax, ax
0263 je 0x496c
0265 jmp 0x535d
0268 push 0x400
026b nop 
026c push cs
026d call 0x158a ; _SRand1
0270 add sp, 2
0273 add ah, 2
0276 mov word ptr [0xac7c], ax ; _SpidX
0279 mov ax, 1
027c les bx, ptr [bp - 0x26]
027f mov word ptr es:[bx], ax
0282 mov es, word ptr [0xc448]
0286 mov word ptr es:[0x729e], ax
028a mov es, word ptr [0xc442]
028e mov word ptr es:[0x8a5a], 0
0295 push 2
0297 nop 
0298 push cs
0299 call 0x158a ; _SRand1
029c add sp, 2
029f or ax, ax
02a1 je 0x49b6
02a3 mov word ptr [0xac7e], 1 ; _SpidY
02a9 mov word ptr [0xac80], 4 ; _SpidDir
02af jmp 0x535d
02b2 mov word ptr [0xac7e], 0x3ff ; _SpidY
02b8 mov word ptr [0xac80], 0 ; _SpidDir
02be pop si
02bf pop di
02c0 leave 
02c1 retf 
02c2 mov word ptr [bp - 0xe], di
02c5 mov word ptr [bp - 0xc], cx
02c8 mov es, word ptr [0xc43e]
02cc test byte ptr es:[0x77ac], 3
02d2 je 0x49db
02d4 jmp 0x4b23
02d7 mov bx, 0x729e
02da mov es, word ptr [0xc448]
02de mov word ptr [bp - 0x16], bx
02e1 mov word ptr [bp - 0x14], es
02e4 cmp word ptr es:[bx], 5
02e8 jl 0x49f1
02ea jmp 0x4b23
02ed mov ax, word ptr [0xac7c] ; _SpidX
02f0 sar ax, 4
02f3 mov word ptr [bp - 6], ax
02f6 mov ax, word ptr [0xac7e] ; _SpidY
02f9 sar ax, 4
02fc mov word ptr [bp - 0xa], ax
02ff mov word ptr [bp - 8], 0
0304 mov dx, 0xffff
0307 mov cx, 0xffff
030a mov ax, word ptr [bp - 6]
030d add ax, dx
030f mov di, ax
0311 mov word ptr [bp - 4], dx
0314 mov dx, word ptr [bp - 8]
0317 mov bx, word ptr [bp - 0xa]
031a add bx, cx
031c mov ax, word ptr [bp - 4]
031f add ax, word ptr [bp - 6]
0322 js 0x4a43
0324 cmp di, 0x7f
0327 jg 0x4a43
0329 or bx, bx
032b jl 0x4a43
032d cmp bx, 0x3f
0330 jg 0x4a43
0332 mov si, di
0334 shl si, 6
0337 cmp byte ptr [bx + si + 0x68e8], 0
033c je 0x4a43
033e inc dx
033f inc cx
0340 cmp cx, 3
0343 jl 0x4a1b
0345 mov word ptr [bp - 8], dx
0348 mov dx, word ptr [bp - 4]
034b inc dx
034c cmp dx, 3
034f jl 0x4a0b
0351 mov dx, word ptr [bp - 8]
0354 cmp dx, 8
0357 jg 0x4a60
0359 jmp 0x4b16
035c les bx, ptr [bp - 0x16]
035f mov word ptr es:[bx], 5
0364 mov es, word ptr [0xc458]
0368 mov word ptr es:[0x72e0], 0x1f4
036f mov es, word ptr [0xc43c]
0373 mov word ptr es:[0x7290], 0
037a les bx, ptr [bp - 0x12]
037d cmp word ptr es:[bx], 1
0381 je 0x4b02
0383 push 0
0385 push 0x273e
0388 push 0
038a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 909, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
038f add sp, 6
0392 mov bx, 0x72c2
0395 mov es, word ptr [0xc440]
0399 mov word ptr [bp - 0x2a], bx
039c mov word ptr [bp - 0x28], es
039f cmp word ptr es:[bx], 5
03a3 jge 0x4aac
03a5 inc word ptr es:[bx]
03a8 les bx, ptr [bp - 0x2a]
03ab cmp word ptr es:[bx], 3
03af jge 0x4ab8
03b1 jmp 0x535d
03b4 cmp word ptr es:[bx], 5
03b8 jl 0x4acc
03ba mov es, word ptr [0xc44a]
03be mov word ptr es:[0x7d60], 8
03c5 jmp 0x4ad7
03c7 nop 
03c8 mov es, word ptr [0xc44a]
03cc mov word ptr es:[0x7d60], 7
03d3 mov es, word ptr [bp - 0x28]
03d6 cmp word ptr es:[bx], 6
03da jge 0x4ae3
03dc jmp 0x535d
03df nop 
03e0 push cs
03e1 call 0x15ae ; _SRand2
03e4 or ax, ax
03e6 je 0x4aef
03e8 jmp 0x535d
03eb les bx, ptr [bp - 0x2a]
03ee mov word ptr es:[bx], ax
03f1 mov es, word ptr [0xc44a]
03f5 mov word ptr es:[0x7d60], ax
03f9 pop si
03fa pop di
03fb leave 
03fc retf 
03fd nop 
03fe mov word ptr es:[bx], 0
0403 push 3
0405 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1032, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
040a add sp, 2
040d pop si
040e pop di
040f leave 
0410 retf 
0411 nop 
0412 cmp dx, 4
0415 jle 0x4b23
0417 les bx, ptr [bp - 0x16]
041a mov word ptr es:[bx], 4
041f mov bx, 0x729e
0422 mov es, word ptr [0xc448]
0426 mov word ptr [bp - 0x16], bx
0429 mov word ptr [bp - 0x14], es
042c cmp word ptr es:[bx], 4
0430 jge 0x4b47
0432 mov es, word ptr [0xc44a]
0436 cmp word ptr es:[0x7d60], 8
043c jne 0x4b47
043e nop 
043f push cs
0440 call 0x5536 ; _SpiderScan
0443 les bx, ptr [bp - 0x16]
0446 mov ax, word ptr es:[bx]
0449 cmp ax, 5
044c jbe 0x4b55
044e jmp 0x52fb
0451 shl ax, 1
0453 xchg bx, ax
0454 jmp word ptr cs:[bx + 0x4b5e]
0459 nop 
045a dw offset 0x4b6a
045c dw offset 0x4bf0
045e dw offset 0x4ca8
0460 dw offset 0x4de5
0462 dw offset 0x4fb4
0464 dw offset 0x507e
0466 mov es, word ptr [0xc43c]
046a mov word ptr es:[0x7290], 2
0471 push 0x96
0474 nop 
0475 push cs
0476 call 0x158a ; _SRand1
0479 add sp, 2
047c or ax, ax
047e jne 0x4b8c
0480 les bx, ptr [bp - 0x16]
0483 mov word ptr es:[bx], 1
0488 nop 
0489 push cs
048a call 0x53f6 ; _SFoundAnt
048d mov bx, 0x7a5e
0490 mov es, word ptr [0xc44c]
0494 mov word ptr [bp - 0x1a], bx
0497 mov word ptr [bp - 0x18], es
049a mov word ptr es:[bx], ax
049d cmp ax, 0xfffe
04a0 je 0x4ba9
04a2 jmp 0x4785
04a5 push 0x1e
04a7 nop 
04a8 push cs
04a9 call 0x158a ; _SRand1
04ac add sp, 2
04af or ax, ax
04b1 jne 0x4bd8
04b3 push 8
04b5 nop 
04b6 push cs
04b7 call 0x158a ; _SRand1
04ba add sp, 2
04bd mov bx, ax
04bf mov ax, word ptr [0xac80] ; _SpidDir
04c2 shl ax, 3
04c5 add bx, ax
04c7 mov es, word ptr [0xc45a]
04cb mov al, byte ptr es:[bx + 0x24]
04d0 cwde 
04d1 mov word ptr [0xac80], ax ; _SpidDir
04d4 mov es, word ptr [0xc44a]
04d8 cmp word ptr es:[0x7d60], 8
04de je 0x4be7
04e0 jmp 0x52fb
04e3 nop 
04e4 push cs
04e5 call 0x5536 ; _SpiderScan
04e8 jmp 0x52fb
04eb nop 
04ec mov es, word ptr [0xc442]
04f0 cmp word ptr es:[0x8a5a], 0
04f6 je 0x4c28
04f8 mov di, word ptr [0xac80] ; _SpidDir
04fc mov es, word ptr [0xc45c]
0500 mov al, byte ptr es:[di - 0x7824]
0505 cwde 
0506 sub word ptr [0xac7c], ax ; _SpidX
050a mov es, word ptr [0xc45e]
050e mov al, byte ptr es:[di - 0x781c]
0513 cwde 
0514 sub word ptr [0xac7e], ax ; _SpidY
0518 mov es, word ptr [0xc43c]
051c mov ax, word ptr es:[0x7290]
0520 dec ax
0521 jmp 0x4c51
0523 nop 
0524 mov di, word ptr [0xac80] ; _SpidDir
0528 mov es, word ptr [0xc45c]
052c mov al, byte ptr es:[di - 0x7824]
0531 cwde 
0532 add word ptr [0xac7c], ax ; _SpidX
0536 mov es, word ptr [0xc45e]
053a mov al, byte ptr es:[di - 0x781c]
053f cwde 
0540 add word ptr [0xac7e], ax ; _SpidY
0544 mov es, word ptr [0xc43c]
0548 mov ax, word ptr es:[0x7290]
054c inc ax
054d and ah, 3
0550 mov word ptr es:[0x7290], ax
0554 push 0x14
0556 nop 
0557 push cs
0558 call 0x158a ; _SRand1
055b add sp, 2
055e or ax, ax
0560 jne 0x4c87
0562 push 8
0564 nop 
0565 push cs
0566 call 0x158a ; _SRand1
0569 add sp, 2
056c mov bx, ax
056e mov ax, word ptr [0xac80] ; _SpidDir
0571 shl ax, 3
0574 add bx, ax
0576 mov es, word ptr [0xc45a]
057a mov al, byte ptr es:[bx + 0x24]
057f cwde 
0580 mov word ptr [0xac80], ax ; _SpidDir
0583 nop 
0584 push cs
0585 call 0x53f6 ; _SFoundAnt
0588 mov bx, 0x7a5e
058b mov es, word ptr [0xc44c]
058f mov word ptr [bp - 0x1a], bx
0592 mov word ptr [bp - 0x18], es
0595 mov word ptr es:[bx], ax
0598 cmp ax, 0xfffe
059b jne 0x4ca4
059d jmp 0x5058
05a0 jmp 0x4785
05a3 nop 
05a4 mov bx, 0x7a5e
05a7 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1448, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
05aa mov es, ax
05ac mov word ptr [bp - 0x1a], bx
05af mov word ptr [bp - 0x18], es
05b2 cmp word ptr es:[bx], 0
05b6 jge 0x4cbf
05b8 jmp 0x4d68
05bb mov bx, word ptr es:[bx]
05be mov <resolved loader operand; see bindings> ; [{'operand_offset': 1471, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
05c1 mov es, ax
05c3 mov al, byte ptr es:[bx + 0x2f62]
05c8 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1481, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
05cb mov es, cx
05cd xor al, byte ptr es:[0x80a8]
05d2 test al, 0xf0
05d4 je 0x4d38
05d6 les bx, ptr [bp - 0x16]
05d9 mov word ptr es:[bx], 0
05de les bx, ptr [bp - 0x1a]
05e1 mov word ptr es:[bx], 0xfffe
05e6 les bx, ptr [bp - 0x12]
05e9 cmp word ptr es:[bx], 1
05ed jne 0x4d62
05ef mov <resolved loader operand; see bindings> ; [{'operand_offset': 1520, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
05f2 mov ds, ax
05f4 mov ax, word ptr ss:[0xac7e]
05f8 sar ax, 4
05fb mov word ptr [0x78ea], ax
05fe mov cx, word ptr ss:[0xac7c]
0603 sar cx, 4
0606 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1543, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0609 mov es, dx
060b mov word ptr es:[0x78b8], cx
0610 mov word ptr ss:[0xcd88], cx
0615 mov word ptr ss:[0xce7e], ax
0619 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1562, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
061c mov es, ax
061e cmp word ptr es:[0x7d60], 6
0624 je 0x4d2d
0626 jmp 0x491e
0629 mov word ptr es:[0x7d60], 0
0630 jmp 0x491e
0633 nop 
0634 push ss
0635 pop ds
0636 les bx, ptr [bp - 0x1a]
0639 cmp word ptr es:[bx], 0
063d jge 0x4d86
063f mov dx, word ptr [0xce7e] ; _MeLocY
0643 sub dx, word ptr [bp - 0xc]
0646 mov bx, word ptr [0xcd88] ; _MeLocX
064a sub bx, word ptr [bp - 0xe]
064d jns 0x4d55
064f neg bx
0651 or dx, dx
0653 jge 0x4d5b
0655 neg dx
0657 mov di, dx
0659 add di, bx
065b jmp 0x4db1
065d nop 
065e push ss
065f pop ds
0660 jmp 0x535d
0663 nop 
0664 push ss
0665 pop ds
0666 cmp word ptr [0xce80], 1 ; _MePlane
066b jle 0x4d3a
066d les bx, ptr [bp - 0x16]
0670 mov word ptr es:[bx], 0
0675 les bx, ptr [bp - 0x1a]
0678 mov word ptr es:[bx], 0xfffe
067d pop si
067e pop di
067f leave 
0680 retf 
0681 nop 
0682 mov bx, word ptr es:[bx]
0685 mov es, word ptr [0xc456]
0689 mov cl, byte ptr es:[bx + 0x278e]
068e sub ch, ch
0690 sub cx, word ptr [bp - 0xc]
0693 mov si, word ptr es:[bx + 0x23a4]
0698 and si, 0xff
069c sub si, word ptr [bp - 0xe]
069f jns 0x4da7
06a1 neg si
06a3 or cx, cx
06a5 jge 0x4dad
06a7 neg cx
06a9 mov di, cx
06ab add di, si
06ad cmp di, 0x40
06b0 jle 0x4dbf
06b2 les bx, ptr [bp - 0x12]
06b5 cmp word ptr es:[bx], 1
06b9 jne 0x4d71
06bb cmp di, 2
06be jl 0x4dc7
06c0 jmp 0x4e8c
06c3 les bx, ptr [bp - 0x16]
06c6 mov word ptr es:[bx], 3
06cb mov ax, word ptr [0xac7c] ; _SpidX
06ce and al, 0xf0
06d0 add ax, 8
06d3 mov word ptr [0xac7c], ax ; _SpidX
06d6 mov ax, word ptr [0xac7e] ; _SpidY
06d9 and al, 0xf0
06db add ax, 8
06de mov word ptr [0xac7e], ax ; _SpidY
06e1 les bx, ptr [bp - 0x12]
06e4 cmp word ptr es:[bx], 1
06e8 jne 0x4e24
06ea mov ax, word ptr [0xac7c] ; _SpidX
06ed sar ax, 4
06f0 mov word ptr [0xcd88], ax ; _MeLocX
06f3 mov ax, word ptr [0xac7e] ; _SpidY
06f6 sar ax, 4
06f9 mov word ptr [0xce7e], ax ; _MeLocY
06fc mov es, word ptr [0xc44a]
0700 cmp word ptr es:[0x7d60], 6
0706 jne 0x4e13
0708 mov word ptr es:[0x7d60], 0
070f mov es, word ptr [0xc460]
0713 cmp word ptr es:[0x85f2], 0
0719 je 0x4e24
071b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1822, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoMyAnt
0720 mov bx, 0x7a5e
0723 mov es, word ptr [0xc44c]
0727 mov word ptr [bp - 0x1a], bx
072a mov word ptr [bp - 0x18], es
072d cmp word ptr es:[bx], -2
0731 jne 0x4e3a
0733 jmp 0x51cf
0736 cmp word ptr es:[bx], 0
073a jge 0x4e43
073c jmp 0x515e
073f mov es, word ptr [0xc44e]
0743 mov ax, word ptr es:[0x80a8]
0747 mov word ptr [bp - 0x30], ax
074a mov es, word ptr [bp - 0x18]
074d mov bx, word ptr es:[bx]
0750 mov es, word ptr [0xc456]
0754 xor al, byte ptr es:[bx + 0x2f62]
0759 test al, 0xf0
075b je 0x4e64
075d jmp 0x5152
0760 test byte ptr [bp - 0x30], 0x80
0764 jne 0x4e6d
0766 jmp 0x5108
0769 mov es, word ptr [0xc462]
076d add word ptr es:[0x7d5c], 1
0773 adc word ptr es:[0x7d5e], 0
0779 mov es, word ptr [0xc43a]
077d mov word ptr es:[0x78da], 4
0784 jmp 0x5123
0787 nop 
0788 les bx, ptr [bp - 0x1a]
078b cmp word ptr es:[bx], 0
078f jge 0x4ea0
0791 push word ptr [0xce7e] ; _MeLocY
0795 push word ptr [0xcd88] ; _MeLocX
0799 jmp 0x4eb5
079b nop 
079c mov bx, word ptr es:[bx]
079f mov es, word ptr [0xc456]
07a3 mov al, byte ptr es:[bx + 0x278e]
07a8 sub ah, ah
07aa push ax
07ab mov al, byte ptr es:[bx + 0x23a4]
07b0 push ax
07b1 push word ptr [bp - 0xc]
07b4 push word ptr [bp - 0xe]
07b7 nop 
07b8 push cs
07b9 call 0x10cc ; _GetDir
07bc add sp, 8
07bf mov si, ax
07c1 mov es, word ptr [0xc45a]
07c5 mov bx, word ptr [0xac80] ; _SpidDir
07c9 shl bx, 3
07cc add bx, si
07ce mov al, byte ptr es:[bx + 0x23]
07d3 cwde 
07d4 mov word ptr [0xac80], ax ; _SpidDir
07d7 les bx, ptr [bp - 0x1a]
07da cmp word ptr es:[bx], 0
07de jge 0x4ee8
07e0 push 0x7e
07e2 jmp 0x4eea
07e4 push -5
07e6 push 0
07e8 push 0x2f
07ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2029, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
07ef add sp, 6
07f2 mov es, word ptr [0xc442]
07f6 cmp word ptr es:[0x8a5a], 0
07fc je 0x4f3e
07fe mov si, word ptr [0xac80] ; _SpidDir
0802 mov es, word ptr [0xc45c]
0806 mov al, byte ptr es:[si - 0x7824]
080b cwde 
080c mov cx, ax
080e shl ax, 2
0811 add ax, cx
0813 sub word ptr [0xac7c], ax ; _SpidX
0817 mov es, word ptr [0xc45e]
081b mov al, byte ptr es:[si - 0x781c]
0820 cwde 
0821 mov cx, ax
0823 shl ax, 2
0826 add ax, cx
0828 sub word ptr [0xac7e], ax ; _SpidY
082c mov es, word ptr [0xc43c]
0830 mov ax, word ptr es:[0x7290]
0834 sub ax, 2
0837 jmp 0x4f77
0839 nop 
083a mov si, word ptr [0xac80] ; _SpidDir
083e mov es, word ptr [0xc45c]
0842 mov al, byte ptr es:[si - 0x7824]
0847 cwde 
0848 mov cx, ax
084a shl ax, 2
084d add ax, cx
084f add word ptr [0xac7c], ax ; _SpidX
0853 mov es, word ptr [0xc45e]
0857 mov al, byte ptr es:[si - 0x781c]
085c cwde 
085d mov cx, ax
085f shl ax, 2
0862 add ax, cx
0864 add word ptr [0xac7e], ax ; _SpidY
0868 mov es, word ptr [0xc43c]
086c mov ax, word ptr es:[0x7290]
0870 add ax, 2
0873 and ah, 3
0876 mov word ptr es:[0x7290], ax
087a les bx, ptr [bp - 0x12]
087d cmp word ptr es:[bx], 1
0881 je 0x4f8a
0883 jmp 0x52fb
0886 mov ax, word ptr [0xac7c] ; _SpidX
0889 sar ax, 4
088c mov word ptr [0xcd88], ax ; _MeLocX
088f mov ax, word ptr [0xac7e] ; _SpidY
0892 sar ax, 4
0895 mov word ptr [0xce7e], ax ; _MeLocY
0898 mov es, word ptr [0xc460]
089c cmp word ptr es:[0x85f2], 0
08a2 jne 0x4fab
08a4 jmp 0x52fb
08a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _GotoMyAnt
08ac jmp 0x52fb
08af nop 
08b0 push 8
08b2 nop 
08b3 push cs
08b4 call 0x158a ; _SRand1
08b7 add sp, 2
08ba mov bx, ax
08bc mov ax, word ptr [0xac80] ; _SpidDir
08bf shl ax, 3
08c2 add bx, ax
08c4 mov es, word ptr [0xc45a]
08c8 mov al, byte ptr es:[bx + 0x24]
08cd cwde 
08ce mov word ptr [0xac80], ax ; _SpidDir
08d1 mov es, word ptr [0xc442]
08d5 cmp word ptr es:[0x8a5a], 0
08db je 0x501a
08dd mov di, ax
08df mov es, word ptr [0xc45c]
08e3 mov al, byte ptr es:[di - 0x7824]
08e8 cwde 
08e9 mov cx, ax
08eb shl ax, 2
08ee add ax, cx
08f0 sub word ptr [0xac7c], ax ; _SpidX
08f4 mov es, word ptr [0xc45e]
08f8 mov al, byte ptr es:[di - 0x781c]
08fd cwde 
08fe mov cx, ax
0900 shl ax, 2
0903 add ax, cx
0905 sub word ptr [0xac7e], ax ; _SpidY
0909 mov es, word ptr [0xc43c]
090d mov ax, word ptr es:[0x7290]
0911 sub ax, 2
0914 jmp 0x5051
0916 mov di, ax
0918 mov es, word ptr [0xc45c]
091c mov al, byte ptr es:[di - 0x7824]
0921 cwde 
0922 mov cx, ax
0924 shl ax, 2
0927 add ax, cx
0929 add word ptr [0xac7c], ax ; _SpidX
092d mov es, word ptr [0xc45e]
0931 mov al, byte ptr es:[di - 0x781c]
0936 cwde 
0937 mov cx, ax
0939 shl ax, 2
093c add ax, cx
093e add word ptr [0xac7e], ax ; _SpidY
0942 mov es, word ptr [0xc43c]
0946 mov ax, word ptr es:[0x7290]
094a add ax, 2
094d and ah, 3
0950 mov word ptr es:[0x7290], ax
0954 push 0x32
0956 nop 
0957 push cs
0958 call 0x158a ; _SRand1
095b add sp, 2
095e or ax, ax
0960 je 0x5069
0962 jmp 0x52fb
0965 les bx, ptr [bp - 0x16]
0968 mov word ptr es:[bx], ax
096b mov es, word ptr [0xc43c]
096f mov word ptr es:[0x7290], 2
0976 jmp 0x52fb
0979 nop 
097a mov bx, 0x72e0
097d mov es, word ptr [0xc458]
0981 mov word ptr [bp - 0x2e], bx
0984 mov word ptr [bp - 0x2c], es
0987 dec word ptr es:[bx]
098a jne 0x50c6
098c mov di, word ptr [bp - 0xe]
098f mov si, word ptr [bp - 0xc]
0992 xor ax, ax
0994 les bx, ptr [bp - 0x26]
0997 mov word ptr es:[bx], ax
099a les bx, ptr [bp - 0x16]
099d mov word ptr es:[bx], ax
09a0 push si
09a1 push di
09a2 nop 
09a3 push cs
09a4 call 0xd86 ; _DropFoodA
09a7 add sp, 4
09aa push si
09ab push di
09ac nop 
09ad push cs
09ae call 0xd86 ; _DropFoodA
09b1 add sp, 4
09b4 push si
09b5 push di
09b6 nop 
09b7 push cs
09b8 call 0xd86 ; _DropFoodA
09bb add sp, 4
09be pop si
09bf pop di
09c0 leave 
09c1 retf 
09c2 push 0x3e8
09c5 nop 
09c6 push cs
09c7 call 0x158a ; _SRand1
09ca add sp, 2
09cd les bx, ptr [bp - 0x2e]
09d0 cmp ax, word ptr es:[bx]
09d3 jl 0x50dc
09d5 jmp 0x52fb
09d8 cmp word ptr es:[bx], 0x190
09dd jle 0x50f0
09df push 3
09e1 nop 
09e2 push cs
09e3 call 0x158a ; _SRand1
09e6 add sp, 2
09e9 inc ax
09ea jmp 0x50fd
09ec push 2
09ee nop 
09ef push cs
09f0 call 0x158a ; _SRand1
09f3 add sp, 2
09f6 add ax, 2
09f9 mov es, word ptr [0xc43c]
09fd mov word ptr es:[0x7290], ax
0a01 jmp 0x52fb
0a04 mov es, word ptr [0xc464]
0a08 add word ptr es:[0x76a0], 1
0a0e adc word ptr es:[0x76a2], 0
0a14 mov es, word ptr [0xc43a]
0a18 mov word ptr es:[0x78da], 0
0a1f xor al, al
0a21 les bx, ptr [bp - 0x1a]
0a24 mov bx, word ptr es:[bx]
0a27 mov es, word ptr [0xc456]
0a2b mov si, word ptr es:[bx + 0x23a4]
0a30 and si, 0xff
0a34 shl si, 6
0a37 mov cx, bx
0a39 mov bl, byte ptr es:[bx + 0x278e]
0a3e sub bh, bh
0a40 mov byte ptr [bx + si + 0x68e8], al
0a44 mov bx, cx
0a46 mov byte ptr es:[bx + 0x2f62], al
0a4b jmp 0x51ab
0a4d nop 
0a4e les bx, ptr [bp - 0x1a]
0a51 mov word ptr es:[bx], 0xfffe
0a56 jmp 0x52c1
0a59 nop 
0a5a push word ptr [0xcf50] ; _MeDir
0a5e push word ptr [0xcc84] ; _MeType
0a62 mov es, word ptr [0xc466]
0a66 mov bx, word ptr [0xac80] ; _SpidDir
0a6a mov al, byte ptr es:[bx - 0x780c]
0a6f add al, byte ptr [bp - 0xc]
0a72 and ax, 0x3f
0a75 push ax
0a76 mov es, word ptr [0xc468]
0a7a mov al, byte ptr es:[bx - 0x7814]
0a7f add al, byte ptr [bp - 0xe]
0a82 and ax, 0x7f
0a85 push ax
0a86 push word ptr [0xce80] ; _MePlane
0a8a nop 
0a8b push cs
0a8c call 0x65fa ; _MoveMyLife
0a8f add sp, 0xa
0a92 push 1
0a94 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2711, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
0a99 add sp, 2
0a9c mov es, word ptr [0xc43a]
0aa0 mov word ptr es:[0x78da], 0
0aa7 les bx, ptr [bp - 0x1a]
0aaa mov word ptr es:[bx], 0xfffe
0aaf mov es, word ptr [0xc44a]
0ab3 cmp word ptr es:[0x7d60], 7
0ab9 jl 0x51c4
0abb mov ax, 0xb
0abe jmp 0x51c7
0ac0 mov ax, 0x32
0ac3 mov es, word ptr [0xc438]
0ac7 mov word ptr es:[0x77ae], ax
0acb mov es, word ptr [0xc468]
0acf mov bx, word ptr [0xac80] ; _SpidDir
0ad3 mov al, byte ptr es:[bx - 0x7814]
0ad8 cwde 
0ad9 mov si, ax
0adb add si, word ptr [bp - 0xe]
0ade and si, 0x7f
0ae1 mov es, word ptr [0xc466]
0ae5 mov al, byte ptr es:[bx - 0x780c]
0aea cwde 
0aeb mov di, ax
0aed add di, word ptr [bp - 0xc]
0af0 and di, 0x3f
0af3 mov es, word ptr [0xc46a]
0af7 cmp word ptr es:[0x9b6e], 0
0afd jne 0x522b
0aff mov bx, si
0b01 shl bx, 6
0b04 add bx, di
0b06 add bx, 0x28e8
0b0a mov word ptr [bp - 0x32], bx
0b0d cmp byte ptr [bx], 0x18
0b10 jae 0x522b
0b12 nop 
0b13 push cs
0b14 call 0x15ce ; _SRand4
0b17 mov es, word ptr [0xc43a]
0b1b add al, byte ptr es:[0x78da]
0b20 add al, 0x10
0b22 mov bx, word ptr [bp - 0x32]
0b25 mov byte ptr [bx], al
0b27 mov word ptr [bp - 4], di
0b2a mov es, word ptr [0xc438]
0b2e cmp word ptr es:[0x77ae], 0
0b34 jle 0x5278
0b36 dec word ptr es:[0x77ae]
0b3b mov ax, word ptr es:[0x77ae]
0b3f mov cx, 0xa
0b42 cdq 
0b43 idiv cx
0b45 or dx, dx
0b47 je 0x5250
0b49 jmp 0x52fb
0b4c nop 
0b4d push cs
0b4e call 0x15ae ; _SRand2
0b51 or ax, ax
0b53 jne 0x525c
0b55 jmp 0x52fb
0b58 push -5
0b5a nop 
0b5b push cs
0b5c call 0x168e ; _SRand256
0b5f shl ax, 3
0b62 add ax, 0x2777
0b65 push ax
0b66 push 0x2c
0b68 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2923, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0b6d add sp, 6
0b70 jmp 0x52fb
0b73 nop 
0b74 mov es, word ptr [0xc436]
0b78 dec word ptr es:[0x8072]
0b7d jne 0x52ac
0b7f mov word ptr es:[0x8072], 0xa
0b86 mov es, word ptr [0xc460]
0b8a cmp word ptr es:[0x85fc], 0
0b90 je 0x52ac
0b92 nop 
0b93 push cs
0b94 call 0x15ae ; _SRand2
0b97 or ax, ax
0b99 jne 0x52ac
0b9b push 0xa
0b9d push ax
0b9e push 0xa
0ba0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2979, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0ba5 add sp, 6
0ba8 mov es, word ptr [0xc43a]
0bac push word ptr es:[0x78da]
0bb1 push word ptr [bp - 4]
0bb4 push si
0bb5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3000, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _DeadAntHere
0bba add sp, 6
0bbd les bx, ptr [bp - 0x16]
0bc0 mov word ptr es:[bx], 0
0bc5 les bx, ptr [bp - 0x12]
0bc8 cmp word ptr es:[bx], 1
0bcc jne 0x52fb
0bce mov es, word ptr [0xc44a]
0bd2 cmp word ptr es:[0x7d60], 6
0bd8 jne 0x52e5
0bda mov word ptr es:[0x7d60], 0
0be1 mov ax, word ptr [bp - 0xe]
0be4 mov es, word ptr [0xc450]
0be8 mov word ptr es:[0x78b8], ax
0bec mov ax, word ptr [bp - 0xc]
0bef mov es, word ptr [0xc452]
0bf3 mov word ptr es:[0x78ea], ax
0bf7 mov ax, word ptr [0xac7e] ; _SpidY
0bfa sar ax, 4
0bfd push ax
0bfe mov ax, word ptr [0xac7c] ; _SpidX
0c01 sar ax, 4
0c04 push ax
0c05 nop 
0c06 push cs
0c07 call 0x9c02 ; _IsValidA
0c0a add sp, 4
0c0d or ax, ax
0c0f jne 0x5331
0c11 les bx, ptr [bp - 0x26]
0c14 mov word ptr es:[bx], ax
0c17 les bx, ptr [bp - 0x12]
0c1a cmp word ptr es:[bx], 1
0c1e jne 0x5331
0c20 mov word ptr es:[bx], ax
0c23 push 4
0c25 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
0c2a add sp, 2
0c2d mov es, word ptr [0xc46a]
0c31 cmp word ptr es:[0x9b6e], 0
0c37 je 0x535d
0c39 mov si, word ptr [0xac7c] ; _SpidX
0c3d and si, 0xfff0
0c40 shl si, 2
0c43 mov bx, word ptr [0xac7e] ; _SpidY
0c47 sar bx, 4
0c4a cmp byte ptr [bx + si + 0x28e8], 0x90
0c4f jbe 0x535d
0c51 les bx, ptr [bp - 0x26]
0c54 mov word ptr es:[bx], 0
0c59 pop si
0c5a pop di
0c5b leave 
0c5c retf 
```

## Known declaration examples

- `extern void far DeadAntHere(int x, int y, int colour);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far GetDir(int a, int b, int c, int d);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far GetDir(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_0000_GetDefendDir_2_scaffold-cdac288ff9.c
- `extern int far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_0000_GetDefendDir_2_scaffold-cdac288ff9.c
- `extern unsigned long far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern void far GotoMyAnt(void);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simtwo_4CDC_StorePillarMap_4_scaffold-c16d27de40.c
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
- `extern void far MoveMyLife(int plane, int x, int y, int type, int direction);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand2(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near SpidX;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near SpidX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near SpidX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int near SpidY;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near SpidY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near SpidY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far YellowDeath(int code);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_DropFoodA'], 'segment': 5, 'target_offset': 3462, 'caller_offsets': [2468, 2478, 2488]}
- {'callee_names': ['_GetDir'], 'segment': 5, 'target_offset': 4300, 'caller_offsets': [335, 1977]}
- {'callee_names': ['_GetDis'], 'segment': 5, 'target_offset': 4386, 'caller_offsets': [241]}
- {'callee_names': ['_SRand1'], 'segment': 5, 'target_offset': 5514, 'caller_offsets': [603, 621, 665, 1142, 1193, 1207, 1368, 1382, 2228, 2392, 2503, 2531, 2544]}
- {'callee_names': ['_SRand2'], 'segment': 5, 'target_offset': 5550, 'caller_offsets': [993, 2894, 2964]}
- {'callee_names': ['_SRand4'], 'segment': 5, 'target_offset': 5582, 'caller_offsets': [2836]}
- {'callee_names': ['_SRand256'], 'segment': 5, 'target_offset': 5774, 'caller_offsets': [2908]}
- {'callee_names': ['_SFoundAnt'], 'segment': 5, 'target_offset': 21494, 'caller_offsets': [105, 1162, 1413]}
- {'callee_names': ['_SpiderScan'], 'segment': 5, 'target_offset': 21814, 'caller_offsets': [196, 1088, 1253]}
- {'callee_names': ['_MoveMyLife'], 'segment': 5, 'target_offset': 26106, 'caller_offsets': [2700]}
- {'callee_names': ['_IsValidA'], 'segment': 5, 'target_offset': 39938, 'caller_offsets': [3079]}

## Neighbors

- {'symbol': '_AddRock3', 'offset': 17836, 'source': None, 'size': 188}
- {'symbol': '_InitSpider', 'offset': 18024, 'source': None, 'size': 156}
- {'symbol': '_ScanForAnts', 'offset': 21346, 'source': None, 'size': 113}
- {'symbol': '_KillSpider', 'offset': 21460, 'source': 'src/recovered/wf_tu_simone_4668_KillSpider_1_scaffold-37d274226a.c', 'size': 34}
