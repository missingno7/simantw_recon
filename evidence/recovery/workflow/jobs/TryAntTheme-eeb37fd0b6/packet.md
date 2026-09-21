# Recovery task _TryAntTheme

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 104 bytes.

```asm
0000 enter 4, 0
0004 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
0009 mov es, word ptr [0xc2fa]
000d mov cx, word ptr es:[0x806e]
0012 mov bx, word ptr es:[0x8070]
0017 add cx, 0x1c20
001b adc bx, 0
001e cmp bx, dx
0020 jg 0x147a
0022 jl 0x143c
0024 cmp cx, ax
0026 ja 0x147a
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _TickCount
002d mov es, word ptr [0xc2fa]
0031 mov word ptr es:[0x806e], ax
0035 mov word ptr es:[0x8070], dx
003a mov bx, 0x80ba
003d mov es, word ptr [0xc2fc]
0041 mov word ptr [bp - 4], bx
0044 mov word ptr [bp - 2], es
0047 inc word ptr es:[bx]
004a cmp word ptr es:[bx], 2
004e jle 0x1469
0050 mov word ptr es:[bx], 0
0055 push 0x7e
0057 les bx, ptr [bp - 4]
005a mov ax, word ptr es:[bx]
005d add ax, 0x2713
0060 push ax
0061 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 100, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSong
0066 leave 
0067 retf 
```

## Known declaration examples

- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetEnterDirB', 'offset': 4836, 'source': None, 'size': 152}
- {'symbol': '_GetEnterDirR', 'offset': 4988, 'source': None, 'size': 152}
- {'symbol': '_SGIRand', 'offset': 5244, 'source': None, 'size': 39}
- {'symbol': '_SGRand', 'offset': 5284, 'source': None, 'size': 39}
