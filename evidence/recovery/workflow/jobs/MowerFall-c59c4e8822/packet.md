# Recovery task _MowerFall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 166 bytes.

```asm
0000 push di
0001 push si
0002 mov es, word ptr [0xc53e]
0006 cmp word ptr es:[0x80b4], 0
000c jne 0x34eb
000e jmp 0x357d
0011 mov es, word ptr [0xc540]
0015 mov si, word ptr es:[0x80f0]
001a or si, si
001c jle 0x353d
001e mov <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0021 mov es, ax
0023 dec si
0024 cmp byte ptr es:[si + 0x2f62], 0
002a je 0x3539
002c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 47, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0031 or ax, ax
0033 jne 0x3516
0035 mov <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0038 mov es, ax
003a jmp 0x3539
003c mov <resolved loader operand; see bindings> ; [{'operand_offset': 61, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
003f mov es, ax
0041 mov bl, byte ptr es:[si + 0x278e]
0046 sub bh, bh
0048 mov di, word ptr es:[si + 0x23a4]
004d and di, 0xff
0051 shl di, 6
0054 xor al, al
0056 mov byte ptr [bx + di + 0x68e8], al
005a mov byte ptr es:[si + 0x2f62], al
005f or si, si
0061 jg 0x34fd
0063 mov es, word ptr [0xc542]
0067 cmp word ptr es:[0x9bd2], 0
006d je 0x3557
006f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0074 or ax, ax
0076 je 0x3557
0078 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _KillSpider
007d mov es, word ptr [0xc544]
0081 cmp word ptr es:[0x9fe8], 1
0087 jg 0x357d
0089 cmp word ptr [0xce80], 1 ; _MePlane
008e jne 0x357d
0090 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0095 or ax, ax
0097 je 0x357d
0099 push 6
009b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 158, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _YellowDeath
00a0 add sp, 2
00a3 pop si
00a4 pop di
00a5 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakeBark', 'offset': 13034, 'source': None, 'size': 155}
- {'symbol': '_FootFall', 'offset': 13190, 'source': None, 'size': 339}
- {'symbol': '_MaintainSwarm', 'offset': 13696, 'source': 'src/recovered/wf_MaintainSwarm-82303a3cad.c', 'size': 119}
- {'symbol': '_SimColonies', 'offset': 13816, 'source': None, 'size': 1771}
