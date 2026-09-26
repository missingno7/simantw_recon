/* immutable parameters assigned into branch-selected result locals; probe whether branch-selected locals yield DX scratch and BX/DI homes. */
extern unsigned char near MapA[];
int GrabMap(int x, int y) {
    int row;
    int column;
    if (x > 0x7f) row = 0; else if (x < 0) row = 0x7f; else row = x;
    if (y > 0x3f) column = 0; else if (y < 0) column = 0x3f; else column = y;
    return MapA[(row << 6) + column];
}
