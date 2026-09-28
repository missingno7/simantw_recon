/* Probe a volatile word counter as an observable local without changing its width. */
extern signed char far Dx8[];
extern signed char far Dy8[];
extern unsigned char near MapA[];
static unsigned char HoleValues[8] = {0x19,0x1a,0x1c,0x1f,0x1e,0x1d,0x1b,0x18};
void far HoleBorder(int x, int y)
{
    volatile int i;
    int row, column;
    for (i = 0; i < 8; ++i) {
        row = Dy8[i] + y; column = Dx8[i] + x;
        if (column >= 0 && column <= 127 && row >= 0 && row <= 63) {
            unsigned char near *tile = MapA + (column << 6) + row;
            if (*tile < 0x50) *tile = HoleValues[i];
        }
    }
}
