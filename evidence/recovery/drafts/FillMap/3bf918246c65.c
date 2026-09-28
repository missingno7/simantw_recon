extern void *memset(void *, int, unsigned);
extern unsigned char near MapA[];

/* Fill the inclusive rectangle on MapA, one row at a time. */
void far FillMap(int last, int first, int left, int right, unsigned char value)
{
    register int lower = last;
    int start;
    struct FillWidth { int width; int spare; } fillWidth;
    int height;
    register int row;

    if (lower > first)
        return;

    row = lower << 6;
    start = left;
    fillWidth.width = right - left + 1;
    height = first - lower + 1;
    do {
        if (left <= right)
            memset(MapA + start + row, value, fillWidth.width);
        row += 0x40;
    } while (--height);
}