# Recovery task _ScanForAnts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 113 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov ax, word ptr [0xac7c] ; _SpidX
0009 sar ax, 4
000c mov word ptr [bp - 6], ax
000f mov ax, word ptr [0xac7e] ; _SpidY
0012 sar ax, 4
0015 mov word ptr [bp - 0xa], ax
0018 mov word ptr [bp - 8], 0
001d mov dx, 0xffff
0020 mov cx, 0xffff
0023 mov ax, word ptr [bp - 6]
0026 add ax, dx
0028 mov di, ax
002a mov word ptr [bp - 4], dx
002d mov dx, word ptr [bp - 8]
0030 mov bx, word ptr [bp - 0xa]
0033 add bx, cx
0035 mov ax, word ptr [bp - 6]
0038 add ax, word ptr [bp - 4]
003b js 0x53ba
003d cmp di, 0x7f
0040 jg 0x53ba
0042 or bx, bx
0044 jl 0x53ba
0046 cmp bx, 0x3f
0049 jg 0x53ba
004b mov si, di
004d shl si, 6
0050 cmp byte ptr [bx + si + 0x68e8], 0
0055 je 0x53ba
0057 inc dx
0058 inc cx
0059 cmp cx, 3
005c jl 0x5392
005e mov word ptr [bp - 8], dx
0061 mov dx, word ptr [bp - 4]
0064 inc dx
0065 cmp dx, 3
0068 jl 0x5382
006a mov ax, word ptr [bp - 8]
006d pop si
006e pop di
006f leave 
0070 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitSpider', 'offset': 18024, 'source': None, 'size': 156}
- {'symbol': '_MoveSpider', 'offset': 18180, 'source': None, 'size': None}
- {'symbol': '_KillSpider', 'offset': 21460, 'source': None, 'size': 34}
- {'symbol': '_SFoundAnt', 'offset': 21494, 'source': None, 'size': 319}
