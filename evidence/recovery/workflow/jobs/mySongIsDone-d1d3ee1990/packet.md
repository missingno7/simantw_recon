# Recovery task _mySongIsDone

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 66 bytes.

```asm
0000 mov es, word ptr [0xbf78]
0004 cmp word ptr es:[0x8d06], 0
000a je 0xa1de
000c cmp word ptr [0xaf6], 0 ; _songsOnFlag
0011 je 0xa1de
0013 cmp word ptr es:[0x8d08], 0
0019 je 0xa1cb
001b cmp word ptr es:[0x8d0c], 0
0021 jne 0xa1cb
0023 cmp word ptr es:[0x8d0a], 0
0029 je 0xa1d2
002b mov bx, 1
002e mov ax, bx
0030 retf 
0031 nop 
0032 cmp word ptr es:[0x8d1c], 1
0038 sbb bx, bx
003a neg bx
003c jmp 0xa1ce
003e mov ax, 1
0041 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_mySoundIsDone', 'offset': 41352, 'source': 'src/recovered/mySoundIsDone.c', 'size': 4}
- {'symbol': '_myBeginSoundReverse', 'offset': 41356, 'source': 'src/recovered/myBeginSoundReverse.c', 'size': 19}
- {'symbol': '_MultiMediaSong', 'offset': 41442, 'source': None, 'size': 51}
- {'symbol': '_myServiceSong', 'offset': 41494, 'source': None, 'size': 78}
