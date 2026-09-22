# Recovery task _ClearHistory

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 299 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 xor ax, ax
0006 mov es, word ptr [0xc086]
000a mov cx, 0x40
000d mov di, 0x9dea
0010 rep stosw word ptr es:[di], ax
0012 mov es, word ptr [0xc088]
0016 mov cx, 0x40
0019 mov di, 0x9eac
001c rep stosw word ptr es:[di], ax
001e mov es, word ptr [0xc08a]
0022 mov cx, 0x40
0025 mov di, 0x9cf2
0028 rep stosw word ptr es:[di], ax
002a mov es, word ptr [0xc08c]
002e mov cx, 0x40
0031 mov di, 0x7382
0034 rep stosw word ptr es:[di], ax
0036 mov es, word ptr [0xc08e]
003a mov cx, 0x40
003d mov di, 0x9ff0
0040 rep stosw word ptr es:[di], ax
0042 mov es, word ptr [0xc090]
0046 mov cx, 0x40
0049 mov di, 0x9f30
004c rep stosw word ptr es:[di], ax
004e mov es, word ptr [0xc092]
0052 mov cx, 0x40
0055 mov di, 0x7d76
0058 rep stosw word ptr es:[di], ax
005a mov es, word ptr [0xc094]
005e mov cx, 0x40
0061 mov di, 0x7c98
0064 rep stosw word ptr es:[di], ax
0066 mov es, word ptr [0xc096]
006a mov cx, 0x40
006d mov di, 0x7608
0070 rep stosw word ptr es:[di], ax
0072 mov es, word ptr [0xc098]
0076 mov cx, 0x40
0079 mov di, 0x72fa
007c rep stosw word ptr es:[di], ax
007e cmp word ptr [bp + 6], 1
0082 jne 0x8db1
0084 mov es, word ptr [0xc09a]
0088 mov word ptr es:[0x789a], ax
008c mov word ptr es:[0x7898], ax
0090 mov ax, 1
0093 mov es, word ptr [0xc09c]
0097 mov word ptr es:[0x80d4], ax
009b mov es, word ptr [0xc09e]
009f mov word ptr es:[0x9c80], ax
00a3 xor ax, ax
00a5 mov es, word ptr [0xc0a0]
00a9 mov word ptr es:[0xa0dc], ax
00ad mov es, word ptr [0xc0a2]
00b1 mov word ptr es:[0x7896], ax
00b5 mov es, word ptr [0xc0a4]
00b9 mov word ptr es:[0x9e6e], 0x3f
00c0 mov es, word ptr [0xc0a6]
00c4 mov word ptr es:[0x8670], ax
00c8 mov es, word ptr [0xc0a8]
00cc mov word ptr es:[0x76a2], ax
00d0 mov word ptr es:[0x76a0], ax
00d4 mov es, word ptr [0xc0aa]
00d8 mov word ptr es:[0x9b28], ax
00dc mov word ptr es:[0x9b26], ax
00e0 mov es, word ptr [0xc0ac]
00e4 mov word ptr es:[0x99e2], ax
00e8 mov word ptr es:[0x99e0], ax
00ec mov es, word ptr [0xc0ae]
00f0 mov word ptr es:[0x7d5e], ax
00f4 mov word ptr es:[0x7d5c], ax
00f8 mov es, word ptr [0xc0b0]
00fc mov word ptr es:[0x9fc8], ax
0100 mov word ptr es:[0x9fc6], ax
0104 mov es, word ptr [0xc0b2]
0108 mov word ptr es:[0x9e98], ax
010c mov word ptr es:[0x9e96], ax
0110 mov es, word ptr [0xc0b4]
0114 mov word ptr es:[0x9afa], ax
0118 mov word ptr es:[0x9af8], ax
011c mov es, word ptr [0xc0b6]
0120 mov word ptr es:[0x7c20], ax
0124 mov word ptr es:[0x7c1e], ax
0128 pop di
0129 leave 
012a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ProcHistoryEvent', 'offset': 35446, 'source': None, 'size': 245}
- {'symbol': '_ToggleHistButton', 'offset': 35692, 'source': None, 'size': 400}
- {'symbol': '_win_DrawHistoryWindow', 'offset': 36392, 'source': None, 'size': 80}
- {'symbol': '_drawHistGraph', 'offset': 36472, 'source': None, 'size': 777}
