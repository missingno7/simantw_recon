# Recovery task _mem_Realloc

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 86 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov ax, word ptr [bp + 0xc]
0009 or ax, ax
000b jl 0x5540
000d jo 0x5540
000f dec ax
0010 dec ax
0011 jle 0x5546
0013 dec ax
0014 je 0x554c
0016 mov si, word ptr [bp - 2]
0019 jmp 0x554f
001b nop 
001c mov si, 0x42
001f jmp 0x554f
0021 nop 
0022 mov si, 0x142
0025 push word ptr [bp + 6]
0028 push word ptr [bp + 0xa]
002b push word ptr [bp + 8]
002e push si
002f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 16}}]
0034 mov di, ax
0036 or di, di
0038 jne 0x557c
003a push -1
003c push -1
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 25}}]
0043 push word ptr [bp + 6]
0046 push word ptr [bp + 0xa]
0049 push word ptr [bp + 8]
004c push si
004d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 16}}]
0052 pop si
0053 pop di
0054 leave 
0055 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_mem_free', 'offset': 21706, 'source': 'src/recovered/mem_free_wrapper.c', 'size': 16}
- {'symbol': '_mem_Alloc', 'offset': 21722, 'source': 'src/recovered/wf_mem_Alloc-846d970a42.c', 'size': 80}
- {'symbol': '_mem_Free', 'offset': 21888, 'source': 'src/recovered/mem_Free.c', 'size': 13}
- {'symbol': '_mem_Lock', 'offset': 21902, 'source': 'src/recovered/mem_Lock.c', 'size': 13}
