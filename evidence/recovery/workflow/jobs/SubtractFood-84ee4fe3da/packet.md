# Recovery task _SubtractFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 77 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 xor di, di
0008 xor si, si
000a mov bx, di
000c add bx, si
000e add bx, 0x28e8
0012 mov word ptr [bp - 4], bx
0015 mov al, byte ptr [bx]
0017 sub ah, ah
0019 push ax
001a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 29, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
001f add sp, 2
0022 dec ax
0023 jne 0x9e53
0025 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 40, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
002a mov bx, word ptr [bp - 4]
002d mov byte ptr [bx], al
002f inc si
0030 cmp si, 0x40
0033 jl 0x9e2e
0035 add di, 0x40
0038 cmp di, 0x2000
003c jl 0x9e2c
003e mov es, word ptr [0xc0e0]
0042 mov word ptr es:[0x9e84], 0
0049 pop si
004a pop di
004b leave 
004c retf 
```

## Known declaration examples

- `extern int far IsItFood(int tile);` — src/recovered/wf_IsThisFood-26910209bd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AddSomeAnts', 'offset': 40196, 'source': None, 'size': 90}
- {'symbol': '_KillSomeAnts', 'offset': 40286, 'source': None, 'size': 198}
- {'symbol': '_SetEditMode', 'offset': 40562, 'source': 'src/recovered/SetEditMode.c', 'size': 16}
- {'symbol': '_SetMapModeAnt', 'offset': 40578, 'source': None, 'size': 274}
