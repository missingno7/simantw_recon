# Recovery task _hanim_RemoveAnimObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 260 bytes.

```asm
0000 enter 0x110, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0x558e ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov di, ax
0017 mov word ptr [bp - 0xc], es
001a push word ptr es:[bx + 2]
001e nop 
001f push cs
0020 call 0x558e ; _mem_Lock
0023 add sp, 2
0026 mov si, ax
0028 mov word ptr [bp - 8], dx
002b mov ax, dx
002d mov word ptr [bp - 4], si
0030 mov word ptr [bp - 2], ax
0033 mov word ptr [bp - 6], 0
0038 mov es, word ptr [bp - 0xc]
003b cmp word ptr es:[di], 0
003f jle 0x66f9
0041 mov cx, word ptr [bp - 6]
0044 mov word ptr [bp - 0xe], di
0047 mov ds, word ptr [bp - 0xc]
004a mov es, dx
004c mov ax, word ptr [bp + 8]
004f cmp word ptr es:[si + 0x20], ax
0053 je 0x673a
0055 add si, 0x2c
0058 inc cx
0059 cmp word ptr [di], cx
005b jg 0x66e6
005d push ss
005e pop ds
005f xor ax, ax
0061 cdq 
0062 mov si, ax
0064 mov es, dx
0066 mov ax, es
0068 or ax, si
006a jne 0x674c
006c push word ptr [bp + 8]
006f push word ptr [bp + 0xc]
0072 push word ptr [bp + 0xa]
0075 push ds
0076 push 0xa15
0079 lea ax, [bp - 0x110]
007d push ss
007e push ax
007f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 130, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _sprintf
0084 add sp, 0xe
0087 push word ptr [0xcd78] ; _rootWnd
008b lea ax, [bp - 0x110]
008f push ss
0090 push ax
0091 push ds
0092 push 0xa45
0095 push 0x1010
0098 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 153, 'type': 3, 'target': {'kind': 'import', 'module': 'USER', 'ordinal': 1}}]
009d jmp 0x6780
009f nop 
00a0 mov word ptr [bp - 4], si
00a3 push ss
00a4 pop ds
00a5 mov word ptr [bp - 0x10], cx
00a8 mov ax, word ptr [bp - 2]
00ab mov es, ax
00ad mov di, word ptr [bp - 0xe]
00b0 jmp 0x6700
00b2 mov word ptr [bp - 8], es
00b5 mov byte ptr es:[si + 5], 1
00ba mov byte ptr es:[si], 0
00be mov ax, word ptr [bp - 0x10]
00c1 mov es, word ptr [bp - 0xc]
00c4 cmp word ptr es:[di], ax
00c7 jle 0x6780
00c9 mov word ptr [bp - 0xe], di
00cc mov ds, word ptr [bp - 0xc]
00cf mov es, word ptr [bp - 8]
00d2 mov byte ptr es:[si + 3], 1
00d7 inc word ptr [bp - 0x10]
00da add si, 0x2c
00dd mov ax, word ptr [bp - 0x10]
00e0 cmp word ptr [di], ax
00e2 jg 0x676c
00e4 push ss
00e5 pop ds
00e6 mov es, word ptr [bp - 0xc]
00e9 push word ptr es:[di + 2]
00ed nop 
00ee push cs
00ef call 0x559c ; _mem_Unlock
00f2 add sp, 2
00f5 push word ptr [bp + 6]
00f8 nop 
00f9 push cs
00fa call 0x559c ; _mem_Unlock
00fd add sp, 2
0100 pop si
0101 pop di
0102 leave 
0103 retf 
```

## Known declaration examples

- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
- `extern int near rootWnd;` — src/recovered/DoWinHelp.c
- `extern int near rootWnd;` — src/recovered/Error.c
- `extern int near rootWnd;` — src/recovered/PopMsg.c
- `extern int far sprintf(char far *buffer, char far *format, ...);` — src/recovered/db_Exists.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '__hanim_FindObject', 'offset': 25546, 'source': 'src/recovered/wf_hanim_FindObject-9334905165.c', 'size': 69}
- {'symbol': '_hanim_AddAnimObject', 'offset': 25616, 'source': None, 'size': 650}
- {'symbol': '_hanim_RemoveAllAnimObjects', 'offset': 26526, 'source': None, 'size': 109}
- {'symbol': '_hanim_ActuallyRemoveAnimObjects', 'offset': 26636, 'source': None, 'size': 248}
