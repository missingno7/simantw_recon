# Recovery task _MakePenny

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 66 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 4], 0
000b mov cx, word ptr [bp + 6]
000e shl cx, 6
0011 mov dx, word ptr [bp + 8]
0014 xor si, si
0016 mov di, word ptr [bp - 4]
0019 add di, 0x2356
001d mov al, byte ptr [di]
001f add di, 3
0022 mov bx, cx
0024 add bx, si
0026 add bx, dx
0028 mov byte ptr [bx + 0x28e8], al
002c inc si
002d cmp si, 3
0030 jl 0x3ee7
0032 add cx, 0x40
0035 inc word ptr [bp - 4]
0038 cmp word ptr [bp - 4], 3
003c jl 0x3ede
003e pop si
003f pop di
0040 leave 
0041 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakePlugH', 'offset': 15942, 'source': None, 'size': 66}
- {'symbol': '_MakeKnob', 'offset': 16008, 'source': None, 'size': 66}
- {'symbol': '_MakeClip', 'offset': 16140, 'source': None, 'size': 71}
- {'symbol': '_FillMap', 'offset': 16212, 'source': None, 'size': 85}
