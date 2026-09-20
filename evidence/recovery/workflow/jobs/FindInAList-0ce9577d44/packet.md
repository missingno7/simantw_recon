# Recovery task _FindInAList

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 68 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 mov es, word ptr [0xc426]
0008 mov bx, word ptr es:[0x80f0]
000d mov cx, word ptr [bp + 8]
0010 mov di, word ptr [bp + 6]
0013 mov <resolved loader operand; see bindings> ; [{'operand_offset': 20, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0016 mov ds, ax
0018 or bx, bx
001a jle 0x2c7e
001c dec bx
001d mov al, byte ptr [bx + 0x23a4]
0021 sub ah, ah
0023 cmp ax, di
0025 jne 0x2c5a
0027 mov al, byte ptr [bx + 0x278e]
002b cmp ax, cx
002d jne 0x2c5a
002f cmp byte ptr [bx + 0x2f62], ah
0033 je 0x2c5a
0035 push ss
0036 pop ds
0037 mov ax, bx
0039 pop di
003a leave 
003b retf 
003c push ss
003d pop ds
003e mov ax, 0xffff
0041 pop di
0042 leave 
0043 retf 
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

- {'symbol': '_CompactListR', 'offset': 10974, 'source': None, 'size': 99}
- {'symbol': '_RemoveFromAList', 'offset': 11074, 'source': None, 'size': 255}
- {'symbol': '_FindInBList', 'offset': 11398, 'source': None, 'size': 72}
- {'symbol': '_FindInRList', 'offset': 11470, 'source': None, 'size': 72}
