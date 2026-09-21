# Recovery task _DoRepoExit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 208 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0008 mov es, ax
000a mov si, word ptr [bp + 4]
000d test byte ptr es:[si + 0x2f62], 0x80
0013 je 0xcae
0015 mov bl, byte ptr es:[si + 0x23a4]
001a and bx, 0xfe
001e shl bx, 4
0021 mov al, byte ptr es:[si + 0x278e]
0026 shr al, 1
0028 sub ah, ah
002a add bx, ax
002c mov cl, byte ptr es:[bx + 0x72d2]
0031 jmp 0xcca
0033 nop 
0034 mov bl, byte ptr es:[si + 0x23a4]
0039 and bx, 0xfe
003d shl bx, 4
0040 mov al, byte ptr es:[si + 0x278e]
0045 shr al, 1
0047 sub ah, ah
0049 add bx, ax
004b mov cl, byte ptr es:[bx + 0x62d2]
0050 sub ch, ch
0052 cmp cx, 0x64
0055 jge 0xcd8
0057 push si
0058 call 0x1676 ; _DoToNestAnt
005b jmp 0xcdc
005d nop 
005e push si
005f call 0x1234 ; _DoRandAntAA
0062 add sp, 2
0065 mov es, word ptr [0xc318]
0069 test byte ptr es:[si + 0x2f62], 0x80
006f je 0xd0a
0071 mov bx, 0x8078
0074 mov es, word ptr [0xc324]
0078 mov word ptr [bp - 4], bx
007b mov word ptr [bp - 2], es
007e cmp word ptr es:[bx], 0
0082 je 0xd47
0084 cmp word ptr es:[bx], 1
0088 je 0xd34
008a push word ptr es:[bx]
008d jmp 0xd28
008f nop 
0090 mov <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0093 mov es, ax
0095 cmp word ptr es:[0x7c44], 0
009b je 0xd47
009d cmp word ptr es:[0x7c44], 1
00a3 je 0xd34
00a5 mov es, word ptr [0xc326]
00a9 push word ptr es:[0x7c44]
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
00b3 add sp, 2
00b6 or ax, ax
00b8 jne 0xd47
00ba mov es, word ptr [0xc316]
00be mov bx, word ptr es:[0x9b6a]
00c3 mov es, word ptr [0xc318]
00c7 mov byte ptr es:[bx + 0x2b78], 0x10
00cd pop si
00ce leave 
00cf ret 
```

## Known declaration examples

- `extern void near DoRandAntAA(int ant);` — src/recovered/wf_DoDefendNest-ed5a5a93f0.c
- `extern void near DoToNestAnt(int ant);` — src/recovered/wf_DoDefendNest-ed5a5a93f0.c
- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRestAnt', 'offset': 2934, 'source': None, 'size': 168}
- {'symbol': '_DoRepoLoit', 'offset': 3102, 'source': None, 'size': 91}
- {'symbol': '_DoRepoFly', 'offset': 3402, 'source': None, 'size': 172}
- {'symbol': '_DoDefendNest', 'offset': 3574, 'source': 'src/recovered/wf_DoDefendNest-ed5a5a93f0.c', 'size': 112}
