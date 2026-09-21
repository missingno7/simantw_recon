# Recovery task _AllocateMapBuffer

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 79 bytes.

```asm
0000 cmp word ptr [0x19aa], 0 ; _mapBuf
0005 jne 0xcd3c
0007 push ds
0008 push 0x19cc
000b push 1
000d mov al, byte ptr [0xcc7e] ; _displayType
0010 and al, 1
0012 cmp al, 1
0014 sbb ax, ax
0016 and ax, 3
0019 inc ax
001a push ax
001b mov es, word ptr [0xc1e2]
001f mov ax, word ptr es:[0x8096]
0023 shl ax, 6
0026 push ax
0027 mov es, word ptr [0xc1e4]
002b mov ax, word ptr es:[0x807c]
002f shl ax, 7
0032 push ax
0033 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _BitmapImageSize
0038 add sp, 6
003b add ax, 0x20
003e adc dx, 0
0041 push dx
0042 push ax
0043 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 70, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0048 add sp, 0xa
004b mov word ptr [0x19aa], ax ; _mapBuf
004e retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPicS-f46da1bb8a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GSetAttrib-bba4337448.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ToggleMapCursor', 'offset': 51022, 'source': None, 'size': 261}
- {'symbol': '_DrawMapData', 'offset': 52064, 'source': None, 'size': 397}
- {'symbol': '_DrawMap', 'offset': 52542, 'source': None, 'size': 264}
- {'symbol': '_win_DrawMapWindow', 'offset': 52806, 'source': None, 'size': 712}
