# Recovery task _DoLifeExchange

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 3379 bytes.

```asm
0000 enter 0x24, 0
0004 push di
0005 push si
0006 mov dx, 0xffff
0009 cmp word ptr [bp + 6], 1
000d jg 0x686e
000f mov di, word ptr [bp + 8]
0012 or di, di
0014 jl 0x6886
0016 cmp di, 0x7f
0019 jg 0x6886
001b cmp word ptr [bp + 0xa], 0
001f jl 0x6886
0021 cmp word ptr [bp + 0xa], 0x3f
0025 jg 0x6886
0027 mov bx, 1
002a jmp 0x6888
002c cmp word ptr [bp + 8], 0
0030 jl 0x6886
0032 cmp word ptr [bp + 8], 0x3f
0036 jg 0x6886
0038 cmp word ptr [bp + 0xa], 0
003c jl 0x6886
003e cmp word ptr [bp + 0xa], 0x3f
0042 jle 0x6869
0044 xor bx, bx
0046 dec bx
0047 jne 0x68d6
0049 mov ax, word ptr [bp + 6]
004c or ax, ax
004e jl 0x68cf
0050 jo 0x68cf
0052 dec ax
0053 jle 0x68a0
0055 dec ax
0056 je 0x68b0
0058 dec ax
0059 je 0x68c0
005b jmp 0x68cf
005d nop 
005e mov si, word ptr [bp + 8]
0061 shl si, 6
0064 mov bx, word ptr [bp + 0xa]
0067 mov dl, byte ptr [bx + si + 0x68e8]
006b jmp 0x68cd
006d nop 
006e mov si, word ptr [bp + 8]
0071 shl si, 6
0074 mov bx, word ptr [bp + 0xa]
0077 mov dl, byte ptr [bx + si - 0x7718]
007b jmp 0x68cd
007d nop 
007e mov si, word ptr [bp + 8]
0081 shl si, 6
0084 mov bx, word ptr [bp + 0xa]
0087 mov dl, byte ptr [bx + si - 0x6718]
008b sub dh, dh
008d or dx, dx
008f jne 0x68d6
0091 mov dx, 0xffff
0094 mov word ptr [bp - 0x10], dx
0097 or dx, dx
0099 jle 0x68e0
009b jmp 0x6c4a
009e cmp word ptr [bp + 6], 1
00a2 je 0x68e9
00a4 jmp 0x737f
00a7 push word ptr [0xac7e] ; _SpidY
00ab push word ptr [0xac7c] ; _SpidX
00af mov ax, word ptr [bp + 0xa]
00b2 shl ax, 4
00b5 add ax, 8
00b8 push ax
00b9 mov ax, word ptr [bp + 8]
00bc shl ax, 4
00bf add ax, 8
00c2 push ax
00c3 nop 
00c4 push cs
00c5 call 0x1122 ; _GetDis
00c8 add sp, 8
00cb or dx, dx
00cd je 0x6914
00cf jmp 0x737f
00d2 cmp ax, 0x200
00d5 jb 0x691c
00d7 jmp 0x737f
00da mov es, word ptr [0xc48a]
00de cmp word ptr es:[0x9fe8], 1
00e4 jne 0x692b
00e6 jmp 0x756e
00e9 mov cx, word ptr [0xcc84] ; _MeType
00ed mov ax, cx
00ef and ax, 0x78
00f2 sar ax, 3
00f5 mov word ptr [bp - 2], ax
00f8 mov word ptr [bp - 0xe], dx
00fb test cl, 8
00fe je 0x696d
0100 cmp ax, 5
0103 je 0x695e
0105 cmp ax, 9
0108 je 0x695e
010a cmp ax, 1
010d jne 0x696d
010f mov es, word ptr [0xc48c]
0113 mov ax, word ptr es:[0x8a6a]
0117 mov word ptr [bp - 0xe], ax
011a jmp 0x696d
011c mov es, word ptr [0xc48e]
0120 mov bx, ax
0122 mov al, byte ptr es:[bx + 0x94]
0127 cwde 
0128 mov word ptr [bp - 2], ax
012b mov ax, word ptr [bp - 2]
012e shl ax, 3
0131 mov dl, byte ptr [0xce98] ; _MeColor
0135 and dx, 0x80
0139 or ax, dx
013b or ax, word ptr [0xcf50] ; _MeDir
013f mov word ptr [bp - 6], ax
0142 cmp cx, 0x60
0145 jne 0x698e
0147 mov ax, 9
014a jmp 0x6990
014c xor ax, ax
014e mov word ptr [bp - 0xa], ax
0151 mov ax, word ptr [0xcd88] ; _MeLocX
0154 mov word ptr [bp - 4], ax
0157 mov ax, word ptr [0xce7e] ; _MeLocY
015a mov word ptr [bp - 8], ax
015d xor si, si
015f mov ax, word ptr [0xce80] ; _MePlane
0162 mov word ptr [bp - 0xc], ax
0165 cmp ax, 1
0168 jg 0x69d0
016a mov es, word ptr [0xc47c]
016e cmp word ptr es:[0x80f0], 0x3e8
0175 jge 0x6a21
0177 push word ptr [bp - 0xe]
017a push word ptr [bp - 0xa]
017d push word ptr [bp - 6]
0180 push word ptr [bp - 8]
0183 push word ptr [bp - 4]
0186 nop 
0187 push cs
0188 call 0x2ef0 ; _AddAntToAList
018b jmp 0x6a1b
018d nop 
018e cmp word ptr [bp - 0xc], 2
0192 jne 0x69fa
0194 mov es, word ptr [0xc47e]
0198 cmp word ptr es:[0x99d4], 0x1f4
019f jge 0x6a21
01a1 push word ptr [bp - 0xe]
01a4 push word ptr [bp - 0xa]
01a7 push word ptr [bp - 6]
01aa push word ptr [bp - 8]
01ad push word ptr [bp - 4]
01b0 nop 
01b1 push cs
01b2 call 0x2f4a ; _AddAntToBList
01b5 jmp 0x6a1b
01b7 nop 
01b8 mov es, word ptr [0xc480]
01bc cmp word ptr es:[0x72cc], 0x1f4
01c3 jge 0x6a21
01c5 push word ptr [bp - 0xe]
01c8 push word ptr [bp - 0xa]
01cb push word ptr [bp - 6]
01ce push word ptr [bp - 8]
01d1 push word ptr [bp - 4]
01d4 nop 
01d5 push cs
01d6 call 0x2fa4 ; _AddAntToRList
01d9 add sp, 0xa
01dc mov si, 1
01df cmp si, 1
01e2 jne 0x6a3a
01e4 push word ptr [bp - 6]
01e7 push word ptr [bp - 8]
01ea push word ptr [bp - 4]
01ed push word ptr [bp - 0xc]
01f0 nop 
01f1 push cs
01f2 call 0x5d18 ; _SetLife
01f5 add sp, 8
01f8 or si, si
01fa jne 0x6a41
01fc jmp 0x737f
01ff cmp word ptr [0xcc84], 0x60 ; _MeType
0204 je 0x6a4b
0206 jmp 0x6b1f
0209 mov es, word ptr [0xc47a]
020d mov bx, word ptr [0xcf50] ; _MeDir
0211 xor bl, 4
0214 mov al, byte ptr es:[bx]
0219 cwde 
021a add ax, word ptr [0xcd88] ; _MeLocX
021e mov word ptr [bp - 2], ax
0221 mov es, word ptr [0xc478]
0225 mov al, byte ptr es:[bx + 8]
022a cwde 
022b add ax, word ptr [0xce7e] ; _MeLocY
022f mov word ptr [bp - 4], ax
0232 xor si, si
0234 mov ax, word ptr [0xce80] ; _MePlane
0237 mov word ptr [bp - 8], ax
023a cmp ax, 1
023d jg 0x6aa6
023f mov es, word ptr [0xc47c]
0243 cmp word ptr es:[0x80f0], 0x3e8
024a jge 0x6afb
024c push si
024d push word ptr [bp - 0xa]
0250 mov ax, word ptr [bp - 6]
0253 add ax, 8
0256 push ax
0257 push word ptr [bp - 4]
025a push word ptr [bp - 2]
025d nop 
025e push cs
025f call 0x2ef0 ; _AddAntToAList
0262 jmp 0x6af5
0264 cmp word ptr [bp - 8], 2
0268 jne 0x6ad2
026a mov es, word ptr [0xc47e]
026e cmp word ptr es:[0x99d4], 0x1f4
0275 jge 0x6afb
0277 push si
0278 push word ptr [bp - 0xa]
027b mov ax, word ptr [bp - 6]
027e add ax, 8
0281 push ax
0282 push word ptr [bp - 4]
0285 push word ptr [bp - 2]
0288 nop 
0289 push cs
028a call 0x2f4a ; _AddAntToBList
028d jmp 0x6af5
028f nop 
0290 mov es, word ptr [0xc480]
0294 cmp word ptr es:[0x72cc], 0x1f4
029b jge 0x6afb
029d push si
029e push word ptr [bp - 0xa]
02a1 mov ax, word ptr [bp - 6]
02a4 add ax, 8
02a7 push ax
02a8 push word ptr [bp - 4]
02ab push word ptr [bp - 2]
02ae nop 
02af push cs
02b0 call 0x2fa4 ; _AddAntToRList
02b3 add sp, 0xa
02b6 mov si, 1
02b9 cmp si, 1
02bc jne 0x6b18
02be mov ax, word ptr [bp - 6]
02c1 add ax, 8
02c4 push ax
02c5 push word ptr [bp - 4]
02c8 push word ptr [bp - 2]
02cb push word ptr [bp - 8]
02ce nop 
02cf push cs
02d0 call 0x5d18 ; _SetLife
02d3 add sp, 8
02d6 or si, si
02d8 jne 0x6b1f
02da jmp 0x737f
02dd mov ax, word ptr [0xce80] ; _MePlane
02e0 mov word ptr [bp - 2], ax
02e3 mov si, word ptr [0xcd88] ; _MeLocX
02e7 mov di, word ptr [0xce7e] ; _MeLocY
02eb mov ax, word ptr [0xcc84] ; _MeType
02ee mov word ptr [bp - 6], ax
02f1 mov ax, word ptr [0xcf50] ; _MeDir
02f4 mov word ptr [bp - 4], ax
02f7 cmp word ptr [bp - 2], 1
02fb jg 0x6b56
02fd or si, si
02ff jl 0x6b68
0301 cmp si, 0x7f
0304 jg 0x6b68
0306 or di, di
0308 jl 0x6b68
030a cmp di, 0x3f
030d jg 0x6b68
030f mov dx, 1
0312 jmp 0x6b6a
0314 or si, si
0316 jl 0x6b68
0318 cmp si, 0x3f
031b jg 0x6b68
031d or di, di
031f jl 0x6b68
0321 cmp di, 0x3f
0324 jle 0x6b51
0326 xor dx, dx
0328 dec dx
0329 jne 0x6baf
032b push 0
032d push di
032e push si
032f push word ptr [bp - 2]
0332 nop 
0333 push cs
0334 call 0x5d18 ; _SetLife
0337 add sp, 8
033a cmp word ptr [bp - 6], 0x60
033e jne 0x6baf
0340 push 0
0342 mov es, word ptr [0xc478]
0346 mov bx, word ptr [bp - 4]
0349 xor bl, 4
034c mov al, byte ptr es:[bx + 8]
0351 cwde 
0352 add ax, di
0354 push ax
0355 mov es, word ptr [0xc47a]
0359 mov al, byte ptr es:[bx]
035e cwde 
035f add ax, si
0361 push ax
0362 push word ptr [bp - 2]
0365 nop 
0366 push cs
0367 call 0x5d18 ; _SetLife
036a add sp, 8
036d mov es, word ptr [0xc490]
0371 mov word ptr es:[0x7a5e], 0xfffe
0378 mov ax, word ptr [0xac7c] ; _SpidX
037b sar ax, 4
037e mov es, word ptr [0xc492]
0382 mov word ptr es:[0x78b8], ax
0386 mov cx, word ptr [0xac7e] ; _SpidY
038a sar cx, 4
038d mov es, word ptr [0xc494]
0391 mov word ptr es:[0x78ea], cx
0396 mov es, word ptr [0xc48a]
039a mov word ptr es:[0x9fe8], 1
03a1 xor dx, dx
03a3 mov es, word ptr [0xc496]
03a7 mov word ptr es:[0x729e], dx
03ac mov es, word ptr [0xc498]
03b0 mov word ptr es:[0x7d60], dx
03b5 mov word ptr [0xce98], dx ; _MeColor
03b9 push cx
03ba push ax
03bb push word ptr [bp + 6]
03be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 961, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ResetYellowVars
03c3 add sp, 6
03c6 sub ax, ax
03c8 add ax, 0x64
03cb mov word ptr [0xac8a], ax ; _MeHealth
03ce mov es, word ptr [0xc49c]
03d2 mov word ptr es:[0x9cf0], 0
03d9 mov bx, ax
03db mov es, word ptr [0xc49e]
03df cmp word ptr es:[0x9bec], bx
03e4 jge 0x6c3c
03e6 cmp bx, 0xa
03e9 jl 0x6c3c
03eb mov es, word ptr [0xc4a0]
03ef mov word ptr es:[0x9af2], 0
03f6 jmp 0x756e
03f9 nop 
03fa mov es, word ptr [0xc4a0]
03fe mov word ptr es:[0x9af2], 1
0405 jmp 0x756e
0408 cmp word ptr [bp + 6], 0
040c jne 0x6c56
040e mov dx, 1
0411 jmp 0x6c59
0413 nop 
0414 mov dx, word ptr [bp + 6]
0417 cmp word ptr [0xce80], dx ; _MePlane
041b jne 0x6c64
041d mov bx, 1
0420 jmp 0x6c66
0422 xor bx, bx
0424 or bx, bx
0426 jne 0x6c72
0428 xor dx, dx
042a mov si, word ptr [bp + 8]
042d jmp 0x6cb9
042f nop 
0430 mov es, word ptr [0xc48a]
0434 cmp word ptr es:[0x9fe8], 1
043a jne 0x6cd0
043c mov si, word ptr [bp + 8]
043f cmp word ptr [bp + 6], 1
0443 jle 0x6c8a
0445 jmp 0x6d20
0448 push word ptr [0xac7e] ; _SpidY
044c push word ptr [0xac7c] ; _SpidX
0450 mov ax, word ptr [bp + 0xa]
0453 shl ax, 4
0456 add ax, 8
0459 push ax
045a mov ax, si
045c shl ax, 4
045f add ax, 8
0462 push ax
0463 nop 
0464 push cs
0465 call 0x1122 ; _GetDis
0468 add sp, 8
046b or dx, dx
046d jne 0x6d20
046f cmp ax, 0x200
0472 jae 0x6d20
0474 mov dx, 1
0477 or dx, dx
0479 je 0x6cc0
047b jmp 0x756e
047e cmp word ptr [bp - 0x10], 0xff
0483 je 0x6d24
0485 cmp word ptr [bp - 0x10], 0xfe
048a je 0x6d24
048c jmp 0x6d27
048e mov si, word ptr [bp + 8]
0491 mov ax, word ptr [bp + 6]
0494 or ax, ax
0496 jl 0x6ce5
0498 jo 0x6ce5
049a dec ax
049b jle 0x6cea
049d dec ax
049e je 0x6cf8
04a0 dec ax
04a1 je 0x6d06
04a3 mov dx, word ptr [bp - 2]
04a6 jmp 0x6d14
04a8 mov bx, word ptr [bp + 0xa]
04ab mov di, si
04ad shl di, 6
04b0 mov dl, byte ptr [bx + di + 0x68e8]
04b4 jmp 0x6d12
04b6 mov bx, word ptr [bp + 0xa]
04b9 mov di, si
04bb shl di, 6
04be mov dl, byte ptr [bx + di - 0x7718]
04c2 jmp 0x6d12
04c4 mov bx, word ptr [bp + 0xa]
04c7 mov di, si
04c9 shl di, 6
04cc mov dl, byte ptr [bx + di - 0x6718]
04d0 sub dh, dh
04d2 cmp dx, 0xff
04d6 je 0x6cb6
04d8 cmp dx, 0xfe
04dc je 0x6cb6
04de xor dx, dx
04e0 jmp 0x6cb9
04e2 mov dx, 1
04e5 or dx, dx
04e7 je 0x6d2e
04e9 jmp 0x756e
04ec mov al, byte ptr [bp - 0x10]
04ef and ax, 0x78
04f2 sar ax, 3
04f5 mov word ptr [bp - 0x14], ax
04f8 cmp ax, 0xc
04fb je 0x6d42
04fd jmp 0x6df2
0500 mov es, word ptr [0xc47a]
0504 mov bl, byte ptr [bp - 0x10]
0507 xor bl, 0xfc
050a and bx, 7
050d mov al, byte ptr es:[bx]
0512 cwde 
0513 mov cx, ax
0515 add cx, si
0517 mov es, word ptr [0xc478]
051b mov al, byte ptr es:[bx + 8]
0520 cwde 
0521 mov di, ax
0523 add di, word ptr [bp + 0xa]
0526 mov word ptr [bp - 2], 0xffff
052b cmp word ptr [bp + 6], 1
052f jg 0x6d8a
0531 or cx, cx
0533 jl 0x6d9c
0535 cmp cx, 0x7f
0538 jg 0x6d9c
053a or di, di
053c jl 0x6d9c
053e cmp di, 0x3f
0541 jg 0x6d9c
0543 mov dx, 1
0546 jmp 0x6d9c
0548 or cx, cx
054a jl 0x6d9c
054c cmp cx, 0x3f
054f jg 0x6d9c
0551 or di, di
0553 jl 0x6d9c
0555 cmp di, 0x3f
0558 jle 0x6d85
055a mov word ptr [bp - 0x18], cx
055d mov word ptr [bp - 0x1a], di
0560 dec dx
0561 je 0x6daa
0563 mov dx, word ptr [bp - 2]
0566 jmp 0x6dc6
0568 mov ax, word ptr [bp + 6]
056b or ax, ax
056d jl 0x6dbc
056f jo 0x6dbc
0571 dec ax
0572 jle 0x6dcc
0574 dec ax
0575 je 0x6dda
0577 dec ax
0578 je 0x6de6
057a mov dx, word ptr [bp - 2]
057d or dx, dx
057f jne 0x6dc6
0581 mov dx, 0xffff
0584 mov word ptr [bp - 0x16], dx
0587 jmp 0x6eaf
058a mov bx, cx
058c shl bx, 6
058f mov dl, byte ptr [bx + di + 0x68e8]
0593 sub dh, dh
0595 jmp 0x6dbf
0597 nop 
0598 mov bx, cx
059a shl bx, 6
059d mov dl, byte ptr [bx + di - 0x7718]
05a1 jmp 0x6dd5
05a3 nop 
05a4 mov bx, cx
05a6 shl bx, 6
05a9 mov dl, byte ptr [bx + di - 0x6718]
05ad jmp 0x6dd5
05af nop 
05b0 cmp ax, 0xd
05b3 je 0x6dfa
05b5 jmp 0x6eaf
05b8 mov word ptr [bp - 0x18], si
05bb mov ax, word ptr [bp + 0xa]
05be mov word ptr [bp - 0x1a], ax
05c1 mov ax, word ptr [bp - 0x10]
05c4 mov word ptr [bp - 0x16], ax
05c7 mov bx, ax
05c9 and bx, 7
05cc mov es, word ptr [0xc47a]
05d0 mov al, byte ptr es:[bx]
05d5 cwde 
05d6 add si, ax
05d8 mov es, word ptr [0xc478]
05dc mov al, byte ptr es:[bx + 8]
05e1 cwde 
05e2 add word ptr [bp + 0xa], ax
05e5 mov cx, 0xffff
05e8 cmp word ptr [bp + 6], 1
05ec jg 0x6e4a
05ee or si, si
05f0 jl 0x6e5e
05f2 cmp si, 0x7f
05f5 jg 0x6e5e
05f7 cmp word ptr [bp + 0xa], dx
05fa jl 0x6e5e
05fc cmp word ptr [bp + 0xa], 0x3f
0600 jg 0x6e5e
0602 mov dx, 1
0605 jmp 0x6e5e
0607 nop 
0608 or si, si
060a jl 0x6e5e
060c cmp si, 0x3f
060f jg 0x6e5e
0611 cmp word ptr [bp + 0xa], dx
0614 jl 0x6e5e
0616 cmp word ptr [bp + 0xa], 0x3f
061a jle 0x6e44
061c dec dx
061d jne 0x6ea7
061f mov ax, word ptr [bp + 6]
0622 or ax, ax
0624 jl 0x6ea0
0626 jo 0x6ea0
0628 dec ax
0629 jle 0x6e76
062b dec ax
062c je 0x6e84
062e dec ax
062f je 0x6e92
0631 jmp 0x6ea0
0633 nop 
0634 mov bx, word ptr [bp + 0xa]
0637 mov di, si
0639 shl di, 6
063c mov cl, byte ptr [bx + di + 0x68e8]
0640 jmp 0x6e9e
0642 mov bx, word ptr [bp + 0xa]
0645 mov di, si
0647 shl di, 6
064a mov cl, byte ptr [bx + di - 0x7718]
064e jmp 0x6e9e
0650 mov bx, word ptr [bp + 0xa]
0653 mov di, si
0655 shl di, 6
0658 mov cl, byte ptr [bx + di - 0x6718]
065c sub ch, ch
065e or cx, cx
0660 jne 0x6ea7
0662 mov cx, 0xffff
0665 mov word ptr [bp - 0x10], cx
0668 mov word ptr [bp - 0x14], 0xc
066d cmp word ptr [bp + 6], 1
0671 jg 0x6ed8
0673 mov es, word ptr [0xc47c]
0677 mov cx, word ptr es:[0x80f0]
067c mov ax, 0x23a4
067f mov <resolved loader operand; see bindings> ; [{'operand_offset': 1664, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0682 mov bx, ax
0684 mov word ptr [bp - 0xc], dx
0687 mov word ptr [bp - 6], 0x278e
068c mov word ptr [bp - 4], dx
068f mov word ptr [bp - 0xa], 0x2f62
0694 jmp 0x6f23
0696 cmp word ptr [bp + 6], 2
069a jne 0x6f02
069c mov es, word ptr [0xc47e]
06a0 mov cx, word ptr es:[0x99d4]
06a5 mov ax, 0x3736
06a8 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1705, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
06ab mov bx, ax
06ad mov word ptr [bp - 0xc], dx
06b0 mov word ptr [bp - 6], 0x392c
06b5 mov word ptr [bp - 4], dx
06b8 mov word ptr [bp - 0xa], 0x3d18
06bd jmp 0x6f23
06bf nop 
06c0 mov es, word ptr [0xc480]
06c4 mov cx, word ptr es:[0x72cc]
06c9 mov ax, 0x4104
06cc mov <resolved loader operand; see bindings> ; [{'operand_offset': 1741, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
06cf mov bx, ax
06d1 mov word ptr [bp - 0xc], dx
06d4 mov word ptr [bp - 6], 0x42fa
06d9 mov word ptr [bp - 4], dx
06dc mov word ptr [bp - 0xa], 0x46e6
06e1 mov word ptr [bp - 8], dx
06e4 mov word ptr [bp + 8], si
06e7 mov dx, cx
06e9 dec dx
06ea mov word ptr [bp - 2], dx
06ed or dx, dx
06ef jl 0x6f68
06f1 mov word ptr [bp - 0xe], bx
06f4 mov si, dx
06f6 mov di, word ptr [bp + 8]
06f9 mov cx, word ptr [bp + 0xa]
06fc mov ds, word ptr [bp - 0xc]
06ff mov bx, word ptr [bp - 0xe]
0702 add bx, si
0704 mov al, byte ptr [bx]
0706 sub ah, ah
0708 cmp ax, di
070a jne 0x6fa0
070c les bx, ptr [bp - 6]
070f mov al, byte ptr es:[bx + si]
0712 cmp ax, cx
0714 jne 0x6fa0
0716 les bx, ptr [bp - 0xa]
0719 mov al, byte ptr es:[bx + si]
071c cmp ax, word ptr [bp - 0x10]
071f jne 0x6fa0
0721 push ss
0722 pop ds
0723 jmp 0x6f6a
0725 nop 
0726 mov si, dx
0728 mov word ptr [bp - 0x12], si
072b cmp word ptr [bp - 0x14], 0xc
072f je 0x6f76
0731 jmp 0x7038
0734 cmp word ptr [bp + 6], 1
0738 jg 0x6fa6
073a mov es, word ptr [0xc47c]
073e mov bx, word ptr es:[0x80f0]
0743 mov ax, 0x23a4
0746 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1863, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0749 mov si, ax
074b mov word ptr [bp - 0xc], cx
074e mov word ptr [bp - 6], 0x278e
0753 mov word ptr [bp - 4], cx
0756 mov word ptr [bp - 0xa], 0x2f62
075b jmp 0x6ff1
075d nop 
075e dec si
075f jns 0x6f41
0761 jmp 0x6f63
0763 nop 
0764 cmp word ptr [bp + 6], 2
0768 jne 0x6fd0
076a mov es, word ptr [0xc47e]
076e mov bx, word ptr es:[0x99d4]
0773 mov ax, 0x3736
0776 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1911, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0779 mov si, ax
077b mov word ptr [bp - 0xc], cx
077e mov word ptr [bp - 6], 0x392c
0783 mov word ptr [bp - 4], cx
0786 mov word ptr [bp - 0xa], 0x3d18
078b jmp 0x6ff1
078d nop 
078e mov es, word ptr [0xc480]
0792 mov bx, word ptr es:[0x72cc]
0797 mov ax, 0x4104
079a mov <resolved loader operand; see bindings> ; [{'operand_offset': 1947, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
079d mov si, ax
079f mov word ptr [bp - 0xc], cx
07a2 mov word ptr [bp - 6], 0x42fa
07a7 mov word ptr [bp - 4], cx
07aa mov word ptr [bp - 0xa], 0x46e6
07af mov word ptr [bp - 8], cx
07b2 lea dx, [bx - 1]
07b5 or dx, dx
07b7 jl 0x7035
07b9 mov word ptr [bp - 0xe], si
07bc mov word ptr [bp - 2], dx
07bf mov si, dx
07c1 mov cx, word ptr [bp - 0x18]
07c4 mov di, word ptr [bp - 0x1a]
07c7 mov ds, word ptr [bp - 0xc]
07ca mov bx, word ptr [bp - 0xe]
07cd add bx, si
07cf mov al, byte ptr [bx]
07d1 sub ah, ah
07d3 cmp ax, cx
07d5 jne 0x7082
07d7 les bx, ptr [bp - 6]
07da mov al, byte ptr es:[bx + si]
07dd cmp ax, di
07df jne 0x7082
07e1 les bx, ptr [bp - 0xa]
07e4 mov al, byte ptr es:[bx + si]
07e7 cmp ax, word ptr [bp - 0x16]
07ea jne 0x7082
07ec mov word ptr [bp - 2], si
07ef mov dx, si
07f1 push ss
07f2 pop ds
07f3 mov word ptr [bp - 4], dx
07f6 cmp word ptr [bp - 0x12], 0
07fa jge 0x7041
07fc jmp 0x737f
07ff mov es, word ptr [0xc48a]
0803 cmp word ptr es:[0x9fe8], 0
0809 je 0x7050
080b jmp 0x7390
080e mov si, word ptr [0xcc84] ; _MeType
0812 and si, 0x78
0815 sar si, 3
0818 mov word ptr [bp - 0xe], 0
081d test byte ptr [0xcc84], 8 ; _MeType
0822 je 0x7094
0824 cmp si, 5
0827 je 0x7088
0829 cmp si, 9
082c je 0x7088
082e cmp si, 1
0831 jne 0x7094
0833 mov es, word ptr [0xc48c]
0837 mov ax, word ptr es:[0x8a6a]
083b mov word ptr [bp - 0xe], ax
083e jmp 0x7094
0840 dec si
0841 jns 0x700c
0843 jmp 0x702e
0845 nop 
0846 mov es, word ptr [0xc48e]
084a mov al, byte ptr es:[si + 0x94]
084f cwde 
0850 mov si, ax
0852 shl si, 3
0855 mov al, byte ptr [bp - 0x10]
0858 and ax, 0x80
085b or si, ax
085d or si, word ptr [0xcf50] ; _MeDir
0861 mov word ptr [bp - 6], si
0864 or ax, ax
0866 je 0x70ad
0868 jmp 0x737f
086b mov dl, byte ptr [bp - 0x10]
086e and dx, 0x78
0871 sar dx, 3
0874 or dx, dx
0876 jg 0x70bd
0878 jmp 0x737f
087b cmp dx, 0xd
087e jle 0x70c5
0880 jmp 0x737f
0883 cmp dx, 0xa
0886 jne 0x70cd
0888 jmp 0x737f
088b cmp dx, 0xb
088e jne 0x70d5
0890 jmp 0x737f
0893 cmp dx, 5
0896 je 0x7116
0898 cmp dx, 9
089b je 0x7116
089d dec dx
089e jne 0x7137
08a0 lea ax, [bp - 0x1c]
08a3 push ss
08a4 push ax
08a5 lea cx, [bp - 0x1e]
08a8 push ss
08a9 push cx
08aa lea cx, [bp - 0x20]
08ad push ss
08ae push cx
08af lea cx, [bp - 0x22]
08b2 push ss
08b3 push cx
08b4 lea cx, [bp - 0x24]
08b7 push ss
08b8 push cx
08b9 push word ptr [bp - 0x12]
08bc push word ptr [bp + 6]
08bf nop 
08c0 push cs
08c1 call 0x573c ; _GetAntIndex
08c4 add sp, 0x18
08c7 mov ax, word ptr [bp - 0x1c]
08ca mov es, word ptr [0xc48c]
08ce mov word ptr es:[0x8a6a], ax
08d2 jmp 0x7137
08d4 mov es, word ptr [0xc48e]
08d8 mov bl, byte ptr [bp - 0x10]
08db and bx, 0x78
08de sar bx, 3
08e1 mov al, byte ptr es:[bx + 0x94]
08e6 cwde 
08e7 shl ax, 3
08ea mov cl, byte ptr [bp - 0x10]
08ed and cx, 7
08f0 or ax, cx
08f2 mov word ptr [bp - 0x10], ax
08f5 cmp word ptr [0xcc84], 0x60 ; _MeType
08fa jne 0x7144
08fc mov ax, 9
08ff jmp 0x7146
0901 nop 
0902 xor ax, ax
0904 mov word ptr [bp - 0xa], ax
0907 push word ptr [0xce7e] ; _MeLocY
090b push word ptr [0xcd88] ; _MeLocX
090f push word ptr [0xce80] ; _MePlane
0913 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0918 add sp, 6
091b cmp word ptr [bp - 0xa], 0
091f je 0x7194
0921 mov es, word ptr [0xc478]
0925 mov bx, word ptr [0xcf50] ; _MeDir
0929 xor bl, 4
092c mov al, byte ptr es:[bx + 8]
0931 cwde 
0932 add ax, word ptr [0xce7e] ; _MeLocY
0936 push ax
0937 mov es, word ptr [0xc47a]
093b mov al, byte ptr es:[bx]
0940 cwde 
0941 add ax, word ptr [0xcd88] ; _MeLocX
0945 push ax
0946 push word ptr [0xce80] ; _MePlane
094a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2381, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
094f add sp, 6
0952 push word ptr [bp + 0xa]
0955 push word ptr [bp + 8]
0958 push word ptr [bp + 6]
095b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2398, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0960 add sp, 6
0963 cmp word ptr [bp - 0x14], 0xc
0967 jne 0x71bc
0969 push word ptr [bp - 0x1a]
096c push word ptr [bp - 0x18]
096f push word ptr [bp + 6]
0972 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2421, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
0977 add sp, 6
097a push 0
097c push 0
097e push 0
0980 push 0
0982 push 0
0984 push word ptr [bp - 0x12]
0987 push word ptr [bp + 6]
098a nop 
098b push cs
098c call 0x584a ; _SetAntIndex
098f add sp, 0xe
0992 cmp word ptr [bp - 0x14], 0xc
0996 jne 0x71f2
0998 push 0
099a push 0
099c push 0
099e push 0
09a0 push 0
09a2 push word ptr [bp - 4]
09a5 push word ptr [bp + 6]
09a8 nop 
09a9 push cs
09aa call 0x584a ; _SetAntIndex
09ad add sp, 0xe
09b0 mov ax, word ptr [0xcd88] ; _MeLocX
09b3 mov word ptr [bp - 2], ax
09b6 mov ax, word ptr [0xce7e] ; _MeLocY
09b9 mov word ptr [bp - 4], ax
09bc xor di, di
09be mov ax, word ptr [0xce80] ; _MePlane
09c1 mov word ptr [bp - 8], ax
09c4 cmp ax, 1
09c7 jg 0x722e
09c9 mov es, word ptr [0xc47c]
09cd cmp word ptr es:[0x80f0], 0x3e8
09d4 jge 0x727f
09d6 push word ptr [bp - 0xe]
09d9 push word ptr [bp - 0xa]
09dc push word ptr [bp - 6]
09df push word ptr [bp - 4]
09e2 push word ptr [bp - 2]
09e5 nop 
09e6 push cs
09e7 call 0x2ef0 ; _AddAntToAList
09ea jmp 0x7279
09ec cmp word ptr [bp - 8], 2
09f0 jne 0x7258
09f2 mov es, word ptr [0xc47e]
09f6 cmp word ptr es:[0x99d4], 0x1f4
09fd jge 0x727f
09ff push word ptr [bp - 0xe]
0a02 push word ptr [bp - 0xa]
0a05 push word ptr [bp - 6]
0a08 push word ptr [bp - 4]
0a0b push word ptr [bp - 2]
0a0e nop 
0a0f push cs
0a10 call 0x2f4a ; _AddAntToBList
0a13 jmp 0x7279
0a15 nop 
0a16 mov es, word ptr [0xc480]
0a1a cmp word ptr es:[0x72cc], 0x1f4
0a21 jge 0x727f
0a23 push word ptr [bp - 0xe]
0a26 push word ptr [bp - 0xa]
0a29 push word ptr [bp - 6]
0a2c push word ptr [bp - 4]
0a2f push word ptr [bp - 2]
0a32 nop 
0a33 push cs
0a34 call 0x2fa4 ; _AddAntToRList
0a37 add sp, 0xa
0a3a mov di, 1
0a3d cmp di, 1
0a40 jne 0x7298
0a42 push word ptr [bp - 6]
0a45 push word ptr [bp - 4]
0a48 push word ptr [bp - 2]
0a4b push word ptr [bp - 8]
0a4e nop 
0a4f push cs
0a50 call 0x5d18 ; _SetLife
0a53 add sp, 8
0a56 or di, di
0a58 jne 0x729f
0a5a jmp 0x737f
0a5d cmp word ptr [0xcc84], 0x60 ; _MeType
0a62 je 0x72a9
0a64 jmp 0x7386
0a67 mov si, word ptr [0xcf50] ; _MeDir
0a6b mov es, word ptr [0xc47a]
0a6f mov bx, si
0a71 xor bl, 4
0a74 mov al, byte ptr es:[bx]
0a79 cwde 
0a7a add ax, word ptr [0xcd88] ; _MeLocX
0a7e mov word ptr [bp - 2], ax
0a81 mov es, word ptr [0xc478]
0a85 mov al, byte ptr es:[bx + 8]
0a8a cwde 
0a8b add ax, word ptr [0xce7e] ; _MeLocY
0a8f mov word ptr [bp - 4], ax
0a92 xor di, di
0a94 mov ax, word ptr [0xce80] ; _MePlane
0a97 mov word ptr [bp - 8], ax
0a9a cmp ax, 1
0a9d jg 0x7306
0a9f mov es, word ptr [0xc47c]
0aa3 cmp word ptr es:[0x80f0], 0x3e8
0aaa jge 0x735e
0aac push di
0aad push word ptr [bp - 0xa]
0ab0 mov ax, word ptr [bp - 6]
0ab3 add ax, 8
0ab6 push ax
0ab7 push word ptr [bp - 4]
0aba push word ptr [bp - 2]
0abd nop 
0abe push cs
0abf call 0x2ef0 ; _AddAntToAList
0ac2 jmp 0x7358
0ac4 mov word ptr [bp - 0xc], di
0ac7 cmp word ptr [bp - 8], 2
0acb jne 0x7334
0acd mov es, word ptr [0xc47e]
0ad1 cmp word ptr es:[0x99d4], 0x1f4
0ad8 jge 0x735e
0ada push di
0adb push word ptr [bp - 0xa]
0ade mov ax, word ptr [bp - 6]
0ae1 add ax, 8
0ae4 push ax
0ae5 push word ptr [bp - 4]
0ae8 push word ptr [bp - 2]
0aeb nop 
0aec push cs
0aed call 0x2f4a ; _AddAntToBList
0af0 jmp 0x7358
0af2 mov es, word ptr [0xc480]
0af6 cmp word ptr es:[0x72cc], 0x1f4
0afd jge 0x735e
0aff push 0
0b01 push word ptr [bp - 0xa]
0b04 mov ax, word ptr [bp - 6]
0b07 add ax, 8
0b0a push ax
0b0b push word ptr [bp - 4]
0b0e push word ptr [bp - 2]
0b11 nop 
0b12 push cs
0b13 call 0x2fa4 ; _AddAntToRList
0b16 add sp, 0xa
0b19 mov di, 1
0b1c cmp di, 1
0b1f jne 0x737b
0b21 mov ax, word ptr [bp - 6]
0b24 add ax, 8
0b27 push ax
0b28 push word ptr [bp - 4]
0b2b push word ptr [bp - 2]
0b2e push word ptr [bp - 8]
0b31 nop 
0b32 push cs
0b33 call 0x5d18 ; _SetLife
0b36 add sp, 8
0b39 or di, di
0b3b jne 0x7386
0b3d xor ax, ax
0b3f pop si
0b40 pop di
0b41 leave 
0b42 retf 
0b43 nop 
0b44 mov si, word ptr [bp - 0x10]
0b47 mov di, word ptr [bp + 6]
0b4a jmp 0x7449
0b4d nop 
0b4e mov si, word ptr [bp - 0x10]
0b51 test si, 0x80
0b55 jne 0x737f
0b57 mov dx, si
0b59 and dx, 0x78
0b5c sar dx, 3
0b5f or dx, dx
0b61 jle 0x737f
0b63 cmp dx, 0xd
0b66 jg 0x737f
0b68 cmp dx, 0xa
0b6b je 0x737f
0b6d cmp dx, 0xb
0b70 je 0x737f
0b72 cmp dx, 5
0b75 je 0x73f6
0b77 cmp dx, 9
0b7a je 0x73f6
0b7c mov di, word ptr [bp + 6]
0b7f dec dx
0b80 jne 0x7417
0b82 lea ax, [bp - 0x1c]
0b85 push ss
0b86 push ax
0b87 lea cx, [bp - 0x1e]
0b8a push ss
0b8b push cx
0b8c lea cx, [bp - 0x20]
0b8f push ss
0b90 push cx
0b91 lea cx, [bp - 0x22]
0b94 push ss
0b95 push cx
0b96 lea cx, [bp - 0x24]
0b99 push ss
0b9a push cx
0b9b push word ptr [bp - 0x12]
0b9e push di
0b9f nop 
0ba0 push cs
0ba1 call 0x573c ; _GetAntIndex
0ba4 add sp, 0x18
0ba7 mov ax, word ptr [bp - 0x1c]
0baa mov es, word ptr [0xc48c]
0bae mov word ptr es:[0x8a6a], ax
0bb2 jmp 0x7417
0bb4 mov di, word ptr [bp + 6]
0bb7 mov bx, si
0bb9 and bx, 0x78
0bbc sar bx, 3
0bbf mov es, word ptr [0xc48e]
0bc3 mov al, byte ptr es:[bx + 0x94]
0bc8 cwde 
0bc9 shl ax, 3
0bcc mov cx, si
0bce and cx, 7
0bd1 or ax, cx
0bd3 mov si, ax
0bd5 push 0
0bd7 push 0
0bd9 push 0
0bdb push 0
0bdd push 0
0bdf push word ptr [bp - 0x12]
0be2 push di
0be3 nop 
0be4 push cs
0be5 call 0x584a ; _SetAntIndex
0be8 add sp, 0xe
0beb cmp word ptr [bp - 0x14], 0xc
0bef jne 0x7449
0bf1 push 0
0bf3 push 0
0bf5 push 0
0bf7 push 0
0bf9 push 0
0bfb push word ptr [bp - 4]
0bfe push di
0bff nop 
0c00 push cs
0c01 call 0x584a ; _SetAntIndex
0c04 add sp, 0xe
0c07 mov ax, si
0c09 and ax, 0x80
0c0c mov word ptr ss:[0xce98], ax
0c10 xor ax, ax
0c12 mov word ptr ss:[0xcf54], ax
0c16 mov <resolved loader operand; see bindings> ; [{'operand_offset': 3095, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0c19 mov es, cx
0c1b mov word ptr es:[0x9fe8], ax
0c1f mov <resolved loader operand; see bindings> ; [{'operand_offset': 3104, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0c22 mov es, cx
0c24 mov word ptr es:[0x7d60], ax
0c28 add ax, 0x64
0c2b mov word ptr ss:[0xac8a], ax
0c2f mov <resolved loader operand; see bindings> ; [{'operand_offset': 3120, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0c32 mov es, ax
0c34 mov word ptr es:[0x9cf0], 0
0c3b mov <resolved loader operand; see bindings> ; [{'operand_offset': 3132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0c3e mov es, ax
0c40 mov ax, word ptr es:[0x9bec]
0c44 cmp word ptr ss:[0xac8a], ax
0c49 jle 0x74a4
0c4b cmp word ptr ss:[0xac8a], 0xa
0c51 jl 0x74a4
0c53 mov <resolved loader operand; see bindings> ; [{'operand_offset': 3156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0c56 mov es, ax
0c58 mov word ptr es:[0x9af2], 0
0c5f jmp 0x74b0
0c61 nop 
0c62 mov <resolved loader operand; see bindings> ; [{'operand_offset': 3171, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0c65 mov es, ax
0c67 mov word ptr es:[0x9af2], 1
0c6e cmp di, 1
0c71 jg 0x74d2
0c73 cmp word ptr [bp + 8], 0
0c77 jl 0x74ea
0c79 cmp word ptr [bp + 8], 0x7f
0c7d jg 0x74ea
0c7f cmp word ptr [bp + 0xa], 0
0c83 jl 0x74ea
0c85 cmp word ptr [bp + 0xa], 0x3f
0c89 jg 0x74ea
0c8b mov dx, 1
0c8e jmp 0x74ec
0c90 cmp word ptr [bp + 8], 0
0c94 jl 0x74ea
0c96 cmp word ptr [bp + 8], 0x3f
0c9a jg 0x74ea
0c9c cmp word ptr [bp + 0xa], 0
0ca0 jl 0x74ea
0ca2 cmp word ptr [bp + 0xa], 0x3f
0ca6 jle 0x74cd
0ca8 xor dx, dx
0caa dec dx
0cab jne 0x756a
0cad push ss
0cae pop ds
0caf push 0xff
0cb2 push word ptr [bp + 0xa]
0cb5 push word ptr [bp + 8]
0cb8 push di
0cb9 nop 
0cba push cs
0cbb call 0x5d18 ; _SetLife
0cbe add sp, 8
0cc1 mov ax, si
0cc3 and al, 0x78
0cc5 cmp al, 0x60
0cc7 jne 0x753b
0cc9 push 0xfe
0ccc mov bx, si
0cce xor bl, 0xfc
0cd1 and bx, 7
0cd4 mov es, word ptr [0xc478]
0cd8 mov al, byte ptr es:[bx + 8]
0cdd cwde 
0cde add ax, word ptr [bp + 0xa]
0ce1 push ax
0ce2 mov es, word ptr [0xc47a]
0ce6 mov al, byte ptr es:[bx]
0ceb cwde 
0cec add ax, word ptr [bp + 8]
0cef push ax
0cf0 push di
0cf1 nop 
0cf2 push cs
0cf3 call 0x5d18 ; _SetLife
0cf6 add sp, 8
0cf9 mov ax, word ptr [bp + 8]
0cfc mov word ptr [0xcd88], ax ; _MeLocX
0cff mov ax, word ptr [bp + 0xa]
0d02 mov word ptr [0xce7e], ax ; _MeLocY
0d05 mov ax, si
0d07 and ax, 7
0d0a mov word ptr [0xcf50], ax ; _MeDir
0d0d mov ax, si
0d0f and ax, 0x78
0d12 mov word ptr [0xcc84], ax ; _MeType
0d15 mov word ptr [0xce80], di ; _MePlane
0d19 cmp word ptr [0xcc84], 8 ; _MeType
0d1e jge 0x756e
0d20 mov ax, word ptr [0xcf50] ; _MeDir
0d23 mov word ptr [0xce92], ax ; _MeEgg
0d26 jmp 0x756e
0d28 push ss
0d29 pop ds
0d2a jmp 0x755b
0d2c mov ax, 1
0d2f pop si
0d30 pop di
0d31 leave 
0d32 retf 
```

