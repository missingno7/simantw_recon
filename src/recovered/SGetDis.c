/* Byte-matched reconstruction; historical declaration spelling is uncertain. */
int SGetDis(int x1, int y1, int x2, int y2)
{
    int dx = y2 - y1;
    int dy = x2 - x1;
    if (dy < 0) dy = -dy;
    if (dx < 0) dx = -dx;
    dx += dy;
    return dx;
}
