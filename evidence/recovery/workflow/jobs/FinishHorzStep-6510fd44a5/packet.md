# Recovery task _FinishHorzStep

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 119 bytes.

```asm
0000 mov ax, word ptr [0xcc76] ; _MapPlane
0003 dec ax
0004 je 0x775c
0006 dec ax
0007 je 0x777c
0009 dec ax
000a je 0x779c
000c jmp 0x77ba
000e mov es, word ptr [0xc64c]
0012 mov ax, word ptr es:[0x7292]
0016 cdq 
0017 sub ax, dx
0019 sar ax, 1
001b mov es, word ptr [0xc64e]
001f add ax, word ptr es:[0x7d2e]
0024 mov es, word ptr [0xc650]
0028 mov word ptr es:[0x9f2c], ax
002c jmp 0x77ba
002e mov es, word ptr [0xc64c]
0032 mov ax, word ptr es:[0x7292]
0036 cdq 
0037 sub ax, dx
0039 sar ax, 1
003b mov es, word ptr [0xc64e]
003f add ax, word ptr es:[0x7d2e]
0044 mov es, word ptr [0xc652]
0048 mov word ptr es:[0x9fb2], ax
004c jmp 0x77ba
004e mov es, word ptr [0xc64c]
0052 mov ax, word ptr es:[0x7292]
0056 cdq 
0057 sub ax, dx
0059 sar ax, 1
005b mov es, word ptr [0xc64e]
005f add ax, word ptr es:[0x7d2e]
0064 mov es, word ptr [0xc654]
0068 mov word ptr es:[0x72f6], ax
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
0076 retf 
```

## Known declaration examples

- `extern void far DrawEdit(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near MapPlane;` — src/recovered/wf_SetDefaultWindows-770f6186c6.c
- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_goStepNW', 'offset': 30030, 'source': None, 'size': 295}
- {'symbol': '_FinishDiagStep', 'offset': 30326, 'source': None, 'size': 215}
- {'symbol': '_FinishVertStep', 'offset': 30662, 'source': None, 'size': 119}
- {'symbol': '_BlockMove', 'offset': 30782, 'source': None, 'size': 33}
