/*
 * TrapFill draws the four XY vertices of a trapezoid. Normal colors use the
 * display-specific GDI polygon path. In sentinel mode it steps the left and
 * right edges across scanlines; -1 inverts a row, and the color pair chooses
 * the solid or patterned fill. DrawSimColonies supplies the four vertices;
 * InvertPatch passes -1/-1.
 */
struct TrapPoint { int x; int y; };
extern unsigned char near displayType;
extern int near clipDC;
extern int far pascal CreatePen(int style, int width, unsigned long color);
extern int far pascal CreateSolidBrush(unsigned long color);
extern int far pascal GetStockObject(int object);
extern int far pascal SelectObject(int dc, int object);
extern int far pascal Polygon(int dc, struct TrapPoint far *points, int count);
extern int far pascal DeleteObject(int object);
extern unsigned far CreateMonoSolidBrush(int color);
extern void far GSetAttrib(int foreColor, int backColor, int pattern);
extern void far GInvBox(int left, int top, int right, int bottom);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);
extern void far GPatBox(int left, int top, int right, int bottom, unsigned int pattern);

void far TrapFill(struct TrapPoint far *points, int foreColor, int backColor)
{
    int pen;
    int brush;
    int oldPen;
    int oldBrush;
    unsigned long colorRef;

    if (foreColor != -1 && backColor != -1) {
        if (!(displayType & 1)) {
            if (foreColor == backColor) {
                colorRef = 0x01000000L | (foreColor & 0xf);
                pen = CreatePen(0, 1, colorRef);
                brush = CreateSolidBrush(colorRef);
            } else {
                pen = CreatePen(0, 1, 0x01000008L);
                brush = CreateSolidBrush(0x01000008L);
            }
        } else {
            pen = GetStockObject(7);
            brush = CreateMonoSolidBrush(foreColor);
        }

        oldPen = SelectObject(clipDC, pen);
        oldBrush = SelectObject(clipDC, brush);
        Polygon(clipDC, points, 4);
        SelectObject(clipDC, oldPen);
        SelectObject(clipDC, oldBrush);
        DeleteObject(pen);
        DeleteObject(brush);
        return;
    }

    {
        int top = points[0].y;
        int bottom = points[2].y;
        long left = points[0].x;
        long right = points[1].x;
        long leftStep = ((long)points[0].x - points[3].x) / (bottom - top);
        long rightStep = ((long)points[1].x - points[2].x) / (bottom - top);

        if (displayType & 1) {
            foreColor = backColor;
            GSetAttrib(backColor, backColor, backColor);
        }

        while (top < bottom) {
            if (foreColor == -1) {
                GInvBox((int)left, top, (int)right, top + 1);
            } else if (foreColor != backColor) {
                GPatBox((int)left, top, (int)right, top + 1, 0x20);
            } else {
                GBoxFill((int)left, top, (int)right, top + 1, foreColor);
            }
            ++top;
            left -= leftStep;
            right -= rightStep;
        }
    }
}
