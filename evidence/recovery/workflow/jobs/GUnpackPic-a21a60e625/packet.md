# Recovery task _GUnpackPic

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 186 bytes.

```asm
0000 enter 0xa, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xa]
0009 mov si, word ptr [bp + 0xe]
000c push ds
000d push 0xbac4
0010 push 1
0012 push si
0013 nop 
0014 push cs
0015 call 0x558e ; _mem_Lock
0018 add sp, 2
001b mov es, dx
001d mov bx, ax
001f push 0
0021 push word ptr es:[bx + 2]
0025 mov word ptr [bp - 8], bx
0028 mov word ptr [bp - 6], es
002b nop 
002c push cs
002d call 0x54da ; _mem_Alloc
0030 add sp, 0xa
0033 mov es, word ptr [bp + 0xc]
0036 mov word ptr es:[di], ax
0039 push ax
003a nop 
003b push cs
003c call 0x558e ; _mem_Lock
003f add sp, 2
0042 mov word ptr [bp - 4], ax
0045 mov word ptr [bp - 2], dx
0048 les bx, ptr [bp - 8]
004b push word ptr es:[bx + 2]
004f mov ax, es
0051 add bx, 4
0054 adc ax, 0
0057 push ax
0058 push bx
0059 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 92, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _UnpackInit
005e add sp, 6
0061 push 0xc
0063 push word ptr [bp + 8]
0066 push word ptr [bp + 6]
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Unpack
006e add sp, 6
0071 les bx, ptr [bp - 8]
0074 mov ax, word ptr es:[bx + 2]
0078 mov cx, ax
007a sub ax, 0x10
007d push ax
007e push word ptr [bp - 2]
0081 push word ptr [bp - 4]
0084 mov word ptr [bp - 0xa], cx
0087 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 138, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _Unpack
008c add sp, 6
008f push ax
0090 push word ptr [bp - 0xa]
0093 push ds
0094 push 0xbac8
0097 nop 
0098 push cs
0099 call 0x62bc ; _WinPrintf
009c add sp, 8
009f push si
00a0 nop 
00a1 push cs
00a2 call 0x559c ; _mem_Unlock
00a5 add sp, 2
00a8 mov es, word ptr [bp + 0xc]
00ab push word ptr es:[di]
00ae nop 
00af push cs
00b0 call 0x559c ; _mem_Unlock
00b3 add sp, 2
00b6 pop si
00b7 pop di
00b8 leave 
00b9 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenCasteWindow-3d435baaee.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_OpenModeWindow-b97cc714f9.c
- `extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RedrawScreen', 'offset': 16440, 'source': 'src/recovered/RedrawScreen.c', 'size': 25}
- {'symbol': '_GBoxMove', 'offset': 16466, 'source': 'src/recovered/wf_GBoxMove-31918745e5.c', 'size': 129}
- {'symbol': '_DrawBitMapToBuffer', 'offset': 16782, 'source': None, 'size': 1004}
- {'symbol': '_MySetCapture', 'offset': 17786, 'source': None, 'size': 88}
