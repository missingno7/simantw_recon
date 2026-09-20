# Recovery task _TargetAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 73 bytes.

```asm
0000 enter 4, 0
0004 mov bx, 0x7c22
0007 mov es, word ptr [0xc482]
000b mov word ptr [bp - 4], bx
000e mov word ptr [bp - 2], es
0011 cmp word ptr es:[bx], 0xb
0015 jne 0x6704
0017 mov word ptr es:[bx], 0xffff
001c mov es, word ptr [0xc484]
0020 push word ptr es:[0x9ea2]
0025 jmp 0x671e
0027 nop 
0028 mov es, word ptr [0xc486]
002c mov ax, word ptr es:[0x9c28]
0030 mov es, word ptr [0xc484]
0034 mov word ptr es:[0x9ea2], ax
0038 les bx, ptr [bp - 4]
003b mov word ptr es:[bx], 0xb
0040 push 1
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PauseGame
0047 leave 
0048 retf 
```

## Known declaration examples

- `extern void far PauseGame(int paused);` — src/recovered/EndLifeTransferMode.c
- `extern void far PauseGame(int paused);` — src/recovered/EndTargetMode.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoMapUpdateDraw', 'offset': 26324, 'source': 'src/recovered/DoMapUpdateDraw.c', 'size': 1}
- {'symbol': '_DoEditAndMapUpdateDraw', 'offset': 26326, 'source': 'src/recovered/DoEditAndMapUpdateDraw.c', 'size': 6}
- {'symbol': '_EndTargetMode', 'offset': 26406, 'source': 'src/recovered/EndTargetMode.c', 'size': 29}
- {'symbol': '_StartLifeTransfer', 'offset': 26436, 'source': None, 'size': 73}
