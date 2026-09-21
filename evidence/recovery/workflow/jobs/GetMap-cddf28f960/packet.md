# Recovery task _GetMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 152 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 6]
0009 mov word ptr [bp - 2], 0xffff
000e cmp dx, 1
0011 jg 0x6112
0013 mov si, word ptr [bp + 8]
0016 or si, si
0018 jl 0x612a
001a cmp si, 0x7f
001d jg 0x612a
001f cmp word ptr [bp + 0xa], 0
0023 jl 0x612a
0025 cmp word ptr [bp + 0xa], 0x3f
0029 jg 0x612a
002b mov bx, 1
002e jmp 0x612c
0030 mov si, word ptr [bp + 8]
0033 or si, si
0035 jl 0x612a
0037 cmp si, 0x3f
003a jg 0x612a
003c cmp word ptr [bp + 0xa], 0
0040 jl 0x612a
0042 cmp word ptr [bp + 0xa], 0x3f
0046 jle 0x610d
0048 xor bx, bx
004a dec bx
004b je 0x6138
004d mov dx, word ptr [bp - 2]
0050 mov ax, dx
0052 pop si
0053 pop di
0054 leave 
0055 retf 
0056 mov ax, dx
0058 or ax, ax
005a jl 0x612f
005c jo 0x612f
005e dec ax
005f jle 0x614c
0061 dec ax
0062 je 0x615a
0064 dec ax
0065 je 0x6168
0067 jmp 0x612f
0069 nop 
006a mov bx, word ptr [bp + 0xa]
006d mov di, si
006f shl di, 6
0072 mov dl, byte ptr [bx + di + 0x28e8]
0076 jmp 0x6172
0078 mov bx, word ptr [bp + 0xa]
007b mov di, si
007d shl di, 6
0080 mov dl, byte ptr [bx + di + 0x48e8]
0084 jmp 0x6172
0086 shl si, 6
0089 mov bx, word ptr [bp + 0xa]
008c mov dl, byte ptr [bx + si + 0x58e8]
0090 sub dh, dh
0092 mov ax, dx
0094 pop si
0095 pop di
0096 leave 
0097 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsItFoodAt', 'offset': 24446, 'source': None, 'size': 193}
- {'symbol': '_GetLife', 'offset': 24640, 'source': None, 'size': 161}
- {'symbol': '_SetMap', 'offset': 24954, 'source': None, 'size': 162}
- {'symbol': '_ClearLife', 'offset': 25116, 'source': None, 'size': 258}
