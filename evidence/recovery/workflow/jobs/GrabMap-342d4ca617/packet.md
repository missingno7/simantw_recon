# Recovery task _GrabMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 64 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 mov dx, word ptr [bp + 6]
0007 cmp dx, 0x7f
000a jle 0x6dbc
000c xor bx, bx
000e jmp 0x6dc8
0010 or dx, dx
0012 jge 0x6dc6
0014 mov bx, 0x7f
0017 jmp 0x6dc8
0019 nop 
001a mov bx, dx
001c cmp word ptr [bp + 8], 0x3f
0020 jle 0x6dd2
0022 xor di, di
0024 jmp 0x6de0
0026 mov dx, word ptr [bp + 8]
0029 or dx, dx
002b jge 0x6dde
002d mov di, 0x3f
0030 jmp 0x6de0
0032 mov di, dx
0034 shl bx, 6
0037 mov al, byte ptr [bx + di + 0x28e8]
003b sub ah, ah
003d pop di
003e leave 
003f retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AddBlackAnts', 'offset': 27738, 'source': None, 'size': 163}
- {'symbol': '_AddRedAnts', 'offset': 27902, 'source': None, 'size': 173}
- {'symbol': '_ClrArrays', 'offset': 28140, 'source': None, 'size': 273}
- {'symbol': '_goStepRight', 'offset': 28414, 'source': None, 'size': 181}
