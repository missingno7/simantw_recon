# Recovery task _DialogAbort

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 49 bytes.

```asm
0000 mov bx, word ptr [0x150a]
0004 shl bx, 1
0006 push word ptr [bx - 0x350c]
000a mov ax, word ptr [0x150a]
000d shl ax, 2
0010 add ax, 0xcad4
0013 push ds
0014 push ax
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitedEnough
001a add sp, 6
001d or ax, ax
001f je 0x9c8c
0021 mov ax, 1
0024 retf 
0025 nop 
0026 push 0x1b
0028 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 41, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
002d and ax, 0x8000
0030 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DialogWait', 'offset': 39904, 'source': None, 'size': 30}
- {'symbol': '_DialogWaitInit', 'offset': 39934, 'source': None, 'size': 104}
- {'symbol': '_DialogAbortOrCont', 'offset': 40088, 'source': None, 'size': 59}
- {'symbol': '_DialogDone', 'offset': 40148, 'source': 'src/recovered/DialogDone.c', 'size': 18}
