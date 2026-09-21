# Recovery task _GetNewModeB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 127 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov es, word ptr [0xc4e0]
0008 cmp word ptr es:[0x9fce], 1
000e jne 0xa2c
0010 mov si, word ptr [bp + 6]
0013 cmp si, 2
0016 jne 0xa08
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
001d mov es, word ptr [0xc4e2]
0021 mov bx, word ptr es:[0x9b8a]
0026 shl bx, 3
0029 add bx, ax
002b mov es, word ptr [0xc4da]
002f mov al, byte ptr es:[bx - 0x761a]
0034 cwde 
0035 pop si
0036 leave 
0037 retf 
0038 cmp si, 6
003b jne 0xa39
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0042 mov es, word ptr [0xc4e2]
0046 mov bx, word ptr es:[0x9b8a]
004b shl bx, 3
004e add bx, ax
0050 mov es, word ptr [0xc4dc]
0054 mov al, byte ptr es:[bx - 0x75ea]
0059 jmp 0xa04
005b nop 
005c mov si, word ptr [bp + 6]
005f cmp si, 2
0062 je 0xa44
0064 cmp si, 6
0067 je 0xa44
0069 mov es, word ptr [0xc4de]
006d mov al, byte ptr es:[si - 0x75ba]
0072 jmp 0xa04
0074 mov es, word ptr [0xc4cc]
0078 mov ax, word ptr es:[0x8a58]
007c pop si
007d leave 
007e retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutR-a39ba19d03.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_UnRecruitRed', 'offset': 2266, 'source': None, 'size': 54}
- {'symbol': '_GetNewMode', 'offset': 2320, 'source': None, 'size': 192}
- {'symbol': '_GetNewModeR', 'offset': 2640, 'source': None, 'size': 95}
- {'symbol': '_GetForageDir', 'offset': 2736, 'source': None, 'size': 384}
