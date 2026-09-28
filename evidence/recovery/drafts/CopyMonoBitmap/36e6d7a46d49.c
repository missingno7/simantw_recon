/* Copy a packed one-bit row at an arbitrary destination bit offset. */
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
    int lastByte;
    int fullByteCount;
    int endBits;
    unsigned int window;
    unsigned char incoming;
    unsigned char following;
    unsigned char edgeMask;
    unsigned char firstMask;
    unsigned char lastMask;

    destinationStride = ((destinationWidth + 31) / 32) * 4;
    sourceStride = (sourceWidth + 7) / 8;
    rows = sourceHeight;
    if (rows > destinationHeight)
        rows = destinationHeight;
    bitOffset = x & 7;
    fullByteCount = (bitOffset + sourceWidth + 7) >> 3;
    byteCount = destinationStride - (x >> 3);
    if (byteCount > fullByteCount)
        byteCount = fullByteCount;
    if (byteCount <= 0 || rows <= 0)
        return;
    lastByte = byteCount - 1;
    endBits = (bitOffset + sourceWidth) & 7;

    for (row = 0; row < rows; ++row) {
                         (long)(y + row) * destinationStride + (x >> 3);

        if (bitOffset == 0) {
            for (byteCount = 0; byteCount <= lastByte; ++byteCount) {
                edgeMask = 0xff;
                if (byteCount == sourceStride - 1 &&
                    (sourceWidth & 7) != 0)
                    edgeMask = (unsigned char)(0xff << (8 - (sourceWidth & 7)));
                destination[(long)(y + row) * destinationStride + (x >> 3) + byteCount] ^=
                    (unsigned char)(source[(long)(sourceHeight - row - 1) * sourceStride + byteCount] & edgeMask);
            }
        } else if (lastByte == 0) {
            incoming = (unsigned char)(source[(long)(sourceHeight - row - 1) * sourceStride + 0] >> bitOffset);
            firstMask = (unsigned char)(0xff >> bitOffset);
            lastMask = 0xff;
            if (lastByte + 1 == fullByteCount && endBits != 0)
                lastMask = (unsigned char)(0xff << (8 - endBits));
            edgeMask = firstMask & lastMask;
            destination[(long)(y + row) * destinationStride + (x >> 3) + 0] ^= (unsigned char)(incoming & edgeMask);
        } else {
            incoming = (unsigned char)(source[(long)(sourceHeight - row - 1) * sourceStride + 0] >> bitOffset);
            edgeMask = (unsigned char)(0xff >> bitOffset);
            destination[(long)(y + row) * destinationStride + (x >> 3) + 0] ^= (unsigned char)(incoming & edgeMask);

            for (byteCount = 1; byteCount < lastByte; ++byteCount) {
                following = 0;
                if (byteCount < sourceStride)
                    following = source[(long)(sourceHeight - row - 1) * sourceStride + byteCount];
                window = (unsigned int)source[(long)(sourceHeight - row - 1) * sourceStride + byteCount - 1] << 8;
                window |= following;
                incoming = (unsigned char)(window >> bitOffset);
                destination[(long)(y + row) * destinationStride + (x >> 3) + byteCount] ^= incoming;
            }

            following = 0;
            if (lastByte < sourceStride)
                following = source[(long)(sourceHeight - row - 1) * sourceStride + lastByte];
            window = (unsigned int)source[(long)(sourceHeight - row - 1) * sourceStride + lastByte - 1] << 8;
            window |= following;
            incoming = (unsigned char)(window >> bitOffset);
            edgeMask = 0xff;
            if (lastByte + 1 == fullByteCount && endBits != 0)
                edgeMask = (unsigned char)(0xff << (8 - endBits));
            destination[(long)(y + row) * destinationStride + (x >> 3) + lastByte] ^=
                (unsigned char)(incoming & edgeMask);
        }
    }
}
