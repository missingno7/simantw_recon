# Recovery task _IsItFoodAt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 193 bytes.

```asm
0000 enter 2, 0
0004 push si
0005 mov word ptr [bp - 2], 0xffff
000a cmp word ptr [bp + 6], 1
000e jg 0x5fac
0010 mov si, word ptr [bp + 8]
0013 or si, si
0015 jl 0x5fc4
0017 cmp si, 0x7f
001a jg 0x5fc4
001c cmp word ptr [bp + 0xa], 0
0020 jl 0x5fc4
0022 cmp word ptr [bp + 0xa], 0x3f
0026 jg 0x5fc4
0028 mov dx, 1
002b jmp 0x5fc6
002d nop 
002e mov si, word ptr [bp + 8]
0031 or si, si
0033 jl 0x5fc4
0035 cmp si, 0x3f
0038 jg 0x5fc4
003a cmp word ptr [bp + 0xa], 0
003e jl 0x5fc4
0040 cmp word ptr [bp + 0xa], 0x3f
0044 jle 0x5fa6
0046 xor dx, dx
0048 dec dx
0049 je 0x5fce
004b mov bx, word ptr [bp - 2]
004e jmp 0x600a
0050 mov ax, word ptr [bp + 6]
0053 or ax, ax
0055 jl 0x5fc9
0057 jo 0x5fc9
0059 dec ax
005a jle 0x5fe2
005c dec ax
005d je 0x5ff0
005f dec ax
0060 je 0x5ffe
0062 jmp 0x5fc9
0064 mov bx, si
0066 shl bx, 6
0069 add bx, word ptr [bp + 0xa]
006c mov bl, byte ptr [bx + 0x28e8]
0070 jmp 0x6008
0072 mov bx, si
0074 shl bx, 6
0077 add bx, word ptr [bp + 0xa]
007a mov bl, byte ptr [bx + 0x48e8]
007e jmp 0x6008
0080 shl si, 6
0083 add si, word ptr [bp + 0xa]
0086 mov bl, byte ptr [si + 0x58e8]
008a sub bh, bh
008c mov si, bx
008e or si, si
0090 jge 0x6016
0092 xor ax, ax
0094 pop si
0095 leave 
0096 retf 
0097 nop 
0098 cmp word ptr [bp + 6], 1
009c jg 0x6028
009e push si
009f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 162, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
00a4 add sp, 2
00a7 pop si
00a8 leave 
00a9 retf 
00aa cmp si, 0x10
00ad jl 0x6038
00af cmp si, 0x13
00b2 jg 0x6038
00b4 mov dx, 1
00b7 jmp 0x603a
00b9 nop 
00ba xor dx, dx
00bc mov ax, dx
00be pop si
00bf leave 
00c0 retf 
```

## Known declaration examples

- `extern int far IsItFood(int tile);` — src/recovered/wf_IsThisFood-26910209bd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsThisPebble', 'offset': 24370, 'source': None, 'size': 49}
- {'symbol': '_IsItNFood', 'offset': 24420, 'source': 'src/recovered/wf_IsItNFood-b827504a64.c', 'size': 26}
- {'symbol': '_GetLife', 'offset': 24640, 'source': 'src/recovered/wf_GetLife-172de0cfc1.c', 'size': 161}
- {'symbol': '_GetMap', 'offset': 24802, 'source': 'src/recovered/wf_GetMap-cddf28f960.c', 'size': 152}
