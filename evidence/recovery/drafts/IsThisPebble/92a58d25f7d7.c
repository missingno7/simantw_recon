int IsThisPebble(int x, int y)
{
    int ok;
    ok = 0;
    if (x <= 1) {
        if (--x == 0)
            ok = y >= 0x51 && y <= 0x53;
        else
            ok = y >= 0x30 && y <= 0x31;
    } else {
        ok = y >= 0x30 && y <= 0x31;
    }
    return ok;
}
