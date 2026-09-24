# Recovery task _MakeBalloon

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 1100 bytes.

```asm
0000 enter 0x70, 0
0004 push di
0005 push si
0006 push 0x12c
0009 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 12, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _malloc
000e add sp, 2
0011 mov word ptr [bp - 0x30], ax
0014 mov word ptr [bp - 0x2e], dx
0017 mov bx, 0x1686
001a mov es, word ptr [0xc288]
001e mov word ptr [bp - 0x5c], bx
0021 mov word ptr [bp - 0x5a], es
0024 mov ax, word ptr es:[bx + 2]
0028 or ax, word ptr es:[bx]
002b jne 0x5a1d
002d push ds
002e push 0x1d1e
0031 nop 
0032 push cs
0033 call 0x18be ; _Punt
0036 add sp, 4
0039 les di, ptr [bp + 6]
003c push ds
003d lds si, ptr [bp - 0x30]
0040 mov cx, 0xffff
0043 xor ax, ax
0045 repne scasb al, byte ptr es:[di]
0047 not cx
0049 sub di, cx
004b xchg si, di
004d push ds
004e push es
004f pop ds
0050 pop es
0051 shr cx, 1
0053 rep movsw word ptr es:[di], word ptr [si]
0055 adc cx, cx
0057 rep movsb byte ptr es:[di], byte ptr [si]
0059 pop ds
005a mov ax, word ptr [bp - 0x30]
005d mov dx, word ptr [bp - 0x2e]
0060 mov word ptr [bp - 0x58], ax
0063 mov word ptr [bp - 0x56], dx
0066 xor cx, cx
0068 mov word ptr [bp - 0x2a], cx
006b mov word ptr [bp - 0x2c], cx
006e mov es, dx
0070 mov bx, ax
0072 cmp byte ptr es:[bx], cl
0075 je 0x5a9b
0077 lea di, [bp - 0x58]
007a mov bx, word ptr [bp - 0x2a]
007d mov cx, word ptr [bp - 0x2c]
0080 lea ax, [bp - 0x30]
0083 cmp di, ax
0085 jae 0x5a9b
0087 les si, ptr [bp - 0x58]
008a cmp byte ptr es:[bx + si], 0x5c
008e jne 0x5a91
0090 add si, bx
0092 cmp byte ptr es:[si + 1], 0x6e
0097 jne 0x5a91
0099 mov si, word ptr [bp - 0x58]
009c mov byte ptr es:[bx + si], 0
00a0 inc cx
00a1 inc bx
00a2 add si, bx
00a4 inc si
00a5 add di, 4
00a8 mov word ptr [di], si
00aa mov word ptr [di + 2], es
00ad inc bx
00ae mov si, word ptr [bp - 0x58]
00b1 cmp byte ptr es:[bx + si], 0
00b5 jne 0x5a64
00b7 xor di, di
00b9 mov word ptr [bp - 0x2a], di
00bc mov word ptr [bp - 0x2c], cx
00bf or cx, cx
00c1 jl 0x5ae3
00c3 mov word ptr [bp - 4], di
00c6 lea si, [bp - 0x58]
00c9 mov dx, cx
00cb inc dx
00cc mov word ptr [bp - 2], dx
00cf mov word ptr [bp - 0x2c], cx
00d2 mov di, dx
00d4 push word ptr [si + 2]
00d7 push word ptr [si]
00d9 nop 
00da push cs
00db call 0x60ce ; _font_StringWidth
00de add sp, 4
00e1 cmp ax, word ptr [bp - 4]
00e4 jle 0x5ada
00e6 push word ptr [si + 2]
00e9 push word ptr [si]
00eb nop 
00ec push cs
00ed call 0x60ce ; _font_StringWidth
00f0 add sp, 4
00f3 mov word ptr [bp - 4], ax
00f6 add si, 4
00f9 dec di
00fa jne 0x5ab8
00fc mov di, word ptr [bp - 4]
00ff push ds
0100 push 0x1d35
0103 push 1
0105 les bx, ptr [bp - 0x5c]
0108 push word ptr es:[bx + 2]
010c push word ptr es:[bx]
010f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 274, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; __font_FontHeight
0114 add sp, 4
0117 mov cx, word ptr [bp - 0x2c]
011a inc cx
011b imul cx
011d add ax, 0x10
0120 mov word ptr [bp - 0x12], ax
0123 inc ax
0124 add di, 0x10
0127 lea cx, [di + 7]
012a and cl, 0xf8
012d mov di, cx
012f imul di
0131 cdq 
0132 and dx, 3
0135 add ax, dx
0137 sar ax, 2
013a mov cx, ax
013c add ax, 0xc
013f push 0
0141 push ax
0142 mov word ptr [bp - 0x5e], cx
0145 nop 
0146 push cs
0147 call 0x54da ; _mem_Alloc
014a add sp, 0xa
014d mov word ptr [bp - 0xc], ax
0150 push ax
0151 nop 
0152 push cs
0153 call 0x558e ; _mem_Lock
0156 add sp, 2
0159 mov si, ax
015b mov word ptr [bp - 6], dx
015e push word ptr [bp - 0x5e]
0161 add ax, 8
0164 push dx
0165 push ax
0166 mov word ptr [bp - 0x62], ax
0169 mov word ptr [bp - 0x60], dx
016c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 367, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _ClearBuffer
0171 add sp, 6
0174 les bx, ptr [bp - 0x62]
0177 mov word ptr es:[bx], di
017a mov ax, word ptr [bp - 0x12]
017d mov es, word ptr [bp - 6]
0180 mov word ptr es:[si + 0xa], ax
0184 sub ax, 8
0187 mov word ptr [bp - 2], ax
018a sar di, 3
018d sub di, 2
0190 mov word ptr [bp - 0xa], di
0193 push word ptr [bp - 0x60]
0196 push bx
0197 push 0
0199 push 0
019b push ds
019c push 0x1c6e
019f mov word ptr [bp - 0x64], ax
01a2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 421, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyChar
01a7 add sp, 0xc
01aa push di
01ab push word ptr [bp - 0x60]
01ae push word ptr [bp - 0x62]
01b1 push 0
01b3 push 1
01b5 push ds
01b6 push 0x1c8e
01b9 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 444, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyCharRep
01be add sp, 0xe
01c1 push word ptr [bp - 0x60]
01c4 push word ptr [bp - 0x62]
01c7 push 0
01c9 lea ax, [di + 1]
01cc push ax
01cd push ds
01ce push 0x1c7e
01d1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 468, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyChar
01d6 add sp, 0xc
01d9 mov word ptr [bp - 0x2a], 8
01de mov word ptr [bp - 8], si
01e1 cmp word ptr [bp - 0x64], 8
01e5 jle 0x5c28
01e7 mov si, word ptr [bp - 0x2a]
01ea mov di, word ptr [bp - 8]
01ed push word ptr [bp - 0xa]
01f0 mov ax, di
01f2 mov dx, word ptr [bp - 6]
01f5 add ax, 8
01f8 push dx
01f9 push ax
01fa push si
01fb push 1
01fd push ds
01fe push 0x1cee
0201 mov word ptr [bp - 0x68], ax
0204 mov word ptr [bp - 0x66], dx
0207 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 522, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyCharRep
020c add sp, 0xe
020f push word ptr [bp - 0x66]
0212 push word ptr [bp - 0x68]
0215 push si
0216 push 0
0218 push ds
0219 push 0x1cae
021c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 543, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyChar
0221 add sp, 0xc
0224 push word ptr [bp - 0x66]
0227 push word ptr [bp - 0x68]
022a push si
022b mov ax, word ptr [bp - 0xa]
022e inc ax
022f push ax
0230 push ds
0231 push 0x1c9e
0234 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 567, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyChar
0239 add sp, 0xc
023c add si, 8
023f cmp si, word ptr [bp - 2]
0242 jl 0x5bd1
0244 xor di, di
0246 cmp word ptr [bp - 0x2c], di
0249 jl 0x5c96
024b lea si, [bp - 0x58]
024e les bx, ptr [bp - 0x5c]
0251 push word ptr es:[bx + 2]
0255 push word ptr es:[bx]
0258 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 603, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; __font_FontHeight
025d add sp, 4
0260 imul di
0262 add ax, 6
0265 push ax
0266 push 1
0268 mov ax, word ptr [bp - 8]
026b mov dx, word ptr [bp - 6]
026e add ax, 8
0271 push dx
0272 push ax
0273 les bx, ptr [bp - 0x5c]
0276 push word ptr es:[bx + 2]
027a push word ptr es:[bx]
027d push word ptr [si + 2]
0280 push word ptr [si]
0282 nop 
0283 push cs
0284 call 0x60ce ; _font_StringWidth
0287 add sp, 4
028a neg ax
028c and ax, 6
028f shr al, 1
0291 push ax
0292 push word ptr [si + 2]
0295 push word ptr [si]
0297 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 666, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _font_MakeImage
029c add sp, 0xa
029f push dx
02a0 push ax
02a1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 676, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _MoveTextToBalloon
02a6 add sp, 0xc
02a9 add si, 4
02ac inc di
02ad cmp di, word ptr [bp - 0x2c]
02b0 jle 0x5c32
02b2 mov word ptr [bp - 0x2a], di
02b5 mov si, di
02b7 mov di, word ptr [bp - 8]
02ba mov ax, di
02bc mov dx, word ptr [bp - 6]
02bf add ax, 8
02c2 push dx
02c3 push ax
02c4 les bx, ptr [bp - 0x5c]
02c7 push word ptr es:[bx + 2]
02cb push word ptr es:[bx]
02ce mov word ptr [bp - 0x6c], ax
02d1 mov word ptr [bp - 0x6a], dx
02d4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 727, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; __font_FontHeight
02d9 add sp, 4
02dc imul si
02de add ax, 6
02e1 mov word ptr [bp - 2], ax
02e4 push ax
02e5 mov cx, word ptr [bp - 0xa]
02e8 inc cx
02e9 push cx
02ea push ds
02eb push 0x1cce
02ee lcall <resolved loader operand; see bindings> ; [{'operand_offset': 753, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyChar
02f3 add sp, 0xc
02f6 push word ptr [bp - 0x6a]
02f9 push word ptr [bp - 0x6c]
02fc push word ptr [bp - 2]
02ff push 0
0301 push ds
0302 push 0x1cbe
0305 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 776, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyChar
030a add sp, 0xc
030d push word ptr [bp - 0xa]
0310 push word ptr [bp - 0x6a]
0313 push word ptr [bp - 0x6c]
0316 push word ptr [bp - 2]
0319 push 1
031b push ds
031c push 0x1cde
031f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 802, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyCharRep
0324 add sp, 0xe
0327 cmp word ptr [bp + 0xa], 0
032b je 0x5d2a
032d mov ax, di
032f mov dx, word ptr [bp - 6]
0332 add ax, 8
0335 push dx
0336 push ax
0337 push word ptr [bp - 2]
033a mov ax, word ptr [bp - 0xa]
033d dec ax
033e push ax
033f push ds
0340 push 0x1cfe
0343 jmp 0x5d3d
0345 nop 
0346 mov ax, di
0348 mov dx, word ptr [bp - 6]
034b add ax, 8
034e push dx
034f push ax
0350 push word ptr [bp - 2]
0353 push 1
0355 push ds
0356 push 0x1d0e
0359 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 860, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _CopyChar
035e add sp, 0xc
0361 mov es, word ptr [bp - 6]
0364 dec word ptr es:[di + 0xa]
0368 cmp word ptr [bp - 0x2c], 1
036c jge 0x5d56
036e dec word ptr es:[di + 0xa]
0372 push word ptr [bp - 0x2e]
0375 push word ptr [bp - 0x30]
0378 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 891, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _free
037d add sp, 4
0380 mov es, word ptr [bp - 6]
0383 mov ax, word ptr es:[di + 8]
0387 cdq 
0388 and dx, 7
038b add ax, dx
038d sar ax, 3
0390 mov word ptr [bp - 4], ax
0393 cmp byte ptr [0xcc7e], 2 ; _displayType
0398 jne 0x5d81
039a jmp 0x5e16
039d cmp byte ptr [0xcc7e], 0xa ; _displayType
03a2 jne 0x5d8b
03a4 jmp 0x5e16
03a7 test byte ptr [0xcc7e], 1 ; _displayType
03ac jne 0x5daa
03ae push word ptr [bp - 0xc]
03b1 nop 
03b2 push cs
03b3 call 0x559c ; _mem_Unlock
03b6 add sp, 2
03b9 push word ptr [bp - 0xc]
03bc nop 
03bd push cs
03be call 0x5f0e ; _ConvertMonoMaskToColor
03c1 jmp 0x5e29
03c4 nop 
03c5 nop 
03c6 mov ax, di
03c8 mov dx, es
03ca add ax, 0xc
03cd mov si, ax
03cf mov word ptr [bp - 0xe], dx
03d2 mov word ptr [bp - 0x2a], 0
03d7 mov cx, word ptr [bp - 0x12]
03da or cx, cx
03dc jle 0x5df7
03de mov word ptr [bp - 2], cx
03e1 mov di, word ptr [bp - 4]
03e4 push di
03e5 mov ax, si
03e7 mov dx, word ptr [bp - 0xe]
03ea add ax, di
03ec push dx
03ed push ax
03ee push dx
03ef push si
03f0 mov word ptr [bp - 0x70], ax
03f3 mov word ptr [bp - 0x6e], dx
03f6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 1017, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _exchange
03fb add sp, 0xa
03fe mov ax, word ptr [bp - 0x70]
0401 mov dx, word ptr [bp - 0x6e]
0404 mov si, ax
0406 mov word ptr [bp - 0xe], dx
0409 add si, di
040b dec word ptr [bp - 2]
040e jne 0x5dc8
0410 mov di, word ptr [bp - 8]
0413 mov es, word ptr [bp - 6]
0416 mov word ptr es:[di], 3
041b mov byte ptr es:[di + 2], 1
0420 push word ptr [bp - 0xc]
0423 nop 
0424 push cs
0425 call 0x559c ; _mem_Unlock
0428 add sp, 2
042b mov ax, word ptr [bp - 0xc]
042e pop si
042f pop di
0430 leave 
0431 retf 
0432 push word ptr [bp - 0xc]
0435 nop 
0436 push cs
0437 call 0x559c ; _mem_Unlock
043a add sp, 2
043d push word ptr [bp - 0xc]
0440 nop 
0441 push cs
0442 call 0x5e30 ; _ConvertMonoMaskToTandy
0445 add sp, 2
0448 pop si
0449 pop di
044a leave 
044b retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern int far _font_FontHeight(unsigned int lo, unsigned int hi);` — src/recovered/font_FontHeight.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
- `extern void far font_MakeImage(char far *text, int mode, FONTARG);` — src/recovered/wf_tu_gr_611C_font_InitFonts_2_scaffold-1c4a9db378.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRect-59694d56d6.c
- `extern int far font_StringWidth(char far *string);` — src/recovered/wf_gr_CenterStrInRectClear-92445db40b.c
- `extern int far font_StringWidth(int first, int second);` — src/recovered/win_StringSize.c
- `extern void free(void far *block);` — src/recovered/mem_free_wrapper.c
- `extern void far free(void far *block);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far *malloc(unsigned int size);` — src/recovered/mem_malloc.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_DoFastMonoBitmap-4c72c58f17.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_tu_antedit_C19C_InitMapFunctions_4_scaffold-619861a01a.c
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

