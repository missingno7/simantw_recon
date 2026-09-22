# Recovery task _DoForageAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 1126 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc318]
000a mov bx, word ptr [bp + 4]
000d mov di, word ptr es:[bx + 0x23a4]
0012 and di, 0xff
0016 mov al, byte ptr es:[bx + 0x278e]
001b sub ah, ah
001d mov si, ax
001f mov al, byte ptr es:[bx + 0x2f62]
0024 mov word ptr [bp - 4], ax
0027 push si
0028 push di
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
002e add sp, 4
0031 or ax, ax
0033 jne 0x1e7c
0035 xor cx, cx
0037 jmp 0x1eb0
0039 nop 
003a mov es, word ptr [0xc320]
003e cmp word ptr es:[0x9b6e], 0
0044 jne 0x1e96
0046 mov bx, di
0048 shl bx, 6
004b cmp byte ptr [bx + si + 0x28e8], 0x50
0050 jne 0x1e77
0052 jmp 0x1ead
0054 mov bx, di
0056 shl bx, 6
0059 mov dl, byte ptr [bx + si + 0x28e8]
005d sub dh, dh
005f cmp dx, 0x80
0063 jl 0x1e77
0065 cmp dx, 0x8f
0069 jg 0x1e77
006b mov cx, 1
006e or cx, cx
0070 je 0x1ec0
0072 push word ptr [bp + 4]
0075 push si
0076 push di
0077 call 0x257a ; _GoInNest
007a jmp 0x22a1
007d nop 
007e mov word ptr [bp - 0xa], si
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
0086 or ax, ax
0088 jne 0x1edc
008a mov es, word ptr [0xc318]
008e mov bx, word ptr [bp + 4]
0091 mov byte ptr es:[bx + 0x2b78], 0xd
0097 jmp 0x22a4
009a mov si, word ptr [bp - 4]
009d mov ax, si
009f and ax, 0xf8
00a2 mov word ptr [bp - 0x10], ax
00a5 mov cx, si
00a7 and cx, 0x78
00aa sar cx, 3
00ad mov <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00b0 mov es, ax
00b2 mov bx, di
00b4 and bl, 0xfe
00b7 shl bx, 4
00ba mov ax, word ptr [bp - 0xa]
00bd sar ax, 1
00bf add bx, ax
00c1 cmp byte ptr es:[bx + 0x52d2], 0
00c7 je 0x1f18
00c9 mov bx, word ptr [bp + 4]
00cc mov byte ptr es:[bx + 0x2b78], 0xb
00d2 pop si
00d3 pop di
00d4 leave 
00d5 ret 
00d6 mov word ptr [bp - 6], di
00d9 mov word ptr [bp - 2], cx
00dc mov si, cx
00de mov di, word ptr [bp - 0xa]
00e1 cmp si, 6
00e4 je 0x1f50
00e6 cmp si, 2
00e9 je 0x1f50
00eb push word ptr [bp - 4]
00ee push si
00ef lcall <resolved loader operand; see bindings> ; [{'operand_offset': 242, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
00f4 add sp, 4
00f7 mov es, word ptr [0xc318]
00fb mov bx, word ptr [bp + 4]
00fe mov byte ptr es:[bx + 0x2b78], al
0103 mov byte ptr es:[bx + 0x334c], 0
0109 pop si
010a pop di
010b leave 
010c ret 
010d nop 
010e mov al, byte ptr [bp - 4]
0111 push word ptr [bp - 4]
0114 and ax, 7
0117 mov word ptr [bp - 0x12], ax
011a push ax
011b push di
011c push word ptr [bp - 6]
011f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 290, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetForageDir
0124 add sp, 8
0127 mov word ptr [bp - 8], ax
012a or ax, ax
012c jge 0x1fbc
012e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0133 or ax, ax
0135 je 0x1f88
0137 mov es, word ptr [0xc318]
013b mov bx, word ptr [bp + 4]
013e mov byte ptr es:[bx + 0x2b78], 0
0144 jmp 0x1fa0
0146 push word ptr [bp - 4]
0149 push si
014a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 333, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
014f add sp, 4
0152 mov es, word ptr [0xc318]
0156 mov bx, word ptr [bp + 4]
0159 mov byte ptr es:[bx + 0x2b78], al
015e mov byte ptr es:[bx + 0x334c], 0
0164 mov al, byte ptr [bp - 4]
0167 and ax, 0x80
016a push ax
016b mov ax, di
016d sar ax, 1
016f push ax
0170 mov ax, word ptr [bp - 6]
0173 sar ax, 1
0175 push ax
0176 jmp 0x2149
0179 nop 
017a mov si, ax
017c mov <resolved loader operand; see bindings> ; [{'operand_offset': 381, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
017f mov ds, ax
0181 mov al, byte ptr [si + 8]
0185 cwde 
0186 add ax, di
0188 mov word ptr [bp - 0xc], ax
018b mov <resolved loader operand; see bindings> ; [{'operand_offset': 396, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
018e mov es, cx
0190 mov cx, ax
0192 mov al, byte ptr es:[si]
0197 cwde 
0198 mov bx, ax
019a add bx, word ptr [bp - 6]
019d mov word ptr [bp - 0xe], bx
01a0 shl bx, 6
01a3 add bx, cx
01a5 mov cl, byte ptr ss:[bx + 0x28e8]
01aa sub ch, ch
01ac mov <resolved loader operand; see bindings> ; [{'operand_offset': 429, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01af mov es, ax
01b1 cmp word ptr es:[0x9b6e], 0
01b7 jne 0x200a
01b9 cmp cx, 0x48
01bc jl 0x2014
01be cmp cx, 0x4b
01c1 jg 0x2014
01c3 mov dx, 1
01c6 jmp 0x2016
01c8 cmp cx, 0x18
01cb jl 0x2014
01cd cmp cx, 0x27
01d0 jle 0x2005
01d2 xor dx, dx
01d4 dec dx
01d5 jne 0x2060
01d7 push ss
01d8 pop ds
01d9 mov ax, si
01db or al, byte ptr [bp - 0x10]
01de or al, 8
01e0 mov es, word ptr [0xc318]
01e4 mov bx, word ptr [bp + 4]
01e7 mov byte ptr es:[bx + 0x2f62], al
01ec mov bx, word ptr [bp - 6]
01ef shl bx, 6
01f2 mov byte ptr [bx + di + 0x68e8], al
01f6 mov bx, word ptr [bp + 4]
01f9 mov byte ptr es:[bx + 0x2b78], 3
01ff push word ptr [bp - 0xc]
0202 push word ptr [bp - 0xe]
0205 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 520, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _PickupFoodA
020a add sp, 4
020d mov es, word ptr [0xc318]
0211 mov bx, word ptr [bp + 4]
0214 mov byte ptr es:[bx + 0x334c], 0xc8
021a pop si
021b pop di
021c leave 
021d ret 
021e push ss
021f pop ds
0220 mov es, word ptr [0xc32c]
0224 cmp word ptr es:[0x7604], cx
0229 jge 0x20b2
022b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 558, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0230 mov bx, word ptr [bp - 0x12]
0233 shl bx, 3
0236 add bx, ax
0238 mov es, word ptr [0xc32e]
023c mov al, byte ptr es:[bx + 0x24]
0241 or al, byte ptr [bp - 0x10]
0244 mov es, word ptr [0xc318]
0248 mov bx, word ptr [bp + 4]
024b mov byte ptr es:[bx + 0x2f62], al
0250 mov bx, word ptr [bp - 6]
0253 shl bx, 6
0256 mov byte ptr [bx + di + 0x68e8], al
025a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 605, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
025f or ax, ax
0261 je 0x20a8
0263 jmp 0x22a4
0266 push word ptr [bp - 4]
0269 push word ptr [bp - 2]
026c jmp 0x1f31
026f nop 
0270 mov di, word ptr [bp - 0xe]
0273 mov si, word ptr [bp - 0xc]
0276 mov cx, word ptr [bp - 0xa]
0279 mov <resolved loader operand; see bindings> ; [{'operand_offset': 634, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
027c mov es, ax
027e mov bx, di
0280 shl bx, 6
0283 add bx, si
0285 add bx, 0x68e8
0289 mov word ptr [bp - 0x14], bx
028c mov al, byte ptr [bx]
028e sub ah, ah
0290 mov word ptr [bp - 2], ax
0293 or ax, ax
0295 jne 0x2150
0297 mov al, byte ptr [bp - 8]
029a or al, byte ptr [bp - 0x10]
029d mov byte ptr [bx], al
029f mov bx, word ptr [bp + 4]
02a2 mov byte ptr es:[bx + 0x2f62], al
02a7 mov bx, word ptr [bp - 6]
02aa shl bx, 6
02ad add bx, cx
02af mov byte ptr [bx + 0x68e8], ah
02b3 mov ax, di
02b5 mov bx, word ptr [bp + 4]
02b8 mov byte ptr es:[bx + 0x23a4], al
02bd mov ax, si
02bf mov byte ptr es:[bx + 0x278e], al
02c4 cmp byte ptr es:[bx + 0x334c], 0
02ca je 0x2140
02cc dec byte ptr es:[bx + 0x334c]
02d1 test byte ptr [bp - 4], 0x80
02d5 je 0x212c
02d7 mov es, word ptr [0xc318]
02db mov al, byte ptr es:[bx + 0x334c]
02e0 sub ah, ah
02e2 push ax
02e3 push si
02e4 push di
02e5 call 0x94f6 ; _JamScentRN
02e8 jmp 0x213d
02ea mov es, word ptr [0xc318]
02ee mov al, byte ptr es:[bx + 0x334c]
02f3 sub ah, ah
02f5 push ax
02f6 push si
02f7 push di
02f8 call 0x94b6 ; _JamScentBN
02fb add sp, 6
02fe mov al, byte ptr [bp - 4]
0301 and ax, 0x80
0304 push ax
0305 push si
0306 push di
0307 call 0x95b6 ; _DecTSmell
030a jmp 0x22a1
030d nop 
030e push ax
030f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 786, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsYellowAnt
0314 add sp, 2
0317 dec ax
0318 je 0x215f
031a jmp 0x21ea
031d mov al, byte ptr [bp - 4]
0320 xor al, byte ptr [0xce98] ; _MeColor
0324 test al, 0x80
0326 je 0x217c
0328 push word ptr [bp + 4]
032b push 1
032d nop 
032e push cs
032f call 0x823e ; _YellowFight
0332 add sp, 4
0335 pop si
0336 pop di
0337 leave 
0338 ret 
0339 nop 
033a mov si, word ptr [bp - 0xa]
033d mov di, word ptr [bp - 0x10]
0340 mov es, word ptr [0xc330]
0344 cmp word ptr es:[0x9af2], 1
034a jne 0x21b8
034c mov ax, di
034e or al, byte ptr [bp - 8]
0351 mov es, word ptr [0xc318]
0355 mov bx, word ptr [bp + 4]
0358 mov byte ptr es:[bx + 0x2f62], al
035d mov bx, word ptr [bp - 6]
0360 shl bx, 6
0363 mov byte ptr [bx + si + 0x68e8], al
0367 push word ptr [bp - 8]
036a push si
036b push word ptr [bp - 6]
036e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 881, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _DoTroph
0373 add sp, 6
0376 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 889, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
037b mov bx, word ptr [bp - 0x12]
037e shl bx, 3
0381 add bx, ax
0383 mov es, word ptr [0xc32e]
0387 mov ax, di
0389 or al, byte ptr es:[bx + 0x24]
038e mov es, word ptr [0xc318]
0392 mov bx, word ptr [bp + 4]
0395 mov byte ptr es:[bx + 0x2f62], al
039a mov bx, word ptr [bp - 6]
039d shl bx, 6
03a0 mov byte ptr [bx + si + 0x68e8], al
03a4 pop si
03a5 pop di
03a6 leave 
03a7 ret 
03a8 mov si, word ptr [bp - 4]
03ab mov al, byte ptr [bp - 2]
03ae mov cx, si
03b0 xor al, cl
03b2 test al, 0x80
03b4 jne 0x222a
03b6 mov di, word ptr [bp - 0x10]
03b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 956, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
03be mov bx, word ptr [bp - 0x12]
03c1 shl bx, 3
03c4 add bx, ax
03c6 mov es, word ptr [0xc32e]
03ca mov ax, di
03cc or al, byte ptr es:[bx + 0x24]
03d1 mov es, word ptr [0xc318]
03d5 mov bx, word ptr [bp + 4]
03d8 mov byte ptr es:[bx + 0x2f62], al
03dd mov si, word ptr [bp - 6]
03e0 shl si, 6
03e3 mov bx, word ptr [bp - 0xa]
03e6 jmp 0x21e2
03e8 mov es, word ptr [0xc318]
03ec mov bx, word ptr [bp + 4]
03ef mov al, byte ptr es:[bx + 0x2f62]
03f4 sub ah, ah
03f6 mov word ptr [bp - 4], ax
03f9 xor al, al
03fb mov byte ptr es:[bx + 0x2f62], al
0400 mov bx, word ptr [bp - 0xa]
0403 mov si, word ptr [bp - 6]
0406 shl si, 6
0409 mov byte ptr [bx + si + 0x68e8], al
040d push word ptr [bp - 0xc]
0410 push di
0411 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1044, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
0416 add sp, 4
0419 mov si, ax
041b or si, si
041d jl 0x22a4
041f push word ptr [bp - 4]
0422 mov es, word ptr [0xc318]
0426 mov al, byte ptr es:[si + 0x2f62]
042b sub ah, ah
042d push ax
042e call 0x26f4 ; _GetWinner
0431 add sp, 4
0434 mov es, word ptr [0xc318]
0438 mov word ptr [bp - 2], ax
043b mov cx, ax
043d and al, 0x80
043f add al, 0x70
0441 mov byte ptr es:[si + 0x2f62], al
0446 mov bx, word ptr [bp - 0x14]
0449 mov byte ptr [bx], al
044b mov byte ptr es:[si + 0x2b78], 0xa
0451 mov byte ptr es:[si + 0x334c], cl
0456 push 0x28
0458 push word ptr [bp - 0xc]
045b push di
045c call 0x947e ; _AlarmHere2
045f add sp, 6
0462 pop si
0463 pop di
0464 leave 
0465 ret 
```

## Known declaration examples

- `extern void near AlarmHere2(int x, int y, int level);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far FindInAList(int x, int y);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near GetWinner(int defender, int attacker);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_IsPillDead-8cef0d554b.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int near MeColor;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MeColor;` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int near MeColor;` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far SRand16(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far SRand32(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand32(void);` — src/recovered/wf_DoRandR-fc777553ef.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c
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

- {'symbol': '_DoToAlarm', 'offset': 6666, 'source': None, 'size': 682}
- {'symbol': '_DoReturnFoodAnt', 'offset': 7348, 'source': None, 'size': 398}
- {'symbol': '_DoRecruitAnt', 'offset': 8872, 'source': None, 'size': 722}
- {'symbol': '_GoInNest', 'offset': 9594, 'source': None, 'size': 240}
