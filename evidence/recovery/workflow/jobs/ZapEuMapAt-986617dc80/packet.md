# Recovery task _ZapEuMapAt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 76 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov si, word ptr [bp + 8]
0008 push word ptr [bp + 0xa]
000b push si
000c push word ptr [bp + 6]
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _TileIsVisible
0014 add sp, 6
0017 dec ax
0018 jne 0x48
001a mov di, si
001c or si, si
001e jl 0x48
0020 cmp word ptr [0xcc80], di ; _editWidth
0024 jle 0x48
0026 mov bx, word ptr [bp + 0xa]
0029 or bx, bx
002b jl 0x48
002d cmp word ptr [0xcd7a], bx ; _editHeight
0031 jle 0x48
0033 mov ax, bx
0035 imul word ptr [0xcc80] ; _editWidth
0039 mov bx, ax
003b add bx, di
003d shl bx, 1
003f les si, ptr [0x1442]
0043 mov word ptr es:[bx + si], 0xffff
0048 pop si
0049 pop di
004a leave 
004b retf 
```

## Known declaration examples

- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InvalEuMap', 'offset': 76, 'source': None, 'size': 168}
- {'symbol': '_OverlayTileSet', 'offset': 244, 'source': None, 'size': 227}
