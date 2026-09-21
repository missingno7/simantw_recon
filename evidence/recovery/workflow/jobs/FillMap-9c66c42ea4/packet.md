# Recovery task _FillMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMONE_MODULE`. Closed extent: 85 bytes.

```asm
0000 enter 8, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 8]
0009 mov cx, word ptr [bp + 6]
000c cmp cx, di
000e jg 0x3fa5
0010 mov bx, cx
0012 shl bx, 6
0015 mov dx, word ptr [bp + 0xa]
0018 mov word ptr [bp - 2], dx
001b mov ax, word ptr [bp + 0xc]
001e sub ax, dx
0020 inc ax
0021 mov word ptr [bp - 8], ax
0024 mov ax, di
0026 sub ax, cx
0028 inc ax
0029 mov word ptr [bp - 4], ax
002c mov ax, word ptr [bp + 0xa]
002f cmp word ptr [bp + 0xc], ax
0032 jl 0x3f9d
0034 mov al, byte ptr [bp + 0xe]
0037 sub ah, ah
0039 mov si, word ptr [bp - 2]
003c add si, bx
003e mov cx, word ptr [bp - 8]
0041 lea di, [si + 0x28e8]
0045 push ds
0046 pop es
0047 rep stosb byte ptr es:[di], al
0049 add bx, 0x40
004c dec word ptr [bp - 4]
004f jne 0x3f80
0051 pop si
0052 pop di
0053 leave 
0054 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_MakePenny', 'offset': 16074, 'source': 'src/recovered/wf_MakePenny-64a43149dd.c', 'size': 66}
- {'symbol': '_MakeClip', 'offset': 16140, 'source': 'src/recovered/wf_MakeClip-d8e5dff058.c', 'size': 71}
- {'symbol': '_FillMapLegs', 'offset': 16298, 'source': None, 'size': 503}
- {'symbol': '_MakeYardPatch', 'offset': 16802, 'source': None, 'size': 401}
