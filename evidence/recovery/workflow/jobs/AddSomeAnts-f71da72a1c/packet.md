# Recovery task _AddSomeAnts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 90 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov es, word ptr [0xc0da]
0008 mov si, word ptr es:[0x80f0]
000d cmp si, 0x3e8
0011 jge 0x9d56
0013 mov es, word ptr [0xc0dc]
0017 cmp word ptr es:[0x85e2], 1
001d jne 0x9d3c
001f cmp word ptr [bp + 6], 1
0023 jne 0x9d32
0025 mov ax, 0x3e8
0028 sub ax, si
002a push ax
002b jmp 0x9d44
002d nop 
002e sub si, 0x3e8
0032 neg si
0034 push si
0035 jmp 0x9d4e
0037 nop 
0038 cmp word ptr [bp + 6], 1
003c jne 0x9d4c
003e push 0x20
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddBlackAnts
0045 jmp 0x9d53
0047 nop 
0048 push 0x20
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _AddRedAnts
004f add sp, 2
0052 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FullCount
0057 pop si
0058 leave 
0059 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DialogDone', 'offset': 40148, 'source': 'src/recovered/DialogDone.c', 'size': 18}
- {'symbol': '_DialogAbortAll', 'offset': 40166, 'source': 'src/recovered/wf_DialogAbortAll-1f3ea4f9f2.c', 'size': 30}
- {'symbol': '_KillSomeAnts', 'offset': 40286, 'source': None, 'size': 198}
- {'symbol': '_SubtractFood', 'offset': 40484, 'source': None, 'size': 77}
