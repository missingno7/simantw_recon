# Recovery task _SetAntIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 216 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov dx, word ptr [bp + 6]
0007 cmp dx, 1
000a jg 0x589c
000c mov si, word ptr [bp + 8]
000f or si, si
0011 jge 0x5860
0013 jmp 0x591d
0016 mov <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0019 mov es, ax
001b cmp word ptr es:[0x80f0], si
0020 jg 0x586f
0022 jmp 0x591d
0025 mov <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0028 mov ds, ax
002a mov al, byte ptr [bp + 0xa]
002d mov byte ptr [si + 0x23a4], al
0031 mov al, byte ptr [bp + 0xc]
0034 mov byte ptr [si + 0x278e], al
0038 mov al, byte ptr [bp + 0xe]
003b mov byte ptr [si + 0x2f62], al
003f mov al, byte ptr [bp + 0x10]
0042 mov byte ptr [si + 0x2b78], al
0046 mov al, byte ptr [bp + 0x12]
0049 mov byte ptr [si + 0x334c], al
004d push ss
004e pop ds
004f pop si
0050 leave 
0051 retf 
0052 cmp dx, 2
0055 jne 0x58e2
0057 mov si, word ptr [bp + 8]
005a or si, si
005c jl 0x591d
005e mov <resolved loader operand; see bindings> ; [{'operand_offset': 95, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0061 mov es, ax
0063 cmp word ptr es:[0x99d4], si
0068 jle 0x591d
006a mov <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
006d mov ds, ax
006f mov al, byte ptr [bp + 0xa]
0072 mov byte ptr [si + 0x3736], al
0076 mov al, byte ptr [bp + 0xc]
0079 mov byte ptr [si + 0x392c], al
007d mov al, byte ptr [bp + 0xe]
0080 mov byte ptr [si + 0x3d18], al
0084 mov al, byte ptr [bp + 0x10]
0087 mov byte ptr [si + 0x3b22], al
008b mov al, byte ptr [bp + 0x12]
008e mov byte ptr [si + 0x3f0e], al
0092 push ss
0093 pop ds
0094 pop si
0095 leave 
0096 retf 
0097 nop 
0098 mov si, word ptr [bp + 8]
009b or si, si
009d jl 0x591d
009f mov <resolved loader operand; see bindings> ; [{'operand_offset': 160, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00a2 mov es, ax
00a4 cmp word ptr es:[0x72cc], si
00a9 jle 0x591d
00ab mov <resolved loader operand; see bindings> ; [{'operand_offset': 172, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ae mov ds, ax
00b0 mov al, byte ptr [bp + 0xa]
00b3 mov byte ptr [si + 0x4104], al
00b7 mov al, byte ptr [bp + 0xc]
00ba mov byte ptr [si + 0x42fa], al
00be mov al, byte ptr [bp + 0xe]
00c1 mov byte ptr [si + 0x46e6], al
00c5 mov al, byte ptr [bp + 0x10]
00c8 mov byte ptr [si + 0x44f0], al
00cc mov al, byte ptr [bp + 0x12]
00cf mov byte ptr [si + 0x48dc], al
00d3 push ss
00d4 pop ds
00d5 pop si
00d6 leave 
00d7 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsYellowAnt', 'offset': 22304, 'source': 'src/recovered/IsYellowAnt.c', 'size': 27}
- {'symbol': '_GetAntIndex', 'offset': 22332, 'source': None, 'size': 269}
- {'symbol': '_FindLifeIndex', 'offset': 22818, 'source': None, 'size': 217}
- {'symbol': '_FindAntIndex', 'offset': 23036, 'source': None, 'size': 213}