## Known declaration examples

- `extern void far AddAntToAList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far AddAntToAList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far AddAntToBList(int life, int column, int attribute, int state, int direction);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern void far AddAntToBList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern void far AddAntToRList(int life, int column, int attribute, int state, int direction);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern void far AddAntToRList(int x, int y, int type, int a, int b);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_0000_GetDefendDir_2_scaffold-cdac288ff9.c
- `extern unsigned long far GetDis(int x1, int y1, int x2, int y2);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern int near MeColor;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeDir;` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near MeHealth;` — src/recovered/wf_SetMyHealth-5d15d1e8e5.c
- `extern int near MeHealth;` — src/recovered/wf_tu_antedit_A998_DrawYardData_2_scaffold-2f57d5cc12.c
- `extern int near MeHealth;` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
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
- `extern void far ResetYellowVars(int plane, int x, int y);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far SetAntIndex(int plane, int index, int a, int b, int c, int d, int e);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_SetQueenTail-103d1d54cd.c
- `extern void far SetLife(int plane, int x, int y, int type);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int near SpidX;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near SpidX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near SpidX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern int near SpidY;` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near SpidY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near SpidY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_AddWater-d30012f385.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_GetDis'], 'segment': 5, 'target_offset': 4386, 'caller_offsets': [197, 1125]}
- {'callee_names': ['_AddAntToAList'], 'segment': 5, 'target_offset': 12016, 'caller_offsets': [392, 607, 2535, 2751]}
- {'callee_names': ['_AddAntToBList'], 'segment': 5, 'target_offset': 12106, 'caller_offsets': [434, 650, 2576, 2797]}
- {'callee_names': ['_AddAntToRList'], 'segment': 5, 'target_offset': 12196, 'caller_offsets': [470, 688, 2612, 2835]}
- {'callee_names': ['_GetAntIndex'], 'segment': 5, 'target_offset': 22332, 'caller_offsets': [2241, 2977]}
- {'callee_names': ['_SetAntIndex'], 'segment': 5, 'target_offset': 22602, 'caller_offsets': [2444, 2474, 3045, 3073]}
- {'callee_names': ['_SetLife'], 'segment': 5, 'target_offset': 23832, 'caller_offsets': [498, 720, 820, 871, 2640, 2867, 3259, 3315]}

## Neighbors

- {'symbol': '_EndLifeTransferMode', 'offset': 26510, 'source': 'src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c', 'size': 29}
- {'symbol': '_ExchangeLives', 'offset': 26540, 'source': 'src/recovered/wf_tu_simone_5AD2_AddAntToList_19_scaffold-42b0ff79cd.c', 'size': 149}
- {'symbol': '_DropMyFood', 'offset': 30070, 'source': None, 'size': 1093}
- {'symbol': '_DropPebble', 'offset': 31164, 'source': None, 'size': 662}
