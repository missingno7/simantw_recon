# Recovery task _UpdateUserButtons

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 303 bytes.

```asm
0000 push di
0001 push si
0002 cmp word ptr [0xbcea], 0
0007 jne 0x24d
0009 cmp word ptr [0xbcec], 0
000e jne 0x24d
0010 jmp 0x366
0013 xor di, di
0015 mov si, di
0017 mov ax, word ptr [di + 0x12]
001b sub ax, 5
001e cmp ax, 8
0021 ja 0x2d6
0023 shl ax, 1
0025 xchg bx, ax
0026 jmp word ptr cs:[bx + 0x266]
002b nop 
002c dw offset 0x278
002e dw offset 0x2d6
0030 dw offset 0x284
0032 dw offset 0x2d6
0034 dw offset 0x290
0036 dw offset 0x29c
0038 dw offset 0x2a8
003a dw offset 0x2b4
003c dw offset 0x2c0
003e mov es, word ptr [0xbe6e]
0042 push word ptr es:[0x9c28]
0047 jmp 0x2c9
0049 nop 
004a mov es, word ptr [0xbe70]
004e push word ptr es:[0x85f4]
0053 jmp 0x2c9
0055 nop 
0056 mov es, word ptr [0xbe70]
005a push word ptr es:[0x85f6]
005f jmp 0x2c9
0061 nop 
0062 mov es, word ptr [0xbe70]
0066 push word ptr es:[0x85fc]
006b jmp 0x2c9
006d nop 
006e mov es, word ptr [0xbe70]
0072 push word ptr es:[0x85f2]
0077 jmp 0x2c9
0079 nop 
007a mov es, word ptr [0xbe70]
007e push word ptr es:[0x85f8]
0083 jmp 0x2c9
0085 nop 
0086 mov es, word ptr [0xbe70]
008a push word ptr es:[0x85fa]
008f lea ax, [si + 0x2210]
0093 push ax
0094 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 151, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0099 add sp, 4
009c mov ax, word ptr [di + 0x22]
00a0 sub ax, 5
00a3 cmp ax, 8
00a6 ja 0x35a
00a8 shl ax, 1
00aa xchg bx, ax
00ab jmp word ptr cs:[bx + 0x2ea]
00b0 dw offset 0x2fc
00b2 dw offset 0x35a
00b4 dw offset 0x308
00b6 dw offset 0x35a
00b8 dw offset 0x314
00ba dw offset 0x320
00bc dw offset 0x32c
00be dw offset 0x338
00c0 dw offset 0x344
00c2 mov es, word ptr [0xbe6e]
00c6 push word ptr es:[0x9c28]
00cb jmp 0x34d
00cd nop 
00ce mov es, word ptr [0xbe70]
00d2 push word ptr es:[0x85f4]
00d7 jmp 0x34d
00d9 nop 
00da mov es, word ptr [0xbe70]
00de push word ptr es:[0x85f6]
00e3 jmp 0x34d
00e5 nop 
00e6 mov es, word ptr [0xbe70]
00ea push word ptr es:[0x85fc]
00ef jmp 0x34d
00f1 nop 
00f2 mov es, word ptr [0xbe70]
00f6 push word ptr es:[0x85f2]
00fb jmp 0x34d
00fd nop 
00fe mov es, word ptr [0xbe70]
0102 push word ptr es:[0x85f8]
0107 jmp 0x34d
0109 nop 
010a mov es, word ptr [0xbe70]
010e push word ptr es:[0x85fa]
0113 lea ax, [si + 0x230b]
0117 push ax
0118 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
011d add sp, 4
0120 inc si
0121 add di, 2
0124 cmp di, 0x10
0127 jge 0x366
0129 jmp 0x251
012c pop si
012d pop di
012e retf 
```

## Known declaration examples

- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_ClearBookmarks-ffba50efd3.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_DoUserButtonUpdate-cf874c4e35.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DecodeString', 'offset': 266, 'source': None, 'size': 172}
- {'symbol': '_DoUserButtonUpdate', 'offset': 438, 'source': 'src/recovered/wf_DoUserButtonUpdate-cf874c4e35.c', 'size': 131}
- {'symbol': '_SetUserButton', 'offset': 874, 'source': None, 'size': 345}
- {'symbol': '_DoUserButton', 'offset': 1220, 'source': None, 'size': 994}
