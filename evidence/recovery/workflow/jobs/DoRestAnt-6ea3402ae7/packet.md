# Recovery task _DoRestAnt

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 168 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc318]
0009 mov bx, word ptr [bp + 4]
000c mov si, word ptr es:[bx + 0x23a4]
0011 and si, 0xff
0015 mov al, byte ptr es:[bx + 0x278e]
001a sub ah, ah
001c mov di, ax
001e push di
001f push si
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
0025 add sp, 4
0028 or ax, ax
002a jne 0xba6
002c xor dx, dx
002e jmp 0xbda
0030 mov es, word ptr [0xc320]
0034 cmp word ptr es:[0x9b6e], 0
003a jne 0xbc0
003c mov bx, si
003e shl bx, 6
0041 cmp byte ptr [bx + di + 0x28e8], 0x50
0046 jne 0xba2
0048 jmp 0xbd7
004a mov bx, si
004c shl bx, 6
004f mov cl, byte ptr [bx + di + 0x28e8]
0053 sub ch, ch
0055 cmp cx, 0x80
0059 jl 0xba2
005b cmp cx, 0x8f
005f jg 0xba2
0061 mov dx, 1
0064 dec dx
0065 jne 0xbe8
0067 push word ptr [bp + 4]
006a push di
006b push si
006c call 0x257a ; _GoInNest
006f jmp 0xc17
0071 nop 
0072 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 117, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0077 or ax, ax
0079 jne 0xc02
007b mov es, word ptr [0xc318]
007f mov bx, word ptr [bp + 4]
0082 mov byte ptr es:[bx + 0x2b78], 2
0088 pop si
0089 pop di
008a leave 
008b ret 
008c mov es, word ptr [0xc322]
0090 cmp word ptr es:[0x85fc], 1
0096 jne 0xc1a
0098 push 1
009a push di
009b push si
009c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 159, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _RestBalloons
00a1 add sp, 6
00a4 pop si
00a5 pop di
00a6 leave 
00a7 ret 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/PillGetLife.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimQueenA', 'offset': 2676, 'source': None, 'size': 169}
- {'symbol': '_LostHeadA', 'offset': 2846, 'source': None, 'size': 87}
- {'symbol': '_DoRepoLoit', 'offset': 3102, 'source': None, 'size': 91}
- {'symbol': '_DoRepoExit', 'offset': 3194, 'source': None, 'size': 208}
