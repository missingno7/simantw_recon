# Recovery task _DoSow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 315 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 xor si, si
0008 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
000d or ax, ax
000f jne 0x3f9e
0011 jmp 0x40b6
0014 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 23, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand4
0019 or ax, ax
001b jne 0x3fea
001d push 3
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0024 add sp, 2
0027 mov es, word ptr [0xc578]
002b mov cl, byte ptr es:[si - 0x63d6]
0030 add cl, al
0032 dec cl
0034 and cx, 7
0037 mov word ptr es:[si - 0x63d6], cx
003c mov bx, cx
003e mov es, word ptr [0xc57c]
0042 mov al, byte ptr es:[bx - 0x7570]
0047 mov es, word ptr [0xc576]
004b mov bx, word ptr es:[si - 0x6426]
0050 mov es, word ptr [0xc574]
0054 mov di, word ptr es:[si - 0x6438]
0059 shl di, 6
005c mov byte ptr [bx + di + 0x28e8], al
0060 mov es, word ptr [0xc578]
0064 mov bx, word ptr es:[si - 0x63d6]
0069 mov es, word ptr [0xc57e]
006d mov al, byte ptr es:[bx + 8]
0072 cwde 
0073 mov di, ax
0075 mov ax, bx
0077 mov bx, si
0079 add bx, 0x9bda
007d mov es, word ptr [0xc576]
0081 mov word ptr [bp - 6], bx
0084 mov word ptr [bp - 4], es
0087 add di, word ptr es:[bx]
008a push di
008b mov bx, ax
008d mov es, word ptr [0xc580]
0091 mov al, byte ptr es:[bx]
0096 cwde 
0097 mov bx, si
0099 add bx, 0x9bc8
009d mov es, word ptr [0xc574]
00a1 mov word ptr [bp - 0xa], bx
00a4 mov word ptr [bp - 8], es
00a7 add ax, word ptr es:[bx]
00aa mov word ptr [bp - 2], ax
00ad push ax
00ae lcall <resolved loader operand; see bindings> ; [{'operand_offset': 177, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidA
00b3 add sp, 4
00b6 or ax, ax
00b8 je 0x40b6
00ba mov bx, word ptr [bp - 2]
00bd shl bx, 6
00c0 add bx, di
00c2 mov word ptr [bp - 0xc], bx
00c5 cmp byte ptr [bx + 0x68e8], 0
00ca jne 0x40b6
00cc mov cl, byte ptr [bx + 0x28e8]
00d0 sub ch, ch
00d2 cmp cx, 0x10
00d5 jge 0x40b6
00d7 mov es, word ptr [0xc57a]
00db mov al, byte ptr es:[si + 0x78cc]
00e0 les bx, ptr [bp - 6]
00e3 mov dx, word ptr es:[bx]
00e6 mov word ptr [bp - 0x10], bx
00e9 mov word ptr [bp - 0xe], es
00ec les bx, ptr [bp - 0xa]
00ef mov bx, word ptr es:[bx]
00f2 shl bx, 6
00f5 add bx, dx
00f7 mov byte ptr [bx + 0x28e8], al
00fb mov es, word ptr [0xc57a]
00ff mov word ptr es:[si + 0x78cc], cx
0104 mov es, word ptr [0xc578]
0108 mov bx, word ptr es:[si - 0x63d6]
010d mov es, word ptr [0xc57c]
0111 mov al, byte ptr es:[bx - 0x7570]
0116 mov bx, word ptr [bp - 0xc]
0119 mov byte ptr [bx + 0x28e8], al
011d mov ax, word ptr [bp - 2]
0120 les bx, ptr [bp - 0xa]
0123 mov word ptr es:[bx], ax
0126 les bx, ptr [bp - 0x10]
0129 mov word ptr es:[bx], di
012c add si, 2
012f cmp si, 6
0132 jge 0x40c1
0134 jmp 0x3f92
0137 pop si
0138 pop di
0139 leave 
013a retf 
```

## Known declaration examples

- `extern int far IsValidA(int x, int y);` — src/recovered/wf_tu_simtwo_4CDC_StorePillarMap_4_scaffold-c16d27de40.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_tu_antedit_7022_DoTool_15_scaffold-064731bfb6.c
- `extern int far SRand4(void);` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_EndMigrate', 'offset': 15980, 'source': None, 'size': 139}
- {'symbol': '_InitSow', 'offset': 16120, 'source': None, 'size': 146}
- {'symbol': '_InitAntLions', 'offset': 16582, 'source': None, 'size': 347}
- {'symbol': '_AddRandAntLion', 'offset': 16930, 'source': None, 'size': 285}
