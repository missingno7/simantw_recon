# Recovery task _hanim_ActuallyRemoveAnimObjects

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 248 bytes.

```asm
0000 enter 0x12, 0
0004 push di
0005 push si
0006 push word ptr [bp + 6]
0009 nop 
000a push cs
000b call 0x558e ; _mem_Lock
000e add sp, 2
0011 mov es, dx
0013 mov bx, ax
0015 mov si, ax
0017 mov word ptr [bp - 0x10], es
001a push word ptr es:[bx + 2]
001e nop 
001f push cs
0020 call 0x558e ; _mem_Lock
0023 add sp, 2
0026 mov di, ax
0028 mov word ptr [bp - 2], dx
002b mov es, word ptr [bp - 0x10]
002e mov ax, word ptr es:[si]
0031 mov word ptr [bp - 0xc], ax
0034 imul cx, ax, 0x2c
0037 add cx, di
0039 sub cx, 0x2c
003c mov word ptr [bp - 0xa], cx
003f mov word ptr [bp - 8], dx
0042 dec ax
0043 mov word ptr [bp - 6], ax
0046 or ax, ax
0048 jl 0x685c
004a mov word ptr [bp - 0x12], si
004d jmp 0x6862
004f nop 
0050 mov di, word ptr [bp - 0xc]
0053 jmp 0x68e3
0056 mov di, word ptr [bp - 0xc]
0059 mov si, cx
005b mov es, word ptr [bp - 8]
005e cmp byte ptr es:[si + 5], 0
0063 je 0x68d8
0065 push word ptr es:[si + 0x22]
0069 nop 
006a push cs
006b call 0x5580 ; _mem_Free
006e add sp, 2
0071 dec di
0072 cmp di, word ptr [bp - 6]
0075 je 0x68d8
0077 mov ax, di
0079 sub ax, word ptr [bp - 6]
007c imul ax, ax, 0x2c
007f push ax
0080 mov ax, si
0082 mov dx, word ptr [bp - 8]
0085 add ax, 0x2c
0088 push dx
0089 push ax
008a push dx
008b push si
008c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 143, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _memmove
0091 add sp, 0xa
0094 mov ax, word ptr [bp - 8]
0097 mov word ptr [bp - 2], ax
009a mov ax, word ptr [bp - 6]
009d cmp ax, di
009f jge 0x68ce
00a1 mov word ptr [bp - 0xa], si
00a4 mov cx, di
00a6 sub cx, ax
00a8 mov bx, si
00aa mov word ptr [bp - 0xc], di
00ad mov ds, word ptr [bp - 2]
00b0 mov byte ptr [bx + 3], 1
00b4 add bx, 0x2c
00b7 dec cx
00b8 jne 0x68bc
00ba mov si, word ptr [bp - 0xa]
00bd mov di, word ptr [bp - 0xc]
00c0 push ss
00c1 pop ds
00c2 mov ax, si
00c4 mov dx, word ptr [bp - 8]
00c7 add ax, 0x2c
00ca mov si, ax
00cc sub si, 0x2c
00cf dec word ptr [bp - 6]
00d2 jns 0x6867
00d4 mov si, word ptr [bp - 0x12]
00d7 mov es, word ptr [bp - 0x10]
00da mov word ptr es:[si], di
00dd push word ptr es:[si + 2]
00e1 nop 
00e2 push cs
00e3 call 0x559c ; _mem_Unlock
00e6 add sp, 2
00e9 push word ptr [bp + 6]
00ec nop 
00ed push cs
00ee call 0x559c ; _mem_Unlock
00f1 add sp, 2
00f4 pop si
00f5 pop di
00f6 leave 
00f7 retf 
```

## Known declaration examples

- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeHandle.c
- `extern void far mem_Free(int handle);` — src/recovered/db_PurgeObject.c
- `extern void far mem_Free(int handle);` — src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c
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

- {'symbol': '_hanim_RemoveAnimObject', 'offset': 26266, 'source': None, 'size': 260}
- {'symbol': '_hanim_RemoveAllAnimObjects', 'offset': 26526, 'source': None, 'size': 109}
- {'symbol': '_hanim_HideObject', 'offset': 26884, 'source': None, 'size': 179}
- {'symbol': '_hanim_ShowObject', 'offset': 27064, 'source': None, 'size': 179}
