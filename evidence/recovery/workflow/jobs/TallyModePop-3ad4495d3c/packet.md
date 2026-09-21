# Recovery task _TallyModePop

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 230 bytes.

```asm
0000 mov es, word ptr [0xc302]
0004 mov ax, word ptr es:[0x786e]
0008 add ax, word ptr es:[0x7870]
000d mov es, word ptr [0xc304]
0011 mov word ptr es:[0x9e70], ax
0015 mov es, word ptr [0xc302]
0019 mov ax, word ptr es:[0x7872]
001d add ax, word ptr es:[0x7874]
0022 mov es, word ptr [0xc304]
0026 mov word ptr es:[0x9e72], ax
002a mov es, word ptr [0xc302]
002e mov ax, word ptr es:[0x786c]
0032 mov es, word ptr [0xc304]
0036 mov word ptr es:[0x9e74], ax
003a mov es, word ptr [0xc302]
003e mov ax, word ptr es:[0x7878]
0042 mov es, word ptr [0xc304]
0046 mov word ptr es:[0x9e76], ax
004a mov es, word ptr [0xc302]
004e mov ax, word ptr es:[0x7882]
0052 mov es, word ptr [0xc304]
0056 mov word ptr es:[0x9e78], ax
005a mov es, word ptr [0xc302]
005e mov ax, word ptr es:[0x7876]
0062 mov es, word ptr [0xc304]
0066 mov word ptr es:[0x9e7a], ax
006a mov es, word ptr [0xc300]
006e mov ax, word ptr es:[0x7be8]
0072 add ax, word ptr es:[0x7bea]
0077 mov es, word ptr [0xc306]
007b mov word ptr es:[0xa084], ax
007f mov es, word ptr [0xc300]
0083 mov ax, word ptr es:[0x7bec]
0087 add ax, word ptr es:[0x7bee]
008c mov es, word ptr [0xc306]
0090 mov word ptr es:[0xa086], ax
0094 mov es, word ptr [0xc300]
0098 mov ax, word ptr es:[0x7be6]
009c mov es, word ptr [0xc306]
00a0 mov word ptr es:[0xa088], ax
00a4 mov es, word ptr [0xc300]
00a8 mov ax, word ptr es:[0x7bf2]
00ac mov es, word ptr [0xc306]
00b0 mov word ptr es:[0xa08a], ax
00b4 mov es, word ptr [0xc300]
00b8 mov ax, word ptr es:[0x7bfc]
00bc mov es, word ptr [0xc306]
00c0 mov word ptr es:[0xa08c], ax
00c4 mov es, word ptr [0xc300]
00c8 mov ax, word ptr es:[0x7bf0]
00cc mov es, word ptr [0xc306]
00d0 mov word ptr es:[0xa08e], ax
00d4 mov es, word ptr [0xc300]
00d8 cmp word ptr es:[0x7c0a], 1
00de jge 0x473
00e0 nop 
00e1 push cs
00e2 call 0xffff967c
00e5 ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoSmells', 'offset': 762, 'source': None, 'size': 79}
- {'symbol': '_ClrModePop', 'offset': 842, 'source': None, 'size': 67}
- {'symbol': '_FeedAnts', 'offset': 1140, 'source': None, 'size': 100}
- {'symbol': '_DoAntSimA', 'offset': 1240, 'source': None, 'size': None}
