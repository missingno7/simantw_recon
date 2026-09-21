# Recovery task _RunTutor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 190 bytes.

```asm
0000 enter 8, 0
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0007 mov es, ax
0009 inc word ptr es:[0x85ec]
000e cmp word ptr es:[0x85ec], 0x400
0015 jle 0x7aae
0017 mov word ptr es:[0x85ec], 0
001e test byte ptr es:[0x85ec], 7
0024 jne 0x7afc
0026 mov bx, 0x7d62
0029 mov <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
002c mov es, ax
002e mov word ptr [bp - 4], bx
0031 mov word ptr [bp - 2], es
0034 inc word ptr es:[bx]
0037 mov bx, 0x85f0
003a mov <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
003d mov es, ax
003f mov word ptr [bp - 8], bx
0042 mov word ptr [bp - 6], es
0045 cmp word ptr es:[bx], 0
0049 jne 0x7b00
004b push ss
004c pop ds
004d mov es, word ptr [0xc65c]
0051 push word ptr es:[0x85ee]
0056 nop 
0057 push cs
0058 call 0x7b4e ; _GiveLesson
005b add sp, 2
005e les bx, ptr [bp - 8]
0061 mov word ptr es:[bx], 1
0066 les bx, ptr [bp - 4]
0069 jmp 0x7b47
006b nop 
006c push ss
006d pop ds
006e leave 
006f retf 
0070 push ss
0071 pop ds
0072 mov es, word ptr [0xc65c]
0076 push word ptr es:[0x85ee]
007b nop 
007c push cs
007d call 0x7f02 ; _LessonDone
0080 add sp, 2
0083 or ax, ax
0085 je 0x7b22
0087 mov es, word ptr [0xc65c]
008b inc word ptr es:[0x85ee]
0090 jmp 0x7b44
0092 les bx, ptr [bp - 4]
0095 cmp word ptr es:[bx], 0xf
0099 jle 0x7b4c
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00a0 mov es, word ptr [0xc65e]
00a4 cmp dx, word ptr es:[0x9b12]
00a9 jl 0x7b4c
00ab jg 0x7b44
00ad cmp ax, word ptr es:[0x9b10]
00b2 jbe 0x7b4c
00b4 les bx, ptr [bp - 8]
00b7 mov word ptr es:[bx], 0
00bc leave 
00bd retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_OverlayInsideTiles', 'offset': 30910, 'source': 'src/recovered/OverlayInsideTiles.c', 'size': 12}
- {'symbol': '_Feedback', 'offset': 30922, 'source': None, 'size': 453}
- {'symbol': '_GiveLesson', 'offset': 31566, 'source': None, 'size': None}
- {'symbol': '_LessonDone', 'offset': 32514, 'source': None, 'size': None}
