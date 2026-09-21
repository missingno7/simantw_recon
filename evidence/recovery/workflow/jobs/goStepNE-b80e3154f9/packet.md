# Recovery task _goStepNE

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 300 bytes.

```asm
0000 enter 6, 0
0004 push si
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0008 mov es, ax
000a xor si, si
000c dec word ptr es:[0x7d30]
0011 jns 0x71cc
0013 mov word ptr es:[0x7d30], si
0018 jmp 0x71da
001a cmp word ptr [bp + 6], 1
001e jne 0x71d7
0020 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 35, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollUpS
0025 mov si, 1
0028 mov es, word ptr [0xc658]
002c mov ax, word ptr es:[0x769a]
0030 mov word ptr [bp - 6], ax
0033 mov bx, 0x7d2e
0036 mov es, word ptr [0xc64e]
003a mov word ptr [bp - 4], bx
003d mov word ptr [bp - 2], es
0040 inc word ptr es:[bx]
0043 cmp word ptr es:[bx], ax
0046 jle 0x7200
0048 mov word ptr es:[bx], ax
004b jmp 0x720e
004d nop 
004e cmp word ptr [bp + 6], 1
0052 jne 0x720b
0054 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 87, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollRightS
0059 mov si, 1
005c mov ax, word ptr [0xcc76] ; _MapPlane
005f dec ax
0060 je 0x721e
0062 dec ax
0063 je 0x725a
0065 dec ax
0066 je 0x7296
0068 jmp 0x72cf
006b nop 
006c mov es, word ptr [0xc64c]
0070 mov ax, word ptr es:[0x7292]
0074 cdq 
0075 sub ax, dx
0077 sar ax, 1
0079 les bx, ptr [bp - 4]
007c add ax, word ptr es:[bx]
007f mov es, word ptr [0xc650]
0083 mov word ptr es:[0x9f2c], ax
0087 mov es, word ptr [0xc656]
008b mov ax, word ptr es:[0x9b6c]
008f cdq 
0090 sub ax, dx
0092 sar ax, 1
0094 mov es, word ptr [0xc64e]
0098 add ax, word ptr es:[0x7d30]
009d mov es, word ptr [0xc650]
00a1 mov word ptr es:[0x9f2e], ax
00a5 jmp 0x72cf
00a7 nop 
00a8 mov es, word ptr [0xc64c]
00ac mov ax, word ptr es:[0x7292]
00b0 cdq 
00b1 sub ax, dx
00b3 sar ax, 1
00b5 les bx, ptr [bp - 4]
00b8 add ax, word ptr es:[bx]
00bb mov es, word ptr [0xc652]
00bf mov word ptr es:[0x9fb2], ax
00c3 mov es, word ptr [0xc656]
00c7 mov ax, word ptr es:[0x9b6c]
00cb cdq 
00cc sub ax, dx
00ce sar ax, 1
00d0 mov es, word ptr [0xc64e]
00d4 add ax, word ptr es:[0x7d30]
00d9 mov es, word ptr [0xc652]
00dd mov word ptr es:[0x9fb4], ax
00e1 jmp 0x72cf
00e3 nop 
00e4 mov es, word ptr [0xc64c]
00e8 mov ax, word ptr es:[0x7292]
00ec cdq 
00ed sub ax, dx
00ef sar ax, 1
00f1 les bx, ptr [bp - 4]
00f4 add ax, word ptr es:[bx]
00f7 mov es, word ptr [0xc654]
00fb mov word ptr es:[0x72f6], ax
00ff mov es, word ptr [0xc656]
0103 mov ax, word ptr es:[0x9b6c]
0107 cdq 
0108 sub ax, dx
010a sar ax, 1
010c mov es, word ptr [0xc64e]
0110 add ax, word ptr es:[0x7d30]
0115 mov es, word ptr [0xc654]
0119 mov word ptr es:[0x72f8], ax
011d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 288, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0122 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 293, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
0127 mov ax, si
0129 pop si
012a leave 
012b retf 
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

- {'symbol': '_goStepDown', 'offset': 28760, 'source': 'src/recovered/wf_tu_simtwo_6EFE_prefix4-43544063f0.c', 'size': 181}
- {'symbol': '_goStepUp', 'offset': 28942, 'source': 'src/recovered/wf_tu_simtwo_6EFE_prefix4-43544063f0.c', 'size': 163}
- {'symbol': '_goStepSE', 'offset': 29406, 'source': None, 'size': 318}
- {'symbol': '_goStepSW', 'offset': 29724, 'source': None, 'size': 306}
