# Recovery task _PatchColorArrays

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 206 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov byte ptr [bp - 0x10], 0xf
000a mov byte ptr [bp - 0xf], 0xb
000e mov byte ptr [bp - 0xd], 9
0012 mov byte ptr [bp - 0xc], 0xe
0016 mov byte ptr [bp - 0xb], 5
001a mov byte ptr [bp - 0xa], 4
001e mov byte ptr [bp - 9], 0xc
0022 mov al, 2
0024 mov byte ptr [bp - 0xe], al
0027 mov byte ptr [bp - 8], al
002a mov byte ptr [bp - 7], 0xa
002e mov byte ptr [bp - 5], 3
0032 mov byte ptr [bp - 4], 6
0036 mov byte ptr [bp - 3], 8
003a mov al, 7
003c mov byte ptr [bp - 6], al
003f mov byte ptr [bp - 2], al
0042 xor si, si
0044 mov byte ptr [bp - 1], 0
0048 mov di, word ptr [si - 0x5718]
004c and di, 0xff
0050 mov al, byte ptr [bp + di - 0x10]
0053 mov byte ptr [si - 0x5718], al
0057 inc si
0058 cmp si, 0x90
005c jl 0x3f54
005e xor si, si
0060 mov di, word ptr [si - 0x5688]
0064 and di, 0xff
0068 mov al, byte ptr [bp + di - 0x10]
006b mov byte ptr [si - 0x5688], al
006f inc si
0070 cmp si, 0xd0
0074 jl 0x3f6c
0076 xor si, si
0078 mov di, word ptr [si - 0x55b8]
007c and di, 0xff
0080 mov al, byte ptr [bp + di - 0x10]
0083 mov byte ptr [si - 0x55b8], al
0087 inc si
0088 cmp si, 0x20
008b jl 0x3f84
008d xor si, si
008f mov di, word ptr [si - 0x5598]
0093 and di, 0xff
0097 mov al, byte ptr [bp + di - 0x10]
009a mov byte ptr [si - 0x5598], al
009e mov di, word ptr [si - 0x5580]
00a2 and di, 0xff
00a6 mov al, byte ptr [bp + di - 0x10]
00a9 mov byte ptr [si - 0x5580], al
00ad inc si
00ae cmp si, 0x18
00b1 jl 0x3f9b
00b3 xor si, si
00b5 mov di, word ptr [si - 0x5568]
00b9 and di, 0xff
00bd mov al, byte ptr [bp + di - 0x10]
00c0 mov byte ptr [si - 0x5568], al
00c4 inc si
00c5 cmp si, 0x10
00c8 jl 0x3fc1
00ca pop si
00cb pop di
00cc leave 
00cd retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitInstance', 'offset': 15498, 'source': None, 'size': 325}
- {'symbol': '_InitApplication', 'offset': 15824, 'source': None, 'size': 315}
- {'symbol': 'WINMAIN', 'offset': 16346, 'source': None, 'size': 1546}
- {'symbol': '_SetDevicePalette', 'offset': 17892, 'source': None, 'size': 185}
