# Recovery task _SetHelpCursor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 201 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 push word ptr [0xcc7c] ; _hInst
000a push ds
000b push 0xb91e
000e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 15, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 173}}]
0013 mov es, word ptr [0xc69c]
0017 mov word ptr es:[0x72d0], ax
001b push 0x100
001e push <resolved loader operand; see bindings> ; [{'operand_offset': 31, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0021 push 0x76ac
0024 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 39, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _getcwd
0029 add sp, 6
002c mov es, word ptr [0xc69e]
0030 mov ax, 0x76ac
0033 mov dx, ax
0035 mov di, ax
0037 mov cx, 0xffff
003a xor ax, ax
003c repne scasb al, byte ptr es:[di]
003e not cx
0040 dec cx
0041 mov bx, cx
0043 cmp byte ptr es:[bx + 0x76ab], 0x5c
0049 je 0x80
004b mov <resolved loader operand; see bindings> ; [{'operand_offset': 76, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
004e mov si, ax
0050 push ds
0051 push si
0052 mov di, 0xb929
0055 mov si, dx
0057 mov cx, ds
0059 mov es, cx
005b pop ds
005c mov cx, 0xffff
005f xor ax, ax
0061 repne scasb al, byte ptr es:[di]
0063 not cx
0065 sub di, cx
0067 mov bx, cx
0069 xchg si, di
006b push ds
006c push es
006d pop ds
006e pop es
006f mov cx, 0xffff
0072 repne scasb al, byte ptr es:[di]
0074 dec di
0075 mov cx, bx
0077 shr cx, 1
0079 rep movsw word ptr es:[di], word ptr [si]
007b adc cx, cx
007d rep movsb byte ptr es:[di], byte ptr [si]
007f pop ds
0080 mov <resolved loader operand; see bindings> ; [{'operand_offset': 129, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0083 mov es, word ptr [0xc6a0]
0087 mov si, word ptr es:[0x8b3a]
008c mov cx, word ptr es:[0x8b3c]
0091 mov di, ax
0093 mov word ptr [bp - 4], si
0096 mov word ptr [bp - 2], cx
0099 push ds
009a push di
009b mov si, dx
009d pop ds
009e les di, ptr [bp - 4]
00a1 mov cx, 0xffff
00a4 xor ax, ax
00a6 repne scasb al, byte ptr es:[di]
00a8 not cx
00aa sub di, cx
00ac mov bx, cx
00ae xchg si, di
00b0 push ds
00b1 push es
00b2 pop ds
00b3 pop es
00b4 mov cx, 0xffff
00b7 repne scasb al, byte ptr es:[di]
00b9 dec di
00ba mov cx, bx
00bc shr cx, 1
00be rep movsw word ptr es:[di], word ptr [si]
00c0 adc cx, cx
00c2 rep movsb byte ptr es:[di], byte ptr [si]
00c4 pop ds
00c5 pop si
00c6 pop di
00c7 leave 
00c8 retf 
```

## Known declaration examples

- `extern unsigned int near hInst;` — src/recovered/wf_LoadFancyCursor-9a23f6f0e0.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DetectDisplay', 'offset': 202, 'source': 'src/recovered/DetectDisplay.c', 'size': 65}
- {'symbol': '_InitGraphics', 'offset': 268, 'source': None, 'size': 275}
