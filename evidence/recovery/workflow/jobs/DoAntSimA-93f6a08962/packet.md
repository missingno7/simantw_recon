# Recovery task _DoAntSimA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 1348 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc314]
000a mov ax, word ptr es:[0x80f0]
000e mov es, word ptr [0xc316]
0012 mov word ptr es:[0x9b6a], ax
0016 or ax, ax
0018 jg 0x4f5
001a jmp 0xa18
001d dec word ptr es:[0x9b6a]
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand256
0027 or ax, ax
0029 je 0x506
002b jmp 0x587
002e mov es, word ptr [0xc316]
0032 mov bx, word ptr es:[0x9b6a]
0037 mov es, word ptr [0xc318]
003b mov si, word ptr es:[bx + 0x2f62]
0040 and si, 0xff
0044 je 0x587
0046 test si, 0x80
004a je 0x52a
004c mov ax, word ptr [0xac88] ; _HealthR
004f jmp 0x52d
0051 nop 
0052 mov ax, word ptr [0xac86] ; _HealthB
0055 mov si, ax
0057 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 90, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
005c cmp ax, si
005e jle 0x587
0060 mov es, word ptr [0xc316]
0064 mov bx, word ptr es:[0x9b6a]
0069 mov es, word ptr [0xc318]
006d mov al, byte ptr es:[bx + 0x2f62]
0072 and ax, 0x80
0075 push ax
0076 mov al, byte ptr es:[bx + 0x278e]
007b sub ah, ah
007d push ax
007e mov al, byte ptr es:[bx + 0x23a4]
0083 push ax
0084 nop 
0085 push cs
0086 call 0x28c0 ; _DeadAntHere
0089 add sp, 6
008c mov es, word ptr [0xc316]
0090 mov bx, word ptr es:[0x9b6a]
0095 mov es, word ptr [0xc318]
0099 mov byte ptr es:[bx + 0x2f62], 0
009f mov es, word ptr [0xc31a]
00a3 add word ptr es:[0x9b26], 1
00a9 adc word ptr es:[0x9b28], 0
00af mov es, word ptr [0xc316]
00b3 mov bx, word ptr es:[0x9b6a]
00b8 mov es, word ptr [0xc318]
00bc mov al, byte ptr es:[bx + 0x2f62]
00c1 mov byte ptr [bp - 0xe], al
00c4 mov bl, al
00c6 sub bh, bh
00c8 mov word ptr [bp - 0xc], bx
00cb or bx, bx
00cd jne 0x5aa
00cf jmp 0xa09
00d2 mov es, word ptr [0xc316]
00d6 mov si, word ptr es:[0x9b6a]
00db mov es, word ptr [0xc318]
00df mov si, word ptr es:[si + 0x2b78]
00e4 and si, 0xff
00e8 test bl, 0x80
00eb je 0x5d4
00ed mov es, word ptr [0xc300]
00f1 mov bx, si
00f3 shl bx, 1
00f5 inc word ptr es:[bx + 0x7be4]
00fa jmp 0x5e1
00fc mov es, word ptr [0xc302]
0100 mov bx, si
0102 shl bx, 1
0104 inc word ptr es:[bx + 0x786a]
0109 mov ax, si
010b cmp ax, 0x13
010e jbe 0x5eb
0110 jmp 0xa09
0113 shl ax, 1
0115 xchg bx, ax
0116 jmp word ptr cs:[bx + 0x5f4]
011b nop 
011c dw offset 0x61c
011e dw offset 0x62c
0120 dw offset 0x638
0122 dw offset 0x648
0124 dw offset 0x62c
0126 dw offset 0x658
0128 dw offset 0x668
012a dw offset 0x678
012c dw offset 0x688
012e dw offset 0x6e2
0130 dw offset 0x7a2
0132 dw offset 0x7b2
0134 dw offset 0x7c2
0136 dw offset 0x836
0138 dw offset 0x8e6
013a dw offset 0x942
013c dw offset 0x952
013e dw offset 0xa09
0140 dw offset 0xa09
0142 dw offset 0x9f8
0144 mov es, word ptr [0xc316]
0148 push word ptr es:[0x9b6a]
014d call 0xe66 ; _DoRandAntA
0150 jmp 0xa06
0153 nop 
0154 mov es, word ptr [0xc316]
0158 push word ptr es:[0x9b6a]
015d jmp 0x828
0160 mov es, word ptr [0xc316]
0164 push word ptr es:[0x9b6a]
0169 call 0x1e42 ; _DoForageAnt
016c jmp 0xa06
016f nop 
0170 mov es, word ptr [0xc316]
0174 push word ptr es:[0x9b6a]
0179 call 0x1cb4 ; _DoReturnFoodAnt
017c jmp 0xa06
017f nop 
0180 mov es, word ptr [0xc316]
0184 push word ptr es:[0x9b6a]
0189 call 0x1480 ; _DoDigOutAntA
018c jmp 0xa06
018f nop 
0190 mov es, word ptr [0xc316]
0194 push word ptr es:[0x9b6a]
0199 call 0x22a8 ; _DoRecruitAnt
019c jmp 0xa06
019f nop 
01a0 mov es, word ptr [0xc316]
01a4 push word ptr es:[0x9b6a]
01a9 call 0x2a40 ; _DoAttackAnt
01ac jmp 0xa06
01af nop 
01b0 mov es, word ptr [0xc316]
01b4 mov bx, word ptr es:[0x9b6a]
01b9 mov si, bx
01bb mov es, word ptr [0xc318]
01bf mov al, byte ptr es:[bx + 0x23a4]
01c4 sub ah, ah
01c6 mov di, ax
01c8 mov cl, byte ptr es:[bx + 0x278e]
01cd sub ch, ch
01cf mov word ptr [bp - 2], cx
01d2 mov bx, ax
01d4 shl bx, 6
01d7 add bx, cx
01d9 mov al, byte ptr [bp - 0xc]
01dc mov byte ptr [bx + 0x68e8], al
01e0 push 0xc8
01e3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 486, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
01e8 add sp, 2
01eb or ax, ax
01ed je 0x6ca
01ef jmp 0xa09
01f2 xor al, al
01f4 mov es, word ptr [0xc318]
01f8 mov byte ptr es:[si + 0x2f62], al
01fd shl di, 6
0200 mov bx, word ptr [bp - 2]
0203 mov byte ptr [bx + di + 0x68e8], al
0207 jmp 0xa09
020a mov <resolved loader operand; see bindings> ; [{'operand_offset': 523, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
020d mov ds, ax
020f mov ax, word ptr [0x9b6a]
0212 mov word ptr [bp - 8], ax
0215 mov <resolved loader operand; see bindings> ; [{'operand_offset': 534, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0218 mov es, cx
021a mov bx, ax
021c mov si, word ptr es:[bx + 0x23a4]
0221 and si, 0xff
0225 mov cl, byte ptr es:[bx + 0x278e]
022a sub ch, ch
022c mov di, cx
022e mov ax, word ptr [bp - 0xc]
0231 mov word ptr [bp - 2], ax
0234 mov bx, si
0236 shl bx, 6
0239 add bx, di
023b mov byte ptr ss:[bx + 0x68e8], al
0240 mov al, byte ptr [bp - 0xc]
0243 and al, 0x7f
0245 cmp al, 0x67
0247 jle 0x762
0249 push ss
024a pop ds
024b mov bl, byte ptr [bp - 2]
024e and bx, 7
0251 mov es, word ptr [0xc31c]
0255 mov al, byte ptr es:[bx + 8]
025a cwde 
025b add ax, di
025d mov word ptr [bp - 4], ax
0260 mov es, word ptr [0xc31e]
0264 mov al, byte ptr es:[bx]
0269 cwde 
026a mov bx, ax
026c add bx, si
026e mov word ptr [bp - 6], bx
0271 shl bx, 6
0274 add bx, word ptr [bp - 4]
0277 mov al, byte ptr [bx + 0x68e8]
027b sub ah, ah
027d sub ax, word ptr [bp - 2]
0280 cmp ax, 0xfff8
0283 jne 0x768
0285 xor ax, ax
0287 jmp 0x77d
0289 nop 
028a push ss
028b pop ds
028c jmp 0xa09
028f nop 
0290 push word ptr [bp - 4]
0293 push word ptr [bp - 6]
0296 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 665, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
029b add sp, 4
029e or ax, ax
02a0 jge 0x75d
02a2 mov ax, 1
02a5 mov word ptr [bp - 0xa], ax
02a8 or ax, ax
02aa jne 0x787
02ac jmp 0xa09
02af xor al, al
02b1 mov bx, si
02b3 shl bx, 6
02b6 mov byte ptr [bx + di + 0x68e8], al
02ba mov es, word ptr [0xc318]
02be mov bx, word ptr [bp - 8]
02c1 mov byte ptr es:[bx + 0x2f62], al
02c6 jmp 0xa09
02c9 nop 
02ca mov es, word ptr [0xc316]
02ce push word ptr es:[0x9b6a]
02d3 call 0x27e6 ; _DoFightA
02d6 jmp 0xa06
02d9 nop 
02da mov es, word ptr [0xc316]
02de push word ptr es:[0x9b6a]
02e3 call 0x1a0a ; _DoToAlarm
02e6 jmp 0xa06
02e9 nop 
02ea mov es, word ptr [0xc316]
02ee mov ax, word ptr es:[0x9b6a]
02f2 mov word ptr [bp - 2], ax
02f5 test byte ptr [bp - 0xe], 0x80
02f9 je 0x7fa
02fb mov es, word ptr [0xc318]
02ff mov bx, ax
0301 mov bl, byte ptr es:[bx + 0x23a4]
0306 and bx, 0xfe
030a shl bx, 4
030d mov si, ax
030f mov al, byte ptr es:[si + 0x278e]
0314 shr al, 1
0316 sub ah, ah
0318 add bx, ax
031a mov cl, byte ptr es:[bx + 0x72d2]
031f jmp 0x820
0321 nop 
0322 mov es, word ptr [0xc318]
0326 mov bx, word ptr [bp - 2]
0329 mov bl, byte ptr es:[bx + 0x23a4]
032e and bx, 0xfe
0332 shl bx, 4
0335 mov si, word ptr [bp - 2]
0338 mov al, byte ptr es:[si + 0x278e]
033d shr al, 1
033f sub ah, ah
0341 add bx, ax
0343 mov cl, byte ptr es:[bx + 0x62d2]
0348 sub ch, ch
034a cmp cx, 0x6e
034d jge 0x82e
034f push si
0350 call 0x1676 ; _DoToNestAnt
0353 jmp 0xa06
0356 push si
0357 call 0x1234 ; _DoRandAntAA
035a jmp 0xa06
035d nop 
035e mov es, word ptr [0xc316]
0362 mov ax, word ptr es:[0x9b6a]
0366 mov word ptr [bp - 2], ax
0369 mov bx, ax
036b mov es, word ptr [0xc318]
036f mov si, word ptr es:[bx + 0x23a4]
0374 and si, 0xff
0378 mov cl, byte ptr es:[bx + 0x278e]
037d sub ch, ch
037f mov di, cx
0381 push di
0382 push si
0383 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 902, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0388 add sp, 4
038b or ax, ax
038d jne 0x86c
038f xor dx, dx
0391 jmp 0x8a0
0393 nop 
0394 mov es, word ptr [0xc320]
0398 cmp word ptr es:[0x9b6e], 0
039e jne 0x886
03a0 mov bx, si
03a2 shl bx, 6
03a5 cmp byte ptr [bx + di + 0x28e8], 0x50
03aa jne 0x867
03ac jmp 0x89d
03ae mov bx, si
03b0 shl bx, 6
03b3 mov cl, byte ptr [bx + di + 0x28e8]
03b7 sub ch, ch
03b9 cmp cx, 0x80
03bd jl 0x867
03bf cmp cx, 0x8f
03c3 jg 0x867
03c5 mov dx, 1
03c8 dec dx
03c9 jne 0x8b2
03cb push word ptr [bp - 2]
03ce push di
03cf push si
03d0 call 0x257a ; _GoInNest
03d3 add sp, 6
03d6 jmp 0xa09
03d9 nop 
03da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 989, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
03df or ax, ax
03e1 jne 0x8cc
03e3 mov es, word ptr [0xc318]
03e7 mov bx, word ptr [bp - 2]
03ea mov byte ptr es:[bx + 0x2b78], 2
03f0 jmp 0xa09
03f3 nop 
03f4 mov es, word ptr [0xc322]
03f8 cmp word ptr es:[0x85fc], 1
03fe je 0x8db
0400 jmp 0xa09
0403 push 1
0405 push di
0406 push si
0407 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1034, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _RestBalloons
040c jmp 0x8ab
040e mov es, word ptr [0xc316]
0412 mov si, word ptr es:[0x9b6a]
0417 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1050, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand2
041c or ax, ax
041e je 0x8fe
0420 push si
0421 call 0x1234 ; _DoRandAntAA
0424 jmp 0x902
0426 push si
0427 call 0x1676 ; _DoToNestAnt
042a add sp, 2
042d mov es, word ptr [0xc318]
0431 test byte ptr es:[si + 0x2f62], 0x80
0437 je 0x936
0439 mov es, word ptr [0xc324]
043d cmp word ptr es:[0x8078], 0x64
0443 jg 0x920
0445 jmp 0xa09
0448 mov es, word ptr [0xc316]
044c mov bx, word ptr es:[0x9b6a]
0451 mov es, word ptr [0xc318]
0455 mov byte ptr es:[bx + 0x2b78], 0xf
045b jmp 0xa09
045e mov es, word ptr [0xc326]
0462 cmp word ptr es:[0x7c44], 0x64
0468 jmp 0x91b
046a mov es, word ptr [0xc316]
046e push word ptr es:[0x9b6a]
0473 call 0xc7a ; _DoRepoExit
0476 jmp 0xa06
0479 nop 
047a mov es, word ptr [0xc316]
047e mov di, word ptr es:[0x9b6a]
0483 mov al, byte ptr [bp - 0xe]
0486 and ax, 0x80
0489 mov si, ax
048b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1166, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
0490 or ax, ax
0492 je 0x96f
0494 jmp 0xa09
0497 or si, si
0499 jne 0x97f
049b mov es, word ptr [0xc328]
049f cmp word ptr es:[0x807a], 0x32
04a5 jl 0x992
04a7 or si, si
04a9 jne 0x986
04ab jmp 0xa09
04ae mov es, word ptr [0xc32a]
04b2 cmp word ptr es:[0x9c26], 0x32
04b8 jge 0xa09
04ba xor al, al
04bc mov es, word ptr [0xc318]
04c0 mov byte ptr es:[di + 0x2f62], al
04c5 mov bl, byte ptr es:[di + 0x278e]
04ca sub bh, bh
04cc mov di, word ptr es:[di + 0x23a4]
04d1 and di, 0xff
04d5 shl di, 6
04d8 mov byte ptr [bx + di + 0x68e8], al
04dc mov es, word ptr [0xc310]
04e0 cmp word ptr es:[0x80b4], 2
04e6 jne 0xa09
04e8 or si, si
04ea jne 0x9d0
04ec mov es, word ptr [0xc328]
04f0 inc word ptr es:[0x807a]
04f5 jmp 0x9d9
04f7 nop 
04f8 mov es, word ptr [0xc32a]
04fc inc word ptr es:[0x9c26]
0501 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1284, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
0506 or ax, ax
0508 jne 0xa09
050a or si, si
050c jne 0x9f2
050e inc word ptr [0xac8c] ; _QueenStorageB
0512 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1301, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InvalQueenStorageDisp
0517 jmp 0xa09
0519 nop 
051a inc word ptr [0xac8e] ; _QueenStorageR
051e jmp 0xa09
0520 mov es, word ptr [0xc316]
0524 push word ptr es:[0x9b6a]
0529 nop 
052a push cs
052b call 0xffff96d4
052e add sp, 2
0531 mov es, word ptr [0xc316]
0535 cmp word ptr es:[0x9b6a], 0
053b jle 0xa18
053d jmp 0x4f5
0540 pop si
0541 pop di
0542 leave 
0543 ret 
```

## Known declaration examples

- `extern void near DoRandAntAA(int ant);` — src/recovered/wf_DoDefendNest-ed5a5a93f0.c
- `extern void near DoToNestAnt(int ant);` — src/recovered/wf_DoDefendNest-ed5a5a93f0.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far FindInAList(int x, int y);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int near HealthB;` — src/recovered/DecEatB.c
- `extern int near HealthB;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int near HealthB;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int near HealthR;` — src/recovered/DecEatR.c
- `extern int near HealthR;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_IsPillDead-8cef0d554b.c
- `extern int near QueenStorageB;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageB;` — src/recovered/wf_MaintainSwarm-82303a3cad.c
- `extern int near QueenStorageR;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageR;` — src/recovered/wf_MaintainSwarm-82303a3cad.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirB-2bfd4e5303.c
- `extern int far SRand2(void);` — src/recovered/wf_GetExitDirR-414ecd2b67.c
- `extern int far SRand2(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand32(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand32(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_TallyModePop', 'offset': 910, 'source': None, 'size': 230}
- {'symbol': '_FeedAnts', 'offset': 1140, 'source': None, 'size': 100}
- {'symbol': '_SimEggA', 'offset': 2588, 'source': None, 'size': 88}
- {'symbol': '_SimQueenA', 'offset': 2676, 'source': None, 'size': 169}
