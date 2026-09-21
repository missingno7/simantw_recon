# Recovery task _SimEggR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 223 bytes.

```asm
0000 enter 8, 0
0004 push si
0005 mov bx, 0x9b6a
0008 mov es, word ptr [0xc384]
000c mov word ptr [bp - 8], bx
000f mov word ptr [bp - 6], es
0012 mov bx, word ptr es:[bx]
0015 mov es, word ptr [0xc386]
0019 mov al, byte ptr es:[bx + 0x46e6]
001e sub ah, ah
0020 mov word ptr [bp - 2], ax
0023 mov si, 0xffff
0026 cmp word ptr [0xac84], 1 ; _RpopT
002b jne 0x62d8
002d mov ax, 0x1f
0030 jmp 0x62db
0032 mov ax, 0x7f
0035 mov es, word ptr [0xc39a]
0039 test word ptr es:[0x75fc], ax
003e jne 0x633d
0040 inc word ptr [bp - 2]
0043 mov al, byte ptr [bp - 2]
0046 and al, 0xf
0048 cmp al, 8
004a jne 0x633d
004c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0051 mov es, word ptr [0xc39c]
0055 mov cx, ax
0057 mov ax, word ptr es:[0x7690]
005b mov dx, 7
005e mov bx, dx
0060 cdq 
0061 idiv bx
0063 mov bx, dx
0065 shl bx, 3
0068 add bx, cx
006a mov es, word ptr [0xc39e]
006e mov al, byte ptr es:[bx - 0x7682]
0073 cwde 
0074 mov si, ax
0076 shl ax, 3
0079 add ax, 0x82
007c mov word ptr [bp - 2], ax
007f push si
0080 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 131, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _GetNewModeR
0085 add sp, 2
0088 les bx, ptr [bp - 8]
008b mov bx, word ptr es:[bx]
008e mov es, word ptr [0xc386]
0092 mov byte ptr es:[bx + 0x44f0], al
0097 mov es, word ptr [0xc38c]
009b cmp word ptr es:[0x85fc], 0
00a1 je 0x635d
00a3 or si, si
00a5 jge 0x635d
00a7 push 3
00a9 push word ptr [bp + 8]
00ac push word ptr [bp + 6]
00af lcall <resolved loader operand; see bindings> ; [{'operand_offset': 178, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _EggBalloons
00b4 add sp, 6
00b7 mov al, byte ptr [bp - 2]
00ba mov si, word ptr [bp + 6]
00bd shl si, 6
00c0 mov bx, word ptr [bp + 8]
00c3 mov byte ptr [bx + si - 0x6718], al
00c7 les bx, ptr [bp - 8]
00ca mov bx, word ptr es:[bx]
00cd mov es, word ptr [0xc386]
00d1 mov byte ptr es:[bx + 0x46e6], al
00d6 mov byte ptr es:[bx + 0x48dc], 0
00dc pop si
00dd leave 
00de retf 
```

## Known declaration examples

- `extern int near RpopT;` — src/recovered/DecEatR.c
- `extern int near RpopT;` — src/recovered/wf_GstrB-b09a4bcc53.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_GetRandDir-2664e9d7f9.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_CheckNestFightR', 'offset': 24994, 'source': None, 'size': 160}
- {'symbol': '_DropFoodR', 'offset': 25154, 'source': None, 'size': 100}
- {'symbol': '_SimQueenR', 'offset': 25478, 'source': None, 'size': 639}
- {'symbol': '_QueenMoveR', 'offset': 26118, 'source': None, 'size': 246}
