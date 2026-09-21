# Recovery task _BuildAntListA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 162 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 xor bx, bx
0008 mov es, word ptr [0xc426]
000c mov word ptr es:[0x80f0], bx
0011 mov word ptr [bp - 4], bx
0014 mov <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0017 mov es, ax
0019 xor si, si
001b mov word ptr [bp - 2], bx
001e mov bx, word ptr [bp - 4]
0021 mov al, byte ptr [bx + si + 0x68e8]
0025 sub ah, ah
0027 mov di, ax
0029 or di, di
002b je 0x30c9
002d push di
002e nop 
002f push cs
0030 call 0x5720 ; _IsYellowAnt
0033 add sp, 2
0036 dec ax
0037 je 0x30c4
0039 mov <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
003c mov es, ax
003e mov <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0041 mov ds, ax
0043 mov al, byte ptr [bp - 2]
0046 mov bx, word ptr [0x80f0]
004a mov byte ptr es:[bx + 0x23a4], al
004f mov ax, si
0051 mov byte ptr es:[bx + 0x278e], al
0056 mov byte ptr es:[bx + 0x2b78], 2
005c mov ax, di
005e mov byte ptr es:[bx + 0x2f62], al
0063 mov byte ptr es:[bx + 0x334c], 0
0069 cmp bx, 0x3e5
006d jge 0x30b9
006f inc word ptr [0x80f0]
0073 inc si
0074 cmp si, 0x40
0077 jge 0x30d0
0079 push ss
007a pop ds
007b jmp 0x3064
007d nop 
007e mov <resolved loader operand; see bindings> ; [{'operand_offset': 127, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0081 mov es, ax
0083 mov <resolved loader operand; see bindings> ; [{'operand_offset': 132, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0086 mov ds, ax
0088 jmp 0x30b9
008a push ss
008b pop ds
008c mov bx, word ptr [bp - 2]
008f inc bx
0090 add word ptr [bp - 4], 0x40
0094 cmp word ptr [bp - 4], 0x2000
0099 jge 0x30e4
009b jmp 0x305f
009e pop si
009f pop di
00a0 leave 
00a1 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far IsYellowAnt(int ant);` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AddAntToRList', 'offset': 12196, 'source': 'src/recovered/wf_AddAntToRList-63e08ccbad.c', 'size': 89}
- {'symbol': '_GetFromAlist', 'offset': 12286, 'source': None, 'size': 72}
- {'symbol': '_ClearListB', 'offset': 12520, 'source': 'src/recovered/ClearListB.c', 'size': 12}
- {'symbol': '_ClearListR', 'offset': 12532, 'source': 'src/recovered/ClearListR.c', 'size': 12}
