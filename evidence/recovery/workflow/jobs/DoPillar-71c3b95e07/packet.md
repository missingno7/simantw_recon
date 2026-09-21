# Recovery task _DoPillar

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 1576 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc59a]
000a cmp word ptr es:[0x9b6e], 1
0010 jne 0x4cf1
0012 jmp 0x5300
0015 nop 
0016 push cs
0017 call 0x3f8a ; _DoSow
001a mov bx, 0x8a8a
001d mov es, word ptr [0xc59c]
0021 mov word ptr [bp - 0xa], bx
0024 mov word ptr [bp - 8], es
0027 cmp word ptr es:[bx], 0
002b jne 0x4d26
002d nop 
002e push cs
002f call 0x53da ; _MakeAPill
0032 les bx, ptr [bp - 0xa]
0035 mov word ptr es:[bx], 1
003a mov es, word ptr [0xc59e]
003e mov word ptr es:[0x78d4], 4
0045 pop si
0046 pop di
0047 leave 
0048 retf 
0049 nop 
004a mov bx, 0x9b1e
004d mov es, word ptr [0xc5a0]
0051 mov word ptr [bp - 0xe], bx
0054 mov word ptr [bp - 0xc], es
0057 mov ax, word ptr es:[bx]
005a or ax, ax
005c je 0x4d4c
005e dec ax
005f je 0x4d72
0061 dec ax
0062 je 0x4d88
0064 dec ax
0065 je 0x4d9e
0067 mov dx, word ptr [bp - 2]
006a jmp 0x4dca
006d nop 
006e nop 
006f nop 
0070 mov es, word ptr [0xc5a2]
0074 mov di, word ptr es:[0x8a8e]
0079 dec di
007a push di
007b mov es, word ptr [0xc5a4]
007f mov si, word ptr es:[0x8a8c]
0084 push si
0085 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
008a add sp, 4
008d or ax, ax
008f jne 0x4dbf
0091 xor dx, dx
0093 jmp 0x4dca
0095 nop 
0096 mov es, word ptr [0xc5a2]
009a mov di, word ptr es:[0x8a8e]
009f push di
00a0 mov es, word ptr [0xc5a4]
00a4 mov si, word ptr es:[0x8a8c]
00a9 inc si
00aa jmp 0x4db2
00ac mov es, word ptr [0xc5a2]
00b0 mov di, word ptr es:[0x8a8e]
00b5 inc di
00b6 push di
00b7 mov es, word ptr [0xc5a4]
00bb mov si, word ptr es:[0x8a8c]
00c0 jmp 0x4db2
00c2 mov es, word ptr [0xc5a2]
00c6 mov di, word ptr es:[0x8a8e]
00cb push di
00cc mov es, word ptr [0xc5a4]
00d0 mov si, word ptr es:[0x8a8c]
00d5 dec si
00d6 push si
00d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
00dc add sp, 4
00df or ax, ax
00e1 je 0x4d6d
00e3 mov bx, si
00e5 shl bx, 6
00e8 mov dl, byte ptr [bx + di + 0x68e8]
00ec sub dh, dh
00ee or dx, dx
00f0 jne 0x4dd1
00f2 jmp 0x4e8e
00f5 xor di, di
00f7 mov bx, 0x8a8c
00fa mov es, word ptr [0xc5a4]
00fe mov word ptr [bp - 0x12], bx
0101 mov word ptr [bp - 0x10], es
0104 mov cx, word ptr es:[bx]
0107 mov ax, cx
0109 dec cx
010a add ax, 2
010d cmp cx, ax
010f jge 0x4e67
0111 mov word ptr [bp - 6], di
0114 mov ax, cx
0116 shl ax, 6
0119 mov word ptr [bp - 4], ax
011c mov ax, 0x8a8e
011f mov <resolved loader operand; see bindings> ; [{'operand_offset': 288, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0122 mov word ptr [bp - 0x16], ax
0125 mov word ptr [bp - 0x14], dx
0128 les bx, ptr [bp - 0x16]
012b mov si, word ptr es:[bx]
012e mov ax, si
0130 dec si
0131 add ax, 2
0134 cmp si, ax
0136 jge 0x4e52
0138 mov di, word ptr [bp - 6]
013b mov word ptr [bp - 2], cx
013e push si
013f push word ptr [bp - 2]
0142 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 325, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0147 add sp, 4
014a or ax, ax
014c jne 0x4e30
014e xor dx, dx
0150 jmp 0x4e39
0152 nop 
0153 nop 
0154 mov bx, word ptr [bp - 4]
0157 mov dl, byte ptr [bx + si + 0x68e8]
015b sub dh, dh
015d or dx, dx
015f je 0x4e3e
0161 inc di
0162 les bx, ptr [bp - 0x16]
0165 mov ax, word ptr es:[bx]
0168 add ax, 2
016b inc si
016c cmp ax, si
016e jg 0x4e1a
0170 mov word ptr [bp - 6], di
0173 mov cx, word ptr [bp - 2]
0176 add word ptr [bp - 4], 0x40
017a les bx, ptr [bp - 0x12]
017d mov ax, word ptr es:[bx]
0180 add ax, 2
0183 inc cx
0184 cmp ax, cx
0186 jg 0x4e04
0188 mov di, word ptr [bp - 6]
018b cmp di, 5
018e jle 0x4e72
0190 mov dx, 1
0193 jmp 0x4e74
0195 nop 
0196 xor dx, dx
0198 cmp dx, 1
019b je 0x4e7c
019d jmp 0x5300
01a0 les bx, ptr [bp - 0xa]
01a3 mov word ptr es:[bx], 0
01a8 nop 
01a9 push cs
01aa call 0x57d2 ; _MakePillFood
01ad pop si
01ae pop di
01af leave 
01b0 retf 
01b1 nop 
01b2 mov bx, 0x78d4
01b5 mov es, word ptr [0xc59e]
01b9 mov word ptr [bp - 0x1a], bx
01bc mov word ptr [bp - 0x18], es
01bf dec word ptr es:[bx]
01c2 cmp word ptr es:[bx], 4
01c6 je 0x4ea7
01c8 jmp 0x4f8e
01cb les bx, ptr [bp - 0xe]
01ce mov ax, word ptr es:[bx]
01d1 or ax, ax
01d3 je 0x4ec4
01d5 dec ax
01d6 je 0x4f18
01d8 dec ax
01d9 jne 0x4eba
01db jmp 0x4f5a
01de dec ax
01df jne 0x4ec0
01e1 jmp 0x4f70
01e4 jmp 0x503c
01e7 nop 
01e8 les bx, ptr [bp - 0x1a]
01eb mov di, word ptr es:[bx]
01ee mov es, word ptr [0xc5a2]
01f2 add di, word ptr es:[0x8a8e]
01f7 inc di
01f8 push di
01f9 mov es, word ptr [0xc5a4]
01fd mov si, word ptr es:[0x8a8c]
0202 push si
0203 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 518, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0208 add sp, 4
020b dec ax
020c je 0x4eed
020e jmp 0x503c
0211 les bx, ptr [bp - 0xe]
0214 test byte ptr es:[bx], 1
0218 je 0x4f38
021a mov ax, si
021c mov cx, 6
021f cdq 
0220 idiv cx
0222 mov es, word ptr [0xc5a6]
0226 mov bx, dx
0228 shl bx, 1
022a mov al, byte ptr es:[bx + 0x7c0e]
022f mov bx, si
0231 shl bx, 6
0234 mov byte ptr [bx + di + 0x28e8], al
0238 jmp 0x503c
023b nop 
023c mov es, word ptr [0xc5a2]
0240 mov di, word ptr es:[0x8a8e]
0245 push di
0246 les bx, ptr [bp - 0x1a]
0249 mov es, word ptr [0xc5a4]
024d mov si, word ptr es:[0x8a8c]
0252 mov es, word ptr [bp - 0x18]
0255 sub si, word ptr es:[bx]
0258 dec si
0259 jmp 0x4ede
025b nop 
025c mov ax, di
025e mov cx, 6
0261 mov bx, ax
0263 cdq 
0264 idiv cx
0266 mov es, word ptr [0xc5a6]
026a mov di, dx
026c shl di, 1
026e mov al, byte ptr es:[di + 0x7c0e]
0273 shl si, 6
0276 mov byte ptr [bx + si + 0x28e8], al
027a jmp 0x503c
027d nop 
027e les bx, ptr [bp - 0x1a]
0281 mov es, word ptr [0xc5a2]
0285 mov di, word ptr es:[0x8a8e]
028a mov es, word ptr [bp - 0x18]
028d sub di, word ptr es:[bx]
0290 dec di
0291 jmp 0x4ed4
0294 mov es, word ptr [0xc5a2]
0298 mov di, word ptr es:[0x8a8e]
029d push di
029e les bx, ptr [bp - 0x1a]
02a1 mov si, word ptr es:[bx]
02a4 mov es, word ptr [0xc5a4]
02a8 add si, word ptr es:[0x8a8c]
02ad inc si
02ae jmp 0x4ede
02b1 nop 
02b2 les bx, ptr [bp - 0xe]
02b5 mov ax, word ptr es:[bx]
02b8 or ax, ax
02ba je 0x4fa4
02bc dec ax
02bd je 0x4fd6
02bf dec ax
02c0 je 0x4ff6
02c2 dec ax
02c3 je 0x500c
02c5 jmp 0x503c
02c8 les bx, ptr [bp - 0x1a]
02cb mov di, word ptr es:[bx]
02ce mov es, word ptr [0xc5a2]
02d2 add di, word ptr es:[0x8a8e]
02d7 inc di
02d8 push di
02d9 mov es, word ptr [0xc5a4]
02dd mov si, word ptr es:[0x8a8c]
02e2 push si
02e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 742, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
02e8 add sp, 4
02eb dec ax
02ec jne 0x503c
02ee mov bx, si
02f0 shl bx, 6
02f3 mov byte ptr [bx + di + 0x28e8], 0x6d
02f8 jmp 0x503c
02fa mov es, word ptr [0xc5a2]
02fe mov di, word ptr es:[0x8a8e]
0303 push di
0304 les bx, ptr [bp - 0x1a]
0307 mov es, word ptr [0xc5a4]
030b mov si, word ptr es:[0x8a8c]
0310 mov es, word ptr [bp - 0x18]
0313 sub si, word ptr es:[bx]
0316 dec si
0317 jmp 0x5026
0319 nop 
031a les bx, ptr [bp - 0x1a]
031d mov es, word ptr [0xc5a2]
0321 mov di, word ptr es:[0x8a8e]
0326 mov es, word ptr [bp - 0x18]
0329 sub di, word ptr es:[bx]
032c dec di
032d jmp 0x4fb4
032f nop 
0330 mov es, word ptr [0xc5a2]
0334 mov di, word ptr es:[0x8a8e]
0339 push di
033a les bx, ptr [bp - 0x1a]
033d mov si, word ptr es:[bx]
0340 mov es, word ptr [0xc5a4]
0344 add si, word ptr es:[0x8a8c]
0349 inc si
034a push si
034b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 846, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0350 add sp, 4
0353 dec ax
0354 jne 0x503c
0356 mov bx, si
0358 shl bx, 6
035b mov byte ptr [bx + di + 0x28e8], 0x69
0360 les bx, ptr [bp - 0xe]
0363 mov ax, word ptr es:[bx]
0366 or ax, ax
0368 je 0x5052
036a dec ax
036b je 0x5084
036d dec ax
036e je 0x50a2
0370 dec ax
0371 je 0x50b6
0373 jmp 0x50e5
0376 les bx, ptr [bp - 0x1a]
0379 mov di, word ptr es:[bx]
037c mov es, word ptr [0xc5a2]
0380 add di, word ptr es:[0x8a8e]
0385 push di
0386 mov es, word ptr [0xc5a4]
038a mov si, word ptr es:[0x8a8c]
038f push si
0390 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 915, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0395 add sp, 4
0398 dec ax
0399 jne 0x50e5
039b mov bx, si
039d shl bx, 6
03a0 mov byte ptr [bx + di + 0x28e8], 0x6e
03a5 jmp 0x50e5
03a7 nop 
03a8 mov es, word ptr [0xc5a2]
03ac mov di, word ptr es:[0x8a8e]
03b1 push di
03b2 les bx, ptr [bp - 0x1a]
03b5 mov es, word ptr [0xc5a4]
03b9 mov si, word ptr es:[0x8a8c]
03be mov es, word ptr [bp - 0x18]
03c1 sub si, word ptr es:[bx]
03c4 jmp 0x50cf
03c6 les bx, ptr [bp - 0x1a]
03c9 mov es, word ptr [0xc5a2]
03cd mov di, word ptr es:[0x8a8e]
03d2 mov es, word ptr [bp - 0x18]
03d5 sub di, word ptr es:[bx]
03d8 jmp 0x5061
03da mov es, word ptr [0xc5a2]
03de mov di, word ptr es:[0x8a8e]
03e3 push di
03e4 les bx, ptr [bp - 0x1a]
03e7 mov si, word ptr es:[bx]
03ea mov es, word ptr [0xc5a4]
03ee add si, word ptr es:[0x8a8c]
03f3 push si
03f4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1015, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
03f9 add sp, 4
03fc dec ax
03fd jne 0x50e5
03ff mov bx, si
0401 shl bx, 6
0404 mov byte ptr [bx + di + 0x28e8], 0x6a
0409 les bx, ptr [bp - 0x1a]
040c cmp word ptr es:[bx], 0
0410 je 0x50f1
0412 jmp 0x5300
0415 les bx, ptr [bp - 0xe]
0418 mov ax, word ptr es:[bx]
041b or ax, ax
041d je 0x5106
041f dec ax
0420 je 0x5112
0422 dec ax
0423 je 0x511e
0425 dec ax
0426 je 0x512a
0428 jmp 0x5133
042a mov es, word ptr [0xc5a2]
042e dec word ptr es:[0x8a8e]
0433 jmp 0x5133
0435 nop 
0436 mov es, word ptr [0xc5a4]
043a inc word ptr es:[0x8a8c]
043f jmp 0x5133
0441 nop 
0442 mov es, word ptr [0xc5a2]
0446 inc word ptr es:[0x8a8e]
044b jmp 0x5133
044d nop 
044e mov es, word ptr [0xc5a4]
0452 dec word ptr es:[0x8a8c]
0457 mov bx, 0x8a8c
045a mov es, word ptr [0xc5a4]
045e mov word ptr [bp - 0x12], bx
0461 mov word ptr [bp - 0x10], es
0464 cmp word ptr es:[bx], -6
0468 jge 0x5149
046a jmp 0x52f8
046d cmp word ptr es:[bx], 0x86
0472 jle 0x5153
0474 jmp 0x52f8
0477 mov bx, 0x8a8e
047a mov es, word ptr [0xc5a2]
047e mov word ptr [bp - 0x16], bx
0481 mov word ptr [bp - 0x14], es
0484 cmp word ptr es:[bx], -6
0488 jge 0x5169
048a jmp 0x52f8
048d cmp word ptr es:[bx], 0x45
0491 jle 0x5172
0493 jmp 0x52f8
0496 mov di, word ptr es:[bx]
0499 push di
049a les bx, ptr [bp - 0x12]
049d mov si, word ptr es:[bx]
04a0 push si
04a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1188, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
04a6 add sp, 4
04a9 dec ax
04aa jne 0x51d6
04ac les bx, ptr [bp - 0xe]
04af test byte ptr es:[bx], 1
04b3 je 0x51b2
04b5 mov bx, si
04b7 shl bx, 6
04ba mov al, byte ptr [bx + di + 0x28e8]
04be sub ah, ah
04c0 mov cx, ax
04c2 mov ax, si
04c4 mov dx, 6
04c7 mov bx, dx
04c9 cdq 
04ca idiv bx
04cc mov bx, dx
04ce shl bx, 1
04d0 mov es, word ptr [0xc5a6]
04d4 jmp 0x51d1
04d6 mov bx, si
04d8 shl bx, 6
04db mov al, byte ptr [bx + di + 0x28e8]
04df mov cx, ax
04e1 mov ax, di
04e3 mov dx, 6
04e6 mov bx, dx
04e8 cdq 
04e9 idiv bx
04eb mov bx, dx
04ed shl bx, 1
04ef mov es, word ptr [0xc5a6]
04f3 sub ch, ch
04f5 mov word ptr es:[bx + 0x7c0e], cx
04fa les bx, ptr [bp - 0xe]
04fd mov ax, word ptr es:[bx]
0500 or ax, ax
0502 je 0x51f4
0504 dec ax
0505 je 0x5242
0507 dec ax
0508 jne 0x51e9
050a jmp 0x5276
050d dec ax
050e jne 0x51ef
0510 jmp 0x52a4
0513 jmp 0x52eb
0516 nop 
0517 nop 
0518 les bx, ptr [bp - 0x16]
051b mov di, word ptr es:[bx]
051e push di
051f les bx, ptr [bp - 0x12]
0522 mov si, word ptr es:[bx]
0525 push si
0526 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1321, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
052b add sp, 4
052e dec ax
052f jne 0x5217
0531 mov bx, si
0533 shl bx, 6
0536 mov byte ptr [bx + di + 0x28e8], 0x6c
053b les bx, ptr [bp - 0x16]
053e mov di, word ptr es:[bx]
0541 inc di
0542 push di
0543 les bx, ptr [bp - 0x12]
0546 mov si, word ptr es:[bx]
0549 push si
054a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1357, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
054f add sp, 4
0552 dec ax
0553 je 0x5234
0555 jmp 0x52eb
0558 mov bx, si
055a shl bx, 6
055d mov byte ptr [bx + di + 0x28e8], 0x6d
0562 jmp 0x52eb
0565 nop 
0566 les bx, ptr [bp - 0x16]
0569 mov di, word ptr es:[bx]
056c push di
056d les bx, ptr [bp - 0x12]
0570 mov si, word ptr es:[bx]
0573 push si
0574 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1399, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0579 add sp, 4
057c dec ax
057d jne 0x5265
057f mov bx, si
0581 shl bx, 6
0584 mov byte ptr [bx + di + 0x28e8], 0x6b
0589 les bx, ptr [bp - 0x16]
058c mov di, word ptr es:[bx]
058f push di
0590 les bx, ptr [bp - 0x12]
0593 mov si, word ptr es:[bx]
0596 dec si
0597 jmp 0x52d5
0599 nop 
059a les bx, ptr [bp - 0x16]
059d mov di, word ptr es:[bx]
05a0 push di
05a1 les bx, ptr [bp - 0x12]
05a4 mov si, word ptr es:[bx]
05a7 push si
05a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1451, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
05ad add sp, 4
05b0 dec ax
05b1 jne 0x5299
05b3 mov bx, si
05b5 shl bx, 6
05b8 mov byte ptr [bx + di + 0x28e8], 0x6f
05bd les bx, ptr [bp - 0x16]
05c0 mov di, word ptr es:[bx]
05c3 dec di
05c4 jmp 0x521e
05c7 nop 
05c8 les bx, ptr [bp - 0x16]
05cb mov di, word ptr es:[bx]
05ce push di
05cf les bx, ptr [bp - 0x12]
05d2 mov si, word ptr es:[bx]
05d5 push si
05d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1497, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
05db add sp, 4
05de dec ax
05df jne 0x52c7
05e1 mov bx, si
05e3 shl bx, 6
05e6 mov byte ptr [bx + di + 0x28e8], 0x68
05eb les bx, ptr [bp - 0x16]
05ee mov di, word ptr es:[bx]
05f1 push di
05f2 les bx, ptr [bp - 0x12]
05f5 mov si, word ptr es:[bx]
05f8 inc si
05f9 push si
05fa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1533, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
05ff add sp, 4
0602 dec ax
0603 jne 0x52eb
0605 mov bx, si
0607 shl bx, 6
060a mov byte ptr [bx + di + 0x28e8], 0x69
060f les bx, ptr [bp - 0x1a]
0612 mov word ptr es:[bx], 5
0617 pop si
0618 pop di
0619 leave 
061a retf 
061b nop 
061c les bx, ptr [bp - 0xa]
061f mov word ptr es:[bx], 0
0624 pop si
0625 pop di
0626 leave 
0627 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_IsPillDead-8cef0d554b.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_KillAntLion', 'offset': 19288, 'source': None, 'size': 160}
- {'symbol': '_InitPillar', 'offset': 19448, 'source': None, 'size': 228}
- {'symbol': '_StorePillarMap', 'offset': 21252, 'source': None, 'size': 110}
- {'symbol': '_ReplacePillarMap', 'offset': 21362, 'source': None, 'size': 104}
