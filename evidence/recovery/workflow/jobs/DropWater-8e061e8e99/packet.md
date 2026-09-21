# Recovery task _DropWater

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 195 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 6]
0009 xor si, si
000b mov word ptr [bp - 6], di
000e mov bx, si
0010 shl bx, 6
0013 mov ax, si
0015 shl ax, 6
0018 add ax, di
001a sub bx, ax
001c add bx, word ptr [bp - 6]
001f mov al, byte ptr [bx + di + 0x48e8]
0023 sub ah, ah
0025 cmp ax, 0x4e
0028 jne 0xc8a
002a push 8
002c nop 
002d push cs
002e call 0x158a ; _SRand1
0031 add sp, 2
0034 jmp 0xc8d
0036 sub ax, 0x2f
0039 mov word ptr [bp - 4], ax
003c mov bx, si
003e shl bx, 6
0041 mov ax, si
0043 shl ax, 6
0046 add ax, di
0048 sub bx, ax
004a add bx, word ptr [bp - 6]
004d mov al, byte ptr [bp - 4]
0050 mov byte ptr [bx + di + 0x48e8], al
0054 mov bx, si
0056 shl bx, 6
0059 mov ax, si
005b shl ax, 6
005e add ax, di
0060 sub bx, ax
0062 add bx, word ptr [bp - 6]
0065 mov al, byte ptr [bx + di + 0x58e8]
0069 sub ah, ah
006b cmp ax, 0x4e
006e jne 0xcd0
0070 push 8
0072 nop 
0073 push cs
0074 call 0x158a ; _SRand1
0077 add sp, 2
007a jmp 0xcd3
007c sub ax, 0x2f
007f mov word ptr [bp - 4], ax
0082 mov bx, si
0084 shl bx, 6
0087 mov ax, si
0089 shl ax, 6
008c add ax, di
008e sub bx, ax
0090 add bx, word ptr [bp - 6]
0093 mov al, byte ptr [bp - 4]
0096 mov byte ptr [bx + di + 0x58e8], al
009a push di
009b push si
009c push 2
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
00a3 add sp, 6
00a6 push di
00a7 push si
00a8 push 3
00aa lcall <resolved loader operand; see bindings> ; [{'operand_offset': 173, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _ZapEuMapAt
00af add sp, 6
00b2 add word ptr [bp - 6], 0x40
00b6 inc si
00b7 cmp si, 0x40
00ba jge 0xd13
00bc jmp 0xc62
00bf pop si
00c0 pop di
00c1 leave 
00c2 retf 
```

## Known declaration examples

- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far SRand1(int range);` — src/recovered/wf_ExpAddFood-cd1bed365e.c
- `extern void far ZapEuMapAt(int plane, int x, int y);` — src/recovered/wf_SetMap-0b7117ef15.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_InitWater', 'offset': 2934, 'source': 'src/recovered/InitWater.c', 'size': 20}
- {'symbol': '_AddWater', 'offset': 2954, 'source': None, 'size': 201}
- {'symbol': '_PickupFoodA', 'offset': 3352, 'source': None, 'size': 109}
- {'symbol': '_DropFoodA', 'offset': 3462, 'source': None, 'size': 292}
