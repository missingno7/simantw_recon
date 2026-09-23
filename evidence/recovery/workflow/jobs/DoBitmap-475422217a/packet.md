# Recovery task _DoBitmap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 678 bytes.

```asm
0000 enter 0x30, 0
0004 push di
0005 push si
0006 push ds
0007 push 0xbaac
000a push 0
000c mov ax, word ptr [bp + 0xc]
000f cdq 
0010 mov word ptr [bp - 0x30], ax
0013 mov word ptr [bp - 0x2e], dx
0016 push dx
0017 push ax
0018 push 0
001a push 0x20
001c mov ax, word ptr [bp + 0xa]
001f cdq 
0020 mov word ptr [bp - 0x2c], ax
0023 mov word ptr [bp - 0x2a], dx
0026 shl ax, 1
0028 rcl dx, 1
002a shl ax, 1
002c rcl dx, 1
002e add ax, 0x1f
0031 adc dx, 0
0034 push dx
0035 push ax
0036 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 57, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFldiv
003b push dx
003c push ax
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; __aFulmul,__aFlmul
0042 shl ax, 1
0044 rcl dx, 1
0046 shl ax, 1
0048 rcl dx, 1
004a mov word ptr [bp - 0x28], ax
004d mov word ptr [bp - 0x26], dx
0050 add ax, 0x20
0053 adc dx, 0
0056 push dx
0057 push ax
0058 nop 
0059 push cs
005a call 0x54da ; _mem_Alloc
005d add sp, 0xa
0060 mov di, ax
0062 push ds
0063 push 0xbaaf
0066 push 0
0068 push 0
006a push 0x68
006c nop 
006d push cs
006e call 0x54da ; _mem_Alloc
0071 add sp, 0xa
0074 mov si, ax
0076 mov ax, word ptr [bp + 0x10]
0079 or ax, word ptr [bp + 0xe]
007c jne 0x33ab
007e jmp 0x35b2
0081 or di, di
0083 jne 0x33b2
0085 jmp 0x35b2
0088 or si, si
008a jne 0x33b9
008c jmp 0x35b2
008f push di
0090 nop 
0091 push cs
0092 call 0x558e ; _mem_Lock
0095 add sp, 2
0098 mov word ptr [bp - 0x1c], ax
009b mov word ptr [bp - 0x1a], dx
009e push si
009f nop 
00a0 push cs
00a1 call 0x558e ; _mem_Lock
00a4 add sp, 2
00a7 mov word ptr [bp - 0x20], ax
00aa mov word ptr [bp - 0x1e], dx
00ad push word ptr [0xcf52] ; _clipDC
00b1 push 1
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 180, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 2}}]
00b8 cmp word ptr [bp + 0x12], 0
00bc je 0x340c
00be mov word ptr [bp - 0x22], si
00c1 mov word ptr [bp - 0x24], di
00c4 push word ptr [bp + 0xa]
00c7 push word ptr [bp + 0xc]
00ca push word ptr [bp + 0x10]
00cd push word ptr [bp + 0xe]
00d0 push word ptr [bp - 0x1a]
00d3 push word ptr [bp - 0x1c]
00d6 nop 
00d7 push cs
00d8 call 0x246e ; _ConvertBitmap
00db add sp, 0xc
00de jmp 0x3488
00e0 nop 
00e1 nop 
00e2 mov word ptr [bp - 0x22], si
00e5 mov word ptr [bp - 0x24], di
00e8 mov ax, word ptr [bp - 0x28]
00eb mov dx, word ptr [bp - 0x26]
00ee mov word ptr [bp - 4], ax
00f1 mov word ptr [bp - 2], dx
00f4 mov ax, word ptr [bp + 0xe]
00f7 mov dx, word ptr [bp + 0x10]
00fa mov word ptr [bp - 8], ax
00fd mov word ptr [bp - 6], dx
0100 mov ax, word ptr [bp - 0x1c]
0103 mov dx, word ptr [bp - 0x1a]
0106 mov word ptr [bp - 0xc], ax
0109 mov word ptr [bp - 0xa], dx
010c sub ax, ax
010e cmp word ptr [bp - 2], ax
0111 jne 0x3442
0113 cmp word ptr [bp - 4], ax
0116 je 0x3488
0118 mov ax, word ptr [bp - 4]
011b mov dx, word ptr [bp - 2]
011e mov word ptr [bp - 0x14], ax
0121 mov ax, dx
0123 mov word ptr [bp - 0x12], ax
0126 neg word ptr [bp - 0x14]
0129 neg word ptr [bp - 0x14]
012c adc word ptr [bp - 0x12], -1
0130 mov cx, word ptr [bp - 0x12]
0133 mov si, word ptr [bp - 0x14]
0136 les bx, ptr [bp - 8]
0139 add word ptr [bp - 8], 1
013d jae 0x346e
013f add <resolved loader operand; see bindings> ; [{'operand_offset': 322, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 114}}]
0144 mov al, byte ptr es:[bx]
0147 les bx, ptr [bp - 0xc]
014a add word ptr [bp - 0xc], 1
014e jae 0x347f
0150 add <resolved loader operand; see bindings> ; [{'operand_offset': 339, 'type': 5, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 114}}]
0155 mov byte ptr es:[bx], al
0158 dec si
0159 jne 0x3460
015b dec cx
015c jns 0x3460
015e les di, ptr [bp - 0x20]
0161 mov word ptr es:[di], 0x28
0166 mov word ptr es:[di + 2], 0
016c mov ax, word ptr [bp - 0x2c]
016f mov dx, word ptr [bp - 0x2a]
0172 mov word ptr es:[di + 4], ax
0176 mov word ptr es:[di + 6], dx
017a mov ax, word ptr [bp - 0x30]
017d mov dx, word ptr [bp - 0x2e]
0180 mov word ptr es:[di + 8], ax
0184 mov word ptr es:[di + 0xa], dx
0188 mov word ptr es:[di + 0xc], 1
018e mov word ptr es:[di + 0xe], 4
0194 sub ax, ax
0196 mov word ptr es:[di + 0x12], ax
019a mov word ptr es:[di + 0x10], ax
019e mov ax, word ptr [bp - 0x28]
01a1 mov dx, word ptr [bp - 0x26]
01a4 mov word ptr es:[di + 0x14], ax
01a8 mov word ptr es:[di + 0x16], dx
01ac sub ax, ax
01ae mov word ptr es:[di + 0x1a], ax
01b2 mov word ptr es:[di + 0x18], ax
01b6 mov word ptr es:[di + 0x1e], ax
01ba mov word ptr es:[di + 0x1c], ax
01be mov word ptr es:[di + 0x22], ax
01c2 mov word ptr es:[di + 0x20], ax
01c6 mov word ptr es:[di + 0x26], ax
01ca mov word ptr es:[di + 0x24], ax
01ce mov word ptr [bp - 8], ax
01d1 lea ax, [di + 0x28]
01d4 mov si, ax
01d6 mov word ptr [bp - 4], es
01d9 mov word ptr [bp - 2], 0
01de mov di, word ptr [bp - 2]
01e1 mov cx, word ptr [bp - 8]
01e4 mov ds, word ptr [bp - 4]
01e7 cmp word ptr ss:[0xba2e], 0
01ed je 0x3534
01ef mov <resolved loader operand; see bindings> ; [{'operand_offset': 496, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
01f2 mov es, ax
01f4 mov al, byte ptr es:[di - 0x73fe]
01f9 mov byte ptr [si], al
01fb mov al, byte ptr es:[di - 0x73ff]
0200 mov byte ptr [si + 1], al
0203 mov al, byte ptr es:[di - 0x7400]
0208 jmp 0x354d
020a mov <resolved loader operand; see bindings> ; [{'operand_offset': 523, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 8}}] ; _Dx8
020d mov es, ax
020f mov al, byte ptr es:[di - 0x73be]
0214 mov byte ptr [si], al
0216 mov al, byte ptr es:[di - 0x73bf]
021b mov byte ptr [si + 1], al
021e mov al, byte ptr es:[di - 0x73c0]
0223 mov byte ptr [si + 2], al
0226 mov byte ptr [si + 3], 0
022a add si, 4
022d add di, 4
0230 cmp di, 0x40
0233 jl 0x3511
0235 push ss
0236 pop ds
0237 mov si, word ptr [bp - 0x22]
023a mov di, word ptr [bp + 0xc]
023d push word ptr [0xcf52] ; _clipDC
0241 push word ptr [bp + 6]
0244 push word ptr [bp + 8]
0247 push word ptr [bp + 0xa]
024a push di
024b push 0
024d push 0
024f push 0
0251 push di
0252 push word ptr [bp - 0x1a]
0255 push word ptr [bp - 0x1c]
0258 push word ptr [bp - 0x1e]
025b push word ptr [bp - 0x20]
025e push 0
0260 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 609, 'type': 3, 'target': {'kind': 'import', 'module': 'GDI', 'ordinal': 443}}]
0265 push word ptr [bp - 0x24]
0268 nop 
0269 push cs
026a call 0x559c ; _mem_Unlock
026d add sp, 2
0270 push word ptr [bp - 0x24]
0273 nop 
0274 push cs
0275 call 0x5580 ; _mem_Free
0278 add sp, 2
027b push si
027c nop 
027d push cs
027e call 0x559c ; _mem_Unlock
0281 add sp, 2
0284 push si
0285 jmp 0x35c4
0287 nop 
0288 or si, si
028a je 0x35bf
028c push si
028d nop 
028e push cs
028f call 0x5580 ; _mem_Free
0292 add sp, 2
0295 or di, di
0297 je 0x35cc
0299 push di
029a nop 
029b push cs
029c call 0x5580 ; _mem_Free
029f add sp, 2
02a2 pop si
02a3 pop di
02a4 leave 
02a5 retf 
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

- {'symbol': '_CopyMonoBitmap', 'offset': 11186, 'source': None, 'size': 801}
- {'symbol': '_CopyMonoMaskBitmap', 'offset': 11988, 'source': None, 'size': 1110}
- {'symbol': '_ConvertMonoBitmap', 'offset': 13776, 'source': None, 'size': 123}
- {'symbol': '_DoMonoBitmap', 'offset': 13900, 'source': None, 'size': 870}
