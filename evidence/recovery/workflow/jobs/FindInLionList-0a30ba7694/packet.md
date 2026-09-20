# Recovery task _FindInLionList

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 69 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 mov es, word ptr [0xc582]
0008 mov bx, word ptr es:[0x8a88]
000d dec bx
000e js 0x4b52
0010 mov cx, word ptr [bp + 8]
0013 mov di, word ptr [bp + 6]
0016 mov <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0019 mov ds, ax
001b mov <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
001e mov es, ax
0020 mov al, byte ptr [bx - 0x7f64]
0024 sub ah, ah
0026 cmp ax, di
0028 jne 0x4b4c
002a mov al, byte ptr es:[bx - 0x7f44]
002f cmp ax, cx
0031 jne 0x4b4c
0033 push ss
0034 pop ds
0035 mov ax, bx
0037 pop di
0038 leave 
0039 retf 
003a dec bx
003b jns 0x4b32
003d jmp 0x4b45
003f nop 
0040 mov ax, bx
0042 pop di
0043 leave 
0044 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAntLions', 'offset': 17402, 'source': None, 'size': 1758}
- {'symbol': '_SetAntLion', 'offset': 19160, 'source': None, 'size': 57}
- {'symbol': '_KillAntLion', 'offset': 19288, 'source': None, 'size': 160}
- {'symbol': '_InitPillar', 'offset': 19448, 'source': None, 'size': 228}
