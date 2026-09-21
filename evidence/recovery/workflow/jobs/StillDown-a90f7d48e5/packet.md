# Recovery task _StillDown

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 161 bytes.

```asm
0000 push si
0001 xor si, si
0003 push si
0004 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 186}}]
0009 or ax, ax
000b je 0x476a
000d push 2
000f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0014 test ah, 0x80
0017 jne 0x4747
0019 push 0x2d
001b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0020 test ah, 0x80
0023 jne 0x4747
0025 push 0x20
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
002c test ah, 0x80
002f je 0x474a
0031 mov si, 1
0034 push 1
0036 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 55, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
003b test ah, 0x80
003e jne 0x4762
0040 push 0x2e
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0047 test ah, 0x80
004a je 0x4765
004c or si, 2
004f push 1
0051 jmp 0x47ae
0053 nop 
0054 push 1
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
005b test ah, 0x80
005e jne 0x478e
0060 push 0x2d
0062 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 99, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0067 test ah, 0x80
006a jne 0x478e
006c push 0x20
006e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0073 test ah, 0x80
0076 je 0x4791
0078 mov si, 1
007b push 2
007d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 126, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0082 test ah, 0x80
0085 jne 0x47a9
0087 push 0x2e
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
008e test ah, 0x80
0091 je 0x47ac
0093 or si, 2
0096 push 0
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 186}}]
009d mov ax, si
009f pop si
00a0 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ms_Delay', 'offset': 17966, 'source': None, 'size': 46}
- {'symbol': '_gr_BitMapSize', 'offset': 18012, 'source': None, 'size': 185}
- {'symbol': '_WaitedEnough', 'offset': 18360, 'source': 'src/recovered/wf_WaitedEnough-b76919c4b5.c', 'size': 94}
- {'symbol': '_gr_CenterStrInRectClear', 'offset': 18454, 'source': None, 'size': 217}
