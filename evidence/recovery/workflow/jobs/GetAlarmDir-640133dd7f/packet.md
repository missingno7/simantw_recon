# Recovery task _GetAlarmDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 286 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 mov si, word ptr [bp + 8]
000c mov ax, di
000e sar ax, 1
0010 mov word ptr [bp - 8], ax
0013 mov ax, si
0015 sar ax, 1
0017 mov word ptr [bp - 6], ax
001a or di, di
001c jne 0xe9e
001e or si, si
0020 jne 0xe86
0022 push 3
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0029 add sp, 2
002c add ax, 3
002f jmp 0xee4
0031 nop 
0032 cmp si, 0x3f
0035 jne 0xe90
0037 push 3
0039 jmp 0xe92
003b nop 
003c push 5
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0043 add sp, 2
0046 inc ax
0047 jmp 0xee4
0049 nop 
004a or si, si
004c jne 0xeba
004e cmp di, 0x7f
0051 jne 0xeb6
0053 push 3
0055 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 88, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
005a add sp, 2
005d add ax, 5
0060 jmp 0xee4
0062 push 5
0064 jmp 0xe78
0066 cmp di, 0x7f
0069 jne 0xed8
006b cmp si, 0x3f
006e jne 0xed4
0070 push 3
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0077 add sp, 2
007a add ax, 7
007d jmp 0xee4
007f nop 
0080 push 5
0082 jmp 0xea9
0084 cmp si, 0x3f
0087 jne 0xee2
0089 push 5
008b jmp 0xec6
008d nop 
008e xor ax, ax
0090 mov word ptr [bp - 2], ax
0093 or ax, ax
0095 je 0xef8
0097 mov al, byte ptr [bp - 2]
009a dec al
009c and ax, 7
009f pop si
00a0 pop di
00a1 leave 
00a2 retf 
00a3 nop 
00a4 xor si, si
00a6 mov di, si
00a8 mov word ptr [bp - 4], di
00ab mov <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ae mov ds, ax
00b0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00b3 mov es, ax
00b5 mov al, byte ptr es:[si + 8]
00ba add al, byte ptr [bp - 6]
00bd and ax, 0x1f
00c0 mov <resolved loader operand; see bindings> ; [{'operand_offset': 193, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00c3 mov es, cx
00c5 mov bl, byte ptr es:[si]
00ca add bl, byte ptr [bp - 8]
00cd and bx, 0x3f
00d0 shl bx, 5
00d3 add bx, ax
00d5 mov cl, byte ptr [bx + 0x52d2]
00d9 sub ch, ch
00db cmp cx, di
00dd jle 0xf38
00df mov di, cx
00e1 mov word ptr [bp - 4], si
00e4 inc si
00e5 cmp si, 8
00e8 jl 0xf04
00ea push ss
00eb pop ds
00ec mov si, word ptr [bp + 0xa]
00ef or di, di
00f1 je 0xf56
00f3 mov es, word ptr [0xc4e6]
00f7 mov bx, si
00f9 shl bx, 3
00fc add bx, word ptr [bp - 4]
00ff jmp 0xf68
0101 nop 
0102 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0107 mov bx, ax
0109 mov ax, si
010b shl ax, 3
010e add bx, ax
0110 mov es, word ptr [0xc4e6]
0114 mov al, byte ptr es:[bx + 0x24]
0119 cwde 
011a pop si
011b pop di
011c leave 
011d retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetForageDir', 'offset': 2736, 'source': None, 'size': 384}
- {'symbol': '_GetNestDir', 'offset': 3120, 'source': None, 'size': 547}
- {'symbol': '_GetRandDir', 'offset': 3954, 'source': 'src/recovered/wf_GetRandDir-2664e9d7f9.c', 'size': 179}
- {'symbol': '_GetDefendDir', 'offset': 4134, 'source': None, 'size': 365}
