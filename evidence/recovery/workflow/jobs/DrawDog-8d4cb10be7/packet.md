# Recovery task _DrawDog

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 134 bytes.

```asm
0000 enter 4, 0
0004 mov ax, word ptr [0xac5c] ; _DogX
0007 mov word ptr [bp - 2], ax
000a mov ax, word ptr [0xac5e] ; _DogY
000d mov word ptr [bp - 4], ax
0010 cmp word ptr [0xac5a], 0 ; _ForSaleState
0015 jne 0xb194
0017 mov dx, word ptr [0xac60] ; _DogFrame
001b cmp dx, 0xc
001e jge 0xb140
0020 mov bx, dx
0022 mov al, byte ptr [bx + 0x1918]
0026 cwde 
0027 add word ptr [bp - 2], ax
002a mov al, byte ptr [bx + 0x1924]
002e jmp 0xb14e
0030 mov bx, dx
0032 mov al, byte ptr [bx + 0x18cc]
0036 cwde 
0037 add word ptr [bp - 2], ax
003a mov al, byte ptr [bx + 0x18d0]
003e cwde 
003f add word ptr [bp - 4], ax
0042 cmp word ptr [0x188e], -1
0047 je 0xb17a
0049 push -1
004b push word ptr [0x188e]
004f push word ptr [0x1886] ; _yardAnimHandle
0053 mov ax, dx
0055 add ax, 0x2134
0058 push ax
0059 push word ptr [bp - 4]
005c push word ptr [bp - 2]
005f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 98, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
0064 add sp, 0xc
0067 leave 
0068 retf 
0069 nop 
006a push -1
006c mov ax, dx
006e add ax, 0x2134
0071 push ax
0072 push word ptr [bp - 4]
0075 push word ptr [bp - 2]
0078 push word ptr [0x1886] ; _yardAnimHandle
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
0081 mov word ptr [0x188e], ax
0084 leave 
0085 retf 
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

- {'symbol': '_UpdateYard', 'offset': 44764, 'source': 'src/recovered/wf_UpdateYard-32751811c5.c', 'size': 56}
- {'symbol': '_DrawSimKid', 'offset': 44820, 'source': None, 'size': 507}
- {'symbol': '_DrawSimBird', 'offset': 45462, 'source': 'src/recovered/wf_DrawSimBird-fa6c3c3f83.c', 'size': 105}
- {'symbol': '_DrawSimCat', 'offset': 45568, 'source': None, 'size': 132}
