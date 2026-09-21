# Recovery task _RaidOutB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 110 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 8]
0008 push 8
000a push di
000b push word ptr [bp + 6]
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirB
0013 add sp, 6
0016 mov si, ax
0018 or si, si
001a jne 0x3636
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0021 mov si, ax
0023 jmp 0x3637
0025 nop 
0026 dec si
0027 push si
0028 push di
0029 push word ptr [bp + 6]
002c nop 
002d push cs
002e call 0x439e ; _TryMoveDirB
0031 add sp, 6
0034 or ax, ax
0036 jne 0x367a
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
003d push ax
003e push di
003f push word ptr [bp + 6]
0042 nop 
0043 push cs
0044 call 0x439e ; _TryMoveDirB
0047 add sp, 6
004a or ax, ax
004c jne 0x367a
004e mov es, word ptr [0xc350]
0052 mov bx, word ptr es:[0x9b6a]
0057 mov es, word ptr [0xc352]
005b mov al, byte ptr es:[bx + 0x3d18]
0060 mov bx, word ptr [bp + 6]
0063 shl bx, 6
0066 mov byte ptr [bx + di - 0x7718], al
006a pop si
006b pop di
006c leave 
006d retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/RandTurn.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoNestAntB', 'offset': 11694, 'source': None, 'size': None}
- {'symbol': '_RaidInB', 'offset': 13604, 'source': None, 'size': 235}
- {'symbol': '_DoRestB', 'offset': 13950, 'source': None, 'size': 294}
- {'symbol': '_DoDrownB', 'offset': 14244, 'source': None, 'size': 210}
