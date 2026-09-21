# Recovery task _win_SetColorFromObj

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 111 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 les si, ptr [bp + 6]
0007 test byte ptr es:[si + 0x24], 4
000c je 0xb456
000e mov al, byte ptr es:[si + 0x27]
0012 jmp 0xb45a
0014 mov al, byte ptr es:[si + 0x26]
0018 cwde 
0019 mov cx, ax
001b shl ax, 1
001d add ax, cx
001f shl ax, 1
0021 add ax, 0x78ec
0024 mov word ptr [0xcc58], ax
0027 mov <resolved loader operand; see bindings> ; [{'operand_offset': 43, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002d test byte ptr [0xcc7e], 1 ; _displayType
0032 jne 0xb48c
0034 les bx, ptr [0xcc58]
0038 mov al, byte ptr es:[bx]
003b cwde 
003c imul ax, ax, 0x101
0040 push ax
0041 mov cx, ax
0043 mov al, byte ptr es:[bx + 2]
0047 jmp 0xb49f
0049 nop 
004a les bx, ptr [0xcc58]
004e mov al, byte ptr es:[bx]
0051 cwde 
0052 imul ax, ax, 0x101
0056 push ax
0057 mov cx, ax
0059 mov al, byte ptr es:[bx + 3]
005d cwde 
005e imul ax, ax, 0x101
0062 push ax
0063 push cx
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GSetAttrib
0069 add sp, 6
006c pop si
006d leave 
006e retf 
```

## Known declaration examples

- `extern void far GSetAttrib(int foreColor, int backColor, int pattern);` — src/recovered/wf_GMixedFillBox-e22515d7ab.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPic-08fc158e1c.c
- `extern unsigned char near displayType;` — src/recovered/wf_GPutPicS-f46da1bb8a.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_gr_JustifyStrInRect', 'offset': 45824, 'source': None, 'size': 234}
- {'symbol': '_win_SetColorNum', 'offset': 46058, 'source': None, 'size': 87}
- {'symbol': '_win_SetColorFromObjNum', 'offset': 46258, 'source': None, 'size': 152}
- {'symbol': '_win_RectFill', 'offset': 46410, 'source': None, 'size': 264}
