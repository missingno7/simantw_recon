# Recovery task _MaintainSwarm

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 119 bytes.

```asm
0000 mov <resolved loader operand; see bindings> ; [{'operand_offset': 1, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0003 mov ds, ax
0005 mov bx, word ptr [0x807a]
0009 or bx, bx
000b jle 0x35a1
000d cmp bx, 4
0010 jl 0x35a0
0012 sar bx, 2
0015 mov ax, bx
0017 mov bx, word ptr [0x807a]
001b sub bx, ax
001d jmp 0x35a1
001f nop 
0020 dec bx
0021 cmp word ptr ss:[0xac8c], bx
0026 jle 0x35ad
0028 mov bx, word ptr ss:[0xac8c]
002d cmp bx, 0x32
0030 jle 0x35b5
0032 mov bx, 0x32
0035 mov word ptr [0x807a], bx
0039 mov <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
003c mov es, ax
003e mov bx, word ptr es:[0x9c26]
0043 or bx, bx
0045 jle 0x35db
0047 cmp bx, 4
004a jl 0x35da
004c sar bx, 2
004f mov ax, bx
0051 mov bx, word ptr es:[0x9c26]
0056 sub bx, ax
0058 jmp 0x35db
005a dec bx
005b cmp word ptr ss:[0xac8e], bx
0060 jle 0x35e7
0062 mov bx, word ptr ss:[0xac8e]
0067 cmp bx, 0x32
006a jle 0x35ef
006c mov bx, 0x32
006f mov word ptr es:[0x9c26], bx
0074 push ss
0075 pop ds
0076 retf 
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

- {'symbol': '_FootFall', 'offset': 13190, 'source': None, 'size': 339}
- {'symbol': '_MowerFall', 'offset': 13530, 'source': None, 'size': 166}
- {'symbol': '_SimColonies', 'offset': 13816, 'source': None, 'size': 1771}
- {'symbol': '_GetNearbyPatches', 'offset': 15588, 'source': None, 'size': 103}
