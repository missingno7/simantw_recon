# Recovery task _MakeClip

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 71 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 4], 0
000b mov cx, word ptr [bp + 6]
000e shl cx, 6
0011 mov dx, word ptr [bp + 8]
0014 xor di, di
0016 mov si, word ptr [bp - 4]
0019 add si, 0x2360
001d cmp byte ptr [si], 0
0020 je 0x3f3a
0022 mov al, byte ptr [si]
0024 mov bx, cx
0026 add bx, di
0028 add bx, dx
002a mov byte ptr [bx + 0x28e8], al
002e add si, 3
0031 inc di
0032 cmp di, 3
0035 jl 0x3f29
0037 add cx, 0x40
003a inc word ptr [bp - 4]
003d cmp word ptr [bp - 4], 3
0041 jl 0x3f20
0043 pop si
0044 pop di
0045 leave 
0046 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeKnob', 'offset': 16008, 'source': None, 'size': 66}
- {'symbol': '_MakePenny', 'offset': 16074, 'source': None, 'size': 66}
- {'symbol': '_FillMap', 'offset': 16212, 'source': None, 'size': 85}
- {'symbol': '_FillMapLegs', 'offset': 16298, 'source': None, 'size': 503}
