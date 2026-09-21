# Recovery task _goStepDown

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 181 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov <resolved loader operand; see bindings> ; [{'operand_offset': 5, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
0007 mov ds, ax
0009 mov <resolved loader operand; see bindings> ; [{'operand_offset': 10, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 9}}] ; _match_position
000c mov es, ax
000e mov bx, word ptr [bp + 6]
0011 xor si, si
0013 mov ax, word ptr es:[0x7d26]
0017 add word ptr [0x7d30], bx
001b cmp word ptr [0x7d30], ax
001f jle 0x7080
0021 mov word ptr [0x7d30], ax
0024 push ss
0025 pop ds
0026 jmp 0x708d
0028 dec bx
0029 jne 0x709c
002b push ss
002c pop ds
002d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 48, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _ScrollDown
0032 mov si, 1
0035 mov ax, word ptr [0xcc76] ; _MapPlane
0038 dec ax
0039 je 0x70a0
003b dec ax
003c je 0x70c0
003e dec ax
003f je 0x70e0
0041 jmp 0x70fe
0043 nop 
0044 push ss
0045 pop ds
0046 jmp 0x708a
0048 mov es, word ptr [0xc656]
004c mov ax, word ptr es:[0x9b6c]
0050 cdq 
0051 sub ax, dx
0053 sar ax, 1
0055 mov es, word ptr [0xc64e]
0059 add ax, word ptr es:[0x7d30]
005e mov es, word ptr [0xc650]
0062 mov word ptr es:[0x9f2e], ax
0066 jmp 0x70fe
0068 mov es, word ptr [0xc656]
006c mov ax, word ptr es:[0x9b6c]
0070 cdq 
0071 sub ax, dx
0073 sar ax, 1
0075 mov es, word ptr [0xc64e]
0079 add ax, word ptr es:[0x7d30]
007e mov es, word ptr [0xc652]
0082 mov word ptr es:[0x9fb4], ax
0086 jmp 0x70fe
0088 mov es, word ptr [0xc656]
008c mov ax, word ptr es:[0x9b6c]
0090 cdq 
0091 sub ax, dx
0093 sar ax, 1
0095 mov es, word ptr [0xc64e]
0099 add ax, word ptr es:[0x7d30]
009e mov es, word ptr [0xc654]
00a2 mov word ptr es:[0x72f8], ax
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _UpdateEdit
00ab lcall <resolved loader operand; see bindings> ; [{'operand_offset': 174, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DrawEdit
00b0 mov ax, si
00b2 pop si
00b3 leave 
00b4 retf 
```

## Known declaration examples

- `extern void far DrawEdit(void);` — src/recovered/wf_FinishHorzStep-6510fd44a5.c
- `extern void far DrawEdit(void);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c
- `extern void far DrawEdit(void);` — src/recovered/wf_goStepLeft-5476adf047.c
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

- {'symbol': '_goStepRight', 'offset': 28414, 'source': None, 'size': 181}
- {'symbol': '_goStepLeft', 'offset': 28596, 'source': 'src/recovered/wf_goStepLeft-5476adf047.c', 'size': 163}
- {'symbol': '_goStepUp', 'offset': 28942, 'source': None, 'size': 163}
- {'symbol': '_goStepNE', 'offset': 29106, 'source': None, 'size': 300}
