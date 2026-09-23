/* Buffer-to-surface transfer; mode 1 uses four-bit groups, mode 0 uses one-bit rows. */
extern unsigned char near displayType;
void far gr_GetFromBuf(int x, int top, unsigned char far *surface,
                       int surfaceWidth, int bottom, unsigned char far *buffer,
                       int width, int rows)
{
    unsigned char far *destination;
    unsigned char far *source;
    int stride;
    int rowBytes;
    int remaining;
    int col;
    if ((displayType & 1) == 0) {
        stride = (((surfaceWidth << 2) + 31) >> 5) << 2;
        rowBytes = ((width + 2) >> 1) + 3;
        destination = surface + (bottom - top - 1) * stride + (x >> 1);
        source = buffer + rowBytes;
        remaining = rows;
        while (remaining > 0) {
            for (col = 0; col < (rowBytes >> 1); col++)
                ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
            if (rowBytes & 1)
                destination[rowBytes - 1] = source[rowBytes - 1];
            destination -= stride;
            source += rowBytes;
            remaining--;
        }
    } else {
        stride = ((surfaceWidth + 31) >> 5) << 2;
        rowBytes = (width + 7) >> 3;
        destination = surface + (bottom - top - 1) * stride + (x >> 3);
        source = buffer + rowBytes;
        remaining = rows;
        while (remaining > 0) {
            for (col = 0; col < (rowBytes >> 1); col++)
                ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
            if (rowBytes & 1)
                destination[rowBytes - 1] = source[rowBytes - 1];
            destination -= stride;
            source += rowBytes;
            remaining--;
        }
    }
}
