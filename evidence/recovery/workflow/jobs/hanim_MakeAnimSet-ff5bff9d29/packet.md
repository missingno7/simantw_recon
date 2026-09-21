# Recovery task _hanim_MakeAnimSet

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 111 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 cmp word ptr [0xad0], 0
000b jne 0x6e4d
000d mov word ptr [0xad0], 1
0013 push ds
0014 push 0xad2
0017 push 1
0019 push 0
001b push 8
001d nop 
001e push cs
001f call 0x54da ; _mem_Alloc
0022 add sp, 0xa
0025 push ax
0026 mov si, ax
0028 nop 
0029 push cs
002a call 0x558e ; _mem_Lock
002d add sp, 2
0030 mov es, dx
0032 mov bx, ax
0034 mov word ptr es:[bx + 4], 0
003a mov word ptr es:[bx], 0
003f push ds
0040 push 0xadd
0043 push 1
0045 push 0
0047 push 4
0049 mov di, ax
004b mov word ptr [bp - 4], di
004e mov word ptr [bp - 2], es
0051 nop 
0052 push cs
0053 call 0x54da ; _mem_Alloc
0056 add sp, 0xa
0059 les bx, ptr [bp - 4]
005c mov word ptr es:[bx + 2], ax
0060 push si
0061 nop 
0062 push cs
0063 call 0x559c ; _mem_Unlock
0066 add sp, 2
0069 mov ax, si
006b pop si
006c pop di
006d leave 
006e retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_hanim_ShowObject', 'offset': 27064, 'source': None, 'size': 179}
- {'symbol': '_hanim_SetObjectPos', 'offset': 27244, 'source': None, 'size': 974}
- {'symbol': '_hanim_RemoveAnimSet', 'offset': 28330, 'source': None, 'size': 146}
- {'symbol': '_hanim_RenderAnimSet', 'offset': 28476, 'source': None, 'size': 1187}
