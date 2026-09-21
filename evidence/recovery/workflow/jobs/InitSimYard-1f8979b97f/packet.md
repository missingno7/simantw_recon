# Recovery task _InitSimYard

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 304 bytes.

```asm
0000 mov es, word ptr [0xc4f6]
0004 sub ax, ax
0006 mov word ptr es:[0x7d4c], ax
000a mov word ptr es:[0x7d4a], ax
000e mov word ptr [0xac76], 0xb4 ; _BoyX
0014 mov word ptr [0xac78], 0x49 ; _BoyY
001a mov es, word ptr [0xc4f8]
001e mov word ptr es:[0x8a74], 0xc
0025 mov es, word ptr [0xc4fa]
0029 mov word ptr es:[0x8a70], 0x14
0030 mov es, word ptr [0xc4fc]
0034 mov word ptr es:[0x9fbe], ax
0038 mov word ptr es:[0x9fbc], ax
003c mov es, word ptr [0xc4fe]
0040 mov word ptr es:[0x7380], ax
0044 mov word ptr es:[0x737e], ax
0048 mov word ptr [0xac5c], 0xfa ; _DogX
004e mov word ptr [0xac5e], 0x96 ; _DogY
0054 mov ax, 2
0057 mov es, word ptr [0xc500]
005b mov word ptr es:[0x8a72], ax
005f mov es, word ptr [0xc502]
0063 mov word ptr es:[0x7a5a], ax
0067 xor ax, ax
0069 mov es, word ptr [0xc504]
006d mov word ptr es:[0x99da], ax
0071 mov es, word ptr [0xc506]
0075 mov word ptr es:[0x78b0], ax
0079 mov es, word ptr [0xc508]
007d mov word ptr es:[0x78d2], ax
0081 mov word ptr [0xac7a], ax ; _BoyFrame
0084 mov word ptr [0xac74], ax ; _BoyHere
0087 mov es, word ptr [0xc50a]
008b mov word ptr es:[0x8a80], ax
008f mov es, word ptr [0xc50c]
0093 mov word ptr es:[0x8a84], ax
0097 mov es, word ptr [0xc50e]
009b mov word ptr es:[0x8a86], ax
009f mov word ptr [0xac64], ax ; _BirdOn
00a2 mov es, word ptr [0xc510]
00a6 mov word ptr es:[0x72b6], ax
00aa mov word ptr [0xac6a], ax ; _CatFrame
00ad mov word ptr [0xac6c], ax ; _CatOn
00b0 mov word ptr [0xac60], ax ; _DogFrame
00b3 mov es, word ptr [0xc512]
00b7 mov word ptr es:[0x7d5a], ax
00bb mov es, word ptr [0xc514]
00bf mov word ptr es:[0x8a7e], ax
00c3 mov es, word ptr [0xc516]
00c7 mov word ptr es:[0x8a82], ax
00cb mov es, word ptr [0xc518]
00cf mov word ptr es:[0x7a4e], ax
00d3 mov es, word ptr [0xc51a]
00d7 mov word ptr es:[0x7a58], ax
00db mov es, word ptr [0xc51c]
00df mov word ptr es:[0x9af4], ax
00e3 mov es, word ptr [0xc51e]
00e7 mov word ptr es:[0x9afc], ax
00eb mov es, word ptr [0xc520]
00ef mov word ptr es:[0x7c92], ax
00f3 mov word ptr [0xac72], ax ; _RainOn
00f6 mov es, word ptr [0xc522]
00fa mov word ptr es:[0x99e6], ax
00fe mov es, word ptr [0xc524]
0102 mov word ptr es:[0x9b30], ax
0106 mov ax, 1
0109 mov word ptr [0xac62], ax ; _BirdFrame
010c mov es, word ptr [0xc526]
0110 mov word ptr es:[0x72c0], ax
0114 mov es, word ptr [0xc528]
0118 mov word ptr es:[0x8118], ax
011c mov ax, 0xffff
011f mov es, word ptr [0xc52a]
0123 mov word ptr es:[0x72f2], ax
0127 mov es, word ptr [0xc52c]
012b mov word ptr es:[0x7a5c], ax
012f retf 
```

## Known declaration examples

- `extern int near BirdFrame;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetRedDefendDir', 'offset': 4500, 'source': None, 'size': 343}
- {'symbol': '_Bounce', 'offset': 4844, 'source': 'src/recovered/wf_Bounce-0d87abbf42.c', 'size': 140}
- {'symbol': '_DoSimYard', 'offset': 5288, 'source': None, 'size': 262}
- {'symbol': '_SendBoyMsg', 'offset': 5550, 'source': None, 'size': 59}
