# Recovery task _SimRain

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 177 bytes.

```asm
0000 mov es, word ptr [0xc52e]
0004 cmp word ptr es:[0x9b6e], 1
000a jne 0x15f9
000c jmp 0x169a
000f cmp word ptr [0xac72], 0 ; _RainOn
0014 jne 0x167a
0016 mov es, word ptr [0xc530]
001a cmp word ptr es:[0x7866], 0xa8
0021 je 0x162a
0023 push 0x20
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
002a add sp, 2
002d or ax, ax
002f jne 0x169a
0031 push 0x80
0034 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 55, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _RRand
0039 add sp, 2
003c or ax, ax
003e jne 0x169a
0040 mov word ptr [0xac72], 1 ; _RainOn
0046 push 0x96
0049 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004e add sp, 2
0051 add ax, 0x96
0054 mov es, word ptr [0xc532]
0058 mov word ptr es:[0x810c], ax
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _InitWater
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
0066 add ax, 0x12c
0069 adc dx, 0
006c mov es, word ptr [0xc4f6]
0070 mov word ptr es:[0x7d4a], ax
0074 mov word ptr es:[0x7d4c], dx
0079 mov es, word ptr [0xc504]
007d mov word ptr es:[0x99da], 1
0084 mov es, word ptr [0xc52a]
0088 mov word ptr es:[0x72f2], 0
008f retf 
0090 mov <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0093 mov es, ax
0095 cmp word ptr es:[0x810c], 0
009b jle 0x168c
009d dec word ptr es:[0x810c]
00a2 cmp word ptr es:[0x810c], 1
00a8 jge 0x169a
00aa mov word ptr [0xac72], 0 ; _RainOn
00b0 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoSimYard', 'offset': 5288, 'source': None, 'size': 262}
- {'symbol': '_SendBoyMsg', 'offset': 5550, 'source': None, 'size': 59}
- {'symbol': '_SimKidOutside', 'offset': 5788, 'source': None, 'size': 2240}
- {'symbol': '_GetMowDir', 'offset': 8028, 'source': None, 'size': 225}
