# Recovery task _FixExitMapR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 198 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 cmp di, 2
000c jge 0x2950
000e mov bx, word ptr [bp + 6]
0011 mov si, bx
0013 shl si, 6
0016 add si, di
0018 cmp byte ptr [si + 0x58e8], 0x18
001d jne 0x2940
001f mov es, word ptr [0xc422]
0023 mov byte ptr es:[si + 0x13a4], 0xff
0029 jmp 0x29d4
002c mov es, word ptr [0xc422]
0030 mov bx, si
0032 mov byte ptr es:[bx + 0x13a4], 0xfe
0038 jmp 0x29d4
003b nop 
003c xor cx, cx
003e mov word ptr [bp - 2], cx
0041 mov <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0044 mov ds, ax
0046 mov <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0049 mov es, ax
004b mov bx, cx
004d mov al, byte ptr es:[bx + 8]
0052 cwde 
0053 mov si, ax
0055 add si, word ptr [bp + 8]
0058 mov <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
005b mov es, ax
005d mov al, byte ptr es:[bx]
0062 cwde 
0063 mov di, ax
0065 add di, word ptr [bp + 6]
0068 js 0x29a1
006a cmp di, 0x3f
006d jg 0x29a1
006f or si, si
0071 jl 0x29a1
0073 cmp si, 0x3f
0076 jg 0x29a1
0078 mov bx, di
007a shl bx, 6
007d add bx, si
007f mov al, byte ptr [bx + 0x13a4]
0083 sub ah, ah
0085 cmp ax, word ptr [bp - 2]
0088 jle 0x29a1
008a mov word ptr [bp - 2], ax
008d inc cx
008e cmp cx, 8
0091 jl 0x295a
0093 mov cx, word ptr [bp - 2]
0096 or cx, cx
0098 je 0x29c4
009a mov bx, word ptr [bp + 6]
009d mov di, word ptr [bp + 8]
00a0 dec cl
00a2 mov si, bx
00a4 shl si, 6
00a7 add si, di
00a9 mov byte ptr [si + 0x13a4], cl
00ad jmp 0x29d4
00af nop 
00b0 mov bx, word ptr [bp + 6]
00b3 mov di, word ptr [bp + 8]
00b6 shl bx, 6
00b9 add bx, di
00bb mov byte ptr [bx + 0x13a4], 0
00c0 push ss
00c1 pop ds
00c2 pop si
00c3 pop di
00c4 leave 
00c5 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SmoothEdgesR', 'offset': 9956, 'source': None, 'size': 362}
- {'symbol': '_FixExitMapB', 'offset': 10318, 'source': None, 'size': 198}
- {'symbol': '_FloodNestB', 'offset': 10714, 'source': None, 'size': 60}
- {'symbol': '_CompactListA', 'offset': 10774, 'source': 'src/recovered/wf_CompactListA-2c6f7e42f7.c', 'size': 99}
