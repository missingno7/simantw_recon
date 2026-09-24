# Recovery task _myBeginSong

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 4110 bytes.

```asm
0000 enter 0x150, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xbf78]
000a cmp word ptr es:[0x8d06], 0
0010 jne 0x85a3
0012 jmp 0x9598
0015 cmp word ptr [0xaf6], 0 ; _songsOnFlag
001a jne 0x85ad
001c jmp 0x9598
001f mov di, word ptr [bp + 6]
0022 push di
0023 push ds
0024 push 0xdef
0027 nop 
0028 push cs
0029 call 0x62bc ; _WinPrintf
002c add sp, 6
002f push 1
0031 push 0x12
0033 push di
0034 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 55, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0039 add sp, 6
003c mov si, ax
003e or si, si
0040 jne 0x85d3
0042 jmp 0x9598
0045 push si
0046 nop 
0047 push cs
0048 call 0x558e ; _mem_Lock
004b add sp, 2
004e mov es, dx
0050 mov bx, ax
0052 push word ptr es:[bx]
0055 mov word ptr [bp - 0x136], bx
0059 mov word ptr [bp - 0x134], es
005d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipWord
0062 add sp, 2
0065 mov word ptr [bp - 0xe], ax
0068 les bx, ptr [bp - 0x136]
006c push word ptr es:[bx + 6]
0070 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 115, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipWord
0075 add sp, 2
0078 mov word ptr [bp - 0x16], ax
007b mov word ptr [bp - 4], 0
0080 mov es, word ptr [0xbf7a]
0084 cmp word ptr es:[0x8da6], -1
008a je 0x863e
008c mov word ptr [bp - 6], si
008f mov dx, 0x8da6
0092 mov word ptr [bp - 2], dx
0095 mov si, dx
0097 mov di, word ptr [bp - 4]
009a mov cx, word ptr [bp + 6]
009d mov <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00a0 mov ds, ax
00a2 cmp word ptr [si], cx
00a4 je 0x8637
00a6 jmp 0x8794
00a9 mov si, word ptr [bp - 6]
00ac push ss
00ad pop ds
00ae jmp 0x8641
00b0 mov di, word ptr [bp - 4]
00b3 push si
00b4 nop 
00b5 push cs
00b6 call 0x559c ; _mem_Unlock
00b9 add sp, 2
00bc push si
00bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 192, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_ReleaseHandle
00c2 add sp, 2
00c5 mov es, word ptr [0xbf7a]
00c9 mov bx, di
00cb shl bx, 1
00cd mov ax, word ptr es:[bx - 0x725a]
00d2 mov word ptr [bp - 0x138], ax
00d6 inc ax
00d7 jne 0x866a
00d9 jmp 0x9598
00dc mov bx, di
00de shl bx, 2
00e1 add bx, 0x8d2a
00e5 mov es, word ptr [0xbf7c]
00e9 mov word ptr [bp - 0x13c], bx
00ed mov word ptr [bp - 0x13a], es
00f1 push word ptr es:[bx + 2]
00f5 push word ptr es:[bx]
00f8 push word ptr [bp - 0x138]
00fc push word ptr [bp - 0x16]
00ff push ds
0100 push 0xe06
0103 nop 
0104 push cs
0105 call 0x62bc ; _WinPrintf
0108 add sp, 0xc
010b mov bx, 0x8d08
010e mov es, word ptr [0xbf78]
0112 mov word ptr [bp - 0x140], bx
0116 mov word ptr [bp - 0x13e], es
011a cmp word ptr es:[bx], 0
011e jne 0x86b1
0120 jmp 0x8c92
0123 mov bx, 0x8d0c
0126 mov word ptr [bp - 0x144], bx
012a mov word ptr [bp - 0x142], es
012e cmp word ptr es:[bx], 0
0132 je 0x86c5
0134 jmp 0x8c92
0137 mov bx, 0x8d0a
013a mov word ptr [bp - 0x148], bx
013e mov word ptr [bp - 0x146], es
0142 cmp word ptr es:[bx], 0
0146 jne 0x86d9
0148 jmp 0x89c0
014b mov bx, word ptr [bp - 0x140]
014f push word ptr es:[bx]
0152 push ds
0153 push 0xe2d
0156 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 343, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
015b mov word ptr [bp - 8], ax
015e mov word ptr [bp - 6], dx
0161 or dx, ax
0163 jne 0x86f6
0165 jmp 0x89b0
0168 push 0
016a push 0
016c push 0x7f02
016f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 368, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
0174 push ax
0175 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 374, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 69}}]
017a mov word ptr [bp - 0xe], ax
017d mov bx, 0x8d0e
0180 mov es, word ptr [0xbf78]
0184 mov word ptr [bp - 0x14c], bx
0188 mov word ptr [bp - 0x14a], es
018c cmp word ptr es:[bx], 0
0190 jne 0x8723
0192 jmp 0x8839
0195 les bx, ptr [bp - 0x140]
0199 cmp word ptr es:[bx], 0
019d jne 0x8730
019f jmp 0x8834
01a2 les bx, ptr [bp - 0x144]
01a6 cmp word ptr es:[bx], 0
01aa je 0x873d
01ac jmp 0x8834
01af les bx, ptr [bp - 0x148]
01b3 cmp word ptr es:[bx], 0
01b7 je 0x87a4
01b9 les bx, ptr [bp - 0x140]
01bd push word ptr es:[bx]
01c0 push ds
01c1 push 0xcb6
01c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 453, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
01c9 mov word ptr [bp - 0xc], ax
01cc mov word ptr [bp - 0xa], dx
01cf push ds
01d0 push 0xcc5
01d3 nop 
01d4 push cs
01d5 call 0x62bc ; _WinPrintf
01d8 add sp, 4
01db mov ax, word ptr [bp - 0xa]
01de or ax, word ptr [bp - 0xc]
01e1 je 0x8787
01e3 les bx, ptr [bp - 0x14c]
01e7 push word ptr es:[bx]
01ea push 0x804
01ed push 0
01ef push 0
01f1 lea ax, [bp - 0x12]
01f4 push ss
01f5 push ax
01f6 lcall [bp - 0xc]
01f9 les bx, ptr [bp - 0x14c]
01fd mov word ptr es:[bx], 0
0202 jmp 0x8839
0205 nop 
0206 inc di
0207 add si, 2
020a cmp word ptr [si], -1
020d je 0x87a0
020f jmp 0x8630
0212 jmp 0x8637
0215 nop 
0216 les bx, ptr [bp - 0x140]
021a push word ptr es:[bx]
021d push ds
021e push 0xcd9
0221 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 546, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0226 mov word ptr [bp - 0xc], ax
0229 mov word ptr [bp - 0xa], dx
022c or dx, ax
022e je 0x87d5
0230 lcall [bp - 0xc]
0233 mov word ptr [bp - 2], ax
0236 or ax, ax
0238 je 0x87d5
023a push ax
023b push ds
023c push 0xce6
023f nop 
0240 push cs
0241 call 0x62bc ; _WinPrintf
0244 add sp, 6
0247 les bx, ptr [bp - 0x140]
024b push word ptr es:[bx]
024e push ds
024f push 0xc4f
0252 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 595, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0257 mov word ptr [bp - 0xc], ax
025a mov word ptr [bp - 0xa], dx
025d or dx, ax
025f je 0x87f2
0261 lcall [bp - 0xc]
0264 mov es, word ptr [0xbf78]
0268 push word ptr es:[0x8d20]
026d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 622, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
0272 mov es, word ptr [0xbf78]
0276 push word ptr es:[0x8d1c]
027b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 636, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
0280 mov es, word ptr [0xbf78]
0284 push word ptr es:[0x8d1c]
0289 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 650, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
028e mov es, word ptr [0xbf78]
0292 mov word ptr es:[0x8d1c], 0
0299 sub ax, ax
029b mov word ptr es:[0x8d20], ax
029f mov word ptr es:[0x8d1e], ax
02a3 jmp 0x8839
02a5 nop 
02a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 679, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 2}}]
02ab sub ax, ax
02ad mov word ptr [bp - 0x48], ax
02b0 mov word ptr [bp - 0x4a], ax
02b3 push word ptr [0xcc7c] ; _hInst
02b7 lea ax, [bp - 0x132]
02bb push ss
02bc push ax
02bd push 0x80
02c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 705, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 49}}]
02c5 push 0x5c
02c7 lea ax, [bp - 0x132]
02cb push ss
02cc push ax
02cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 720, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strrchr
02d2 add sp, 6
02d5 mov es, dx
02d7 mov bx, ax
02d9 mov byte ptr es:[bx + 1], 0
02de les bx, ptr [bp - 0x13c]
02e2 push word ptr es:[bx + 2]
02e6 push word ptr es:[bx]
02e9 lea ax, [bp - 0x132]
02ed push ss
02ee push ax
02ef push ds
02f0 push 0xe3c
02f3 lea ax, [bp - 0xb2]
02f7 push ss
02f8 push ax
02f9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 764, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
02fe add sp, 0x10
0301 lea ax, [bp - 0xb2]
0305 mov word ptr [bp - 0x46], ax
0308 mov word ptr [bp - 0x44], ss
030b push ss
030c push ax
030d push ds
030e push 0xe4b
0311 nop 
0312 push cs
0313 call 0x62bc ; _WinPrintf
0316 add sp, 8
0319 push 0
031b push 0x803
031e push 0
0320 push 0x200
0323 lea ax, [bp - 0x52]
0326 push ss
0327 push ax
0328 lcall [bp - 8]
032b or dx, ax
032d je 0x88c0
032f jmp 0x8998
0332 mov ax, word ptr [bp - 0x4e]
0335 les bx, ptr [bp - 0x14c]
0339 mov word ptr es:[bx], ax
033c push ds
033d push 0xe55
0340 nop 
0341 push cs
0342 call 0x62bc ; _WinPrintf
0345 add sp, 4
0348 les bx, ptr [bp - 0x14c]
034c push word ptr es:[bx]
034f push 0x814
0352 push 0
0354 push 0x4003
0357 lea ax, [bp - 0x3e]
035a push ss
035b push ax
035c lcall [bp - 8]
035f cmp word ptr [bp - 0x3a], -1
0363 jne 0x8900
0365 cmp word ptr [bp - 0x38], -1
0369 jne 0x8900
036b push ds
036c push 0xe6f
036f jmp 0x893a
0371 nop 
0372 push ds
0373 push 0xe81
0376 nop 
0377 push cs
0378 call 0x62bc ; _WinPrintf
037b add sp, 4
037e mov word ptr [bp - 0x62], 0xffff
0383 mov word ptr [bp - 0x60], 0xffff
0388 les bx, ptr [bp - 0x14c]
038c push word ptr es:[bx]
038f push 0x80d
0392 push 2
0394 push 0
0396 lea ax, [bp - 0x72]
0399 push ss
039a push ax
039b lcall [bp - 8]
039e or dx, ax
03a0 jne 0x8936
03a2 push ds
03a3 push 0xe92
03a6 jmp 0x893a
03a8 push ds
03a9 push 0xeaa
03ac nop 
03ad push cs
03ae call 0x62bc ; _WinPrintf
03b1 add sp, 4
03b4 push ds
03b5 push 0xec7
03b8 nop 
03b9 push cs
03ba call 0x62bc ; _WinPrintf
03bd add sp, 4
03c0 sub ax, ax
03c2 mov word ptr [bp - 0x6c], ax
03c5 mov word ptr [bp - 0x6e], ax
03c8 les bx, ptr [bp - 0x14c]
03cc push word ptr es:[bx]
03cf push 0x80d
03d2 push ax
03d3 push 0x400
03d6 lea ax, [bp - 0x72]
03d9 push ss
03da push ax
03db lcall [bp - 8]
03de push ds
03df push 0xed7
03e2 nop 
03e3 push cs
03e4 call 0x62bc ; _WinPrintf
03e7 add sp, 4
03ea sub ax, ax
03ec mov word ptr [bp - 0x28], ax
03ef mov word ptr [bp - 0x2a], ax
03f2 les bx, ptr [bp - 0x14c]
03f6 push word ptr es:[bx]
03f9 push 0x806
03fc push ax
03fd push 4
03ff lea ax, [bp - 0x2e]
0402 push ss
0403 push ax
0404 lcall [bp - 8]
0407 jmp 0x89a4
0409 nop 
040a push ds
040b push 0xee9
040e nop 
040f push cs
0410 call 0x62bc ; _WinPrintf
0413 add sp, 4
0416 push word ptr [bp - 0xe]
0419 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1050, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 69}}]
041e pop si
041f pop di
0420 leave 
0421 retf 
0422 push ds
0423 push 0xf03
0426 nop 
0427 push cs
0428 call 0x62bc ; _WinPrintf
042b add sp, 4
042e pop si
042f pop di
0430 leave 
0431 retf 
0432 les bx, ptr [bp - 0x140]
0436 push word ptr es:[bx]
0439 push ds
043a push 0xf2b
043d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1086, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0442 mov word ptr [bp - 0xa], ax
0445 mov word ptr [bp - 8], dx
0448 mov bx, 0x8d1c
044b mov es, word ptr [0xbf78]
044f mov word ptr [bp - 0x150], bx
0453 mov word ptr [bp - 0x14e], es
0457 cmp word ptr es:[bx], 0
045b jne 0x89ee
045d jmp 0x8af5
0460 les bx, ptr [bp - 0x140]
0464 cmp word ptr es:[bx], 0
0468 jne 0x89fb
046a jmp 0x8af0
046d les bx, ptr [bp - 0x144]
0471 cmp word ptr es:[bx], 0
0475 je 0x8a08
0477 jmp 0x8af0
047a les bx, ptr [bp - 0x148]
047e cmp word ptr es:[bx], 0
0482 je 0x8a62
0484 les bx, ptr [bp - 0x140]
0488 push word ptr es:[bx]
048b push ds
048c push 0xcb6
048f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1168, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0494 mov word ptr [bp - 4], ax
0497 mov word ptr [bp - 2], dx
049a push ds
049b push 0xcc5
049e nop 
049f push cs
04a0 call 0x62bc ; _WinPrintf
04a3 add sp, 4
04a6 mov ax, word ptr [bp - 2]
04a9 or ax, word ptr [bp - 4]
04ac je 0x8a54
04ae mov es, word ptr [0xbf78]
04b2 push word ptr es:[0x8d0e]
04b7 push 0x804
04ba push 0
04bc push 0
04be lea ax, [bp - 0x12]
04c1 push ss
04c2 push ax
04c3 lcall [bp - 4]
04c6 mov es, word ptr [0xbf78]
04ca mov word ptr es:[0x8d0e], 0
04d1 jmp 0x8af5
04d4 les bx, ptr [bp - 0x140]
04d8 push word ptr es:[bx]
04db push ds
04dc push 0xcd9
04df lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1248, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
04e4 mov word ptr [bp - 4], ax
04e7 mov word ptr [bp - 2], dx
04ea or dx, ax
04ec je 0x8a93
04ee lcall [bp - 4]
04f1 mov word ptr [bp - 6], ax
04f4 or ax, ax
04f6 je 0x8a93
04f8 push ax
04f9 push ds
04fa push 0xce6
04fd nop 
04fe push cs
04ff call 0x62bc ; _WinPrintf
0502 add sp, 6
0505 les bx, ptr [bp - 0x140]
0509 push word ptr es:[bx]
050c push ds
050d push 0xc4f
0510 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1297, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0515 mov word ptr [bp - 4], ax
0518 mov word ptr [bp - 2], dx
051b or dx, ax
051d je 0x8ab0
051f lcall [bp - 4]
0522 mov es, word ptr [0xbf78]
0526 push word ptr es:[0x8d20]
052b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1324, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
0530 les bx, ptr [bp - 0x150]
0534 push word ptr es:[bx]
0537 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1336, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
053c les bx, ptr [bp - 0x150]
0540 push word ptr es:[bx]
0543 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1348, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
0548 les bx, ptr [bp - 0x150]
054c mov word ptr es:[bx], 0
0551 mov es, word ptr [0xbf78]
0555 sub ax, ax
0557 mov word ptr es:[0x8d20], ax
055b mov word ptr es:[0x8d1e], ax
055f jmp 0x8af5
0561 nop 
0562 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1379, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 2}}]
0567 mov ax, word ptr [bp - 8]
056a or ax, word ptr [bp - 0xa]
056d jne 0x8b00
056f jmp 0x9598
0572 push word ptr [0xcd78] ; _rootWnd
0576 lcall [bp - 0xa]
0579 mov si, ax
057b or si, si
057d je 0x8b1e
057f push si
0580 push ds
0581 push 0xf39
0584 nop 
0585 push cs
0586 call 0x62bc ; _WinPrintf
0589 add sp, 6
058c pop si
058d pop di
058e leave 
058f retf 
0590 push 1
0592 push 0x14
0594 push word ptr [bp - 0xe]
0597 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1434, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
059c add sp, 6
059f mov word ptr [bp - 0xc], ax
05a2 or ax, ax
05a4 jne 0x8b37
05a6 jmp 0x9598
05a9 les bx, ptr [bp - 0x140]
05ad push word ptr es:[bx]
05b0 push ds
05b1 push 0xf59
05b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1461, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
05b9 mov word ptr [bp - 4], ax
05bc mov word ptr [bp - 2], dx
05bf les bx, ptr [bp - 0x140]
05c3 push word ptr es:[bx]
05c6 push ds
05c7 push 0xf6a
05ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1483, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
05cf mov word ptr [bp - 0xa], ax
05d2 mov word ptr [bp - 8], dx
05d5 push word ptr [bp - 0xc]
05d8 nop 
05d9 push cs
05da call 0x558e ; _mem_Lock
05dd add sp, 2
05e0 mov word ptr [bp - 0x10], ax
05e3 mov word ptr [bp - 0xe], dx
05e6 push 2
05e8 push word ptr [bp - 0xc]
05eb nop 
05ec push cs
05ed call 0x55aa ; _mem_Size
05f0 add sp, 2
05f3 push dx
05f4 push ax
05f5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1526, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
05fa les bx, ptr [bp - 0x150]
05fe mov word ptr es:[bx], ax
0601 push ax
0602 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1539, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 111}}]
0607 mov es, word ptr [0xbf78]
060b mov word ptr es:[0x8d1e], ax
060f mov word ptr es:[0x8d20], dx
0614 push word ptr [bp - 0xc]
0617 nop 
0618 push cs
0619 call 0x55aa ; _mem_Size
061c add sp, 2
061f mov word ptr [bp - 6], ax
0622 mov es, word ptr [0xbf78]
0626 mov ax, word ptr es:[0x8d1e]
062a mov dx, word ptr es:[0x8d20]
062f mov bx, word ptr [bp - 0x10]
0632 mov si, word ptr [bp - 0xe]
0635 mov cx, word ptr [bp - 6]
0638 push ds
0639 push si
063a mov di, ax
063c mov si, bx
063e mov es, dx
0640 pop ds
0641 shr cx, 1
0643 rep movsw word ptr es:[di], word ptr [si]
0645 adc cx, cx
0647 rep movsb byte ptr es:[di], byte ptr [si]
0649 pop ds
064a push dx
064b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1612, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 191}}]
0650 mov ax, word ptr [bp - 2]
0653 or ax, word ptr [bp - 4]
0656 je 0x8bec
0658 push word ptr [bp - 0x16]
065b lcall [bp - 4]
065e mov ax, word ptr [bp - 8]
0661 or ax, word ptr [bp - 0xa]
0664 jne 0x8bf7
0666 jmp 0x8c80
0669 mov es, word ptr [0xbf78]
066d push word ptr es:[0x8d20]
0672 push word ptr es:[0x8d1e]
0677 lcall [bp - 0xa]
067a mov word ptr [bp - 2], ax
067d or ax, ax
067f je 0x8c80
0681 les bx, ptr [bp - 0x140]
0685 push word ptr es:[bx]
0688 push ds
0689 push 0xc4f
068c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1677, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0691 mov word ptr [bp - 6], ax
0694 mov word ptr [bp - 4], dx
0697 or dx, ax
0699 je 0x8c2c
069b lcall [bp - 6]
069e mov es, word ptr [0xbf78]
06a2 push word ptr es:[0x8d20]
06a7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1704, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
06ac les bx, ptr [bp - 0x150]
06b0 push word ptr es:[bx]
06b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1716, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
06b8 les bx, ptr [bp - 0x150]
06bc push word ptr es:[bx]
06bf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1728, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
06c4 les bx, ptr [bp - 0x150]
06c8 mov word ptr es:[bx], 0
06cd mov es, word ptr [0xbf78]
06d1 sub ax, ax
06d3 mov word ptr es:[0x8d20], ax
06d7 mov word ptr es:[0x8d1e], ax
06db mov ax, word ptr [bp - 8]
06de or ax, word ptr [bp - 0xa]
06e1 je 0x8c80
06e3 push word ptr [bp - 2]
06e6 push ds
06e7 push 0xf79
06ea nop 
06eb push cs
06ec call 0x62bc ; _WinPrintf
06ef add sp, 6
06f2 push word ptr [bp - 0xc]
06f5 nop 
06f6 push cs
06f7 call 0x559c ; _mem_Unlock
06fa add sp, 2
06fd push word ptr [bp - 0xc]
0700 jmp 0x9590
0703 nop 
0704 les bx, ptr [bp - 0x140]
0708 cmp word ptr es:[bx], 0
070c jne 0x8c9f
070e jmp 0x8d96
0711 mov es, word ptr [0xbf78]
0715 cmp word ptr es:[0x8d0c], 0
071b je 0x8cae
071d jmp 0x8d96
0720 cmp word ptr es:[0x8d0a], 0
0726 je 0x8d06
0728 mov es, word ptr [bp - 0x13e]
072c push word ptr es:[bx]
072f push ds
0730 push 0xcb6
0733 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1844, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0738 mov word ptr [bp - 4], ax
073b mov word ptr [bp - 2], dx
073e push ds
073f push 0xcc5
0742 nop 
0743 push cs
0744 call 0x62bc ; _WinPrintf
0747 add sp, 4
074a mov ax, word ptr [bp - 2]
074d or ax, word ptr [bp - 4]
0750 je 0x8cf8
0752 mov es, word ptr [0xbf78]
0756 push word ptr es:[0x8d0e]
075b push 0x804
075e push 0
0760 push 0
0762 lea ax, [bp - 0xa]
0765 push ss
0766 push ax
0767 lcall [bp - 4]
076a mov es, word ptr [0xbf78]
076e mov word ptr es:[0x8d0e], 0
0775 jmp 0x8d9b
0778 mov es, word ptr [bp - 0x13e]
077c push word ptr es:[bx]
077f push ds
0780 push 0xcd9
0783 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1924, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0788 mov word ptr [bp - 4], ax
078b mov word ptr [bp - 2], dx
078e or dx, ax
0790 je 0x8d37
0792 lcall [bp - 4]
0795 mov word ptr [bp - 6], ax
0798 or ax, ax
079a je 0x8d37
079c push ax
079d push ds
079e push 0xce6
07a1 nop 
07a2 push cs
07a3 call 0x62bc ; _WinPrintf
07a6 add sp, 6
07a9 les bx, ptr [bp - 0x140]
07ad push word ptr es:[bx]
07b0 push ds
07b1 push 0xc4f
07b4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1973, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
07b9 mov word ptr [bp - 4], ax
07bc mov word ptr [bp - 2], dx
07bf or dx, ax
07c1 je 0x8d54
07c3 lcall [bp - 4]
07c6 mov es, word ptr [0xbf78]
07ca push word ptr es:[0x8d20]
07cf lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2000, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
07d4 mov es, word ptr [0xbf78]
07d8 push word ptr es:[0x8d1c]
07dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2014, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
07e2 mov es, word ptr [0xbf78]
07e6 push word ptr es:[0x8d1c]
07eb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2028, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
07f0 mov es, word ptr [0xbf78]
07f4 mov word ptr es:[0x8d1c], 0
07fb sub ax, ax
07fd mov word ptr es:[0x8d20], ax
0801 mov word ptr es:[0x8d1e], ax
0805 jmp 0x8d9b
0807 nop 
0808 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2057, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 2}}]
080d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2062, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 1}}]
0812 or ax, ax
0814 jne 0x8da7
0816 jmp 0x9598
0819 push 1
081b push 0x32
081d push word ptr [bp - 0xe]
0820 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2083, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0825 add sp, 6
0828 mov word ptr [bp - 0x20], ax
082b push 1
082d push 0x1400
0830 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2097, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 3}}]
0835 cmp word ptr [bp - 0x20], 0
0839 jne 0x8dcc
083b jmp 0x9598
083e push word ptr [bp - 0x20]
0841 nop 
0842 push cs
0843 call 0x558e ; _mem_Lock
0846 add sp, 2
0849 mov word ptr [bp - 0x1a], ax
084c mov word ptr [bp - 0x18], dx
084f les bx, ptr [bp - 0x1a]
0852 mov al, byte ptr es:[bx + 3]
0856 cwde 
0857 push ax
0858 mov al, byte ptr es:[bx + 2]
085c cwde 
085d push ax
085e mov al, byte ptr es:[bx + 1]
0862 cwde 
0863 push ax
0864 mov al, byte ptr es:[bx]
0867 cwde 
0868 push ax
0869 push ds
086a push 0xf9a
086d nop 
086e push cs
086f call 0x62bc ; _WinPrintf
0872 add sp, 0xc
0875 mov ax, ds
0877 mov cx, 4
087a mov di, 0xfb1
087d mov es, ax
087f push ds
0880 lds si, ptr [bp - 0x1a]
0883 shr cx, 1
0885 sbb ax, ax
0887 cmp cx, cx
0889 repe cmpsw word ptr [si], word ptr es:[di]
088b jne 0x8e1f
088d sub cx, ax
088f repe cmpsb byte ptr [si], byte ptr es:[di]
0891 pop ds
0892 je 0x8e25
0894 jmp 0x9576
0897 mov ax, word ptr [bp - 0x1a]
089a mov dx, word ptr [bp - 0x18]
089d add ax, 4
08a0 adc dx, 0
08a3 mov word ptr [bp - 0x1a], ax
08a6 mov word ptr [bp - 0x18], dx
08a9 les bx, ptr [bp - 0x1a]
08ac mov ax, word ptr es:[bx]
08af mov dx, word ptr es:[bx + 2]
08b3 mov word ptr [bp - 0x1e], ax
08b6 mov word ptr [bp - 0x1c], dx
08b9 push dx
08ba push ax
08bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2238, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipLong
08c0 add sp, 4
08c3 mov word ptr [bp - 0x1e], ax
08c6 mov word ptr [bp - 0x1c], dx
08c9 mov ax, word ptr [bp - 0x1a]
08cc mov dx, word ptr [bp - 0x18]
08cf add ax, 4
08d2 adc dx, 0
08d5 mov word ptr [bp - 0x1a], ax
08d8 mov word ptr [bp - 0x18], dx
08db push word ptr [bp - 0x1c]
08de push word ptr [bp - 0x1e]
08e1 push ds
08e2 push 0xfb6
08e5 nop 
08e6 push cs
08e7 call 0x62bc ; _WinPrintf
08ea add sp, 8
08ed les bx, ptr [bp - 0x1a]
08f0 mov ax, word ptr es:[bx]
08f3 mov word ptr [bp - 0xe], ax
08f6 push ax
08f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipWord
08fc add sp, 2
08ff mov word ptr [bp - 0xe], ax
0902 mov ax, word ptr [bp - 0x1a]
0905 mov dx, word ptr [bp - 0x18]
0908 add ax, 2
090b adc dx, 0
090e mov word ptr [bp - 0x1a], ax
0911 mov word ptr [bp - 0x18], dx
0914 les bx, ptr [bp - 0x1a]
0917 mov ax, word ptr es:[bx]
091a mov word ptr [bp - 0x10], ax
091d push ax
091e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2337, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipWord
0923 add sp, 2
0926 mov word ptr [bp - 0x10], ax
0929 mov ax, word ptr [bp - 0x1a]
092c mov dx, word ptr [bp - 0x18]
092f add ax, 2
0932 adc dx, 0
0935 mov word ptr [bp - 0x1a], ax
0938 mov word ptr [bp - 0x18], dx
093b les bx, ptr [bp - 0x1a]
093e mov ax, word ptr es:[bx]
0941 mov word ptr [bp - 0xc], ax
0944 push ax
0945 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2376, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipWord
094a add sp, 2
094d mov word ptr [bp - 0xc], ax
0950 mov ax, word ptr [bp - 0x1a]
0953 mov dx, word ptr [bp - 0x18]
0956 add ax, 2
0959 adc dx, 0
095c mov word ptr [bp - 0x1a], ax
095f mov word ptr [bp - 0x18], dx
0962 push word ptr [bp - 0xc]
0965 push word ptr [bp - 0x10]
0968 push word ptr [bp - 0xe]
096b push ds
096c push 0xfc5
096f nop 
0970 push cs
0971 call 0x62bc ; _WinPrintf
0974 add sp, 0xa
0977 mov ax, ds
0979 mov cx, 4
097c mov di, 0xff0
097f mov es, ax
0981 push ds
0982 lds si, ptr [bp - 0x1a]
0985 shr cx, 1
0987 sbb ax, ax
0989 cmp cx, cx
098b repe cmpsw word ptr [si], word ptr es:[di]
098d jne 0x8f21
098f sub cx, ax
0991 repe cmpsb byte ptr [si], byte ptr es:[di]
0993 pop ds
0994 je 0x8f27
0996 jmp 0x9570
0999 mov ax, word ptr [bp - 0x1a]
099c mov dx, word ptr [bp - 0x18]
099f add ax, 4
09a2 adc dx, 0
09a5 mov word ptr [bp - 0x1a], ax
09a8 mov word ptr [bp - 0x18], dx
09ab les bx, ptr [bp - 0x1a]
09ae mov ax, word ptr es:[bx]
09b1 mov dx, word ptr es:[bx + 2]
09b5 mov word ptr [bp - 0x1e], ax
09b8 mov word ptr [bp - 0x1c], dx
09bb push dx
09bc push ax
09bd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2496, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipLong
09c2 add sp, 4
09c5 mov word ptr [bp - 0x1e], ax
09c8 mov word ptr [bp - 0x1c], dx
09cb mov ax, word ptr [bp - 0x1a]
09ce mov dx, word ptr [bp - 0x18]
09d1 add ax, 4
09d4 adc dx, 0
09d7 mov word ptr [bp - 0x1a], ax
09da mov word ptr [bp - 0x18], dx
09dd cmp word ptr [bp - 0x1c], 0
09e1 jne 0x8f7a
09e3 cmp word ptr [bp - 0x1e], 0
09e7 jne 0x8f7a
09e9 jmp 0x90b3
09ec lea ax, [bp - 0x1e]
09ef push ss
09f0 push ax
09f1 lea ax, [bp - 0x24]
09f4 push ss
09f5 push ax
09f6 lea cx, [bp - 0x1a]
09f9 push ss
09fa push cx
09fb nop 
09fc push cs
09fd call 0x843a ; _ExtractVariableLen
0a00 add sp, 0xc
0a03 push word ptr [bp - 0x22]
0a06 push word ptr [bp - 0x24]
0a09 push ds
0a0a push 0xff5
0a0d nop 
0a0e push cs
0a0f call 0x62bc ; _WinPrintf
0a12 add sp, 8
0a15 les bx, ptr [bp - 0x1a]
0a18 mov al, byte ptr es:[bx]
0a1b cwde 
0a1c inc ax
0a1d je 0x8fbc
0a1f push ds
0a20 push 0x1019
0a23 nop 
0a24 push cs
0a25 call 0x62bc ; _WinPrintf
0a28 add sp, 4
0a2b jmp 0x90a1
0a2e sub word ptr [bp - 0x1e], 1
0a32 sbb word ptr [bp - 0x1c], 0
0a36 mov cx, es
0a38 add bx, 1
0a3b adc cx, 0
0a3e mov es, cx
0a40 mov word ptr [bp - 0x1a], bx
0a43 mov word ptr [bp - 0x18], es
0a46 mov al, byte ptr es:[bx]
0a49 cwde 
0a4a sub ax, 0x51
0a4d je 0x901e
0a4f sub word ptr [bp - 0x1e], 1
0a53 sbb word ptr [bp - 0x1c], 0
0a57 mov dx, es
0a59 add bx, 1
0a5c adc dx, 0
0a5f mov es, dx
0a61 mov word ptr [bp - 0x1a], bx
0a64 mov word ptr [bp - 0x18], es
0a67 mov al, byte ptr es:[bx]
0a6a sub ah, ah
0a6c mov cx, ax
0a6e cdq 
0a6f mov si, es
0a71 add ax, bx
0a73 adc dx, si
0a75 add ax, 1
0a78 adc dx, 0
0a7b mov word ptr [bp - 0x1a], ax
0a7e mov word ptr [bp - 0x18], dx
0a81 mov ax, cx
0a83 inc ax
0a84 cdq 
0a85 sub word ptr [bp - 0x1e], ax
0a88 sbb word ptr [bp - 0x1c], dx
0a8b jmp 0x90a1
0a8e nop 
0a8f nop 
0a90 mov ax, bx
0a92 mov dx, es
0a94 add ax, 2
0a97 adc dx, 0
0a9a mov word ptr [bp - 0x1a], ax
0a9d mov word ptr [bp - 0x18], dx
0aa0 sub word ptr [bp - 0x1e], 2
0aa4 sbb word ptr [bp - 0x1c], 0
0aa8 sub ax, ax
0aaa mov word ptr [bp - 0x26], ax
0aad mov word ptr [bp - 0x28], ax
0ab0 lea ax, [bp - 0x28]
0ab3 mov dx, ss
0ab5 add ax, 1
0ab8 adc dx, 0
0abb mov bx, word ptr [bp - 0x1a]
0abe mov si, word ptr [bp - 0x18]
0ac1 push ds
0ac2 push si
0ac3 mov di, ax
0ac5 mov si, bx
0ac7 mov es, dx
0ac9 pop ds
0aca movsw word ptr es:[di], word ptr [si]
0acb movsb byte ptr es:[di], byte ptr [si]
0acc pop ds
0acd push word ptr [bp - 0x26]
0ad0 push word ptr [bp - 0x28]
0ad3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2774, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipLong
0ad8 add sp, 4
0adb mov word ptr [bp - 0x28], ax
0ade mov word ptr [bp - 0x26], dx
0ae1 mov ax, word ptr [bp - 0x1a]
0ae4 mov dx, word ptr [bp - 0x18]
0ae7 add ax, 3
0aea adc dx, 0
0aed mov word ptr [bp - 0x1a], ax
0af0 mov word ptr [bp - 0x18], dx
0af3 sub word ptr [bp - 0x1e], 3
0af7 sbb word ptr [bp - 0x1c], 0
0afb push word ptr [bp - 0x26]
0afe push word ptr [bp - 0x28]
0b01 push word ptr [bp - 0x26]
0b04 push word ptr [bp - 0x28]
0b07 push ds
0b08 push 0x1005
0b0b nop 
0b0c push cs
0b0d call 0x62bc ; _WinPrintf
0b10 add sp, 0xc
0b13 cmp word ptr [bp - 0x1c], 0
0b17 je 0x90aa
0b19 jmp 0x8f7a
0b1c cmp word ptr [bp - 0x1e], 0
0b20 je 0x90b3
0b22 jmp 0x8f7a
0b25 mov ax, ds
0b27 mov cx, 4
0b2a mov di, 0x102a
0b2d mov es, ax
0b2f push ds
0b30 lds si, ptr [bp - 0x1a]
0b33 shr cx, 1
0b35 sbb ax, ax
0b37 cmp cx, cx
0b39 repe cmpsw word ptr [si], word ptr es:[di]
0b3b jne 0x90cf
0b3d sub cx, ax
0b3f repe cmpsb byte ptr [si], byte ptr es:[di]
0b41 pop ds
0b42 je 0x90d5
0b44 jmp 0x956a
0b47 xor ax, ax
0b49 mov word ptr [bp - 0xa], ax
0b4c mov word ptr [bp - 8], ax
0b4f mov cx, word ptr [bp - 0x1a]
0b52 mov dx, word ptr [bp - 0x18]
0b55 add cx, 4
0b58 adc dx, ax
0b5a mov word ptr [bp - 0x1a], cx
0b5d mov word ptr [bp - 0x18], dx
0b60 les bx, ptr [bp - 0x1a]
0b63 mov cx, word ptr es:[bx]
0b66 mov dx, word ptr es:[bx + 2]
0b6a mov word ptr [bp - 0x1e], cx
0b6d mov word ptr [bp - 0x1c], dx
0b70 push dx
0b71 push cx
0b72 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2933, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipLong
0b77 add sp, 4
0b7a mov word ptr [bp - 0x1e], ax
0b7d mov word ptr [bp - 0x1c], dx
0b80 mov ax, word ptr [bp - 0x1a]
0b83 mov dx, word ptr [bp - 0x18]
0b86 add ax, 4
0b89 adc dx, 0
0b8c mov word ptr [bp - 0x1a], ax
0b8f mov word ptr [bp - 0x18], dx
0b92 add ax, word ptr [bp - 0x1e]
0b95 adc dx, word ptr [bp - 0x1c]
0b98 mov word ptr [bp - 0x1a], ax
0b9b mov word ptr [bp - 0x18], dx
0b9e mov ax, ds
0ba0 mov cx, 4
0ba3 mov di, 0x102f
0ba6 mov es, ax
0ba8 push ds
0ba9 lds si, ptr [bp - 0x1a]
0bac shr cx, 1
0bae sbb ax, ax
0bb0 cmp cx, cx
0bb2 repe cmpsw word ptr [si], word ptr es:[di]
0bb4 jne 0x9148
0bb6 sub cx, ax
0bb8 repe cmpsb byte ptr [si], byte ptr es:[di]
0bba pop ds
0bbb je 0x9166
0bbd push ds
0bbe push 0x1034
0bc1 nop 
0bc2 push cs
0bc3 call 0x62bc ; _WinPrintf
0bc6 add sp, 4
0bc9 mov ax, word ptr [bp - 0x1a]
0bcc mov dx, word ptr [bp - 0x18]
0bcf sub ax, word ptr [bp - 0x1e]
0bd2 sbb dx, word ptr [bp - 0x1c]
0bd5 jmp 0x91a1
0bd7 nop 
0bd8 mov ax, word ptr [bp - 0x1a]
0bdb add ax, 4
0bde adc dx, 0
0be1 mov word ptr [bp - 0x1a], ax
0be4 mov word ptr [bp - 0x18], dx
0be7 les bx, ptr [bp - 0x1a]
0bea mov ax, word ptr es:[bx]
0bed mov dx, word ptr es:[bx + 2]
0bf1 mov word ptr [bp - 0x1e], ax
0bf4 mov word ptr [bp - 0x1c], dx
0bf7 push dx
0bf8 push ax
0bf9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3068, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _FlipLong
0bfe add sp, 4
0c01 mov word ptr [bp - 0x1e], ax
0c04 mov word ptr [bp - 0x1c], dx
0c07 mov ax, word ptr [bp - 0x1a]
0c0a mov dx, word ptr [bp - 0x18]
0c0d add ax, 4
0c10 adc dx, 0
0c13 mov word ptr [bp - 0x1a], ax
0c16 mov word ptr [bp - 0x18], dx
0c19 cmp word ptr [bp - 0x1c], 0
0c1d jne 0x91b6
0c1f cmp word ptr [bp - 0x1e], 1
0c23 ja 0x91b6
0c25 jmp 0x9563
0c28 mov di, word ptr [bp - 0x12]
0c2b lea ax, [bp - 0x1e]
0c2e push ss
0c2f push ax
0c30 lea ax, [bp - 0x24]
0c33 push ss
0c34 push ax
0c35 lea ax, [bp - 0x1a]
0c38 push ss
0c39 push ax
0c3a nop 
0c3b push cs
0c3c call 0x843a ; _ExtractVariableLen
0c3f add sp, 0xc
0c42 les bx, ptr [bp - 0x1a]
0c45 test byte ptr es:[bx], 0x80
0c49 je 0x91f7
0c4b mov al, byte ptr es:[bx]
0c4e sub ah, ah
0c50 mov word ptr [bp - 8], ax
0c53 mov ax, es
0c55 add bx, 1
0c58 adc ax, 0
0c5b mov word ptr [bp - 0x1a], bx
0c5e mov word ptr [bp - 0x18], ax
0c61 sub word ptr [bp - 0x1e], 1
0c65 sbb word ptr [bp - 0x1c], 0
0c69 mov ax, word ptr [bp - 8]
0c6c sub ax, 0x80
0c6f cmp ax, 0x7f
0c72 jbe 0x9205
0c74 jmp 0x930e
0c77 shl ax, 1
0c79 xchg bx, ax
0c7a jmp word ptr cs:[bx - 0x6df2]
0c7f nop 
0c80 dw offset 0x9320
0c82 dw offset 0x9320
0c84 dw offset 0x9320
0c86 dw offset 0x9320
0c88 dw offset 0x9320
0c8a dw offset 0x9320
0c8c dw offset 0x9320
0c8e dw offset 0x9320
0c90 dw offset 0x9320
0c92 dw offset 0x9320
0c94 dw offset 0x9320
0c96 dw offset 0x9320
0c98 dw offset 0x9320
0c9a dw offset 0x9320
0c9c dw offset 0x9320
0c9e dw offset 0x930e
0ca0 dw offset 0x93ce
0ca2 dw offset 0x93ce
0ca4 dw offset 0x93ce
0ca6 dw offset 0x93ce
0ca8 dw offset 0x93ce
0caa dw offset 0x93ce
0cac dw offset 0x93ce
0cae dw offset 0x93ce
0cb0 dw offset 0x93ce
0cb2 dw offset 0x93ce
0cb4 dw offset 0x93ce
0cb6 dw offset 0x93ce
0cb8 dw offset 0x93ce
0cba dw offset 0x93ce
0cbc dw offset 0x93ce
0cbe dw offset 0x93ce
0cc0 dw offset 0x930e
0cc2 dw offset 0x930e
0cc4 dw offset 0x930e
0cc6 dw offset 0x930e
0cc8 dw offset 0x930e
0cca dw offset 0x930e
0ccc dw offset 0x930e
0cce dw offset 0x930e
0cd0 dw offset 0x930e
0cd2 dw offset 0x930e
0cd4 dw offset 0x930e
0cd6 dw offset 0x930e
0cd8 dw offset 0x930e
0cda dw offset 0x930e
0cdc dw offset 0x930e
0cde dw offset 0x930e
0ce0 dw offset 0x94aa
0ce2 dw offset 0x94aa
0ce4 dw offset 0x94aa
0ce6 dw offset 0x94aa
0ce8 dw offset 0x94aa
0cea dw offset 0x94aa
0cec dw offset 0x94aa
0cee dw offset 0x94aa
0cf0 dw offset 0x94aa
0cf2 dw offset 0x94aa
0cf4 dw offset 0x94aa
0cf6 dw offset 0x94aa
0cf8 dw offset 0x94aa
0cfa dw offset 0x94aa
0cfc dw offset 0x94aa
0cfe dw offset 0x930e
0d00 dw offset 0x94d2
0d02 dw offset 0x94d2
0d04 dw offset 0x94d2
0d06 dw offset 0x94d2
0d08 dw offset 0x94d2
0d0a dw offset 0x94d2
0d0c dw offset 0x94d2
0d0e dw offset 0x94d2
0d10 dw offset 0x94d2
0d12 dw offset 0x94d2
0d14 dw offset 0x94d2
0d16 dw offset 0x94d2
0d18 dw offset 0x94d2
0d1a dw offset 0x94d2
0d1c dw offset 0x94d2
0d1e dw offset 0x930e
0d20 dw offset 0x930e
0d22 dw offset 0x930e
0d24 dw offset 0x930e
0d26 dw offset 0x930e
0d28 dw offset 0x930e
0d2a dw offset 0x930e
0d2c dw offset 0x930e
0d2e dw offset 0x930e
0d30 dw offset 0x930e
0d32 dw offset 0x930e
0d34 dw offset 0x930e
0d36 dw offset 0x930e
0d38 dw offset 0x930e
0d3a dw offset 0x930e
0d3c dw offset 0x930e
0d3e dw offset 0x930e
0d40 dw offset 0x930e
0d42 dw offset 0x930e
0d44 dw offset 0x930e
0d46 dw offset 0x930e
0d48 dw offset 0x930e
0d4a dw offset 0x930e
0d4c dw offset 0x930e
0d4e dw offset 0x930e
0d50 dw offset 0x930e
0d52 dw offset 0x930e
0d54 dw offset 0x930e
0d56 dw offset 0x930e
0d58 dw offset 0x930e
0d5a dw offset 0x930e
0d5c dw offset 0x930e
0d5e dw offset 0x930e
0d60 dw offset 0x930e
0d62 dw offset 0x930e
0d64 dw offset 0x930e
0d66 dw offset 0x930e
0d68 dw offset 0x930e
0d6a dw offset 0x930e
0d6c dw offset 0x930e
0d6e dw offset 0x930e
0d70 dw offset 0x930e
0d72 dw offset 0x930e
0d74 dw offset 0x930e
0d76 dw offset 0x930e
0d78 dw offset 0x930e
0d7a dw offset 0x930e
0d7c dw offset 0x930e
0d7e dw offset 0x94f6
0d80 push word ptr [bp - 8]
0d83 push ds
0d84 push 0x110f
0d87 nop 
0d88 push cs
0d89 call 0x62bc ; _WinPrintf
0d8c add sp, 6
0d8f jmp 0x9551
0d92 mov ax, word ptr [bp - 0x1a]
0d95 mov dx, word ptr [bp - 0x18]
0d98 add ax, 2
0d9b adc dx, 0
0d9e mov word ptr [bp - 0x1a], ax
0da1 mov word ptr [bp - 0x18], dx
0da4 sub word ptr [bp - 0x1e], 2
0da8 sbb word ptr [bp - 0x1c], 0
0dac cmp word ptr [bp - 0x22], 0
0db0 jne 0x9346
0db2 cmp word ptr [bp - 0x24], 0
0db6 je 0x9391
0db8 push word ptr [bp - 0x22]
0dbb push word ptr [bp - 0x24]
0dbe mov ax, word ptr [bp - 0xc]
0dc1 shl ax, 2
0dc4 push 0
0dc6 push ax
0dc7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3530, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0dcc mov si, ax
0dce or si, si
0dd0 jne 0x9363
0dd2 mov si, 1
0dd5 mov word ptr [bp - 2], si
0dd8 cmp si, 0x20
0ddb jle 0x9370
0ddd mov word ptr [bp - 2], 0x20
0de2 cmp word ptr [bp - 0xa], 0
0de6 jne 0x937c
0de8 push 1
0dea push 0
0dec jmp 0x9385
0dee push 1
0df0 mov ax, word ptr [bp - 0x14]
0df3 add ax, word ptr [bp - 0x16]
0df6 push ax
0df7 push word ptr [bp - 2]
0dfa push 0
0dfc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3581, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 4}}]
0e01 mov di, ax
0e03 mov ax, di
0e05 sub ax, 0xfff9
0e08 je 0x93a4
0e0a dec ax
0e0b je 0x93aa
0e0d dec ax
0e0e je 0x93b0
0e10 dec ax
0e11 je 0x93b6
0e13 jmp 0x93c2
0e15 nop 
0e16 push ds
0e17 push 0x1097
0e1a jmp 0x93ba
0e1c push ds
0e1d push 0x10ab
0e20 jmp 0x93ba
0e22 push ds
0e23 push 0x10c1
0e26 jmp 0x93ba
0e28 push ds
0e29 push 0x10d0
0e2c nop 
0e2d push cs
0e2e call 0x62bc ; _WinPrintf
0e31 add sp, 4
0e34 xor ax, ax
0e36 mov word ptr [bp - 0xa], ax
0e39 mov word ptr [bp - 0x14], ax
0e3c jmp 0x9551
0e3f nop 
0e40 les bx, ptr [bp - 0x1a]
0e43 mov al, byte ptr es:[bx]
0e46 sub ah, ah
0e48 sub ax, 0x1e
0e4b mov word ptr [bp - 4], ax
0e4e sub word ptr [bp - 0x1e], 1
0e52 sbb word ptr [bp - 0x1c], 0
0e56 mov ax, es
0e58 add bx, 1
0e5b adc ax, 0
0e5e mov es, ax
0e60 mov word ptr [bp - 0x1a], bx
0e63 mov word ptr [bp - 0x18], es
0e66 mov al, byte ptr es:[bx]
0e69 sub ah, ah
0e6b mov word ptr [bp - 6], ax
0e6e mov ax, es
0e70 add bx, 1
0e73 adc ax, 0
0e76 mov word ptr [bp - 0x1a], bx
0e79 mov word ptr [bp - 0x18], ax
0e7c sub word ptr [bp - 0x1e], 1
0e80 sbb word ptr [bp - 0x1c], 0
0e84 cmp word ptr [bp - 0x22], 0
0e88 jne 0x941e
0e8a cmp word ptr [bp - 0x24], 0
0e8e je 0x9469
0e90 push word ptr [bp - 0x22]
0e93 push word ptr [bp - 0x24]
0e96 mov ax, word ptr [bp - 0xc]
0e99 shl ax, 2
0e9c push 0
0e9e push ax
0e9f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3746, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0ea4 mov si, ax
0ea6 or si, si
0ea8 jne 0x943b
0eaa mov si, 1
0ead mov word ptr [bp - 2], si
0eb0 cmp si, 0x20
0eb3 jle 0x9448
0eb5 mov word ptr [bp - 2], 0x20
0eba cmp word ptr [bp - 0xa], 0
0ebe jne 0x9454
0ec0 push 1
0ec2 push 0
0ec4 jmp 0x945d
0ec6 push 1
0ec8 mov ax, word ptr [bp - 0x14]
0ecb add ax, word ptr [bp - 0x16]
0ece push ax
0ecf push word ptr [bp - 2]
0ed2 push 0
0ed4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3797, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 4}}]
0ed9 mov di, ax
0edb mov ax, di
0edd sub ax, 0xfff9
0ee0 je 0x947c
0ee2 dec ax
0ee3 je 0x9482
0ee5 dec ax
0ee6 je 0x9488
0ee8 dec ax
0ee9 je 0x948e
0eeb jmp 0x949a
0eed nop 
0eee push ds
0eef push 0x104b
0ef2 jmp 0x9492
0ef4 push ds
0ef5 push 0x105f
0ef8 jmp 0x9492
0efa push ds
0efb push 0x1075
0efe jmp 0x9492
0f00 push ds
0f01 push 0x1084
0f04 nop 
0f05 push cs
0f06 call 0x62bc ; _WinPrintf
0f09 add sp, 4
0f0c mov ax, word ptr [bp - 4]
0f0f mov word ptr [bp - 0x14], ax
0f12 mov ax, word ptr [bp - 6]
0f15 mov word ptr [bp - 0xa], ax
0f18 jmp 0x9551
0f1b nop 
0f1c push ds
0f1d push 0x10e3
0f20 nop 
0f21 push cs
0f22 call 0x62bc ; _WinPrintf
0f25 add sp, 4
0f28 mov ax, word ptr [bp - 0x1a]
0f2b mov dx, word ptr [bp - 0x18]
0f2e add ax, 2
0f31 adc dx, 0
0f34 mov word ptr [bp - 0x1a], ax
0f37 mov word ptr [bp - 0x18], dx
0f3a sub word ptr [bp - 0x1e], 2
0f3e sbb word ptr [bp - 0x1c], 0
0f42 jmp 0x9551
0f44 push ds
0f45 push 0x10f3
0f48 nop 
0f49 push cs
0f4a call 0x62bc ; _WinPrintf
0f4d add sp, 4
0f50 mov ax, word ptr [bp - 0x1a]
0f53 mov dx, word ptr [bp - 0x18]
0f56 add ax, 1
0f59 adc dx, 0
0f5c mov word ptr [bp - 0x1a], ax
0f5f mov word ptr [bp - 0x18], dx
0f62 sub word ptr [bp - 0x1e], 1
0f66 jmp 0x94cc
0f68 push ds
0f69 push 0x1103
0f6c nop 
0f6d push cs
0f6e call 0x62bc ; _WinPrintf
0f71 add sp, 4
0f74 mov ax, word ptr [bp - 0x1a]
0f77 mov dx, word ptr [bp - 0x18]
0f7a add ax, 1
0f7d adc dx, 0
0f80 mov word ptr [bp - 0x1a], ax
0f83 mov word ptr [bp - 0x18], dx
0f86 sub word ptr [bp - 0x1e], 1
0f8a sbb word ptr [bp - 0x1c], 0
0f8e lea ax, [bp - 0x1e]
0f91 push ss
0f92 push ax
0f93 lea cx, [bp - 0x24]
0f96 push ss
0f97 push cx
0f98 lea dx, [bp - 0x1a]
0f9b push ss
0f9c push dx
0f9d nop 
0f9e push cs
0f9f call 0x843a ; _ExtractVariableLen
0fa2 add sp, 0xc
0fa5 mov ax, word ptr [bp - 0x24]
0fa8 mov dx, word ptr [bp - 0x22]
0fab add ax, word ptr [bp - 0x1a]
0fae adc dx, word ptr [bp - 0x18]
0fb1 mov word ptr [bp - 0x1a], ax
0fb4 mov word ptr [bp - 0x18], dx
0fb7 mov ax, word ptr [bp - 0x24]
0fba mov dx, word ptr [bp - 0x22]
0fbd sub word ptr [bp - 0x1e], ax
0fc0 sbb word ptr [bp - 0x1c], dx
0fc3 cmp word ptr [bp - 0x1c], 0
0fc7 je 0x955a
0fc9 jmp 0x91b9
0fcc cmp word ptr [bp - 0x1e], 1
0fd0 jbe 0x9563
0fd2 jmp 0x91b9
0fd5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 4054, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 9}}]
0fda jmp 0x9582
0fdc push ds
0fdd push 0x1125
0fe0 jmp 0x957a
0fe2 push ds
0fe3 push 0x113b
0fe6 jmp 0x957a
0fe8 push ds
0fe9 push 0x1151
0fec nop 
0fed push cs
0fee call 0x62bc ; _WinPrintf
0ff1 add sp, 4
0ff4 push word ptr [bp - 0x20]
0ff7 nop 
0ff8 push cs
0ff9 call 0x559c ; _mem_Unlock
0ffc add sp, 2
0fff push word ptr [bp - 0x20]
1002 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 4101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_ReleaseHandle
1007 add sp, 2
100a pop si
100b pop di
100c leave 
100d retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern unsigned long far FlipLong(unsigned long value);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern unsigned short FlipWord(unsigned short);` — src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern int near hInst;` — src/recovered/wf_tu_simant_01B6_DoUserButtonUpdate_13_scaffold-11b35534e1.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far songsOnFlag;` — src/recovered/wf_SetMenuEntries-c937b84870.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c
- `extern char far * far strrchr(const char far *text, int character);` — src/recovered/wf_SpecialTutorialInit-e0cff25916.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_mem_Lock'], 'segment': 2, 'target_offset': 21902, 'caller_offsets': [72, 1498, 2115]}
- {'callee_names': ['_mem_Unlock'], 'segment': 2, 'target_offset': 21916, 'caller_offsets': [182, 1783, 4089]}
- {'callee_names': ['_mem_Size'], 'segment': 2, 'target_offset': 21930, 'caller_offsets': [1517, 1561]}
- {'callee_names': ['_WinPrintf'], 'segment': 2, 'target_offset': 25276, 'caller_offsets': [41, 261, 469, 577, 787, 834, 888, 942, 954, 996, 1040, 1064, 1184, 1279, 1414, 1772, 1860, 1955, 2159, 2279, 2417, 2575, 2597, 2829, 3011, 3465, 3630, 3846, 3874, 3914, 3950, 4078]}
- {'callee_names': ['_ExtractVariableLen'], 'segment': 2, 'target_offset': 33850, 'caller_offsets': [2557, 3132, 3999]}

## Neighbors

- {'symbol': '_ExtractVariableLen', 'offset': 33850, 'source': None, 'size': 222}
- {'symbol': '_Extract24BitVal', 'offset': 34072, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 118}
- {'symbol': '_MciOutWave', 'offset': 38300, 'source': None, 'size': 788}
- {'symbol': '_myBeginSound', 'offset': 39088, 'source': None, 'size': 2263}
