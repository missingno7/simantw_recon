# Recovery task _hanim_SetObjectPos

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 974 bytes.

```asm
0000 enter 0x11e, 0
0004 push di
0005 push si
0006 push word ptr [bp + 0xc]
0009 nop 
000a push cs
000b call 0x558e ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov di, bx
0017 mov word ptr [bp - 0x12], bx
001a mov word ptr [bp - 0x10], es
001d mov ax, word ptr es:[bx]
0020 mov word ptr [bp - 0xe], ax
0023 add bx, 2
0026 mov word ptr [bp - 0x11e], bx
002a mov word ptr [bp - 0x11c], es
002e push word ptr es:[bx]
0031 nop 
0032 push cs
0033 call 0x558e ; _mem_Lock
0036 add sp, 2
0039 mov si, ax
003b mov word ptr [bp - 2], dx
003e mov ax, dx
0040 mov word ptr [bp - 8], si
0043 mov word ptr [bp - 6], ax
0046 xor ax, ax
0048 mov word ptr [bp - 0xc], ax
004b mov word ptr [bp - 0xa], ax
004e les bx, ptr [bp - 0x12]
0051 cmp word ptr es:[bx], ax
0054 jle 0x6ae2
0056 mov bx, ax
0058 mov word ptr [bp - 0x12], di
005b lds cx, ptr [bp - 0x12]
005e mov es, word ptr [bp - 6]
0061 mov ax, word ptr [bp + 0xe]
0064 cmp word ptr es:[si + 0x20], ax
0068 je 0x6b06
006a add si, 0x2c
006d inc bx
006e mov di, cx
0070 cmp word ptr [di], bx
0072 jg 0x6acd
0074 push ss
0075 pop ds
0076 xor ax, ax
0078 cdq 
0079 mov si, ax
007b mov es, dx
007d mov ax, es
007f or ax, si
0081 jne 0x6b18
0083 push word ptr [0xcd78] ; _rootWnd
0087 push ds
0088 push 0xaa7
008b push ds
008c push 0xa91
008f push 0x1010
0092 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 147, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
0097 jmp 0x6e1c
009a mov word ptr [bp - 8], si
009d push ss
009e pop ds
009f mov word ptr [bp - 0x16], bx
00a2 mov cx, si
00a4 mov ax, word ptr [bp - 6]
00a7 mov es, ax
00a9 jmp 0x6ae9
00ab nop 
00ac mov word ptr [bp - 2], es
00af mov bx, word ptr [bp + 6]
00b2 cmp bx, 0x8000
00b6 je 0x6b2a
00b8 mov word ptr es:[si + 0x16], bx
00bc jmp 0x6b31
00be mov ax, word ptr es:[si + 0x16]
00c2 mov word ptr [bp + 6], ax
00c5 cmp word ptr [bp + 8], 0x8000
00ca je 0x6b42
00cc mov ax, word ptr [bp + 8]
00cf mov word ptr es:[si + 0x18], ax
00d3 jmp 0x6b49
00d5 nop 
00d6 mov ax, word ptr es:[si + 0x18]
00da mov word ptr [bp + 8], ax
00dd cmp word ptr [bp + 0xa], 0x8000
00e2 jne 0x6b8a
00e4 mov di, word ptr es:[si + 0x26]
00e8 cmp word ptr [bp + 0x10], 0x8000
00ed jne 0x6b65
00ef mov es, word ptr [bp - 2]
00f2 mov ax, word ptr es:[si + 0x24]
00f6 mov word ptr [bp + 0x10], ax
00f9 cmp word ptr [bp + 0x10], -1
00fd jne 0x6ba7
00ff cmp di, 0x7530
0103 jl 0x6b90
0105 mov es, word ptr [0xbf74]
0109 les bx, ptr es:[0xa072]
010e mov ax, word ptr es:[bx + 8]
0112 mov word ptr [bp - 0x1a], ax
0115 mov ax, word ptr es:[bx + 0xa]
0119 mov word ptr [bp - 0x18], ax
011c jmp 0x6b9e
011e mov di, word ptr [bp + 0xa]
0121 jmp 0x6b54
0123 nop 
0124 push di
0125 lea ax, [bp - 0x1a]
0128 push ss
0129 push ax
012a nop 
012b push cs
012c call 0x465c ; _gr_BitMapSize
012f add sp, 6
0132 mov ax, word ptr [bp - 0x18]
0135 add ax, word ptr [bp + 8]
0138 mov word ptr [bp + 0x10], ax
013b mov word ptr [bp + 0xa], di
013e mov ax, word ptr [bp + 0x10]
0141 mov es, word ptr [bp - 2]
0144 cmp word ptr es:[si + 0x24], ax
0148 je 0x6bb9
014a jmp 0x6c54
014d cmp word ptr es:[si + 0x26], di
0151 je 0x6c08
0153 mov word ptr es:[si + 0x26], di
0157 cmp di, 0x7530
015b jl 0x6be2
015d mov es, word ptr [0xbf74]
0161 les bx, ptr es:[0xa072]
0166 mov ax, word ptr es:[bx + 8]
016a mov word ptr [bp - 0x1a], ax
016d mov ax, word ptr es:[bx + 0xa]
0171 mov word ptr [bp - 0x18], ax
0174 jmp 0x6bf0
0176 push di
0177 lea ax, [bp - 0x1a]
017a push ss
017b push ax
017c nop 
017d push cs
017e call 0x465c ; _gr_BitMapSize
0181 add sp, 6
0184 mov es, word ptr [bp - 2]
0187 mov ax, word ptr es:[si + 0x1a]
018b xor ax, word ptr [bp - 0x1a]
018e test ax, 0xfff8
0191 jne 0x6c54
0193 mov ax, word ptr [bp - 0x18]
0196 cmp word ptr es:[si + 0x1c], ax
019a jne 0x6c54
019c mov ax, word ptr [bp + 6]
019f and al, 0xf8
01a1 mov word ptr es:[si + 0xe], ax
01a5 add ax, word ptr es:[si + 0x1a]
01a9 add ax, 0xf
01ac and al, 0xf8
01ae mov word ptr es:[si + 0x12], ax
01b2 mov ax, word ptr [bp + 8]
01b5 mov word ptr es:[si + 0x10], ax
01b9 add ax, word ptr es:[si + 0x1c]
01bd mov word ptr es:[si + 0x14], ax
01c1 mov byte ptr es:[si + 4], 1
01c6 mov ax, word ptr [bp - 0x16]
01c9 cmp word ptr [bp - 0xe], ax
01cc jg 0x6c3d
01ce jmp 0x6e1c
01d1 mov bx, word ptr [bp - 0xe]
01d4 mov byte ptr es:[si + 3], 1
01d9 add si, 0x2c
01dc inc word ptr [bp - 0x16]
01df cmp word ptr [bp - 0x16], bx
01e2 jl 0x6c40
01e4 jmp 0x6e1c
01e7 nop 
01e8 les bx, ptr [bp - 0x11e]
01ec push word ptr es:[bx]
01ef nop 
01f0 push cs
01f1 call 0x559c ; _mem_Unlock
01f4 add sp, 2
01f7 push word ptr [bp + 0xc]
01fa nop 
01fb push cs
01fc call 0x559c ; _mem_Unlock
01ff add sp, 2
0202 push word ptr [bp + 0xc]
0205 nop 
0206 push cs
0207 call 0x558e ; _mem_Lock
020a add sp, 2
020d mov es, dx
020f mov bx, ax
0211 mov di, bx
0213 mov word ptr [bp - 0xc], es
0216 push word ptr es:[bx + 2]
021a nop 
021b push cs
021c call 0x558e ; _mem_Lock
021f add sp, 2
0222 mov si, ax
0224 mov word ptr [bp - 8], dx
0227 mov ax, dx
0229 mov word ptr [bp - 4], si
022c mov word ptr [bp - 2], ax
022f mov word ptr [bp - 6], 0
0234 mov es, word ptr [bp - 0xc]
0237 cmp word ptr es:[di], 0
023b jle 0x6cc7
023d mov cx, word ptr [bp - 6]
0240 mov word ptr [bp - 0xe], di
0243 mov ds, word ptr [bp - 0xc]
0246 mov es, dx
0248 mov ax, word ptr [bp + 0xe]
024b cmp word ptr es:[si + 0x20], ax
024f je 0x6d08
0251 add si, 0x2c
0254 inc cx
0255 cmp word ptr [di], cx
0257 jg 0x6cb4
0259 push ss
025a pop ds
025b xor ax, ax
025d cdq 
025e mov si, ax
0260 mov es, dx
0262 mov ax, es
0264 or ax, si
0266 jne 0x6d1a
0268 push word ptr [bp + 0xe]
026b push ds
026c push 0xacb
026f push ds
0270 push 0xa15
0273 lea ax, [bp - 0x11a]
0277 push ss
0278 push ax
0279 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 636, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
027e add sp, 0xe
0281 push word ptr [0xcd78] ; _rootWnd
0285 lea ax, [bp - 0x11a]
0289 push ss
028a push ax
028b push ds
028c push 0xa45
028f push 0x1010
0292 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 659, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
0297 mov word ptr [bp - 0xe], di
029a jmp 0x6d4e
029c mov word ptr [bp - 4], si
029f push ss
02a0 pop ds
02a1 mov word ptr [bp - 0x14], cx
02a4 mov ax, word ptr [bp - 2]
02a7 mov es, ax
02a9 mov di, word ptr [bp - 0xe]
02ac jmp 0x6cce
02ae mov word ptr [bp - 8], es
02b1 mov byte ptr es:[si + 5], 1
02b6 mov byte ptr es:[si], 0
02ba mov ax, word ptr [bp - 0x14]
02bd mov es, word ptr [bp - 0xc]
02c0 cmp word ptr es:[di], ax
02c3 jle 0x6d03
02c5 mov word ptr [bp - 0xe], di
02c8 mov ds, word ptr [bp - 0xc]
02cb mov es, word ptr [bp - 8]
02ce mov byte ptr es:[si + 3], 1
02d3 inc word ptr [bp - 0x14]
02d6 add si, 0x2c
02d9 mov ax, word ptr [bp - 0x14]
02dc cmp word ptr [di], ax
02de jg 0x6d3a
02e0 push ss
02e1 pop ds
02e2 les bx, ptr [bp - 0xe]
02e5 push word ptr es:[bx + 2]
02e9 nop 
02ea push cs
02eb call 0x559c ; _mem_Unlock
02ee add sp, 2
02f1 push word ptr [bp + 0xc]
02f4 nop 
02f5 push cs
02f6 call 0x559c ; _mem_Unlock
02f9 add sp, 2
02fc push word ptr [bp + 0x10]
02ff push word ptr [bp + 0xa]
0302 push word ptr [bp + 8]
0305 push word ptr [bp + 6]
0308 push word ptr [bp + 0xc]
030b nop 
030c push cs
030d call 0x6410 ; _hanim_AddAnimObject
0310 add sp, 0xa
0313 mov word ptr [bp - 0xc], ax
0316 push word ptr [bp + 0xc]
0319 nop 
031a push cs
031b call 0x558e ; _mem_Lock
031e add sp, 2
0321 mov es, dx
0323 mov bx, ax
0325 mov word ptr [bp - 0x12], bx
0328 mov word ptr [bp - 0x10], es
032b add bx, 2
032e mov word ptr [bp - 0x11e], bx
0332 mov word ptr [bp - 0x11c], es
0336 push word ptr es:[bx]
0339 nop 
033a push cs
033b call 0x558e ; _mem_Lock
033e add sp, 2
0341 mov word ptr [bp - 4], ax
0344 mov word ptr [bp - 2], dx
0347 mov word ptr [bp - 8], ax
034a mov word ptr [bp - 6], dx
034d mov word ptr [bp - 0xa], 0
0352 les bx, ptr [bp - 0x12]
0355 cmp word ptr es:[bx], 0
0359 jle 0x6dfa
035b mov bx, ax
035d mov cx, word ptr [bp - 0xa]
0360 mov di, word ptr [bp + 0xe]
0363 mov ds, word ptr [bp - 0x10]
0366 mov es, dx
0368 cmp word ptr es:[bx + 0x20], di
036c je 0x6dea
036e add bx, 0x2c
0371 inc cx
0372 mov si, word ptr [bp - 0x12]
0375 cmp word ptr [si], cx
0377 jg 0x6dd4
0379 push ss
037a pop ds
037b jmp 0x6dfa
037d nop 
037e push ss
037f pop ds
0380 mov word ptr [bp - 0x16], cx
0383 mov ax, word ptr [bp - 6]
0386 mov word ptr [bp - 4], bx
0389 mov word ptr [bp - 2], ax
038c jmp 0x6e02
038e sub ax, ax
0390 mov word ptr [bp - 2], ax
0393 mov word ptr [bp - 4], ax
0396 mov ax, word ptr [bp - 0xc]
0399 les bx, ptr [bp - 4]
039c mov word ptr es:[bx + 0x20], ax
03a0 mov ax, word ptr [bp + 0xe]
03a3 mov es, word ptr [0xbf76]
03a7 les bx, ptr es:[0x7c3e]
03ac mov word ptr es:[bx + 0x20], ax
03b0 les bx, ptr [bp - 0x11e]
03b4 push word ptr es:[bx]
03b7 nop 
03b8 push cs
03b9 call 0x559c ; _mem_Unlock
03bc add sp, 2
03bf push word ptr [bp + 0xc]
03c2 nop 
03c3 push cs
03c4 call 0x559c ; _mem_Unlock
03c7 add sp, 2
03ca pop si
03cb pop di
03cc leave 
03cd retf 
```

