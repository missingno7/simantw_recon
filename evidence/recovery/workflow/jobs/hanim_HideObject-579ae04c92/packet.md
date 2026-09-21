# Recovery task _hanim_HideObject

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 179 bytes.

```asm
0000 enter 0x10, 0
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
0017 mov word ptr [bp - 0xe], bx
001a mov word ptr [bp - 0xc], es
001d push word ptr es:[bx + 2]
0021 nop 
0022 push cs
0023 call 0x558e ; _mem_Lock
0026 add sp, 2
0029 mov si, ax
002b mov word ptr [bp - 8], dx
002e mov ax, dx
0030 mov word ptr [bp - 2], ax
0033 mov word ptr [bp - 6], 0
0038 les bx, ptr [bp - 0xe]
003b cmp word ptr es:[bx], 0
003f jle 0x6976
0041 mov bx, si
0043 mov cx, word ptr [bp - 6]
0046 mov word ptr [bp - 0xe], di
0049 mov ds, word ptr [bp - 0xc]
004c mov es, dx
004e mov ax, word ptr [bp + 8]
0051 cmp word ptr es:[bx + 0x20], ax
0055 je 0x6968
0057 add bx, 0x2c
005a inc cx
005b cmp word ptr [di], cx
005d jg 0x6952
005f push ss
0060 pop ds
0061 jmp 0x6976
0063 nop 
0064 push ss
0065 pop ds
0066 mov ax, word ptr [bp - 2]
0069 mov word ptr [bp - 0xa], bx
006c mov word ptr [bp - 8], ax
006f jmp 0x697e
0071 nop 
0072 sub ax, ax
0074 mov word ptr [bp - 8], ax
0077 mov word ptr [bp - 0xa], ax
007a mov ax, word ptr [bp - 8]
007d or ax, word ptr [bp - 0xa]
0080 jne 0x6992
0082 push ds
0083 push 0xa5b
0086 nop 
0087 push cs
0088 call 0x18be ; _Punt
008b add sp, 4
008e les bx, ptr [bp - 0xa]
0091 mov byte ptr es:[bx], 0
0095 les bx, ptr [bp - 0xe]
0098 push word ptr es:[bx + 2]
009c nop 
009d push cs
009e call 0x559c ; _mem_Unlock
00a1 add sp, 2
00a4 push word ptr [bp + 6]
00a7 nop 
00a8 push cs
00a9 call 0x559c ; _mem_Unlock
00ac add sp, 2
00af pop si
00b0 pop di
00b1 leave 
00b2 retf 
```

## Known declaration examples

- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeHandle.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_PurgeObject.c
- `extern void far Punt(char far *message, ...);` — src/recovered/db_ReleaseObject.c
- `extern void far *mem_Lock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c
- `extern int far mem_Unlock(unsigned int handle);` — src/recovered/wf_hanim_MakeAnimSet-ff5bff9d29.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_hanim_RemoveAllAnimObjects', 'offset': 26526, 'source': None, 'size': 109}
- {'symbol': '_hanim_ActuallyRemoveAnimObjects', 'offset': 26636, 'source': None, 'size': 248}
- {'symbol': '_hanim_ShowObject', 'offset': 27064, 'source': None, 'size': 179}
- {'symbol': '_hanim_SetObjectPos', 'offset': 27244, 'source': None, 'size': 974}
