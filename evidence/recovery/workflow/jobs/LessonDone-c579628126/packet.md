# Recovery task _LessonDone

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `SIMTWO_MODULE`. Closed extent: 627 bytes.

```asm
0000 push bp
0001 mov bp, sp
0003 push si
0004 mov ax, word ptr [bp + 6]
0007 dec ax
0008 cmp ax, 0x37
000b jbe 0x7f12
000d jmp 0x8170
0010 shl ax, 1
0012 xchg bx, ax
0013 jmp word ptr cs:[bx + 0x7f1a]
0018 dw offset 0x7f8a
001a dw offset 0x7f8a
001c dw offset 0x7f90
001e dw offset 0x7f90
0020 dw offset 0x8072
0022 dw offset 0x7f8a
0024 dw offset 0x7fc4
0026 dw offset 0x80e0
0028 dw offset 0x800a
002a dw offset 0x8028
002c dw offset 0x7f8a
002e dw offset 0x8130
0030 dw offset 0x8038
0032 dw offset 0x8054
0034 dw offset 0x7f8a
0036 dw offset 0x8062
0038 dw offset 0x7f8a
003a dw offset 0x806a
003c dw offset 0x8082
003e dw offset 0x8072
0040 dw offset 0x807a
0042 dw offset 0x8082
0044 dw offset 0x7f8a
0046 dw offset 0x808a
0048 dw offset 0x7f8a
004a dw offset 0x7fc4
004c dw offset 0x8096
004e dw offset 0x7f8a
0050 dw offset 0x7f8a
0052 dw offset 0x80c8
0054 dw offset 0x7f8a
0056 dw offset 0x8028
0058 dw offset 0x80f4
005a dw offset 0x7f8a
005c dw offset 0x7f8a
005e dw offset 0x80fc
0060 dw offset 0x7f8a
0062 dw offset 0x8104
0064 dw offset 0x810c
0066 dw offset 0x7f8a
0068 dw offset 0x8112
006a dw offset 0x8028
006c dw offset 0x80e0
006e dw offset 0x7f8a
0070 dw offset 0x7f8a
0072 dw offset 0x80e0
0074 dw offset 0x812a
0076 dw offset 0x7f8a
0078 dw offset 0x8130
007a dw offset 0x80e0
007c dw offset 0x7f8a
007e dw offset 0x8136
0080 dw offset 0x7f8a
0082 dw offset 0x8144
0084 dw offset 0x7f8a
0086 dw offset 0x7f8a
0088 mov ax, 1
008b pop si
008c leave 
008d retf 
008e mov es, word ptr [0xc66a]
0092 mov ax, word ptr es:[0x72c8]
0096 cdq 
0097 mov es, word ptr [0xc65e]
009b cmp dx, word ptr es:[0x9b12]
00a0 jge 0x7fa7
00a2 jmp 0x8170
00a5 jg 0x7fb3
00a7 cmp ax, word ptr es:[0x9b10]
00ac ja 0x7fb3
00ae jmp 0x8170
00b1 mov es, word ptr [0xc676]
00b5 cmp word ptr es:[0x7d24], 0
00bb je 0x7fc2
00bd jmp 0x8170
00c0 jmp 0x7f8a
00c2 mov ax, word ptr [0xce7e] ; _MeLocY
00c5 add ax, word ptr [0xcd88] ; _MeLocX
00c9 mov es, word ptr [0xc66e]
00cd cmp ax, word ptr es:[0x9fb0]
00d2 jne 0x7fd9
00d4 jmp 0x8170
00d7 mov es, word ptr [0xc678]
00db cmp word ptr es:[0x9fe2], 0
00e1 je 0x7fe8
00e3 jmp 0x8170
00e6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 233, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _MacTickCount
00eb mov es, word ptr [0xc65e]
00ef cmp dx, word ptr es:[0x9b12]
00f4 jge 0x7ffb
00f6 jmp 0x8170
00f9 jg 0x7f8a
00fb cmp ax, word ptr es:[0x9b10]
0100 ja 0x8007
0102 jmp 0x8170
0105 jmp 0x7f8a
0107 nop 
0108 mov es, word ptr [0xc670]
010c mov ax, word ptr es:[0x7d30]
0110 add ax, word ptr es:[0x7d2e]
0115 mov es, word ptr [0xc66e]
0119 cmp ax, word ptr es:[0x9fb0]
011e je 0x8025
0120 jmp 0x7f8a
0123 jmp 0x7fe8
0125 nop 
0126 push 0x100
0129 nop 
012a push cs
012b call 0xc19e ; _win_IsWinInFront
012e add sp, 2
0131 or ax, ax
0133 jmp 0x80ea
0136 cmp word ptr [0xce80], 1 ; _MePlane
013b je 0x8042
013d jmp 0x8170
0140 mov si, word ptr [0xcd88] ; _MeLocX
0144 shl si, 6
0147 mov bx, word ptr [0xce7e] ; _MeLocY
014b cmp byte ptr [bx + si + 0x28e8], 0x47
0150 jmp 0x8002
0152 cmp word ptr [0xac8a], 0x5a ; _MeHealth
0157 jg 0x805e
0159 jmp 0x8170
015c jmp 0x7f8a
015f nop 
0160 cmp word ptr [0xcc84], 0x18 ; _MeType
0165 jmp 0x7fbd
0168 cmp word ptr [0xce80], 2 ; _MePlane
016d jmp 0x7fbd
0170 cmp word ptr [0xce80], 1 ; _MePlane
0175 jmp 0x7fbd
0178 cmp word ptr [0xcc84], 0x28 ; _MeType
017d jmp 0x7fbd
0180 cmp word ptr [0xcc84], 0x10 ; _MeType
0185 jmp 0x7fbd
0188 mov es, word ptr [0xc67a]
018c cmp word ptr es:[0x9e7a], 1
0192 jmp 0x8059
0194 mov ax, word ptr [0xce7e] ; _MeLocY
0197 add ax, word ptr [0xcd88] ; _MeLocX
019b mov es, word ptr [0xc66e]
019f cmp ax, word ptr es:[0x9fb0]
01a4 jne 0x80ab
01a6 jmp 0x8170
01a9 mov es, word ptr [0xc67c]
01ad cmp word ptr es:[0x75fa], 0
01b3 jne 0x80ba
01b5 jmp 0x8170
01b8 mov es, word ptr [0xc678]
01bc cmp word ptr es:[0x9fe2], 0
01c2 jmp 0x7fbd
01c5 nop 
01c6 mov es, word ptr [0xc67c]
01ca cmp word ptr es:[0x75fa], 0
01d0 je 0x80e0
01d2 push 1
01d4 push 0
01d6 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 473, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 1}}] ; _SetAlarmDropState
01db add sp, 4
01de mov es, word ptr [0xc66e]
01e2 cmp word ptr es:[0x9fb0], 0
01e8 jne 0x80ef
01ea jmp 0x8170
01ed jmp 0x7f8a
01f0 nop 
01f1 nop 
01f2 cmp word ptr [0xcc76], 0 ; _MapPlane
01f7 jmp 0x7fbd
01fa cmp word ptr [0xce82], 1 ; _YardMode
01ff jmp 0x7fbd
0202 cmp word ptr [0xcc76], 1 ; _MapPlane
0207 jmp 0x7fbd
020a push 0x1200
020d jmp 0x802b
0210 mov es, word ptr [0xc672]
0214 mov ax, word ptr es:[0x9c76]
0218 add ax, word ptr es:[0x9c74]
021d mov es, word ptr [0xc66e]
0221 cmp ax, word ptr es:[0x9fb0]
0226 jmp 0x80ea
0228 push 0x1300
022b jmp 0x802b
022e push 0
0230 jmp 0x802b
0233 nop 
0234 mov es, word ptr [0xc67a]
0238 cmp word ptr es:[0x9e7a], 0x28
023e jmp 0x8059
0241 nop 
0242 mov dx, word ptr [0xce80] ; _MePlane
0246 cmp dx, 3
0249 jne 0x815c
024b mov es, word ptr [0xc66e]
024f mov word ptr es:[0x9fb0], 0
0256 jmp 0x7f8a
0259 nop 
025a cmp dx, 2
025d jne 0x8170
025f mov ax, 1
0262 mov es, word ptr [0xc66e]
0266 mov word ptr es:[0x9fb0], ax
026a pop si
026b leave 
026c retf 
026d nop 
026e xor ax, ax
0270 pop si
0271 leave 
0272 retf 
```

