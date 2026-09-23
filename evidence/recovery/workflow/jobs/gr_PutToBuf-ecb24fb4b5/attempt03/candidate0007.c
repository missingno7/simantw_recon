/* Transfer packed buffer rows onto a GR surface using the current display mode. */
extern unsigned char near displayType;
extern void far * far memcpy(void far *, void far *, unsigned int);
void far gr_PutToBuf(int x, int top, unsigned char far *surface,
                     int surfaceWidth, int bottom, unsigned char far *buffer,
                     int width, int rows)
{
    unsigned char far *destination;
    unsigned char far *source;
    int stride;
    unsigned int rowBytes;
    int remaining;
    int col;
    if ((displayType & 1) == 0) {
        stride = ((surfaceWidth * 4 + 31) / 32) * 4;
        rowBytes = (width + 1) / 2 + 3;
        destination = surface + (bottom - top - 1) * stride + (x >> 1);
        source = buffer;
        remaining = rows;
        while (remaining > 0) {
            {
                unsigned char far *d = destination;
                unsigned char far *s = source;
                for (col = 0; col < rowBytes; col++)
                    *d++ = *s++;
            }
            destination -= stride;
            source += rowBytes;
            remaining--;
        }
    } else {
        stride = ((surfaceWidth + 31) / 32) * 4;
        rowBytes = (width + 7) / 8;
        destination = surface + (bottom - top - 1) * stride + (x >> 3);
        source = buffer;
        remaining = rows;
        while (remaining > 0) {
            for (col = 0; col < rowBytes; col++)
                destination[col] = source[col];
            destination -= stride;
            source += rowBytes;
            remaining--;
        }
    }
}
