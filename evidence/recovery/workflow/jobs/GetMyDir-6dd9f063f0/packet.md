# Recovery task _GetMyDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 788 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 cmp word ptr [bp + 6], 1
000a jle 0x8ed9
000c jmp 0x8f90
000f mov dx, word ptr [bp + 0xc]
0012 cmp dx, 1
0015 jg 0x8f4e
0017 mov bx, 0x72e4
001a mov es, word ptr [0xc3f6]
001e mov word ptr [bp - 0xc], bx
0021 mov word ptr [bp - 0xa], es
0024 cmp word ptr es:[bx], 0
0028 jge 0x8ef7
002a jmp 0x8fae
002d push word ptr [bp + 0x10]
0030 push word ptr [bp + 0xe]
0033 push word ptr [bp + 0xa]
0036 push word ptr [bp + 8]
0039 push word ptr [bp + 6]
003c lea ax, [bp - 4]
003f push ss
0040 push ax
0041 nop 
0042 push cs
0043 call 0x8b40 ; _CheckMyBestDirs
0046 add sp, 0xe
0049 cmp ax, 0xfffe
004c jne 0x8f1b
004e jmp 0x904e
0051 les bx, ptr [bp - 0xc]
0054 mov word ptr es:[bx], 0xffff
0059 push word ptr [bp + 0x10]
005c push word ptr [bp + 0xe]
005f push word ptr [bp + 0xa]
0062 push word ptr [bp + 8]
0065 push word ptr [bp + 6]
0068 nop 
0069 push cs
006a call 0x8828 ; _GetMyBestDirs
006d add sp, 0xa
0070 mov si, ax
0072 mov word ptr [bp - 2], si
0075 les bx, ptr [bp - 0xc]
0078 dec word ptr es:[bx]
007b mov dx, word ptr [bp - 2]
007e mov ax, dx
0080 pop si
0081 pop di
0082 leave 
0083 retf 
0084 cmp dx, 2
0087 jne 0x8f64
0089 mov es, word ptr [0xc3f0]
008d mov ax, word ptr es:[0x835a]
0091 mov word ptr [bp - 2], ax
0094 mov ax, word ptr es:[0x835c]
0098 jmp 0x8f73
009a mov es, word ptr [0xc3f2]
009e mov ax, word ptr es:[0x835e]
00a2 mov word ptr [bp - 2], ax
00a5 mov ax, word ptr es:[0x8360]
00a9 mov word ptr [bp - 4], ax
00ac mov bx, 0x72e4
00af mov es, word ptr [0xc3f6]
00b3 mov word ptr [bp - 0xc], bx
00b6 mov word ptr [bp - 0xa], es
00b9 cmp word ptr es:[bx], 0
00bd jge 0x8f8c
00bf jmp 0x90a1
00c2 push ax
00c3 jmp 0x9121
00c6 mov ax, word ptr [bp + 6]
00c9 cmp word ptr [bp + 0xc], ax
00cc je 0x8f9b
00ce jmp 0x9074
00d1 mov bx, 0x72e4
00d4 mov es, word ptr [0xc3f6]
00d8 mov word ptr [bp - 0xc], bx
00db mov word ptr [bp - 0xa], es
00de cmp word ptr es:[bx], 0
00e2 jge 0x902c
00e4 mov di, word ptr [bp + 0xe]
00e7 mov si, word ptr [bp + 0x10]
00ea push si
00eb push di
00ec push word ptr [bp + 0xa]
00ef push word ptr [bp + 8]
00f2 push word ptr [bp + 6]
00f5 nop 
00f6 push cs
00f7 call 0x8828 ; _GetMyBestDirs
00fa add sp, 0xa
00fd mov word ptr [bp - 2], ax
0100 cmp ax, 0xfffe
0103 je 0x8fd2
0105 jmp 0x8f45
0108 les bx, ptr [bp - 0xc]
010b cmp word ptr es:[bx], ax
010e je 0x8fdd
0110 jmp 0x8f45
0113 push si
0114 push di
0115 push word ptr [bp + 0xa]
0118 push word ptr [bp + 8]
011b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 286, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
0120 add sp, 8
0123 dec ax
0124 mov es, word ptr [0xc3f8]
0128 mov word ptr es:[0xa0d8], ax
012c les bx, ptr [bp - 0xc]
012f mov word ptr es:[bx], 0x10
0134 mov es, word ptr [0xc3fa]
0138 mov word ptr es:[0x78a4], 0
013f push si
0140 push di
0141 push word ptr [bp + 0xa]
0144 push word ptr [bp + 8]
0147 push word ptr [bp + 6]
014a push <resolved loader operand; see bindings> ; [{'operand_offset': 331, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
014d push 0xa0d8
0150 push es
0151 push 0x78a4
0154 nop 
0155 push cs
0156 call 0x8928 ; _GetMyRandDirs
0159 add sp, 0x12
015c mov word ptr [bp - 2], ax
015f jmp 0x8f45
0162 push word ptr [bp + 0x10]
0165 push word ptr [bp + 0xe]
0168 push word ptr [bp + 0xa]
016b push word ptr [bp + 8]
016e push ax
016f lea ax, [bp - 4]
0172 push ss
0173 push ax
0174 nop 
0175 push cs
0176 call 0x8b40 ; _CheckMyBestDirs
0179 add sp, 0xe
017c cmp ax, 0xfffe
017f je 0x904e
0181 jmp 0x8f1b
0184 push word ptr [bp + 0x10]
0187 push word ptr [bp + 0xe]
018a push word ptr [bp + 0xa]
018d push word ptr [bp + 8]
0190 push word ptr [bp + 6]
0193 push <resolved loader operand; see bindings> ; [{'operand_offset': 404, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0196 push 0xa0d8
0199 push <resolved loader operand; see bindings> ; [{'operand_offset': 410, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
019c push 0x78a4
019f nop 
01a0 push cs
01a1 call 0x8928 ; _GetMyRandDirs
01a4 add sp, 0x12
01a7 jmp 0x8f3a
01aa cmp ax, 2
01ad je 0x907c
01af jmp 0x9164
01b2 mov es, word ptr [0xc3ee]
01b6 mov ax, word ptr es:[0x8352]
01ba mov word ptr [bp - 2], ax
01bd mov ax, word ptr es:[0x8354]
01c1 mov word ptr [bp - 4], ax
01c4 mov bx, 0x72e4
01c7 mov es, word ptr [0xc3f6]
01cb mov word ptr [bp - 0xc], bx
01ce mov word ptr [bp - 0xa], es
01d1 cmp word ptr es:[bx], 0
01d5 jge 0x911e
01d7 mov di, word ptr [bp + 8]
01da mov si, word ptr [bp + 0xa]
01dd push ax
01de push word ptr [bp - 2]
01e1 push si
01e2 push di
01e3 push word ptr [bp + 6]
01e6 nop 
01e7 push cs
01e8 call 0x8828 ; _GetMyBestDirs
01eb add sp, 0xa
01ee mov word ptr [bp - 6], ax
01f1 cmp ax, 0xfffe
01f4 je 0x90c3
01f6 jmp 0x91d5
01f9 les bx, ptr [bp - 0xc]
01fc cmp word ptr es:[bx], ax
01ff je 0x90ce
0201 jmp 0x91d5
0204 push word ptr [bp - 4]
0207 push word ptr [bp - 2]
020a push si
020b push di
020c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 527, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
0211 add sp, 8
0214 dec ax
0215 mov es, word ptr [0xc3f8]
0219 mov word ptr es:[0xa0d8], ax
021d les bx, ptr [bp - 0xc]
0220 mov word ptr es:[bx], 0x10
0225 mov es, word ptr [0xc3fa]
0229 mov word ptr es:[0x78a4], 0
0230 push word ptr [bp - 4]
0233 push word ptr [bp - 2]
0236 push si
0237 push di
0238 push word ptr [bp + 6]
023b push <resolved loader operand; see bindings> ; [{'operand_offset': 572, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
023e push 0xa0d8
0241 push es
0242 push 0x78a4
0245 nop 
0246 push cs
0247 call 0x8928 ; _GetMyRandDirs
024a add sp, 0x12
024d mov word ptr [bp - 6], ax
0250 jmp 0x91d5
0253 nop 
0254 push word ptr [bp - 4]
0257 push word ptr [bp - 2]
025a push word ptr [bp + 0xa]
025d push word ptr [bp + 8]
0260 push word ptr [bp + 6]
0263 lea ax, [bp - 8]
0266 push ss
0267 push ax
0268 nop 
0269 push cs
026a call 0x8b40 ; _CheckMyBestDirs
026d add sp, 0xe
0270 cmp ax, 0xfffe
0273 jne 0x91ab
0275 push word ptr [bp - 4]
0278 push word ptr [bp - 2]
027b push word ptr [bp + 0xa]
027e push word ptr [bp + 8]
0281 push word ptr [bp + 6]
0284 push <resolved loader operand; see bindings> ; [{'operand_offset': 645, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0287 push 0xa0d8
028a push <resolved loader operand; see bindings> ; [{'operand_offset': 651, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
028d push 0x78a4
0290 nop 
0291 push cs
0292 call 0x8928 ; _GetMyRandDirs
0295 add sp, 0x12
0298 jmp 0x91ca
029a mov es, word ptr [0xc3f4]
029e mov ax, word ptr es:[0x8356]
02a2 mov word ptr [bp - 2], ax
02a5 mov ax, word ptr es:[0x8358]
02a9 mov word ptr [bp - 4], ax
02ac mov bx, 0x72e4
02af mov es, word ptr [0xc3f6]
02b3 mov word ptr [bp - 0xc], bx
02b6 mov word ptr [bp - 0xa], es
02b9 cmp word ptr es:[bx], 0
02bd jge 0x918c
02bf jmp 0x90a1
02c2 push ax
02c3 push word ptr [bp - 2]
02c6 push word ptr [bp + 0xa]
02c9 push word ptr [bp + 8]
02cc push word ptr [bp + 6]
02cf lea ax, [bp - 8]
02d2 push ss
02d3 push ax
02d4 nop 
02d5 push cs
02d6 call 0x8b40 ; _CheckMyBestDirs
02d9 add sp, 0xe
02dc cmp ax, 0xfffe
02df je 0x913f
02e1 les bx, ptr [bp - 0xc]
02e4 mov word ptr es:[bx], 0xffff
02e9 push word ptr [bp - 4]
02ec push word ptr [bp - 2]
02ef push word ptr [bp + 0xa]
02f2 push word ptr [bp + 8]
02f5 push word ptr [bp + 6]
02f8 nop 
02f9 push cs
02fa call 0x8828 ; _GetMyBestDirs
02fd add sp, 0xa
0300 mov si, ax
0302 mov word ptr [bp - 6], si
0305 les bx, ptr [bp - 0xc]
0308 dec word ptr es:[bx]
030b mov dx, word ptr [bp - 6]
030e mov ax, dx
0310 pop si
0311 pop di
0312 leave 
0313 retf 
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

- {'symbol': '_GetMyInitialRandDir', 'offset': 36062, 'source': None, 'size': 91}
- {'symbol': '_GetMyBestDir', 'offset': 36154, 'source': None, 'size': 399}
- {'symbol': '_FillHolesBN', 'offset': 37342, 'source': None, 'size': 102}
- {'symbol': '_FillHolesRN', 'offset': 37444, 'source': None, 'size': 102}
