# Recovery task _EnterNest

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 155 bytes.

```asm
0000 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 3, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _TryAntTheme
0005 mov es, word ptr [0xc3ce]
0009 cmp word ptr es:[0x75fa], 0
000f je 0x8425
0011 push 1
0013 push 0
0015 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 24, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetAlarmDropState
001a add sp, 4
001d push word ptr [0xcf50] ; _MeDir
0021 push word ptr [0xcc84] ; _MeType
0025 push word ptr [0xce7e] ; _MeLocY
0029 push word ptr [0xcd88] ; _MeLocX
002d push word ptr [0xce80] ; _MePlane
0031 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 52, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ClearMyLife
0036 add sp, 0xa
0039 cmp word ptr [0xcd88], 0x40 ; _MeLocX
003e jle 0x844e
0040 mov ax, 3
0043 jmp 0x8451
0045 nop 
0046 mov ax, 2
0049 mov word ptr [0xce80], ax ; _MePlane
004c mov ax, word ptr [0xce7e] ; _MeLocY
004f mov word ptr [0xcd88], ax ; _MeLocX
0052 cmp word ptr [0xcc84], 0x60 ; _MeType
0057 jne 0x8466
0059 mov ax, 2
005c jmp 0x8469
005e mov ax, 1
0061 mov word ptr [0xce7e], ax ; _MeLocY
0064 mov word ptr [0xcf50], 4 ; _MeDir
006a push ax
006b push word ptr [0xcd88] ; _MeLocX
006f push word ptr [0xce80] ; _MePlane
0073 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 118, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _DigMyTile
0078 add sp, 6
007b push 0xff
007e push word ptr [0xcf50] ; _MeDir
0082 push word ptr [0xcc84] ; _MeType
0086 push word ptr [0xce7e] ; _MeLocY
008a push word ptr [0xcd88] ; _MeLocX
008e push word ptr [0xce80] ; _MePlane
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyLife
0097 add sp, 0xc
009a retf 
```

## Known declaration examples

- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AnimYellowInsane', 'offset': 32888, 'source': None, 'size': 454}
- {'symbol': '_YellowFight', 'offset': 33342, 'source': None, 'size': 457}
- {'symbol': '_ExitNest', 'offset': 33956, 'source': None, 'size': 477}
- {'symbol': '_GetMyDis', 'offset': 34434, 'source': None, 'size': 421}
