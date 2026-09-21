# Recovery task _DoTroph

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 93 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov es, word ptr [0xbf70]
0009 mov bx, word ptr [bp + 0xa]
000c mov al, byte ptr es:[bx]
0011 cwde 
0012 mov si, ax
0014 add si, word ptr [bp + 6]
0017 mov es, word ptr [0xbf72]
001b mov al, byte ptr es:[bx + 8]
0020 cwde 
0021 mov di, ax
0023 add di, word ptr [bp + 8]
0026 push word ptr [bp + 8]
0029 push word ptr [bp + 6]
002c push di
002d push si
002e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 49, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _GetDir
0033 add sp, 8
0036 dec ax
0037 push ax
0038 push word ptr [0xcc84] ; _MeType
003c push di
003d push si
003e push word ptr [0xce80] ; _MePlane
0042 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 69, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _MoveMyLife
0047 add sp, 0xa
004a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 77, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 3}}] ; _DoEditUpdateDraw
004f push 1
0051 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 84, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _EatMyFood
0056 add sp, 2
0059 pop si
005a pop di
005b leave 
005c retf 
```

## Known declaration examples

- `extern void far DoEditUpdateDraw(void);` — src/recovered/DoEditAndMapUpdateDraw.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_LionDialog', 'offset': 32928, 'source': None, 'size': 449}
- {'symbol': '_YellowDialog', 'offset': 33378, 'source': None, 'size': 523}
- {'symbol': '_SetAlarmDropState', 'offset': 33996, 'source': None, 'size': 149}
- {'symbol': '_YellowCommandKey', 'offset': 34146, 'source': None, 'size': None}
