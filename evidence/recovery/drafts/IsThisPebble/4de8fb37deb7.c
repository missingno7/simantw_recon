int IsThisPebble(int x, int y)
{
    if (x <= 1) {
        if (--x == 0) {
            if (y < 0x51 || y > 0x53)
                return 0;
            return 1;
        }
    }
    {
        register int lowY;
        lowY = y;
        if (lowY < 0x30 || lowY > 0x31)
            return 0;
        return 1;
    }
}
