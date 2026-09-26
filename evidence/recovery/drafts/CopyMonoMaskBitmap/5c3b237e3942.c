/*
 * Clip a one-bit bitmap transfer and preserve destination pixels outside its
 * rectangle.  An aligned transfer copies whole bytes; an unaligned transfer
 * shifts a two-byte source window and merges it through first/last byte masks.
 */
void far CopyMonoMaskBitmap(unsigned char huge *destination,
                            unsigned char huge *source,
                            int destinationHeight,
                            int destinationWidth,
                            int copyHeight,
                            int copyWidth,
                            register int x,
                            register int y)
{
    int sourceX;
    int sourceY;
    int width;
    int height;
    int destinationStride;
    int sourceStride;
    int bitOffset;
    volatile int rightClipped;
    int row;

    destinationStride = ((destinationWidth + 31) / 32) * 4;
    sourceStride = (copyWidth + 7) / 8;
    bitOffset = x & 7;
    rightClipped = 1;

    if (x < 0) {
        sourceX = -x;
        width = copyWidth;
        bitOffset = 0;
    } else {
        sourceX = 0;
        if (x + copyWidth > destinationWidth) {
            width = destinationWidth - x;
            rightClipped = 0;
        } else {
            width = copyWidth;
        }
    }

    if (y < 0) {
        sourceY = -y;
        height = copyHeight - sourceY;
        y = 0;
    } else {
        sourceY = 0;
        height = copyHeight;
        if (y + height > destinationHeight)
            height = destinationHeight - y;
    }

    if (width <= 0 || height <= 0)
        return;

    for (row = 0; row < height; ++row) {
        unsigned char huge *sourceRow = source + ((long)(sourceY + row) * sourceStride);
        unsigned char huge *destinationRow = destination + ((long)(y + row) * destinationStride);
        int sourceByte = sourceX >> 3;
        int destinationByte = x >> 3;
        int byteCount = (width + 7) / 8;
        int index;

        if (bitOffset == 0) {
            for (index = 0; index < byteCount; ++index) {
                unsigned char mask = 0xff;
                unsigned char incoming = sourceRow[sourceByte + index];
                unsigned char huge *out = destinationRow + destinationByte + index;
                if (index == byteCount - 1 && (width & 7) != 0)
                    mask = (unsigned char)(0xff << (8 - (width & 7)));
                *out ^= (unsigned char)((*out ^ incoming) & mask);
            }
        } else {
            int last = byteCount - 1;
            unsigned char firstMask = (unsigned char)(0xff >> bitOffset);
            unsigned char lastMask = (width & 7) ? (unsigned char)(0xff << (8 - (width & 7))) : 0xff;
            if (byteCount == 1) {
                unsigned int pair = sourceRow[sourceByte];
                unsigned char incoming;
                unsigned char mask = (unsigned char)(firstMask & lastMask);
                unsigned char huge *out = destinationRow + destinationByte;
                pair |= (unsigned int)sourceRow[sourceByte + 1] << 8;
                incoming = (unsigned char)(pair >> bitOffset);
                *out ^= (unsigned char)((*out ^ incoming) & mask);
            } else {
                unsigned int pair = sourceRow[sourceByte];
                unsigned char incoming;
                unsigned char huge *out = destinationRow + destinationByte;
                pair |= (unsigned int)sourceRow[sourceByte + 1] << 8;
                incoming = (unsigned char)(pair >> bitOffset);
                *out ^= (unsigned char)((*out ^ incoming) & firstMask);
                for (index = 1; index < last; ++index) {
                    pair = sourceRow[sourceByte + index];
                    pair |= (unsigned int)sourceRow[sourceByte + index + 1] << 8;
                    incoming = (unsigned char)(pair >> bitOffset);
                    out = destinationRow + destinationByte + index;
                    *out ^= (unsigned char)((*out ^ incoming) & 0xff);
                }
                pair = sourceRow[sourceByte + last];
                pair |= (unsigned int)sourceRow[sourceByte + last + 1] << 8;
                incoming = (unsigned char)(pair >> bitOffset);
                out = destinationRow + destinationByte + last;
                *out ^= (unsigned char)((*out ^ incoming) & lastMask);
            }
        }
    }
}
