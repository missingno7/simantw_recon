/* R2 use zero termination for row loop */
/* Use the compiler-recognized copy operation once for each packed row. */
extern unsigned char near displayType;
extern void far * far memcpy(void far *, void far *, unsigned int);
void far gr_GetFromBuf(int x, int top, unsigned char far *surface,
                       int surfaceWidth, int bottom, unsigned char far *buffer,
                       int width, int rows)
{
    unsigned char far *destination;
    unsigned char far *source;
    int stride;
    unsigned int rowBytes;
    int remaining;
    if ((displayType & 1) == 0) {
        stride = ((surfaceWidth * 4 + 31) / 32) * 4;
        rowBytes = (width + 1) / 2 + 3;
        source = surface + (bottom - top - 1) * stride + (x >> 1);
        destination = buffer;
        remaining = rows;
        while (remaining != 0) {
            { unsigned char far *d=destination, *s=source; unsigned int n=rowBytes; while(n>0) { *d++=*s++; --n; } }
            source -= stride;
            destination += rowBytes;
            remaining--;
        }
    } else {
        stride = ((surfaceWidth + 31) / 32) * 4;
        rowBytes = (width + 7) / 8;
        source = surface + (bottom - top - 1) * stride + (x >> 3);
        destination = buffer;
        remaining = rows;
        while (remaining > 0) {
            { unsigned char far *d=destination, *s=source; unsigned int n=rowBytes+1; while(n>0) { *d++=*s++; --n; } }
            source -= stride;
            destination += rowBytes + 1;
            remaining--;
        }
    }
}