## Known declaration examples

- `extern unsigned long far MacTickCount(void);` — src/recovered/wf_tu_simtwo_1378_InitSimYard_4-bf9b121c43.c
- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int near MeLocX;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocX;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocX;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeLocY;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MeLocY;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeLocY;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MePlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MePlane;` — src/recovered/wf_DoRecruitN-cac1aa103b.c
- `extern int near MePlane;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near MeType;` — src/recovered/wf_MoveMyLife-f66a8c0d06.c
- `extern int near MeType;` — src/recovered/wf_YellowHelp-e88c6bf26d.c
- `extern void far SetAlarmDropState(int state, int quiet);` — src/recovered/wf_EnterNest-606488b329.c
- `extern int near YardMode;` — src/recovered/wf_SetMapTitle-b3c9718398.c
- `extern int near YardMode;` — src/recovered/wf_tu_antedit_A998_DrawYard_2-943dd971c2.c
- `extern int near YardMode;` — src/recovered/wf_tu_simtwo_5AB0_RandWorld_12-c7664162e4.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/DoTab.c
- `extern int far win_IsWinInFront(int window);` — src/recovered/wf_ReDrawMapEdit-0c32a1284f.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_RunTutor', 'offset': 31376, 'source': None, 'size': 190}
- {'symbol': '_GiveLesson', 'offset': 31566, 'source': None, 'size': 948}
- {'symbol': '_db_Exists', 'offset': 33142, 'source': 'src/recovered/db_Exists.c', 'size': 54}
- {'symbol': '_db_SetDataBase', 'offset': 33196, 'source': None, 'size': 146}
