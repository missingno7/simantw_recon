/* Fills an inclusive rectangle in the 64-byte-row map. */
extern void *memset(void *, int, unsigned);
extern unsigned char near MapA[];
void far FillMap(int last, int first, int left, int right, unsigned char value) {
    int bottom, top, start, width, height, row;
    bottom = last; top = first;
    if (bottom > top) return;
    row = bottom << 6; start = left; width = right - left + 1;
    height = top - bottom + 1;
    do {
        if (left <= right) memset(MapA + start + row, value, width);
        row += 0x40;
    } while (--height);
}
