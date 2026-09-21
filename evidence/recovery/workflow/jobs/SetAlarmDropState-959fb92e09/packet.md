# Recovery task _SetAlarmDropState

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 149 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov cx, word ptr [bp + 6]
0006 or cx, cx
0008 je 0x8514
000a cmp word ptr [0xce80], 1 ; _MePlane
000f jne 0x8506
0011 mov es, word ptr [0xbf0c]
0015 cmp word ptr es:[0x9fe8], 0
001b jne 0x8506
001d mov word ptr [0xac58], 0 ; _ELayerMode
0023 push cx
0024 push 0x10
0026 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
002b mov sp, bp
002d mov es, word ptr [0xbf50]
0031 mov word ptr es:[0x75fa], 1
0038 jmp 0x8530
003a cmp word ptr [bp + 8], 0
003e jne 0x8544
0040 push 0x7e
0042 push 0
0044 push 1
0046 jmp 0x853c
0048 mov es, word ptr [0xbf50]
004c mov word ptr es:[0x75fa], 0
0053 push cx
0054 push 0x10
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
005b add sp, 4
005e mov word ptr [0xac58], 0xffff ; _ELayerMode
0064 cmp word ptr [bp + 8], 0
0068 jne 0x8544
006a push 0x7e
006c push 0
006e push 0xf
0070 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 115, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0075 add sp, 6
0078 mov es, word ptr [0xbf52]
007c push word ptr es:[0x9b6c]
0081 mov es, word ptr [0xbf54]
0085 push word ptr es:[0x7292]
008a push 0
008c push 0
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _InvalEuMap
0093 leave 
0094 retf 
```

## Known declaration examples

- `extern int near ELayerMode;` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_ClearBookmarks-ffba50efd3.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_YellowDialog', 'offset': 33378, 'source': None, 'size': 523}
- {'symbol': '_DoTroph', 'offset': 33902, 'source': None, 'size': 93}
- {'symbol': '_YellowCommandKey', 'offset': 34146, 'source': None, 'size': None}
- {'symbol': '_YellowCommand', 'offset': 34746, 'source': None, 'size': None}
