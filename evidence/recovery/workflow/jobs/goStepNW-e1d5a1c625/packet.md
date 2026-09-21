# Recovery task _goStepNW

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 295 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0007 mov es, ax
0009 xor si, si
000b dec word ptr es:[0x7d30]
0010 jns 0x7568
0012 mov word ptr es:[0x7d30], si
0017 jmp 0x757b
0019 nop 
001a cmp word ptr [bp + 6], 1
001e jne 0x7578
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollDownS
0025 mov <resolved loader operand; see bindings> ; [{'operand_offset': 38, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0028 mov es, ax
002a mov si, 1
002d dec word ptr es:[0x7d2e]
0032 jns 0x758c
0034 mov word ptr es:[0x7d2e], 0
003b jmp 0x759a
003d nop 
003e cmp word ptr [bp + 6], 1
0042 jne 0x7597
0044 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 71, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollRightS
0049 mov si, 1
004c mov ax, word ptr [0xcc76] ; _MapPlane
004f dec ax
0050 je 0x75ae
0052 dec ax
0053 je 0x75ec
0055 dec ax
0056 jne 0x75a9
0058 jmp 0x762a
005b jmp 0x7666
005e nop 
005f nop 
0060 mov es, word ptr [0xc64c]
0064 mov ax, word ptr es:[0x7292]
0068 cdq 
0069 sub ax, dx
006b sar ax, 1
006d mov es, word ptr [0xc64e]
0071 add ax, word ptr es:[0x7d2e]
0076 mov es, word ptr [0xc650]
007a mov word ptr es:[0x9f2c], ax
007e mov es, word ptr [0xc656]
0082 mov ax, word ptr es:[0x9b6c]
0086 cdq 
0087 sub ax, dx
0089 sar ax, 1
008b mov es, word ptr [0xc64e]
008f add ax, word ptr es:[0x7d30]
0094 mov es, word ptr [0xc650]
0098 mov word ptr es:[0x9f2e], ax
009c jmp 0x7666
009e mov es, word ptr [0xc64c]
00a2 mov ax, word ptr es:[0x7292]
00a6 cdq 
00a7 sub ax, dx
00a9 sar ax, 1
00ab mov es, word ptr [0xc64e]
00af add ax, word ptr es:[0x7d2e]
00b4 mov es, word ptr [0xc652]
00b8 mov word ptr es:[0x9fb2], ax
00bc mov es, word ptr [0xc656]
00c0 mov ax, word ptr es:[0x9b6c]
00c4 cdq 
00c5 sub ax, dx
00c7 sar ax, 1
00c9 mov es, word ptr [0xc64e]
00cd add ax, word ptr es:[0x7d30]
00d2 mov es, word ptr [0xc652]
00d6 mov word ptr es:[0x9fb4], ax
00da jmp 0x7666
00dc mov es, word ptr [0xc64c]
00e0 mov ax, word ptr es:[0x7292]
00e4 cdq 
00e5 sub ax, dx
00e7 sar ax, 1
00e9 mov es, word ptr [0xc64e]
00ed add ax, word ptr es:[0x7d2e]
00f2 mov es, word ptr [0xc654]
00f6 mov word ptr es:[0x72f6], ax
00fa mov es, word ptr [0xc656]
00fe mov ax, word ptr es:[0x9b6c]
0102 cdq 
0103 sub ax, dx
0105 sar ax, 1
0107 mov es, word ptr [0xc64e]
010b add ax, word ptr es:[0x7d30]
0110 mov es, word ptr [0xc654]
0114 mov word ptr es:[0x72f8], ax
0118 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 283, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
011d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 288, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
0122 mov ax, si
0124 pop si
0125 leave 
0126 retf 
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

- {'symbol': '_goStepSE', 'offset': 29406, 'source': None, 'size': 318}
- {'symbol': '_goStepSW', 'offset': 29724, 'source': None, 'size': 306}
- {'symbol': '_FinishDiagStep', 'offset': 30326, 'source': None, 'size': 215}
- {'symbol': '_FinishHorzStep', 'offset': 30542, 'source': 'src/recovered/wf_tu_simtwo_6EFE_prefix2-d0592154b0.c', 'size': 119}
