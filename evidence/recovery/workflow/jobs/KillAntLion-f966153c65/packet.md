# Recovery task _KillAntLion

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 160 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 push 0x3f
000b mov es, word ptr [0xc588]
000f mov al, byte ptr es:[di - 0x7f44]
0014 sub ah, ah
0016 push ax
0017 mov es, word ptr [0xc586]
001b mov al, byte ptr es:[di - 0x7f64]
0020 push ax
0021 push 1
0023 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMap
0028 add sp, 8
002b mov bx, 0x8a88
002e mov es, word ptr [0xc582]
0032 mov word ptr [bp - 4], bx
0035 mov word ptr [bp - 2], es
0038 cmp word ptr es:[bx], 0
003c jle 0x4bf4
003e mov si, di
0040 dec word ptr es:[bx]
0043 cmp word ptr es:[bx], di
0046 jle 0x4bf4
0048 mov <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004b mov ds, ax
004d mov <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0050 mov es, ax
0052 mov al, byte ptr es:[si - 0x7f63]
0057 mov byte ptr es:[si - 0x7f64], al
005c mov al, byte ptr [si - 0x7f43]
0060 mov byte ptr [si - 0x7f44], al
0064 mov <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0067 mov es, ax
0069 mov al, byte ptr es:[si + 0x7d4f]
006e mov byte ptr es:[si + 0x7d4e], al
0073 mov <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0076 mov es, ax
0078 mov al, byte ptr es:[si + 0x7a69]
007d mov byte ptr es:[si + 0x7a68], al
0082 mov <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0085 mov es, ax
0087 mov al, byte ptr es:[si + 0x7d35]
008c mov byte ptr es:[si + 0x7d34], al
0091 inc si
0092 mov es, word ptr [bp - 2]
0095 cmp word ptr es:[bx], si
0098 jg 0x4ba5
009a push ss
009b pop ds
009c pop si
009d pop di
009e leave 
009f retf 
```

## Known declaration examples

- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetAntLion', 'offset': 19160, 'source': None, 'size': 57}
- {'symbol': '_FindInLionList', 'offset': 19218, 'source': None, 'size': 69}
- {'symbol': '_InitPillar', 'offset': 19448, 'source': None, 'size': 228}
- {'symbol': '_DoPillar', 'offset': 19676, 'source': None, 'size': 1576}
