# Recovery task _ButtonHeld

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 441 bytes.

```asm
0000 push si
0001 mov es, word ptr [0xc6bc]
0005 cmp word ptr es:[0x7236], 0
000b je 0x4a90
000d nop 
000e push cs
000f call 0x18ac ; _TickCount
0012 mov es, word ptr [0xc6bc]
0016 cmp ax, word ptr es:[0x7230]
001b jne 0x4a75
001d cmp dx, word ptr es:[0x7232]
0022 jne 0x4a75
0024 jmp 0x4c02
0027 dec word ptr es:[0x7236]
002c nop 
002d push cs
002e call 0x18ac ; _TickCount
0031 mov es, word ptr [0xc6bc]
0035 mov word ptr es:[0x7230], ax
0039 mov word ptr es:[0x7232], dx
003e jmp 0x4c02
0041 nop 
0042 mov <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0045 mov es, ax
0047 cmp word ptr es:[0x7234], 0
004d je 0x4aa0
004f jmp 0x4b4c
0052 xor si, si
0054 push si
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 186}}]
005a or ax, ax
005c je 0x4af2
005e push 2
0060 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0065 test ah, 0x80
0068 jne 0x4ad0
006a push 0x2d
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0071 test ah, 0x80
0074 jne 0x4ad0
0076 push 0x20
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
007d test ah, 0x80
0080 je 0x4ad3
0082 mov si, 1
0085 push 1
0087 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 136, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
008c test ah, 0x80
008f jne 0x4aeb
0091 push 0x2e
0093 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 148, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0098 test ah, 0x80
009b je 0x4aee
009d or si, 2
00a0 push 1
00a2 jmp 0x4b36
00a4 push 1
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
00ab test ah, 0x80
00ae jne 0x4b16
00b0 push 0x2d
00b2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
00b7 test ah, 0x80
00ba jne 0x4b16
00bc push 0x20
00be lcall <resolved loader operand; see bindings> ; [{'operand_offset': 191, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
00c3 test ah, 0x80
00c6 je 0x4b19
00c8 mov si, 1
00cb push 2
00cd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 206, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
00d2 test ah, 0x80
00d5 jne 0x4b31
00d7 push 0x2e
00d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
00de test ah, 0x80
00e1 je 0x4b34
00e3 or si, 2
00e6 push 0
00e8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 186}}]
00ed mov <resolved loader operand; see bindings> ; [{'operand_offset': 238, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00f0 mov es, ax
00f2 or si, si
00f4 jne 0x4b4c
00f6 mov word ptr es:[0x7234], si
00fb jmp 0x4b53
00fd nop 
00fe mov word ptr es:[0x7234], 1
0105 cmp word ptr es:[0x7234], 0
010b jne 0x4b5e
010d jmp 0x4c02
0110 xor si, si
0112 push si
0113 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 276, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 186}}]
0118 or ax, ax
011a je 0x4bb0
011c push 2
011e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0123 test ah, 0x80
0126 jne 0x4b8e
0128 push 0x2d
012a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 299, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
012f test ah, 0x80
0132 jne 0x4b8e
0134 push 0x20
0136 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
013b test ah, 0x80
013e je 0x4b91
0140 mov si, 1
0143 push 1
0145 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 326, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
014a test ah, 0x80
014d jne 0x4ba9
014f push 0x2e
0151 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 338, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0156 test ah, 0x80
0159 je 0x4bac
015b or si, 2
015e push 1
0160 jmp 0x4bf4
0162 push 1
0164 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 357, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0169 test ah, 0x80
016c jne 0x4bd4
016e push 0x2d
0170 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 369, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0175 test ah, 0x80
0178 jne 0x4bd4
017a push 0x20
017c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 381, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0181 test ah, 0x80
0184 je 0x4bd7
0186 mov si, 1
0189 push 2
018b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 396, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0190 test ah, 0x80
0193 jne 0x4bef
0195 push 0x2e
0197 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 408, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
019c test ah, 0x80
019f je 0x4bf2
01a1 or si, 2
01a4 push 0
01a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 423, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 186}}]
01ab or si, si
01ad jne 0x4c02
01af xor ax, ax
01b1 pop si
01b2 retf 
01b3 nop 
01b4 mov ax, 1
01b7 pop si
01b8 retf 
```

## Known declaration examples

- `extern unsigned long far TickCount(void);` — src/recovered/ButtonHeldInit.c
- `extern unsigned long TickCount(void);` — src/recovered/MacTickCount.c
- `extern unsigned long far TickCount(void);` — src/recovered/SeedSRand.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern int far match_position[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int far match_position[];` — src/recovered/wf_CompactListR-17480d0ee2.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetMousePos', 'offset': 18972, 'source': 'src/recovered/GetMousePos.c', 'size': 16}
- {'symbol': '_ButtonHeldInit', 'offset': 18988, 'source': 'src/recovered/ButtonHeldInit.c', 'size': 33}
- {'symbol': '_ButtonHeldEnd', 'offset': 19464, 'source': 'src/recovered/ButtonHeldEnd.c', 'size': 6}
- {'symbol': '_ConvColor', 'offset': 19470, 'source': 'src/recovered/ConvColor.c', 'size': 39}
