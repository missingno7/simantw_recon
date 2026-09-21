# Recovery task _DecodeString

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 172 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov word ptr [bp - 2], 0
000b cmp word ptr [0x142], 0
0010 je 0x134
0012 push word ptr [0x142]
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
001b add sp, 2
001e push word ptr [0x142]
0022 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 37, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Free
0027 add sp, 2
002a push ds
002b push 0x144
002e push 1
0030 les di, ptr [bp + 6]
0033 mov cx, 0xffff
0036 xor ax, ax
0038 repne scasb al, byte ptr es:[di]
003a not cx
003c dec cx
003d push ax
003e push cx
003f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 66, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
0044 add sp, 0xa
0047 mov word ptr [0x142], ax
004a push ax
004b lcall <resolved loader operand; see bindings> ; [{'operand_offset': 78, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0050 add sp, 2
0053 mov word ptr [bp - 4], dx
0056 les bx, ptr [bp + 6]
0059 cmp byte ptr es:[bx], 0
005d jne 0x170
005f mov cx, ax
0061 mov si, word ptr [bp - 2]
0064 jmp 0x1a5
0066 mov si, word ptr [bp - 2]
0069 mov di, bx
006b mov cx, ax
006d mov ds, word ptr [bp + 8]
0070 mov es, dx
0072 mov bx, di
0074 mov al, byte ptr [bx + si]
0076 mov dx, ax
0078 shl al, 4
007b sar dl, 4
007e mov bx, ax
0080 xor al, dl
0082 and al, 0xf
0084 mov dx, bx
0086 xor bl, al
0088 mov ax, bx
008a mov bx, cx
008c add bx, si
008e mov byte ptr es:[bx], al
0091 mov bx, di
0093 inc si
0094 cmp byte ptr [bx + si], 0
0097 jne 0x17c
0099 push ss
009a pop ds
009b mov bx, cx
009d mov es, word ptr [bp - 4]
00a0 mov byte ptr es:[bx + si], 0
00a4 mov ax, cx
00a6 mov dx, es
00a8 pop si
00a9 pop di
00aa leave 
00ab retf 
```

## Known declaration examples

- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
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

- {'symbol': '_RestartSimulation', 'offset': 52, 'source': 'src/recovered/RestartSimulation.c', 'size': 28}
- {'symbol': '_CleanUp', 'offset': 80, 'source': None, 'size': 186}
- {'symbol': '_DoUserButtonUpdate', 'offset': 438, 'source': None, 'size': None}
- {'symbol': '_UpdateUserButtons', 'offset': 570, 'source': None, 'size': None}
