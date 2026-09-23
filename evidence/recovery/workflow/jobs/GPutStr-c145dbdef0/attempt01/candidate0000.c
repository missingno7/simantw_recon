/* Configure text drawing, output the string, and update the last-string extent. */
extern unsigned int far strlen(char far *text);
extern unsigned char near displayType;
extern unsigned char near monoPat;
extern int near clipDC;
extern int near _backColor;
extern int near _foreColor;
struct StrPos { int x; int y; };
extern struct StrPos far lastStrPos;
extern long far pascal SetBkColor(int dc, unsigned long color);
extern int far pascal SetTextColor(int dc, unsigned long color);
extern int far pascal SetBkMode(int dc, int mode);
extern int far pascal SetMapMode(int dc, int mode);
extern int far pascal SetTextAlign(int dc, int mode);
extern int far pascal TextOut(int dc, int x, int y, char far *text, int count);
extern unsigned long far pascal GetTextExtent(int dc, char far *text, int count);

void far GPutStr(int x, int y, char far *text)
{
    unsigned long extent;
    if (!(displayType & 1)) {
        SetBkColor(clipDC, 0x01000000UL | (unsigned long)(_backColor & 0x0f));
        SetBkColor(clipDC, 0x01000000UL | (unsigned long)(_foreColor & 0x0f));
    } else {
        if (monoPat & 0x80) {
            SetBkColor(clipDC, 0xffff00ffUL);
            SetBkColor(clipDC, 0);
        } else {
            SetBkColor(clipDC, 0);
            SetTextColor(clipDC, 0xffff00ffUL);
        }
        SetBkMode(clipDC, 2);
        SetMapMode(clipDC, 1);
        SetTextAlign(clipDC, 0);
    }
    TextOut(clipDC, x, y, text, strlen(text));
    lastStrPos.y = y;
    extent = GetTextExtent(clipDC, text, strlen(text));
    lastStrPos.x = x + (int)extent;
}

