# Recovery task __hanim_FindObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 69 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push di
0004 push si
0005 lds di, ptr [bp + 0xa]
0008 xor cx, cx
000a cmp word ptr [di], cx
000c jg 0x63dc
000e push ss
000f pop ds
0010 jmp 0x6408
0012 mov bx, word ptr [bp + 6]
0015 mov es, word ptr [bp + 8]
0018 mov ax, word ptr [bp + 0xe]
001b cmp word ptr es:[bx + 0x20], ax
001f je 0x63f6
0021 add bx, 0x2c
0024 inc cx
0025 cmp word ptr [di], cx
0027 jg 0x63e2
0029 jmp 0x63d8
002b nop 
002c push ss
002d pop ds
002e les si, ptr [bp + 0x10]
0031 mov word ptr es:[si], cx
0034 mov ax, bx
0036 mov dx, word ptr [bp + 8]
0039 pop si
003a pop di
003b leave 
003c retf 
003d nop 
003e xor ax, ax
0040 cdq 
0041 pop si
0042 pop di
0043 leave 
0044 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SetDebugFlag', 'offset': 25524, 'source': 'src/recovered/SetDebugFlag.c', 'size': 7}
- {'symbol': '_hanim_PrintSet', 'offset': 25532, 'source': 'src/recovered/hanim_PrintSet.c', 'size': 13}
- {'symbol': '_hanim_AddAnimObject', 'offset': 25616, 'source': None, 'size': 650}
- {'symbol': '_hanim_RemoveAnimObject', 'offset': 26266, 'source': None, 'size': 260}
