# Recovery task _NetworkSend

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMANT_MODULE`. Closed extent: 451 bytes.

```asm
0000 enter 8, 0
0004 push 0x1e
0006 push 0x1e
0008 push ds
0009 push 0x2d6
000c push ds
000d push 0x2de
0010 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 19, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbCall
0015 add sp, 0xc
0018 mov byte ptr [bp - 1], al
001b or al, al
001d jne 0x2082
001f jmp 0x2221
0022 mov word ptr [bp - 4], 2
0027 lea ax, [bp - 4]
002a push ss
002b push ax
002c lea ax, [bp - 8]
002f push ss
0030 push ax
0031 mov cl, byte ptr [bp - 1]
0034 push cx
0035 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 56, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
003a add sp, 0xa
003d mov ax, word ptr [bp - 8]
0040 or ax, ax
0042 jge 0x20a7
0044 jmp 0x21e5
0047 jno 0x20ac
0049 jmp 0x21e5
004c dec ax
004d jle 0x20be
004f dec ax
0050 jne 0x20b5
0052 jmp 0x2168
0055 dec ax
0056 jne 0x20bb
0058 jmp 0x21a4
005b jmp 0x21e5
005e mov al, byte ptr [bp - 1]
0061 push ax
0062 push 0x1000
0065 push ds
0066 push 0x28e8
0069 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 108, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
006e add sp, 8
0071 mov word ptr [bp - 4], 2
0076 lea cx, [bp - 4]
0079 push ss
007a push cx
007b lea dx, [bp - 6]
007e push ss
007f push dx
0080 mov dl, byte ptr [bp - 1]
0083 push dx
0084 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 135, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
0089 add sp, 0xa
008c mov al, byte ptr [bp - 1]
008f push ax
0090 push 0x1000
0093 mov cx, 0x28e8
0096 mov dx, ds
0098 add ch, 0x10
009b adc dx, 0
009e push dx
009f push cx
00a0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 163, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
00a5 add sp, 8
00a8 mov word ptr [bp - 4], 2
00ad lea ax, [bp - 4]
00b0 push ss
00b1 push ax
00b2 lea cx, [bp - 6]
00b5 push ss
00b6 push cx
00b7 mov cl, byte ptr [bp - 1]
00ba push cx
00bb lcall <resolved loader operand; see bindings> ; [{'operand_offset': 190, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
00c0 add sp, 0xa
00c3 mov al, byte ptr [bp - 1]
00c6 push ax
00c7 push 0x1000
00ca mov cx, 0x68e8
00cd mov dx, ds
00cf add ch, 0x10
00d2 adc dx, 0
00d5 push dx
00d6 push cx
00d7 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 218, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
00dc add sp, 8
00df mov word ptr [bp - 4], 2
00e4 lea ax, [bp - 4]
00e7 push ss
00e8 push ax
00e9 lea ax, [bp - 6]
00ec push ss
00ed push ax
00ee mov al, byte ptr [bp - 1]
00f1 push ax
00f2 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 245, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
00f7 add sp, 0xa
00fa mov al, byte ptr [bp - 1]
00fd push ax
00fe push 0x1000
0101 push ds
0102 push 0x68e8
0105 jmp 0x21dd
0107 nop 
0108 mov al, byte ptr [bp - 1]
010b push ax
010c push 0x1000
010f push ds
0110 push 0x48e8
0113 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 278, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
0118 add sp, 8
011b mov word ptr [bp - 4], 2
0120 lea ax, [bp - 4]
0123 push ss
0124 push ax
0125 lea ax, [bp - 6]
0128 push ss
0129 push ax
012a mov al, byte ptr [bp - 1]
012d push ax
012e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 305, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
0133 add sp, 0xa
0136 mov al, byte ptr [bp - 1]
0139 push ax
013a push 0x1000
013d push ds
013e push 0x88e8
0141 jmp 0x21dd
0143 nop 
0144 mov al, byte ptr [bp - 1]
0147 push ax
0148 push 0x1000
014b push ds
014c push 0x58e8
014f lcall <resolved loader operand; see bindings> ; [{'operand_offset': 338, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
0154 add sp, 8
0157 mov word ptr [bp - 4], 2
015c lea ax, [bp - 4]
015f push ss
0160 push ax
0161 lea ax, [bp - 6]
0164 push ss
0165 push ax
0166 mov al, byte ptr [bp - 1]
0169 push ax
016a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 365, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
016f add sp, 0xa
0172 mov al, byte ptr [bp - 1]
0175 push ax
0176 push 0x1000
0179 push ds
017a push 0x98e8
017d lcall <resolved loader operand; see bindings> ; [{'operand_offset': 384, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
0182 add sp, 8
0185 mov word ptr [bp - 4], 2
018a lea ax, [bp - 4]
018d push ss
018e push ax
018f lea ax, [bp - 6]
0192 push ss
0193 push ax
0194 mov al, byte ptr [bp - 1]
0197 push ax
0198 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 411, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbReceive
019d add sp, 0xa
01a0 mov al, byte ptr [bp - 1]
01a3 push ax
01a4 mov cx, 0xacac
01a7 sub cx, 0xac5a
01ab push cx
01ac push ds
01ad push 0xac5a
01b0 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 435, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbSend
01b5 add sp, 8
01b8 mov al, byte ptr [bp - 1]
01bb push ax
01bc lcall <resolved loader operand; see bindings> ; [{'operand_offset': 447, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 4}}] ; _NbHangUp
01c1 leave 
01c2 retf 
```

## Known declaration examples


## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_NetBIOSPost', 'offset': 7538, 'source': None, 'size': None}
- {'symbol': '_ProcessPost', 'offset': 7615, 'source': None, 'size': 672}
- {'symbol': '_UpdateWindows', 'offset': 8740, 'source': None, 'size': 540}
- {'symbol': 'MYTIMERFUNC', 'offset': 9280, 'source': None, 'size': 973}
