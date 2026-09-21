# Recovery task _PlaceDrop

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 170 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 push 0x80
0009 nop 
000a push cs
000b call 0x156e ; _RRand
000e add sp, 2
0011 mov si, ax
0013 push 0x40
0015 nop 
0016 push cs
0017 call 0x156e ; _RRand
001a add sp, 2
001d mov di, ax
001f mov ax, si
0021 mov es, word ptr [0xc2ee]
0025 mov bx, word ptr [bp + 6]
0028 mov byte ptr es:[bx + 0x79e6], al
002d mov es, word ptr [0xc2ec]
0031 mov ax, di
0033 mov byte ptr es:[bx + 0x7a72], al
0038 mov bx, si
003a shl bx, 6
003d add bx, di
003f add bx, 0x28e8
0043 mov word ptr [bp - 2], bx
0046 cmp byte ptr [bx], 0xe
0049 jae 0xb72
004b mov byte ptr [bx], 0x74
004e mov <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0051 mov es, ax
0053 xor al, al
0055 sar si, 1
0057 mov bx, si
0059 shl bx, 5
005c sar di, 1
005e add bx, di
0060 mov word ptr [bp - 4], bx
0063 mov byte ptr es:[bx + 0x52d2], al
0068 mov byte ptr es:[bx + 0x5ad2], al
006d cmp byte ptr es:[bx + 0x62d2], 0x14
0073 jb 0xb4a
0075 sub byte ptr es:[bx + 0x62d2], 0x14
007b jmp 0xb50
007d nop 
007e mov byte ptr es:[bx + 0x62d2], 0
0084 mov byte ptr es:[bx + 0x6ad2], 0
008a cmp byte ptr es:[bx + 0x72d2], 0x14
0090 jb 0xb66
0092 sub byte ptr es:[bx + 0x72d2], 0x14
0098 jmp 0xb6c
009a mov byte ptr es:[bx + 0x72d2], 0
00a0 mov byte ptr es:[bx + 0x7ad2], 0
00a6 pop si
00a7 pop di
00a8 leave 
00a9 retf 
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

- {'symbol': '_CountUpdate', 'offset': 1984, 'source': 'src/countupd.c', 'size': 6}
- {'symbol': '_DoWater', 'offset': 1990, 'source': None, 'size': 773}
- {'symbol': '_InitWater', 'offset': 2934, 'source': 'src/recovered/InitWater.c', 'size': 20}
- {'symbol': '_AddWater', 'offset': 2954, 'source': None, 'size': 201}
