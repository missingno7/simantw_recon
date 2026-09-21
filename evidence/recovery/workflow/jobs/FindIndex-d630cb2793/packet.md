# Recovery task _FindIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 237 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0009 mov es, ax
000b mov <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000e mov ds, ax
0010 mov word ptr [0x9e92], 0
0016 imul bx, word ptr [bp + 6], 0x7c
001a mov word ptr [bp - 6], bx
001d mov bx, word ptr es:[bx + 0x745c]
0022 dec bx
0023 mov word ptr [bp - 4], bx
0026 mov ax, bx
0028 inc ax
0029 jne 0x9d52
002b jmp 0x9e08
002e or bx, bx
0030 jl 0x9dbb
0032 mov word ptr [bp - 2], bx
0035 mov di, word ptr [bp + 0xa]
0038 mov ax, word ptr [0x9e92]
003b add ax, word ptr [bp - 2]
003e cdq 
003f sub ax, dx
0041 sar ax, 1
0043 mov si, ax
0045 shl ax, 3
0048 mov <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004b mov es, cx
004d mov bx, word ptr [bp - 6]
0050 add ax, word ptr es:[bx + 0x7458]
0055 mov dx, word ptr es:[bx + 0x745a]
005a mov <resolved loader operand; see bindings> ; [{'operand_offset': 91, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
005d mov es, cx
005f mov word ptr es:[0x9c7a], ax
0063 mov word ptr es:[0x9c7c], dx
0068 mov es, dx
006a mov bx, ax
006c mov ax, di
006e cmp byte ptr es:[bx + 6], al
0072 ja 0x9da3
0074 jne 0x9dac
0076 mov ax, word ptr [bp + 8]
0079 cmp word ptr es:[bx + 4], ax
007d jl 0x9dac
007f lea ax, [si - 1]
0082 mov word ptr [bp - 2], ax
0085 jmp 0x9db2
0087 nop 
0088 lea ax, [si + 1]
008b mov word ptr [0x9e92], ax
008e mov ax, word ptr [bp - 2]
0091 cmp word ptr [0x9e92], ax
0095 jle 0x9d5c
0097 mov <resolved loader operand; see bindings> ; [{'operand_offset': 152, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
009a mov es, ax
009c mov bx, word ptr [bp - 6]
009f mov ax, word ptr es:[bx + 0x7458]
00a4 mov dx, word ptr es:[bx + 0x745a]
00a9 mov cx, word ptr [0x9e92]
00ad mov bx, cx
00af shl cx, 3
00b2 add ax, cx
00b4 mov <resolved loader operand; see bindings> ; [{'operand_offset': 181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00b7 mov es, cx
00b9 mov word ptr es:[0x9c7a], ax
00bd mov word ptr es:[0x9c7c], dx
00c2 cmp bx, word ptr [bp - 4]
00c5 jg 0x9e08
00c7 mov ax, word ptr [bp + 8]
00ca les bx, ptr es:[0x9c7a]
00cf cmp word ptr es:[bx + 4], ax
00d3 jne 0x9e08
00d5 mov al, byte ptr [bp + 0xa]
00d8 cmp byte ptr es:[bx + 6], al
00dc jne 0x9e08
00de mov es, cx
00e0 mov ax, bx
00e2 jmp 0x9e0b
00e4 xor ax, ax
00e6 cdq 
00e7 push ss
00e8 pop ds
00e9 pop si
00ea pop di
00eb leave 
00ec retf 
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

- {'symbol': '_CreateIndex', 'offset': 39752, 'source': None, 'size': 251}
- {'symbol': '_CloseIndex', 'offset': 40004, 'source': None, 'size': 222}
- {'symbol': '_DeleteCurrentIndex', 'offset': 40466, 'source': None, 'size': 259}
- {'symbol': '_AddIndex', 'offset': 40726, 'source': None, 'size': 351}
