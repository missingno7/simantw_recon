# Recovery task _DrawSimBird

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 105 bytes.

```asm
0000 enter 4, 0
0004 mov ax, word ptr [0xac66] ; _BirdX
0007 sub ax, 0xa
000a mov word ptr [bp - 2], ax
000d mov ax, word ptr [0xac68] ; _BirdY
0010 sub ax, 3
0013 mov word ptr [bp - 4], ax
0016 cmp word ptr [0xac62], 0 ; _BirdFrame
001b je 0xb1ba
001d inc word ptr [bp - 2]
0020 add word ptr [bp - 4], 2
0024 cmp word ptr [0x188c], -1
0029 je 0xb1e2
002b push -1
002d push word ptr [0x188c]
0031 push word ptr [0x1886] ; _yardAnimHandle
0035 mov ax, word ptr [0xac62] ; _BirdFrame
0038 add ax, 0x4e2
003b push ax
003c push word ptr [bp - 4]
003f push word ptr [bp - 2]
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
0047 add sp, 0xc
004a leave 
004b retf 
004c push -1
004e mov ax, word ptr [0xac62] ; _BirdFrame
0051 add ax, 0x4e2
0054 push ax
0055 push word ptr [bp - 4]
0058 push word ptr [bp - 2]
005b push word ptr [0x1886] ; _yardAnimHandle
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
0064 mov word ptr [0x188c], ax
0067 leave 
0068 retf 
```

## Known declaration examples

- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawForSale-956dc12b43.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawSimKid', 'offset': 44820, 'source': None, 'size': 507}
- {'symbol': '_DrawDog', 'offset': 45328, 'source': None, 'size': 134}
- {'symbol': '_DrawSimCat', 'offset': 45568, 'source': None, 'size': 132}
- {'symbol': '_DrawForSale', 'offset': 45700, 'source': 'src/recovered/wf_DrawForSale-956dc12b43.c', 'size': 63}
