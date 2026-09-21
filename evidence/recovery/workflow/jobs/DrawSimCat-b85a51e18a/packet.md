# Recovery task _DrawSimCat

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 132 bytes.

```asm
0000 enter 4, 0
0004 mov dx, word ptr [0xac6a] ; _CatFrame
0008 mov ax, word ptr [0xac6e] ; _CatX
000b mov word ptr [bp - 2], ax
000e mov ax, word ptr [0xac70] ; _CatY
0011 mov word ptr [bp - 4], ax
0014 cmp dx, 0xa
0017 jl 0xb240
0019 cmp dx, 0x14
001c jge 0xb22e
001e mov bx, dx
0020 mov al, byte ptr [bx + 0x192e]
0024 cwde 
0025 add word ptr [bp - 2], ax
0028 mov al, byte ptr [bx + 0x1932]
002c jmp 0xb23c
002e mov bx, dx
0030 mov al, byte ptr [bx + 0x192c]
0034 cwde 
0035 add word ptr [bp - 2], ax
0038 mov al, byte ptr [bx + 0x1936]
003c cwde 
003d add word ptr [bp - 4], ax
0040 cmp word ptr [0x188a], -1
0045 je 0xb268
0047 push -1
0049 push word ptr [0x188a]
004d push word ptr [0x1886] ; _yardAnimHandle
0051 mov ax, dx
0053 add ax, 0x514
0056 push ax
0057 push word ptr [bp - 4]
005a push word ptr [bp - 2]
005d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 96, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
0062 add sp, 0xc
0065 leave 
0066 retf 
0067 nop 
0068 push -1
006a mov ax, dx
006c add ax, 0x514
006f push ax
0070 push word ptr [bp - 4]
0073 push word ptr [bp - 2]
0076 push word ptr [0x1886] ; _yardAnimHandle
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
007f mov word ptr [0x188a], ax
0082 leave 
0083 retf 
```

## Known declaration examples

- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawDog', 'offset': 45328, 'source': None, 'size': 134}
- {'symbol': '_DrawSimBird', 'offset': 45462, 'source': 'src/recovered/wf_DrawSimBird-fa6c3c3f83.c', 'size': 105}
- {'symbol': '_DrawForSale', 'offset': 45700, 'source': 'src/recovered/wf_DrawForSale-956dc12b43.c', 'size': 63}
- {'symbol': '_DrawMower', 'offset': 45764, 'source': None, 'size': 229}
