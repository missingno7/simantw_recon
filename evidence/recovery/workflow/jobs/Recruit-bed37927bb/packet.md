# Recovery task _Recruit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 184 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 6]
0008 mov es, word ptr [0xc4d2]
000c mov si, word ptr es:[0x80f0]
0011 or si, si
0013 jle 0x6f2
0015 mov <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0018 mov ds, ax
001a or di, di
001c jg 0x712
001e push ss
001f pop ds
0020 mov es, word ptr [0xc4d4]
0024 mov si, word ptr es:[0x99d4]
0029 or si, si
002b jg 0x702
002d jmp 0x786
0030 mov <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0033 mov ds, ax
0035 or di, di
0037 jg 0x74c
0039 push ss
003a pop ds
003b pop si
003c pop di
003d leave 
003e retf 
003f nop 
0040 dec si
0041 mov cl, byte ptr [si + 0x2f62]
0045 sub ch, ch
0047 or cx, cx
0049 je 0x746
004b test cl, 0x80
004e jne 0x746
0050 mov dx, cx
0052 and dx, 0x78
0055 sar dx, 3
0058 cmp dx, 2
005b je 0x734
005d cmp dx, 6
0060 jne 0x746
0062 cmp byte ptr [si + 0x2b78], 6
0067 je 0x746
0069 mov byte ptr [si + 0x2b78], 6
006e mov byte ptr [si + 0x334c], 0
0073 dec di
0074 or si, si
0076 jg 0x6ec
0078 jmp 0x6f0
007a dec si
007b mov cl, byte ptr [si + 0x3d18]
007f sub ch, ch
0081 or cx, cx
0083 je 0x780
0085 test cl, 0x80
0088 jne 0x780
008a mov dx, cx
008c and dx, 0x78
008f sar dx, 3
0092 cmp dx, 2
0095 je 0x76e
0097 cmp dx, 6
009a jne 0x780
009c cmp byte ptr [si + 0x3b22], 6
00a1 je 0x780
00a3 mov byte ptr [si + 0x3b22], 6
00a8 mov byte ptr [si + 0x3f0e], 0
00ad dec di
00ae or si, si
00b0 jg 0x707
00b2 jmp 0x70b
00b4 pop si
00b5 pop di
00b6 leave 
00b7 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ForceModeA', 'offset': 1360, 'source': None, 'size': None}
- {'symbol': '_ForceModeB', 'offset': 1570, 'source': None, 'size': None}
- {'symbol': '_UnRecruit', 'offset': 1930, 'source': None, 'size': 220}
- {'symbol': '_RecruitRed', 'offset': 2150, 'source': None, 'size': 115}
