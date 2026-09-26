/* Declare the based data view and keep the near offset pointer before the index local. */
extern int __based(__segname("PACK")) Dx8[];
extern int far ConvColor(int); extern void far win_FillObjRect(int, int); extern void near drawHistGraph(int, int, int);
void far win_DrawHistoryWindow(int flags) {
    register int __based(__segname("PACK")) *sample;
    register int index;
    int value;
    if ((flags & 2) == 0) return;
    win_FillObjRect(0x150e, ConvColor(0));
    index = 0;
    for (sample = &Dx8[0x472a]; index < 4; ++index, ++sample) {
        value = *sample;
        if (value != (int)0x8000) drawHistGraph(value, 0, index);
    }
}