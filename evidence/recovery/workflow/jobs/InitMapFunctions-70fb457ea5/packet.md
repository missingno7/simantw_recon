# Recovery task _InitMapFunctions

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 133 bytes.

```asm
0000 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _RallocMemorySoft
0005 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 8, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _RallocMemoryFree
000a push ds
000b push 0x19ac
000e push 1
0010 push 0
0012 push 0x2000
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
001a add sp, 0xa
001d mov es, word ptr [0xc1e0]
0021 mov word ptr es:[0x72ca], ax
0025 mov ax, 4
0028 mov es, word ptr [0xc1e2]
002c mov word ptr es:[0x8096], ax
0030 mov es, word ptr [0xc1e4]
0034 mov word ptr es:[0x807c], ax
0038 test byte ptr [0xcc7e], 1 ; _displayType
003d jne 0xc1fc
003f mov ax, 0x4674
0042 mov <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}]
0045 mov es, word ptr [0xc1e6]
0049 mov word ptr es:[0x806a], ax
004d mov word ptr es:[0x806c], dx
0052 mov es, word ptr [0xc1e8]
0056 mov word ptr es:[0x8092], ax
005a mov word ptr es:[0x8094], dx
005f retf 
0060 mov es, word ptr [0xc1e6]
0064 mov word ptr es:[0x806a], 0x442c
006b mov <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}]
0072 mov es, word ptr [0xc1e8]
0076 mov word ptr es:[0x8092], 0x44b9
007d mov <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}]
0084 retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_YardArea', 'offset': 49306, 'source': None, 'size': 255}
- {'symbol': '_DeinitMapFunctions', 'offset': 49562, 'source': 'src/recovered/DeinitMapFunctions.c', 'size': 1}
- {'symbol': '_ProcMapEvent', 'offset': 49698, 'source': None, 'size': None}
- {'symbol': '_ProcMapRibbonEvent', 'offset': 50132, 'source': None, 'size': None}
