# Recovery task _DrawRain

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 112 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, 0xe
0009 mov si, 0xcb20
000c jmp 0xbb00
000e push 0x190
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0016 add sp, 2
0019 add ax, 0x32
001c mov word ptr [bp - 2], ax
001f push 0x96
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0027 add sp, 2
002a cmp word ptr [si], -1
002d je 0xbae8
002f push 0x8000
0032 push word ptr [si]
0034 push word ptr [0x1886] ; _yardAnimHandle
0038 push 0x1b5d
003b push ax
003c push word ptr [bp - 2]
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_SetObjectPos
0044 add sp, 0xc
0047 jmp 0xbb00
0049 nop 
004a push 0x3e8
004d push 0x1b5d
0050 push ax
0051 push word ptr [bp - 2]
0054 push word ptr [0x1886] ; _yardAnimHandle
0058 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 91, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_AddAnimObject
005d add sp, 0xa
0060 mov word ptr [si], ax
0062 sub si, 2
0065 mov ax, di
0067 dec di
0068 or ax, ax
006a jne 0xbaac
006c pop si
006d pop di
006e leave 
006f retf 
```

## Known declaration examples

- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_SetObjectPos(int right, int bottom, int size, int animation, int object, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int near yardAnimHandle;` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DrawAnimYardMessage', 'offset': 45994, 'source': None, 'size': 184}
- {'symbol': '_Draw_SimYard', 'offset': 46178, 'source': None, 'size': 1595}
- {'symbol': '_DrawSwarm', 'offset': 47886, 'source': None, 'size': 718}
- {'symbol': '_TooFar', 'offset': 48604, 'source': 'src/recovered/wf_TooFar-89685c4366.c', 'size': 39}
