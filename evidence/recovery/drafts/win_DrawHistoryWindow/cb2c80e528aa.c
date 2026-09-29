extern unsigned char __based(__segname("SIMANT_DATA_GROUP")) Dx8[];
extern int far ConvColor(int);
extern void far win_FillObjRect(int, int);
extern void near drawHistGraph(int, int, int);

void far win_DrawHistoryWindow(int flags) {
    register int index;
    register int __based(__segname("SIMANT_DATA_GROUP")) *sample;
    volatile int value[1];
    if ((flags & 2) == 0) return;
    win_FillObjRect(0x150e, ConvColor(0));
    index = 0;
    sample = (int __based(__segname("SIMANT_DATA_GROUP")) *)(Dx8 + 0x8e54);
    while (sample < (int __based(__segname("SIMANT_DATA_GROUP")) *)(Dx8 + 0x8e5c)) {
        value[0] = *sample;
        if (value[0] != (int)0x8000) drawHistGraph(value[0], 0, index);
        ++index;
        ++sample;
    }
}
