# Recovery task _CopyRootName

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 107 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 push 0x4f
000b push word ptr [bp + 0xc]
000e push word ptr [bp + 0xa]
0011 push word ptr [bp + 8]
0014 push si
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strncpy
001a add sp, 0xa
001d mov es, word ptr [bp + 8]
0020 mov byte ptr es:[si + 0x4f], 0
0025 cmp byte ptr es:[si], 0x2e
0029 jne 0x8e8e
002b mov ds, word ptr [bp + 8]
002e inc si
002f cmp byte ptr [si], 0x2e
0032 je 0x8e86
0034 push ss
0035 pop ds
0036 push 0x2e
0038 push word ptr [bp + 8]
003b push si
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strrchr
0041 add sp, 6
0044 mov di, ax
0046 mov word ptr [bp - 2], dx
0049 or dx, ax
004b je 0x8ebf
004d push 0x5c
004f mov ax, word ptr [bp + 8]
0052 push ax
0053 push si
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _strrchr
0059 add sp, 6
005c cmp ax, di
005e jae 0x8ebf
0060 mov es, word ptr [bp - 2]
0063 mov byte ptr es:[di], 0
0067 pop si
0068 pop di
0069 leave 
006a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FlushDB', 'offset': 36342, 'source': 'src/recovered/FlushDB.c', 'size': 1}
- {'symbol': '_CloseDB', 'offset': 36344, 'source': None, 'size': 95}
- {'symbol': '_GetFreeHandle', 'offset': 36548, 'source': None, 'size': 72}
- {'symbol': '_DosPunt', 'offset': 36620, 'source': None, 'size': 57}
