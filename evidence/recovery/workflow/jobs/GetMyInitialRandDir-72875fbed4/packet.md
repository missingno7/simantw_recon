# Recovery task _GetMyInitialRandDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 91 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 0x14]
0008 mov si, word ptr [bp + 0x16]
000b push si
000c push di
000d push word ptr [bp + 0x12]
0010 push word ptr [bp + 0x10]
0013 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
0018 add sp, 8
001b dec ax
001c mov es, word ptr [0xc3f8]
0020 mov word ptr es:[0xa0d8], ax
0024 mov es, word ptr [0xc3f6]
0028 mov word ptr es:[0x72e4], 0x10
002f mov es, word ptr [0xc3fa]
0033 mov word ptr es:[0x78a4], 0
003a push si
003b push di
003c push word ptr [bp + 0x12]
003f push word ptr [bp + 0x10]
0042 push word ptr [bp + 0xe]
0045 push <resolved loader operand; see bindings> ; [{'operand_offset': 70, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0048 push 0xa0d8
004b push es
004c push 0x78a4
004f nop 
0050 push cs
0051 call 0x8928 ; _GetMyRandDirs
0054 add sp, 0x12
0057 pop si
0058 pop di
0059 leave 
005a retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CheckMyBestDirs', 'offset': 35648, 'source': None, 'size': 169}
- {'symbol': '_GetMyNextRandDirs', 'offset': 35818, 'source': None, 'size': 244}
- {'symbol': '_GetMyBestDir', 'offset': 36154, 'source': None, 'size': 399}
- {'symbol': '_GetMyDir', 'offset': 36554, 'source': None, 'size': 788}
