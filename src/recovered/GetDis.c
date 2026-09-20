long GetDis(int x1, int y1, int x2, int y2)
{
    int dx;
    int dy;
    dx = x2 - x1;
    dy = y2 - y1;
    return (long)dx * dx + (long)dy * dy;
}
