# Recovery task _EditMsgBalloon

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 114 bytes.

```asm
0000 enter 0x200, 0
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0007 mov es, ax
0009 mov bx, word ptr [bp + 6]
000c sar bx, 4
000f add bx, word ptr es:[0x7d2e]
0014 mov cx, word ptr [bp + 8]
0017 sar cx, 4
001a add cx, word ptr es:[0x7d30]
001f mov ax, word ptr [0xcc76] ; _MapPlane
0022 cmp word ptr [bp + 0xa], ax
0025 jne 0x578a
0027 cmp word ptr es:[0x7d2e], bx
002c jg 0x578a
002e mov ax, word ptr es:[0x7d2e]
0032 add ax, word ptr [0xcc80] ; _editWidth
0036 cmp ax, bx
0038 jle 0x578a
003a mov ax, cx
003c sub ax, 3
003f cmp word ptr es:[0x7d30], ax
0044 jg 0x578a
0046 mov ax, word ptr es:[0x7d30]
004a add ax, word ptr [0xcd7a] ; _editHeight
004e cmp ax, cx
0050 jle 0x578a
0052 mov dx, 1
0055 jmp 0x578c
0057 nop 
0058 xor dx, dx
005a or dx, dx
005c je 0x57a2
005e mov ax, word ptr [bp + 0x10]
0061 or ax, word ptr [bp + 0xe]
0064 je 0x57a2
0066 xor al, al
0068 mov byte ptr [bp - 0x200], al
006c mov byte ptr [bp - 0x100], al
0070 leave 
0071 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern int near editHeight;` — src/recovered/BalloonIsVisible.c
- `extern int near editWidth;` — src/recovered/BalloonIsVisible.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_AddMsgBalloon', 'offset': 19352, 'source': None, 'size': 276}
- {'symbol': '_DrawCurBalloons', 'offset': 19628, 'source': None, 'size': 2693}
- {'symbol': '_PreDrawBalloons', 'offset': 22436, 'source': 'src/recovered/PreDrawBalloons.c', 'size': 6}
- {'symbol': '_DrawBalloons', 'offset': 22442, 'source': None, 'size': 897}
