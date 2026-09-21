# Recovery task _InitSow

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 146 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov si, 4
0009 push 0x80
000c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0011 add sp, 2
0014 mov di, ax
0016 push 0x40
0018 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 27, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
001d add sp, 2
0020 mov bx, ax
0022 mov word ptr [bp - 2], bx
0025 mov ax, di
0027 shl ax, 6
002a add bx, ax
002c add bx, 0x28e8
0030 mov word ptr [bp - 4], bx
0033 cmp byte ptr [bx], 0x10
0036 jae 0x3f7f
0038 mov es, word ptr [0xc574]
003c mov word ptr es:[si - 0x6438], di
0041 mov ax, word ptr [bp - 2]
0044 mov es, word ptr [0xc576]
0048 mov word ptr es:[si - 0x6426], ax
004d push 8
004f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 82, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0054 add sp, 2
0057 mov es, word ptr [0xc578]
005b mov word ptr es:[si - 0x63d6], ax
0060 mov bx, word ptr [bp - 4]
0063 mov al, byte ptr [bx]
0065 sub ah, ah
0067 mov es, word ptr [0xc57a]
006b mov word ptr es:[si + 0x78cc], ax
0070 mov es, word ptr [0xc578]
0074 mov di, word ptr es:[si - 0x63d6]
0079 mov es, word ptr [0xc57c]
007d mov al, byte ptr es:[di - 0x7570]
0082 mov byte ptr [bx], al
0084 sub si, 2
0087 or si, si
0089 je 0x3f86
008b jmp 0x3f01
008e pop si
008f pop di
0090 leave 
0091 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_StartMigrate', 'offset': 15858, 'source': None, 'size': 121}
- {'symbol': '_EndMigrate', 'offset': 15980, 'source': None, 'size': 139}
- {'symbol': '_DoSow', 'offset': 16266, 'source': None, 'size': 315}
- {'symbol': '_InitAntLions', 'offset': 16582, 'source': None, 'size': 347}