## Known declaration examples

- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_B324_InitTriVars_6_scaffold-355c471c2b.c
- `extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);` — src/recovered/wf_tu_simant_B324_initControls_1_scaffold-03091459d8.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawForSale-956dc12b43.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern int far hanim_AddAnimObject(int animation, int right, int bottom, int size, int layer);` — src/recovered/wf_DrawSimBird-fa6c3c3f83.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int near rootWnd;` — src/recovered/ProcMenuHelp.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_gr_0000_InitGraphics_1-8959d65c41.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/wf_tu_simtwo_81AC_db_SetDataBase_1_reviewed-7aea199e9a.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_gr_BitMapSize'], 'segment': 2, 'target_offset': 18012, 'caller_offsets': [300, 382]}
- {'callee_names': ['_mem_Lock'], 'segment': 2, 'target_offset': 21902, 'caller_offsets': [11, 51, 519, 540, 795, 827]}
- {'callee_names': ['_mem_Unlock'], 'segment': 2, 'target_offset': 21916, 'caller_offsets': [497, 508, 747, 758, 953, 964]}
- {'callee_names': ['_hanim_AddAnimObject'], 'segment': 2, 'target_offset': 25616, 'caller_offsets': [781]}

## Neighbors

- {'symbol': '_hanim_HideObject', 'offset': 26884, 'source': None, 'size': 179}
- {'symbol': '_hanim_ShowObject', 'offset': 27064, 'source': None, 'size': 179}
- {'symbol': '_hanim_MakeAnimSet', 'offset': 28218, 'source': 'src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c', 'size': 111}
- {'symbol': '_hanim_RemoveAnimSet', 'offset': 28330, 'source': 'src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c', 'size': 146}
