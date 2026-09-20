# Recovery task _DialogAbortAll

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 30 bytes.

```asm
0000 push di
0001 mov bx, word ptr [0x150a]
0005 or bx, bx
0007 jl 0x9cfc
0009 mov ax, 0xffff
000c lea cx, [bx + 1]
000f mov di, 0xcaf4
0012 push ds
0013 pop es
0014 rep stosw word ptr es:[di], ax
0016 mov word ptr [0x150a], 0xffff
001c pop di
001d retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DialogAbortOrCont', 'offset': 40088, 'source': None, 'size': 59}
- {'symbol': '_DialogDone', 'offset': 40148, 'source': 'src/recovered/DialogDone.c', 'size': 18}
- {'symbol': '_AddSomeAnts', 'offset': 40196, 'source': None, 'size': 90}
- {'symbol': '_KillSomeAnts', 'offset': 40286, 'source': None, 'size': 198}
