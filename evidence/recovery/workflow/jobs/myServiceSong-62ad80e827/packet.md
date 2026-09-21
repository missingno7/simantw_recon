# Recovery task _myServiceSong

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 78 bytes.

```asm
0000 enter 0x12, 0
0004 cmp word ptr [0xaf6], 0 ; _songsOnFlag
0009 je 0xa24a
000b mov es, word ptr [0xbf78]
000f cmp word ptr es:[0x8d08], 0
0015 je 0xa24a
0017 cmp word ptr es:[0x8d0a], 0
001d je 0xa24a
001f cmp word ptr es:[0x8d0c], 0
0025 jne 0xa24a
0027 cmp word ptr es:[0x8d0e], 0
002d je 0xa24a
002f mov dx, 1
0032 jmp 0xa24c
0034 xor dx, dx
0036 or dx, dx
0038 je 0xa262
003a lea ax, [bp - 0x12]
003d push ss
003e push ax
003f push 0
0041 push 0
0043 push 0
0045 push 0
0047 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 72, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 109}}]
004c leave 
004d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_mySongIsDone', 'offset': 41376, 'source': None, 'size': 66}
- {'symbol': '_MultiMediaSong', 'offset': 41442, 'source': None, 'size': 51}
- {'symbol': '_myBeginSoundSection', 'offset': 41572, 'source': 'src/recovered/myBeginSoundSection.c', 'size': 1}
- {'symbol': '_Beep', 'offset': 41574, 'source': 'src/recovered/Beep.c', 'size': 8}
