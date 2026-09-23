/* Fill the inclusive endpoint rectangle with the display-specific brush color. */
struct WinRect { int left; int top; int right; int bottom; };
extern unsigned char near displayType;
extern int near clipDC;
extern int far pascal CreateSolidBrush(unsigned long color);
extern int far pascal FillRect(int dc, struct WinRect far *rect, int brush);
extern int far pascal DeleteObject(int object);

void far GBoxFill(int x1, int y1, int x2, int y2, int color)
{
    struct WinRect rect;
    int brush;
    register int colorLo;
    register int colorHi;

    rect.left = x1 < x2 ? x1 : x2;
    rect.top = y1 < y2 ? y1 : y2;
    rect.right = (x1 > x2 ? x1 : x2) + 1;
    rect.bottom = (y1 > y2 ? y1 : y2) + 1;

    if (displayType & 1) {
        if (color & 0x0f) {
            colorHi = 0x00ff; colorLo = 0xffff;
        } else {
            switch (color & 0x70) {
            case 0x00: colorHi = 0; colorLo = 0; break;
            case 0x10: colorHi = 0x0060; colorLo = 0x6060; break;
            case 0x20: colorHi = 0x0080; colorLo = 0x8080; break;
            case 0x30: colorHi = 0x00a0; colorLo = 0xa0a0; break;
            case 0x50: colorHi = 0x00c0; colorLo = 0xc0c0; break;
            case 0x60: colorHi = 0x0020; colorLo = 0x2020; break;
            default: colorHi = 0x00ff; colorLo = 0xffff; break;
            }
        }
    } else {
        colorHi = 0x0100; colorLo = color & 0x0f;
    }

    brush = CreateSolidBrush(((unsigned long)(unsigned short)colorHi << 16) | (unsigned short)colorLo);
    FillRect(clipDC, &rect, brush);
    DeleteObject(brush);
}
