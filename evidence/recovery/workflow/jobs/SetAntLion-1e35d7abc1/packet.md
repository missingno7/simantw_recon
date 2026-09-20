# Recovery task _SetAntLion

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 57 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 mov es, word ptr [0xc58e]
000b mov al, byte ptr es:[si + 0x7d4e]
0010 sub ah, ah
0012 add ax, 0x38
0015 push ax
0016 mov es, word ptr [0xc588]
001a mov al, byte ptr es:[si - 0x7f44]
001f sub ah, ah
0021 push ax
0022 mov es, word ptr [0xc586]
0026 mov al, byte ptr es:[si - 0x7f64]
002b push ax
002c push 1
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
0033 add sp, 8
0036 pop si
0037 leave 
0038 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AddAntLion', 'offset': 17216, 'source': None, 'size': 186}
- {'symbol': '_DoAntLions', 'offset': 17402, 'source': None, 'size': 1758}
- {'symbol': '_FindInLionList', 'offset': 19218, 'source': None, 'size': 69}
- {'symbol': '_KillAntLion', 'offset': 19288, 'source': None, 'size': 160}
