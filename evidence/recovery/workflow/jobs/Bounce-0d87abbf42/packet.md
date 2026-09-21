# Recovery task _Bounce

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 140 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 mov si, word ptr [bp + 8]
000b or di, di
000d jne 0x132a
000f or si, si
0011 jne 0x1310
0013 push 3
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
001a add sp, 2
001d add ax, 3
0020 pop si
0021 pop di
0022 leave 
0023 retf 
0024 cmp si, 0x3f
0027 jne 0x131a
0029 push 3
002b jmp 0x131c
002d nop 
002e push 5
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0035 add sp, 2
0038 inc ax
0039 pop si
003a pop di
003b leave 
003c retf 
003d nop 
003e or si, si
0040 jne 0x1348
0042 cmp di, 0x7f
0045 jne 0x1344
0047 push 3
0049 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004e add sp, 2
0051 add ax, 5
0054 pop si
0055 pop di
0056 leave 
0057 retf 
0058 push 5
005a jmp 0x1301
005c cmp di, 0x7f
005f jne 0x1368
0061 cmp si, 0x3f
0064 jne 0x1364
0066 push 3
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
006d add sp, 2
0070 add ax, 7
0073 pop si
0074 pop di
0075 leave 
0076 retf 
0077 nop 
0078 push 5
007a jmp 0x1335
007c cmp si, 0x3f
007f jne 0x1372
0081 push 5
0083 jmp 0x1354
0085 nop 
0086 xor ax, ax
0088 pop si
0089 pop di
008a leave 
008b retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetDefendDir', 'offset': 4134, 'source': None, 'size': 365}
- {'symbol': '_GetRedDefendDir', 'offset': 4500, 'source': None, 'size': 343}
- {'symbol': '_InitSimYard', 'offset': 4984, 'source': None, 'size': 304}
- {'symbol': '_DoSimYard', 'offset': 5288, 'source': None, 'size': 262}
