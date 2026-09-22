# Recovery task _win_LoadAllWindows

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 552 bytes.

```asm
0000 enter 0xe, 0
0004 push di
0005 push si
0006 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 7, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 286}}]
000b push ax
000c lea ax, [bp - 0xe]
000f push ss
0010 push ax
0011 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 18, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 32}}]
0016 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 25, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _font_InitFonts
001b nop 
001c push cs
001d call 0xe39e ; _win_LockInit
0020 xor ax, ax
0022 mov es, word ptr [0xc6cc]
0026 mov cx, 0xb4
0029 mov di, 0x77b2
002c rep stosb byte ptr es:[di], al
002e mov word ptr [bp - 2], 0x7f02
0033 mov es, word ptr [0xc6ce]
0037 mov bx, word ptr [bp - 2]
003a mov di, bx
003c mov si, 0xbd54
003f movsw word ptr es:[di], word ptr [si]
0040 movsw word ptr es:[di], word ptr [si]
0041 movsw word ptr es:[di], word ptr [si]
0042 movsw word ptr es:[di], word ptr [si]
0043 add word ptr [bp - 2], 8
0047 cmp word ptr [bp - 2], 0x806a
004c jb 0xc83d
004e mov al, byte ptr [0xcc7e] ; _displayType
0051 cwde 
0052 sub ax, 9
0055 je 0xc86c
0057 dec ax
0058 je 0xc884
005a push 0
005c push 9
005e mov al, byte ptr [0xcc7e] ; _displayType
0061 cwde 
0062 push ax
0063 jmp 0xc89a
0065 nop 
0066 cmp word ptr [bp - 8], 0x1e0
006b jle 0xc87c
006d push 0
006f push 9
0071 push 7
0073 jmp 0xc89a
0075 nop 
0076 push 0
0078 push 9
007a push 5
007c jmp 0xc89a
007e cmp word ptr [bp - 8], 0x1e0
0083 jle 0xc894
0085 push 0
0087 push 9
0089 push 8
008b jmp 0xc89a
008d nop 
008e push 0
0090 push 9
0092 push 0
0094 nop 
0095 push cs
0096 call 0x8292 ; _db_LoadObject
0099 add sp, 6
009c mov word ptr [bp - 2], ax
009f or ax, ax
00a1 je 0xc912
00a3 push ax
00a4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 167, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
00a9 add sp, 2
00ac mov es, word ptr [0xc6ce]
00b0 push ds
00b1 mov di, 0x7f02
00b4 mov si, ax
00b6 mov ds, dx
00b8 mov cx, 0xa0
00bb rep movsw word ptr es:[di], word ptr [si]
00bd pop ds
00be push word ptr [bp - 2]
00c1 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 196, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
00c6 add sp, 2
00c9 mov al, byte ptr [0xcc7e] ; _displayType
00cc cwde 
00cd sub ax, 9
00d0 je 0xc8e4
00d2 dec ax
00d3 je 0xc8f8
00d5 push 9
00d7 mov al, byte ptr [0xcc7e] ; _displayType
00da cwde 
00db push ax
00dc jmp 0xc90a
00de cmp word ptr [bp - 8], 0x1e0
00e3 jle 0xc8f2
00e5 push 9
00e7 push 7
00e9 jmp 0xc90a
00eb nop 
00ec push 9
00ee push 5
00f0 jmp 0xc90a
00f2 cmp word ptr [bp - 8], 0x1e0
00f7 jle 0xc906
00f9 push 9
00fb push 8
00fd jmp 0xc90a
00ff nop 
0100 push 9
0102 push 0
0104 nop 
0105 push cs
0106 call 0x834e ; _db_PurgeObject
0109 add sp, 4
010c push 0
010e push 0
0110 push 0x80
0113 nop 
0114 push cs
0115 call 0x8292 ; _db_LoadObject
0118 add sp, 6
011b mov si, ax
011d or si, si
011f jne 0xc932
0121 push ds
0122 push 0xbd5c
0125 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 296, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _Punt
012a jmp 0xc979
012c push si
012d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 304, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0132 add sp, 2
0135 mov es, dx
0137 mov bx, ax
0139 mov ax, word ptr es:[bx]
013c mov es, word ptr [0xc6d0]
0140 mov word ptr es:[0x78de], ax
0144 mov es, dx
0146 mov ax, word ptr es:[bx + 2]
014a mov es, word ptr [0xc6d2]
014e mov word ptr es:[0xa0ea], ax
0152 mov es, dx
0154 mov ax, word ptr es:[bx + 4]
0158 mov es, word ptr [0xc6d4]
015c mov word ptr es:[0x769e], ax
0160 push si
0161 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 356, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
0166 add sp, 2
0169 push 0
016b push 0x80
016e nop 
016f push cs
0170 call 0x834e ; _db_PurgeObject
0173 add sp, 4
0176 push 0
0178 push 0
017a push 0x81
017d nop 
017e push cs
017f call 0x8292 ; _db_LoadObject
0182 add sp, 6
0185 push ax
0186 mov si, ax
0188 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 395, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
018d add sp, 2
0190 mov word ptr [bp - 6], ax
0193 mov word ptr [bp - 4], dx
0196 mov es, word ptr [0xc6d2]
019a mov cx, word ptr es:[0xa0ea]
019f mov ax, cx
01a1 shl cx, 1
01a3 add cx, ax
01a5 shl cx, 1
01a7 mov es, word ptr [0xc6d6]
01ab mov ax, word ptr [bp - 6]
01ae push si
01af push ds
01b0 mov di, 0x78ec
01b3 mov si, ax
01b5 mov ds, dx
01b7 shr cx, 1
01b9 rep movsw word ptr es:[di], word ptr [si]
01bb adc cx, cx
01bd rep movsb byte ptr es:[di], byte ptr [si]
01bf pop ds
01c0 pop si
01c1 push si
01c2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 453, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
01c7 add sp, 2
01ca push 0
01cc push 0x81
01cf nop 
01d0 push cs
01d1 call 0x834e ; _db_PurgeObject
01d4 add sp, 4
01d7 mov word ptr [bp - 2], 0
01dc mov es, word ptr [0xc6d0]
01e0 cmp word ptr es:[0x78de], 0
01e6 jle 0xca27
01e8 mov word ptr [bp - 4], 0xbca6
01ed xor si, si
01ef mov di, word ptr [bp - 2]
01f2 push si
01f3 nop 
01f4 push cs
01f5 call 0xc662 ; _win_LoadWindow
01f8 add sp, 2
01fb push 0
01fd push di
01fe nop 
01ff push cs
0200 call 0x847e ; _db_UnhookObject
0203 add sp, 4
0206 mov bx, word ptr [bp - 4]
0209 add word ptr [bp - 4], 2
020d mov word ptr [bx], 0
0211 add si, 0x100
0215 inc di
0216 mov es, word ptr [0xc6d0]
021a cmp word ptr es:[0x78de], di
021f jg 0xc9f8
0221 mov ax, 1
0224 pop si
0225 pop di
0226 leave 
0227 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern void far db_PurgeObject(int object, int kind);` — src/recovered/wf_tu_simant_5530_DoWinHelp_4_scaffold-e0e0435c97.c
- `extern void far db_UnhookObject(int object, int kind);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c
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

- {'symbol': '_RepointObjects', 'offset': 50694, 'source': None, 'size': 91}
- {'symbol': '_win_LoadWindow', 'offset': 50786, 'source': None, 'size': 419}
- {'symbol': '_win_Open', 'offset': 51758, 'source': None, 'size': 1385}
- {'symbol': '_win_Close', 'offset': 53144, 'source': None, 'size': 168}
