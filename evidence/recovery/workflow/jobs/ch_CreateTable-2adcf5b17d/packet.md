# Recovery task _ch_CreateTable

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 265 bytes.

```asm
0000 enter 0x10, 0
0004 push di
0005 push si
0006 mov si, word ptr [bp + 6]
0009 or si, si
000b jne 0x8f5a
000d mov si, 0x96
0010 jmp 0x8ff5
0013 nop 
0014 mov word ptr [bp - 0x10], 1
0019 mov word ptr [bp - 0xe], 2
001e xor di, di
0020 push ds
0021 push 0xb655
0024 push 0x320
0027 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 42, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_malloc
002c add sp, 6
002f mov word ptr [bp - 0xc], ax
0032 mov word ptr [bp - 0xa], dx
0035 cmp si, 1
0038 jle 0x8fe4
003a mov word ptr [bp - 8], di
003d mov si, di
003f mov es, dx
0041 cmp si, 0x190
0045 jl 0x8f92
0047 push ss
0048 pop ds
0049 jmp 0x8fe4
004b nop 
004c xor di, di
004e or si, si
0050 jle 0x8fc6
0052 mov word ptr [bp - 8], si
0055 mov ax, word ptr [bp - 0xc]
0058 mov cx, es
005a mov word ptr [bp - 4], ax
005d mov ds, cx
005f mov si, di
0061 mov bx, ax
0063 mov ax, word ptr [bp - 0xe]
0066 cdq 
0067 idiv word ptr [bx]
0069 or dx, dx
006b jne 0x8fba
006d mov si, word ptr [bp - 8]
0070 push ss
0071 pop ds
0072 jmp 0x8fd9
0074 add bx, 2
0077 inc si
0078 cmp si, word ptr [bp - 8]
007b jl 0x8fa9
007d mov si, word ptr [bp - 8]
0080 push ss
0081 pop ds
0082 mov ax, word ptr [bp - 0xe]
0085 mov word ptr [bp - 0x10], ax
0088 mov bx, si
008a shl bx, 1
008c add bx, word ptr [bp - 0xc]
008f mov word ptr es:[bx], ax
0092 inc si
0093 inc word ptr [bp - 0xe]
0096 mov ax, word ptr [bp + 6]
0099 cmp word ptr [bp - 0x10], ax
009c jl 0x8f87
009e push word ptr [bp - 0xa]
00a1 push word ptr [bp - 0xc]
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_free
00a9 add sp, 4
00ac mov si, word ptr [bp - 0x10]
00af push ds
00b0 push 0xb588
00b3 push 0
00b5 mov ax, si
00b7 shl si, 1
00b9 add si, ax
00bb shl si, 1
00bd add si, 4
00c0 push 0
00c2 push si
00c3 mov si, ax
00c5 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 200, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Alloc
00ca add sp, 0xa
00cd push ax
00ce mov di, ax
00d0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 211, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00d5 add sp, 2
00d8 mov word ptr [bp - 4], ax
00db mov word ptr [bp - 2], dx
00de lea cx, [si + 1]
00e1 shl cx, 2
00e4 mov ax, 0xffff
00e7 push di
00e8 les di, ptr [bp - 4]
00eb rep stosb byte ptr es:[di], al
00ed pop di
00ee mov bx, word ptr [bp - 4]
00f1 mov word ptr es:[bx], si
00f4 mov word ptr es:[bx + 2], 0
00fa push di
00fb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 254, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0100 add sp, 2
0103 mov ax, di
0105 pop si
0106 pop di
0107 leave 
0108 retf 
```

## Known declaration examples

- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
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

- {'symbol': '_GetFreeHandle', 'offset': 36548, 'source': None, 'size': 72}
- {'symbol': '_DosPunt', 'offset': 36620, 'source': None, 'size': 57}
- {'symbol': '_ch_RemoveEntry', 'offset': 36944, 'source': None, 'size': 114}
- {'symbol': '_ch_PurgeCache', 'offset': 37058, 'source': None, 'size': 128}
