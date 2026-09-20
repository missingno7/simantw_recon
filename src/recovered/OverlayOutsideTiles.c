extern int far Barrier;

void OverlayOutsideTiles(void)
{
    Barrier = 0x50;
}
