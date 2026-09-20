int IsThisPebble(int x, int y)
{
    if (x <= 1) {
        if (--x)
            return 0;
        if (y >= 0x51 && y <= 0x53)
            return 1;
    } else {
        if (y >= 0x30 && y <= 0x31)
            return 1;
    }
    return 0;
}
