# Recovery task _Reproduce

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 165 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 push 4
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SGSRand
000d add sp, 2
0010 mov di, ax
0012 add di, word ptr [bp + 6]
0015 push 4
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SGSRand
001c add sp, 2
001f mov si, ax
0021 add si, word ptr [bp + 8]
0024 or di, di
0026 jge 0x3d76
0028 xor di, di
002a cmp di, 0xb
002d jle 0x3d7e
002f mov di, 0xb
0032 or si, si
0034 jge 0x3d84
0036 xor si, si
0038 cmp si, 0xf
003b jle 0x3d8c
003d mov si, 0xf
0040 cmp word ptr [bp + 6], di
0043 jne 0x3d96
0045 cmp word ptr [bp + 8], si
0048 je 0x3deb
004a cmp word ptr [bp + 0xa], 0
004e je 0x3dc4
0050 mov <resolved loader operand; see bindings> ; [{'operand_offset': 81, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0053 mov ds, ax
0055 mov bx, di
0057 shl bx, 4
005a add bx, si
005c add bx, 0x164
0060 mov word ptr [bp - 4], bx
0063 mov word ptr [bp - 2], ds
0066 cmp byte ptr [bx], 0
0069 jne 0x3de9
006b mov <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006e mov es, ax
0070 inc word ptr es:[0x9c80]
0075 jmp 0x3de9
0077 nop 
0078 mov <resolved loader operand; see bindings> ; [{'operand_offset': 121, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
007b mov ds, ax
007d mov bx, di
007f shl bx, 4
0082 add bx, si
0084 add bx, 0xa4
0088 mov word ptr [bp - 8], bx
008b mov word ptr [bp - 6], ds
008e cmp byte ptr [bx], 0
0091 jne 0x3de9
0093 mov <resolved loader operand; see bindings> ; [{'operand_offset': 148, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0096 mov es, ax
0098 inc word ptr es:[0x80d4]
009d inc byte ptr [bx]
009f push ss
00a0 pop ds
00a1 pop si
00a2 pop di
00a3 leave 
00a4 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimColonies', 'offset': 13816, 'source': None, 'size': 1771}
- {'symbol': '_GetNearbyPatches', 'offset': 15588, 'source': None, 'size': 103}
- {'symbol': '_StartMigrate', 'offset': 15858, 'source': None, 'size': 121}
- {'symbol': '_EndMigrate', 'offset': 15980, 'source': None, 'size': 139}
