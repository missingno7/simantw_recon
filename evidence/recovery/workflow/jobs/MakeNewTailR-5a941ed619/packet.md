# Recovery task _MakeNewTailR

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT1_MODULE`. Closed extent: 101 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov si, word ptr [bp + 6]
0007 push 0
0009 push 9
000b mov es, word ptr [0xc386]
000f mov al, byte ptr es:[si + 0x46e6]
0014 mov cx, ax
0016 sub ah, ah
0018 add ax, 8
001b push ax
001c mov es, word ptr [0xc396]
0020 mov bl, cl
0022 and bl, 7
0025 xor bl, 4
0028 sub bh, bh
002a mov al, byte ptr es:[bx + 8]
002f cwde 
0030 mov es, word ptr [0xc386]
0034 mov cl, byte ptr es:[si + 0x42fa]
0039 sub ch, ch
003b add ax, cx
003d push ax
003e mov ax, es
0040 mov es, word ptr [0xc398]
0044 mov cx, es
0046 mov es, ax
0048 mov dl, byte ptr es:[si + 0x4104]
004d sub dh, dh
004f mov es, cx
0051 mov al, byte ptr es:[bx]
0056 cwde 
0057 add ax, dx
0059 push ax
005a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 93, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _AddAntToRList
005f add sp, 0xa
0062 pop si
0063 leave 
0064 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SimQueenR', 'offset': 25478, 'source': None, 'size': 639}
- {'symbol': '_QueenMoveR', 'offset': 26118, 'source': None, 'size': 246}
- {'symbol': '_KillTailR', 'offset': 26466, 'source': None, 'size': 45}
- {'symbol': '_LostHeadR', 'offset': 26512, 'source': None, 'size': 94}
