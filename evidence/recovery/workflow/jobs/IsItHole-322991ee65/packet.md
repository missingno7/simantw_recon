# Recovery task _IsItHole

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 89 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 8]
0008 mov si, word ptr [bp + 6]
000b push di
000c push si
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0012 add sp, 4
0015 or ax, ax
0017 je 0x2d15
0019 mov es, word ptr [0xc320]
001d cmp word ptr es:[0x9b6e], 0
0023 jne 0x2cf4
0025 mov bx, si
0027 shl bx, 6
002a cmp byte ptr [bx + di + 0x28e8], 0x50
002f jne 0x2d05
0031 jmp 0x2d12
0033 nop 
0034 mov bx, si
0036 shl bx, 6
0039 mov dl, byte ptr [bx + di + 0x28e8]
003d sub dh, dh
003f cmp dx, 0x80
0043 jge 0x2d0c
0045 xor ax, ax
0047 pop si
0048 pop di
0049 leave 
004a retf 
004b nop 
004c cmp dx, 0x8f
0050 jg 0x2d05
0052 mov ax, 1
0055 pop si
0056 pop di
0057 leave 
0058 retf 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RandTurn', 'offset': 10786, 'source': 'src/recovered/RandTurn.c', 'size': 30}
- {'symbol': '_DoAttackAnt', 'offset': 10816, 'source': None, 'size': 640}
- {'symbol': '_IsItFood', 'offset': 11546, 'source': 'src/recovered/wf_IsItFood-c02f58780a.c', 'size': 51}
- {'symbol': '_DoAntSimB', 'offset': 11598, 'source': None, 'size': 95}
