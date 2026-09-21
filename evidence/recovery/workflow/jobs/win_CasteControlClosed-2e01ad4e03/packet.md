# Recovery task _win_CasteControlClosed

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 149 bytes.

```asm
0000 enter 0x10, 0
0004 push si
0005 mov bx, 0x7c4a
0008 mov es, word ptr [0xc12c]
000c mov word ptr [bp - 0x10], bx
000f mov word ptr [bp - 0xe], es
0012 cmp word ptr es:[bx], 0
0016 je 0xc759
0018 push word ptr es:[bx]
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _hanim_RemoveAnimSet
0020 add sp, 2
0023 les bx, ptr [bp - 0x10]
0026 mov word ptr es:[bx], 0
002b cmp word ptr [0x15b8], 0 ; _casteBitmap
0030 je 0xc7c0
0032 push 0x120c
0035 lea ax, [bp - 0xc]
0038 push ss
0039 push ax
003a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
003f add sp, 6
0042 push word ptr [0x15b8] ; _casteBitmap
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
004b add sp, 2
004e mov si, ax
0050 mov word ptr [bp - 2], dx
0053 mov ax, word ptr [bp - 0xc]
0056 mov es, dx
0058 mov word ptr es:[si], ax
005b mov ax, word ptr [bp - 0xa]
005e mov word ptr es:[si + 2], ax
0062 lea ax, [bp - 6]
0065 push ss
0066 push ax
0067 lea ax, [bp - 8]
006a push ss
006b push ax
006c push 0x120c
006f push word ptr [bp - 0xc]
0072 push word ptr [bp - 0xa]
0075 push 0
0077 push 0
0079 lea ax, [si + 4]
007c push es
007d push ax
007e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _DrawBitMapToBuffer
0083 add sp, 0x16
0086 push word ptr [0x15b8] ; _casteBitmap
008a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 141, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
008f add sp, 2
0092 pop si
0093 leave 
0094 retf 
```

## Known declaration examples

- `extern unsigned int near casteBitmap;` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern void far hanim_RemoveAnimSet(unsigned int setHandle);` — src/recovered/wf_win_YardClosed-13af30aa32.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_ModeControlClosed', 'offset': 50624, 'source': None, 'size': 149}
- {'symbol': '_win_DrawCasteWindow', 'offset': 50774, 'source': None, 'size': 216}
- {'symbol': '_DrawControlLevels', 'offset': 51140, 'source': None, 'size': 538}
- {'symbol': '_cvtLevels2IdealCaste', 'offset': 51678, 'source': None, 'size': 156}
