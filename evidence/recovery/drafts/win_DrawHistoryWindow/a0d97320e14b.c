/* Index the four history words from the byte offset 0x8e54 and call the local graph routine near. */
extern int far Dx8[]; extern int far ConvColor(int); extern void far win_FillObjRect(int, int); extern void near drawHistGraph(int, int, int);
void far win_DrawHistoryWindow(int flags) {
    int index, value;
    if (flags & 2) return;
    win_FillObjRect(0x150e, ConvColor(0));
    index = 0;
    while (index < 4) {
        value = Dx8[0x472a + index];
        if (value != (int)0x8000) drawHistGraph(value, 0, index);
        ++index;
    }
}