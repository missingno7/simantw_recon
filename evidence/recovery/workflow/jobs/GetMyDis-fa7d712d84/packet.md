# Recovery task _GetMyDis

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 421 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov ax, word ptr [bp + 6]
0007 cmp word ptr [bp + 0xc], ax
000a jne 0x86a6
000c push word ptr [bp + 0x10]
000f push word ptr [bp + 0xe]
0012 push word ptr [bp + 0xa]
0015 push word ptr [bp + 8]
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
001d add sp, 8
0020 pop si
0021 leave 
0022 retf 
0023 nop 
0024 cmp ax, 1
0027 jne 0x8726
0029 cmp word ptr [bp + 0xc], ax
002c jle 0x8726
002e cmp word ptr [bp + 0xc], 2
0032 jne 0x86fa
0034 push word ptr [bp + 0x10]
0037 push word ptr [bp + 0xe]
003a mov es, word ptr [0xc3ee]
003e push word ptr es:[0x8354]
0043 push word ptr es:[0x8352]
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
004d add sp, 8
0050 mov es, word ptr [0xc3f0]
0054 push word ptr es:[0x835c]
0059 push word ptr es:[0x835a]
005e push word ptr [bp + 0xa]
0061 push word ptr [bp + 8]
0064 mov si, ax
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
006b add sp, 8
006e mov cx, ax
0070 mov ax, si
0072 add ax, cx
0074 pop si
0075 leave 
0076 retf 
0077 nop 
0078 push word ptr [bp + 0x10]
007b push word ptr [bp + 0xe]
007e mov es, word ptr [0xc3ee]
0082 push word ptr es:[0x8354]
0087 push word ptr es:[0x8352]
008c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
0091 add sp, 8
0094 mov es, word ptr [0xc3f2]
0098 push word ptr es:[0x8360]
009d push word ptr es:[0x835e]
00a2 jmp 0x86e0
00a4 cmp word ptr [bp + 0xc], 1
00a8 jne 0x878c
00aa cmp ax, 2
00ad jne 0x875e
00af push word ptr [bp + 0x10]
00b2 push word ptr [bp + 0xe]
00b5 mov es, word ptr [0xc3f0]
00b9 push word ptr es:[0x835c]
00be push word ptr es:[0x835a]
00c3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 198, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
00c8 add sp, 8
00cb mov es, word ptr [0xc3ee]
00cf push word ptr es:[0x8354]
00d4 push word ptr es:[0x8352]
00d9 jmp 0x86e0
00db nop 
00dc push word ptr [bp + 0x10]
00df push word ptr [bp + 0xe]
00e2 mov es, word ptr [0xc3f2]
00e6 push word ptr es:[0x8360]
00eb push word ptr es:[0x835e]
00f0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 243, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
00f5 add sp, 8
00f8 mov es, word ptr [0xc3f4]
00fc push word ptr es:[0x8358]
0101 push word ptr es:[0x8356]
0106 jmp 0x86e0
0109 nop 
010a cmp ax, 2
010d jne 0x87dc
010f push word ptr [bp + 0x10]
0112 push word ptr [bp + 0xe]
0115 mov es, word ptr [0xc3f4]
0119 push word ptr es:[0x8358]
011e push word ptr es:[0x8356]
0123 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 294, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
0128 add sp, 8
012b mov es, word ptr [0xc3f2]
012f push word ptr es:[0x8360]
0134 push word ptr es:[0x835e]
0139 mov es, word ptr [0xc3f0]
013d push word ptr es:[0x835c]
0142 push word ptr es:[0x835a]
0147 mov si, ax
0149 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 332, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
014e add sp, 8
0151 mov cx, ax
0153 mov ax, si
0155 add ax, cx
0157 jmp 0x874d
015a push word ptr [bp + 0x10]
015d push word ptr [bp + 0xe]
0160 mov es, word ptr [0xc3ee]
0164 push word ptr es:[0x8354]
0169 push word ptr es:[0x8352]
016e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 369, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
0173 add sp, 8
0176 mov es, word ptr [0xc3f0]
017a push word ptr es:[0x835c]
017f push word ptr es:[0x835a]
0184 mov es, word ptr [0xc3f2]
0188 push word ptr es:[0x8360]
018d push word ptr es:[0x835e]
0192 mov si, ax
0194 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 407, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
0199 add sp, 8
019c mov cx, ax
019e mov ax, si
01a0 add ax, cx
01a2 jmp 0x877a
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EnterNest', 'offset': 33800, 'source': 'src/recovered/wf_EnterNest-606488b329.c', 'size': 155}
- {'symbol': '_ExitNest', 'offset': 33956, 'source': None, 'size': 477}
- {'symbol': '_GetMyBestDirs', 'offset': 34856, 'source': None, 'size': 256}
- {'symbol': '_GetMyRandDirs', 'offset': 35112, 'source': None, 'size': 536}
