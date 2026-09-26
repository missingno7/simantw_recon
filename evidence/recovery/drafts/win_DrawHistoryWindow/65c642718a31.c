/* Use the history offset itself for graph iteration and increment after the optional call. */
extern int far Dx8[]; extern int far ConvColor(int); extern void far win_FillObjRect(int, int); extern void far drawHistGraph(int, int, int);
void far win_DrawHistoryWindow(int flags) {
    int offset = 0x8e54, index = 0, value;
    if (flags & 2) return;
    win_FillObjRect(0x150e, ConvColor(0));
    while (offset < 0x8e5c) {
        value = Dx8[offset];
        if (value != (int)0x8000) drawHistGraph(value, 0, index);
        offset += 1; ++index;
    }
}