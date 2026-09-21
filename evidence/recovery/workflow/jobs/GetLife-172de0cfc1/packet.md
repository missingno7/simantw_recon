# Recovery task _GetLife

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 161 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 6]
0009 mov word ptr [bp - 2], 0xffff
000e cmp dx, 1
0011 jg 0x6070
0013 mov si, word ptr [bp + 8]
0016 or si, si
0018 jl 0x6088
001a cmp si, 0x7f
001d jg 0x6088
001f cmp word ptr [bp + 0xa], 0
0023 jl 0x6088
0025 cmp word ptr [bp + 0xa], 0x3f
0029 jg 0x6088
002b mov bx, 1
002e jmp 0x608a
0030 mov si, word ptr [bp + 8]
0033 or si, si
0035 jl 0x6088
0037 cmp si, 0x3f
003a jg 0x6088
003c cmp word ptr [bp + 0xa], 0
0040 jl 0x6088
0042 cmp word ptr [bp + 0xa], 0x3f
0046 jle 0x606b
0048 xor bx, bx
004a dec bx
004b je 0x6096
004d mov dx, word ptr [bp - 2]
0050 mov ax, dx
0052 pop si
0053 pop di
0054 leave 
0055 retf 
0056 mov ax, dx
0058 or ax, ax
005a jl 0x60a7
005c jo 0x60a7
005e dec ax
005f jle 0x60ac
0061 dec ax
0062 je 0x60ba
0064 dec ax
0065 je 0x60c8
0067 mov dx, word ptr [bp - 2]
006a jmp 0x60d4
006c mov bx, word ptr [bp + 0xa]
006f mov di, si
0071 shl di, 6
0074 mov dl, byte ptr [bx + di + 0x68e8]
0078 jmp 0x60d2
007a mov bx, word ptr [bp + 0xa]
007d mov di, si
007f shl di, 6
0082 mov dl, byte ptr [bx + di - 0x7718]
0086 jmp 0x60d2
0088 shl si, 6
008b mov bx, word ptr [bp + 0xa]
008e mov dl, byte ptr [bx + si - 0x6718]
0092 sub dh, dh
0094 or dx, dx
0096 jne 0x60db
0098 mov dx, 0xffff
009b mov ax, dx
009d pop si
009e pop di
009f leave 
00a0 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsItNFood', 'offset': 24420, 'source': 'src/recovered/wf_IsItNFood-b827504a64.c', 'size': 26}
- {'symbol': '_IsItFoodAt', 'offset': 24446, 'source': None, 'size': 193}
- {'symbol': '_GetMap', 'offset': 24802, 'source': 'src/recovered/wf_GetMap-cddf28f960.c', 'size': 152}
- {'symbol': '_SetMap', 'offset': 24954, 'source': None, 'size': 162}
