struct MonoMaskPair { unsigned char left; unsigned char right; };
struct MonoMaskTables { struct MonoMaskPair pair[8]; int word[8]; };
static struct MonoMaskTables monoMasks = {
    {{0x00,0x00},{0x80,0x7f},{0xc0,0x3f},{0xe0,0x1f},
     {0xf0,0x0f},{0xf8,0x07},{0xfc,0x03},{0xfe,0x01}},
    {-256,-128,-64,-32,-16,-8,-4,-2}
};
extern void far *_fmemcpy(void far *destination, const void far *source,
                          unsigned int count);

void far CopyMonoBitmap(unsigned char huge *destination,
                        unsigned char huge *source,
                        int destinationHeight, int destinationWidth,
                        int sourceHeight, int sourceWidth,
                        int x, int y)
{
    int destinationStride;
    int sourceStride;
    int rows;
    int row;
    int bitOffset;
    int byteCount;
    int byteIndex;
    int sourceRemainder;
    unsigned int window;
    unsigned int shifted;
    unsigned char difference;
    unsigned char incoming;

    destinationStride = ((destinationWidth + 31) / 32) * 4;
    sourceStride = (sourceWidth + 7) / 8;
    rows = sourceHeight;
    if (rows > destinationHeight)
        rows = destinationHeight;
    bitOffset = x & 7;

    if (bitOffset != 0) {
        byteCount = (bitOffset + sourceWidth + 7) >> 3;
        if (byteCount > destinationStride - (x >> 3))
            byteCount = destinationStride - (x >> 3);
        if (byteCount <= 0 || rows <= 0)
            return;
        sourceRemainder = sourceWidth & 7;

        for (row = 0; row < rows; ++row) {
            for (byteIndex = 0; byteIndex < byteCount - 1; ++byteIndex) {
                if (byteIndex < sourceStride) {
                    window = (unsigned int)source[(long)(sourceHeight - row - 1) * sourceStride + byteIndex] << 8;
                    if (byteIndex + 1 < sourceStride)
                        window |= source[(long)(sourceHeight - row - 1) * sourceStride + byteIndex + 1];
                    if (sourceRemainder != 0 && byteIndex + 1 == sourceStride - 1)
                        window &= (unsigned int)monoMasks.word[sourceRemainder];
                    if (sourceRemainder != 0 && byteIndex == sourceStride - 1)
                        window &= (unsigned int)monoMasks.pair[sourceRemainder].left << 8;
                    shifted = window >> bitOffset;

                    difference = (unsigned char)(
                        ((unsigned char)shifted ^ destination[(long)(y + row) * destinationStride +
                         (x >> 3) + byteIndex + 1]) & monoMasks.pair[bitOffset].left);
                    destination[(long)(y + row) * destinationStride + (x >> 3) + byteIndex + 1] ^= difference;

                    difference = (unsigned char)(
                        ((unsigned char)(shifted >> 8) ^ destination[(long)(y + row) * destinationStride +
                         (x >> 3) + byteIndex]) & monoMasks.pair[bitOffset].right);
                    destination[(long)(y + row) * destinationStride + (x >> 3) + byteIndex] ^= difference;
                }
            }

            byteIndex = byteCount - 1;
            if (byteIndex < sourceStride) {
                window = (unsigned int)source[(long)(sourceHeight - row - 1) * sourceStride + byteIndex] << 8;
                if (byteIndex + 1 < sourceStride)
                    window |= source[(long)(sourceHeight - row - 1) * sourceStride + byteIndex + 1];
                if (sourceRemainder != 0 && byteIndex == sourceStride - 1)
                    window &= (unsigned int)monoMasks.pair[sourceRemainder].left << 8;
                shifted = window >> bitOffset;
                incoming = (unsigned char)(shifted >> 8);
                difference = (unsigned char)(
                    (incoming ^ destination[(long)(y + row) * destinationStride +
                     (x >> 3) + byteIndex]) & monoMasks.pair[bitOffset].right);
                destination[(long)(y + row) * destinationStride + (x >> 3) + byteIndex] ^= difference;
            }
        }
        } else {
        byteCount = destinationStride - (x >> 3);
        if (byteCount > sourceStride)
            byteCount = sourceStride;
        if (byteCount > 0) {
            for (row = 0; row < rows; ++row) {
                _fmemcpy(destination + (long)(y + row) * destinationStride + (x >> 3),
                         source + (long)(sourceHeight - row - 1) * sourceStride,
                         (unsigned int)byteCount);
            }
        }
        }
}
