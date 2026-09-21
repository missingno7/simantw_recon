# Recovery task _GstrB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 162 bytes.

```asm
0000 push di
0001 mov cx, word ptr ss:[0xac86]
0006 cmp cx, 0xa
0009 jge 0x1fe
000b mov bx, word ptr ss:[0xac84]
0010 mov ax, word ptr ss:[0xac82]
0014 sar ax, 1
0016 cmp ax, bx
0018 jle 0x1fe
001a or bx, bx
001c jle 0x1fe
001e mov <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0021 mov es, ax
0023 cmp word ptr es:[0x79dc], 0
0029 jle 0x1fe
002b xor ax, ax
002d push ss
002e pop ds
002f pop di
0030 retf 
0031 nop 
0032 cmp cx, 0x1e
0035 jge 0x20a
0037 mov ax, 5
003a push ss
003b pop ds
003c pop di
003d retf 
003e cmp cx, 0x32
0041 jge 0x216
0043 mov ax, 4
0046 push ss
0047 pop ds
0048 pop di
0049 retf 
004a mov di, word ptr ss:[0xac82]
004f mov <resolved loader operand; see bindings> ; [{'operand_offset': 80, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0052 mov es, ax
0054 cmp word ptr es:[0x72c8], di
0059 jge 0x22e
005b mov ax, 3
005e push ss
005f pop ds
0060 pop di
0061 retf 
0062 mov ax, di
0064 shl ax, 1
0066 cmp word ptr es:[0x72c8], ax
006b jge 0x240
006d mov ax, 2
0070 push ss
0071 pop ds
0072 pop di
0073 retf 
0074 cmp di, 0x64
0077 jle 0x267
0079 mov bx, word ptr ss:[0xac84]
007e or bx, bx
0080 jle 0x267
0082 mov <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0085 mov es, ax
0087 cmp word ptr es:[0x79dc], 0
008d jle 0x267
008f mov ax, di
0091 mov cx, 3
0094 cdq 
0095 idiv cx
0097 cmp ax, bx
0099 jg 0x1f7
009b mov ax, 1
009e push ss
009f pop ds
00a0 pop di
00a1 retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetStrategy', 'offset': 0, 'source': None, 'size': 460}
- {'symbol': '_SetCasteProd', 'offset': 622, 'source': None, 'size': 183}
- {'symbol': '_SetModeProd', 'offset': 806, 'source': 'src/recovered/wf_SetModeProd-f696675003.c', 'size': 156}
