# Recovery task _GetNewMode

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 192 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 test byte ptr [bp + 8], 0x80
0009 je 0x958
000b mov di, word ptr [bp + 6]
000e cmp di, 2
0011 jne 0x942
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0018 mov es, word ptr [0xc4c4]
001c mov bx, word ptr es:[0x7690]
0021 shl bx, 3
0024 add bx, ax
0026 mov es, word ptr [0xc4da]
002a mov al, byte ptr es:[bx - 0x761a]
002f jmp 0x9ab
0031 nop 
0032 cmp di, 6
0035 jne 0x9a2
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
003c mov es, word ptr [0xc4c4]
0040 mov bx, word ptr es:[0x7690]
0045 jmp 0x98f
0047 nop 
0048 mov es, word ptr [0xc4e0]
004c cmp word ptr es:[0x9fce], 1
0052 jne 0x9b4
0054 mov si, word ptr [bp + 6]
0057 cmp si, 2
005a jne 0x97c
005c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0061 mov es, word ptr [0xc4e2]
0065 mov bx, word ptr es:[0x9b8a]
006a jmp 0x931
006c cmp si, 6
006f jne 0x9a0
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0076 mov es, word ptr [0xc4e2]
007a mov bx, word ptr es:[0x9b8a]
007f shl bx, 3
0082 add bx, ax
0084 mov es, word ptr [0xc4dc]
0088 mov al, byte ptr es:[bx - 0x75ea]
008d jmp 0x9ab
008f nop 
0090 mov di, si
0092 mov es, word ptr [0xc4de]
0096 mov al, byte ptr es:[di - 0x75ba]
009b cwde 
009c mov si, ax
009e mov ax, si
00a0 pop si
00a1 pop di
00a2 leave 
00a3 retf 
00a4 mov di, word ptr [bp + 6]
00a7 cmp di, 2
00aa je 0x9c1
00ac cmp di, 6
00af jne 0x9a2
00b1 mov es, word ptr [0xc4cc]
00b5 mov si, word ptr es:[0x8a58]
00ba mov ax, si
00bc pop si
00bd pop di
00be leave 
00bf retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RecruitRed', 'offset': 2150, 'source': None, 'size': 115}
- {'symbol': '_UnRecruitRed', 'offset': 2266, 'source': None, 'size': 54}
- {'symbol': '_GetNewModeB', 'offset': 2512, 'source': None, 'size': 127}
- {'symbol': '_GetNewModeR', 'offset': 2640, 'source': None, 'size': 95}
