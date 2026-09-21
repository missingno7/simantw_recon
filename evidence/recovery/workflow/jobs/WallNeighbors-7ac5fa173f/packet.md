# Recovery task _WallNeighbors

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 190 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 xor si, si
0007 push word ptr [bp + 8]
000a mov ax, word ptr [bp + 6]
000d dec ax
000e push ax
000f push word ptr [bp + 0xa]
0012 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 21, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0017 add sp, 6
001a mov di, ax
001c cmp di, 0x60
001f jl 0x866c
0021 cmp di, 0x67
0024 jg 0x866c
0026 mov dx, 1
0029 jmp 0x866e
002b nop 
002c xor dx, dx
002e dec dx
002f jne 0x8674
0031 mov si, 1
0034 shl si, 1
0036 mov ax, word ptr [bp + 8]
0039 inc ax
003a push ax
003b push word ptr [bp + 6]
003e push word ptr [bp + 0xa]
0041 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 68, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0046 add sp, 6
0049 mov di, ax
004b cmp di, 0x60
004e jl 0x869a
0050 cmp di, 0x67
0053 jg 0x869a
0055 mov dx, 1
0058 jmp 0x869c
005a xor dx, dx
005c dec dx
005d jne 0x86a0
005f inc si
0060 shl si, 1
0062 push word ptr [bp + 8]
0065 mov ax, word ptr [bp + 6]
0068 inc ax
0069 push ax
006a push word ptr [bp + 0xa]
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0072 add sp, 6
0075 mov di, ax
0077 cmp di, 0x60
007a jl 0x86c6
007c cmp di, 0x67
007f jg 0x86c6
0081 mov dx, 1
0084 jmp 0x86c8
0086 xor dx, dx
0088 dec dx
0089 jne 0x86cc
008b inc si
008c shl si, 1
008e mov ax, word ptr [bp + 8]
0091 dec ax
0092 push ax
0093 push word ptr [bp + 6]
0096 push word ptr [bp + 0xa]
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
009e add sp, 6
00a1 mov di, ax
00a3 cmp di, 0x60
00a6 jl 0x86f2
00a8 cmp di, 0x67
00ab jg 0x86f2
00ad mov dx, 1
00b0 jmp 0x86f4
00b2 xor dx, dx
00b4 dec dx
00b5 jne 0x86f8
00b7 inc si
00b8 mov ax, si
00ba pop si
00bb pop di
00bc leave 
00bd retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ConnectAll', 'offset': 32858, 'source': None, 'size': 1267}
- {'symbol': '_ConnectWall', 'offset': 34126, 'source': None, 'size': 241}
- {'symbol': '_IsItWall', 'offset': 34558, 'source': 'src/recovered/wf_IsItWall-da7d76733f.c', 'size': 26}
- {'symbol': '_FillDirtB', 'offset': 34584, 'source': None, 'size': 193}
