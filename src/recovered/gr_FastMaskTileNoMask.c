extern void far DoFastBitmap(int x, int y, int width, int height,
                             int imageOffset, int imageSegment, int mask);

void gr_FastMaskTileNoMask(int x, int y, int imageOffset, int imageSegment)
{
    volatile int locals[2];
    locals[0] = x;

    DoFastBitmap(locals[0], *((volatile int *)&y), 0x10, 0x10,
                 imageOffset, imageSegment, 0);
}
