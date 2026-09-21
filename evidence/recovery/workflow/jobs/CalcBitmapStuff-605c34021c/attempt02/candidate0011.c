/*
 * CalcBitmapStuff: clip a bitmap placed at (x, y) with the given width and
 * height against a destination that is limitWidth by limitHeight.  For
 * each axis, a negative position yields a source offset of -position and
 * the full extent; otherwise the offset is zero and the extent is cut to
 * the limit when position + extent overruns it.  All four results are
 * returned through far pointers.
 */
#define EXT unsigned
#define OVER(pos, ext, lim) ((ext) + (pos) > (lim))
#define CLIP(out, pos, ext, lim) if (OVER(pos, ext, lim)) { lim -= pos; *out = lim; } else *out = ext;

void far CalcBitmapStuff(EXT limitHeight, EXT limitWidth, EXT height, EXT width,
                         int x, int y, int far *xOffset, EXT far *outWidth,
                         int far *yOffset, EXT far *outHeight)
{
    if (x < 0) {
        *xOffset = -x;
        *outWidth = width;
    } else {
        *xOffset = 0;
        CLIP(outWidth, x, width, limitWidth)
    }
    if (y < 0) {
        *yOffset = -y;
        *outHeight = height;
    } else {
        *yOffset = 0;
        CLIP(outHeight, y, height, limitHeight)
    }
}
