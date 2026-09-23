# Recovery task _gr_PutToBuf

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `GR_MODULE`. Closed extent: 342 bytes.

```asm
0000 enter 0x14, 0
0004 push di
0005 push si
0006 test byte ptr [0xcc7e], 1 ; _displayType
000b je 0x7546
000d jmp 0x75e8
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
003e jg 0x7579
0040 jmp 0x7688
0043 mov ax, word ptr [bp + 0x12]
0046 mov dx, word ptr [bp + 0x14]
0049 mov word ptr [bp - 6], ax
004c mov word ptr [bp - 4], dx
004f mov ax, word ptr [bp + 0x10]
0052 sub ax, word ptr [bp + 8]
0055 dec ax
0056 imul bx
0058 mov cx, word ptr [bp + 6]
005b sar cx, 1
005d add ax, cx
005f add ax, word ptr [bp + 0xa]
0062 mov dx, word ptr [bp + 0xc]
0065 mov word ptr [bp - 0xa], ax
0068 mov word ptr [bp - 8], dx
006b mov ax, word ptr [bp + 0x18]
006e mov word ptr [bp - 0xc], ax
0071 mov word ptr [bp - 2], di
0074 mov word ptr [bp - 0xe], bx
0077 cmp word ptr [bp - 2], 0
007b jle 0x75d3
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
0099 jae 0x75d2
009b movsb byte ptr es:[di], byte ptr [si]
009c pop ds
009d mov ax, word ptr [bp - 2]
00a0 add word ptr [bp - 6], ax
00a3 mov ax, word ptr [bp - 0xe]
00a6 sub word ptr [bp - 0xa], ax
00a9 dec word ptr [bp - 0xc]
00ac jne 0x75ad
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
00db jle 0x7688
00dd mov ax, word ptr [bp + 0x12]
00e0 mov dx, word ptr [bp + 0x14]
00e3 mov word ptr [bp - 4], ax
00e6 mov word ptr [bp - 2], dx
00e9 lea ax, [di + 1]
00ec mov word ptr [bp - 0x14], ax
00ef mov word ptr [bp - 0x10], ax
00f2 mov ax, word ptr [bp + 0x10]
00f5 sub ax, word ptr [bp + 8]
00f8 dec ax
00f9 imul bx
00fb mov cx, word ptr [bp + 6]
00fe sar cx, 3
0101 add ax, cx
0103 add ax, word ptr [bp + 0xa]
0106 mov dx, word ptr [bp + 0xc]
0109 mov word ptr [bp - 8], ax
010c mov word ptr [bp - 6], dx
010f mov ax, word ptr [bp + 0x18]
0112 mov word ptr [bp - 0xc], ax
0115 mov word ptr [bp - 0xa], di
0118 mov word ptr [bp - 0xe], bx
011b cmp word ptr [bp - 0x14], 0
011f jle 0x7677
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
013d jae 0x7676
013f movsb byte ptr es:[di], byte ptr [si]
0140 pop ds
0141 mov ax, word ptr [bp - 0x10]
0144 add word ptr [bp - 4], ax
0147 mov ax, word ptr [bp - 0xe]
014a sub word ptr [bp - 8], ax
014d dec word ptr [bp - 0xc]
0150 jne 0x7651
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

- {'symbol': '_hanim_RenderAnimSet', 'offset': 28476, 'source': None, 'size': 1187}
- {'symbol': '_gr_GetFromBuf', 'offset': 29664, 'source': None, 'size': 342}
- {'symbol': '_UncompressDACInstrument', 'offset': 30348, 'source': None, 'size': 133}
- {'symbol': '_IsMMMidiAvail', 'offset': 30482, 'source': 'src/recovered/wf_tu_gr_7712_IsMMMidiAvail_14_reviewed-9f2a039d59.c', 'size': 42}
