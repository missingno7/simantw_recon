extern void near DoFastBitmap(int a, int b, int width, int height,
                              int x, int y, int mask);

void gr_FastMaskTileNoMask(int source, int color, int x, int y)
{
    int savedSource = source;

    DoFastBitmap(savedSource, color, 16, 16, x, y, 0);
}
