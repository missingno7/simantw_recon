# Recovery task _snd_IsSongDone

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 44 bytes.

```asm
0000 mov es, word ptr [0xbf78]
0004 cmp word ptr es:[0x8d08], 0
000a je 0x7ee6
000c cmp word ptr es:[0x8d0c], 0
0012 jne 0x7ee6
0014 cmp word ptr es:[0x8d0a], 0
001a jne 0x7ee6
001c cmp word ptr es:[0x8d1c], 1
0022 sbb ax, ax
0024 neg ax
0026 retf 
0027 nop 
0028 mov ax, 1
002b retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_snd_Install', 'offset': 31034, 'source': None, 'size': 804}
- {'symbol': '_snd_Deinstall', 'offset': 31838, 'source': None, 'size': 608}
- {'symbol': '_musSoundBlasterClose', 'offset': 32490, 'source': None, 'size': 100}
- {'symbol': '_vocSoundBlasterClose', 'offset': 32590, 'source': None, 'size': 100}
