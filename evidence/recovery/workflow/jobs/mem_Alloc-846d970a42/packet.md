# Recovery task _mem_Alloc

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 80 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov ax, word ptr [bp + 0xa]
0009 or ax, ax
000b jl 0x54f0
000d jo 0x54f0
000f dec ax
0010 dec ax
0011 jle 0x54f6
0013 dec ax
0014 je 0x54fc
0016 mov di, word ptr [bp - 2]
0019 jmp 0x54ff
001b nop 
001c mov di, 0x42
001f jmp 0x54ff
0021 nop 
0022 mov di, 0x142
0025 push di
0026 push word ptr [bp + 8]
0029 push word ptr [bp + 6]
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
0031 mov si, ax
0033 or si, si
0035 jne 0x5526
0037 push -1
0039 push -1
003b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 60, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
0040 push di
0041 push word ptr [bp + 8]
0044 push word ptr [bp + 6]
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 15}}]
004c pop si
004d pop di
004e leave 
004f retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_mem_malloc', 'offset': 21692, 'source': 'src/recovered/mem_malloc.c', 'size': 13}
- {'symbol': '_mem_free', 'offset': 21706, 'source': 'src/recovered/mem_free_wrapper.c', 'size': 16}
- {'symbol': '_mem_Realloc', 'offset': 21802, 'source': None, 'size': 86}
- {'symbol': '_mem_Free', 'offset': 21888, 'source': 'src/recovered/mem_Free.c', 'size': 13}
