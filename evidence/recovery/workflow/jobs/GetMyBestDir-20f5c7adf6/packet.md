# Recovery task _GetMyBestDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 399 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov bx, 0x72e4
0009 mov es, word ptr [0xc3f6]
000d mov word ptr [bp - 0xc], bx
0010 mov word ptr [bp - 0xa], es
0013 cmp word ptr es:[bx], 0
0017 jge 0x8dd2
0019 mov di, word ptr [bp + 0xc]
001c mov si, word ptr [bp + 0xe]
001f push si
0020 push di
0021 push word ptr [bp + 0xa]
0024 push word ptr [bp + 8]
0027 push word ptr [bp + 6]
002a nop 
002b push cs
002c call 0x8828 ; _GetMyBestDirs
002f add sp, 0xa
0032 mov word ptr [bp - 2], ax
0035 cmp ax, 0xfffe
0038 je 0x8d77
003a jmp 0x8ec2
003d les bx, ptr [bp - 0xc]
0040 cmp word ptr es:[bx], ax
0043 je 0x8d82
0045 jmp 0x8ec2
0048 push si
0049 push di
004a push word ptr [bp + 0xa]
004d push word ptr [bp + 8]
0050 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 83, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
0055 add sp, 8
0058 dec ax
0059 mov es, word ptr [0xc3f8]
005d mov word ptr es:[0xa0d8], ax
0061 les bx, ptr [bp - 0xc]
0064 mov word ptr es:[bx], 0x10
0069 mov es, word ptr [0xc3fa]
006d mov word ptr es:[0x78a4], 0
0074 push si
0075 push di
0076 push word ptr [bp + 0xa]
0079 push word ptr [bp + 8]
007c push word ptr [bp + 6]
007f push <resolved loader operand; see bindings> ; [{'operand_offset': 128, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0082 push 0xa0d8
0085 push es
0086 push 0x78a4
0089 nop 
008a push cs
008b call 0x8928 ; _GetMyRandDirs
008e add sp, 0x12
0091 mov word ptr [bp - 2], ax
0094 jmp 0x8ec2
0097 nop 
0098 mov di, word ptr [bp + 0xa]
009b mov word ptr [bp - 6], 0
00a0 push word ptr [bp + 0xe]
00a3 push word ptr [bp + 0xc]
00a6 push di
00a7 push word ptr [bp + 8]
00aa push word ptr [bp + 6]
00ad nop 
00ae push cs
00af call 0x8828 ; _GetMyBestDirs
00b2 add sp, 0xa
00b5 mov si, ax
00b7 or si, si
00b9 jge 0x8df8
00bb jmp 0x8e92
00be mov es, word ptr [0xc3ca]
00c2 mov al, byte ptr es:[si]
00c7 cwde 
00c8 add ax, word ptr [bp + 8]
00cb mov word ptr [bp - 2], ax
00ce mov es, word ptr [0xc3c4]
00d2 mov al, byte ptr es:[si + 8]
00d7 cwde 
00d8 add ax, di
00da mov word ptr [bp - 4], ax
00dd or si, si
00df jl 0x8e92
00e1 mov di, word ptr [bp - 6]
00e4 cmp di, 0x40
00e7 jge 0x8e5f
00e9 push word ptr [bp + 0xe]
00ec push word ptr [bp + 0xc]
00ef push word ptr [bp - 4]
00f2 push word ptr [bp - 2]
00f5 push word ptr [bp + 6]
00f8 nop 
00f9 push cs
00fa call 0x8828 ; _GetMyBestDirs
00fd add sp, 0xa
0100 mov si, ax
0102 or si, si
0104 jl 0x8e5a
0106 mov es, word ptr [0xc3ca]
010a mov al, byte ptr es:[si]
010f cwde 
0110 add word ptr [bp - 2], ax
0113 mov es, word ptr [0xc3c4]
0117 mov al, byte ptr es:[si + 8]
011c cwde 
011d add word ptr [bp - 4], ax
0120 inc di
0121 or si, si
0123 jge 0x8e1e
0125 or si, si
0127 jl 0x8e66
0129 mov si, 0xffff
012c cmp si, -2
012f jne 0x8e98
0131 push word ptr [bp + 0xe]
0134 push word ptr [bp + 0xc]
0137 push word ptr [bp + 0xa]
013a push word ptr [bp + 8]
013d push word ptr [bp + 6]
0140 push <resolved loader operand; see bindings> ; [{'operand_offset': 321, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0143 push 0xa0d8
0146 push <resolved loader operand; see bindings> ; [{'operand_offset': 327, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0149 push 0x78a4
014c nop 
014d push cs
014e call 0x8928 ; _GetMyRandDirs
0151 add sp, 0x12
0154 jmp 0x8eb7
0156 nop 
0157 nop 
0158 mov di, word ptr [bp - 6]
015b jmp 0x8e5f
015d nop 
015e les bx, ptr [bp - 0xc]
0161 mov word ptr es:[bx], 0xffff
0166 push word ptr [bp + 0xe]
0169 push word ptr [bp + 0xc]
016c push word ptr [bp + 0xa]
016f push word ptr [bp + 8]
0172 push word ptr [bp + 6]
0175 nop 
0176 push cs
0177 call 0x8828 ; _GetMyBestDirs
017a add sp, 0xa
017d mov si, ax
017f mov word ptr [bp - 2], si
0182 les bx, ptr [bp - 0xc]
0185 dec word ptr es:[bx]
0188 mov ax, word ptr [bp - 2]
018b pop si
018c pop di
018d leave 
018e retf 
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

- {'symbol': '_GetMyNextRandDirs', 'offset': 35818, 'source': None, 'size': 244}
- {'symbol': '_GetMyInitialRandDir', 'offset': 36062, 'source': None, 'size': 91}
- {'symbol': '_GetMyDir', 'offset': 36554, 'source': None, 'size': 788}
- {'symbol': '_FillHolesBN', 'offset': 37342, 'source': None, 'size': 102}
