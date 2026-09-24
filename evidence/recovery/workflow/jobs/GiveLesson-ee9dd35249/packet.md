# Recovery task _GiveLesson

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 948 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov ax, word ptr [bp + 6]
0008 dec ax
0009 cmp ax, 0x37
000c jbe 0x7b5f
000e jmp 0x7efe
0011 shl ax, 1
0013 xchg bx, ax
0014 jmp word ptr cs:[bx + 0x7b68]
0019 nop 
001a dw offset 0x7bd8
001c dw offset 0x7be0
001e dw offset 0x7bec
0020 dw offset 0x7c18
0022 dw offset 0x7c34
0024 dw offset 0x7c40
0026 dw offset 0x7c48
0028 dw offset 0x7c74
002a dw offset 0x7c92
002c dw offset 0x7cb0
002e dw offset 0x7cb8
0030 dw offset 0x7cc4
0032 dw offset 0x7ccc
0034 dw offset 0x7cd8
0036 dw offset 0x7cf6
0038 dw offset 0x7cfe
003a dw offset 0x7d06
003c dw offset 0x7d12
003e dw offset 0x7d1e
0040 dw offset 0x7d26
0042 dw offset 0x7d2e
0044 dw offset 0x7d3a
0046 dw offset 0x7d42
0048 dw offset 0x7d54
004a dw offset 0x7d5c
004c dw offset 0x7d64
004e dw offset 0x7d6c
0050 dw offset 0x7d8e
0052 dw offset 0x7d96
0054 dw offset 0x7d9e
0056 dw offset 0x7da6
0058 dw offset 0x7dae
005a dw offset 0x7db6
005c dw offset 0x7dc2
005e dw offset 0x7dca
0060 dw offset 0x7dd2
0062 dw offset 0x7dde
0064 dw offset 0x7de6
0066 dw offset 0x7df2
0068 dw offset 0x7dfa
006a dw offset 0x7e06
006c dw offset 0x7e26
006e dw offset 0x7e2e
0070 dw offset 0x7eee
0072 dw offset 0x7e3a
0074 dw offset 0x7e46
0076 dw offset 0x7e52
0078 dw offset 0x7e5a
007a dw offset 0x7e66
007c dw offset 0x7e9c
007e dw offset 0x7ea8
0080 dw offset 0x7eb0
0082 dw offset 0x7eb8
0084 dw offset 0x7ec0
0086 dw offset 0x7ec8
0088 dw offset 0x7ee4
008a push 1
008c push 0x2af8
008f jmp 0x7ee9
0092 push 1
0094 push 0x2afa
0097 push 0x4268
009a jmp 0x7ef6
009d nop 
009e push 1
00a0 push 0x2afc
00a3 push 0
00a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
00aa add sp, 6
00ad mov es, word ptr [0xc66a]
00b1 mov ax, word ptr es:[0x72c8]
00b5 add ax, 2
00b8 cdq 
00b9 mov es, word ptr [0xc65e]
00bd mov word ptr es:[0x9b10], ax
00c1 mov word ptr es:[0x9b12], dx
00c6 pop si
00c7 pop di
00c8 leave 
00c9 retf 
00ca push 1
00cc push 0x2afe
00cf push 0
00d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 212, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
00d6 add sp, 6
00d9 mov es, word ptr [0xc66a]
00dd mov ax, word ptr es:[0x72c8]
00e1 add ax, 0xa
00e4 jmp 0x7c06
00e6 push 1
00e8 push 0x2b00
00eb push 0x4269
00ee jmp 0x7ef6
00f1 nop 
00f2 push 1
00f4 push 0x2b02
00f7 jmp 0x7ee9
00fa push 1
00fc push 0x2b04
00ff push 0
0101 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 260, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
0106 add sp, 6
0109 mov ax, word ptr [0xce7e] ; _MeLocY
010c add ax, word ptr [0xcd88] ; _MeLocX
0110 mov es, word ptr [0xc66e]
0114 mov word ptr es:[0x9fb0], ax
0118 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
011d add ax, 0x258
0120 adc dx, 0
0123 jmp 0x7c07
0125 nop 
0126 push 1
0128 push 0x2b06
012b push 0
012d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 304, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
0132 add sp, 6
0135 mov es, word ptr [0xc66e]
0139 mov word ptr es:[0x9fb0], 0
0140 pop si
0141 pop di
0142 leave 
0143 retf 
0144 push 1
0146 push 0x2b08
0149 push 0
014b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 334, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
0150 add sp, 6
0153 mov es, word ptr [0xc670]
0157 mov ax, word ptr es:[0x7d30]
015b add ax, word ptr es:[0x7d2e]
0160 jmp 0x7c5e
0162 push 1
0164 push 0x2b0a
0167 jmp 0x7ee9
016a push 1
016c push 0x2b0c
016f push 0x4276
0172 jmp 0x7ef6
0175 nop 
0176 push 1
0178 push 0x2b0e
017b jmp 0x7ee9
017e push 1
0180 push 0x2b10
0183 push 0x426a
0186 jmp 0x7ef6
0189 nop 
018a push 1
018c push 0x2b12
018f push 0x426a
0192 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 405, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
0197 add sp, 6
019a push 8
019c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 415, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SetMyHealth
01a1 add sp, 2
01a4 pop si
01a5 pop di
01a6 leave 
01a7 retf 
01a8 push 1
01aa push 0x2b14
01ad jmp 0x7ee9
01b0 push 1
01b2 push 0x2b16
01b5 jmp 0x7ee9
01b8 push 1
01ba push 0x2b18
01bd push 0x4275
01c0 jmp 0x7ef6
01c3 nop 
01c4 push 1
01c6 push 0x2b1a
01c9 push 0x426b
01cc jmp 0x7ef6
01cf nop 
01d0 push 1
01d2 push 0x2b1c
01d5 jmp 0x7ee9
01d8 push 1
01da push 0x2b1e
01dd jmp 0x7ee9
01e0 push 1
01e2 push 0x2b20
01e5 push 0x426c
01e8 jmp 0x7ef6
01eb nop 
01ec push 1
01ee push 0x2b22
01f1 jmp 0x7ee9
01f4 push 0xa
01f6 nop 
01f7 push cs
01f8 call 0x6c5a ; _AddBlackAnts
01fb add sp, 2
01fe push 1
0200 push 0x2b24
0203 jmp 0x7ee9
0206 push 1
0208 push 0x2b26
020b jmp 0x7ee9
020e push 1
0210 push 0x2b28
0213 jmp 0x7ee9
0216 push 1
0218 push 0x2b2a
021b jmp 0x7c4d
021e push 1
0220 push 0x2b2c
0223 push 0
0225 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 552, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
022a add sp, 6
022d mov ax, word ptr [0xce7e] ; _MeLocY
0230 add ax, word ptr [0xcd88] ; _MeLocX
0234 mov es, word ptr [0xc66e]
0238 mov word ptr es:[0x9fb0], ax
023c pop si
023d pop di
023e leave 
023f retf 
0240 push 1
0242 push 0x2b2e
0245 jmp 0x7ee9
0248 push 1
024a push 0x2b30
024d jmp 0x7ee9
0250 push 1
0252 push 0x2b32
0255 jmp 0x7c79
0258 push 1
025a push 0x2b34
025d jmp 0x7ee9
0260 push 1
0262 push 0x2b36
0265 jmp 0x7ee9
0268 push 1
026a push 0x2b38
026d push 0x426d
0270 jmp 0x7ef6
0273 nop 
0274 push 1
0276 push 0x2b3a
0279 jmp 0x7ee9
027c push 1
027e push 0x2b3c
0281 jmp 0x7ee9
0284 push 1
0286 push 0x2b3e
0289 push 0x426e
028c jmp 0x7ef6
028f nop 
0290 push 1
0292 push 0x2b40
0295 jmp 0x7ee9
0298 push 1
029a push 0x2b42
029d push 0x426f
02a0 jmp 0x7ef6
02a3 nop 
02a4 push 1
02a6 push 0x2b44
02a9 jmp 0x7dff
02ab nop 
02ac push 1
02ae push 0x2b46
02b1 push 0x4270
02b4 jmp 0x7ef6
02b7 nop 
02b8 push 1
02ba push 0x2b48
02bd push 0x4270
02c0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 707, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
02c5 add sp, 6
02c8 mov es, word ptr [0xc672]
02cc mov ax, word ptr es:[0x9c76]
02d0 add ax, word ptr es:[0x9c74]
02d5 jmp 0x7d82
02d8 push 1
02da push 0x2b4a
02dd jmp 0x7ee9
02e0 mov es, word ptr [0xc65c]
02e4 inc word ptr es:[0x85ee]
02e9 jmp 0x7eee
02ec push 1
02ee push 0x2b50
02f1 push 0x4272
02f4 jmp 0x7ef6
02f7 nop 
02f8 push 1
02fa push 0x2b52
02fd push 0x4272
0300 jmp 0x7c7b
0303 nop 
0304 push 1
0306 push 0x2b54
0309 jmp 0x7e5f
030b nop 
030c push 1
030e push 0x2b56
0311 push 0x4273
0314 jmp 0x7ef6
0317 nop 
0318 push 1
031a push 0x2b58
031d push 0
031f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 802, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
0324 add sp, 6
0327 push 0x50
0329 nop 
032a push cs
032b call 0x6c5a ; _AddBlackAnts
032e add sp, 2
0331 mov si, 0x52d2
0334 mov es, word ptr [0xc674]
0338 xor ax, ax
033a mov cx, 0x10
033d mov di, si
033f rep stosw word ptr es:[di], ax
0341 add si, 0x20
0344 cmp si, 0x5ad2
0348 jb 0x7e86
034a pop si
034b pop di
034c leave 
034d retf 
034e push 1
0350 push 0x2b5a
0353 push 0x4274
0356 jmp 0x7c7b
0359 nop 
035a push 1
035c push 0x2b5c
035f jmp 0x7ee9
0361 nop 
0362 push 1
0364 push 0x2b5e
0367 jmp 0x7ee9
0369 nop 
036a push 1
036c push 0x2b60
036f jmp 0x7ee9
0371 nop 
0372 push 1
0374 push 0x2b62
0377 jmp 0x7ee9
0379 nop 
037a mov es, word ptr [0xc66e]
037e cmp word ptr es:[0x9fb0], 0
0384 jne 0x7edc
0386 push 1
0388 push 0x2b64
038b jmp 0x7ee9
038d nop 
038e push 1
0390 push 0x2b66
0393 jmp 0x7ee9
0395 nop 
0396 push 1
0398 push 0x2b68
039b push 0
039d jmp 0x7ef6
039f nop 
03a0 push 1
03a2 push 0x2b4e
03a5 push 0x4271
03a8 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 939, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _PictStrnDialog
03ad add sp, 6
03b0 pop si
03b1 pop di
03b2 leave 
03b3 retf 
```

## Known declaration examples

- `extern void far AddBlackAnts(int count);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far AddBlackAnts(int count);` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_9_scaffold-e90b738f21.c
- `extern void far AddBlackAnts(int count);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_12_scaffold-851a6419ac.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocX;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_6A38_processSpider_5_scaffold-758a633aa7.c
- `extern int near MeLocY;` — src/recovered/wf_tu_simant_9D04_AddSomeAnts_7_scaffold-8594bec5c8.c
- `extern void far SetMyHealth(int health);` — src/recovered/wf_tu_simant1_75F4_DoAntSimY_3_scaffold-7e7e8ed0c2.c
- `extern void far SetMyHealth(int health);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_Feedback', 'offset': 30922, 'source': None, 'size': 453}
- {'symbol': '_RunTutor', 'offset': 31376, 'source': None, 'size': 190}
- {'symbol': '_LessonDone', 'offset': 32514, 'source': None, 'size': 627}
- {'symbol': '_db_Exists', 'offset': 33142, 'source': 'src/recovered/db_Exists.c', 'size': 54}
