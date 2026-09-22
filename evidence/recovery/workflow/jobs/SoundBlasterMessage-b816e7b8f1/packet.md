# Recovery task _SoundBlasterMessage

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 296 bytes.

```asm
0000 enter 4, 0
0004 mov ax, word ptr [bp + 6]
0007 cmp ax, 0x28
000a jne 0x803b
000c jmp 0x80e8
000f jbe 0x8040
0011 jmp 0x8152
0014 dec al
0016 je 0x804a
0018 sub al, 0x13
001a je 0x8074
001c leave 
001d retf 
001e mov es, word ptr [0xbf78]
0022 push word ptr es:[0x8d08]
0027 push ds
0028 push 0xc7a
002b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0030 mov word ptr [bp - 4], ax
0033 mov word ptr [bp - 2], dx
0036 or dx, ax
0038 jne 0x8069
003a jmp 0x8152
003d push word ptr [bp + 0xa]
0040 push word ptr [bp + 8]
0043 lcall [bp - 4]
0046 leave 
0047 retf 
0048 mov ax, word ptr [bp + 0xa]
004b sub ax, 5
004e je 0x807f
0050 jmp 0x8152
0053 cmp word ptr [bp + 8], 0
0057 je 0x8088
0059 jmp 0x8152
005c mov es, word ptr [0xbf78]
0060 push word ptr es:[0x8d08]
0065 push ds
0066 push 0xc5e
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
006e mov word ptr [bp - 4], ax
0071 mov word ptr [bp - 2], dx
0074 or dx, ax
0076 je 0x80a7
0078 lcall [bp - 4]
007b mov es, word ptr [0xbf78]
007f push word ptr es:[0x8d26]
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
0089 mov es, word ptr [0xbf78]
008d push word ptr es:[0x8d22]
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
0097 mov es, word ptr [0xbf78]
009b push word ptr es:[0x8d22]
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
00a5 mov es, word ptr [0xbf78]
00a9 mov word ptr es:[0x8d22], 0
00b0 sub ax, ax
00b2 mov word ptr es:[0x8d26], ax
00b6 mov word ptr es:[0x8d24], ax
00ba leave 
00bb retf 
00bc mov ax, word ptr [bp + 0xa]
00bf dec ax
00c0 jne 0x8152
00c2 cmp word ptr [bp + 8], 0
00c6 jne 0x8152
00c8 mov es, word ptr [0xbf78]
00cc push word ptr es:[0x8d08]
00d1 push ds
00d2 push 0xc4f
00d5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 214, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00da mov word ptr [bp - 4], ax
00dd mov word ptr [bp - 2], dx
00e0 or dx, ax
00e2 je 0x8113
00e4 lcall [bp - 4]
00e7 mov es, word ptr [0xbf78]
00eb push word ptr es:[0x8d20]
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 241, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
00f5 mov es, word ptr [0xbf78]
00f9 push word ptr es:[0x8d1c]
00fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 255, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
0103 mov es, word ptr [0xbf78]
0107 push word ptr es:[0x8d1c]
010c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 269, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
0111 mov es, word ptr [0xbf78]
0115 mov word ptr es:[0x8d1c], 0
011c sub ax, ax
011e mov word ptr es:[0x8d20], ax
0122 mov word ptr es:[0x8d1e], ax
0126 leave 
0127 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_vocSoundBlasterClose', 'offset': 32590, 'source': None, 'size': 100}
- {'symbol': '_vocMciClose', 'offset': 32690, 'source': None, 'size': 122}
- {'symbol': '_MciMessage', 'offset': 33108, 'source': None, 'size': 295}
- {'symbol': '_MusicInit', 'offset': 33404, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_11_scaffold-950e5ffcca.c', 'size': 13}
