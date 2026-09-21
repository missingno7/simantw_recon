# Recovery task _font_DumpFont

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 123 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 les si, ptr [bp + 6]
0007 mov ax, es
0009 or ax, si
000b je 0xacbf
000d mov ax, word ptr es:[si + 0x1c]
0011 or ax, word ptr es:[si + 0x1a]
0015 je 0xac71
0017 push word ptr es:[si + 0x1c]
001b push word ptr es:[si + 0x1a]
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
0024 add sp, 4
0027 mov es, word ptr [bp + 8]
002a mov ax, word ptr es:[si + 0x20]
002e or ax, word ptr es:[si + 0x1e]
0032 je 0xac8e
0034 push word ptr es:[si + 0x20]
0038 push word ptr es:[si + 0x1e]
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
0041 add sp, 4
0044 mov es, word ptr [bp + 8]
0047 mov ax, word ptr es:[si + 0x24]
004b or ax, word ptr es:[si + 0x22]
004f je 0xacab
0051 push word ptr es:[si + 0x24]
0055 push word ptr es:[si + 0x22]
0059 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
005e add sp, 4
0061 mov ax, word ptr [bp + 8]
0064 or ax, si
0066 je 0xacbf
0068 mov ax, word ptr [bp + 8]
006b push ax
006c push si
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
0072 add sp, 4
0075 xor ax, ax
0077 cdq 
0078 pop si
0079 leave 
007a retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DeleteNode', 'offset': 43406, 'source': None, 'size': 189}
- {'symbol': '_font_ReadFont', 'offset': 43596, 'source': None, 'size': 509}
- {'symbol': '__font_StringWidth', 'offset': 44230, 'source': None, 'size': 150}
- {'symbol': '__font_CharWidth', 'offset': 44380, 'source': None, 'size': 99}
