# Recovery task _win_GetArg

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 60 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov bx, word ptr [bp + 6]
0007 mov ax, bx
0009 mov al, ah
000b cwde 
000c mov es, word ptr [0xc6dc]
0010 cmp word ptr es:[0x78de], ax
0015 jg 0xe596
0017 cmp bx, 0x2800
001b jge 0xe596
001d mov ax, 0x8000
0020 pop si
0021 leave 
0022 retf 
0023 nop 
0024 sar bx, 8
0027 shl bx, 2
002a les bx, ptr [bx - 0x3166]
002e add bx, 0x10
0031 mov si, word ptr [bp + 8]
0034 shl si, 1
0036 mov ax, word ptr es:[bx + si]
0039 pop si
003a leave 
003b retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_AutoSize', 'offset': 58374, 'source': None, 'size': None}
- {'symbol': '_win_GetVal', 'offset': 58600, 'source': None, 'size': 138}
- {'symbol': '__win_CalcObjElement', 'offset': 58798, 'source': None, 'size': None}
- {'symbol': '_win_Recalc', 'offset': 59106, 'source': None, 'size': None}
