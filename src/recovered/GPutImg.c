extern void far DoMonoBitmap(int x, int y, int width, int height,
                             void far *data, int mask);

void GPutImg(int x, int y, unsigned char far *image, int mask)
{
    volatile int localX = x;
    volatile int localY = y;
    int far *words = (int far *)image;

    DoMonoBitmap(localX, localY, words[0], words[1],
                 (void far *)(image + 4), mask);
}
