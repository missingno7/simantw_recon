# Recovery task _FinishDiagStep

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 215 bytes.

```asm
0000 mov ax, word ptr [0xcc76] ; _MapPlane
0003 dec ax
0004 je 0x768a
0006 dec ax
0007 je 0x76c8
0009 dec ax
000a jne 0x7685
000c jmp 0x7706
000f jmp 0x7742
0012 nop 
0013 nop 
0014 mov es, word ptr [0xc64c]
0018 mov ax, word ptr es:[0x7292]
001c cdq 
001d sub ax, dx
001f sar ax, 1
0021 mov es, word ptr [0xc64e]
0025 add ax, word ptr es:[0x7d2e]
002a mov es, word ptr [0xc650]
002e mov word ptr es:[0x9f2c], ax
0032 mov es, word ptr [0xc656]
0036 mov ax, word ptr es:[0x9b6c]
003a cdq 
003b sub ax, dx
003d sar ax, 1
003f mov es, word ptr [0xc64e]
0043 add ax, word ptr es:[0x7d30]
0048 mov es, word ptr [0xc650]
004c mov word ptr es:[0x9f2e], ax
0050 jmp 0x7742
0052 mov es, word ptr [0xc64c]
0056 mov ax, word ptr es:[0x7292]
005a cdq 
005b sub ax, dx
005d sar ax, 1
005f mov es, word ptr [0xc64e]
0063 add ax, word ptr es:[0x7d2e]
0068 mov es, word ptr [0xc652]
006c mov word ptr es:[0x9fb2], ax
0070 mov es, word ptr [0xc656]
0074 mov ax, word ptr es:[0x9b6c]
0078 cdq 
0079 sub ax, dx
007b sar ax, 1
007d mov es, word ptr [0xc64e]
0081 add ax, word ptr es:[0x7d30]
0086 mov es, word ptr [0xc652]
008a mov word ptr es:[0x9fb4], ax
008e jmp 0x7742
0090 mov es, word ptr [0xc64c]
0094 mov ax, word ptr es:[0x7292]
0098 cdq 
0099 sub ax, dx
009b sar ax, 1
009d mov es, word ptr [0xc64e]
00a1 add ax, word ptr es:[0x7d2e]
00a6 mov es, word ptr [0xc654]
00aa mov word ptr es:[0x72f6], ax
00ae mov es, word ptr [0xc656]
00b2 mov ax, word ptr es:[0x9b6c]
00b6 cdq 
00b7 sub ax, dx
00b9 sar ax, 1
00bb mov es, word ptr [0xc64e]
00bf add ax, word ptr es:[0x7d30]
00c4 mov es, word ptr [0xc654]
00c8 mov word ptr es:[0x72f8], ax
00cc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
00d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 212, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
00d6 retf 
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

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_goStepSW', 'offset': 29724, 'source': None, 'size': 306}
- {'symbol': '_goStepNW', 'offset': 30030, 'source': None, 'size': 295}
- {'symbol': '_FinishHorzStep', 'offset': 30542, 'source': 'src/recovered/wf_tu_simtwo_6EFE_prefix2-d0592154b0.c', 'size': 119}
- {'symbol': '_FinishVertStep', 'offset': 30662, 'source': 'src/recovered/wf_tu_simtwo_6EFE_prefix2-d0592154b0.c', 'size': 119}
