# Recovery task _IsItAHole

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 184 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov dx, word ptr [bp + 6]
0009 cmp dx, 1
000c jg 0x9b6a
000e push word ptr [bp + 0xa]
0011 push word ptr [bp + 8]
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 6}}] ; _IsItHole
0019 add sp, 4
001c pop si
001d pop di
001e leave 
001f retf 
0020 mov si, word ptr [bp + 0xa]
0023 or si, si
0025 jle 0x9b74
0027 jmp 0x9bfc
002a mov word ptr [bp - 2], 0xffff
002f cmp dx, 1
0032 jg 0x9b98
0034 mov di, word ptr [bp + 8]
0037 or di, di
0039 jl 0x9bad
003b cmp di, 0x7f
003e jg 0x9bad
0040 or si, si
0042 jl 0x9bad
0044 cmp si, 0x3f
0047 jg 0x9bad
0049 mov cx, 1
004c jmp 0x9baf
004e mov di, word ptr [bp + 8]
0051 or di, di
0053 jl 0x9bad
0055 cmp di, 0x3f
0058 jg 0x9bad
005a or si, si
005c jl 0x9bad
005e cmp si, 0x3f
0061 jle 0x9b93
0063 xor cx, cx
0065 dec cx
0066 je 0x9bb8
0068 mov dx, word ptr [bp - 2]
006b jmp 0x9bef
006d nop 
006e mov ax, dx
0070 or ax, ax
0072 jl 0x9bb2
0074 jo 0x9bb2
0076 dec ax
0077 jle 0x9bcc
0079 dec ax
007a je 0x9bd8
007c dec ax
007d je 0x9be4
007f jmp 0x9bb2
0081 nop 
0082 mov bx, di
0084 shl bx, 6
0087 mov dl, byte ptr [bx + si + 0x28e8]
008b jmp 0x9bed
008d nop 
008e mov bx, di
0090 shl bx, 6
0093 mov dl, byte ptr [bx + si + 0x48e8]
0097 jmp 0x9bed
0099 nop 
009a mov bx, di
009c shl bx, 6
009f mov dl, byte ptr [bx + si + 0x58e8]
00a3 sub dh, dh
00a5 cmp dx, 0x18
00a8 jne 0x9bfc
00aa mov ax, 1
00ad pop si
00ae pop di
00af leave 
00b0 retf 
00b1 nop 
00b2 xor ax, ax
00b4 pop si
00b5 pop di
00b6 leave 
00b7 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IsLiftable', 'offset': 38858, 'source': None, 'size': 275}
- {'symbol': '_TryMyDropOrLift', 'offset': 39134, 'source': None, 'size': 619}
- {'symbol': '_IsValidA', 'offset': 39938, 'source': 'src/recovered/IsValidA.c', 'size': 36}
- {'symbol': '_IsValidB', 'offset': 39974, 'source': 'src/recovered/IsValidB.c', 'size': 36}
