/*
 * CalcBitmapStuff: clip a bitmap placed at (x, y) with the given width and
 * height against a destination that is limitWidth by limitHeight.  For
 * each axis, a negative position yields a source offset of -position and
 * the full extent; otherwise the offset is zero and the extent is cut to
 * the limit when position + extent overruns it.  All four results are
 * returned through far pointers.
 */
void far CalcBitmapStuff(int limitHeight, int limitWidth, int height, int width,
                         int x, int y, int far *xOffset, int far *outWidth,
                         int far *yOffset, int far *outHeight)
{
    if (x < 0) {
        *xOffset = -x;
        *outWidth = width;
    } else {
        *xOffset = 0;
        if (x + width > limitWidth)
            *outWidth = limitWidth - x;
        else
            *outWidth = width;
    }
    if (y < 0) {
        *yOffset = -y;
        *outHeight = height;
    } else {
        *yOffset = 0;
        if (y + height > limitHeight)
            *outHeight = limitHeight - y;
        else
            *outHeight = height;
    }
}
