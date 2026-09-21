# Recovery task _AddRedAnts

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 173 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov dx, 0x7f
0009 mov di, 0x1fc0
000c mov si, 0x10
000f mov word ptr [bp - 6], dx
0012 mov bx, di
0014 add bx, si
0016 mov word ptr [bp - 0xa], bx
0019 cmp byte ptr [bx + 0x28e8], 0x50
001e jae 0x6d8e
0020 cmp byte ptr [bx + 0x68e8], 0
0025 jne 0x6d8e
0027 push 0xa
0029 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 44, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
002e add sp, 2
0031 or ax, ax
0033 jl 0x6d3a
0035 jo 0x6d3a
0037 sub ax, 3
003a jle 0x6d48
003c mov word ptr [bp - 2], 0x10
0041 mov word ptr [bp - 4], 4
0046 jmp 0x6d52
0048 nop 
0049 nop 
004a mov word ptr [bp - 2], 0x30
004f mov word ptr [bp - 4], 2
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0059 add ax, word ptr [bp - 2]
005c add ax, 0x80
005f mov cx, ax
0061 mov bx, word ptr [bp - 0xa]
0064 mov byte ptr [bx + 0x68e8], al
0068 push 0
006a push word ptr [bp - 4]
006d push cx
006e push si
006f push word ptr [bp - 6]
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToAList
0077 add sp, 0xa
007a dec word ptr [bp + 6]
007d cmp word ptr [bp + 6], 0
0081 jle 0x6da7
0083 mov es, word ptr [0xc62c]
0087 cmp word ptr es:[0x80f0], 0x3e8
008e jge 0x6da7
0090 inc si
0091 cmp si, 0x30
0094 jge 0x6d97
0096 jmp 0x6d10
0099 mov dx, word ptr [bp - 6]
009c dec dx
009d sub di, 0x40
00a0 cmp di, 0x1000
00a4 jl 0x6da7
00a6 jmp 0x6d0a
00a9 pop si
00aa pop di
00ab leave 
00ac retf 
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

- {'symbol': '_AddFood', 'offset': 27224, 'source': None, 'size': 513}
- {'symbol': '_AddBlackAnts', 'offset': 27738, 'source': None, 'size': 163}
- {'symbol': '_GrabMap', 'offset': 28076, 'source': None, 'size': 64}
- {'symbol': '_ClrArrays', 'offset': 28140, 'source': None, 'size': 273}
