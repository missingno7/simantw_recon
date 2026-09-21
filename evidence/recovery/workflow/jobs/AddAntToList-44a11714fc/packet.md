# Recovery task _AddAntToList

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 159 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 xor si, si
0006 cmp word ptr [bp + 6], 1
000a jg 0x5ca8
000c mov es, word ptr [0xc47c]
0010 cmp word ptr es:[0x80f0], 0x3e8
0017 jge 0x5cf9
0019 push word ptr [bp + 0x10]
001c push word ptr [bp + 0xe]
001f push word ptr [bp + 0xc]
0022 push word ptr [bp + 0xa]
0025 push word ptr [bp + 8]
0028 nop 
0029 push cs
002a call 0x2ef0 ; _AddAntToAList
002d jmp 0x5cf3
002f nop 
0030 cmp word ptr [bp + 6], 2
0034 jne 0x5cd2
0036 mov es, word ptr [0xc47e]
003a cmp word ptr es:[0x99d4], 0x1f4
0041 jge 0x5cf9
0043 push word ptr [bp + 0x10]
0046 push word ptr [bp + 0xe]
0049 push word ptr [bp + 0xc]
004c push word ptr [bp + 0xa]
004f push word ptr [bp + 8]
0052 nop 
0053 push cs
0054 call 0x2f4a ; _AddAntToBList
0057 jmp 0x5cf3
0059 nop 
005a mov es, word ptr [0xc480]
005e cmp word ptr es:[0x72cc], 0x1f4
0065 jge 0x5cf9
0067 push word ptr [bp + 0x10]
006a push word ptr [bp + 0xe]
006d push word ptr [bp + 0xc]
0070 push word ptr [bp + 0xa]
0073 push word ptr [bp + 8]
0076 nop 
0077 push cs
0078 call 0x2fa4 ; _AddAntToRList
007b add sp, 0xa
007e mov si, 1
0081 cmp si, 1
0084 jne 0x5d12
0086 push word ptr [bp + 0xc]
0089 push word ptr [bp + 0xa]
008c push word ptr [bp + 8]
008f push word ptr [bp + 6]
0092 nop 
0093 push cs
0094 call 0x5d18 ; _SetLife
0097 add sp, 8
009a mov ax, si
009c pop si
009d leave 
009e retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsClear3x3', 'offset': 23250, 'source': None, 'size': 90}
- {'symbol': '_IsClearTile', 'offset': 23340, 'source': None, 'size': 332}
- {'symbol': '_SetLife', 'offset': 23832, 'source': None, 'size': 432}
- {'symbol': '_IsThisEgg', 'offset': 24264, 'source': 'src/recovered/IsThisEgg.c', 'size': 28}
