/* Fill the inclusive endpoint rectangle with the display-specific brush color. */
struct WinRect { int left; int top; int right; int bottom; };
extern unsigned char near displayType;
extern int near clipDC;
extern int far pascal CreateSolidBrush(unsigned long color);
extern int far pascal FillRect(int dc, struct WinRect far *rect, int brush);
extern int far pascal DeleteObject(int object);

static __inline unsigned long MonoBrushColor(int color)
{
    switch (color & 0x70) {
    case 0x00: return 0x00000000L;
    case 0x10: return 0x00606060L;
    case 0x20: return 0x00808080L;
    case 0x30: return 0x00a0a0a0L;
    case 0x50: return 0x00c0c0c0L;
    case 0x60: return 0x00202020L;
    default: return 0x00ffffffL;
    }
}

void far GBoxFill(int x1, int y1, int x2, int y2, int color)
{
    struct WinRect rect;
    int brush;

    rect.left = x1 < x2 ? x1 : x2;
    rect.top = y1 < y2 ? y1 : y2;
    rect.right = (x1 > x2 ? x1 : x2) + 1;
    rect.bottom = (y1 > y2 ? y1 : y2) + 1;

    brush = CreateSolidBrush((displayType & 1)
        ? ((color & 0x0f) ? 0x00ffffffL : MonoBrushColor(color))
        : (0x01000000L | (unsigned long)(color & 0x0f)));

    FillRect(clipDC, &rect, brush);
    DeleteObject(brush);
}
