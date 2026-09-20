# Recovery task _MultiMediaSong

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 51 bytes.

```asm
0000 cmp word ptr [0xaf6], 0 ; _songsOnFlag
0005 je 0xa212
0007 mov es, word ptr [0xbf78]
000b cmp word ptr es:[0x8d08], 0
0011 je 0xa212
0013 cmp word ptr es:[0x8d0a], 0
0019 je 0xa212
001b cmp word ptr es:[0x8d0c], 0
0021 jne 0xa212
0023 cmp word ptr es:[0x8d0e], 0
0029 je 0xa212
002b mov ax, 1
002e retf 
002f nop 
0030 xor ax, ax
0032 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_myBeginSoundReverse', 'offset': 41356, 'source': 'src/recovered/myBeginSoundReverse.c', 'size': 19}
- {'symbol': '_mySongIsDone', 'offset': 41376, 'source': None, 'size': 66}
- {'symbol': '_myServiceSong', 'offset': 41494, 'source': None, 'size': 78}
- {'symbol': '_myBeginSoundSection', 'offset': 41572, 'source': 'src/recovered/myBeginSoundSection.c', 'size': 1}
