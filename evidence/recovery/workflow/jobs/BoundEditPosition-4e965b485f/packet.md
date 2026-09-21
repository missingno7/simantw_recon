# Recovery task _BoundEditPosition

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 107 bytes.

```asm
0000 mov ax, word ptr [0xcc76] ; _MapPlane
0003 or ax, ax
0005 jl 0x15c0
0007 jo 0x15c0
0009 dec ax
000a jle 0x15c6
000c mov cx, 0x40
000f jmp 0x15c9
0011 nop 
0012 mov cx, 0x80
0015 mov <resolved loader operand; see bindings> ; [{'operand_offset': 22, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0018 mov es, ax
001a cmp word ptr es:[0x7d2e], 0
0020 jge 0x15e0
0022 mov word ptr es:[0x7d2e], 0
0029 jmp 0x15f5
002b nop 
002c mov bx, word ptr [0xcc80] ; _editWidth
0030 mov ax, word ptr es:[0x7d2e]
0034 add ax, bx
0036 cmp ax, cx
0038 jle 0x15f5
003a sub cx, bx
003c mov word ptr es:[0x7d2e], cx
0041 cmp word ptr es:[0x7d30], 0
0047 jge 0x1606
0049 mov word ptr es:[0x7d30], 0
0050 retf 
0051 nop 
0052 mov bx, word ptr [0xcd7a] ; _editHeight
0056 mov ax, word ptr es:[0x7d30]
005a add ax, bx
005c cmp ax, 0x40
005f jle 0x161e
0061 mov ax, 0x40
0064 sub ax, bx
0066 mov word ptr es:[0x7d30], ax
006a retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
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

- {'symbol': '_DrawEdit', 'offset': 5358, 'source': 'src/recovered/DrawEdit.c', 'size': 1}
- {'symbol': '_win_DrawEditWindow', 'offset': 5360, 'source': None, 'size': 195}
- {'symbol': '_CenterEdit', 'offset': 5664, 'source': None, 'size': 180}
- {'symbol': '_DrawEditGraphs', 'offset': 6538, 'source': None, 'size': 379}
