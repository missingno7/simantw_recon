# Recovery task _DoDigOutAntA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 502 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 4]
0009 mov es, word ptr [0xc318]
000d mov al, byte ptr es:[si + 0x23a4]
0012 sub ah, ah
0014 mov word ptr [bp - 4], ax
0017 mov al, byte ptr es:[si + 0x278e]
001c mov word ptr [bp - 6], ax
001f mov al, byte ptr es:[si + 0x2f62]
0024 mov di, ax
0026 mov cx, di
0028 and ax, 0xf8
002b mov word ptr [bp - 0xc], ax
002e and cx, 0x78
0031 sar cx, 3
0034 mov word ptr [bp - 2], cx
0037 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 58, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
003c mov bx, ax
003e mov ax, di
0040 and ax, 7
0043 shl ax, 3
0046 mov word ptr [bp - 0x10], ax
0049 add bx, ax
004b mov es, word ptr [0xc32e]
004f mov al, byte ptr es:[bx + 0x24]
0054 cwde 
0055 mov word ptr [bp - 0xe], ax
0058 push word ptr [bp - 6]
005b push word ptr [bp - 4]
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Bounce
0063 add sp, 4
0066 mov word ptr [bp - 8], ax
0069 or ax, ax
006b je 0x14f8
006d mov al, byte ptr [bp - 8]
0070 dec al
0072 and ax, 7
0075 mov word ptr [bp - 0xe], ax
0078 mov es, word ptr [0xc31e]
007c mov bx, word ptr [bp - 0xe]
007f mov al, byte ptr es:[bx]
0084 cwde 
0085 add ax, word ptr [bp - 4]
0088 mov word ptr [bp - 8], ax
008b mov es, word ptr [0xc31c]
008f mov al, byte ptr es:[bx + 8]
0094 cwde 
0095 add ax, word ptr [bp - 6]
0098 mov word ptr [bp - 0xa], ax
009b cmp word ptr [bp - 2], 5
009f je 0x1546
00a1 cmp word ptr [bp - 2], 9
00a5 je 0x1546
00a7 push di
00a8 push word ptr [bp - 2]
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
00b0 add sp, 4
00b3 mov es, word ptr [0xc318]
00b7 mov byte ptr es:[si + 0x2b78], al
00bc mov byte ptr es:[si + 0x334c], 0
00c2 pop si
00c3 pop di
00c4 leave 
00c5 ret 
00c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 201, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
00cb or ax, ax
00cd jne 0x158a
00cf mov es, word ptr [0xc318]
00d3 sub byte ptr es:[si + 0x2f62], 0x18
00d9 push di
00da push word ptr [bp - 2]
00dd lcall <resolved loader operand; see bindings> ; [{'operand_offset': 224, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewMode
00e2 add sp, 4
00e5 mov es, word ptr [0xc318]
00e9 mov byte ptr es:[si + 0x2b78], al
00ee mov byte ptr es:[si + 0x334c], 0
00f4 mov al, byte ptr es:[si + 0x2f62]
00f9 mov bx, word ptr [bp - 4]
00fc shl bx, 6
00ff add bx, word ptr [bp - 6]
0102 mov byte ptr [bx + 0x68e8], al
0106 pop si
0107 pop di
0108 leave 
0109 ret 
010a mov bx, word ptr [bp - 8]
010d shl bx, 6
0110 add bx, word ptr [bp - 0xa]
0113 mov al, byte ptr [bx + 0x28e8]
0117 sub ah, ah
0119 mov es, word ptr [0xc32c]
011d cmp ax, word ptr es:[0x7604]
0122 jle 0x15c6
0124 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 295, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0129 mov bx, ax
012b add bx, word ptr [bp - 0x10]
012e mov es, word ptr [0xc32e]
0132 mov al, byte ptr es:[bx + 0x24]
0137 or al, byte ptr [bp - 0xc]
013a mov es, word ptr [0xc318]
013e mov byte ptr es:[si + 0x2f62], al
0143 jmp 0x1579
0145 nop 
0146 mov <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0149 mov es, ax
014b cmp byte ptr [bx + 0x68e8], 0
0150 jne 0x1646
0152 mov al, byte ptr [bp - 0xe]
0155 or al, byte ptr [bp - 0xc]
0158 mov byte ptr [bx + 0x68e8], al
015c mov byte ptr es:[si + 0x2f62], al
0161 mov bx, word ptr [bp - 4]
0164 shl bx, 6
0167 add bx, word ptr [bp - 6]
016a mov byte ptr [bx + 0x68e8], 0
016f mov al, byte ptr [bp - 8]
0172 mov byte ptr es:[si + 0x23a4], al
0177 mov al, byte ptr [bp - 0xa]
017a mov byte ptr es:[si + 0x278e], al
017f cmp byte ptr es:[si + 0x334c], 0
0185 je 0x1672
0187 dec byte ptr es:[si + 0x334c]
018c mov ax, di
018e test al, 0x80
0190 je 0x162e
0192 mov es, word ptr [0xc318]
0196 mov al, byte ptr es:[si + 0x334c]
019b sub ah, ah
019d push ax
019e push word ptr [bp - 0xa]
01a1 push word ptr [bp - 8]
01a4 call 0x94f6 ; _JamScentRN
01a7 add sp, 6
01aa pop si
01ab pop di
01ac leave 
01ad ret 
01ae mov es, word ptr [0xc318]
01b2 mov al, byte ptr es:[si + 0x334c]
01b7 sub ah, ah
01b9 push ax
01ba push word ptr [bp - 0xa]
01bd push word ptr [bp - 8]
01c0 call 0x94b6 ; _JamScentBN
01c3 jmp 0x1627
01c5 nop 
01c6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 457, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
01cb mov bx, ax
01cd add bx, word ptr [bp - 0x10]
01d0 mov es, word ptr [0xc32e]
01d4 mov al, byte ptr es:[bx + 0x24]
01d9 or al, byte ptr [bp - 0xc]
01dc mov es, word ptr [0xc318]
01e0 mov byte ptr es:[si + 0x2f62], al
01e5 mov si, word ptr [bp - 4]
01e8 shl si, 6
01eb mov bx, word ptr [bp - 6]
01ee mov byte ptr [bx + si + 0x68e8], al
01f2 pop si
01f3 pop di
01f4 leave 
01f5 ret 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandB-ce86a18bea.c
- `extern int far SRand8(void);` — src/recovered/wf_DoRandR-fc777553ef.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoRandAntA', 'offset': 3686, 'source': None, 'size': 974}
- {'symbol': '_DoRandAntAA', 'offset': 4660, 'source': None, 'size': 588}
- {'symbol': '_DoToNestAnt', 'offset': 5750, 'source': None, 'size': 915}
- {'symbol': '_DoToAlarm', 'offset': 6666, 'source': None, 'size': 682}
