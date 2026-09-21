# Recovery task _DoUserButtonUpdate

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 131 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 mov ax, word ptr [bp + 6]
0006 sub ax, 5
0009 cmp ax, 8
000c ja 0x237
000e shl ax, 1
0010 xchg bx, ax
0011 jmp word ptr cs:[bx + 0x1cc]
0016 fiadd word ptr [bx + di]
0018 aaa 
0019 add ch, dl
001b add word ptr [bx], si
001d add dh, dh
001f add word ptr [bp + si], ax
0021 add cl, byte ptr [0x1a02]
0025 add ah, byte ptr [0x8e02]
0029 push es
002a outsb dx, byte ptr [si]
002b mov si, 0xff26
002e sub byte ptr ss:[si + 0x46eb], bl
0033 nop 
0034 mov es, word ptr [0xbe70]
0038 push word ptr es:[0x85f4]
003d jmp 0x22f
003f nop 
0040 mov es, word ptr [0xbe70]
0044 push word ptr es:[0x85f6]
0049 jmp 0x22f
004b nop 
004c mov es, word ptr [0xbe70]
0050 push word ptr es:[0x85fc]
0055 jmp 0x22f
0057 nop 
0058 mov es, word ptr [0xbe70]
005c push word ptr es:[0x85f2]
0061 jmp 0x22f
0063 nop 
0064 mov es, word ptr [0xbe70]
0068 push word ptr es:[0x85f8]
006d jmp 0x22f
006f nop 
0070 mov es, word ptr [0xbe70]
0074 push word ptr es:[0x85fa]
0079 push word ptr [bp + 8]
007c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _win_SetObjSelectedState
0081 leave 
0082 retf 
```

## Known declaration examples

- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_ClearBookmarks-ffba50efd3.c
- `extern void far win_SetObjSelectedState(int object, int selected);` — src/recovered/wf_EditScentMenu-abd185cb06.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CleanUp', 'offset': 80, 'source': None, 'size': 186}
- {'symbol': '_DecodeString', 'offset': 266, 'source': None, 'size': 172}
- {'symbol': '_UpdateUserButtons', 'offset': 570, 'source': None, 'size': 303}
- {'symbol': '_SetUserButton', 'offset': 874, 'source': None, 'size': 345}
