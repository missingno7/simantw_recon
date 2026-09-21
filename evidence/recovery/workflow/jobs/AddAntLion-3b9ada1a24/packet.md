# Recovery task _AddAntLion

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 186 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 push 0x38
000b push di
000c push word ptr [bp + 6]
000f push 1
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
0016 add sp, 8
0019 xor si, si
001b mov es, word ptr [0xc57e]
001f mov al, byte ptr es:[si + 8]
0024 cwde 
0025 add ax, di
0027 mov word ptr [bp - 2], ax
002a push ax
002b mov es, word ptr [0xc580]
002f mov al, byte ptr es:[si]
0034 cwde 
0035 add ax, word ptr [bp + 6]
0038 mov word ptr [bp - 4], ax
003b push ax
003c push 1
003e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
0043 add sp, 6
0046 dec ax
0047 jne 0x43a3
0049 mov al, byte ptr [si + 0x25e8]
004d sub ah, ah
004f add ax, 0x30
0052 push ax
0053 push word ptr [bp - 2]
0056 push word ptr [bp - 4]
0059 push 1
005b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 94, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
0060 add sp, 8
0063 inc si
0064 cmp si, 8
0067 jl 0x435b
0069 mov <resolved loader operand; see bindings> ; [{'operand_offset': 106, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
006c mov ds, ax
006e mov al, byte ptr [bp + 6]
0071 mov <resolved loader operand; see bindings> ; [{'operand_offset': 114, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0074 mov es, cx
0076 mov bx, word ptr [0x8a88]
007a mov byte ptr es:[bx - 0x7f64], al
007f mov ax, di
0081 mov <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0084 mov es, cx
0086 mov byte ptr es:[bx - 0x7f44], al
008b xor al, al
008d mov <resolved loader operand; see bindings> ; [{'operand_offset': 142, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0090 mov es, cx
0092 mov byte ptr es:[bx + 0x7a68], al
0097 mov <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
009a mov es, cx
009c mov byte ptr es:[bx + 0x7d34], al
00a1 mov <resolved loader operand; see bindings> ; [{'operand_offset': 162, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00a4 mov es, cx
00a6 mov byte ptr es:[bx + 0x7d4e], al
00ab cmp bx, 9
00ae jge 0x43f4
00b0 inc word ptr [0x8a88]
00b4 push ss
00b5 pop ds
00b6 pop si
00b7 pop di
00b8 leave 
00b9 retf 
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

- {'symbol': '_InitAntLions', 'offset': 16582, 'source': None, 'size': 347}
- {'symbol': '_AddRandAntLion', 'offset': 16930, 'source': None, 'size': 285}
- {'symbol': '_DoAntLions', 'offset': 17402, 'source': None, 'size': 1758}
- {'symbol': '_SetAntLion', 'offset': 19160, 'source': None, 'size': 57}
