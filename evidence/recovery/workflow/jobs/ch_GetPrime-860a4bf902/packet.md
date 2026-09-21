# Recovery task _ch_GetPrime

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 159 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 0x10], 1
000b mov word ptr [bp - 0xe], 2
0010 xor si, si
0012 push ds
0013 push 0xb655
0016 push 0x320
0019 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 28, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
001e add sp, 6
0021 mov word ptr [bp - 0xc], ax
0024 mov word ptr [bp - 0xa], dx
0027 cmp word ptr [bp + 6], 1
002b jle 0x9a50
002d mov es, dx
002f cmp si, 0x190
0033 jl 0x9a00
0035 push ss
0036 pop ds
0037 jmp 0x9a50
0039 nop 
003a xor di, di
003c or si, si
003e jle 0x9a32
0040 mov word ptr [bp - 8], si
0043 mov ax, word ptr [bp - 0xc]
0046 mov cx, es
0048 mov ds, cx
004a mov si, di
004c mov bx, ax
004e mov ax, word ptr [bp - 0xe]
0051 cdq 
0052 idiv word ptr [bx]
0054 or dx, dx
0056 jne 0x9a26
0058 mov si, word ptr [bp - 8]
005b push ss
005c pop ds
005d jmp 0x9a45
005f nop 
0060 add bx, 2
0063 inc si
0064 cmp si, word ptr [bp - 8]
0067 jl 0x9a14
0069 mov si, word ptr [bp - 8]
006c push ss
006d pop ds
006e mov ax, word ptr [bp - 0xe]
0071 mov word ptr [bp - 0x10], ax
0074 mov bx, si
0076 shl bx, 1
0078 add bx, word ptr [bp - 0xc]
007b mov word ptr es:[bx], ax
007e inc si
007f inc word ptr [bp - 0xe]
0082 mov ax, word ptr [bp + 6]
0085 cmp word ptr [bp - 0x10], ax
0088 jl 0x99f5
008a push word ptr [bp - 0xa]
008d push word ptr [bp - 0xc]
0090 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
0095 add sp, 4
0098 mov ax, word ptr [bp - 0x10]
009b pop si
009c pop di
009d leave 
009e retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ch_CleanupTable', 'offset': 38820, 'source': None, 'size': 226}
- {'symbol': '_ch_DumpOldest', 'offset': 39046, 'source': None, 'size': 320}
- {'symbol': '_ch_SetCacheHooks', 'offset': 39526, 'source': 'src/recovered/ch_SetCacheHooks.c', 'size': 31}
- {'symbol': '_OpenIndex', 'offset': 39558, 'source': None, 'size': 194}
