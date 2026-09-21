# Recovery task _RaidOutR

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
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 17, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetExitDirR
0013 add sp, 6
0016 mov si, ax
0018 or si, si
001a jne 0x5d36
001c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0021 mov si, ax
0023 jmp 0x5d37
0025 nop 
0026 dec si
0027 push si
0028 push di
0029 push word ptr [bp + 6]
002c nop 
002d push cs
002e call 0x6850 ; _TryMoveDirR
0031 add sp, 6
0034 or ax, ax
0036 jne 0x5d7a
0038 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
003d push ax
003e push di
003f push word ptr [bp + 6]
0042 nop 
0043 push cs
0044 call 0x6850 ; _TryMoveDirR
0047 add sp, 6
004a or ax, ax
004c jne 0x5d7a
004e mov es, word ptr [0xc384]
0052 mov bx, word ptr es:[0x9b6a]
0057 mov es, word ptr [0xc386]
005b mov al, byte ptr es:[bx + 0x46e6]
0060 mov bx, word ptr [bp + 6]
0063 shl bx, 6
0066 mov byte ptr [bx + di - 0x6718], al
006a pop si
006b pop di
006c leave 
006d retf 
```

## Known declaration examples

- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RaidInR', 'offset': 23338, 'source': None, 'size': 235}
- {'symbol': '_StayInR', 'offset': 23574, 'source': None, 'size': 249}
- {'symbol': '_DoRestR', 'offset': 23934, 'source': None, 'size': 298}
- {'symbol': '_DoDrownR', 'offset': 24232, 'source': None, 'size': 210}
