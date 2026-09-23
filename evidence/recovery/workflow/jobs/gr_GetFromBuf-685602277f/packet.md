# Recovery task _gr_GetFromBuf

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 342 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 test byte ptr [0xcc7e], 1 ; _displayType
000b je 0x73f0
000d jmp 0x7492
0010 mov ax, word ptr [bp + 0xe]
0013 shl ax, 2
0016 add ax, 0x1f
0019 cdq 
001a and dx, 0x1f
001d add ax, dx
001f sar ax, 5
0022 mov bx, ax
0024 shl bx, 2
0027 mov ax, word ptr [bp + 0x16]
002a inc ax
002b cdq 
002c sub ax, dx
002e sar ax, 1
0030 mov di, ax
0032 add di, 3
0035 mov word ptr [bp - 0x10], 0
003a cmp word ptr [bp + 0x18], 0
003e jg 0x7423
0040 jmp 0x7532
0043 mov ax, word ptr [bp + 0x10]
0046 sub ax, word ptr [bp + 8]
0049 dec ax
004a imul bx
004c mov cx, word ptr [bp + 6]
004f sar cx, 1
0051 add ax, cx
0053 add ax, word ptr [bp + 0xa]
0056 mov dx, word ptr [bp + 0xc]
0059 mov word ptr [bp - 6], ax
005c mov word ptr [bp - 4], dx
005f mov ax, word ptr [bp + 0x12]
0062 mov dx, word ptr [bp + 0x14]
0065 mov word ptr [bp - 0xa], ax
0068 mov word ptr [bp - 8], dx
006b mov ax, word ptr [bp + 0x18]
006e mov word ptr [bp - 0xc], ax
0071 mov word ptr [bp - 2], di
0074 mov word ptr [bp - 0xe], bx
0077 cmp word ptr [bp - 2], 0
007b jle 0x747d
007d mov ax, word ptr [bp - 0xa]
0080 mov dx, word ptr [bp - 8]
0083 mov bx, word ptr [bp - 6]
0086 mov si, word ptr [bp - 4]
0089 mov cx, word ptr [bp - 2]
008c shr cx, 1
008e push ds
008f push si
0090 mov di, ax
0092 mov si, bx
0094 mov es, dx
0096 pop ds
0097 rep movsw word ptr es:[di], word ptr [si]
0099 jae 0x747c
009b movsb byte ptr es:[di], byte ptr [si]
009c pop ds
009d mov ax, word ptr [bp - 0xe]
00a0 sub word ptr [bp - 6], ax
00a3 mov ax, word ptr [bp - 2]
00a6 add word ptr [bp - 0xa], ax
00a9 dec word ptr [bp - 0xc]
00ac jne 0x7457
00ae pop si
00af pop di
00b0 leave 
00b1 retf 
00b2 mov ax, word ptr [bp + 0xe]
00b5 add ax, 0x1f
00b8 cdq 
00b9 and dx, 0x1f
00bc add ax, dx
00be sar ax, 5
00c1 mov bx, ax
00c3 shl bx, 2
00c6 mov ax, word ptr [bp + 0x16]
00c9 add ax, 7
00cc cdq 
00cd and dx, 7
00d0 add ax, dx
00d2 sar ax, 3
00d5 mov di, ax
00d7 cmp word ptr [bp + 0x18], 0
00db jle 0x7532
00dd mov ax, word ptr [bp + 0x10]
00e0 sub ax, word ptr [bp + 8]
00e3 dec ax
00e4 imul bx
00e6 mov cx, word ptr [bp + 6]
00e9 sar cx, 3
00ec add ax, cx
00ee add ax, word ptr [bp + 0xa]
00f1 mov dx, word ptr [bp + 0xc]
00f4 mov word ptr [bp - 4], ax
00f7 mov word ptr [bp - 2], dx
00fa mov ax, word ptr [bp + 0x12]
00fd mov dx, word ptr [bp + 0x14]
0100 mov word ptr [bp - 8], ax
0103 mov word ptr [bp - 6], dx
0106 lea ax, [di + 1]
0109 mov word ptr [bp - 0x14], ax
010c mov word ptr [bp - 0x10], ax
010f mov ax, word ptr [bp + 0x18]
0112 mov word ptr [bp - 0xc], ax
0115 mov word ptr [bp - 0xa], di
0118 mov word ptr [bp - 0xe], bx
011b cmp word ptr [bp - 0x14], 0
011f jle 0x7521
0121 mov ax, word ptr [bp - 8]
0124 mov dx, word ptr [bp - 6]
0127 mov bx, word ptr [bp - 4]
012a mov si, word ptr [bp - 2]
012d mov cx, word ptr [bp - 0x14]
0130 shr cx, 1
0132 push ds
0133 push si
0134 mov di, ax
0136 mov si, bx
0138 mov es, dx
013a pop ds
013b rep movsw word ptr es:[di], word ptr [si]
013d jae 0x7520
013f movsb byte ptr es:[di], byte ptr [si]
0140 pop ds
0141 mov ax, word ptr [bp - 0xe]
0144 sub word ptr [bp - 4], ax
0147 mov ax, word ptr [bp - 0x10]
014a add word ptr [bp - 8], ax
014d dec word ptr [bp - 0xc]
0150 jne 0x74fb
0152 pop si
0153 pop di
0154 leave 
0155 retf 
```

## Known declaration examples

- `extern unsigned char near displayType;` — src/recovered/ConvColor.c
- `extern unsigned char near displayType;` — src/recovered/wf_GLine-590430737a.c
- `extern unsigned char near displayType;` — src/recovered/wf_GMixedFill-842c303c86.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_hanim_RemoveAnimSet', 'offset': 28330, 'source': 'src/recovered/wf_hanim_RemoveAnimSet-91a33c0781.c', 'size': 146}
- {'symbol': '_hanim_RenderAnimSet', 'offset': 28476, 'source': None, 'size': 1187}
- {'symbol': '_gr_PutToBuf', 'offset': 30006, 'source': None, 'size': 342}
- {'symbol': '_UncompressDACInstrument', 'offset': 30348, 'source': None, 'size': 133}
