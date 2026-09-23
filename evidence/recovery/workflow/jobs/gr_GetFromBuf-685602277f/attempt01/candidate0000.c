/*
 * Copy a rectangular buffer into a GR surface. In 4-pixel mode each row
 * uses a four-byte aligned packed stride and two pixels per byte; otherwise
 * rows use 32-bit alignment and eight pixels per byte. The destination walks
 * upward through the surface while source rows advance through the buffer.
 */
extern unsigned char near displayType;

void far gr_GetFromBuf(int x, int top, unsigned char far *surface,
                       int surfaceWidth, int bottom, unsigned char far *buffer,
                       int width, int rows)
{
    unsigned char far *destination;
    unsigned char far *source;
    int stride;
    int rowBytes;
    int row;
    int col;

    if (displayType & 1) {
        stride = (((surfaceWidth << 2) + 31) >> 5) << 2;
        rowBytes = ((width + 2) >> 1) + 3;
        destination = surface + (bottom - top - 1) * stride + (x >> 1);
        source = buffer + rowBytes;
        for (row = 0; row < rows; row++) {
            for (col = 0; col < (rowBytes >> 1); col++)
                ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
            if (rowBytes & 1)
                destination[rowBytes - 1] = source[rowBytes - 1];
            destination -= stride;
            source += rowBytes;
        }
    } else {
        stride = ((surfaceWidth + 31) >> 5) << 2;
        rowBytes = (width + 7) >> 3;
        destination = surface + (bottom - top - 1) * stride + (x >> 3);
        source = buffer + rowBytes;
        for (row = 0; row < rows; row++) {
            for (col = 0; col < (rowBytes >> 1); col++)
                ((unsigned int far *)destination)[col] = ((unsigned int far *)source)[col];
            if (rowBytes & 1)
                destination[rowBytes - 1] = source[rowBytes - 1];
            destination -= stride;
            source += rowBytes;
        }
    }
}
