# Recovery task _ConvertMonoMaskToTandy

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 221 bytes.

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
0015 mov word ptr [bp - 8], bx
0018 mov word ptr [bp - 6], es
001b mov si, word ptr es:[bx + 8]
001f mov di, word ptr es:[bx + 0xa]
0023 cmp byte ptr [0xcc7e], 0xa ; _displayType
0028 jne 0x5e7c
002a push ds
002b push 0x1d3d
002e push 1
0030 mov ax, si
0032 shl ax, 2
0035 add ax, 0x1f
0038 cdq 
0039 and dx, 0x1f
003c add ax, dx
003e sar ax, 5
0041 imul di
0043 add ax, 3
0046 shl ax, 2
0049 jmp 0x5e8e
004b nop 
004c push ds
004d push 0x1d48
0050 push 1
0052 mov ax, di
0054 imul si
0056 cdq 
0057 sub ax, dx
0059 sar ax, 1
005b add ax, 0xc
005e push 0
0060 push ax
0061 nop 
0062 push cs
0063 call 0x54da ; _mem_Alloc
0066 add sp, 0xa
0069 mov word ptr [bp - 0xa], ax
006c push ax
006d nop 
006e push cs
006f call 0x558e ; _mem_Lock
0072 add sp, 2
0075 mov es, dx
0077 mov bx, ax
0079 mov word ptr es:[bx + 8], si
007d mov word ptr es:[bx + 0xa], di
0081 mov word ptr es:[bx], 3
0086 cmp byte ptr [0xcc7e], 0xa ; _displayType
008b jne 0x5ec4
008d mov byte ptr es:[bx + 2], 0x84
0092 jmp 0x5ec9
0094 mov byte ptr es:[bx + 2], 4
0099 mov ax, bx
009b mov dx, es
009d add ax, 8
00a0 push dx
00a1 push ax
00a2 mov ax, word ptr [bp - 8]
00a5 mov dx, word ptr [bp - 6]
00a8 add ax, 8
00ab push dx
00ac push ax
00ad lcall <resolved loader operand; see bindings> ; [{'operand_offset': 176, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _MaskMono2Tandy
00b2 add sp, 8
00b5 push word ptr [bp + 6]
00b8 nop 
00b9 push cs
00ba call 0x559c ; _mem_Unlock
00bd add sp, 2
00c0 push word ptr [bp - 0xa]
00c3 nop 
00c4 push cs
00c5 call 0x559c ; _mem_Unlock
00c8 add sp, 2
00cb push word ptr [bp + 6]
00ce nop 
00cf push cs
00d0 call 0x5580 ; _mem_Free
00d3 add sp, 2
00d6 mov ax, word ptr [bp - 0xa]
00d9 pop si
00da pop di
00db leave 
00dc retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_InitMapFunctions-70fb457ea5.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
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

- {'symbol': '_RallocFreed', 'offset': 22988, 'source': 'src/recovered/RallocFreed.c', 'size': 24}
- {'symbol': '_MakeBalloon', 'offset': 23012, 'source': None, 'size': 1100}
- {'symbol': '_ConvertMonoMaskToColor', 'offset': 24334, 'source': None, 'size': 379}
- {'symbol': '_font_CharWidth', 'offset': 24714, 'source': 'src/recovered/font_CharWidth.c', 'size': 36}
