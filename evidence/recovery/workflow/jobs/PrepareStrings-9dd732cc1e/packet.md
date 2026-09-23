# Recovery task _PrepareStrings

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 433 bytes.

```asm
0000 push 0x3e8
0003 nop 
0004 push cs
0005 call 0x3f4 ; _LoadStringAnt
0008 add sp, 2
000b mov es, word ptr [0xc2ac]
000f mov word ptr es:[0x9be6], ax
0013 mov word ptr es:[0x9be8], dx
0018 push 0x3e9
001b nop 
001c push cs
001d call 0x3f4 ; _LoadStringAnt
0020 add sp, 2
0023 mov es, word ptr [0xc2ae]
0027 mov word ptr es:[0x7a4a], ax
002b mov word ptr es:[0x7a4c], dx
0030 push 0x3f2
0033 nop 
0034 push cs
0035 call 0x3f4 ; _LoadStringAnt
0038 add sp, 2
003b mov es, word ptr [0xc2b0]
003f mov word ptr es:[0x737a], ax
0043 mov word ptr es:[0x737c], dx
0048 push 0x3fc
004b nop 
004c push cs
004d call 0x3f4 ; _LoadStringAnt
0050 add sp, 2
0053 mov es, word ptr [0xc2b2]
0057 mov word ptr es:[0x7c94], ax
005b mov word ptr es:[0x7c96], dx
0060 push 0x41a
0063 nop 
0064 push cs
0065 call 0x3f4 ; _LoadStringAnt
0068 add sp, 2
006b mov es, word ptr [0xc2b4]
006f mov word ptr es:[0x72e8], ax
0073 mov word ptr es:[0x72ea], dx
0078 push 0x44c
007b nop 
007c push cs
007d call 0x3f4 ; _LoadStringAnt
0080 add sp, 2
0083 mov es, word ptr [0xc2b6]
0087 mov word ptr es:[0x8098], ax
008b mov word ptr es:[0x809a], dx
0090 push 0x44d
0093 nop 
0094 push cs
0095 call 0x3f4 ; _LoadStringAnt
0098 add sp, 2
009b mov es, word ptr [0xc2b8]
009f mov word ptr es:[0x8074], ax
00a3 mov word ptr es:[0x8076], dx
00a8 push 0x44e
00ab nop 
00ac push cs
00ad call 0x3f4 ; _LoadStringAnt
00b0 add sp, 2
00b3 mov es, word ptr [0xc2ba]
00b7 mov word ptr es:[0x78b2], ax
00bb mov word ptr es:[0x78b4], dx
00c0 push 0x44f
00c3 nop 
00c4 push cs
00c5 call 0x3f4 ; _LoadStringAnt
00c8 add sp, 2
00cb mov es, word ptr [0xc2bc]
00cf mov word ptr es:[0x7892], ax
00d3 mov word ptr es:[0x7894], dx
00d8 push 0x4b0
00db nop 
00dc push cs
00dd call 0x3f4 ; _LoadStringAnt
00e0 add sp, 2
00e3 mov es, word ptr [0xc2be]
00e7 mov word ptr es:[0x9e88], ax
00eb mov word ptr es:[0x9e8a], dx
00f0 push 0x4ba
00f3 nop 
00f4 push cs
00f5 call 0x3f4 ; _LoadStringAnt
00f8 add sp, 2
00fb mov es, word ptr [0xc2c0]
00ff mov word ptr es:[0x76a4], ax
0103 mov word ptr es:[0x76a6], dx
0108 push 0x4c4
010b nop 
010c push cs
010d call 0x3f4 ; _LoadStringAnt
0110 add sp, 2
0113 mov es, word ptr [0xc2c2]
0117 mov word ptr es:[0x9c68], ax
011b mov word ptr es:[0x9c6a], dx
0120 push 0x4ce
0123 nop 
0124 push cs
0125 call 0x3f4 ; _LoadStringAnt
0128 add sp, 2
012b mov es, word ptr [0xc2c4]
012f mov word ptr es:[0xa0ec], ax
0133 mov word ptr es:[0xa0ee], dx
0138 push 0x4d8
013b nop 
013c push cs
013d call 0x3f4 ; _LoadStringAnt
0140 add sp, 2
0143 mov es, word ptr [0xc2c6]
0147 mov word ptr es:[0x8108], ax
014b mov word ptr es:[0x810a], dx
0150 push 0x4e2
0153 nop 
0154 push cs
0155 call 0x3f4 ; _LoadStringAnt
0158 add sp, 2
015b mov es, word ptr [0xc2c8]
015f mov word ptr es:[0x9e8e], ax
0163 mov word ptr es:[0x9e90], dx
0168 push 0x4ec
016b nop 
016c push cs
016d call 0x3f4 ; _LoadStringAnt
0170 add sp, 2
0173 mov es, word ptr [0xc2ca]
0177 mov word ptr es:[0xa076], ax
017b mov word ptr es:[0xa078], dx
0180 push 0x76c
0183 nop 
0184 push cs
0185 call 0x3f4 ; _LoadStringAnt
0188 add sp, 2
018b mov es, word ptr [0xc2cc]
018f mov word ptr es:[0x78ac], ax
0193 mov word ptr es:[0x78ae], dx
0198 push 0x708
019b nop 
019c push cs
019d call 0x3f4 ; _LoadStringAnt
01a0 add sp, 2
01a3 mov es, word ptr [0xc2ce]
01a7 mov word ptr es:[0x7294], ax
01ab mov word ptr es:[0x7296], dx
01b0 retf 
```

## Known declaration examples

- `extern char far * far * far LoadStringAnt(int object);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_initStuff', 'offset': 0, 'source': None, 'size': 576}
- {'symbol': '_SimAllocate', 'offset': 576, 'source': 'src/recovered/SimAllocate.c', 'size': 1}
- {'symbol': '_LoadStringAnt', 'offset': 1012, 'source': None, 'size': 231}
- {'symbol': '_CreateSimPats', 'offset': 1244, 'source': 'src/recovered/CreateSimPats.c', 'size': 1}
