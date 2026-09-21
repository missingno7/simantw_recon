# Recovery task _SetCasteProd

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 183 bytes.

```asm
0000 enter 0x1a, 0
0004 push di
0005 push si
0006 xor bx, bx
0008 mov di, bx
000a mov cx, bx
000c mov <resolved loader operand; see bindings> ; [{'operand_offset': 13, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
000f mov es, ax
0011 add di, word ptr [bx - 0x536a]
0015 add cx, word ptr es:[bx - 0x79de]
001a add bx, 2
001d cmp bx, 8
0020 jl 0x27f
0022 xor si, si
0024 mov word ptr [bp - 6], cx
0027 mov word ptr [bp - 4], di
002a or di, di
002c jg 0x2a4
002e mov word ptr [bp + si - 0x10], 0
0033 jmp 0x2ba
0035 nop 
0036 mov ax, di
0038 cdq 
0039 push dx
003a push ax
003b mov ax, 0x64
003e imul word ptr [si - 0x536a]
0042 push dx
0043 push ax
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
0049 mov word ptr [bp + si - 0x10], ax
004c cmp word ptr [bp - 6], 0
0050 jg 0x2c8
0052 mov word ptr [bp + si - 0x1a], 0
0057 jmp 0x2e0
0059 nop 
005a mov ax, word ptr [bp - 6]
005d cdq 
005e push dx
005f push ax
0060 mov ax, 0x64
0063 imul word ptr es:[si - 0x79de]
0068 push dx
0069 push ax
006a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 109, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
006f mov word ptr [bp + si - 0x1a], ax
0072 add si, 2
0075 cmp si, 8
0078 jl 0x298
007a xor bx, bx
007c mov di, bx
007e mov word ptr [bp - 4], di
0081 mov dx, bx
0083 mov si, bx
0085 mov cx, word ptr [bp + si - 0x10]
0088 sub cx, word ptr [bp + si - 0x1a]
008b cmp cx, di
008d jge 0x302
008f mov di, cx
0091 mov word ptr [bp - 4], dx
0094 inc dx
0095 add bx, 2
0098 cmp bx, 8
009b jl 0x2f1
009d mov es, word ptr [0xc4c6]
00a1 mov bx, word ptr [bp - 4]
00a4 shl bx, 1
00a6 mov ax, word ptr es:[bx - 0x7652]
00ab mov es, word ptr [0xc4c8]
00af mov word ptr es:[0x8a56], ax
00b3 pop si
00b4 pop di
00b5 leave 
00b6 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetStrategy', 'offset': 0, 'source': None, 'size': 460}
- {'symbol': '_GstrB', 'offset': 460, 'source': 'src/recovered/wf_GstrB-b09a4bcc53.c', 'size': 162}
- {'symbol': '_SetModeProd', 'offset': 806, 'source': 'src/recovered/wf_SetModeProd-f696675003.c', 'size': 156}
- {'symbol': '_GstrR', 'offset': 962, 'source': None, 'size': 332}
