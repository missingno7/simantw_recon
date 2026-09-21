# Recovery task _SimEggB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 290 bytes.

```asm
0000 enter 8, 0
0004 push si
0005 mov bx, 0x9b6a
0008 mov es, word ptr [0xc350]
000c mov word ptr [bp - 8], bx
000f mov word ptr [bp - 6], es
0012 mov bx, word ptr es:[bx]
0015 mov es, word ptr [0xc352]
0019 mov al, byte ptr es:[bx + 0x3d18]
001e sub ah, ah
0020 mov word ptr [bp - 4], ax
0023 mov word ptr [bp - 2], 0xffff
0028 cmp word ptr [0xac82], 2 ; _BpopT
002d jg 0x3cd4
002f mov bx, 0x1f
0032 jmp 0x3cd7
0034 mov bx, 0x7f
0037 mov es, word ptr [0xc368]
003b test word ptr es:[0x75fc], bx
0040 je 0x3ce5
0042 jmp 0x3d78
0045 inc word ptr [bp - 4]
0048 mov al, byte ptr [bp - 4]
004b and al, 0xf
004d cmp al, 8
004f je 0x3cf4
0051 jmp 0x3d78
0054 mov es, word ptr [0xc36a]
0058 cmp word ptr es:[0x9fce], 0
005e jne 0x3d32
0060 push 0xff
0063 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 102, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SGRand
0068 add sp, 2
006b mov es, word ptr [0xc36c]
006f mov cx, word ptr es:[0x9c78]
0074 shr cx, 7
0077 cmp cx, ax
0079 jge 0x3d32
007b mov word ptr [bp - 4], 0
0080 mov es, word ptr [0xc360]
0084 add word ptr es:[0x7c1e], 1
008a adc word ptr es:[0x7c20], 0
0090 jmp 0x3d78
0092 mov es, word ptr [0xc36e]
0096 mov ax, word ptr es:[0x8a56]
009a mov word ptr [bp - 2], ax
009d mov cx, ax
009f shl ax, 3
00a2 add ax, 2
00a5 mov word ptr [bp - 4], ax
00a8 cmp cx, 2
00ab jne 0x3d60
00ad les bx, ptr [bp - 8]
00b0 mov bx, word ptr es:[bx]
00b3 mov es, word ptr [0xc352]
00b7 mov byte ptr es:[bx + 0x3b22], 1
00bd jmp 0x3d78
00bf nop 
00c0 push cx
00c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 196, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeB
00c6 add sp, 2
00c9 les bx, ptr [bp - 8]
00cc mov bx, word ptr es:[bx]
00cf mov es, word ptr [0xc352]
00d3 mov byte ptr es:[bx + 0x3b22], al
00d8 mov es, word ptr [0xc358]
00dc cmp word ptr es:[0x85fc], 0
00e2 je 0x3d9a
00e4 cmp word ptr [bp - 2], 0
00e8 jge 0x3d9a
00ea push 2
00ec push word ptr [bp + 8]
00ef push word ptr [bp + 6]
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EggBalloons
00f7 add sp, 6
00fa mov al, byte ptr [bp - 4]
00fd mov si, word ptr [bp + 6]
0100 shl si, 6
0103 mov bx, word ptr [bp + 8]
0106 mov byte ptr [bx + si - 0x7718], al
010a les bx, ptr [bp - 8]
010d mov bx, word ptr es:[bx]
0110 mov es, word ptr [0xc352]
0114 mov byte ptr es:[bx + 0x3d18], al
0119 mov byte ptr es:[bx + 0x3f0e], 0
011f pop si
0120 leave 
0121 retf 
```

## Known declaration examples

- `extern int near BpopT;` — src/recovered/DecEatB.c
- `extern int near BpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CheckNestFightB', 'offset': 15266, 'source': 'src/recovered/wf_CheckNestFightB-6daf29ea80.c', 'size': 154}
- {'symbol': '_DropFoodB', 'offset': 15420, 'source': None, 'size': 100}
- {'symbol': '_SimQueenB', 'offset': 15810, 'source': None, 'size': 666}
- {'symbol': '_GetBestDir', 'offset': 16478, 'source': None, 'size': 246}
