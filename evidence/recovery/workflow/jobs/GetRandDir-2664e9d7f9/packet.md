# Recovery task _GetRandDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 179 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c or di, di
000e jne 0xfae
0010 or si, si
0012 jne 0xf96
0014 push 3
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
001b add sp, 2
001e add ax, 3
0021 jmp 0xff4
0023 nop 
0024 cmp si, 0x3f
0027 jne 0xfa0
0029 push 3
002b jmp 0xfa2
002d nop 
002e push 5
0030 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 51, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0035 add sp, 2
0038 inc ax
0039 jmp 0xff4
003b nop 
003c or si, si
003e jne 0xfca
0040 cmp di, 0x7f
0043 jne 0xfc6
0045 push 3
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
004c add sp, 2
004f add ax, 5
0052 jmp 0xff4
0054 push 5
0056 jmp 0xf88
0058 cmp di, 0x7f
005b jne 0xfe8
005d cmp si, 0x3f
0060 jne 0xfe4
0062 push 3
0064 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 103, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0069 add sp, 2
006c add ax, 7
006f jmp 0xff4
0071 nop 
0072 push 5
0074 jmp 0xfb9
0076 cmp si, 0x3f
0079 jne 0xff2
007b push 5
007d jmp 0xfd6
007f nop 
0080 xor ax, ax
0082 mov word ptr [bp - 2], ax
0085 or ax, ax
0087 je 0x1008
0089 mov al, byte ptr [bp - 2]
008c dec al
008e and ax, 7
0091 pop si
0092 pop di
0093 leave 
0094 retf 
0095 nop 
0096 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
009b mov bx, ax
009d mov ax, word ptr [bp + 0xa]
00a0 shl ax, 3
00a3 add bx, ax
00a5 mov es, word ptr [0xc4e6]
00a9 mov al, byte ptr es:[bx + 0x24]
00ae cwde 
00af pop si
00b0 pop di
00b1 leave 
00b2 retf 
```

## Known declaration examples

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

- {'symbol': '_GetNestDir', 'offset': 3120, 'source': None, 'size': 547}
- {'symbol': '_GetAlarmDir', 'offset': 3668, 'source': None, 'size': 286}
- {'symbol': '_GetDefendDir', 'offset': 4134, 'source': None, 'size': 365}
- {'symbol': '_GetRedDefendDir', 'offset': 4500, 'source': None, 'size': 343}
