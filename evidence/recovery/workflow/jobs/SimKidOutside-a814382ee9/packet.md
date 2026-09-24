# Recovery task _SimKidOutside

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 2240 bytes.

```asm
0000 enter 0x22, 0
0004 push di
0005 push si
0006 mov bx, 0x8a7e
0009 mov es, word ptr [0xc514]
000d mov word ptr [bp - 0xc], bx
0010 mov word ptr [bp - 0xa], es
0013 cmp word ptr es:[bx], 0
0017 je 0x16c4
0019 mov es, word ptr [0xc52c]
001d test byte ptr es:[0x7a5c], 3
0023 je 0x16c4
0025 jmp 0x1f56
0028 mov bx, 0x7c92
002b mov es, word ptr [0xc520]
002f mov word ptr [bp - 0x10], bx
0032 mov word ptr [bp - 0xe], es
0035 cmp word ptr es:[bx], 0
0039 jne 0x16da
003b jmp 0x1812
003e mov es, word ptr [0xc506]
0042 mov ax, word ptr es:[0x78b0]
0046 mov es, word ptr [0xc534]
004a cmp word ptr es:[0x9bbe], ax
004f jne 0x1703
0051 mov es, word ptr [0xc508]
0055 mov ax, word ptr es:[0x78d2]
0059 mov es, word ptr [0xc536]
005d cmp word ptr es:[0x9bd4], ax
0062 jne 0x1703
0064 jmp 0x1844
0067 mov es, word ptr [0xc506]
006b mov ax, word ptr es:[0x78b0]
006f mov word ptr [bp - 6], ax
0072 mov es, word ptr [0xc508]
0076 mov ax, word ptr es:[0x78d2]
007a mov word ptr [bp - 8], ax
007d mov word ptr [bp - 4], 3
0082 mov <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0085 mov es, ax
0087 mov bx, word ptr [bp - 4]
008a mov al, byte ptr [bx + 0x25d4]
008e cwde 
008f mov si, ax
0091 add si, word ptr [bp - 6]
0094 mov al, byte ptr [bx + 0x25d8]
0098 cwde 
0099 mov di, ax
009b add di, word ptr [bp - 8]
009e or si, si
00a0 jl 0x1752
00a2 or di, di
00a4 jl 0x1752
00a6 cmp si, 0xb
00a9 jg 0x1752
00ab cmp di, 0xf
00ae jg 0x1752
00b0 mov dx, 1
00b3 jmp 0x1754
00b5 nop 
00b6 xor dx, dx
00b8 or dx, dx
00ba je 0x1780
00bc mov bx, si
00be shl bx, 1
00c0 mov cx, di
00c2 mov ax, 1
00c5 shl ax, cl
00c7 mov word ptr [bp - 2], ax
00ca test word ptr es:[bx - 0x5f4a], ax
00cf je 0x177a
00d1 shl si, 1
00d3 sub word ptr es:[si - 0x5f4a], ax
00d8 mov bx, 1
00db jmp 0x177c
00dd nop 
00de xor bx, bx
00e0 or bx, bx
00e2 jne 0x179a
00e4 dec word ptr [bp - 4]
00e7 jns 0x1723
00e9 cmp word ptr [bp - 6], 0xa
00ed jle 0x17a8
00ef mov es, word ptr [0xc500]
00f3 mov word ptr es:[0x8a72], 0
00fa jmp 0x1844
00fd nop 
00fe mov ax, word ptr [bp - 4]
0101 mov es, word ptr [0xc500]
0105 mov word ptr es:[0x8a72], ax
0109 jmp 0x1844
010c mov bx, word ptr [bp - 8]
010f cmp bx, 0xe
0112 jle 0x17be
0114 mov es, word ptr [0xc500]
0118 mov word ptr es:[0x8a72], 1
011f jmp 0x1844
0122 cmp bx, 1
0125 jge 0x1804
0127 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 298, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
012c add ax, 0x12c
012f adc dx, 0
0132 mov es, word ptr [0xc4f6]
0136 mov word ptr es:[0x7d4a], ax
013a mov word ptr es:[0x7d4c], dx
013f mov es, word ptr [0xc504]
0143 mov word ptr es:[0x99da], 1
014a mov es, word ptr [0xc52a]
014e mov word ptr es:[0x72f2], 6
0155 mov word ptr [0xac74], 4 ; _BoyHere
015b mov es, word ptr [0xc500]
015f mov word ptr es:[0x8a72], 2
0166 jmp 0x1844
0168 mov es, word ptr [0xc52c]
016c mov al, byte ptr es:[0x7a5c]
0170 and ax, 3
0173 jmp 0x179d
0175 nop 
0176 mov es, word ptr [0xc4f8]
017a dec word ptr es:[0x8a74]
017f jns 0x1844
0181 push 3
0183 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 390, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0188 add sp, 2
018b mov es, word ptr [0xc500]
018f add al, byte ptr es:[0x8a72]
0194 dec al
0196 and ax, 3
0199 mov word ptr es:[0x8a72], ax
019d mov es, word ptr [0xc4f8]
01a1 mov word ptr es:[0x8a74], 4
01a8 mov ax, word ptr [0xac74] ; _BoyHere
01ab dec ax
01ac je 0x1866
01ae dec ax
01af jne 0x1850
01b1 jmp 0x1960
01b4 dec ax
01b5 jne 0x1856
01b7 jmp 0x1a0c
01ba dec ax
01bb jne 0x185c
01bd jmp 0x1ac8
01c0 dec ax
01c1 jne 0x1862
01c3 jmp 0x1b46
01c6 jmp 0x1b76
01c9 nop 
01ca push 0x384
01cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 464, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
01d2 add sp, 2
01d5 or ax, ax
01d7 jne 0x18aa
01d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 476, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
01de add ax, 0x12c
01e1 adc dx, 0
01e4 mov es, word ptr [0xc4f6]
01e8 mov word ptr es:[0x7d4a], ax
01ec mov word ptr es:[0x7d4c], dx
01f1 mov ax, 1
01f4 mov es, word ptr [0xc504]
01f8 mov word ptr es:[0x99da], ax
01fc mov es, word ptr [0xc52a]
0200 mov word ptr es:[0x72f2], ax
0204 mov word ptr [0xac74], 2 ; _BoyHere
020a jmp 0x1b76
020d nop 
020e push 0x258
0211 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 532, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0216 add sp, 2
0219 or ax, ax
021b je 0x1930
021d mov <resolved loader operand; see bindings> ; [{'operand_offset': 542, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0220 mov es, ax
0222 cmp word ptr es:[0x80b4], 3
0228 je 0x1930
022a cmp word ptr es:[0x80b4], 0
0230 je 0x1930
0232 push 0xc8
0235 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 568, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
023a add sp, 2
023d or ax, ax
023f jne 0x191d
0241 push 8
0243 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 582, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0248 add sp, 2
024b mov si, ax
024d add si, 7
0250 cmp si, 0x16
0253 jg 0x191d
0255 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 600, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
025a add ax, 0x12c
025d adc dx, 0
0260 mov es, word ptr [0xc4f6]
0264 mov word ptr es:[0x7d4a], ax
0268 mov word ptr es:[0x7d4c], dx
026d mov es, word ptr [0xc504]
0271 mov word ptr es:[0x99da], 1
0278 mov es, word ptr [0xc52a]
027c mov word ptr es:[0x72f2], si
0281 cmp word ptr [0xac72], 0 ; _RainOn
0286 jne 0x1927
0288 jmp 0x1b76
028b mov word ptr [0xac74], 5 ; _BoyHere
0291 jmp 0x1b76
0294 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 663, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0299 add ax, 0x12c
029c adc dx, 0
029f mov es, word ptr [0xc4f6]
02a3 mov word ptr es:[0x7d4a], ax
02a7 mov word ptr es:[0x7d4c], dx
02ac mov es, word ptr [0xc504]
02b0 mov word ptr es:[0x99da], 1
02b7 mov es, word ptr [0xc52a]
02bb mov word ptr es:[0x72f2], 2
02c2 jmp 0x1927
02c4 mov bx, 0x78d2
02c7 mov es, word ptr [0xc508]
02cb mov word ptr [bp - 0x14], bx
02ce mov word ptr [bp - 0x12], es
02d1 cmp word ptr es:[bx], 0xc
02d5 jge 0x1982
02d7 mov es, word ptr [0xc500]
02db mov word ptr es:[0x8a72], 2
02e2 jmp 0x1b76
02e5 nop 
02e6 les bx, ptr [bp - 0x14]
02e9 cmp word ptr es:[bx], 0xc
02ed jle 0x199a
02ef mov es, word ptr [0xc500]
02f3 mov word ptr es:[0x8a72], 0
02fa jmp 0x1b76
02fd nop 
02fe mov es, word ptr [0xc506]
0302 cmp word ptr es:[0x78b0], 3
0308 jle 0x19b4
030a mov es, word ptr [0xc500]
030e mov word ptr es:[0x8a72], 3
0315 jmp 0x1b76
0318 mov ax, 3
031b mov word ptr [0xac74], ax ; _BoyHere
031e mov es, word ptr [0xc534]
0322 mov word ptr es:[0x9bbe], ax
0326 mov es, word ptr [0xc536]
032a mov word ptr es:[0x9bd4], 0xd
0331 les bx, ptr [bp - 0x10]
0334 mov word ptr es:[bx], 1
0339 xor ax, ax
033b mov es, word ptr [0xc538]
033f mov word ptr es:[0xa0b6], ax
0343 mov word ptr es:[0xa0b8], ax
0347 mov word ptr es:[0xa0ba], ax
034b mov ax, 0xffff
034e mov cx, 9
0351 mov di, 0xa0bc
0354 rep stosw word ptr es:[di], ax
0356 mov es, word ptr [0xc500]
035a mov word ptr es:[0x8a72], 2
0361 mov word ptr [0xac76], 0x7d ; _BoyX
0367 mov word ptr [0xac78], 0xaa ; _BoyY
036d jmp 0x1b76
0370 push 0x64
0372 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 885, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0377 add sp, 2
037a or ax, ax
037c jne 0x1a5a
037e push 3
0380 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 899, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0385 add sp, 2
0388 mov si, ax
038a add si, 3
038d cmp si, 0x16
0390 jg 0x1a5a
0392 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 917, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0397 add ax, 0x12c
039a adc dx, 0
039d mov es, word ptr [0xc4f6]
03a1 mov word ptr es:[0x7d4a], ax
03a5 mov word ptr es:[0x7d4c], dx
03aa mov es, word ptr [0xc504]
03ae mov word ptr es:[0x99da], 1
03b5 mov es, word ptr [0xc52a]
03b9 mov word ptr es:[0x72f2], si
03be push 0xc8
03c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 964, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
03c6 add sp, 2
03c9 or ax, ax
03cb jne 0x1a9d
03cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 976, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
03d2 add ax, 0x12c
03d5 adc dx, 0
03d8 mov es, word ptr [0xc4f6]
03dc mov word ptr es:[0x7d4a], ax
03e0 mov word ptr es:[0x7d4c], dx
03e5 mov es, word ptr [0xc504]
03e9 mov word ptr es:[0x99da], 1
03f0 mov es, word ptr [0xc52a]
03f4 mov word ptr es:[0x72f2], 6
03fb mov word ptr [0xac74], 4 ; _BoyHere
0401 mov es, word ptr [0xc506]
0405 mov ax, word ptr es:[0x78b0]
0409 mov es, word ptr [0xc534]
040d mov word ptr es:[0x9bbe], ax
0411 mov es, word ptr [0xc508]
0415 mov ax, word ptr es:[0x78d2]
0419 mov es, word ptr [0xc536]
041d mov word ptr es:[0x9bd4], ax
0421 les bx, ptr [bp - 0x10]
0424 mov word ptr es:[bx], 1
0429 jmp 0x1b76
042c mov bx, 0x78d2
042f mov es, word ptr [0xc508]
0433 mov word ptr [bp - 0x14], bx
0436 mov word ptr [bp - 0x12], es
0439 cmp word ptr es:[bx], 0xc
043d jge 0x1ae8
043f mov es, word ptr [0xc500]
0443 mov word ptr es:[0x8a72], 2
044a jmp 0x1b26
044c les bx, ptr [bp - 0x14]
044f cmp word ptr es:[bx], 0xc
0453 jle 0x1afe
0455 mov es, word ptr [0xc500]
0459 mov word ptr es:[0x8a72], 0
0460 jmp 0x1b26
0462 mov es, word ptr [0xc506]
0466 cmp word ptr es:[0x78b0], 3
046c jle 0x1b18
046e mov es, word ptr [0xc500]
0472 mov word ptr es:[0x8a72], 3
0479 jmp 0x1b26
047b nop 
047c mov word ptr [0xac74], 5 ; _BoyHere
0482 les bx, ptr [bp - 0x10]
0485 mov word ptr es:[bx], 0
048a mov es, word ptr [0xc506]
048e mov ax, word ptr es:[0x78b0]
0492 mov es, word ptr [0xc534]
0496 mov word ptr es:[0x9bbe], ax
049a les bx, ptr [bp - 0x14]
049d mov ax, word ptr es:[bx]
04a0 mov es, word ptr [0xc536]
04a4 mov word ptr es:[0x9bd4], ax
04a8 jmp 0x1b76
04aa mov bx, 0x78d2
04ad mov es, word ptr [0xc508]
04b1 mov word ptr [bp - 0x14], bx
04b4 mov word ptr [bp - 0x12], es
04b7 cmp word ptr es:[bx], 5
04bb jge 0x1b5c
04bd jmp 0x1973
04c0 jle 0x1b61
04c2 jmp 0x198b
04c5 mov es, word ptr [0xc506]
04c9 cmp word ptr es:[0x78b0], 3
04cf jle 0x1b70
04d1 jmp 0x19a6
04d4 mov word ptr [0xac74], 1 ; _BoyHere
04da mov bx, 0x8a72
04dd mov es, word ptr [0xc500]
04e1 mov word ptr [bp - 0x18], bx
04e4 mov word ptr [bp - 0x16], es
04e7 mov bx, word ptr es:[bx]
04ea mov al, byte ptr [bx + 0x25c0]
04ee cwde 
04ef mov es, word ptr [0xc52c]
04f3 mov bl, byte ptr es:[0x7a5c]
04f8 and bx, 3
04fb mov cx, ax
04fd mov al, byte ptr [bx + 0x25bc]
0501 cwde 
0502 add cx, ax
0504 mov word ptr [0xac7a], cx ; _BoyFrame
0508 les bx, ptr [bp - 0x10]
050b cmp word ptr es:[bx], 0
050f je 0x1bd6
0511 add word ptr [0xac7a], 0x64 ; _BoyFrame
0516 les bx, ptr [bp - 0x18]
0519 mov bx, word ptr es:[bx]
051c mov es, word ptr [0xc53a]
0520 mov al, byte ptr es:[bx - 0x758a]
0525 cwde 
0526 add word ptr [0xac76], ax ; _BoyX
052a mov es, word ptr [0xc53c]
052e mov al, byte ptr es:[bx - 0x7586]
0533 cwde 
0534 add word ptr [0xac78], ax ; _BoyY
0538 jmp 0x1c0f
053a mov bx, 0x8a80
053d mov es, word ptr [0xc50a]
0541 mov word ptr [bp - 0x1c], bx
0544 mov word ptr [bp - 0x1a], es
0547 cmp word ptr es:[bx], 0
054b jne 0x1bfc
054d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1360, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
0552 or ax, ax
0554 jne 0x1bb2
0556 les bx, ptr [bp - 0x1c]
0559 mov word ptr es:[bx], 0x14
055e jmp 0x1bb2
0560 les bx, ptr [bp - 0x1c]
0563 dec word ptr es:[bx]
0566 les bx, ptr [bp - 0x18]
0569 mov ax, word ptr es:[bx]
056c add ax, 0x14
056f mov word ptr ss:[0xac7a], ax
0573 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1396, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0576 mov es, ax
0578 mov ax, word ptr ss:[0xac78]
057c add ax, word ptr ss:[0xac76]
0581 sub ax, 0xc8
0584 mov word ptr [bp - 0x1e], ax
0587 mov cx, 0x1c
058a cdq 
058b idiv cx
058d mov word ptr es:[0x78b0], ax
0591 mov ax, word ptr ss:[0xac78]
0595 sub ax, 0x26
0598 mov word ptr [bp - 0x20], ax
059b mov cx, 0xa
059e cdq 
059f idiv cx
05a1 mov bx, 0x78d2
05a4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1445, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
05a7 mov ds, cx
05a9 mov word ptr [bp - 0x14], bx
05ac mov word ptr [bp - 0x12], ds
05af mov word ptr [bx], ax
05b1 or ax, ax
05b3 jge 0x1c55
05b5 mov word ptr [bx], 0
05b9 lds bx, ptr [bp - 0x14]
05bc cmp word ptr [bx], 0xf
05bf jle 0x1c61
05c1 mov word ptr [bx], 0xf
05c5 cmp word ptr es:[0x78b0], 0
05cb jge 0x1c70
05cd mov word ptr es:[0x78b0], 0
05d4 cmp word ptr es:[0x78b0], 0xb
05da jle 0x1c7f
05dc mov word ptr es:[0x78b0], 0xb
05e3 lds bx, ptr [bp - 0x10]
05e6 cmp word ptr [bx], 0
05e9 jne 0x1cfe
05eb lds bx, ptr [bp - 0x14]
05ee cmp word ptr [bx], 1
05f1 jge 0x1c9a
05f3 lds bx, ptr [bp - 0x18]
05f6 mov word ptr [bx], 2
05fa jmp 0x1ca9
05fc nop 
05fd nop 
05fe mov ds, word ptr [bp - 0x12]
0601 cmp word ptr [bx], 0xe
0604 jle 0x1ca9
0606 lds bx, ptr [bp - 0x18]
0609 mov word ptr [bx], 0
060d cmp word ptr es:[0x78b0], 0xa
0613 jle 0x1cba
0615 lds bx, ptr [bp - 0x18]
0618 mov word ptr [bx], 3
061c jmp 0x1cfe
061e lds bx, ptr [bp - 0x14]
0621 cmp word ptr [bx], 5
0624 jge 0x1cd4
0626 cmp word ptr es:[0x78b0], 4
062c jge 0x1cfe
062e lds bx, ptr [bp - 0x18]
0631 mov word ptr [bx], 1
0635 jmp 0x1cfe
0637 nop 
0638 cmp word ptr es:[0x78b0], 3
063e jge 0x1cfe
0640 lds bx, ptr [bp - 0x18]
0643 mov word ptr [bx], 0
0647 lds bx, ptr [bp - 0x14]
064a cmp word ptr [bx], 6
064d jge 0x1cfe
064f cmp word ptr ss:[0xac74], 3
0655 je 0x1cca
0657 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1624, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
065a mov ds, ax
065c mov word ptr [0x8a86], 0x15
0662 lds bx, ptr [bp - 0xc]
0665 mov word ptr [bx], 0
0669 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1642, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
066c mov ds, ax
066e cmp word ptr [0x8a82], 1
0673 sbb ax, ax
0675 neg ax
0677 mov word ptr [0x8a82], ax
067a mov <resolved loader operand; see bindings> ; [{'operand_offset': 1659, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
067d mov ds, ax
067f mov ax, word ptr [0x7a62]
0682 lds bx, ptr [bp - 0x14]
0685 cmp word ptr [bx], ax
0687 je 0x1d28
0689 jmp 0x1edc
068c mov <resolved loader operand; see bindings> ; [{'operand_offset': 1677, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
068f mov ds, ax
0691 mov ax, word ptr [0x7a60]
0694 cmp word ptr es:[0x78b0], ax
0699 je 0x1d3a
069b jmp 0x1edc
069e les bx, ptr [bp - 0xc]
06a1 mov word ptr es:[bx], 1
06a6 mov ax, word ptr [bp - 0x20]
06a9 mov cx, 0xa
06ac cdq 
06ad idiv cx
06af mov <resolved loader operand; see bindings> ; [{'operand_offset': 1712, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
06b2 mov es, ax
06b4 mov word ptr es:[0x7a58], dx
06b9 mov ax, word ptr [bp - 0x1e]
06bc mov cx, 0x1c
06bf mov bx, dx
06c1 cdq 
06c2 idiv cx
06c4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1733, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
06c7 mov ds, ax
06c9 mov word ptr [0x7a4e], dx
06cd shl dl, 2
06d0 add dl, 6
06d3 and dx, 0x7f
06d6 mov word ptr [0x7a4e], dx
06da lea ax, [bx + 1]
06dd mov cx, ax
06df shl ax, 1
06e1 add ax, cx
06e3 shl ax, 1
06e5 and ax, 0x3f
06e8 mov word ptr es:[0x7a58], ax
06ec les bx, ptr [bp - 0x18]
06ef mov bx, word ptr es:[bx]
06f2 mov cx, bx
06f4 and bx, 3
06f7 shl bx, 1
06f9 add dx, word ptr ss:[bx + 0x25c4]
06fe mov <resolved loader operand; see bindings> ; [{'operand_offset': 1791, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0701 mov es, si
0703 mov word ptr es:[0x9af4], dx
0708 add ax, word ptr ss:[bx + 0x25cc]
070d mov <resolved loader operand; see bindings> ; [{'operand_offset': 1806, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0710 mov es, dx
0712 mov word ptr es:[0x9afc], ax
0716 test cl, 1
0719 je 0x1de0
071b mov <resolved loader operand; see bindings> ; [{'operand_offset': 1820, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
071e mov es, ax
0720 cmp word ptr es:[0x8a82], 0
0726 je 0x1dd2
0728 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1833, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
072b mov es, ax
072d add word ptr es:[0x7a58], 6
0733 jmp 0x1e05
0735 nop 
0736 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1847, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0739 mov es, ax
073b sub word ptr es:[0x7a58], 6
0741 jmp 0x1e05
0743 nop 
0744 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1861, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0747 mov es, ax
0749 cmp word ptr es:[0x8a82], 0
074f je 0x1dfa
0751 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1874, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0754 mov es, ax
0756 add word ptr es:[0x7a4e], 6
075c jmp 0x1e05
075e mov <resolved loader operand; see bindings> ; [{'operand_offset': 1887, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0761 mov es, ax
0763 sub word ptr es:[0x7a4e], 6
0769 push ss
076a pop ds
076b mov es, word ptr [0xc51a]
076f push word ptr es:[0x7a58]
0774 mov es, word ptr [0xc518]
0778 push word ptr es:[0x7a4e]
077d nop 
077e push cs
077f call 0x3386 ; _FootFall
0782 add sp, 4
0785 les bx, ptr [bp - 0x10]
0788 cmp word ptr es:[bx], 0
078c jne 0x1e2d
078e jmp 0x1f56
0791 mov es, word ptr [0xc53e]
0795 cmp word ptr es:[0x80b4], 0
079b jne 0x1e3c
079d jmp 0x1f56
07a0 mov es, word ptr [0xc540]
07a4 mov si, word ptr es:[0x80f0]
07a9 or si, si
07ab jle 0x1e87
07ad mov <resolved loader operand; see bindings> ; [{'operand_offset': 1966, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
07b0 mov es, ax
07b2 dec si
07b3 cmp byte ptr es:[si + 0x2f62], 0
07b9 je 0x1e83
07bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1982, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
07c0 or ax, ax
07c2 je 0x1ed4
07c4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1989, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
07c7 mov es, ax
07c9 mov bl, byte ptr es:[si + 0x278e]
07ce sub bh, bh
07d0 mov di, word ptr es:[si + 0x23a4]
07d5 and di, 0xff
07d9 shl di, 6
07dc xor al, al
07de mov byte ptr [bx + di + 0x68e8], al
07e2 mov byte ptr es:[si + 0x2f62], al
07e7 or si, si
07e9 jg 0x1e4e
07eb mov es, word ptr [0xc542]
07ef cmp word ptr es:[0x9bd2], 0
07f5 je 0x1ea1
07f7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2042, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
07fc or ax, ax
07fe je 0x1ea1
0800 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2051, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _KillSpider
0805 mov es, word ptr [0xc544]
0809 cmp word ptr es:[0x9fe8], 1
080f jle 0x1eb0
0811 jmp 0x1f56
0814 cmp word ptr [0xce80], 1 ; _MePlane
0819 je 0x1eba
081b jmp 0x1f56
081e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2081, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0823 or ax, ax
0825 jne 0x1ec6
0827 jmp 0x1f56
082a push 6
082c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 2095, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
0831 add sp, 2
0834 jmp 0x1f56
0837 nop 
0838 mov <resolved loader operand; see bindings> ; [{'operand_offset': 2105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
083b mov es, ax
083d jmp 0x1e83
083f nop 
0840 lds bx, ptr [bp - 0x10]
0843 cmp word ptr [bx], 0
0846 je 0x1f56
0848 mov bx, word ptr es:[0x78b0]
084d shl bx, 4
0850 lds si, ptr [bp - 0x14]
0853 add bx, word ptr [si]
0855 mov word ptr [bp - 0x22], bx
0858 add bx, 0xa4
085c mov <resolved loader operand; see bindings> ; [{'operand_offset': 2141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
085f mov ds, ax
0861 mov bl, byte ptr [bx]
0863 sub bh, bh
0865 or bx, bx
0867 je 0x1f23
0869 mov ax, bx
086b sar ax, 2
086e sub bx, ax
0870 jne 0x1f17
0872 mov <resolved loader operand; see bindings> ; [{'operand_offset': 2163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0875 mov ds, ax
0877 inc word ptr [0xa0dc]
087b mov <resolved loader operand; see bindings> ; [{'operand_offset': 2172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
087e mov ds, ax
0880 mov si, word ptr [bp - 0x22]
0883 mov byte ptr [si + 0xa4], bl
0887 mov bx, word ptr [bp - 0x22]
088a add bx, 0x164
088e mov <resolved loader operand; see bindings> ; [{'operand_offset': 2191, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0891 mov ds, ax
0893 mov bl, byte ptr [bx]
0895 sub bh, bh
0897 or bx, bx
0899 je 0x1f56
089b mov ax, bx
089d sar ax, 2
08a0 sub bx, ax
08a2 jne 0x1f49
08a4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 2213, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
08a7 mov ds, ax
08a9 inc word ptr [0x7896]
08ad mov si, word ptr [bp - 0x22]
08b0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 2225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
08b3 mov es, ax
08b5 mov byte ptr es:[si + 0x164], bl
08ba push ss
08bb pop ds
08bc pop si
08bd pop di
08be leave 
08bf retf 
```

## Known declaration examples

- `extern int near BoyFrame;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near BoyHere;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near BoyX;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near BoyY;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MePlane;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near RainOn;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int far SRand1(int n);` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern int far SRand1(int range);` — src/recovered/wf_AddRocks-01eddceee1.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand32(void);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far SRand32(void);` — src/recovered/wf_tu_simant1_2D4E_DoAntSimB_12_scaffold-4b5d5c0634.c
- `extern int far SRand32(void);` — src/recovered/wf_tu_simant1_5344_DoAntSimR_11_scaffold-77ef66a1e6.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern void far YellowDeath(int code);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
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

- {'callee_names': ['_FootFall'], 'segment': 7, 'target_offset': 13190, 'caller_offsets': [1919]}

## Neighbors

- {'symbol': '_SendBoyMsg', 'offset': 5550, 'source': 'src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c', 'size': 59}
- {'symbol': '_SimRain', 'offset': 5610, 'source': 'src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c', 'size': 177}
- {'symbol': '_GetMowDir', 'offset': 8028, 'source': None, 'size': 225}
- {'symbol': '_NotMowed', 'offset': 8254, 'source': None, 'size': 52}
