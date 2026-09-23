# Recovery task _DoFastMonoBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 337 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 push ds
0007 push 0xbabb
000a push 0
000c push 0
000e push 0x30
0010 nop 
0011 push cs
0012 call 0x54da ; _mem_Alloc
0015 add sp, 0xa
0018 mov word ptr [bp - 6], ax
001b mov ax, word ptr [bp + 0x10]
001e or ax, word ptr [bp + 0xe]
0021 jne 0x3b6e
0023 jmp 0x3c84
0026 cmp word ptr [bp - 6], 0
002a jne 0x3b77
002c jmp 0x3c84
002f mov di, word ptr [bp + 0xc]
0032 push word ptr [bp - 6]
0035 nop 
0036 push cs
0037 call 0x558e ; _mem_Lock
003a add sp, 2
003d mov si, ax
003f mov word ptr [bp - 2], dx
0042 push word ptr [0xcf52] ; _clipDC
0046 push 1
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 73, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 2}}]
004d mov es, word ptr [bp - 2]
0050 mov word ptr es:[si], 0x28
0055 mov word ptr es:[si + 2], 0
005b mov ax, word ptr [bp + 0xa]
005e cdq 
005f mov word ptr es:[si + 4], ax
0063 mov word ptr es:[si + 6], dx
0067 mov cx, ax
0069 mov ax, di
006b mov bx, di
006d mov di, dx
006f cdq 
0070 mov word ptr es:[si + 8], ax
0074 mov word ptr es:[si + 0xa], dx
0078 mov word ptr [bp - 0xa], ax
007b mov ax, 1
007e mov word ptr es:[si + 0xc], ax
0082 mov word ptr es:[si + 0xe], ax
0086 sub ax, ax
0088 mov word ptr es:[si + 0x12], ax
008c mov word ptr es:[si + 0x10], ax
0090 push dx
0091 push word ptr [bp - 0xa]
0094 push ax
0095 push 0x20
0097 add cx, 0x1f
009a adc di, ax
009c push di
009d push cx
009e mov di, bx
00a0 mov word ptr [bp - 0xe], si
00a3 mov word ptr [bp - 0xc], es
00a6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 169, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00ab push dx
00ac push ax
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00b2 shl ax, 1
00b4 rcl dx, 1
00b6 shl ax, 1
00b8 rcl dx, 1
00ba les bx, ptr [bp - 0xe]
00bd mov word ptr es:[bx + 0x14], ax
00c1 mov word ptr es:[bx + 0x16], dx
00c5 sub ax, ax
00c7 mov word ptr es:[bx + 0x1a], ax
00cb mov word ptr es:[bx + 0x18], ax
00cf mov word ptr es:[bx + 0x1e], ax
00d3 mov word ptr es:[bx + 0x1c], ax
00d7 mov word ptr es:[bx + 0x22], ax
00db mov word ptr es:[bx + 0x20], ax
00df mov word ptr es:[bx + 0x26], ax
00e3 mov word ptr es:[bx + 0x24], ax
00e7 mov al, 0xff
00e9 mov byte ptr es:[bx + 0x2c], al
00ed mov byte ptr es:[bx + 0x2d], al
00f1 mov byte ptr es:[bx + 0x2e], al
00f5 xor al, al
00f7 mov byte ptr es:[bx + 0x28], al
00fb mov byte ptr es:[bx + 0x29], al
00ff mov byte ptr es:[bx + 0x2a], al
0103 mov byte ptr es:[bx + 0x2b], al
0107 mov byte ptr es:[bx + 0x2f], al
010b push word ptr [0xcf52] ; _clipDC
010f push word ptr [bp + 6]
0112 push word ptr [bp + 8]
0115 push word ptr [bp + 0xa]
0118 push di
0119 push 0
011b push 0
011d push 0
011f push di
0120 push word ptr [bp + 0x10]
0123 push word ptr [bp + 0xe]
0126 push es
0127 push bx
0128 push 0
012a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 299, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 443}}]
012f push word ptr [bp - 6]
0132 nop 
0133 push cs
0134 call 0x559c ; _mem_Unlock
0137 add sp, 2
013a jmp 0x3c8a
013c cmp word ptr [bp - 6], 0
0140 je 0x3c95
0142 push word ptr [bp - 6]
0145 nop 
0146 push cs
0147 call 0x5580 ; _mem_Free
014a add sp, 2
014d pop si
014e pop di
014f leave 
0150 retf 
```

## Known declaration examples

- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_GPatBox-b326d1b571.c
- `extern int near clipDC;` — src/recovered/wf_MSClipEnd-48c3851864.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_DoMonoBitmap', 'offset': 13900, 'source': None, 'size': 870}
- {'symbol': '_DoFastBitmap', 'offset': 14770, 'source': None, 'size': 405}
- {'symbol': '_GPutPic', 'offset': 15514, 'source': 'src/recovered/wf_GPutPic-08fc158e1c.c', 'size': 104}
- {'symbol': '_GPutImg', 'offset': 15618, 'source': 'src/recovered/GPutImg.c', 'size': 57}
