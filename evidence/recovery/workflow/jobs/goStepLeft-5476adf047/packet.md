# Recovery task _goStepLeft

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 163 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0007 mov es, ax
0009 mov bx, word ptr [bp + 6]
000c xor si, si
000e sub word ptr es:[0x7d2e], bx
0013 jns 0x6fd0
0015 mov word ptr es:[0x7d2e], si
001a jmp 0x6fdb
001c dec bx
001d jne 0x6fd8
001f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 34, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollLeft
0024 mov si, 1
0027 mov ax, word ptr [0xcc76] ; _MapPlane
002a dec ax
002b je 0x6fea
002d dec ax
002e je 0x700a
0030 dec ax
0031 je 0x702a
0033 jmp 0x7048
0035 nop 
0036 mov es, word ptr [0xc64c]
003a mov ax, word ptr es:[0x7292]
003e cdq 
003f sub ax, dx
0041 sar ax, 1
0043 mov es, word ptr [0xc64e]
0047 add ax, word ptr es:[0x7d2e]
004c mov es, word ptr [0xc650]
0050 mov word ptr es:[0x9f2c], ax
0054 jmp 0x7048
0056 mov es, word ptr [0xc64c]
005a mov ax, word ptr es:[0x7292]
005e cdq 
005f sub ax, dx
0061 sar ax, 1
0063 mov es, word ptr [0xc64e]
0067 add ax, word ptr es:[0x7d2e]
006c mov es, word ptr [0xc652]
0070 mov word ptr es:[0x9fb2], ax
0074 jmp 0x7048
0076 mov es, word ptr [0xc64c]
007a mov ax, word ptr es:[0x7292]
007e cdq 
007f sub ax, dx
0081 sar ax, 1
0083 mov es, word ptr [0xc64e]
0087 add ax, word ptr es:[0x7d2e]
008c mov es, word ptr [0xc654]
0090 mov word ptr es:[0x72f6], ax
0094 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 151, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
0099 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 156, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
009e mov ax, si
00a0 pop si
00a1 leave 
00a2 retf 
```

## Known declaration examples

- `extern void far DrawEdit(void);` — src/recovered/wf_FinishHorzStep-6510fd44a5.c
- `extern void far DrawEdit(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
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

- {'symbol': '_ClrArrays', 'offset': 28140, 'source': None, 'size': 273}
- {'symbol': '_goStepRight', 'offset': 28414, 'source': None, 'size': 181}
- {'symbol': '_goStepDown', 'offset': 28760, 'source': None, 'size': 181}
- {'symbol': '_goStepUp', 'offset': 28942, 'source': None, 'size': 163}
