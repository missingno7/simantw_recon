# Recovery task _MakeNewTailB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 101 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 push 0
0009 push 9
000b mov es, word ptr [0xc352]
000f mov al, byte ptr es:[si + 0x3d18]
0014 mov cx, ax
0016 sub ah, ah
0018 add ax, 8
001b push ax
001c mov es, word ptr [0xc364]
0020 mov bl, cl
0022 and bl, 7
0025 xor bl, 4
0028 sub bh, bh
002a mov al, byte ptr es:[bx + 8]
002f cwde 
0030 mov es, word ptr [0xc352]
0034 mov cl, byte ptr es:[si + 0x392c]
0039 sub ch, ch
003b add ax, cx
003d push ax
003e mov ax, es
0040 mov es, word ptr [0xc366]
0044 mov cx, es
0046 mov es, ax
0048 mov dl, byte ptr es:[si + 0x3736]
004d sub dh, dh
004f mov es, cx
0051 mov al, byte ptr es:[bx]
0056 cwde 
0057 add ax, dx
0059 push ax
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToBList
005f add sp, 0xa
0062 pop si
0063 leave 
0064 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetBestDir', 'offset': 16478, 'source': None, 'size': 246}
- {'symbol': '_QueenMoveB', 'offset': 16724, 'source': None, 'size': 246}
- {'symbol': '_KillTailB', 'offset': 17072, 'source': None, 'size': 45}
- {'symbol': '_LostHeadB', 'offset': 17118, 'source': None, 'size': 94}
