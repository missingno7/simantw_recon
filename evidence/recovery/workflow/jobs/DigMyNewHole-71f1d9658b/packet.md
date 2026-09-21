# Recovery task _DigMyNewHole

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 107 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 xor si, si
0007 cmp word ptr [bp + 6], 1
000b jl 0x1713
000d cmp word ptr [bp + 6], 0x7f
0011 jg 0x1713
0013 cmp word ptr [bp + 8], 1
0017 jl 0x1713
0019 cmp word ptr [bp + 8], 0x3f
001d jg 0x1713
001f mov es, word ptr [0xc3fc]
0023 cmp word ptr es:[0x9b6e], si
0028 je 0x16ee
002a mov bx, word ptr [bp + 8]
002d mov di, word ptr [bp + 6]
0030 shl di, 6
0033 cmp byte ptr [bx + di + 0x28e8], 0xc8
0038 jae 0x1700
003a mov si, 1
003d jmp 0x1700
003f nop 
0040 push word ptr [bp + 8]
0043 push word ptr [bp + 6]
0046 push 1
0048 nop 
0049 push cs
004a call 0x5ad2 ; _IsClear3x3
004d add sp, 6
0050 mov si, ax
0052 cmp si, 1
0055 jne 0x1713
0057 push word ptr [bp + 8]
005a push word ptr [bp + 6]
005d nop 
005e push cs
005f call 0x171a ; _CreateNewHole
0062 add sp, 4
0065 mov ax, si
0067 pop si
0068 pop di
0069 leave 
006a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SRand128', 'offset': 5742, 'source': None, 'size': 31}
- {'symbol': '_SRand256', 'offset': 5774, 'source': None, 'size': 31}
- {'symbol': '_CreateNewHole', 'offset': 5914, 'source': None, 'size': 506}
- {'symbol': '_DigMyTile', 'offset': 6420, 'source': None, 'size': 498}
