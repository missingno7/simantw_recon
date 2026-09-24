# Recovery task _ConnectAll

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 1267 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 6]
0009 shl bx, 6
000c add bx, word ptr [bp + 8]
000f mov word ptr [bp - 6], bx
0012 mov dl, byte ptr [bx + 0x28e8]
0016 sub dh, dh
0018 cmp dx, 0x60
001b jl 0x8082
001d cmp dx, 0x67
0020 jg 0x8082
0022 mov dx, 1
0025 jmp 0x8084
0027 nop 
0028 xor dx, dx
002a or dx, dx
002c jne 0x808b
002e jmp 0x8151
0031 mov word ptr [bp - 2], 0
0036 push word ptr [bp + 8]
0039 mov ax, word ptr [bp + 6]
003c dec ax
003d push ax
003e push 1
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 67, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0045 add sp, 6
0048 mov di, ax
004a cmp di, 0x60
004d jl 0x80b4
004f cmp di, 0x67
0052 jg 0x80b4
0054 mov dx, 1
0057 jmp 0x80b6
0059 nop 
005a xor dx, dx
005c dec dx
005d jne 0x80e2
005f mov si, 1
0062 shl si, 1
0064 mov ax, word ptr [bp + 8]
0067 inc ax
0068 push ax
0069 push word ptr [bp + 6]
006c push 1
006e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 113, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0073 add sp, 6
0076 mov word ptr [bp - 4], ax
0079 cmp ax, 0x60
007c jl 0x80e8
007e cmp ax, 0x67
0081 jg 0x80e8
0083 mov dx, 1
0086 jmp 0x80ea
0088 mov si, word ptr [bp - 2]
008b jmp 0x80bc
008d nop 
008e xor dx, dx
0090 dec dx
0091 jne 0x80ee
0093 inc si
0094 shl si, 1
0096 push word ptr [bp + 8]
0099 mov ax, word ptr [bp + 6]
009c inc ax
009d push ax
009e push 1
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
00a5 add sp, 6
00a8 mov word ptr [bp - 4], ax
00ab cmp ax, 0x60
00ae jl 0x8114
00b0 cmp ax, 0x67
00b3 jg 0x8114
00b5 mov dx, 1
00b8 jmp 0x8116
00ba xor dx, dx
00bc dec dx
00bd jne 0x811a
00bf inc si
00c0 shl si, 1
00c2 mov ax, word ptr [bp + 8]
00c5 dec ax
00c6 push ax
00c7 push word ptr [bp + 6]
00ca push 1
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
00d1 add sp, 6
00d4 mov word ptr [bp - 4], ax
00d7 cmp ax, 0x60
00da jl 0x8140
00dc cmp ax, 0x67
00df jg 0x8140
00e1 mov dx, 1
00e4 jmp 0x8142
00e6 xor dx, dx
00e8 dec dx
00e9 jne 0x8146
00eb inc si
00ec mov al, byte ptr [si + 0x1bce]
00f0 mov bx, word ptr [bp - 6]
00f3 mov byte ptr [bx + 0x28e8], al
00f7 mov ax, word ptr [bp + 8]
00fa dec ax
00fb mov word ptr [bp - 8], ax
00fe push ax
00ff push word ptr [bp + 6]
0102 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 261, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0107 add sp, 4
010a dec ax
010b je 0x816a
010d jmp 0x8251
0110 mov bx, word ptr [bp - 6]
0113 mov dl, byte ptr [bx + 0x28e7]
0117 sub dh, dh
0119 cmp dx, 0x60
011c jl 0x8182
011e cmp dx, 0x67
0121 jg 0x8182
0123 mov dx, 1
0126 jmp 0x8184
0128 xor dx, dx
012a or dx, dx
012c jne 0x818b
012e jmp 0x8251
0131 mov word ptr [bp - 2], 0
0136 push word ptr [bp - 8]
0139 mov ax, word ptr [bp + 6]
013c dec ax
013d push ax
013e push 1
0140 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 323, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0145 add sp, 6
0148 mov si, ax
014a cmp si, 0x60
014d jl 0x81b4
014f cmp si, 0x67
0152 jg 0x81b4
0154 mov dx, 1
0157 jmp 0x81b6
0159 nop 
015a xor dx, dx
015c dec dx
015d jne 0x81e0
015f mov si, 1
0162 shl si, 1
0164 push word ptr [bp + 8]
0167 push word ptr [bp + 6]
016a push 1
016c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 367, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0171 add sp, 6
0174 mov word ptr [bp - 4], ax
0177 cmp ax, 0x60
017a jl 0x81e6
017c cmp ax, 0x67
017f jg 0x81e6
0181 mov dx, 1
0184 jmp 0x81e8
0186 mov si, word ptr [bp - 2]
0189 jmp 0x81bc
018b nop 
018c xor dx, dx
018e dec dx
018f jne 0x81ec
0191 inc si
0192 shl si, 1
0194 push word ptr [bp - 8]
0197 mov ax, word ptr [bp + 6]
019a inc ax
019b push ax
019c push 1
019e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 417, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
01a3 add sp, 6
01a6 mov word ptr [bp - 4], ax
01a9 cmp ax, 0x60
01ac jl 0x8212
01ae cmp ax, 0x67
01b1 jg 0x8212
01b3 mov dx, 1
01b6 jmp 0x8214
01b8 xor dx, dx
01ba dec dx
01bb jne 0x8218
01bd inc si
01be shl si, 1
01c0 mov ax, word ptr [bp + 8]
01c3 sub ax, 2
01c6 push ax
01c7 push word ptr [bp + 6]
01ca push 1
01cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 463, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
01d1 add sp, 6
01d4 mov word ptr [bp - 4], ax
01d7 cmp ax, 0x60
01da jl 0x8240
01dc cmp ax, 0x67
01df jg 0x8240
01e1 mov dx, 1
01e4 jmp 0x8242
01e6 xor dx, dx
01e8 dec dx
01e9 jne 0x8246
01eb inc si
01ec mov al, byte ptr [si + 0x1bce]
01f0 mov bx, word ptr [bp - 6]
01f3 mov byte ptr [bx + 0x28e7], al
01f7 push word ptr [bp + 8]
01fa mov ax, word ptr [bp + 6]
01fd inc ax
01fe mov word ptr [bp - 0xa], ax
0201 push ax
0202 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 517, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0207 add sp, 4
020a dec ax
020b je 0x826a
020d jmp 0x834f
0210 mov bx, word ptr [bp - 6]
0213 mov dl, byte ptr [bx + 0x2928]
0217 sub dh, dh
0219 cmp dx, 0x60
021c jl 0x8282
021e cmp dx, 0x67
0221 jg 0x8282
0223 mov dx, 1
0226 jmp 0x8284
0228 xor dx, dx
022a or dx, dx
022c jne 0x828b
022e jmp 0x834f
0231 mov word ptr [bp - 2], 0
0236 push word ptr [bp + 8]
0239 push word ptr [bp + 6]
023c push 1
023e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 577, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0243 add sp, 6
0246 mov si, ax
0248 cmp si, 0x60
024b jl 0x82b2
024d cmp si, 0x67
0250 jg 0x82b2
0252 mov dx, 1
0255 jmp 0x82b4
0257 nop 
0258 xor dx, dx
025a dec dx
025b jne 0x82e0
025d mov si, 1
0260 shl si, 1
0262 mov ax, word ptr [bp + 8]
0265 inc ax
0266 push ax
0267 push word ptr [bp - 0xa]
026a push 1
026c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 623, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0271 add sp, 6
0274 mov word ptr [bp - 4], ax
0277 cmp ax, 0x60
027a jl 0x82e6
027c cmp ax, 0x67
027f jg 0x82e6
0281 mov dx, 1
0284 jmp 0x82e8
0286 mov si, word ptr [bp - 2]
0289 jmp 0x82ba
028b nop 
028c xor dx, dx
028e dec dx
028f jne 0x82ec
0291 inc si
0292 shl si, 1
0294 push word ptr [bp + 8]
0297 mov ax, word ptr [bp + 6]
029a add ax, 2
029d push ax
029e push 1
02a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 675, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
02a5 add sp, 6
02a8 mov word ptr [bp - 4], ax
02ab cmp ax, 0x60
02ae jl 0x8314
02b0 cmp ax, 0x67
02b3 jg 0x8314
02b5 mov dx, 1
02b8 jmp 0x8316
02ba xor dx, dx
02bc dec dx
02bd jne 0x831a
02bf inc si
02c0 shl si, 1
02c2 push word ptr [bp - 8]
02c5 push word ptr [bp - 0xa]
02c8 push 1
02ca lcall <resolved loader operand; see bindings> ; [{'operand_offset': 717, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
02cf add sp, 6
02d2 mov word ptr [bp - 4], ax
02d5 cmp ax, 0x60
02d8 jl 0x833e
02da cmp ax, 0x67
02dd jg 0x833e
02df mov dx, 1
02e2 jmp 0x8340
02e4 xor dx, dx
02e6 dec dx
02e7 jne 0x8344
02e9 inc si
02ea mov al, byte ptr [si + 0x1bce]
02ee mov bx, word ptr [bp - 6]
02f1 mov byte ptr [bx + 0x2928], al
02f5 mov ax, word ptr [bp + 8]
02f8 inc ax
02f9 mov word ptr [bp - 0xc], ax
02fc push ax
02fd push word ptr [bp + 6]
0300 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 771, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0305 add sp, 4
0308 dec ax
0309 je 0x8368
030b jmp 0x844d
030e mov bx, word ptr [bp - 6]
0311 mov dl, byte ptr [bx + 0x28e9]
0315 sub dh, dh
0317 cmp dx, 0x60
031a jl 0x8380
031c cmp dx, 0x67
031f jg 0x8380
0321 mov dx, 1
0324 jmp 0x8382
0326 xor dx, dx
0328 or dx, dx
032a jne 0x8389
032c jmp 0x844d
032f mov word ptr [bp - 2], 0
0334 push word ptr [bp - 0xc]
0337 mov ax, word ptr [bp + 6]
033a dec ax
033b push ax
033c push 1
033e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 833, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0343 add sp, 6
0346 mov si, ax
0348 cmp si, 0x60
034b jl 0x83b2
034d cmp si, 0x67
0350 jg 0x83b2
0352 mov dx, 1
0355 jmp 0x83b4
0357 nop 
0358 xor dx, dx
035a dec dx
035b jne 0x83e2
035d mov si, 1
0360 shl si, 1
0362 mov ax, word ptr [bp + 8]
0365 add ax, 2
0368 push ax
0369 push word ptr [bp + 6]
036c push 1
036e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 881, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0373 add sp, 6
0376 mov word ptr [bp - 4], ax
0379 cmp ax, 0x60
037c jl 0x83e8
037e cmp ax, 0x67
0381 jg 0x83e8
0383 mov dx, 1
0386 jmp 0x83ea
0388 mov si, word ptr [bp - 2]
038b jmp 0x83ba
038d nop 
038e xor dx, dx
0390 dec dx
0391 jne 0x83ee
0393 inc si
0394 shl si, 1
0396 push word ptr [bp - 0xc]
0399 push word ptr [bp - 0xa]
039c push 1
039e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 929, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
03a3 add sp, 6
03a6 mov word ptr [bp - 4], ax
03a9 cmp ax, 0x60
03ac jl 0x8412
03ae cmp ax, 0x67
03b1 jg 0x8412
03b3 mov dx, 1
03b6 jmp 0x8414
03b8 xor dx, dx
03ba dec dx
03bb jne 0x8418
03bd inc si
03be shl si, 1
03c0 push word ptr [bp + 8]
03c3 push word ptr [bp + 6]
03c6 push 1
03c8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 971, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
03cd add sp, 6
03d0 mov word ptr [bp - 4], ax
03d3 cmp ax, 0x60
03d6 jl 0x843c
03d8 cmp ax, 0x67
03db jg 0x843c
03dd mov dx, 1
03e0 jmp 0x843e
03e2 xor dx, dx
03e4 dec dx
03e5 jne 0x8442
03e7 inc si
03e8 mov al, byte ptr [si + 0x1bce]
03ec mov bx, word ptr [bp - 6]
03ef mov byte ptr [bx + 0x28e9], al
03f3 push word ptr [bp + 8]
03f6 mov ax, word ptr [bp + 6]
03f9 dec ax
03fa mov word ptr [bp - 0xe], ax
03fd push ax
03fe lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1025, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0403 add sp, 4
0406 dec ax
0407 je 0x8466
0409 jmp 0x8549
040c mov bx, word ptr [bp - 6]
040f mov dl, byte ptr [bx + 0x28a8]
0413 sub dh, dh
0415 cmp dx, 0x60
0418 jl 0x847e
041a cmp dx, 0x67
041d jg 0x847e
041f mov dx, 1
0422 jmp 0x8480
0424 xor dx, dx
0426 or dx, dx
0428 jne 0x8487
042a jmp 0x8549
042d mov word ptr [bp - 2], 0
0432 push word ptr [bp + 8]
0435 mov ax, word ptr [bp + 6]
0438 sub ax, 2
043b push ax
043c push 1
043e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1089, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0443 add sp, 6
0446 mov si, ax
0448 cmp si, 0x60
044b jl 0x84b2
044d cmp si, 0x67
0450 jg 0x84b2
0452 mov dx, 1
0455 jmp 0x84b4
0457 nop 
0458 xor dx, dx
045a dec dx
045b jne 0x84de
045d mov si, 1
0460 shl si, 1
0462 push word ptr [bp - 0xc]
0465 push word ptr [bp - 0xe]
0468 push 1
046a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1133, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
046f add sp, 6
0472 mov word ptr [bp - 4], ax
0475 cmp ax, 0x60
0478 jl 0x84e4
047a cmp ax, 0x67
047d jg 0x84e4
047f mov dx, 1
0482 jmp 0x84e6
0484 mov si, word ptr [bp - 2]
0487 jmp 0x84ba
0489 nop 
048a xor dx, dx
048c dec dx
048d jne 0x84ea
048f inc si
0490 shl si, 1
0492 push word ptr [bp + 8]
0495 push word ptr [bp + 6]
0498 push 1
049a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
049f add sp, 6
04a2 mov word ptr [bp - 4], ax
04a5 cmp ax, 0x60
04a8 jl 0x850e
04aa cmp ax, 0x67
04ad jg 0x850e
04af mov dx, 1
04b2 jmp 0x8510
04b4 xor dx, dx
04b6 dec dx
04b7 jne 0x8514
04b9 inc si
04ba shl si, 1
04bc push word ptr [bp - 8]
04bf push word ptr [bp - 0xe]
04c2 push 1
04c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1223, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
04c9 add sp, 6
04cc mov word ptr [bp - 4], ax
04cf cmp ax, 0x60
04d2 jl 0x8538
04d4 cmp ax, 0x67
04d7 jg 0x8538
04d9 mov dx, 1
04dc jmp 0x853a
04de xor dx, dx
04e0 dec dx
04e1 jne 0x853e
04e3 inc si
04e4 mov al, byte ptr [si + 0x1bce]
04e8 mov bx, word ptr [bp - 6]
04eb mov byte ptr [bx + 0x28a8], al
04ef pop si
04f0 pop di
04f1 leave 
04f2 retf 
```

## Known declaration examples

- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simant1_0000_DoSmells_15_scaffold-74956f98fa.c
- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simtwo_4CDC_StorePillarMap_4_scaffold-c16d27de40.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExpKillAnts', 'offset': 32092, 'source': None, 'size': 478}
- {'symbol': '_IncFoodHere', 'offset': 32570, 'source': None, 'size': 287}
- {'symbol': '_ConnectWall', 'offset': 34126, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 241}
- {'symbol': '_WallNeighbors', 'offset': 34368, 'source': 'src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c', 'size': 190}