- {'callee_names': ['_Punt'], 'segment': 2, 'target_offset': 6334, 'caller_offsets': [51]}
- {'callee_names': ['_mem_Alloc'], 'segment': 2, 'target_offset': 21722, 'caller_offsets': [327]}
- {'callee_names': ['_mem_Lock'], 'segment': 2, 'target_offset': 21902, 'caller_offsets': [339]}
- {'callee_names': ['_mem_Unlock'], 'segment': 2, 'target_offset': 21916, 'caller_offsets': [947, 1061, 1079]}
- {'callee_names': ['_ConvertMonoMaskToTandy'], 'segment': 2, 'target_offset': 24112, 'caller_offsets': [1090]}
- {'callee_names': ['_ConvertMonoMaskToColor'], 'segment': 2, 'target_offset': 24334, 'caller_offsets': [958]}
- {'callee_names': ['_font_StringWidth'], 'segment': 2, 'target_offset': 24782, 'caller_offsets': [219, 237, 644]}

## Neighbors

- {'symbol': '_RallocMemorySoft', 'offset': 22984, 'source': 'src/recovered/RallocMemorySoft.c', 'size': 4}
- {'symbol': '_RallocFreed', 'offset': 22988, 'source': 'src/recovered/RallocFreed.c', 'size': 24}
- {'symbol': '_ConvertMonoMaskToTandy', 'offset': 24112, 'source': None, 'size': 221}
- {'symbol': '_ConvertMonoMaskToColor', 'offset': 24334, 'source': None, 'size': 379}
