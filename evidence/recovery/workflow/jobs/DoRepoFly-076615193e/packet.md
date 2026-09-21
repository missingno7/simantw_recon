# Recovery task _DoRepoFly

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 172 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov di, word ptr [bp + 4]
0008 mov es, word ptr [0xc318]
000c mov al, byte ptr es:[di + 0x2f62]
0011 and ax, 0x80
0014 mov si, ax
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand32
001b or ax, ax
001d je 0xd6c
001f jmp 0xdf2
0022 or si, si
0024 jne 0xd7c
0026 mov es, word ptr [0xc328]
002a cmp word ptr es:[0x807a], 0x32
0030 jl 0xd8c
0032 or si, si
0034 je 0xdf2
0036 mov es, word ptr [0xc32a]
003a cmp word ptr es:[0x9c26], 0x32
0040 jge 0xdf2
0042 xor al, al
0044 mov es, word ptr [0xc318]
0048 mov byte ptr es:[di + 0x2f62], al
004d mov bl, byte ptr es:[di + 0x278e]
0052 sub bh, bh
0054 mov di, word ptr es:[di + 0x23a4]
0059 and di, 0xff
005d shl di, 6
0060 mov byte ptr [bx + di + 0x68e8], al
0064 mov es, word ptr [0xc310]
0068 cmp word ptr es:[0x80b4], 2
006e jne 0xdf2
0070 or si, si
0072 jne 0xdca
0074 mov es, word ptr [0xc328]
0078 inc word ptr es:[0x807a]
007d jmp 0xdd3
007f nop 
0080 mov es, word ptr [0xc32a]
0084 inc word ptr es:[0x9c26]
0089 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 140, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand16
008e or ax, ax
0090 jne 0xdf2
0092 or si, si
0094 jne 0xdee
0096 inc word ptr [0xac8c] ; _QueenStorageB
009a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 157, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _InvalQueenStorageDisp
009f pop si
00a0 pop di
00a1 leave 
00a2 ret 
00a3 nop 
00a4 inc word ptr [0xac8e] ; _QueenStorageR
00a8 pop si
00a9 pop di
00aa leave 
00ab ret 
```

## Known declaration examples

- `extern int near QueenStorageB;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageB;` — src/recovered/wf_MaintainSwarm-82303a3cad.c
- `extern int near QueenStorageR;` — src/recovered/InitSimVars.c
- `extern int near QueenStorageR;` — src/recovered/wf_MaintainSwarm-82303a3cad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRepoLoit', 'offset': 3102, 'source': None, 'size': 91}
- {'symbol': '_DoRepoExit', 'offset': 3194, 'source': None, 'size': 208}
- {'symbol': '_DoDefendNest', 'offset': 3574, 'source': 'src/recovered/wf_DoDefendNest-ed5a5a93f0.c', 'size': 112}
- {'symbol': '_DoRandAntA', 'offset': 3686, 'source': None, 'size': 974}
