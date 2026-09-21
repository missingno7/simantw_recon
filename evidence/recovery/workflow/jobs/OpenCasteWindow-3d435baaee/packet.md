# Recovery task _OpenCasteWindow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 141 bytes.

```asm
0000 enter 8, 0
0004 push 0x1300
0007 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 10, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Recalc
000c add sp, 2
000f cmp word ptr [0x15b6], 0 ; _modeBitmap
0014 jne 0xbc4d
0016 push 0x120c
0019 lea ax, [bp - 8]
001c push ss
001d push ax
001e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 33, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _gr_BitMapSize
0023 add sp, 6
0026 push ds
0027 push 0x15ba
002a push 1
002c test byte ptr [0xcc7e], 1 ; _displayType
0031 jne 0xbc24
0033 push 4
0035 jmp 0xbc26
0037 nop 
0038 push 1
003a push word ptr [bp - 6]
003d push word ptr [bp - 8]
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _BitmapImageSize
0045 add sp, 6
0048 mov word ptr [bp - 4], ax
004b mov word ptr [bp - 2], dx
004e add ax, 4
0051 adc dx, 0
0054 push dx
0055 push ax
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
005b add sp, 0xa
005e mov word ptr [0x15b8], ax ; _casteBitmap
0061 nop 
0062 push cs
0063 call 0xb3bc ; _win_CasteControlChanged
0066 push 0x1302
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeObjInvisible
006e add sp, 2
0071 push 0x1300
0074 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 119, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_Open
0079 add sp, 2
007c nop 
007d push cs
007e call 0xb7a4 ; _UpdateCasteWindow
0081 push 4
0083 push 0x1300
0086 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 137, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_MakeGroupInvisible
008b leave 
008c retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far win_Open(int window);` — src/recovered/MakeEditOpen.c
- `extern void far win_Open(int flags);` — src/recovered/OpenEditWindow.c
- `extern void far win_Open(int flags);` — src/recovered/OpenHistoryWindow.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UpdateCasteWindow', 'offset': 47012, 'source': None, 'size': 547}
- {'symbol': '_UpdateModeWindow', 'offset': 47560, 'source': None, 'size': 547}
- {'symbol': '_OpenModeWindow', 'offset': 48250, 'source': None, 'size': 141}
- {'symbol': '_ProcCasteEvent', 'offset': 48392, 'source': None, 'size': None}
