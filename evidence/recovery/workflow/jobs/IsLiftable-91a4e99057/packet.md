# Recovery task _IsLiftable

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 275 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov si, word ptr [bp + 0xa]
000c push si
000d push di
000e push word ptr [bp + 6]
0011 lea ax, [bp - 6]
0014 push ss
0015 push ax
0016 nop 
0017 push cs
0018 call 0x88a2 ; _FindEggAt
001b add sp, 0xa
001e mov word ptr [bp - 4], ax
0021 mov word ptr [bp - 2], 0xffff
0026 cmp word ptr [bp + 6], 1
002a jg 0x980e
002c or di, di
002e jl 0x9820
0030 cmp di, 0x7f
0033 jg 0x9820
0035 or si, si
0037 jl 0x9820
0039 cmp si, 0x3f
003c jg 0x9820
003e mov dx, 1
0041 jmp 0x9822
0043 nop 
0044 or di, di
0046 jl 0x9820
0048 cmp di, 0x3f
004b jg 0x9820
004d or si, si
004f jl 0x9820
0051 cmp si, 0x3f
0054 jle 0x9808
0056 xor dx, dx
0058 dec dx
0059 je 0x982a
005b mov dx, word ptr [bp - 2]
005e jmp 0x9861
0060 mov ax, word ptr [bp + 6]
0063 or ax, ax
0065 jl 0x9825
0067 jo 0x9825
0069 dec ax
006a jle 0x983e
006c dec ax
006d je 0x984a
006f dec ax
0070 je 0x9856
0072 jmp 0x9825
0074 mov bx, di
0076 shl bx, 6
0079 mov dl, byte ptr [bx + si + 0x28e8]
007d jmp 0x985f
007f nop 
0080 mov bx, di
0082 shl bx, 6
0085 mov dl, byte ptr [bx + si + 0x48e8]
0089 jmp 0x985f
008b nop 
008c mov bx, di
008e shl bx, 6
0091 mov dl, byte ptr [bx + si + 0x58e8]
0095 sub dh, dh
0097 mov si, dx
0099 cmp word ptr [bp + 6], 1
009d jg 0x9876
009f push si
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItFood
00a5 add sp, 2
00a8 mov di, ax
00aa jmp 0x9888
00ac cmp si, 0x10
00af jl 0x9886
00b1 cmp si, 0x13
00b4 jg 0x9886
00b6 mov di, 1
00b9 jmp 0x9888
00bb nop 
00bc xor di, di
00be or di, di
00c0 jne 0x98d6
00c2 cmp word ptr [bp + 6], 1
00c6 jg 0x98a4
00c8 jne 0x98ae
00ca cmp si, 0x51
00cd jl 0x98ae
00cf cmp si, 0x53
00d2 jg 0x98ae
00d4 mov dx, 1
00d7 jmp 0x98b0
00d9 nop 
00da cmp si, 0x30
00dd jl 0x98ae
00df cmp si, 0x31
00e2 jle 0x989e
00e4 xor dx, dx
00e6 or dx, dx
00e8 jne 0x98d6
00ea mov dl, byte ptr [bp - 4]
00ed and dx, 0x7f
00f0 cmp dx, 1
00f3 jl 0x98ca
00f5 cmp dx, 7
00f8 jg 0x98ca
00fa mov dx, 1
00fd jmp 0x98cc
00ff nop 
0100 xor dx, dx
0102 or dx, dx
0104 jne 0x98d6
0106 xor ax, ax
0108 pop si
0109 pop di
010a leave 
010b retf 
010c mov ax, 1
010f pop si
0110 pop di
0111 leave 
0112 retf 
```

## Known declaration examples

- `extern int far IsItFood(int tile);` — src/recovered/wf_IsThisFood-26910209bd.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsLessThanHole', 'offset': 38788, 'source': 'src/recovered/IsLessThanHole.c', 'size': 37}
- {'symbol': '_IsSamePlane', 'offset': 38826, 'source': None, 'size': 32}
- {'symbol': '_TryMyDropOrLift', 'offset': 39134, 'source': None, 'size': 619}
- {'symbol': '_IsItAHole', 'offset': 39754, 'source': 'src/recovered/wf_IsItAHole-fd9d6ad240.c', 'size': 184}
