# Recovery task _ConvertMonoMaskToColor

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 379 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0x558e ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov si, word ptr es:[bx + 8]
0019 push ds
001a push 0x1d53
001d push 1
001f mov ax, si
0021 mov cx, si
0023 cdq 
0024 and dx, 7
0027 add ax, dx
0029 sar ax, 3
002c mov si, ax
002e mov di, word ptr es:[bx + 0xa]
0032 mov ax, di
0034 imul si
0036 mov dx, ax
0038 shl ax, 2
003b add ax, dx
003d add ax, 0xc
0040 push 0
0042 push ax
0043 mov word ptr [bp - 0x14], cx
0046 mov word ptr [bp - 0x18], bx
0049 mov word ptr [bp - 0x16], es
004c nop 
004d push cs
004e call 0x54da ; _mem_Alloc
0051 add sp, 0xa
0054 mov word ptr [bp - 0xe], ax
0057 push ax
0058 nop 
0059 push cs
005a call 0x558e ; _mem_Lock
005d add sp, 2
0060 mov es, dx
0062 mov bx, ax
0064 mov ax, word ptr [bp - 0x14]
0067 mov word ptr es:[bx + 8], ax
006b mov word ptr es:[bx + 0xa], di
006f mov byte ptr es:[bx + 2], 4
0074 mov word ptr es:[bx], 3
0079 mov cx, word ptr [bp - 0x18]
007c mov dx, word ptr [bp - 0x16]
007f add cx, 0xc
0082 mov word ptr [bp - 0xa], cx
0085 mov word ptr [bp - 8], dx
0088 lea cx, [bx + 0xc]
008b mov word ptr [bp - 4], cx
008e mov word ptr [bp - 2], es
0091 mov word ptr [bp - 6], si
0094 push di
0095 push ax
0096 push ds
0097 push 0x1d5a
009a nop 
009b push cs
009c call 0x62bc ; _WinPrintf
009f add sp, 8
00a2 or di, di
00a4 jg 0x5fb7
00a6 jmp 0x6061
00a9 mov word ptr [bp - 0xc], di
00ac mov ax, word ptr [bp - 0xa]
00af mov dx, word ptr [bp - 8]
00b2 mov cx, word ptr [bp - 6]
00b5 add ax, cx
00b7 push ds
00b8 mov si, ax
00ba mov ds, dx
00bc les di, ptr [bp - 4]
00bf shr cx, 1
00c1 rep movsw word ptr es:[di], word ptr [si]
00c3 adc cx, cx
00c5 rep movsb byte ptr es:[di], byte ptr [si]
00c7 pop ds
00c8 mov ax, word ptr [bp - 6]
00cb add word ptr [bp - 4], ax
00ce cmp byte ptr [0xcc7e], 0xa ; _displayType
00d3 je 0x5ff0
00d5 push ax
00d6 push dx
00d7 push word ptr [bp - 0xa]
00da lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _invert
00df add sp, 6
00e2 mov ax, word ptr [bp - 0xa]
00e5 mov dx, word ptr [bp - 8]
00e8 mov cx, word ptr [bp - 6]
00eb mov bx, cx
00ed push ds
00ee mov si, ax
00f0 mov ds, dx
00f2 les di, ptr [bp - 4]
00f5 shr cx, 1
00f7 rep movsw word ptr es:[di], word ptr [si]
00f9 adc cx, cx
00fb rep movsb byte ptr es:[di], byte ptr [si]
00fd pop ds
00fe add word ptr [bp - 4], bx
0101 mov cx, bx
0103 push ds
0104 mov si, ax
0106 mov ds, dx
0108 mov di, word ptr [bp - 4]
010b shr cx, 1
010d rep movsw word ptr es:[di], word ptr [si]
010f adc cx, cx
0111 rep movsb byte ptr es:[di], byte ptr [si]
0113 pop ds
0114 add word ptr [bp - 4], bx
0117 mov cx, bx
0119 push ds
011a mov si, ax
011c mov ds, dx
011e mov di, word ptr [bp - 4]
0121 shr cx, 1
0123 rep movsw word ptr es:[di], word ptr [si]
0125 adc cx, cx
0127 rep movsb byte ptr es:[di], byte ptr [si]
0129 pop ds
012a add word ptr [bp - 4], bx
012d mov cx, bx
012f push ds
0130 mov si, ax
0132 mov ds, dx
0134 mov di, word ptr [bp - 4]
0137 shr cx, 1
0139 rep movsw word ptr es:[di], word ptr [si]
013b adc cx, cx
013d rep movsb byte ptr es:[di], byte ptr [si]
013f pop ds
0140 add word ptr [bp - 4], bx
0143 add ax, bx
0145 mov word ptr [bp - 0xa], ax
0148 add word ptr [bp - 0xa], bx
014b dec word ptr [bp - 0xc]
014e je 0x6061
0150 jmp 0x5fba
0153 push word ptr [bp + 6]
0156 nop 
0157 push cs
0158 call 0x559c ; _mem_Unlock
015b add sp, 2
015e push word ptr [bp - 0xe]
0161 nop 
0162 push cs
0163 call 0x559c ; _mem_Unlock
0166 add sp, 2
0169 push word ptr [bp + 6]
016c nop 
016d push cs
016e call 0x5580 ; _mem_Free
0171 add sp, 2
0174 mov ax, word ptr [bp - 0xe]
0177 pop si
0178 pop di
0179 leave 
017a retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
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

## Neighbors

- {'symbol': '_MakeBalloon', 'offset': 23012, 'source': None, 'size': 1100}
- {'symbol': '_ConvertMonoMaskToTandy', 'offset': 24112, 'source': None, 'size': 221}
- {'symbol': '_font_CharWidth', 'offset': 24714, 'source': 'src/recovered/font_CharWidth.c', 'size': 36}
- {'symbol': '_font_FontHeight', 'offset': 24750, 'source': 'src/recovered/font_FontHeight.c', 'size': 31}
