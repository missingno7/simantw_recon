extern unsigned char far Dx8[];
extern int far ConvColor(int);
extern void far win_FillObjRect(int, int);
extern void near drawHistGraph(int, int, int);

void far win_DrawHistoryWindow(int flags) {
    register int index;
    volatile int value[1];
    if ((flags & 2) == 0) return;
    win_FillObjRect(0x150e, ConvColor(0));
    index = 0;
    while (index < 4) {
        value[0] = ((int far *)Dx8)[0x472A + index];
        if (((int far *)Dx8)[0x472A + index] != (int)0x8000)
            drawHistGraph(((int far *)Dx8)[0x472A + index], 0, index);
        ++index;
    }
}
