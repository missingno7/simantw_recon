# Recovery task _AddBlackAnts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 163 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 xor di, di
0008 mov dx, di
000a mov si, 0x10
000d mov word ptr [bp - 6], dx
0010 mov bx, di
0012 add bx, si
0014 mov word ptr [bp - 0xa], bx
0017 cmp byte ptr [bx + 0x28e8], 0x50
001c jae 0x6ce3
001e cmp byte ptr [bx + 0x68e8], 0
0023 jne 0x6ce3
0025 push 0xa
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
002c add sp, 2
002f or ax, ax
0031 jl 0x6c94
0033 jo 0x6c94
0035 sub ax, 3
0038 jle 0x6ca0
003a mov word ptr [bp - 2], 0x10
003f mov word ptr [bp - 4], 4
0044 jmp 0x6caa
0046 mov word ptr [bp - 2], 0x30
004b mov word ptr [bp - 4], 2
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0055 add ax, word ptr [bp - 2]
0058 mov cx, ax
005a mov bx, word ptr [bp - 0xa]
005d mov byte ptr [bx + 0x68e8], al
0061 push 0
0063 push word ptr [bp - 4]
0066 push cx
0067 push si
0068 push word ptr [bp - 6]
006b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 110, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToAList
0070 add sp, 0xa
0073 dec word ptr [bp + 6]
0076 cmp word ptr [bp + 6], 0
007a jle 0x6cf9
007c mov es, word ptr [0xc62c]
0080 cmp word ptr es:[0x80f0], 0x3e8
0087 jge 0x6cf9
0089 inc si
008a cmp si, 0x30
008d jl 0x6c6a
008f mov dx, word ptr [bp - 6]
0092 inc dx
0093 add di, 0x40
0096 cmp di, 0x1000
009a jge 0x6cf9
009c jmp 0x6c64
009f pop si
00a0 pop di
00a1 leave 
00a2 retf 
```

## Known declaration examples

- `extern void far AddAntToAList(int x, int y, int type, int a, int b);` — src/recovered/wf_AddAntToList-44a11714fc.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutR-a39ba19d03.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_fracCOS', 'offset': 27150, 'source': 'src/recovered/wf_fracCOS-62316b393c.c', 'size': 74}
- {'symbol': '_AddFood', 'offset': 27224, 'source': None, 'size': 513}
- {'symbol': '_AddRedAnts', 'offset': 27902, 'source': None, 'size': 173}
- {'symbol': '_GrabMap', 'offset': 28076, 'source': None, 'size': 64}
