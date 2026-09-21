# Recovery task _GetMyNextRandDirs

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 244 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xa]
0009 mov word ptr [bp - 6], 0
000e push word ptr [bp + 0xe]
0011 push word ptr [bp + 0xc]
0014 push di
0015 push word ptr [bp + 8]
0018 push word ptr [bp + 6]
001b nop 
001c push cs
001d call 0x8828 ; _GetMyBestDirs
0020 add sp, 0xa
0023 mov si, ax
0025 or si, si
0027 jge 0x8c16
0029 jmp 0x8cb2
002c mov es, word ptr [0xc3ca]
0030 mov al, byte ptr es:[si]
0035 cwde 
0036 add ax, word ptr [bp + 8]
0039 mov word ptr [bp - 2], ax
003c mov es, word ptr [0xc3c4]
0040 mov al, byte ptr es:[si + 8]
0045 cwde 
0046 add ax, di
0048 mov word ptr [bp - 4], ax
004b or si, si
004d jl 0x8cb2
004f mov di, word ptr [bp - 6]
0052 cmp di, 0x40
0055 jge 0x8c7d
0057 push word ptr [bp + 0xe]
005a push word ptr [bp + 0xc]
005d push word ptr [bp - 4]
0060 push word ptr [bp - 2]
0063 push word ptr [bp + 6]
0066 nop 
0067 push cs
0068 call 0x8828 ; _GetMyBestDirs
006b add sp, 0xa
006e mov si, ax
0070 or si, si
0072 jl 0x8c78
0074 mov es, word ptr [0xc3ca]
0078 mov al, byte ptr es:[si]
007d cwde 
007e add word ptr [bp - 2], ax
0081 mov es, word ptr [0xc3c4]
0085 mov al, byte ptr es:[si + 8]
008a cwde 
008b add word ptr [bp - 4], ax
008e inc di
008f or si, si
0091 jge 0x8c3c
0093 or si, si
0095 jl 0x8c84
0097 mov si, 0xffff
009a cmp si, -2
009d jne 0x8cb8
009f push word ptr [bp + 0xe]
00a2 push word ptr [bp + 0xc]
00a5 push word ptr [bp + 0xa]
00a8 push word ptr [bp + 8]
00ab push word ptr [bp + 6]
00ae push <resolved loader operand; see bindings> ; [{'operand_offset': 175, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00b1 push 0xa0d8
00b4 push <resolved loader operand; see bindings> ; [{'operand_offset': 181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00b7 push 0x78a4
00ba nop 
00bb push cs
00bc call 0x8928 ; _GetMyRandDirs
00bf add sp, 0x12
00c2 pop si
00c3 pop di
00c4 leave 
00c5 retf 
00c6 nop 
00c7 nop 
00c8 mov di, word ptr [bp - 6]
00cb jmp 0x8c7d
00cd nop 
00ce mov es, word ptr [0xc3f6]
00d2 mov word ptr es:[0x72e4], 0xffff
00d9 push word ptr [bp + 0xe]
00dc push word ptr [bp + 0xc]
00df push word ptr [bp + 0xa]
00e2 push word ptr [bp + 8]
00e5 push word ptr [bp + 6]
00e8 nop 
00e9 push cs
00ea call 0x8828 ; _GetMyBestDirs
00ed add sp, 0xa
00f0 pop si
00f1 pop di
00f2 leave 
00f3 retf 
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

- {'symbol': '_GetMyRandDirs', 'offset': 35112, 'source': None, 'size': 536}
- {'symbol': '_CheckMyBestDirs', 'offset': 35648, 'source': None, 'size': 169}
- {'symbol': '_GetMyInitialRandDir', 'offset': 36062, 'source': None, 'size': 91}
- {'symbol': '_GetMyBestDir', 'offset': 36154, 'source': None, 'size': 399}
