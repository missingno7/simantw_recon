# Recovery task _ExpKillAnts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 478 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc270]
000a cmp byte ptr es:[0x8606], 1
0010 sbb ax, ax
0012 and ax, 7
0015 inc ax
0016 mov word ptr [bp - 6], ax
0019 mov ax, 0x9b6a
001c mov <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
001f mov word ptr [bp - 0xa], ax
0022 mov word ptr [bp - 8], cx
0025 mov word ptr [bp - 4], 8
002a cmp word ptr [bp - 6], 1
002e jne 0x7d98
0030 mov si, word ptr [bp + 6]
0033 mov di, word ptr [bp + 8]
0036 push 0x7e
0038 push 0
003a jmp 0x7dcd
003c push 9
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0043 add sp, 2
0046 mov si, ax
0048 add si, word ptr [bp + 6]
004b sub si, 4
004e push 9
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0055 add sp, 2
0058 mov di, ax
005a add di, word ptr [bp + 8]
005d sub di, 4
0060 push 0x7e
0062 push 0x3e8
0065 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 104, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
006a add sp, 2
006d add ax, 0x278f
0070 push ax
0071 push 9
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0078 add sp, 6
007b push di
007c push si
007d push word ptr [0xcc76] ; _MapPlane
0081 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidLocation
0086 add sp, 6
0089 or ax, ax
008b jne 0x7dec
008d jmp 0x7f2e
0090 mov ax, word ptr [0xcc76] ; _MapPlane
0093 or ax, ax
0095 jge 0x7df6
0097 jmp 0x7f2e
009a jno 0x7dfb
009c jmp 0x7f2e
009f dec ax
00a0 jle 0x7e0e
00a2 dec ax
00a3 jne 0x7e04
00a5 jmp 0x7eb0
00a8 dec ax
00a9 jne 0x7e0a
00ab jmp 0x7ef0
00ae jmp 0x7f2e
00b1 nop 
00b2 mov bx, si
00b4 shl bx, 6
00b7 add bx, di
00b9 mov word ptr [bp - 0xc], bx
00bc cmp byte ptr [bx + 0x68e8], 0
00c1 je 0x7e65
00c3 push di
00c4 push si
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
00ca add sp, 4
00cd les bx, ptr [bp - 0xa]
00d0 mov word ptr es:[bx], ax
00d3 or ax, ax
00d5 jl 0x7e65
00d7 mov bx, word ptr es:[bx]
00da mov es, word ptr [0xc27a]
00de mov al, byte ptr es:[bx + 0x2f62]
00e3 and ax, 0x80
00e6 push ax
00e7 push di
00e8 push si
00e9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 236, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _DeadAntHere
00ee add sp, 6
00f1 xor al, al
00f3 les bx, ptr [bp - 0xa]
00f6 mov bx, word ptr es:[bx]
00f9 mov es, word ptr [0xc27a]
00fd mov byte ptr es:[bx + 0x2f62], al
0102 mov bx, word ptr [bp - 0xc]
0105 mov byte ptr [bx + 0x68e8], al
0109 mov ax, word ptr [0xac7c] ; _SpidX
010c sar ax, 4
010f cmp ax, si
0111 jne 0x7e7e
0113 mov ax, word ptr [0xac7e] ; _SpidY
0116 sar ax, 4
0119 cmp ax, di
011b jne 0x7e7e
011d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 288, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _KillSpider
0122 mov bx, word ptr [bp - 0xc]
0125 mov dl, byte ptr [bx + 0x28e8]
0129 sub dh, dh
012b cmp dx, 0x38
012e jge 0x7e8f
0130 jmp 0x7f2e
0133 cmp dx, 0x3e
0136 jle 0x7e97
0138 jmp 0x7f2e
013b push di
013c push si
013d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 320, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _FindInLionList
0142 add sp, 4
0145 push ax
0146 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 329, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _KillAntLion
014b add sp, 2
014e jmp 0x7f2e
0151 nop 
0152 nop 
0153 nop 
0154 mov bx, si
0156 shl bx, 6
0159 add bx, di
015b mov word ptr [bp - 0xc], bx
015e mov al, byte ptr [bx - 0x7718]
0162 sub ah, ah
0164 or ax, ax
0166 je 0x7f2e
0168 push ax
0169 push di
016a push si
016b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 366, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInBList
0170 add sp, 6
0173 les bx, ptr [bp - 0xa]
0176 mov word ptr es:[bx], ax
0179 or ax, ax
017b jl 0x7f2e
017d xor al, al
017f mov bx, word ptr es:[bx]
0182 mov es, word ptr [0xc27a]
0186 mov byte ptr es:[bx + 0x3d18], al
018b mov bx, word ptr [bp - 0xc]
018e mov byte ptr [bx - 0x7718], al
0192 jmp 0x7f2e
0194 mov bx, si
0196 shl bx, 6
0199 add bx, di
019b mov word ptr [bp - 0xc], bx
019e mov al, byte ptr [bx - 0x6718]
01a2 sub ah, ah
01a4 or ax, ax
01a6 je 0x7f2e
01a8 push ax
01a9 push di
01aa push si
01ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 430, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInRList
01b0 add sp, 6
01b3 les bx, ptr [bp - 0xa]
01b6 mov word ptr es:[bx], ax
01b9 or ax, ax
01bb jl 0x7f2e
01bd xor al, al
01bf mov bx, word ptr es:[bx]
01c2 mov es, word ptr [0xc27a]
01c6 mov byte ptr es:[bx + 0x46e6], al
01cb mov bx, word ptr [bp - 0xc]
01ce mov byte ptr [bx - 0x6718], al
01d2 dec word ptr [bp - 4]
01d5 je 0x7f36
01d7 jmp 0x7d86
01da pop si
01db pop di
01dc leave 
01dd retf 
```

## Known declaration examples

- `extern int far FindInAList(int x, int y);` — src/recovered/wf_StartFightA-b2f3e31b2f.c
- `extern int far FindInBList(int x, int y, int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far IsValidLocation(int plane, int x, int y);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/wf_ExpAddFood-cd1bed365e.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExpAddFood', 'offset': 31494, 'source': 'src/recovered/wf_ExpAddFood-cd1bed365e.c', 'size': 152}
- {'symbol': '_ExpIncSmell', 'offset': 31646, 'source': None, 'size': 445}
- {'symbol': '_IncFoodHere', 'offset': 32570, 'source': None, 'size': 287}
- {'symbol': '_ConnectAll', 'offset': 32858, 'source': None, 'size': 1267}
