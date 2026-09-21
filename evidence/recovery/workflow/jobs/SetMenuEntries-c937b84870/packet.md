# Recovery task _SetMenuEntries

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 158 bytes.

```asm
0000 push di
0001 push si
0002 mov si, 0x43
0005 mov ax, si
0007 mov es, word ptr [0xbeca]
000b sub ax, word ptr es:[0x8614]
0010 cmp ax, 0x43
0013 jne 0x4c3e
0015 mov ax, 0x10
0018 jmp 0x4c41
001a mov ax, 0x20
001d push ax
001e push si
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
0024 add sp, 4
0027 inc si
0028 cmp si, 0x46
002b jle 0x4c29
002d mov es, word ptr [0xbecc]
0031 cmp word ptr es:[0x9c28], 0
0037 je 0x4c62
0039 mov ax, 0x900
003c jmp 0x4c65
003e mov ax, 0x911
0041 push ds
0042 push ax
0043 push 0x41
0045 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuOptionText
004a add sp, 6
004d mov di, 0x31
0050 mov si, 0x85f2
0053 mov es, word ptr [0xbece]
0057 cmp word ptr es:[si], 1
005b sbb ax, ax
005d and ax, 0x10
0060 add ax, 0x10
0063 push ax
0064 push di
0065 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 104, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _SetMenuItemState
006a add sp, 4
006d add si, 2
0070 inc di
0071 cmp di, 0x36
0074 jle 0x4c77
0076 nop 
0077 push cs
0078 call 0x23a ; _UpdateUserButtons
007b mov es, word ptr [0xbece]
007f mov ax, word ptr es:[0x85f4]
0083 mov es, word ptr [0xbed0]
0087 mov word ptr es:[0xaf6], ax
008b mov es, word ptr [0xbece]
008f mov ax, word ptr es:[0x85f6]
0093 mov es, word ptr [0xbed2]
0097 mov word ptr es:[0xaf8], ax
009b pop si
009c pop di
009d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitPalette', 'offset': 18750, 'source': None, 'size': 718}
- {'symbol': '_ClosePalette', 'offset': 19468, 'source': 'src/recovered/ClosePalette.c', 'size': 23}
- {'symbol': '_PauseGame', 'offset': 19650, 'source': None, 'size': 369}
- {'symbol': '_SetPause', 'offset': 20020, 'source': None, 'size': 369}
