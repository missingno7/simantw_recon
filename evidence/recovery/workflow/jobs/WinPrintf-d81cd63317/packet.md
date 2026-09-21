# Recovery task _WinPrintf

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 101 bytes.

```asm
0000 enter 0x200, 0
0004 push si
0005 cmp word ptr [0x8f2], 0
000a je 0x631c
000c lea ax, [bp - 0x200]
0010 push ss
0011 push ax
0012 push word ptr [bp + 8]
0015 push word ptr [bp + 6]
0018 lea cx, [bp + 0xa]
001b push ss
001c push cx
001d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 30, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 421}}]
0022 cmp byte ptr [bp - 0x200], 0xa
0027 jne 0x62ee
0029 push ds
002a push 0x8f4
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 46, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 115}}]
0032 lea ax, [bp - 0x200]
0036 push ss
0037 push ax
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 115}}]
003d lea ax, [bp - 0x200]
0041 push ss
0042 push ax
0043 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 90}}]
0048 mov si, ax
004a cmp byte ptr [bp + si - 0x201], 0xa
004f jne 0x6316
0051 push ds
0052 push 0x8f6
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 86, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 115}}]
005a mov ax, 1
005d pop si
005e leave 
005f retf 
0060 xor ax, ax
0062 pop si
0063 leave 
0064 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_font_InitFonts', 'offset': 24940, 'source': None, 'size': 169}
- {'symbol': '_font_PrintStr', 'offset': 25110, 'source': None, 'size': 165}
- {'symbol': '_DebugWinPrintf', 'offset': 25378, 'source': None, 'size': 101}
- {'symbol': '_printf', 'offset': 25480, 'source': 'src/recovered/wf_printf-41e459f08e.c', 'size': 43}
