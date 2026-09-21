# Recovery task _SetMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 162 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 cmp word ptr [bp + 6], 1
0008 jg 0x61a2
000a mov dx, word ptr [bp + 8]
000d or dx, dx
000f jl 0x61ba
0011 cmp dx, 0x7f
0014 jg 0x61ba
0016 cmp word ptr [bp + 0xa], 0
001a jl 0x61ba
001c cmp word ptr [bp + 0xa], 0x3f
0020 jg 0x61ba
0022 mov bx, 1
0025 jmp 0x61bc
0027 nop 
0028 cmp word ptr [bp + 8], 0
002c jl 0x61ba
002e cmp word ptr [bp + 8], 0x3f
0032 jg 0x61ba
0034 cmp word ptr [bp + 0xa], 0
0038 jl 0x61ba
003a cmp word ptr [bp + 0xa], 0x3f
003e jle 0x619c
0040 xor bx, bx
0042 dec bx
0043 jne 0x6219
0045 mov ax, word ptr [bp + 6]
0048 or ax, ax
004a jl 0x6208
004c jo 0x6208
004e dec ax
004f jle 0x61d4
0051 dec ax
0052 je 0x61e6
0054 dec ax
0055 je 0x61f8
0057 jmp 0x6208
0059 nop 
005a mov al, byte ptr [bp + 0xc]
005d mov si, word ptr [bp + 8]
0060 shl si, 6
0063 mov bx, word ptr [bp + 0xa]
0066 mov byte ptr [bx + si + 0x28e8], al
006a jmp 0x6208
006c mov al, byte ptr [bp + 0xc]
006f mov si, word ptr [bp + 8]
0072 shl si, 6
0075 mov bx, word ptr [bp + 0xa]
0078 mov byte ptr [bx + si + 0x48e8], al
007c jmp 0x6208
007e mov al, byte ptr [bp + 0xc]
0081 mov si, word ptr [bp + 8]
0084 shl si, 6
0087 mov bx, word ptr [bp + 0xa]
008a mov byte ptr [bx + si + 0x58e8], al
008e push word ptr [bp + 0xa]
0091 push word ptr [bp + 8]
0094 push word ptr [bp + 6]
0097 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 154, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
009c add sp, 6
009f pop si
00a0 leave 
00a1 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_GetLife', 'offset': 24640, 'source': 'src/recovered/wf_GetLife-172de0cfc1.c', 'size': 161}
- {'symbol': '_GetMap', 'offset': 24802, 'source': 'src/recovered/wf_GetMap-cddf28f960.c', 'size': 152}
- {'symbol': '_ClearLife', 'offset': 25116, 'source': None, 'size': 258}
- {'symbol': '_ClearMyLife', 'offset': 25374, 'source': None, 'size': 465}
