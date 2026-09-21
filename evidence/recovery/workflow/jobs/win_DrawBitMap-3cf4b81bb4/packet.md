# Recovery task _win_DrawBitMap

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 214 bytes.

```asm
0000 enter 6, 0
0004 push di
0005 push si
0006 mov di, word ptr [bp + 0xa]
0009 push 0
000b push 2
000d push di
000e nop 
000f push cs
0010 call 0x8292 ; _db_LoadObject
0013 add sp, 6
0016 mov word ptr [bp - 2], ax
0019 or ax, ax
001b jne 0xbd7a
001d jmp 0xbe2a
0020 push ax
0021 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 36, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Lock
0026 add sp, 2
0029 mov es, dx
002b mov bx, ax
002d mov si, ax
002f cmp word ptr es:[bx], -1
0033 jne 0xbdbc
0035 push es
0036 push si
0037 push word ptr [bp + 8]
003a push word ptr [bp + 6]
003d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 64, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GPutPacked
0042 add sp, 8
0045 push word ptr [bp - 2]
0048 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 75, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _mem_Unlock
004d add sp, 2
0050 push 2
0052 push di
0053 nop 
0054 push cs
0055 call 0x8426 ; _db_ReleaseObject
0058 add sp, 4
005b mov ax, 1
005e pop si
005f pop di
0060 leave 
0061 retf 
0062 cmp word ptr es:[si], 0x8000
0067 je 0xbd8f
0069 cmp word ptr es:[si], 0
006d jne 0xbe14
006f mov al, byte ptr es:[si + 2]
0073 and al, 0x7f
0075 dec al
0077 jne 0xbdf2
0079 mov al, byte ptr es:[si + 2]
007d and al, 0x80
007f cmp al, 1
0081 sbb ax, ax
0083 neg ax
0085 push ax
0086 lea ax, [si + 8]
0089 push es
008a push ax
008b push word ptr [bp + 8]
008e push word ptr [bp + 6]
0091 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 148, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GPutImg
0096 jmp 0xbe0f
0098 mov al, byte ptr es:[si + 2]
009c and al, 0x80
009e cmp al, 1
00a0 sbb ax, ax
00a2 neg ax
00a4 push ax
00a5 lea ax, [si + 8]
00a8 push es
00a9 push ax
00aa push word ptr [bp + 8]
00ad push word ptr [bp + 6]
00b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 179, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _GPutPic
00b5 add sp, 0xa
00b8 jmp 0xbd9f
00ba cmp word ptr es:[si], 3
00be jne 0xbd9f
00c0 push ds
00c1 push 0xbc84
00c4 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 199, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _WinPrintf
00c9 add sp, 4
00cc jmp 0xbd9f
00cf nop 
00d0 xor ax, ax
00d2 pop si
00d3 pop di
00d4 leave 
00d5 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
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

- {'symbol': '_win_DrawWindow', 'offset': 48022, 'source': None, 'size': 256}
- {'symbol': '_win_DrawTitle', 'offset': 48280, 'source': None, 'size': 193}
- {'symbol': '_win_DrawBitMapAtObj', 'offset': 48688, 'source': 'src/recovered/wf_win_DrawBitMapAtObj-9cde99b504.c', 'size': 64}
- {'symbol': '_win_DrawBitMapAtObjNum', 'offset': 48752, 'source': 'src/recovered/wf_win_DrawBitMapAtObjNum-4dd41620af.c', 'size': 98}
