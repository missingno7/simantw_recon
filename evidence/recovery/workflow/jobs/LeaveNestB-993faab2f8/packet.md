# Recovery task _LeaveNestB

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 172 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov si, word ptr [bp + 6]
0008 mov es, word ptr [0xc350]
000c mov bx, word ptr es:[0x9b6a]
0011 mov es, word ptr [0xc352]
0015 mov al, byte ptr es:[bx + 0x3d18]
001a sub ah, ah
001c mov di, ax
001e mov byte ptr es:[bx + 0x3d18], ah
0023 mov es, word ptr [0xc380]
0027 cmp byte ptr es:[si - 0x7d2e], ah
002c jne 0x5195
002e push si
002f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 50, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MakeNewHoleB
0034 add sp, 2
0037 mov es, word ptr [0xc350]
003b mov bx, word ptr es:[0x9b6a]
0040 mov es, word ptr [0xc352]
0044 mov al, byte ptr es:[bx + 0x3f0e]
0049 sub ah, ah
004b push ax
004c mov al, byte ptr es:[bx + 0x3b22]
0051 push ax
0052 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 85, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand8
0057 mov cx, di
0059 and cx, 0xf8
005d add ax, cx
005f push ax
0060 push si
0061 mov es, word ptr [0xc380]
0065 mov al, byte ptr es:[si - 0x7d2e]
006a sub ah, ah
006c push ax
006d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 112, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _ExitHole
0072 add sp, 0xa
0075 or ax, ax
0077 je 0x51e8
0079 shl si, 6
007c mov bx, word ptr [bp + 8]
007f mov byte ptr [bx + si - 0x7718], 0
0084 mov ax, 1
0087 jmp 0x5204
0089 nop 
008a mov <resolved loader operand; see bindings> ; [{'operand_offset': 139, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
008d mov es, ax
008f mov <resolved loader operand; see bindings> ; [{'operand_offset': 144, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0092 mov ds, ax
0094 mov ax, di
0096 mov bx, word ptr [0x9b6a]
009a mov byte ptr es:[bx + 0x3d18], al
009f xor ax, ax
00a1 mov byte ptr es:[bx + 0x3b22], al
00a6 push ss
00a7 pop ds
00a8 pop si
00a9 pop di
00aa leave 
00ab retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far SRand8(void);` — src/recovered/RandTurn.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutB-794c50ee5a.c
- `extern int far SRand8(void);` — src/recovered/wf_RaidOutR-a39ba19d03.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoDigInB', 'offset': 19408, 'source': None, 'size': 735}
- {'symbol': '_DoDigOutB', 'offset': 20144, 'source': None, 'size': 686}
- {'symbol': '_GetOutB', 'offset': 21002, 'source': None, 'size': 314}
- {'symbol': '_DoAntSimR', 'offset': 21316, 'source': 'src/recovered/wf_DoAntSimR-682e4ecadf.c', 'size': 95}
