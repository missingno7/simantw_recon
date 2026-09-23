/* Fill the normalized inclusive rectangle with the display-specific pattern brush. */
struct WinRect { int left; int top; int right; int bottom; };
extern unsigned char near displayType;
extern int near clipDC;
extern int far pascal CreateSolidBrush(unsigned long color);
extern int far pascal FillRect(int dc, struct WinRect far *rect, int brush);
extern int far pascal DeleteObject(int object);

void far GPatBox(int x1, int y1, int x2, int y2, register int pattern)
{
    struct WinRect rect;
    int brush;
    register int savedPattern;

    savedPattern = pattern;

    rect.left = x2 <= x1 ? x2 : x1;
    rect.top = y2 <= y1 ? y2 : y1;
    rect.right = (x2 >= x1 ? x2 : x1) + 1;
    rect.bottom = (y2 >= y1 ? y2 : y1) + 1;

    if (!(displayType & 1)) {
        brush = CreateSolidBrush(0x01000000L | (unsigned long)(savedPattern & 0x0f));
    } else {
        savedPattern &= 0x70;
        if (savedPattern & 0x0f) {
            brush = CreateSolidBrush(0x00ffffffL);
        } else {
            switch (savedPattern & 0x70) {
            case 0x00: brush = CreateSolidBrush(0x00000000L); break;
            case 0x10: brush = CreateSolidBrush(0x00606060L); break;
            case 0x20: brush = CreateSolidBrush(0x00808080L); break;
            case 0x30: brush = CreateSolidBrush(0x00a0a0a0L); break;
            case 0x50: brush = CreateSolidBrush(0x00c0c0c0L); break;
            case 0x60: brush = CreateSolidBrush(0x00202020L); break;
            default: brush = CreateSolidBrush(0x00ffffffL); break;
            }
        }
    }
    FillRect(clipDC, &rect, brush);
    DeleteObject(brush);
}
