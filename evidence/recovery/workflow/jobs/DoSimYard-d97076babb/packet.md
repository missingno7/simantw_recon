# Recovery task _DoSimYard

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 262 bytes.

```asm
0000 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0003 mov ds, ax
0005 inc word ptr [0x7a5c]
0009 cmp word ptr [0x7a5c], 0x400
000f jl 0x14bf
0011 mov word ptr [0x7a5c], 0
0017 mov <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
001a mov es, ax
001c cmp word ptr es:[0x8a86], 0x26
0022 jge 0x14d6
0024 push ss
0025 pop ds
0026 nop 
0027 push cs
0028 call 0x20b6 ; _SimKidInside
002b jmp 0x14dd
002d nop 
002e push ss
002f pop ds
0030 nop 
0031 push cs
0032 call 0x169c ; _SimKidOutside
0035 nop 
0036 push cs
0037 call 0x28aa ; _SimBird
003a nop 
003b push cs
003c call 0x2b24 ; _SimCat
003f cmp word ptr [0xac5a], 0 ; _ForSaleState
0044 jne 0x14f3
0046 nop 
0047 push cs
0048 call 0x2dbc ; _SimDog
004b mov es, word ptr [0xc52e]
004f cmp word ptr es:[0x9b6e], 1
0055 jne 0x1502
0057 jmp 0x15a8
005a cmp word ptr [0xac72], 0 ; _RainOn
005f jne 0x1588
0061 mov es, word ptr [0xc530]
0065 cmp word ptr es:[0x7866], 0xa8
006c je 0x1536
006e push 0x20
0070 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 115, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
0075 add sp, 2
0078 or ax, ax
007a je 0x1527
007c jmp 0x15a8
007f push 0x80
0082 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
0087 add sp, 2
008a or ax, ax
008c jne 0x15a8
008e mov word ptr [0xac72], 1 ; _RainOn
0094 push 0x96
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
009c add sp, 2
009f add ax, 0x96
00a2 mov es, word ptr [0xc532]
00a6 mov word ptr es:[0x810c], ax
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _InitWater
00af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 178, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00b4 add ax, 0x12c
00b7 adc dx, 0
00ba mov es, word ptr [0xc4f6]
00be mov word ptr es:[0x7d4a], ax
00c2 mov word ptr es:[0x7d4c], dx
00c7 mov es, word ptr [0xc504]
00cb mov word ptr es:[0x99da], 1
00d2 mov es, word ptr [0xc52a]
00d6 mov word ptr es:[0x72f2], 0
00dd jmp 0x15a8
00df nop 
00e0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 225, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00e3 mov es, ax
00e5 cmp word ptr es:[0x810c], 0
00eb jle 0x159a
00ed dec word ptr es:[0x810c]
00f2 cmp word ptr es:[0x810c], 1
00f8 jge 0x15a8
00fa mov word ptr [0xac72], 0 ; _RainOn
0100 nop 
0101 push cs
0102 call 0x35f8 ; _SimColonies
0105 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int near RainOn;` — src/recovered/wf_InitSimYard-1f8979b97f.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Bounce', 'offset': 4844, 'source': 'src/recovered/wf_Bounce-0d87abbf42.c', 'size': 140}
- {'symbol': '_InitSimYard', 'offset': 4984, 'source': 'src/recovered/wf_InitSimYard-1f8979b97f.c', 'size': 304}
- {'symbol': '_SendBoyMsg', 'offset': 5550, 'source': None, 'size': 59}
- {'symbol': '_SimRain', 'offset': 5610, 'source': None, 'size': 177}
