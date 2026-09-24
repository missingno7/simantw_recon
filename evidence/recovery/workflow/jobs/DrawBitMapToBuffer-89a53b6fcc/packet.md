# Recovery task _DrawBitMapToBuffer

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 1004 bytes.

```asm
0000 enter 0x1c, 0
0004 push di
0005 push si
0006 push 1
0008 push 2
000a push word ptr [bp + 0x12]
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0012 add sp, 6
0015 mov word ptr [bp - 6], ax
0018 push ax
0019 nop 
001a push cs
001b call 0x558e ; _mem_Lock
001e add sp, 2
0021 mov es, dx
0023 mov bx, ax
0025 mov di, bx
0027 mov word ptr [bp - 8], es
002a cmp word ptr es:[bx], -1
002e je 0x41c1
0030 jmp 0x43be
0033 push word ptr [bp - 6]
0036 nop 
0037 push cs
0038 call 0x558e ; _mem_Lock
003b add sp, 2
003e mov es, dx
0040 mov bx, ax
0042 mov si, word ptr es:[bx + 2]
0046 push ds
0047 push 0xbac4
004a push 1
004c push 0
004e push si
004f mov di, bx
0051 mov word ptr [bp - 0x1c], di
0054 mov word ptr [bp - 0x1a], es
0057 nop 
0058 push cs
0059 call 0x54da ; _mem_Alloc
005c add sp, 0xa
005f mov word ptr [bp - 0xc], ax
0062 push ax
0063 nop 
0064 push cs
0065 call 0x558e ; _mem_Lock
0068 add sp, 2
006b mov di, ax
006d mov word ptr [bp - 8], dx
0070 push si
0071 mov ax, word ptr [bp - 0x1c]
0074 mov dx, word ptr [bp - 0x1a]
0077 add ax, 4
007a adc dx, 0
007d push dx
007e push ax
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UnpackInit
0084 add sp, 6
0087 push 0xc
0089 lea ax, [bp - 0x18]
008c push ss
008d push ax
008e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 145, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Unpack
0093 add sp, 6
0096 lea ax, [si - 0x10]
0099 push ax
009a push word ptr [bp - 8]
009d push di
009e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 161, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Unpack
00a3 add sp, 6
00a6 push ax
00a7 push si
00a8 push ds
00a9 push 0xbac8
00ac nop 
00ad push cs
00ae call 0x62bc ; _WinPrintf
00b1 add sp, 8
00b4 push word ptr [bp - 6]
00b7 nop 
00b8 push cs
00b9 call 0x559c ; _mem_Unlock
00bc add sp, 2
00bf push word ptr [bp - 0xc]
00c2 nop 
00c3 push cs
00c4 call 0x559c ; _mem_Unlock
00c7 add sp, 2
00ca push word ptr [bp - 0xc]
00cd nop 
00ce push cs
00cf call 0x558e ; _mem_Lock
00d2 add sp, 2
00d5 mov word ptr [bp - 4], ax
00d8 mov word ptr [bp - 2], dx
00db mov ax, word ptr [bp - 0x18]
00de or ax, ax
00e0 je 0x427c
00e2 sub ax, 3
00e5 jne 0x4278
00e7 jmp 0x430c
00ea jmp 0x4399
00ed nop 
00ee test byte ptr [0xcc7e], 1 ; _displayType
00f3 jne 0x42e0
00f5 test byte ptr [bp - 0x16], 0x80
00f9 jne 0x42b4
00fb mov si, word ptr [bp + 0xe]
00fe mov ax, si
0100 sub si, word ptr [bp - 0xe]
0103 sub si, word ptr [bp + 0xc]
0106 push si
0107 push word ptr [bp + 0xa]
010a push word ptr [bp - 0x10]
010d push word ptr [bp - 0xe]
0110 push word ptr [bp + 0x10]
0113 push ax
0114 push dx
0115 push word ptr [bp - 4]
0118 push word ptr [bp + 8]
011b push word ptr [bp + 6]
011e nop 
011f push cs
0120 call 0x2710 ; _ConvertBitmap2
0123 jmp 0x4396
0126 mov si, word ptr [bp + 0xe]
0129 mov ax, si
012b sub si, word ptr [bp - 0xe]
012e sub si, word ptr [bp + 0xc]
0131 push si
0132 push word ptr [bp + 0xa]
0135 push word ptr [bp - 0x10]
0138 push word ptr [bp - 0xe]
013b push word ptr [bp + 0x10]
013e push ax
013f push dx
0140 push word ptr [bp - 4]
0143 push word ptr [bp + 8]
0146 push word ptr [bp + 6]
0149 nop 
014a push cs
014b call 0x2a40 ; _CopyBitmap2
014e jmp 0x4396
0151 nop 
0152 mov si, word ptr [bp + 0xe]
0155 mov ax, si
0157 sub si, word ptr [bp - 0xe]
015a sub si, word ptr [bp + 0xc]
015d push si
015e push word ptr [bp + 0xa]
0161 push word ptr [bp - 0x10]
0164 push word ptr [bp - 0xe]
0167 push word ptr [bp + 0x10]
016a push ax
016b push dx
016c push word ptr [bp - 4]
016f push word ptr [bp + 8]
0172 push word ptr [bp + 6]
0175 nop 
0176 push cs
0177 call 0x2bb2 ; _CopyMonoBitmap
017a jmp 0x4396
017d nop 
017e test byte ptr [0xcc7e], 1 ; _displayType
0183 jne 0x436e
0185 test byte ptr [bp - 0x16], 0x80
0189 jne 0x4344
018b mov si, word ptr [bp + 0xe]
018e mov ax, si
0190 sub si, word ptr [bp - 0xe]
0193 sub si, word ptr [bp + 0xc]
0196 push si
0197 push word ptr [bp + 0xa]
019a push word ptr [bp - 0x10]
019d push word ptr [bp - 0xe]
01a0 push word ptr [bp + 0x10]
01a3 push ax
01a4 push dx
01a5 push word ptr [bp - 4]
01a8 push word ptr [bp + 8]
01ab push word ptr [bp + 6]
01ae nop 
01af push cs
01b0 call 0x1f04 ; _ConvertMaskBitmap2
01b3 jmp 0x4396
01b5 nop 
01b6 mov si, word ptr [bp + 0xe]
01b9 mov ax, si
01bb sub si, word ptr [bp - 0xe]
01be sub si, word ptr [bp + 0xc]
01c1 push si
01c2 push word ptr [bp + 0xa]
01c5 push word ptr [bp - 0x10]
01c8 push word ptr [bp - 0xe]
01cb push word ptr [bp + 0x10]
01ce push ax
01cf push dx
01d0 push word ptr [bp - 4]
01d3 push word ptr [bp + 8]
01d6 push word ptr [bp + 6]
01d9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 476, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _CopyMaskBitmap2
01de jmp 0x4396
01e0 mov si, word ptr [bp + 0xe]
01e3 mov ax, si
01e5 sub si, word ptr [bp - 0xe]
01e8 sub si, word ptr [bp + 0xc]
01eb push si
01ec push word ptr [bp + 0xa]
01ef push word ptr [bp - 0x10]
01f2 push word ptr [bp - 0xe]
01f5 push word ptr [bp + 0x10]
01f8 push ax
01f9 push dx
01fa push word ptr [bp - 4]
01fd push word ptr [bp + 8]
0200 push word ptr [bp + 6]
0203 nop 
0204 push cs
0205 call 0x2ed4 ; _CopyMonoMaskBitmap
0208 add sp, 0x14
020b push word ptr [bp - 0xc]
020e nop 
020f push cs
0210 call 0x559c ; _mem_Unlock
0213 add sp, 2
0216 push word ptr [bp - 0xc]
0219 nop 
021a push cs
021b call 0x5580 ; _mem_Free
021e add sp, 2
0221 mov ax, word ptr [bp - 0x10]
0224 les bx, ptr [bp + 0x18]
0227 mov word ptr es:[bx], ax
022a mov ax, word ptr [bp - 0xe]
022d jmp 0x455a
0230 mov ax, es
0232 mov si, di
0234 mov word ptr [bp - 2], ax
0237 mov ax, word ptr es:[di]
023a or ax, ax
023c je 0x43d8
023e sub ax, 3
0241 jne 0x43d4
0243 jmp 0x4490
0246 jmp 0x4545
0249 nop 
024a test byte ptr [0xcc7e], 1 ; _displayType
024f jne 0x4456
0251 mov es, word ptr [bp - 2]
0254 test byte ptr es:[si + 2], 0x80
0259 jne 0x4420
025b mov di, word ptr [bp + 0xe]
025e mov ax, di
0260 sub di, word ptr es:[si + 0xa]
0264 sub di, word ptr [bp + 0xc]
0267 push di
0268 push word ptr [bp + 0xa]
026b push word ptr es:[si + 8]
026f push word ptr es:[si + 0xa]
0273 push word ptr [bp + 0x10]
0276 push ax
0277 mov ax, si
0279 mov dx, es
027b add ax, 0xc
027e adc dx, 0
0281 push dx
0282 push ax
0283 push word ptr [bp + 8]
0286 push word ptr [bp + 6]
0289 nop 
028a push cs
028b call 0x2710 ; _ConvertBitmap2
028e jmp 0x4542
0291 nop 
0292 mov di, word ptr [bp + 0xe]
0295 mov ax, di
0297 sub di, word ptr es:[si + 0xa]
029b sub di, word ptr [bp + 0xc]
029e push di
029f push word ptr [bp + 0xa]
02a2 push word ptr es:[si + 8]
02a6 push word ptr es:[si + 0xa]
02aa push word ptr [bp + 0x10]
02ad push ax
02ae mov ax, si
02b0 mov dx, es
02b2 add ax, 0xc
02b5 adc dx, 0
02b8 push dx
02b9 push ax
02ba push word ptr [bp + 8]
02bd push word ptr [bp + 6]
02c0 nop 
02c1 push cs
02c2 call 0x2a40 ; _CopyBitmap2
02c5 jmp 0x4542
02c8 mov di, word ptr [bp + 0xe]
02cb mov es, word ptr [bp - 2]
02ce mov ax, di
02d0 sub di, word ptr es:[si + 0xa]
02d4 sub di, word ptr [bp + 0xc]
02d7 push di
02d8 push word ptr [bp + 0xa]
02db push word ptr es:[si + 8]
02df push word ptr es:[si + 0xa]
02e3 push word ptr [bp + 0x10]
02e6 push ax
02e7 mov ax, si
02e9 mov dx, es
02eb add ax, 0xc
02ee adc dx, 0
02f1 push dx
02f2 push ax
02f3 push word ptr [bp + 8]
02f6 push word ptr [bp + 6]
02f9 nop 
02fa push cs
02fb call 0x2bb2 ; _CopyMonoBitmap
02fe jmp 0x4542
0301 nop 
0302 test byte ptr [0xcc7e], 1 ; _displayType
0307 jne 0x450c
0309 mov es, word ptr [bp - 2]
030c test byte ptr es:[si + 2], 0x80
0311 jne 0x44d6
0313 mov di, word ptr [bp + 0xe]
0316 mov ax, di
0318 sub di, word ptr es:[si + 0xa]
031c sub di, word ptr [bp + 0xc]
031f push di
0320 push word ptr [bp + 0xa]
0323 push word ptr es:[si + 8]
0327 push word ptr es:[si + 0xa]
032b push word ptr [bp + 0x10]
032e push ax
032f mov ax, si
0331 mov dx, es
0333 add ax, 0xc
0336 adc dx, 0
0339 push dx
033a push ax
033b push word ptr [bp + 8]
033e push word ptr [bp + 6]
0341 nop 
0342 push cs
0343 call 0x1f04 ; _ConvertMaskBitmap2
0346 jmp 0x4542
0348 mov di, word ptr [bp + 0xe]
034b mov ax, di
034d sub di, word ptr es:[si + 0xa]
0351 sub di, word ptr [bp + 0xc]
0354 push di
0355 push word ptr [bp + 0xa]
0358 push word ptr es:[si + 8]
035c push word ptr es:[si + 0xa]
0360 push word ptr [bp + 0x10]
0363 push ax
0364 mov ax, si
0366 mov dx, es
0368 add ax, 0xc
036b adc dx, 0
036e push dx
036f push ax
0370 push word ptr [bp + 8]
0373 push word ptr [bp + 6]
0376 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 889, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _CopyMaskBitmap2
037b jmp 0x4542
037d nop 
037e mov di, word ptr [bp + 0xe]
0381 mov es, word ptr [bp - 2]
0384 mov ax, di
0386 sub di, word ptr es:[si + 0xa]
038a sub di, word ptr [bp + 0xc]
038d push di
038e push word ptr [bp + 0xa]
0391 push word ptr es:[si + 8]
0395 push word ptr es:[si + 0xa]
0399 push word ptr [bp + 0x10]
039c push ax
039d mov ax, si
039f mov dx, es
03a1 add ax, 0xc
03a4 adc dx, 0
03a7 push dx
03a8 push ax
03a9 push word ptr [bp + 8]
03ac push word ptr [bp + 6]
03af nop 
03b0 push cs
03b1 call 0x2ed4 ; _CopyMonoMaskBitmap
03b4 add sp, 0x14
03b7 mov es, word ptr [bp - 2]
03ba mov ax, word ptr es:[si + 8]
03be mov cx, es
03c0 les bx, ptr [bp + 0x18]
03c3 mov word ptr es:[bx], ax
03c6 mov es, cx
03c8 mov ax, word ptr es:[si + 0xa]
03cc les bx, ptr [bp + 0x14]
03cf mov word ptr es:[bx], ax
03d2 push word ptr [bp - 6]
03d5 nop 
03d6 push cs
03d7 call 0x559c ; _mem_Unlock
03da add sp, 2
03dd push word ptr [bp - 6]
03e0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 995, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_ReleaseHandle
03e5 add sp, 2
03e8 pop si
03e9 pop di
03ea leave 
03eb retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_initStuff-9712c2c2ff.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
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
- Named NOP; PUSH CS; CALL near sites match LINK same-segment far-call translation. Use linker_lowered_far_calls for site offsets; do not infer a near C prototype from the final CALL opcode.

## LINK-lowered far-call evidence

- {'callee_names': ['_ConvertMaskBitmap2'], 'segment': 2, 'target_offset': 7940, 'caller_offsets': [432, 835]}
- {'callee_names': ['_ConvertBitmap2'], 'segment': 2, 'target_offset': 10000, 'caller_offsets': [288, 651]}
- {'callee_names': ['_CopyBitmap2'], 'segment': 2, 'target_offset': 10816, 'caller_offsets': [331, 706]}
- {'callee_names': ['_CopyMonoBitmap'], 'segment': 2, 'target_offset': 11186, 'caller_offsets': [375, 763]}
- {'callee_names': ['_CopyMonoMaskBitmap'], 'segment': 2, 'target_offset': 11988, 'caller_offsets': [517, 945]}
- {'callee_names': ['_mem_Alloc'], 'segment': 2, 'target_offset': 21722, 'caller_offsets': [89]}
- {'callee_names': ['_mem_Free'], 'segment': 2, 'target_offset': 21888, 'caller_offsets': [539]}
- {'callee_names': ['_mem_Lock'], 'segment': 2, 'target_offset': 21902, 'caller_offsets': [27, 56, 101, 207]}
- {'callee_names': ['_mem_Unlock'], 'segment': 2, 'target_offset': 21916, 'caller_offsets': [185, 196, 528, 983]}
- {'callee_names': ['_WinPrintf'], 'segment': 2, 'target_offset': 25276, 'caller_offsets': [174]}

## Neighbors

- {'symbol': '_GBoxMove', 'offset': 16466, 'source': 'src/recovered/wf_GBoxMove-31918745e5.c', 'size': 129}
- {'symbol': '_GUnpackPic', 'offset': 16596, 'source': None, 'size': 186}
- {'symbol': '_MySetCapture', 'offset': 17786, 'source': None, 'size': 88}
- {'symbol': '_MyReleaseCapture', 'offset': 17874, 'source': 'src/recovered/MyReleaseCapture.c', 'size': 29}
