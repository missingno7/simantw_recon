/* pointer alias with row-shift computed before column use; residual includes wrong transient homes and raw-versus-relocated MapA. */
extern unsigned char near MapA[];
int GrabMap(int x, int y) {
    unsigned char near *cell;
    int row = x;
    if (row > 0x7f) row = 0; else if (row < 0) row = 0x7f;
    cell = MapA + (row << 6);
    if (y > 0x3f) y = 0; else if (y < 0) y = 0x3f;
    return *(cell + y);
}
