# Recovery task _ClearLifeR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 83 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xc27c]
0009 mov bx, word ptr es:[0x72cc]
000e or bx, bx
0010 je 0x79e9
0012 mov di, word ptr [bp + 8]
0015 mov cx, word ptr [bp + 6]
0018 mov <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
001b mov ds, ax
001d dec bx
001e cmp byte ptr [bx + 0x46e6], 0
0023 je 0x79e3
0025 mov al, byte ptr [bx + 0x4104]
0029 sub ah, ah
002b cmp ax, cx
002d jne 0x79e3
002f mov al, byte ptr [bx + 0x42fa]
0033 cmp ax, di
0035 jne 0x79e3
0037 mov byte ptr [bx + 0x46e6], ah
003b or bx, bx
003d jne 0x79c5
003f push ss
0040 pop ds
0041 mov si, word ptr [bp + 6]
0044 shl si, 6
0047 mov bx, word ptr [bp + 8]
004a mov byte ptr [bx + si - 0x6718], 0
004f pop si
0050 pop di
0051 leave 
0052 retf 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_ClearLifeB-f9a6e1c57a.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_FindInBList-d950932078.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_FindInRList-130e8e266c.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ExpDig', 'offset': 30062, 'source': None, 'size': 997}
- {'symbol': '_ClearLifeB', 'offset': 31060, 'source': 'src/recovered/wf_ClearLifeB-f9a6e1c57a.c', 'size': 83}
- {'symbol': '_ExpAddAnt', 'offset': 31228, 'source': None, 'size': 266}
- {'symbol': '_ExpAddFood', 'offset': 31494, 'source': None, 'size': 152}
