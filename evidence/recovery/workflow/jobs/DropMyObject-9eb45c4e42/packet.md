# Recovery task _DropMyObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 100 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov ax, word ptr [0xcc84] ; _MeType
0006 cmp ax, 0x48
0009 je 0x923a
000b ja 0x9209
000d sub al, 8
000f je 0x920e
0011 sub al, 0x10
0013 je 0x9224
0015 sub al, 0x10
0017 je 0x923a
0019 sub al, 0x10
001b je 0x9224
001d xor ax, ax
001f leave 
0020 retf 
0021 nop 
0022 push word ptr [bp + 0xe]
0025 push word ptr [bp + 0xc]
0028 push word ptr [bp + 0xa]
002b push word ptr [bp + 8]
002e push word ptr [bp + 6]
0031 nop 
0032 push cs
0033 call 0x8188 ; _DropMyEgg
0036 leave 
0037 retf 
0038 push word ptr [bp + 0xe]
003b push word ptr [bp + 0xc]
003e push word ptr [bp + 0xa]
0041 push word ptr [bp + 8]
0044 push word ptr [bp + 6]
0047 nop 
0048 push cs
0049 call 0x7576 ; _DropMyFood
004c leave 
004d retf 
004e push word ptr [bp + 0xe]
0051 push word ptr [bp + 0xc]
0054 push word ptr [bp + 0xa]
0057 push word ptr [bp + 8]
005a push word ptr [bp + 6]
005d nop 
005e push cs
005f call 0x7c52 ; _DropMyRock
0062 leave 
0063 retf 
```

## Known declaration examples

- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PickupMyEgg', 'offset': 36502, 'source': None, 'size': 181}
- {'symbol': '_PickupMyFood', 'offset': 36684, 'source': None, 'size': 672}
- {'symbol': '_PickupMyObject', 'offset': 37456, 'source': None, 'size': 241}
- {'symbol': '_TileCanBeMovedOn', 'offset': 37698, 'source': None, 'size': 349}
