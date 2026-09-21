# Recovery task _RandYard

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 476 bytes.

```asm
0000 enter 0x10, 0
0004 push si
0005 nop 
0006 push cs
0007 call 0x6dec ; _ClrArrays
000a push 1
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ClearHistory
0011 add sp, 2
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _initControls
0019 mov ax, 0xb
001c mov bx, 0x7a60
001f mov es, word ptr [0xc5fa]
0023 mov word ptr [bp - 8], bx
0026 mov word ptr [bp - 6], es
0029 mov word ptr es:[bx], ax
002c mov bx, 0x789e
002f mov es, word ptr [0xc5fc]
0033 mov word ptr [bp - 4], bx
0036 mov word ptr [bp - 2], es
0039 mov word ptr es:[bx], ax
003c mov ax, 8
003f mov bx, 0x7a62
0042 mov es, word ptr [0xc5fa]
0046 mov word ptr [bp - 0x10], bx
0049 mov word ptr [bp - 0xe], es
004c mov word ptr es:[bx], ax
004f mov bx, 0x78a0
0052 mov es, word ptr [0xc5fc]
0056 mov word ptr [bp - 0xc], bx
0059 mov word ptr [bp - 0xa], es
005c mov word ptr es:[bx], ax
005f nop 
0060 push cs
0061 call 0x1378 ; _InitSimYard
0064 mov es, word ptr [0xc5fe]
0068 mov word ptr es:[0x7c22], 0xffff
006f mov es, word ptr [0xc600]
0073 sub ax, ax
0075 mov word ptr es:[0x8070], ax
0079 mov word ptr es:[0x806e], ax
007d mov es, word ptr [0xc602]
0081 mov word ptr es:[0x9b12], ax
0085 mov word ptr es:[0x9b10], ax
0089 mov es, word ptr [0xc604]
008d mov word ptr es:[0x80ba], ax
0091 mov es, word ptr [0xc606]
0095 mov word ptr es:[0x9b22], ax
0099 mov es, word ptr [0xc608]
009d mov word ptr es:[0x78dc], ax
00a1 mov es, word ptr [0xc60a]
00a5 mov word ptr es:[0x9cea], ax
00a9 mov es, word ptr [0xc60c]
00ad mov word ptr es:[0x9dda], ax
00b1 mov word ptr [0xac5a], ax ; _ForSaleState
00b4 mov es, word ptr [0xc60e]
00b8 mov word ptr es:[0x8a60], ax
00bc mov es, word ptr [0xc610]
00c0 mov word ptr es:[0x8a5e], ax
00c4 mov es, word ptr [0xc612]
00c8 mov word ptr es:[0x8a5c], ax
00cc mov es, word ptr [0xc614]
00d0 sub cx, cx
00d2 mov word ptr es:[0x76aa], cx
00d7 mov word ptr es:[0x76a8], cx
00dc mov es, word ptr [0xc5bc]
00e0 cmp word ptr es:[0x80b4], 1
00e6 jg 0x6174
00e8 mov ax, 2
00eb jmp 0x6177
00ed nop 
00ee mov ax, 1
00f1 mov word ptr [0xcc76], ax ; _MapPlane
00f4 mov es, word ptr [0xc616]
00f8 mov word ptr es:[0x8610], ax
00fc mov word ptr [0xce82], cx ; _YardMode
0100 mov si, 0x224
0103 push 0x7fff
0106 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
010b add sp, 2
010e sub ax, 0xc000
0111 and ah, 0x7f
0114 mov es, word ptr [0xc5b6]
0118 mov word ptr es:[si], ax
011b add si, 2
011e cmp si, 0x3a4
0122 jb 0x6189
0124 mov es, word ptr [0xc5bc]
0128 cmp word ptr es:[0x80b4], 2
012e jne 0x61d0
0130 les bx, ptr [bp - 0xc]
0133 push word ptr es:[bx]
0136 les bx, ptr [bp - 4]
0139 push word ptr es:[bx]
013c push 1
013e xor ax, ax
0140 mov es, word ptr [0xc618]
0144 mov word ptr es:[0x8a6c], ax
0148 jmp 0x61e8
014a les bx, ptr [bp - 0xc]
014d push word ptr es:[bx]
0150 les bx, ptr [bp - 4]
0153 push word ptr es:[bx]
0156 mov ax, 1
0159 mov es, word ptr [0xc618]
015d mov word ptr es:[0x8a6c], ax
0161 push ax
0162 push ax
0163 les bx, ptr [bp - 0x10]
0166 mov bx, word ptr es:[bx]
0169 mov ax, bx
016b shl bx, 1
016d add bx, ax
016f shl bx, 2
0172 les si, ptr [bp - 8]
0175 add bx, word ptr es:[si]
0178 shl bx, 1
017a mov es, word ptr [0xc5b6]
017e push word ptr es:[bx + 0x224]
0183 nop 
0184 push cs
0185 call 0x5ab0 ; _RandWorld
0188 add sp, 0xa
018b cmp word ptr [0xce80], 1 ; _MePlane
0190 jg 0x622e
0192 mov <resolved loader operand; see bindings> ; [{'operand_offset': 403, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0195 mov es, ax
0197 mov ax, word ptr [0xcd88] ; _MeLocX
019a mov word ptr es:[0x9f2c], ax
019e mov ax, word ptr [0xce7e] ; _MeLocY
01a1 mov word ptr es:[0x9f2e], ax
01a5 pop si
01a6 leave 
01a7 retf 
01a8 cmp word ptr [0xce80], 2 ; _MePlane
01ad jne 0x624c
01af mov <resolved loader operand; see bindings> ; [{'operand_offset': 432, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01b2 mov es, ax
01b4 mov ax, word ptr [0xcd88] ; _MeLocX
01b7 mov word ptr es:[0x9fb2], ax
01bb mov ax, word ptr [0xce7e] ; _MeLocY
01be mov word ptr es:[0x9fb4], ax
01c2 pop si
01c3 leave 
01c4 retf 
01c5 nop 
01c6 mov <resolved loader operand; see bindings> ; [{'operand_offset': 455, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
01c9 mov es, ax
01cb mov ax, word ptr [0xcd88] ; _MeLocX
01ce mov word ptr es:[0x72f6], ax
01d2 mov ax, word ptr [0xce7e] ; _MeLocY
01d5 mov word ptr es:[0x72f8], ax
01d9 pop si
01da leave 
01db retf 
```

## Known declaration examples

- `extern int near ForSaleState;` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int far RRand(int range);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitSimVars', 'offset': 23152, 'source': 'src/recovered/InitSimVars.c', 'size': 63}
- {'symbol': '_RandWorld', 'offset': 23216, 'source': None, 'size': 1493}
- {'symbol': '_GenerateTutorial', 'offset': 25186, 'source': None, 'size': 124}
- {'symbol': '_DigOutBNest', 'offset': 25310, 'source': None, 'size': 218}
