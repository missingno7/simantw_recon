# Recovery task _DoFastBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 405 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 push ds
0007 push 0xbab8
000a push 0
000c push 0
000e push 0x68
0010 nop 
0011 push cs
0012 call 0x54da ; _mem_Alloc
0015 add sp, 0xa
0018 mov si, ax
001a mov ax, word ptr [bp + 0x10]
001d or ax, word ptr [bp + 0xe]
0020 jne 0x39d7
0022 jmp 0x3b36
0025 or si, si
0027 jne 0x39de
0029 jmp 0x3b36
002c push si
002d nop 
002e push cs
002f call 0x558e ; _mem_Lock
0032 add sp, 2
0035 mov di, ax
0037 mov word ptr [bp - 0xc], dx
003a push word ptr [0xcf52] ; _clipDC
003e push 1
0040 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 65, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 2}}]
0045 mov es, word ptr [bp - 0xc]
0048 mov word ptr es:[di], 0x28
004d mov word ptr es:[di + 2], 0
0053 mov ax, word ptr [bp + 0xa]
0056 cdq 
0057 mov word ptr es:[di + 4], ax
005b mov word ptr es:[di + 6], dx
005f mov cx, ax
0061 mov ax, word ptr [bp + 0xc]
0064 mov bx, dx
0066 cdq 
0067 mov word ptr es:[di + 8], ax
006b mov word ptr es:[di + 0xa], dx
006f mov word ptr es:[di + 0xc], 1
0075 mov word ptr es:[di + 0xe], 4
007b mov word ptr [bp - 0x12], ax
007e sub ax, ax
0080 mov word ptr es:[di + 0x12], ax
0084 mov word ptr es:[di + 0x10], ax
0088 push dx
0089 push word ptr [bp - 0x12]
008c push ax
008d push 0x20
008f shl cx, 1
0091 rcl bx, 1
0093 shl cx, 1
0095 rcl bx, 1
0097 add cx, 0x1f
009a adc bx, ax
009c push bx
009d push cx
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
00a3 push dx
00a4 push ax
00a5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 168, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
00aa shl ax, 1
00ac rcl dx, 1
00ae shl ax, 1
00b0 rcl dx, 1
00b2 mov es, word ptr [bp - 0xc]
00b5 mov word ptr es:[di + 0x14], ax
00b9 mov word ptr es:[di + 0x16], dx
00bd sub ax, ax
00bf mov word ptr es:[di + 0x1a], ax
00c3 mov word ptr es:[di + 0x18], ax
00c7 mov word ptr es:[di + 0x1e], ax
00cb mov word ptr es:[di + 0x1c], ax
00cf mov word ptr es:[di + 0x22], ax
00d3 mov word ptr es:[di + 0x20], ax
00d7 mov word ptr es:[di + 0x26], ax
00db mov word ptr es:[di + 0x24], ax
00df mov word ptr [bp - 8], ax
00e2 mov word ptr [bp - 0xa], si
00e5 lea ax, [di + 0x28]
00e8 mov dx, es
00ea mov ds, dx
00ec mov word ptr [bp - 6], 0
00f1 mov word ptr [bp - 0xe], di
00f4 mov si, ax
00f6 mov di, word ptr [bp - 6]
00f9 mov cx, word ptr [bp - 8]
00fc cmp word ptr [bp + 0x12], 0
0100 je 0x3ad0
0102 mov <resolved loader operand; see bindings> ; [{'operand_offset': 259, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0105 mov es, ax
0107 mov al, byte ptr es:[di - 0x73fe]
010c mov byte ptr [si], al
010e mov al, byte ptr es:[di - 0x73ff]
0113 mov byte ptr [si + 1], al
0116 mov al, byte ptr es:[di - 0x7400]
011b jmp 0x3ae9
011d nop 
011e mov <resolved loader operand; see bindings> ; [{'operand_offset': 287, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
0121 mov es, ax
0123 mov al, byte ptr es:[di - 0x73be]
0128 mov byte ptr [si], al
012a mov al, byte ptr es:[di - 0x73bf]
012f mov byte ptr [si + 1], al
0132 mov al, byte ptr es:[di - 0x73c0]
0137 mov byte ptr [si + 2], al
013a mov byte ptr [si + 3], 0
013e add si, 4
0141 add di, 4
0144 cmp di, 0x40
0147 jl 0x3aae
0149 push ss
014a pop ds
014b mov si, word ptr [bp - 0xa]
014e mov di, word ptr [bp + 0xc]
0151 push word ptr [0xcf52] ; _clipDC
0155 push word ptr [bp + 6]
0158 push word ptr [bp + 8]
015b push word ptr [bp + 0xa]
015e push di
015f push 0
0161 push 0
0163 push 0
0165 push di
0166 push word ptr [bp + 0x10]
0169 push word ptr [bp + 0xe]
016c push word ptr [bp - 0xc]
016f push word ptr [bp - 0xe]
0172 push 0
0174 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 373, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 443}}]
0179 push si
017a nop 
017b push cs
017c call 0x559c ; _mem_Unlock
017f add sp, 2
0182 jmp 0x3b3a
0184 or si, si
0186 je 0x3b43
0188 push si
0189 nop 
018a push cs
018b call 0x5580 ; _mem_Free
018e add sp, 2
0191 pop si
0192 pop di
0193 leave 
0194 retf 
```

## Known declaration examples

- `extern char far Dx8[];` — src/recovered/wf_AddRandAntLion-bd2ae22846.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListA-2c6f7e42f7.c
- `extern unsigned char far Dx8[];` — src/recovered/wf_CompactListB-6f09945019.c
- `extern int near clipDC;` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int near clipDC;` — src/recovered/wf_GLine-590430737a.c
- `extern int near clipDC;` — src/recovered/wf_GPatBox-b326d1b571.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ConvertMonoBitmap', 'offset': 13776, 'source': None, 'size': 123}
- {'symbol': '_DoMonoBitmap', 'offset': 13900, 'source': None, 'size': 870}
- {'symbol': '_DoFastMonoBitmap', 'offset': 15176, 'source': 'src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c', 'size': 337}
- {'symbol': '_GPutPic', 'offset': 15514, 'source': 'src/recovered/wf_GPutPic-08fc158e1c.c', 'size': 104}
