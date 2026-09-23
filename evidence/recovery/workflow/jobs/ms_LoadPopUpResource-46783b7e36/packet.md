# Recovery task _ms_LoadPopUpResource

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 359 bytes.

```asm
0000 enter 0x18, 0
0004 push di
0005 push si
0006 push 1
0008 push 6
000a push word ptr [bp + 6]
000d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 16, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 7}}] ; _db_LoadObject
0012 add sp, 6
0015 mov word ptr [bp - 0x14], ax
0018 or ax, ax
001a jne 0x4d06
001c push word ptr [bp + 6]
001f push ds
0020 push 0xbae6
0023 nop 
0024 push cs
0025 call 0x62bc ; _WinPrintf
0028 add sp, 6
002b les bx, ptr [bp + 8]
002e xor ax, ax
0030 mov word ptr es:[bx], ax
0033 cdq 
0034 pop si
0035 pop di
0036 leave 
0037 retf 
0038 push ax
0039 nop 
003a push cs
003b call 0x558e ; _mem_Lock
003e add sp, 2
0041 mov di, ax
0043 mov word ptr [bp - 0x16], dx
0046 mov es, dx
0048 inc di
0049 mov al, byte ptr es:[di]
004c sub ah, ah
004e mov si, ax
0050 mov ax, di
0052 inc ax
0053 mov di, ax
0055 mov word ptr [bp - 6], ax
0058 mov word ptr [bp - 4], dx
005b xor ax, ax
005d mov word ptr [bp - 2], ax
0060 mov word ptr [bp - 0xc], ax
0063 mov word ptr [bp - 0x18], di
0066 cmp si, ax
0068 jle 0x4d5b
006a mov cx, si
006c mov word ptr [bp - 0x12], si
006f lds si, ptr [bp - 6]
0072 mov di, ax
0074 mov al, byte ptr [si]
0076 sub ah, ah
0078 mov dx, ax
007a add ax, 2
007d add di, ax
007f inc dx
0080 add si, dx
0082 dec cx
0083 jne 0x4d42
0085 mov word ptr [bp - 2], di
0088 mov si, word ptr [bp - 0x12]
008b push ss
008c pop ds
008d push ds
008e push 0xbafd
0091 lea ax, [si + 1]
0094 shl ax, 2
0097 add ax, word ptr [bp - 2]
009a push ax
009b nop 
009c push cs
009d call 0x54bc ; _mem_malloc
00a0 add sp, 6
00a3 mov word ptr [bp - 0x10], ax
00a6 mov word ptr [bp - 0xe], dx
00a9 mov cx, si
00ab shl cx, 2
00ae add ax, cx
00b0 add ax, 4
00b3 mov word ptr [bp - 6], ax
00b6 mov word ptr [bp - 4], dx
00b9 mov word ptr [bp - 0xc], 0
00be or si, si
00c0 jle 0x4e06
00c2 mov word ptr [bp - 0x12], si
00c5 mov ax, word ptr [bp - 0x10]
00c8 mov word ptr [bp - 0xa], ax
00cb mov ds, dx
00cd les bx, ptr [bp - 0x18]
00d0 mov al, byte ptr es:[bx]
00d3 sub ah, ah
00d5 mov word ptr [bp - 2], ax
00d8 or ax, ax
00da jne 0x4dae
00dc push ss
00dd pop ds
00de jmp 0x4e06
00e0 mov bx, word ptr [bp - 0xa]
00e3 les si, ptr [bp - 6]
00e6 mov word ptr [bx], si
00e8 mov word ptr [bx + 2], es
00eb mov byte ptr es:[si], 0x20
00ef mov ax, word ptr [bp - 0x18]
00f2 mov dx, word ptr [bp - 0x16]
00f5 inc ax
00f6 mov cx, word ptr [bp - 2]
00f9 push si
00fa push es
00fb push ds
00fc lea di, [si + 1]
00ff mov si, ax
0101 mov ds, dx
0103 shr cx, 1
0105 rep movsw word ptr es:[di], word ptr [si]
0107 adc cx, cx
0109 rep movsb byte ptr es:[di], byte ptr [si]
010b pop ds
010c pop es
010d pop si
010e add si, word ptr [bp - 2]
0111 mov byte ptr es:[si + 1], 0
0116 lea ax, [si + 2]
0119 mov word ptr [bp - 6], ax
011c mov word ptr [bp - 4], es
011f mov ax, word ptr [bp - 2]
0122 inc ax
0123 add word ptr [bp - 0x18], ax
0126 add word ptr [bp - 0xa], 4
012a mov ax, word ptr [bp - 0x12]
012d inc word ptr [bp - 0xc]
0130 cmp word ptr [bp - 0xc], ax
0133 jl 0x4d9b
0135 jmp 0x4daa
0137 nop 
0138 mov bx, word ptr [bp - 0xc]
013b shl bx, 2
013e les si, ptr [bp - 0x10]
0141 sub ax, ax
0143 mov word ptr es:[bx + si + 2], ax
0147 mov word ptr es:[bx + si], ax
014a push word ptr [bp - 0x14]
014d nop 
014e push cs
014f call 0x559c ; _mem_Unlock
0152 add sp, 2
0155 mov ax, word ptr [bp - 0xc]
0158 les bx, ptr [bp + 8]
015b mov word ptr es:[bx], ax
015e mov ax, si
0160 mov dx, word ptr [bp - 0xe]
0163 pop si
0164 pop di
0165 leave 
0166 retf 
```

## Known declaration examples

- `extern void far WinPrintf(char far *text);` — src/recovered/Quit.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/RallocInfo.c
- `extern void far WinPrintf(char far *format, ...);` — src/recovered/db_PurgeHandle.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_18_scaffold-8260025fb8.c
- `extern unsigned int far db_LoadObject(int object, int kind, int lock);` — src/recovered/wf_tu_antedit_00F4_OverlayTileSet_20_scaffold-e8caf5259e.c
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

- {'symbol': '_SetMenuOptionState', 'offset': 19564, 'source': 'src/recovered/menu_state_tu.c', 'size': 50}
- {'symbol': '_SetMenuOptionText', 'offset': 19614, 'source': 'src/recovered/SetMenuOptionText.c', 'size': 48}
- {'symbol': '_InitMenu', 'offset': 20022, 'source': None, 'size': 790}
- {'symbol': '_ms_PopUpMenuResource', 'offset': 20812, 'source': None, 'size': 320}
