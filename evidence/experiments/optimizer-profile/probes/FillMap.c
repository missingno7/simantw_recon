/*
 * Hypothesis: fill the inclusive rectangle [first,last] x [left,right]
 * in the 64-byte-row MapA plane.  The target computes the vertical count
 * and horizontal count before rejecting a reversed horizontal range, then
 * emits one byte-fill per row and advances by one map row.
 */
extern unsigned char near MapA[];

void far FillMap(int last, int first, int left, int right, unsigned char value)
{
    int start;
    int width;
    int height;
    register int row;

    if (last > first)
        return;

    row = last << 6;
    start = left;
    width = right - left + 1;
    height = first - last + 1;
    do {
        if (left <= right) {
            int i;
            for (i = 0; i < width; ++i)
                MapA[start + row + i] = value;
        }
        row += 0x40;
    } while (--height);
}
