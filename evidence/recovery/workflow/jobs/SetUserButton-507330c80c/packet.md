# Recovery task _SetUserButton

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 345 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 mov si, word ptr [bp + 8]
0008 lea ax, [si + 0x3857]
000c push ax
000d lea ax, [si + 0x3889]
0011 push ax
0012 push word ptr [bp + 6]
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetButtonBitmaps
001a add sp, 6
001d push word ptr [bp + 6]
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_LockWin
0025 add sp, 2
0028 push word ptr [bp + 6]
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_ObjAddr
0030 add sp, 2
0033 mov word ptr [bp - 4], ax
0036 mov word ptr [bp - 2], dx
0039 mov ax, si
003b cmp ax, 0xf
003e jbe 0x3ad
0040 jmp 0x4b5
0043 shl ax, 1
0045 xchg bx, ax
0046 jmp word ptr cs:[bx + 0x3b6]
004b nop 
004c dw offset 0x3d6
004e dw offset 0x3d6
0050 dw offset 0x3d6
0052 dw offset 0x3d6
0054 dw offset 0x3e8
0056 dw offset 0x402
0058 dw offset 0x3d6
005a dw offset 0x41c
005c dw offset 0x3d6
005e dw offset 0x434
0060 dw offset 0x44c
0062 dw offset 0x464
0064 dw offset 0x47c
0066 dw offset 0x494
0068 dw offset 0x3d6
006a dw offset 0x3d6
006c les bx, ptr [bp - 4]
006f and byte ptr es:[bx + 0x24], 0xf7
0074 or byte ptr es:[bx + 0x25], 8
0079 push 0
007b jmp 0x4aa
007e les bx, ptr [bp - 4]
0081 or byte ptr es:[bx + 0x24], 8
0086 and byte ptr es:[bx + 0x25], 0xf7
008b mov es, word ptr [0xbe72]
008f push word ptr es:[0x1998]
0094 jmp 0x4aa
0097 nop 
0098 les bx, ptr [bp - 4]
009b or byte ptr es:[bx + 0x24], 8
00a0 and byte ptr es:[bx + 0x25], 0xf7
00a5 mov es, word ptr [0xbe6e]
00a9 push word ptr es:[0x9c28]
00ae jmp 0x4aa
00b1 nop 
00b2 les bx, ptr [bp - 4]
00b5 or byte ptr es:[bx + 0x24], 8
00ba and byte ptr es:[bx + 0x25], 0xf7
00bf mov es, word ptr [0xbe70]
00c3 push word ptr es:[0x85f4]
00c8 jmp 0x4aa
00ca les bx, ptr [bp - 4]
00cd or byte ptr es:[bx + 0x24], 8
00d2 and byte ptr es:[bx + 0x25], 0xf7
00d7 mov es, word ptr [0xbe70]
00db push word ptr es:[0x85f6]
00e0 jmp 0x4aa
00e2 les bx, ptr [bp - 4]
00e5 or byte ptr es:[bx + 0x24], 8
00ea and byte ptr es:[bx + 0x25], 0xf7
00ef mov es, word ptr [0xbe70]
00f3 push word ptr es:[0x85fc]
00f8 jmp 0x4aa
00fa les bx, ptr [bp - 4]
00fd or byte ptr es:[bx + 0x24], 8
0102 and byte ptr es:[bx + 0x25], 0xf7
0107 mov es, word ptr [0xbe70]
010b push word ptr es:[0x85f2]
0110 jmp 0x4aa
0112 les bx, ptr [bp - 4]
0115 or byte ptr es:[bx + 0x24], 8
011a and byte ptr es:[bx + 0x25], 0xf7
011f mov es, word ptr [0xbe70]
0123 push word ptr es:[0x85f8]
0128 jmp 0x4aa
012a les bx, ptr [bp - 4]
012d or byte ptr es:[bx + 0x24], 8
0132 and byte ptr es:[bx + 0x25], 0xf7
0137 mov es, word ptr [0xbe70]
013b push word ptr es:[0x85fa]
0140 push word ptr [bp + 6]
0143 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0148 add sp, 4
014b push word ptr [bp + 6]
014e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 337, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_UnlockWin
0153 add sp, 2
0156 pop si
0157 leave 
0158 retf 
```

## Known declaration examples

- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_LockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinBitmapObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c
- `extern struct WinButtonObject far * far win_ObjAddr(int objectNumber);` — src/recovered/wf_win_SetButtonBitmaps-cdd8450c47.c
- `extern void far * far win_ObjAddr(int objectNumber);` — src/recovered/win_DrawObjectNum.c
- `extern void far win_SetButtonBitmaps(int objectNumber, unsigned int bitmapUp, unsigned int bitmapDown);` — src/recovered/wf_ClearBookmarks-ffba50efd3.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_ClearBookmarks-ffba50efd3.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_DoUserButtonUpdate-cf874c4e35.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_CenterStrAtObj-57d14d8d10.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_ClearObjArea-a3b268354e.c
- `extern void far win_UnlockWin(int objectNumber);` — src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoUserButtonUpdate', 'offset': 438, 'source': 'src/recovered/wf_DoUserButtonUpdate-cf874c4e35.c', 'size': 131}
- {'symbol': '_UpdateUserButtons', 'offset': 570, 'source': 'src/recovered/wf_UpdateUserButtons-609b2b7960.c', 'size': 303}
- {'symbol': '_DoUserButton', 'offset': 1220, 'source': None, 'size': 994}
- {'symbol': '_DoBookMark', 'offset': 2214, 'source': None, 'size': 513}
