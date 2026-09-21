# Recovery task _GetAntIndex

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 269 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov dx, word ptr [bp + 6]
0007 cmp dx, 1
000a jg 0x5798
000c mov si, word ptr [bp + 8]
000f or si, si
0011 jge 0x5752
0013 jmp 0x5842
0016 mov <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0019 mov es, ax
001b cmp word ptr es:[0x80f0], si
0020 jg 0x5761
0022 jmp 0x5842
0025 mov <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0028 mov ds, ax
002a mov al, byte ptr [si + 0x23a4]
002e sub ah, ah
0030 les bx, ptr [bp + 0xa]
0033 mov word ptr es:[bx], ax
0036 mov al, byte ptr [si + 0x278e]
003a les bx, ptr [bp + 0xe]
003d mov word ptr es:[bx], ax
0040 mov al, byte ptr [si + 0x2f62]
0044 les bx, ptr [bp + 0x12]
0047 mov word ptr es:[bx], ax
004a mov al, byte ptr [si + 0x2b78]
004e les bx, ptr [bp + 0x16]
0051 mov word ptr es:[bx], ax
0054 mov al, byte ptr [si + 0x334c]
0058 jmp 0x5832
005b nop 
005c cmp dx, 2
005f jne 0x57ec
0061 mov si, word ptr [bp + 8]
0064 or si, si
0066 jge 0x57a7
0068 jmp 0x5842
006b mov <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
006e mov es, ax
0070 cmp word ptr es:[0x99d4], si
0075 jg 0x57b6
0077 jmp 0x5842
007a mov <resolved loader operand; see bindings> ; [{'operand_offset': 123, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
007d mov ds, ax
007f mov al, byte ptr [si + 0x3736]
0083 sub ah, ah
0085 les bx, ptr [bp + 0xa]
0088 mov word ptr es:[bx], ax
008b mov al, byte ptr [si + 0x392c]
008f les bx, ptr [bp + 0xe]
0092 mov word ptr es:[bx], ax
0095 mov al, byte ptr [si + 0x3d18]
0099 les bx, ptr [bp + 0x12]
009c mov word ptr es:[bx], ax
009f mov al, byte ptr [si + 0x3b22]
00a3 les bx, ptr [bp + 0x16]
00a6 mov word ptr es:[bx], ax
00a9 mov al, byte ptr [si + 0x3f0e]
00ad jmp 0x5832
00af nop 
00b0 mov si, word ptr [bp + 8]
00b3 or si, si
00b5 jl 0x5842
00b7 mov <resolved loader operand; see bindings> ; [{'operand_offset': 184, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
00ba mov es, ax
00bc cmp word ptr es:[0x72cc], si
00c1 jle 0x5842
00c3 mov <resolved loader operand; see bindings> ; [{'operand_offset': 196, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00c6 mov ds, ax
00c8 mov al, byte ptr [si + 0x4104]
00cc sub ah, ah
00ce les bx, ptr [bp + 0xa]
00d1 mov word ptr es:[bx], ax
00d4 mov al, byte ptr [si + 0x42fa]
00d8 les bx, ptr [bp + 0xe]
00db mov word ptr es:[bx], ax
00de mov al, byte ptr [si + 0x46e6]
00e2 les bx, ptr [bp + 0x12]
00e5 mov word ptr es:[bx], ax
00e8 mov al, byte ptr [si + 0x44f0]
00ec les bx, ptr [bp + 0x16]
00ef mov word ptr es:[bx], ax
00f2 mov al, byte ptr [si + 0x48dc]
00f6 sub ah, ah
00f8 les bx, ptr [bp + 0x1a]
00fb mov word ptr es:[bx], ax
00fe mov ax, 1
0101 push ss
0102 pop ds
0103 pop si
0104 leave 
0105 retf 
0106 xor ax, ax
0108 push ss
0109 pop ds
010a pop si
010b leave 
010c retf 
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

- {'symbol': '_IsValidLocation', 'offset': 22234, 'source': 'src/recovered/IsValidLocation.c', 'size': 70}
- {'symbol': '_IsYellowAnt', 'offset': 22304, 'source': 'src/recovered/IsYellowAnt.c', 'size': 27}
- {'symbol': '_SetAntIndex', 'offset': 22602, 'source': 'src/recovered/wf_SetAntIndex-965b821698.c', 'size': 216}
- {'symbol': '_FindLifeIndex', 'offset': 22818, 'source': 'src/recovered/wf_FindLifeIndex-3b1fa0607c.c', 'size': 217}
