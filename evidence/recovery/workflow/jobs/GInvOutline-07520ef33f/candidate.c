/*
 * GInvOutline: invert a rectangular frame of the given width inside the
 * rectangle (left, top, right, bottom) by inverting four boxes with the
 * same-code-group GInvBox (four-argument box inversion, far via LINK
 * translation): the top band, the bottom band, the left band and the
 * right band, each excluding the corners already covered.  A zero width
 * does nothing.  The compiler keeps the shared coordinate expressions
 * (width, right - width - 1, left + width, bottom - 1) in frame temps and
 * the derived right - width in SI.
 */
extern void far GInvBox(int a, int b, int c, int d);

void far GInvOutline(int left, int top, int right, int bottom, int width)
{
    if (width == 0)
        return;
    GInvBox(left + width, top + width - 1, right - width - 1, top);
    GInvBox(left + width, bottom - width, right - width - 1, bottom - 1);
    GInvBox(left + width - 1, top, left, bottom - 1);
    GInvBox(right - 1, top, right - width, bottom - 1);
}
