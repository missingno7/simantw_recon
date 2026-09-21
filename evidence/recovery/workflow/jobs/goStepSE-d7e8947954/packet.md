# Recovery task _goStepSE

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 318 bytes.

```asm
0000 enter 6, 0
0004 push si
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0008 mov ds, ax
000a mov <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000d mov es, ax
000f xor si, si
0011 mov ax, word ptr es:[0x7d26]
0015 inc word ptr [0x7d30]
0019 cmp word ptr [0x7d30], ax
001d jle 0x7304
001f mov word ptr [0x7d30], ax
0022 push ss
0023 pop ds
0024 jmp 0x7314
0026 cmp word ptr [bp + 6], 1
002a jne 0x733a
002c push ss
002d pop ds
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollDownS
0033 mov si, 1
0036 mov es, word ptr [0xc658]
003a mov ax, word ptr es:[0x769a]
003e mov word ptr [bp - 6], ax
0041 mov bx, 0x7d2e
0044 mov es, word ptr [0xc64e]
0048 mov word ptr [bp - 4], bx
004b mov word ptr [bp - 2], es
004e inc word ptr es:[bx]
0051 cmp word ptr es:[bx], ax
0054 jle 0x733e
0056 mov word ptr es:[bx], ax
0059 jmp 0x734c
005b nop 
005c push ss
005d pop ds
005e jmp 0x7311
0060 cmp word ptr [bp + 6], 1
0064 jne 0x7349
0066 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 105, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollRightS
006b mov si, 1
006e mov ax, word ptr [0xcc76] ; _MapPlane
0071 dec ax
0072 je 0x735c
0074 dec ax
0075 je 0x7398
0077 dec ax
0078 je 0x73d4
007a jmp 0x740d
007d nop 
007e mov es, word ptr [0xc64c]
0082 mov ax, word ptr es:[0x7292]
0086 cdq 
0087 sub ax, dx
0089 sar ax, 1
008b les bx, ptr [bp - 4]
008e add ax, word ptr es:[bx]
0091 mov es, word ptr [0xc650]
0095 mov word ptr es:[0x9f2c], ax
0099 mov es, word ptr [0xc656]
009d mov ax, word ptr es:[0x9b6c]
00a1 cdq 
00a2 sub ax, dx
00a4 sar ax, 1
00a6 mov es, word ptr [0xc64e]
00aa add ax, word ptr es:[0x7d30]
00af mov es, word ptr [0xc650]
00b3 mov word ptr es:[0x9f2e], ax
00b7 jmp 0x740d
00b9 nop 
00ba mov es, word ptr [0xc64c]
00be mov ax, word ptr es:[0x7292]
00c2 cdq 
00c3 sub ax, dx
00c5 sar ax, 1
00c7 les bx, ptr [bp - 4]
00ca add ax, word ptr es:[bx]
00cd mov es, word ptr [0xc652]
00d1 mov word ptr es:[0x9fb2], ax
00d5 mov es, word ptr [0xc656]
00d9 mov ax, word ptr es:[0x9b6c]
00dd cdq 
00de sub ax, dx
00e0 sar ax, 1
00e2 mov es, word ptr [0xc64e]
00e6 add ax, word ptr es:[0x7d30]
00eb mov es, word ptr [0xc652]
00ef mov word ptr es:[0x9fb4], ax
00f3 jmp 0x740d
00f5 nop 
00f6 mov es, word ptr [0xc64c]
00fa mov ax, word ptr es:[0x7292]
00fe cdq 
00ff sub ax, dx
0101 sar ax, 1
0103 les bx, ptr [bp - 4]
0106 add ax, word ptr es:[bx]
0109 mov es, word ptr [0xc654]
010d mov word ptr es:[0x72f6], ax
0111 mov es, word ptr [0xc656]
0115 mov ax, word ptr es:[0x9b6c]
0119 cdq 
011a sub ax, dx
011c sar ax, 1
011e mov es, word ptr [0xc64e]
0122 add ax, word ptr es:[0x7d30]
0127 mov es, word ptr [0xc654]
012b mov word ptr es:[0x72f8], ax
012f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 306, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0134 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 311, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
0139 mov ax, si
013b pop si
013c leave 
013d retf 
```

## Known declaration examples

- `extern void far DrawEdit(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern void far DrawEdit(void);` — src/recovered/wf_tu_simtwo_6EFE_prefix2-d0592154b0.c
- `extern void far DrawEdit(void);` — src/recovered/wf_tu_simtwo_6EFE_prefix4-43544063f0.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToBList-e7a166edf6.c
- `extern int far match_position[];` — src/recovered/wf_AddAntToRList-63e08ccbad.c
- `extern int far match_position[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_goStepUp', 'offset': 28942, 'source': 'src/recovered/wf_tu_simtwo_6EFE_prefix4-43544063f0.c', 'size': 163}
- {'symbol': '_goStepNE', 'offset': 29106, 'source': None, 'size': 300}
- {'symbol': '_goStepSW', 'offset': 29724, 'source': None, 'size': 306}
- {'symbol': '_goStepNW', 'offset': 30030, 'source': None, 'size': 295}
