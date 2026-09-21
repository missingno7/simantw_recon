extern int far Dx8[];
extern int far ConvColor(int color);
extern void far win_FillObjRect(int object, int color);
extern void far drawHistGraph(int value, int zero, int index);

void far win_DrawHistoryWindow(int flags)
{
    int index;
    int value;
    int color;
    int far *scan;

    if (flags & 2)
        return;
    color = ConvColor(0);
    win_FillObjRect(0x150e, color);
    index = 0;
    scan = &Dx8[0x8e54];
    while (scan < &Dx8[0x8e5c]) {
        value = *scan;
        if (value != (int)0x8000)
            drawHistGraph(value, 0, index);
        ++index;
        ++scan;
    }
}
