# Recovery task _SimQueenA

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 169 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0009 mov es, ax
000b mov bx, word ptr [bp + 4]
000e mov si, word ptr es:[bx + 0x278e]
0013 and si, 0xff
0017 mov al, byte ptr es:[bx + 0x2f62]
001c sub ah, ah
001e mov di, ax
0020 mov bl, byte ptr es:[bx + 0x23a4]
0025 sub bh, bh
0027 mov word ptr [bp - 2], bx
002a shl bx, 6
002d mov byte ptr [bx + si + 0x68e8], al
0031 and al, 0x7f
0033 cmp al, 0x67
0035 jle 0xb19
0037 mov bx, di
0039 and bx, 7
003c mov es, word ptr [0xc31c]
0040 mov al, byte ptr es:[bx + 8]
0045 cwde 
0046 add ax, si
0048 mov word ptr [bp - 4], ax
004b mov es, word ptr [0xc31e]
004f mov al, byte ptr es:[bx]
0054 cwde 
0055 mov bx, ax
0057 add bx, word ptr [bp - 2]
005a mov word ptr [bp - 6], bx
005d shl bx, 6
0060 add bx, word ptr [bp - 4]
0063 mov al, byte ptr [bx + 0x68e8]
0067 sub ah, ah
0069 sub ax, di
006b cmp ax, 0xfff8
006e jne 0xae8
0070 xor ax, ax
0072 jmp 0xafd
0074 push word ptr [bp - 4]
0077 push word ptr [bp - 6]
007a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 125, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _FindInAList
007f add sp, 4
0082 or ax, ax
0084 jge 0xae4
0086 mov ax, 1
0089 or ax, ax
008b je 0xb19
008d xor al, al
008f mov bx, word ptr [bp - 2]
0092 shl bx, 6
0095 mov byte ptr [bx + si + 0x68e8], al
0099 mov es, word ptr [0xc318]
009d mov bx, word ptr [bp + 4]
00a0 mov byte ptr es:[bx + 0x2f62], al
00a5 pop si
00a6 pop di
00a7 leave 
00a8 ret 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern unsigned char far Dx8;` — src/recovered/wf_CheckNestFightB-6daf29ea80.c
- `extern int far FindInAList(int x, int y);` — src/recovered/wf_StartFightA-b2f3e31b2f.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoAntSimA', 'offset': 1240, 'source': None, 'size': None}
- {'symbol': '_SimEggA', 'offset': 2588, 'source': None, 'size': 88}
- {'symbol': '_LostHeadA', 'offset': 2846, 'source': None, 'size': 87}
- {'symbol': '_DoRestAnt', 'offset': 2934, 'source': None, 'size': 168}
