# Recovery task _mem_SetType

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 78 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov ax, word ptr [bp + 8]
0007 or ax, ax
0009 jl 0x5621
000b jo 0x5621
000d dec ax
000e dec ax
000f jle 0x55ee
0011 dec ax
0012 je 0x5606
0014 pop si
0015 leave 
0016 retf 
0017 nop 
0018 mov si, word ptr [bp + 6]
001b push si
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 22}}]
0021 test ah, 1
0024 je 0x5621
0026 push si
0027 push 0
0029 push 0
002b push 0x80
002e jmp 0x561c
0030 mov si, word ptr [bp + 6]
0033 push si
0034 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 53, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 22}}]
0039 test ah, 1
003c jne 0x5621
003e push si
003f push 0
0041 push 0
0043 push 0x180
0046 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 16}}]
004b pop si
004c leave 
004d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_mem_Size', 'offset': 21930, 'source': None, 'size': 23}
- {'symbol': '_mem_MakeDiscardable', 'offset': 21954, 'source': 'src/recovered/mem_MakeDiscardable.c', 'size': 20}
- {'symbol': '_mem_Age', 'offset': 22052, 'source': 'src/recovered/mem_Age.c', 'size': 8}
- {'symbol': '_mem_Freshen', 'offset': 22060, 'source': 'src/recovered/mem_Freshen.c', 'size': 13}
