# Recovery task _ConnectWall

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 241 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov bx, word ptr [bp + 6]
0009 shl bx, 6
000c add bx, word ptr [bp + 8]
000f add bx, 0x28e8
0013 mov word ptr [bp - 2], bx
0016 mov dl, byte ptr [bx]
0018 sub dh, dh
001a cmp dx, 0x60
001d jl 0x8578
001f cmp dx, 0x67
0022 jg 0x8578
0024 mov dx, 1
0027 jmp 0x857a
0029 nop 
002a xor dx, dx
002c or dx, dx
002e jne 0x8581
0030 jmp 0x863b
0033 xor si, si
0035 push word ptr [bp + 8]
0038 mov ax, word ptr [bp + 6]
003b dec ax
003c push ax
003d push 1
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0044 add sp, 6
0047 mov di, ax
0049 cmp di, 0x60
004c jl 0x85a6
004e cmp di, 0x67
0051 jg 0x85a6
0053 mov dx, 1
0056 jmp 0x85a8
0058 xor dx, dx
005a dec dx
005b jne 0x85ae
005d mov si, 1
0060 shl si, 1
0062 mov ax, word ptr [bp + 8]
0065 inc ax
0066 push ax
0067 push word ptr [bp + 6]
006a push 1
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
0071 add sp, 6
0074 mov di, ax
0076 cmp di, 0x60
0079 jl 0x85d4
007b cmp di, 0x67
007e jg 0x85d4
0080 mov dx, 1
0083 jmp 0x85d6
0085 nop 
0086 xor dx, dx
0088 dec dx
0089 jne 0x85da
008b inc si
008c shl si, 1
008e push word ptr [bp + 8]
0091 mov ax, word ptr [bp + 6]
0094 inc ax
0095 push ax
0096 push 1
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 155, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
009d add sp, 6
00a0 mov di, ax
00a2 cmp di, 0x60
00a5 jl 0x8600
00a7 cmp di, 0x67
00aa jg 0x8600
00ac mov dx, 1
00af jmp 0x8602
00b1 nop 
00b2 xor dx, dx
00b4 dec dx
00b5 jne 0x8606
00b7 inc si
00b8 shl si, 1
00ba mov ax, word ptr [bp + 8]
00bd dec ax
00be push ax
00bf push word ptr [bp + 6]
00c2 push 1
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
00c9 add sp, 6
00cc mov di, ax
00ce cmp di, 0x60
00d1 jl 0x862c
00d3 cmp di, 0x67
00d6 jg 0x862c
00d8 mov dx, 1
00db jmp 0x862e
00dd nop 
00de xor dx, dx
00e0 dec dx
00e1 jne 0x8632
00e3 inc si
00e4 mov al, byte ptr [si + 0x1bce]
00e8 mov bx, word ptr [bp - 2]
00eb mov byte ptr [bx], al
00ed pop si
00ee pop di
00ef leave 
00f0 retf 
```

## Known declaration examples

- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_WallNeighbors-7ac5fa173f.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_IncFoodHere', 'offset': 32570, 'source': None, 'size': 287}
- {'symbol': '_ConnectAll', 'offset': 32858, 'source': None, 'size': 1267}
- {'symbol': '_WallNeighbors', 'offset': 34368, 'source': 'src/recovered/wf_WallNeighbors-7ac5fa173f.c', 'size': 190}
- {'symbol': '_IsItWall', 'offset': 34558, 'source': 'src/recovered/wf_IsItWall-da7d76733f.c', 'size': 26}
