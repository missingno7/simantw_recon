# Recovery task _hanim_RenderAnimSet

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 1187 bytes.

```asm
0000 enter 0x22, 0
0004 push di
0005 push si
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 9, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; PROFSTART
000b test byte ptr [0xcc7e], 1 ; _displayType
0010 je 0x6f6a
0012 push ds
0013 push 0xae6
0016 push 1
0018 push 0
001a push 0x1770
001d nop 
001e push cs
001f call 0x54da ; _mem_Alloc
0022 add sp, 0xa
0025 push ax
0026 nop 
0027 push cs
0028 call 0x5580 ; _mem_Free
002b add sp, 2
002e push word ptr [bp + 6]
0031 nop 
0032 push cs
0033 call 0x558e ; _mem_Lock
0036 add sp, 2
0039 mov es, dx
003b mov bx, ax
003d mov di, ax
003f mov word ptr [bp - 6], es
0042 push word ptr es:[bx + 2]
0046 nop 
0047 push cs
0048 call 0x558e ; _mem_Lock
004b add sp, 2
004e mov si, ax
0050 mov word ptr [bp - 0xa], dx
0053 mov word ptr [bp - 2], 0
0058 mov es, word ptr [bp - 6]
005b cmp word ptr es:[di], 0
005f jle 0x6ffc
0061 mov word ptr [bp - 8], di
0064 mov di, word ptr [bp - 2]
0067 mov es, word ptr [bp - 0xa]
006a push word ptr es:[si + 0x22]
006e nop 
006f push cs
0070 call 0x558e ; _mem_Lock
0073 add sp, 2
0076 mov es, word ptr [bp - 0xa]
0079 mov word ptr es:[si + 0x28], ax
007d mov word ptr es:[si + 0x2a], dx
0081 push word ptr es:[si + 0x22]
0085 nop 
0086 push cs
0087 call 0x55aa ; _mem_Size
008a add sp, 2
008d mov es, word ptr [bp - 0xa]
0090 mov cx, word ptr es:[si + 0x1e]
0094 mov bx, cx
0096 shl cx, 1
0098 add cx, bx
009a sub bx, bx
009c cmp bx, dx
009e jb 0x6fee
00a0 ja 0x6fe2
00a2 cmp cx, ax
00a4 jbe 0x6fee
00a6 push ds
00a7 push 0x9a7
00aa nop 
00ab push cs
00ac call 0x18be ; _Punt
00af add sp, 4
00b2 add si, 0x2c
00b5 inc di
00b6 les bx, ptr [bp - 8]
00b9 cmp word ptr es:[bx], di
00bc jg 0x6fa3
00be mov di, bx
00c0 push word ptr es:[di + 2]
00c4 mov si, es
00c6 nop 
00c7 push cs
00c8 call 0x559c ; _mem_Unlock
00cb add sp, 2
00ce mov word ptr [bp - 0x14], di
00d1 mov word ptr [bp - 0x12], si
00d4 mov es, si
00d6 mov si, word ptr es:[di]
00d9 push word ptr es:[di + 2]
00dd nop 
00de push cs
00df call 0x558e ; _mem_Lock
00e2 add sp, 2
00e5 mov word ptr [bp - 0xc], ax
00e8 mov word ptr [bp - 0xa], dx
00eb mov word ptr [bp - 4], ax
00ee mov word ptr [bp - 2], dx
00f1 mov word ptr [bp - 0x10], 0
00f6 or si, si
00f8 jg 0x7039
00fa jmp 0x70e3
00fd mov di, word ptr [bp + 8]
0100 mov ax, di
0102 mov al, ah
0104 cwde 
0105 shl ax, 1
0107 add ax, 0xbca6
010a mov word ptr [bp - 0x1e], ax
010d mov word ptr [bp - 6], si
0110 mov word ptr [bp - 0xe], si
0113 mov si, word ptr [bp - 4]
0116 mov es, word ptr [bp - 2]
0119 cmp word ptr es:[si + 6], -1
011e je 0x70d5
0120 push word ptr es:[si + 0xc]
0124 push word ptr es:[si + 0xa]
0128 push word ptr es:[si + 0x2a]
012c push word ptr es:[si + 0x28]
0130 push word ptr [bp + 0x14]
0133 push word ptr [bp + 0x12]
0136 push word ptr [bp + 0x10]
0139 push word ptr [bp + 0xe]
013c push word ptr es:[si + 8]
0140 push word ptr es:[si + 6]
0144 nop 
0145 push cs
0146 call 0x7536 ; _gr_PutToBuf
0149 add sp, 0x14
014c mov bx, word ptr [bp - 0x1e]
014f cmp word ptr [bx], 0
0152 je 0x70d5
0154 mov es, word ptr [bp - 2]
0157 mov ax, word ptr es:[si + 6]
015b add ax, word ptr [bp + 0xa]
015e sub ax, 2
0161 mov word ptr [bp - 0x1c], ax
0164 mov ax, word ptr es:[si + 0xa]
0168 add ax, word ptr [bp - 0x1c]
016b add ax, 8
016e mov word ptr [bp - 0x18], ax
0171 mov ax, word ptr es:[si + 8]
0175 add ax, word ptr [bp + 0xc]
0178 sub ax, 2
017b mov word ptr [bp - 0x1a], ax
017e mov ax, word ptr es:[si + 0xc]
0182 add ax, word ptr [bp - 0x1a]
0185 add ax, 4
0188 mov word ptr [bp - 0x16], ax
018b push word ptr [bx]
018d lea ax, [bp - 0x1c]
0190 push ss
0191 push ax
0192 push 0
0194 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 405, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
0199 add si, 0x2c
019c dec word ptr [bp - 6]
019f je 0x70e0
01a1 jmp 0x7052
01a4 mov si, word ptr [bp - 0xe]
01a7 mov ax, word ptr [bp - 0xc]
01aa mov dx, word ptr [bp - 0xa]
01ad mov cx, ax
01af mov word ptr [bp - 2], dx
01b2 mov word ptr [bp - 0x10], 0
01b7 or si, si
01b9 jle 0x7169
01bb mov di, si
01bd mov word ptr [bp - 4], cx
01c0 mov word ptr [bp - 0xe], si
01c3 mov si, ax
01c5 mov es, word ptr [bp - 2]
01c8 cmp byte ptr es:[si], 0
01cc je 0x7160
01ce cmp byte ptr es:[si + 3], 0
01d3 je 0x7160
01d5 push word ptr es:[si + 0x1c]
01d9 push word ptr es:[si + 0x1a]
01dd push word ptr es:[si + 0x2a]
01e1 push word ptr es:[si + 0x28]
01e5 push word ptr [bp + 0x14]
01e8 push word ptr [bp + 0x12]
01eb push word ptr [bp + 0x10]
01ee push word ptr [bp + 0xe]
01f1 push word ptr es:[si + 0x18]
01f5 push word ptr es:[si + 0x16]
01f9 nop 
01fa push cs
01fb call 0x73e0 ; _gr_GetFromBuf
01fe add sp, 0x14
0201 mov es, word ptr [bp - 2]
0204 mov ax, word ptr es:[si + 0x16]
0208 mov word ptr es:[si + 6], ax
020c mov ax, word ptr es:[si + 0x18]
0210 mov word ptr es:[si + 8], ax
0214 mov ax, word ptr es:[si + 0x1a]
0218 mov word ptr es:[si + 0xa], ax
021c mov ax, word ptr es:[si + 0x1c]
0220 mov word ptr es:[si + 0xc], ax
0224 add si, 0x2c
0227 dec di
0228 jne 0x7101
022a mov si, word ptr [bp - 0xe]
022d mov ax, word ptr [bp - 0xc]
0230 mov dx, word ptr [bp - 0xa]
0233 mov word ptr [bp - 4], ax
0236 mov word ptr [bp - 2], dx
0239 mov word ptr [bp - 0x10], 0
023e or si, si
0240 jg 0x7181
0242 jmp 0x7324
0245 mov al, byte ptr [bp + 9]
0248 cwde 
0249 shl ax, 1
024b add ax, 0xbca6
024e mov word ptr [bp - 0x1e], ax
0251 mov word ptr [bp - 6], si
0254 mov word ptr [bp - 0xe], si
0257 mov si, word ptr [bp - 4]
025a mov di, word ptr [bp + 0x14]
025d mov es, word ptr [bp - 2]
0260 mov al, byte ptr es:[si + 1]
0264 mov byte ptr es:[si + 2], al
0268 cmp byte ptr es:[si], 0
026c jne 0x71ad
026e jmp 0x7314
0271 cmp byte ptr es:[si + 3], 0
0276 jne 0x71b7
0278 jmp 0x7319
027b cmp word ptr es:[si + 0x26], 0x7530
0281 jge 0x71c2
0283 jmp 0x7292
0286 mov es, word ptr [0xbf74]
028a les bx, ptr es:[0xa072]
028f mov word ptr [bp - 0x22], bx
0292 mov word ptr [bp - 0x20], es
0295 mov ax, word ptr es:[bx + 0xa]
0299 mov word ptr [bp - 8], ax
029c mov ax, word ptr es:[bx + 8]
02a0 mov word ptr [bp - 0xa], ax
02a3 test byte ptr [0xcc7e], 1 ; _displayType
02a8 jne 0x725c
02aa test byte ptr es:[bx + 2], 0x80
02af jne 0x7226
02b1 mov ax, di
02b3 mov es, word ptr [bp - 2]
02b6 sub ax, word ptr es:[si + 0x18]
02ba sub ax, word ptr [bp - 8]
02bd push ax
02be push word ptr es:[si + 0x16]
02c2 push word ptr [bp - 0xa]
02c5 push word ptr [bp - 8]
02c8 push word ptr [bp + 0x12]
02cb push di
02cc mov ax, bx
02ce mov dx, word ptr [bp - 0x20]
02d1 add ax, 0xc
02d4 adc dx, 0
02d7 push dx
02d8 push ax
02d9 push word ptr [bp + 0x10]
02dc push word ptr [bp + 0xe]
02df nop 
02e0 push cs
02e1 call 0x1f04 ; _ConvertMaskBitmap2
02e4 add sp, 0x14
02e7 jmp 0x72bd
02ea mov ax, di
02ec mov es, word ptr [bp - 2]
02ef sub ax, word ptr es:[si + 0x18]
02f3 sub ax, word ptr [bp - 8]
02f6 push ax
02f7 push word ptr es:[si + 0x16]
02fb push word ptr [bp - 0xa]
02fe push word ptr [bp - 8]
0301 push word ptr [bp + 0x12]
0304 push di
0305 mov ax, word ptr [bp - 0x22]
0308 mov dx, word ptr [bp - 0x20]
030b add ax, 0xc
030e adc dx, 0
0311 push dx
0312 push ax
0313 push word ptr [bp + 0x10]
0316 push word ptr [bp + 0xe]
0319 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 796, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _CopyMaskBitmap2
031e jmp 0x7220
0320 mov ax, di
0322 mov es, word ptr [bp - 2]
0325 sub ax, word ptr es:[si + 0x18]
0329 sub ax, word ptr [bp - 8]
032c push ax
032d push word ptr es:[si + 0x16]
0331 push word ptr [bp - 0xa]
0334 push word ptr [bp - 8]
0337 push word ptr [bp + 0x12]
033a push di
033b mov ax, word ptr [bp - 0x22]
033e mov dx, word ptr [bp - 0x20]
0341 add ax, 0xc
0344 adc dx, 0
0347 push dx
0348 push ax
0349 push word ptr [bp + 0x10]
034c push word ptr [bp + 0xe]
034f nop 
0350 push cs
0351 call 0x2ed4 ; _CopyMonoMaskBitmap
0354 jmp 0x7220
0356 lea ax, [bp - 0xa]
0359 push ss
035a push ax
035b lea ax, [bp - 8]
035e push ss
035f push ax
0360 mov es, word ptr [bp - 2]
0363 push word ptr es:[si + 0x26]
0367 push word ptr [bp + 0x12]
036a push di
036b push word ptr es:[si + 0x18]
036f push word ptr es:[si + 0x16]
0373 push word ptr [bp + 0x10]
0376 push word ptr [bp + 0xe]
0379 nop 
037a push cs
037b call 0x418e ; _DrawBitMapToBuffer
037e add sp, 0x16
0381 mov bx, word ptr [bp - 0x1e]
0384 cmp word ptr [bx], 0
0387 je 0x730a
0389 mov es, word ptr [bp - 2]
038c mov ax, word ptr es:[si + 0x16]
0390 add ax, word ptr [bp + 0xa]
0393 sub ax, 2
0396 mov word ptr [bp - 0x1c], ax
0399 mov ax, word ptr es:[si + 0x1a]
039d add ax, word ptr [bp - 0x1c]
03a0 add ax, 8
03a3 mov word ptr [bp - 0x18], ax
03a6 mov ax, word ptr es:[si + 0x18]
03aa add ax, word ptr [bp + 0xc]
03ad sub ax, 2
03b0 mov word ptr [bp - 0x1a], ax
03b3 mov ax, word ptr es:[si + 0x1c]
03b7 add ax, word ptr [bp - 0x1a]
03ba add ax, 4
03bd mov word ptr [bp - 0x16], ax
03c0 push word ptr [bx]
03c2 lea ax, [bp - 0x1c]
03c5 push ss
03c6 push ax
03c7 push 0
03c9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 970, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 125}}]
03ce mov es, word ptr [bp - 2]
03d1 mov byte ptr es:[si + 1], 1
03d6 jmp 0x7319
03d8 mov byte ptr es:[si + 1], 0
03dd add si, 0x2c
03e0 dec word ptr [bp - 6]
03e3 je 0x7324
03e5 jmp 0x7199
03e8 mov bx, word ptr [bp + 8]
03eb sar bx, 8
03ee shl bx, 1
03f0 cmp word ptr [bx - 0x435a], 0
03f5 je 0x7344
03f7 mov bx, word ptr [bp + 8]
03fa sar bx, 8
03fd shl bx, 1
03ff push word ptr [bx - 0x435a]
0403 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1028, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 124}}]
0408 les bx, ptr [bp - 0x14]
040b push word ptr es:[bx + 2]
040f nop 
0410 push cs
0411 call 0x559c ; _mem_Unlock
0414 add sp, 2
0417 push word ptr [bp + 6]
041a nop 
041b push cs
041c call 0x558e ; _mem_Lock
041f add sp, 2
0422 mov es, dx
0424 mov bx, ax
0426 mov di, ax
0428 mov word ptr [bp - 4], es
042b push word ptr es:[bx + 2]
042f nop 
0430 push cs
0431 call 0x558e ; _mem_Lock
0434 add sp, 2
0437 mov si, ax
0439 mov word ptr [bp - 8], dx
043c mov word ptr [bp - 2], 0
0441 mov es, word ptr [bp - 4]
0444 cmp word ptr es:[di], 0
0448 jle 0x73a9
044a mov word ptr [bp - 6], di
044d mov di, word ptr [bp - 2]
0450 mov es, word ptr [bp - 8]
0453 push word ptr es:[si + 0x22]
0457 nop 
0458 push cs
0459 call 0x559c ; _mem_Unlock
045c add sp, 2
045f add si, 0x2c
0462 inc di
0463 les bx, ptr [bp - 6]
0466 cmp word ptr es:[bx], di
0469 jg 0x738c
046b mov di, bx
046d push word ptr es:[di + 2]
0471 nop 
0472 push cs
0473 call 0x559c ; _mem_Unlock
0476 add sp, 2
0479 push word ptr [bp + 6]
047c nop 
047d push cs
047e call 0x559c ; _mem_Unlock
0481 add sp, 2
0484 push word ptr [bp + 6]
0487 nop 
0488 push cs
0489 call 0x559c ; _mem_Unlock
048c add sp, 2
048f push word ptr [bp + 6]
0492 nop 
0493 push cs
0494 call 0x680c ; _hanim_ActuallyRemoveAnimObjects
0497 add sp, 2
049a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1181, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; PROFSTOP
049f pop si
04a0 pop di
04a1 leave 
04a2 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
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

- {'callee_names': ['_Punt'], 'segment': 2, 'target_offset': 6334, 'caller_offsets': [172]}
- {'callee_names': ['_ConvertMaskBitmap2'], 'segment': 2, 'target_offset': 7940, 'caller_offsets': [737]}
- {'callee_names': ['_CopyMonoMaskBitmap'], 'segment': 2, 'target_offset': 11988, 'caller_offsets': [849]}
- {'callee_names': ['_DrawBitMapToBuffer'], 'segment': 2, 'target_offset': 16782, 'caller_offsets': [891]}
- {'callee_names': ['_mem_Alloc'], 'segment': 2, 'target_offset': 21722, 'caller_offsets': [31]}
- {'callee_names': ['_mem_Free'], 'segment': 2, 'target_offset': 21888, 'caller_offsets': [40]}
- {'callee_names': ['_mem_Lock'], 'segment': 2, 'target_offset': 21902, 'caller_offsets': [51, 72, 112, 223, 1052, 1073]}
- {'callee_names': ['_mem_Unlock'], 'segment': 2, 'target_offset': 21916, 'caller_offsets': [200, 1041, 1113, 1139, 1150, 1161]}
- {'callee_names': ['_mem_Size'], 'segment': 2, 'target_offset': 21930, 'caller_offsets': [135]}
- {'callee_names': ['_hanim_ActuallyRemoveAnimObjects'], 'segment': 2, 'target_offset': 26636, 'caller_offsets': [1172]}
- {'callee_names': ['_gr_GetFromBuf'], 'segment': 2, 'target_offset': 29664, 'caller_offsets': [507]}
- {'callee_names': ['_gr_PutToBuf'], 'segment': 2, 'target_offset': 30006, 'caller_offsets': [326]}

## Neighbors

- {'symbol': '_hanim_MakeAnimSet', 'offset': 28218, 'source': 'src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c', 'size': 111}
- {'symbol': '_hanim_RemoveAnimSet', 'offset': 28330, 'source': 'src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c', 'size': 146}
- {'symbol': '_gr_GetFromBuf', 'offset': 29664, 'source': None, 'size': 342}
- {'symbol': '_gr_PutToBuf', 'offset': 30006, 'source': None, 'size': 342}
