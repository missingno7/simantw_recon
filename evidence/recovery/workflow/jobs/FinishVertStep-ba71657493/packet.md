# Recovery task _FinishVertStep

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 119 bytes.

```asm
0000 mov ax, word ptr [0xcc76] ; _MapPlane
0003 dec ax
0004 je 0x77d4
0006 dec ax
0007 je 0x77f4
0009 dec ax
000a je 0x7814
000c jmp 0x7832
000e mov es, word ptr [0xc656]
0012 mov ax, word ptr es:[0x9b6c]
0016 cdq 
0017 sub ax, dx
0019 sar ax, 1
001b mov es, word ptr [0xc64e]
001f add ax, word ptr es:[0x7d30]
0024 mov es, word ptr [0xc650]
0028 mov word ptr es:[0x9f2e], ax
002c jmp 0x7832
002e mov es, word ptr [0xc656]
0032 mov ax, word ptr es:[0x9b6c]
0036 cdq 
0037 sub ax, dx
0039 sar ax, 1
003b mov es, word ptr [0xc64e]
003f add ax, word ptr es:[0x7d30]
0044 mov es, word ptr [0xc652]
0048 mov word ptr es:[0x9fb4], ax
004c jmp 0x7832
004e mov es, word ptr [0xc656]
0052 mov ax, word ptr es:[0x9b6c]
0056 cdq 
0057 sub ax, dx
0059 sar ax, 1
005b mov es, word ptr [0xc64e]
005f add ax, word ptr es:[0x7d30]
0064 mov es, word ptr [0xc654]
0068 mov word ptr es:[0x72f8], ax
006c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 111, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0071 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 116, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
0076 retf 
```

## Known declaration examples

- `extern void far DrawEdit(void);` — src/recovered/wf_FinishHorzStep-6510fd44a5.c
- `extern void far DrawEdit(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near MapPlane;` — src/recovered/wf_FinishHorzStep-6510fd44a5.c
- `extern void far UpdateEdit(void);` — src/recovered/DoEditUpdateDraw.c
- `extern void far UpdateEdit(void);` — src/recovered/ForceUpdateEdit.c
- `extern void far UpdateEdit(void);` — src/recovered/UpdateEditWindow.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_FinishDiagStep', 'offset': 30326, 'source': None, 'size': 215}
- {'symbol': '_FinishHorzStep', 'offset': 30542, 'source': 'src/recovered/wf_FinishHorzStep-6510fd44a5.c', 'size': 119}
- {'symbol': '_BlockMove', 'offset': 30782, 'source': None, 'size': 33}
- {'symbol': '_FlipHandleWords', 'offset': 30816, 'source': None, 'size': 82}
