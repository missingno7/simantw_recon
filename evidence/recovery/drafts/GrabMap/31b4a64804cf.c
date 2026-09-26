/* row temporary shifted before reusing direct y parameter; tests local lifetime/reuse and early-return tails. */
extern unsigned char near MapA[];
int GrabMap(int x, int y) {
    int index;
    if (x > 0x7f) index = 0; else if (x < 0) index = 0x7f; else index = x;
    index = index << 6;
    if (y > 0x3f) y = 0; else if (y < 0) y = 0x3f;
    return MapA[index + y];
}
