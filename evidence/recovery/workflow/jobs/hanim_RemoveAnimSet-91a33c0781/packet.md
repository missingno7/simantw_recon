# Recovery task _hanim_RemoveAnimSet

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 146 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0x558e ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov si, ax
0017 mov word ptr [bp - 8], es
001a push word ptr es:[bx + 2]
001e nop 
001f push cs
0020 call 0x558e ; _mem_Lock
0023 add sp, 2
0026 mov word ptr [bp - 2], dx
0029 mov word ptr [bp - 6], 0
002e mov es, word ptr [bp - 8]
0031 cmp word ptr es:[si], 0
0035 jle 0x6f06
0037 mov word ptr [bp - 0xa], si
003a mov si, ax
003c mov di, word ptr [bp - 6]
003f mov es, word ptr [bp - 2]
0042 push word ptr es:[si + 0x22]
0046 nop 
0047 push cs
0048 call 0x5580 ; _mem_Free
004b add sp, 2
004e add si, 0x2c
0051 inc di
0052 les bx, ptr [bp - 0xa]
0055 cmp word ptr es:[bx], di
0058 jg 0x6ee9
005a mov si, bx
005c push word ptr es:[si + 2]
0060 mov di, es
0062 nop 
0063 push cs
0064 call 0x559c ; _mem_Unlock
0067 add sp, 2
006a mov es, di
006c push word ptr es:[si + 2]
0070 nop 
0071 push cs
0072 call 0x5580 ; _mem_Free
0075 add sp, 2
0078 push word ptr [bp + 6]
007b nop 
007c push cs
007d call 0x559c ; _mem_Unlock
0080 add sp, 2
0083 push word ptr [bp + 6]
0086 nop 
0087 push cs
0088 call 0x5580 ; _mem_Free
008b add sp, 2
008e pop si
008f pop di
0090 leave 
0091 retf 
```

## Known declaration examples

- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_hanim_SetObjectPos', 'offset': 27244, 'source': None, 'size': 974}
- {'symbol': '_hanim_MakeAnimSet', 'offset': 28218, 'source': 'src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c', 'size': 111}
- {'symbol': '_hanim_RenderAnimSet', 'offset': 28476, 'source': None, 'size': 1187}
- {'symbol': '_gr_GetFromBuf', 'offset': 29664, 'source': None, 'size': 342}
