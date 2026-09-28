/* Count-down loops keep the original inclusive bounds and hoisted guards. */
extern unsigned char near MapA[];
void far FillMap(int first, int last, int left, int right, unsigned char value)
{
    int height;
    int start;
    int width;
    register int row;
    if (first > last)
        return;
    row = first << 6;
    start = left;
    width = right - left + 1;
    height = last - first + 1;
    if (right < left)
        return;
    while (height) {
        int i;
        for (i = 0; i < width; ++i)
            MapA[start + row + i] = value;
        row += 0x40;
        --height;
    }
}
