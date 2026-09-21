# Recovery task _win_SetColorNum

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 87 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov ax, word ptr [bp + 6]
0006 mov cx, ax
0008 shl ax, 1
000a add ax, cx
000c shl ax, 1
000e add ax, 0x78ec
0011 mov word ptr [0xcc58], ax
0014 mov <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
001a test byte ptr [0xcc7e], 1 ; _displayType
001f jne 0xb420
0021 les bx, ptr [0xcc58]
0025 mov al, byte ptr es:[bx]
0028 cwde 
0029 imul ax, ax, 0x101
002d push ax
002e mov cx, ax
0030 mov al, byte ptr es:[bx + 2]
0034 jmp 0xb433
0036 les bx, ptr [0xcc58]
003a mov al, byte ptr es:[bx]
003d cwde 
003e imul ax, ax, 0x101
0042 push ax
0043 mov cx, ax
0045 mov al, byte ptr es:[bx + 3]
0049 cwde 
004a imul ax, ax, 0x101
004e push ax
004f push cx
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
0055 leave 
0056 retf 
```

## Known declaration examples

- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPicS-f46da1bb8a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GSetAttrib-bba4337448.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CopyMaskBitmap2', 'offset': 45328, 'source': None, 'size': 496}
- {'symbol': '_gr_JustifyStrInRect', 'offset': 45824, 'source': None, 'size': 234}
- {'symbol': '_win_SetColorFromObj', 'offset': 46146, 'source': None, 'size': 111}
- {'symbol': '_win_SetColorFromObjNum', 'offset': 46258, 'source': None, 'size': 152}
