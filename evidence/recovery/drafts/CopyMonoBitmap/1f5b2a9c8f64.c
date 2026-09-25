/*
 * Capture only CopyMonoBitmap's evidenced setup: compute DWORD-aligned
 * destination rows, byte-aligned source rows, and clamp the copied height.
 * The later raster path indexes two unnamed DS tables at 0xBA8C/0xBA8D and
 * another at 0xBA9C; this scratch hypothesis does not assign them invented
 * identities or substitute guessed table declarations.
 */
void far CopyMonoBitmap(unsigned char huge *destination,
                        unsigned char huge *source,
                        int destinationHeight, int destinationWidth,
                        int sourceHeight, int sourceWidth,
                        int x, int y)
{
    int destinationStride;
    int sourceStride;
    int copyHeight;

    destinationStride = ((destinationWidth + 31) / 32) * 4;
    sourceStride = (sourceWidth + 7) / 8;
    copyHeight = sourceHeight;
    if (copyHeight > destinationHeight)
        copyHeight = destinationHeight;

    (void)destination;
    (void)source;
    (void)destinationStride;
    (void)sourceStride;
    (void)copyHeight;
    (void)x;
    (void)y;
}
