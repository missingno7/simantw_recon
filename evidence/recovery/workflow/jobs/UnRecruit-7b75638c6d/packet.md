# Recovery task _UnRecruit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 220 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc4d6]
0009 mov di, word ptr es:[0x7876]
000e cmp word ptr [bp + 6], 0
0012 jne 0x7aa
0014 mov cx, 2
0017 mov ax, di
0019 cdq 
001a idiv cx
001c mov di, ax
001e jmp 0x7ad
0020 add di, 0x64
0023 mov es, word ptr [0xc4d2]
0027 mov si, word ptr es:[0x80f0]
002c or si, si
002e jle 0x7c5
0030 mov <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0033 mov ds, ax
0035 or di, di
0037 jg 0x7fa
0039 push ss
003a pop ds
003b mov es, word ptr [0xc4d4]
003f mov si, word ptr es:[0x99d4]
0044 or si, si
0046 jle 0x7dd
0048 mov <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
004b mov ds, ax
004d or di, di
004f jg 0x81c
0051 push ss
0052 pop ds
0053 mov es, word ptr [0xc4d8]
0057 mov si, word ptr es:[0x72cc]
005c or si, si
005e jle 0x862
0060 mov <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0063 mov ds, ax
0065 or di, di
0067 jg 0x83e
0069 push ss
006a pop ds
006b pop si
006c pop di
006d leave 
006e retf 
006f nop 
0070 dec si
0071 mov cl, byte ptr [si + 0x2f62]
0075 sub ch, ch
0077 or cx, cx
0079 je 0x816
007b test cl, 0x80
007e jne 0x816
0080 cmp byte ptr [si + 0x2b78], 6
0085 jne 0x816
0087 mov byte ptr [si + 0x2b78], ch
008b dec di
008c or si, si
008e jg 0x7bf
0090 jmp 0x7c3
0092 dec si
0093 mov cl, byte ptr [si + 0x3d18]
0097 sub ch, ch
0099 or cx, cx
009b je 0x838
009d test cl, 0x80
00a0 jne 0x838
00a2 cmp byte ptr [si + 0x3b22], 6
00a7 jne 0x838
00a9 mov byte ptr [si + 0x3b22], ch
00ad dec di
00ae or si, si
00b0 jg 0x7d7
00b2 jmp 0x7db
00b4 dec si
00b5 mov cl, byte ptr [si + 0x46e6]
00b9 sub ch, ch
00bb or cx, cx
00bd je 0x85b
00bf test cl, 0x80
00c2 jne 0x85b
00c4 cmp byte ptr [si + 0x44f0], 6
00c9 jne 0x85b
00cb mov byte ptr [si + 0x44f0], 7
00d0 dec di
00d1 or si, si
00d3 jg 0x7ef
00d5 jmp 0x7f3
00d7 nop 
00d8 pop si
00d9 pop di
00da leave 
00db retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ForceModeB', 'offset': 1570, 'source': None, 'size': None}
- {'symbol': '_Recruit', 'offset': 1746, 'source': 'src/recovered/wf_Recruit-bed37927bb.c', 'size': 184}
- {'symbol': '_RecruitRed', 'offset': 2150, 'source': 'src/recovered/wf_RecruitRed-253bf13685.c', 'size': 115}
- {'symbol': '_UnRecruitRed', 'offset': 2266, 'source': None, 'size': 54}
