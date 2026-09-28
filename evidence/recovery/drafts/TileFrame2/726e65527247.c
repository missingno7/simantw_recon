/* TileFrame2 draws the same rectangular border as TileFrame1, using its paired tile IDs. */
extern unsigned char near MapA[];
void far TileFrame2(int top, int bottom, int left, int right)
{
    int r;
    int c;
    for (r = top; r <= bottom; r++)
        for (c = left; c <= left; c++) MapA[(r << 6) + c] = 0x51;
    for (r = top; r <= bottom; r++)
        for (c = right; c <= right; c++) MapA[(r << 6) + c] = 0x54;
    for (r = top; r <= top; r++)
        for (c = left; c <= right; c++) MapA[(r << 6) + c] = 0x5b;
    for (r = bottom; r <= bottom; r++)
        for (c = left; c <= right; c++) MapA[(r << 6) + c] = 0x5a;
    MapA[(top << 6) + left] = 0x56;
    MapA[(bottom << 6) + left] = 0x58;
    MapA[(top << 6) + right] = 0x57;
    MapA[(bottom << 6) + right] = 0x59;
}
