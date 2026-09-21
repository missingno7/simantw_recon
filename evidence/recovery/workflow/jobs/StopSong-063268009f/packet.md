# Recovery task _StopSong

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 272 bytes.

```asm
0000 enter 0xc, 0
0004 push si
0005 mov bx, 0x8d08
0008 mov es, word ptr [0xbf78]
000c mov word ptr [bp - 0xc], bx
000f mov word ptr [bp - 0xa], es
0012 cmp word ptr es:[bx], 0
0016 jne 0x82af
0018 jmp 0x839c
001b cmp word ptr es:[0x8d0c], 0
0021 je 0x82ba
0023 jmp 0x839c
0026 cmp word ptr es:[0x8d0a], 0
002c je 0x830e
002e push word ptr es:[bx]
0031 push ds
0032 push 0xcb6
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 54, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
003a mov word ptr [bp - 4], ax
003d mov word ptr [bp - 2], dx
0040 push ds
0041 push 0xcc5
0044 nop 
0045 push cs
0046 call 0x62bc ; _WinPrintf
0049 add sp, 4
004c mov ax, word ptr [bp - 2]
004f or ax, word ptr [bp - 4]
0052 je 0x8300
0054 mov es, word ptr [0xbf78]
0058 push word ptr es:[0x8d0e]
005d push 0x804
0060 push 0
0062 push 0
0064 lea ax, [bp - 8]
0067 push ss
0068 push ax
0069 lcall [bp - 4]
006c mov es, word ptr [0xbf78]
0070 mov word ptr es:[0x8d0e], 0
0077 pop si
0078 leave 
0079 retf 
007a les bx, ptr [bp - 0xc]
007d push word ptr es:[bx]
0080 push ds
0081 push 0xcd9
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 133, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
0089 mov word ptr [bp - 4], ax
008c mov word ptr [bp - 2], dx
008f or dx, ax
0091 je 0x833d
0093 lcall [bp - 4]
0096 mov si, ax
0098 or si, si
009a je 0x833d
009c push si
009d push ds
009e push 0xce6
00a1 nop 
00a2 push cs
00a3 call 0x62bc ; _WinPrintf
00a6 add sp, 6
00a9 les bx, ptr [bp - 0xc]
00ac push word ptr es:[bx]
00af push ds
00b0 push 0xc4f
00b3 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 180, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 50}}]
00b8 mov word ptr [bp - 4], ax
00bb mov word ptr [bp - 2], dx
00be or dx, ax
00c0 je 0x8359
00c2 lcall [bp - 4]
00c5 mov es, word ptr [0xbf78]
00c9 push word ptr es:[0x8d20]
00ce lcall <resolved loader operand; see bindings> ; [{'operand_offset': 207, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 192}}]
00d3 mov es, word ptr [0xbf78]
00d7 push word ptr es:[0x8d1c]
00dc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 221, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 112}}]
00e1 mov es, word ptr [0xbf78]
00e5 push word ptr es:[0x8d1c]
00ea lcall <resolved loader operand; see bindings> ; [{'operand_offset': 235, 'type': 3, 'target': {'kind': 'import', 'module': 'KERNEL', 'ordinal': 17}}]
00ef mov es, word ptr [0xbf78]
00f3 mov word ptr es:[0x8d1c], 0
00fa sub ax, ax
00fc mov word ptr es:[0x8d20], ax
0100 mov word ptr es:[0x8d1e], ax
0104 pop si
0105 leave 
0106 retf 
0107 nop 
0108 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 265, 'type': 3, 'target': {'kind': 'import', 'module': 'SOUND', 'ordinal': 2}}]
010d pop si
010e leave 
010f retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/MusicInit.c
- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_SysBeep', 'offset': 33418, 'source': 'src/recovered/SysBeep.c', 'size': 8}
- {'symbol': '_myBeginSoundList', 'offset': 33426, 'source': 'src/recovered/myBeginSoundList.c', 'size': 1}
- {'symbol': '_ExtractDWord', 'offset': 33700, 'source': 'src/recovered/wf_ExtractDWord-f367d1b9bc.c', 'size': 81}
- {'symbol': '_ExtractWord', 'offset': 33782, 'source': 'src/recovered/ExtractWord.c', 'size': 68}
