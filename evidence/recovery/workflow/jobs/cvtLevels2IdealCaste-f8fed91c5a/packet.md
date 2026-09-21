# Recovery task _cvtLevels2IdealCaste

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 156 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov si, word ptr [bp + 6]
0008 push 0
000a push -1
000c mov ax, 0x64
000f mov es, word ptr [0xc128]
0013 mul word ptr es:[0x9b66]
0018 add ax, 0x3fff
001b adc dx, 0
001e push dx
001f push ax
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0025 mov es, word ptr [bp + 8]
0028 mov word ptr es:[si], ax
002b push 0
002d push -1
002f mov ax, 0x64
0032 mov cx, es
0034 mov es, word ptr [0xc128]
0038 mul word ptr es:[0x9b68]
003d add ax, 0x3fff
0040 adc dx, 0
0043 push dx
0044 push ax
0045 mov di, cx
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 74, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
004c mov es, di
004e mov word ptr es:[si + 2], ax
0052 push 0
0054 push -1
0056 mov es, word ptr [0xc128]
005a mov ax, 0x32
005d mul word ptr es:[0x9b64]
0062 add ax, 0x3fff
0065 adc dx, 0
0068 push dx
0069 push ax
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
006f mov es, di
0071 mov word ptr es:[si + 4], ax
0075 push 0
0077 push -1
0079 mov ax, 0x32
007c mov es, word ptr [0xc128]
0080 mul word ptr es:[0x9b64]
0085 add ax, 0x3fff
0088 adc dx, 0
008b push dx
008c push ax
008d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFuldiv
0092 mov es, di
0094 mov word ptr es:[si + 6], ax
0098 pop si
0099 pop di
009a leave 
009b retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_CasteControlClosed', 'offset': 50990, 'source': None, 'size': 149}
- {'symbol': '_DrawControlLevels', 'offset': 51140, 'source': None, 'size': 538}
- {'symbol': '_GetTriLatDist', 'offset': 51834, 'source': None, 'size': 299}
- {'symbol': '_SetTriLatPoint', 'offset': 52134, 'source': None, 'size': 221}
