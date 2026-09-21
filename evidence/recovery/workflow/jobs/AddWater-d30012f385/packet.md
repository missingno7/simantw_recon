# Recovery task _AddWater

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 201 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 push di
000a nop 
000b push cs
000c call 0x2d16 ; _DrownBList
000f add sp, 2
0012 push di
0013 nop 
0014 push cs
0015 call 0x2d66 ; _DrownRList
0018 add sp, 2
001b xor si, si
001d mov word ptr [bp - 6], di
0020 mov bx, si
0022 shl bx, 6
0025 mov ax, si
0027 shl ax, 6
002a add ax, di
002c sub bx, ax
002e add bx, word ptr [bp - 6]
0031 mov al, byte ptr [bx + di + 0x48e8]
0035 sub ah, ah
0037 cmp ax, 0x20
003a jge 0xbcc
003c mov ax, 0x4e
003f jmp 0xbcf
0041 nop 
0042 add ax, 0x2f
0045 mov word ptr [bp - 4], ax
0048 mov bx, si
004a shl bx, 6
004d mov ax, si
004f shl ax, 6
0052 add ax, di
0054 sub bx, ax
0056 add bx, word ptr [bp - 6]
0059 mov al, byte ptr [bp - 4]
005c mov byte ptr [bx + di + 0x48e8], al
0060 mov bx, si
0062 shl bx, 6
0065 mov ax, si
0067 shl ax, 6
006a add ax, di
006c sub bx, ax
006e add bx, word ptr [bp - 6]
0071 mov al, byte ptr [bx + di + 0x58e8]
0075 sub ah, ah
0077 cmp ax, 0x20
007a jge 0xc0c
007c mov ax, 0x4e
007f jmp 0xc0f
0081 nop 
0082 add ax, 0x2f
0085 mov word ptr [bp - 4], ax
0088 mov bx, si
008a shl bx, 6
008d mov ax, si
008f shl ax, 6
0092 add ax, di
0094 sub bx, ax
0096 add bx, word ptr [bp - 6]
0099 mov al, byte ptr [bp - 4]
009c mov byte ptr [bx + di + 0x58e8], al
00a0 push di
00a1 push si
00a2 push 2
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
00a9 add sp, 6
00ac push di
00ad push si
00ae push 3
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
00b5 add sp, 6
00b8 add word ptr [bp - 6], 0x40
00bc inc si
00bd cmp si, 0x40
00c0 jge 0xc4f
00c2 jmp 0xbaa
00c5 pop si
00c6 pop di
00c7 leave 
00c8 retf 
```

## Known declaration examples

- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_SetMap-0b7117ef15.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_PlaceDrop', 'offset': 2764, 'source': None, 'size': 170}
- {'symbol': '_InitWater', 'offset': 2934, 'source': 'src/recovered/InitWater.c', 'size': 20}
- {'symbol': '_DropWater', 'offset': 3156, 'source': None, 'size': 195}
- {'symbol': '_PickupFoodA', 'offset': 3352, 'source': None, 'size': 109}
