# Recovery task _AlarmHere2

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 56 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 mov <resolved loader operand; see bindings> ; [{'operand_offset': 6, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0008 mov es, ax
000a mov di, word ptr [bp + 6]
000d mov si, word ptr [bp + 4]
0010 sar si, 1
0012 mov bx, si
0014 shl bx, 5
0017 sar di, 1
0019 add bx, di
001b mov al, byte ptr es:[bx + 0x52d2]
0020 sub ah, ah
0022 cmp ax, word ptr [bp + 8]
0025 jg 0x94b2
0027 mov al, byte ptr [bp + 8]
002a shl si, 5
002d add si, di
002f mov byte ptr es:[si + 0x52d2], al
0034 pop si
0035 pop di
0036 leave 
0037 ret 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SmoothAlarm', 'offset': 37760, 'source': None, 'size': 187}
- {'symbol': '_AlarmHere', 'offset': 37948, 'source': None, 'size': 65}
- {'symbol': '_JamScentBN', 'offset': 38070, 'source': None, 'size': 63}
- {'symbol': '_JamScentRN', 'offset': 38134, 'source': None, 'size': 63}
