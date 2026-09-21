# Recovery task _CenterEdit

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 180 bytes.

```asm
0000 enter 2, 0
0004 mov ax, word ptr [0xcd7a] ; _editHeight
0007 cdq 
0008 sub ax, dx
000a sar ax, 1
000c mov cx, word ptr [bp + 8]
000f mov es, word ptr [0xbf92]
0013 sub cx, word ptr es:[0x7d30]
0018 sub cx, ax
001a push cx
001b mov ax, word ptr [0xcc80] ; _editWidth
001e cdq 
001f sub ax, dx
0021 sar ax, 1
0023 mov cx, word ptr [bp + 6]
0026 sub cx, word ptr es:[0x7d2e]
002b sub cx, ax
002d push cx
002e call 0x616c
0031 add sp, 4
0034 or ax, ax
0036 je 0x16ce
0038 mov word ptr [bp - 2], 0x40
003d mov <resolved loader operand; see bindings> ; [{'operand_offset': 62, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0040 mov es, ax
0042 mov ax, word ptr [0xcc76] ; _MapPlane
0045 or ax, ax
0047 jl 0x166e
0049 jo 0x166e
004b dec ax
004c jle 0x1674
004e mov cx, 0x40
0051 jmp 0x1677
0053 nop 
0054 mov cx, 0x80
0057 cmp word ptr es:[0x7d2e], 0
005d jge 0x1688
005f mov word ptr es:[0x7d2e], 0
0066 jmp 0x169d
0068 mov bx, word ptr [0xcc80] ; _editWidth
006c mov ax, word ptr es:[0x7d2e]
0070 add ax, bx
0072 cmp ax, cx
0074 jle 0x169d
0076 sub cx, bx
0078 mov word ptr es:[0x7d2e], cx
007d cmp word ptr es:[0x7d30], 0
0083 jge 0x16ae
0085 mov word ptr es:[0x7d30], 0
008c jmp 0x16c6
008e mov bx, word ptr [0xcd7a] ; _editHeight
0092 mov ax, word ptr es:[0x7d30]
0096 add ax, bx
0098 cmp ax, 0x40
009b jle 0x16c6
009d mov ax, 0x40
00a0 sub ax, bx
00a2 mov word ptr es:[0x7d30], ax
00a6 mov dx, 1
00a9 mov ax, dx
00ab leave 
00ac retf 
00ad nop 
00ae xor dx, dx
00b0 mov ax, dx
00b2 leave 
00b3 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editHeight;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editHeight;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near editWidth;` — src/recovered/wf_EggBalloons-c5deff5dd7.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_win_DrawEditWindow', 'offset': 5360, 'source': None, 'size': 195}
- {'symbol': '_BoundEditPosition', 'offset': 5556, 'source': None, 'size': 107}
- {'symbol': '_DrawEditGraphs', 'offset': 6538, 'source': None, 'size': 379}
- {'symbol': '_SetEditWinTitle', 'offset': 6918, 'source': None, 'size': 232}
