# Recovery task _MciMessage

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 295 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 cmp word ptr [0xaf2], 0
000b jne 0x8164
000d jmp 0x8277
0010 cmp word ptr [0xaf0], 0
0015 jne 0x816e
0017 jmp 0x8277
001a mov es, word ptr [0xbf78]
001e push word ptr es:[0x8d08]
0023 push ds
0024 push 0xc86
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
002c mov word ptr [bp - 8], ax
002f mov word ptr [bp - 6], dx
0032 mov es, word ptr [0xbf78]
0036 push word ptr es:[0x8d08]
003b push ds
003c push 0xc93
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0044 mov word ptr [bp - 4], ax
0047 mov word ptr [bp - 2], dx
004a mov ax, word ptr [bp - 6]
004d or ax, word ptr [bp - 8]
0050 je 0x81b2
0052 mov es, word ptr [0xbf78]
0056 push word ptr es:[0x8d14]
005b lcall [bp - 8]
005e les bx, ptr [bp + 8]
0061 mov ax, word ptr es:[bx + 0x10]
0065 mov dx, word ptr es:[bx + 0x12]
0069 and al, 0xe0
006b or dx, ax
006d jne 0x8204
006f mov ax, word ptr [bp - 2]
0072 or ax, word ptr [bp - 4]
0075 je 0x81dd
0077 mov es, word ptr [0xbf78]
007b push word ptr es:[0x8d14]
0080 push word ptr [bp + 0xa]
0083 push bx
0084 push 0x20
0086 lcall [bp - 4]
0089 les bx, ptr [bp + 8]
008c mov di, word ptr es:[bx + 0xc]
0090 mov si, word ptr es:[bx + 0xe]
0094 cmp word ptr [0xaf2], 0
0099 je 0x8224
009b push si
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
00a1 push si
00a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
00a7 mov word ptr [0xaf2], 0
00ad jmp 0x8224
00af nop 
00b0 xor ax, ax
00b2 mov word ptr [0xaf2], ax
00b5 mov word ptr [0xaf0], ax
00b8 mov di, ax
00ba mov si, ax
00bc cmp si, ax
00be je 0x8224
00c0 push si
00c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 194, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
00c6 push si
00c7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
00cc mov word ptr [0xaf2], si
00d0 cmp word ptr [0xaf0], 0
00d5 je 0x823d
00d7 push di
00d8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 217, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 19}}]
00dd push di
00de lcall <resolved loader operand; see bindings> ; [{'operand_offset': 223, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
00e3 mov word ptr [0xaf0], 0
00e9 mov es, word ptr [0xbf78]
00ed dec word ptr es:[0x8d1a]
00f2 jne 0x8277
00f4 push word ptr es:[0x8d08]
00f9 push ds
00fa push 0xc6d
00fd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 254, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0102 mov word ptr [bp - 4], ax
0105 mov word ptr [bp - 2], dx
0108 or dx, ax
010a je 0x826c
010c mov es, word ptr [0xbf78]
0110 push word ptr es:[0x8d14]
0115 lcall [bp - 4]
0118 mov es, word ptr [0xbf78]
011c mov word ptr es:[0x8d14], 0
0123 pop si
0124 pop di
0125 leave 
0126 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_vocMciClose', 'offset': 32690, 'source': None, 'size': 122}
- {'symbol': '_SoundBlasterMessage', 'offset': 32812, 'source': None, 'size': 296}
- {'symbol': '_MusicInit', 'offset': 33404, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_11_scaffold-950e5ffcca.c', 'size': 13}
- {'symbol': '_SysBeep', 'offset': 33418, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_11_scaffold-950e5ffcca.c', 'size': 8}
