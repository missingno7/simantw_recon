int IsThisPebble(int x, register int y)
{
    if (x <= 1) {
        if (--x != 0)
            return 0;
        if (y < 0x51 || y > 0x53)
            return 0;
        return 1;
    }
    if (y < 0x30 || y > 0x31)
        return 0;
    return 1;
}
