# Recovery task _EndMigrate

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 139 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0009 mov es, ax
000b mov ax, word ptr es:[0x9cee]
000f mov word ptr [bp - 4], ax
0012 or ax, ax
0014 jl 0x3ef1
0016 mov ax, word ptr [bp + 8]
0019 sub ax, 0x42
001c mov cx, 0xa
001f cdq 
0020 idiv cx
0022 mov si, ax
0024 mov ax, word ptr [bp + 8]
0027 add ax, word ptr [bp + 6]
002a sub ax, 0xee
002d mov cx, 0x1c
0030 cdq 
0031 idiv cx
0033 mov di, ax
0035 or di, di
0037 jl 0x3ef1
0039 or si, si
003b jl 0x3ef1
003d cmp di, 0xb
0040 jg 0x3ef1
0042 cmp si, 0xf
0045 jg 0x3ef1
0047 mov <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
004a mov ds, ax
004c mov bx, word ptr [bp - 4]
004f shl bx, 4
0052 mov <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0055 mov es, ax
0057 add bx, word ptr es:[0x9d72]
005c mov al, byte ptr [bx + 0xa4]
0060 shr al, 1
0062 sub ah, ah
0064 sub byte ptr [bx + 0xa4], al
0068 mov bx, di
006a shl bx, 4
006d add bx, si
006f add bx, 0xa4
0073 mov cl, byte ptr [bx]
0075 add cx, ax
0077 cmp cx, 0xfb
007b jge 0x3eee
007d mov byte ptr [bx], cl
007f jmp 0x3ef1
0081 nop 
0082 mov byte ptr [bx], 0xfa
0085 push ss
0086 pop ds
0087 pop si
0088 pop di
0089 leave 
008a retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_ClearLifeB-f9a6e1c57a.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Reproduce', 'offset': 15692, 'source': None, 'size': 165}
- {'symbol': '_StartMigrate', 'offset': 15858, 'source': None, 'size': 121}
- {'symbol': '_InitSow', 'offset': 16120, 'source': None, 'size': 146}
- {'symbol': '_DoSow', 'offset': 16266, 'source': None, 'size': 315}
