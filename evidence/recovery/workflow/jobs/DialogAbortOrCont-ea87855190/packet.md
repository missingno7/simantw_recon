# Recovery task _DialogAbortOrCont

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 59 bytes.

```asm
0000 push si
0001 mov bx, word ptr [0x150a]
0005 shl bx, 1
0007 push word ptr [bx - 0x350c]
000b mov ax, word ptr [0x150a]
000e shl ax, 2
0011 add ax, 0xcad4
0014 push ds
0015 push ax
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WaitedEnough
001b add sp, 6
001e or ax, ax
0020 je 0x9cc2
0022 mov si, 1
0025 mov ax, si
0027 pop si
0028 retf 
0029 nop 
002a push 0x20
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 249}}]
0031 mov si, ax
0033 and si, 0x8000
0037 mov ax, si
0039 pop si
003a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DialogWaitInit', 'offset': 39934, 'source': None, 'size': 104}
- {'symbol': '_DialogAbort', 'offset': 40038, 'source': None, 'size': 49}
- {'symbol': '_DialogDone', 'offset': 40148, 'source': 'src/recovered/DialogDone.c', 'size': 18}
- {'symbol': '_DialogAbortAll', 'offset': 40166, 'source': None, 'size': 30}
