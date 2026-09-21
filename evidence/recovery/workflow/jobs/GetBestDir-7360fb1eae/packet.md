# Recovery task _GetBestDir

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 246 bytes.

```asm
0000 enter 0xc, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 0xc], 0xffff
000b push word ptr [bp + 0xe]
000e push word ptr [bp + 0xc]
0011 push word ptr [bp + 0xa]
0014 push word ptr [bp + 8]
0017 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 26, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
001c add sp, 8
001f mov word ptr [bp - 8], ax
0022 or ax, ax
0024 jg 0x4087
0026 jmp 0x4128
0029 mov word ptr [bp - 0xa], 0xfffe
002e xor si, si
0030 mov di, word ptr [bp + 6]
0033 mov es, word ptr [0xc364]
0037 mov al, byte ptr es:[si + 8]
003c cwde 
003d add ax, word ptr [bp + 0xa]
0040 mov word ptr [bp - 2], ax
0043 push ax
0044 mov es, word ptr [0xc366]
0048 mov al, byte ptr es:[si]
004d cwde 
004e add ax, word ptr [bp + 8]
0051 mov word ptr [bp - 4], ax
0054 push ax
0055 push di
0056 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 89, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetMap
005b add sp, 6
005e mov word ptr [bp - 6], ax
0061 push word ptr [bp - 2]
0064 push word ptr [bp - 4]
0067 push di
0068 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 107, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsNotObstacle
006d add sp, 6
0070 dec ax
0071 jne 0x413b
0073 push word ptr [bp - 6]
0076 push di
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 122, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsThisPebble
007c add sp, 4
007f or ax, ax
0081 jne 0x413b
0083 push word ptr [bp + 0xe]
0086 push word ptr [bp + 0xc]
0089 push word ptr [bp - 2]
008c push word ptr [bp - 4]
008f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 146, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDis
0094 add sp, 8
0097 mov word ptr [bp - 6], ax
009a cmp ax, word ptr [bp - 8]
009d jge 0x413b
009f push word ptr [bp - 2]
00a2 push word ptr [bp - 4]
00a5 push di
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetLife
00ab add sp, 6
00ae or ax, ax
00b0 jg 0x4132
00b2 push word ptr [bp - 2]
00b5 push word ptr [bp - 4]
00b8 push di
00b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 188, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsClearTile
00be add sp, 6
00c1 dec ax
00c2 jne 0x4132
00c4 mov word ptr [bp - 0xc], si
00c7 jmp 0x4135
00c9 nop 
00ca mov dx, word ptr [bp - 0xc]
00cd mov ax, dx
00cf pop si
00d0 pop di
00d1 leave 
00d2 retf 
00d3 nop 
00d4 mov word ptr [bp - 0xa], si
00d7 mov ax, word ptr [bp - 6]
00da mov word ptr [bp - 8], ax
00dd inc si
00de cmp si, 8
00e1 jge 0x4144
00e3 jmp 0x4091
00e6 mov dx, word ptr [bp - 0xc]
00e9 or dx, dx
00eb jge 0x414e
00ed mov dx, word ptr [bp - 0xa]
00f0 mov ax, dx
00f2 pop si
00f3 pop di
00f4 leave 
00f5 retf 
```

## Known declaration examples

- `extern int far GetMap(int plane, int x, int y);` — src/recovered/wf_WallNeighbors-7ac5fa173f.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_AddAntLion-3b9ada1a24.c
- `extern int far IsClearTile(int plane, int x, int y);` — src/recovered/wf_ExpAddAnt-6ef6c47e91.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimEggB', 'offset': 15520, 'source': None, 'size': 290}
- {'symbol': '_SimQueenB', 'offset': 15810, 'source': None, 'size': 666}
- {'symbol': '_QueenMoveB', 'offset': 16724, 'source': None, 'size': 246}
- {'symbol': '_MakeNewTailB', 'offset': 16970, 'source': None, 'size': 101}
