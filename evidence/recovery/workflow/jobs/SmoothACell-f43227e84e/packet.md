# Recovery task _SmoothACell

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 944 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 mov word ptr [bp - 6], 0
000e or si, si
0010 jl 0x8920
0012 mov di, word ptr [bp + 8]
0015 cmp si, 0x3f
0018 jg 0x8923
001a lea ax, [di - 1]
001d or ax, ax
001f jl 0x8923
0021 cmp ax, 0x1f
0024 jg 0x8923
0026 mov dx, 1
0029 jmp 0x8925
002b nop 
002c mov di, word ptr [bp + 8]
002f xor dx, dx
0031 or dx, dx
0033 jne 0x893c
0035 mov word ptr [bp - 4], 0xffff
003a mov <resolved loader operand; see bindings> ; [{'operand_offset': 59, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
003d mov es, ax
003f mov <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0042 mov ds, ax
0044 jmp 0x89c6
0047 nop 
0048 mov <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
004b mov ds, ax
004d mov al, byte ptr [0x8605]
0050 cwde 
0051 or ax, ax
0053 je 0x8960
0055 dec ax
0056 je 0x8974
0058 dec ax
0059 je 0x8988
005b dec ax
005c je 0x899c
005e dec ax
005f je 0x89b0
0061 mov cx, word ptr [bp - 2]
0064 mov <resolved loader operand; see bindings> ; [{'operand_offset': 101, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0067 mov es, ax
0069 jmp 0x89c3
006b nop 
006c mov <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
006f mov es, ax
0071 mov bx, si
0073 shl bx, 5
0076 add bx, di
0078 mov cl, byte ptr es:[bx + 0x62d1]
007d jmp 0x89c1
007f nop 
0080 mov <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0083 mov es, ax
0085 mov bx, si
0087 shl bx, 5
008a add bx, di
008c mov cl, byte ptr es:[bx + 0x6ad1]
0091 jmp 0x89c1
0093 nop 
0094 mov <resolved loader operand; see bindings> ; [{'operand_offset': 149, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0097 mov es, ax
0099 mov bx, si
009b shl bx, 5
009e add bx, di
00a0 mov cl, byte ptr es:[bx + 0x72d1]
00a5 jmp 0x89c1
00a7 nop 
00a8 mov <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00ab mov es, ax
00ad mov bx, si
00af shl bx, 5
00b2 add bx, di
00b4 mov cl, byte ptr es:[bx + 0x7ad1]
00b9 jmp 0x89c1
00bb nop 
00bc mov <resolved loader operand; see bindings> ; [{'operand_offset': 189, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
00bf mov es, ax
00c1 mov bx, si
00c3 shl bx, 5
00c6 add bx, di
00c8 mov cl, byte ptr es:[bx + 0x52d1]
00cd sub ch, ch
00cf mov word ptr [bp - 4], cx
00d2 mov ax, word ptr [bp - 4]
00d5 mov word ptr [bp - 6], ax
00d8 lea ax, [si + 1]
00db or ax, ax
00dd jl 0x89e6
00df cmp ax, 0x3f
00e2 jg 0x89e6
00e4 or di, di
00e6 jl 0x89e6
00e8 cmp di, 0x1f
00eb jg 0x89e6
00ed mov dx, 1
00f0 jmp 0x89e8
00f2 xor dx, dx
00f4 or dx, dx
00f6 jne 0x89f4
00f8 mov word ptr [bp - 2], 0xffff
00fd jmp 0x8a57
00ff nop 
0100 mov al, byte ptr [0x8605]
0103 cwde 
0104 or ax, ax
0106 je 0x8a0e
0108 dec ax
0109 je 0x8a1c
010b dec ax
010c je 0x8a2a
010e dec ax
010f je 0x8a38
0111 dec ax
0112 je 0x8a46
0114 mov cx, word ptr [bp - 4]
0117 jmp 0x8a54
0119 nop 
011a mov bx, si
011c shl bx, 5
011f add bx, di
0121 mov cl, byte ptr es:[bx + 0x62f2]
0126 jmp 0x8a52
0128 mov bx, si
012a shl bx, 5
012d add bx, di
012f mov cl, byte ptr es:[bx + 0x6af2]
0134 jmp 0x8a52
0136 mov bx, si
0138 shl bx, 5
013b add bx, di
013d mov cl, byte ptr es:[bx + 0x72f2]
0142 jmp 0x8a52
0144 mov bx, si
0146 shl bx, 5
0149 add bx, di
014b mov cl, byte ptr es:[bx + 0x7af2]
0150 jmp 0x8a52
0152 mov bx, si
0154 shl bx, 5
0157 add bx, di
0159 mov cl, byte ptr es:[bx + 0x52f2]
015e sub ch, ch
0160 mov word ptr [bp - 2], cx
0163 mov ax, word ptr [bp - 2]
0166 add word ptr [bp - 6], ax
0169 or si, si
016b jl 0x8a78
016d cmp si, 0x3f
0170 jg 0x8a78
0172 lea ax, [di + 1]
0175 or ax, ax
0177 jl 0x8a78
0179 cmp ax, 0x1f
017c jg 0x8a78
017e mov dx, 1
0181 jmp 0x8a7a
0183 nop 
0184 xor dx, dx
0186 or dx, dx
0188 jne 0x8a86
018a mov word ptr [bp - 2], 0xffff
018f jmp 0x8ae9
0191 nop 
0192 mov al, byte ptr [0x8605]
0195 cwde 
0196 or ax, ax
0198 je 0x8aa0
019a dec ax
019b je 0x8aae
019d dec ax
019e je 0x8abc
01a0 dec ax
01a1 je 0x8aca
01a3 dec ax
01a4 je 0x8ad8
01a6 mov cx, word ptr [bp - 4]
01a9 jmp 0x8ae6
01ab nop 
01ac mov bx, si
01ae shl bx, 5
01b1 add bx, di
01b3 mov cl, byte ptr es:[bx + 0x62d3]
01b8 jmp 0x8ae4
01ba mov bx, si
01bc shl bx, 5
01bf add bx, di
01c1 mov cl, byte ptr es:[bx + 0x6ad3]
01c6 jmp 0x8ae4
01c8 mov bx, si
01ca shl bx, 5
01cd add bx, di
01cf mov cl, byte ptr es:[bx + 0x72d3]
01d4 jmp 0x8ae4
01d6 mov bx, si
01d8 shl bx, 5
01db add bx, di
01dd mov cl, byte ptr es:[bx + 0x7ad3]
01e2 jmp 0x8ae4
01e4 mov bx, si
01e6 shl bx, 5
01e9 add bx, di
01eb mov cl, byte ptr es:[bx + 0x52d3]
01f0 sub ch, ch
01f2 mov word ptr [bp - 2], cx
01f5 mov ax, word ptr [bp - 2]
01f8 add word ptr [bp - 6], ax
01fb lea ax, [si - 1]
01fe or ax, ax
0200 jl 0x8b0a
0202 cmp ax, 0x3f
0205 jg 0x8b0a
0207 or di, di
0209 jl 0x8b0a
020b cmp di, 0x1f
020e jg 0x8b0a
0210 mov dx, 1
0213 jmp 0x8b0c
0215 nop 
0216 xor dx, dx
0218 or dx, dx
021a jne 0x8b18
021c mov word ptr [bp - 2], 0xffff
0221 jmp 0x8b7b
0223 nop 
0224 mov al, byte ptr [0x8605]
0227 cwde 
0228 or ax, ax
022a je 0x8b32
022c dec ax
022d je 0x8b40
022f dec ax
0230 je 0x8b4e
0232 dec ax
0233 je 0x8b5c
0235 dec ax
0236 je 0x8b6a
0238 mov cx, word ptr [bp - 4]
023b jmp 0x8b78
023d nop 
023e mov bx, si
0240 shl bx, 5
0243 add bx, di
0245 mov cl, byte ptr es:[bx + 0x62b2]
024a jmp 0x8b76
024c mov bx, si
024e shl bx, 5
0251 add bx, di
0253 mov cl, byte ptr es:[bx + 0x6ab2]
0258 jmp 0x8b76
025a mov bx, si
025c shl bx, 5
025f add bx, di
0261 mov cl, byte ptr es:[bx + 0x72b2]
0266 jmp 0x8b76
0268 mov bx, si
026a shl bx, 5
026d add bx, di
026f mov cl, byte ptr es:[bx + 0x7ab2]
0274 jmp 0x8b76
0276 mov bx, si
0278 shl bx, 5
027b add bx, di
027d mov cl, byte ptr es:[bx + 0x52b2]
0282 sub ch, ch
0284 mov word ptr [bp - 2], cx
0287 mov ax, word ptr [bp - 2]
028a add word ptr [bp - 6], ax
028d or si, si
028f jl 0x8b98
0291 cmp si, 0x3f
0294 jg 0x8b98
0296 or di, di
0298 jl 0x8b98
029a cmp di, 0x1f
029d jg 0x8b98
029f mov dx, 1
02a2 jmp 0x8b9a
02a4 xor dx, dx
02a6 or dx, dx
02a8 jne 0x8ba6
02aa mov word ptr [bp - 4], 0xffff
02af jmp 0x8c09
02b1 nop 
02b2 mov al, byte ptr [0x8605]
02b5 cwde 
02b6 or ax, ax
02b8 je 0x8bc0
02ba dec ax
02bb je 0x8bce
02bd dec ax
02be je 0x8bdc
02c0 dec ax
02c1 je 0x8bea
02c3 dec ax
02c4 je 0x8bf8
02c6 mov cx, word ptr [bp - 2]
02c9 jmp 0x8c06
02cb nop 
02cc mov bx, si
02ce shl bx, 5
02d1 add bx, di
02d3 mov cl, byte ptr es:[bx + 0x62d2]
02d8 jmp 0x8c04
02da mov bx, si
02dc shl bx, 5
02df add bx, di
02e1 mov cl, byte ptr es:[bx + 0x6ad2]
02e6 jmp 0x8c04
02e8 mov bx, si
02ea shl bx, 5
02ed add bx, di
02ef mov cl, byte ptr es:[bx + 0x72d2]
02f4 jmp 0x8c04
02f6 mov bx, si
02f8 shl bx, 5
02fb add bx, di
02fd mov cl, byte ptr es:[bx + 0x7ad2]
0302 jmp 0x8c04
0304 mov bx, si
0306 shl bx, 5
0309 add bx, di
030b mov cl, byte ptr es:[bx + 0x52d2]
0310 sub ch, ch
0312 mov word ptr [bp - 4], cx
0315 mov ax, word ptr [bp - 6]
0318 cdq 
0319 and dx, 3
031c add ax, dx
031e sar ax, 2
0321 add ax, word ptr [bp - 4]
0324 cdq 
0325 sub ax, dx
0327 sar ax, 1
0329 or si, si
032b jl 0x8c34
032d cmp si, 0x3f
0330 jg 0x8c34
0332 or di, di
0334 jl 0x8c34
0336 cmp di, 0x1f
0339 jg 0x8c34
033b mov dx, 1
033e jmp 0x8c36
0340 xor dx, dx
0342 or dx, dx
0344 je 0x8c9e
0346 cmp ax, 0xff
0349 jle 0x8c58
034b mov cx, 0xff
034e mov al, byte ptr [0x8605]
0351 cwde 
0352 or ax, ax
0354 je 0x8c5c
0356 dec ax
0357 je 0x8c6a
0359 dec ax
035a je 0x8c78
035c dec ax
035d je 0x8c86
035f dec ax
0360 je 0x8c94
0362 jmp 0x8c9e
0364 mov cx, ax
0366 jmp 0x8c42
0368 mov bx, si
036a shl bx, 5
036d add bx, di
036f mov byte ptr es:[bx + 0x62d2], cl
0374 jmp 0x8c9e
0376 mov bx, si
0378 shl bx, 5
037b add bx, di
037d mov byte ptr es:[bx + 0x6ad2], cl
0382 jmp 0x8c9e
0384 mov bx, si
0386 shl bx, 5
0389 add bx, di
038b mov byte ptr es:[bx + 0x72d2], cl
0390 jmp 0x8c9e
0392 mov bx, si
0394 shl bx, 5
0397 add bx, di
0399 mov byte ptr es:[bx + 0x7ad2], cl
039e jmp 0x8c9e
03a0 shl si, 5
03a3 add si, di
03a5 mov byte ptr es:[si + 0x52d2], cl
03aa push ss
03ab pop ds
03ac pop si
03ad pop di
03ae leave 
03af retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FillDirtR', 'offset': 34778, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 193}
- {'symbol': '_SmoothMany', 'offset': 34972, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 87}
- {'symbol': '_IsValidSLoc', 'offset': 36004, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 36}
- {'symbol': '_GetSM', 'offset': 36040, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 193}
