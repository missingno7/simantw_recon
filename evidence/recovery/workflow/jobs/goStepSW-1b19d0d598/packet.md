# Recovery task _goStepSW

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 306 bytes.

```asm
0000 enter 4, 0
0004 push si
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0008 mov ds, ax
000a mov <resolved loader operand; see bindings> ; [{'operand_offset': 11, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000d mov es, ax
000f xor si, si
0011 mov ax, word ptr es:[0x7d26]
0015 inc word ptr [0x7d30]
0019 cmp word ptr [0x7d30], ax
001d jle 0x7442
001f mov word ptr [0x7d30], ax
0022 push ss
0023 pop ds
0024 jmp 0x7452
0026 cmp word ptr [bp + 6], 1
002a jne 0x746c
002c push ss
002d pop ds
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollDownS
0033 mov si, 1
0036 mov bx, 0x7d2e
0039 mov es, word ptr [0xc64e]
003d mov word ptr [bp - 4], bx
0040 mov word ptr [bp - 2], es
0043 dec word ptr es:[bx]
0046 jns 0x7470
0048 mov word ptr es:[bx], 0
004d jmp 0x747e
004f nop 
0050 push ss
0051 pop ds
0052 jmp 0x744f
0054 cmp word ptr [bp + 6], 1
0058 jne 0x747b
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollRightS
005f mov si, 1
0062 mov ax, word ptr [0xcc76] ; _MapPlane
0065 dec ax
0066 je 0x748e
0068 dec ax
0069 je 0x74ca
006b dec ax
006c je 0x7506
006e jmp 0x753f
0071 nop 
0072 mov es, word ptr [0xc64c]
0076 mov ax, word ptr es:[0x7292]
007a cdq 
007b sub ax, dx
007d sar ax, 1
007f les bx, ptr [bp - 4]
0082 add ax, word ptr es:[bx]
0085 mov es, word ptr [0xc650]
0089 mov word ptr es:[0x9f2c], ax
008d mov es, word ptr [0xc656]
0091 mov ax, word ptr es:[0x9b6c]
0095 cdq 
0096 sub ax, dx
0098 sar ax, 1
009a mov es, word ptr [0xc64e]
009e add ax, word ptr es:[0x7d30]
00a3 mov es, word ptr [0xc650]
00a7 mov word ptr es:[0x9f2e], ax
00ab jmp 0x753f
00ad nop 
00ae mov es, word ptr [0xc64c]
00b2 mov ax, word ptr es:[0x7292]
00b6 cdq 
00b7 sub ax, dx
00b9 sar ax, 1
00bb les bx, ptr [bp - 4]
00be add ax, word ptr es:[bx]
00c1 mov es, word ptr [0xc652]
00c5 mov word ptr es:[0x9fb2], ax
00c9 mov es, word ptr [0xc656]
00cd mov ax, word ptr es:[0x9b6c]
00d1 cdq 
00d2 sub ax, dx
00d4 sar ax, 1
00d6 mov es, word ptr [0xc64e]
00da add ax, word ptr es:[0x7d30]
00df mov es, word ptr [0xc652]
00e3 mov word ptr es:[0x9fb4], ax
00e7 jmp 0x753f
00e9 nop 
00ea mov es, word ptr [0xc64c]
00ee mov ax, word ptr es:[0x7292]
00f2 cdq 
00f3 sub ax, dx
00f5 sar ax, 1
00f7 les bx, ptr [bp - 4]
00fa add ax, word ptr es:[bx]
00fd mov es, word ptr [0xc654]
0101 mov word ptr es:[0x72f6], ax
0105 mov es, word ptr [0xc656]
0109 mov ax, word ptr es:[0x9b6c]
010d cdq 
010e sub ax, dx
0110 sar ax, 1
0112 mov es, word ptr [0xc64e]
0116 add ax, word ptr es:[0x7d30]
011b mov es, word ptr [0xc654]
011f mov word ptr es:[0x72f8], ax
0123 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 294, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0128 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 299, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
012d mov ax, si
012f pop si
0130 leave 
0131 retf 
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

- {'symbol': '_goStepNE', 'offset': 29106, 'source': None, 'size': 300}
- {'symbol': '_goStepSE', 'offset': 29406, 'source': None, 'size': 318}
- {'symbol': '_goStepNW', 'offset': 30030, 'source': None, 'size': 295}
- {'symbol': '_FinishDiagStep', 'offset': 30326, 'source': None, 'size': 215}
