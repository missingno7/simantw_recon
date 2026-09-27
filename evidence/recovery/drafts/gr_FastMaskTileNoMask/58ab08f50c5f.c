/* gr_FastMaskTileNoMask: call the shared bitmap tile renderer with a 16x16 tile and mask zero. */
extern void far DoFastBitmap(int a, int b, int width, int height,
                              int x, int y, int mask);

void gr_FastMaskTileNoMask(int source, int color, int x, int y)
{
    volatile int sourceSlot[2];
    volatile int savedColor;
    sourceSlot[0] = source;
    savedColor = color;

    DoFastBitmap(sourceSlot[0], savedColor, 16, 16, x, y, 0);
}
