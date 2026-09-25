/*
 * GLine: draw a one-pixel line from (x1, y1) to (x2, y2) on the clip
 * device context.  On a colour display the pen colour is the palette
 * index of the low four colour bits (PALETTEINDEX, 0x01000000 | index,
 * formed as a long with the high byte set); on a monochrome-class display
 * (displayType bit 0) bit 6 of the colour selects white (0x00ffffff) or
 * black.  The pen is created (GDI CreatePen), selected into clipDC, the
 * line is drawn with MoveTo/LineTo, the previous object is restored and
 * the pen deleted.  All are Pascal imports; clipDC is the near DC handle.
 */
extern unsigned char near displayType;
extern int near clipDC;
extern int far pascal CreatePen(int style, int width, unsigned long color);
extern int far pascal SelectObject(int dc, int object);
extern unsigned long far pascal MoveTo(int dc, int x, int y);
extern int far pascal LineTo(int dc, int x, int y);
extern int far pascal DeleteObject(int handle);

void far GLine(int x1, int y1, int x2, int y2, int color)
{
    int pen;
    int old;

    if (!(displayType & 1))
        pen = CreatePen(0, 1, (long)(color & 0xf) | 0x01000000L);
    else if (color & 0x40)
        pen = CreatePen(0, 1, 0x00ffffffL);
    else
        pen = CreatePen(0, 1, 0L);
    old = SelectObject(clipDC, pen);
    MoveTo(clipDC, x1, y1);
    LineTo(clipDC, x2, y2);
    SelectObject(clipDC, old);
    DeleteObject(pen);
}
