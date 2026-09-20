# Recovery task _AlarmHere

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 65 bytes.

```asm
0000 enter 2, 0
0004 push di
0005 push si
0006 mov <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0009 mov es, ax
000b mov di, word ptr [bp + 6]
000e mov si, word ptr [bp + 4]
0011 sar si, 1
0013 mov bx, si
0015 shl bx, 5
0018 sar di, 1
001a add bx, di
001c mov al, byte ptr es:[bx + 0x52d2]
0021 sub ah, ah
0023 add ax, word ptr [bp + 8]
0026 cmp ax, 0xc8
0029 jg 0x946c
002b mov cx, ax
002d jmp 0x946f
002f nop 
0030 mov cx, 0xc8
0033 shl si, 5
0036 add si, di
0038 mov byte ptr es:[si + 0x52d2], cl
003d pop si
003e pop di
003f leave 
0040 ret 
```

## Known declaration examples

- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentBN-cd34069882.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentBT-86d27c2a8a.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_JamScentRN-18f9c8a2bb.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ColonySmellRT', 'offset': 37700, 'source': None, 'size': 60}
- {'symbol': '_SmoothAlarm', 'offset': 37760, 'source': None, 'size': 187}
- {'symbol': '_AlarmHere2', 'offset': 38014, 'source': None, 'size': 56}
- {'symbol': '_JamScentBN', 'offset': 38070, 'source': 'src/recovered/wf_JamScentBN-cd34069882.c', 'size': 63}
