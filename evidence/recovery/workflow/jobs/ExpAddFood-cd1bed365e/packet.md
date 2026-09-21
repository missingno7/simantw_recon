# Recovery task _ExpAddFood

Use `docs/cheap-model-handoff.md`. Write readable C and a semantic hypothesis; use the workflow commands for proof and promotion.

Code group: `ANTEDIT_MODULE`. Closed extent: 152 bytes.

```asm
0000 enter 4, 0
0004 push di
0005 push si
0006 mov es, word ptr [0xc270]
000a cmp byte ptr es:[0x8604], 0
0010 jne 0x7b3c
0012 push word ptr [bp + 8]
0015 push word ptr [bp + 6]
0018 nop 
0019 push cs
001a call 0x7f3a ; _IncFoodHere
001d add sp, 4
0020 or ax, ax
0022 je 0x7b9a
0024 push 0x7e
0026 push 0
0028 push 0x1d
002a lcall <resolved loader operand; see bindings> ; [{'operand_offset': 45, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
002f add sp, 6
0032 pop si
0033 pop di
0034 leave 
0035 retf 
0036 push 0x7e
0038 push 0
003a push 0x20
003c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 63, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 2}}] ; _myBeginSound
0041 add sp, 6
0044 mov si, 0x14
0047 mov di, word ptr [bp + 6]
004a push 9
004c lcall <resolved loader operand; see bindings> ; [{'operand_offset': 79, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0051 add sp, 2
0054 add ax, di
0056 sub ax, 4
0059 mov word ptr [bp - 2], ax
005c push 9
005e lcall <resolved loader operand; see bindings> ; [{'operand_offset': 97, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _SRand1
0063 add sp, 2
0066 add ax, word ptr [bp + 8]
0069 sub ax, 4
006c mov word ptr [bp - 4], ax
006f push ax
0070 push word ptr [bp - 2]
0073 push word ptr [0xcc76] ; _MapPlane
0077 lcall <resolved loader operand; see bindings> ; [{'operand_offset': 122, 'type': 2, 'target': {'kind': 'internal', 'offset': 0, 'segment': 5}}] ; _IsValidLocation
007c add sp, 6
007f or ax, ax
0081 je 0x7b97
0083 push word ptr [bp - 4]
0086 push word ptr [bp - 2]
0089 nop 
008a push cs
008b call 0x7f3a ; _IncFoodHere
008e add sp, 4
0091 dec si
0092 jne 0x7b50
0094 pop si
0095 pop di
0096 leave 
0097 retf 
```

## Known declaration examples

- `extern int near MapPlane;` — src/recovered/BalloonIsVisible.c
- `extern int near MapPlane;` — src/recovered/wf_CenterAnt-5b585d8f15.c
- `extern int near MapPlane;` — src/recovered/wf_EditMsgBalloon-9036028d9e.c
- `extern int far SRand1(int range);` — src/recovered/wf_Bounce-0d87abbf42.c
- `extern int far SRand1(int range);` — src/recovered/wf_DrawRain-d667f83eb1.c
- `extern void far myBeginSound(unsigned int first, unsigned int second, unsigned int third);` — src/recovered/myBeginSoundReverse.c

## Interpretation

- ?? bytes belong to NE loader relocation chains, never literal C addresses.
- Global DS annotations assume normal DGROUP; far/huge and aggregate types require evidence.
- Next MAPSYM public is an upper bound, not the function end.
- Declared types in other verified sources are useful hypotheses, not proof of a shared historical header.

## Neighbors

- {'symbol': '_ClearLifeR', 'offset': 31144, 'source': 'src/recovered/wf_ClearLifeR-d74962e731.c', 'size': 83}
- {'symbol': '_ExpAddAnt', 'offset': 31228, 'source': None, 'size': 266}
- {'symbol': '_ExpIncSmell', 'offset': 31646, 'source': None, 'size': 445}
- {'symbol': '_ExpKillAnts', 'offset': 32092, 'source': None, 'size': 478}
