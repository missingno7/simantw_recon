/* Candidate unit gr:1560 (GSetSmallFont, GSetBigFont) composed from the exact candidates; internal evidence id. */
typedef struct {
    short tmHeight, tmAscent, tmDescent, tmInternalLeading, tmExternalLeading;
    short tmAveCharWidth, tmMaxCharWidth, tmWeight, tmOverhang;
    short tmDigitizedAspectX, tmDigitizedAspectY;
    unsigned char tmFirstChar, tmLastChar, tmDefaultChar, tmBreakChar;
    unsigned char tmItalic, tmUnderlined, tmStruckOut, tmPitchAndFamily, tmCharSet;
}
TEXTMETRIC;
extern int near smallFontH;
extern int near rootWnd;
extern int near clipDC;
extern unsigned char near fontWidth;
extern unsigned char near fontHeight;
static int near savedFont;
static unsigned char near smallAvgWidthByte;
static unsigned char near bigAvgWidthByte;
static unsigned char __based(__segname("PACK")) smallFontHeightByte;
extern int far pascal AddFontResource(char far *filename);
extern long far pascal SendMessage(int hwnd, unsigned int msg, unsigned int wParam, long lParam);
extern int far pascal CreateFont(int height, int width, int escapement, int orientation,
                                  int weight, unsigned char italic, unsigned char underline,
                                  unsigned char strikeOut, unsigned char charSet,
                                  unsigned char outPrecision, unsigned char clipPrecision,
                                  unsigned char quality, unsigned char pitchAndFamily,
                                  char far *faceName);
extern int far pascal GetDC(int hwnd);
extern int far pascal ReleaseDC(int hwnd, int hdc);
extern int far pascal SelectObject(int hdc, int obj);
extern int far pascal GetTextMetrics(int hdc, TEXTMETRIC far *tm);
extern long far pascal SetMapperFlags(int hdc, long flags);
extern int near bigFontH;
static unsigned char __based(__segname("PACK")) bigFontHeightByte;

void far GSetSmallFont(void)
{
    TEXTMETRIC tm;
    int hdc;
    int oldFont;

    if (smallFontH == 0) {
        if (AddFontResource("fontres.fon"))
            SendMessage(-1, 0x1d, 0, 0L);
        smallFontH = CreateFont(8, 8, 0, 0, 0x190, 0, 0, 0, 0, 2, 1, 2, 1, "Gaia8x8");
        hdc = GetDC(rootWnd);
        oldFont = SelectObject(hdc, smallFontH);
        savedFont = oldFont;
        GetTextMetrics(hdc, &tm);
        smallAvgWidthByte = (unsigned char)(tm.tmExternalLeading + tm.tmHeight);
        smallFontHeightByte = (unsigned char)((tm.tmAveCharWidth + tm.tmMaxCharWidth) / 2);
        SetMapperFlags(hdc, 0L);
        SelectObject(hdc, savedFont);
        ReleaseDC(rootWnd, hdc);
        savedFont = 0;
    }
    if (clipDC != 0) {
        SetMapperFlags(clipDC, 0L);
        if (savedFont == 0)
            savedFont = SelectObject(clipDC, smallFontH);
        else
            SelectObject(clipDC, smallFontH);
    }
    fontWidth = smallFontHeightByte;
    fontHeight = smallAvgWidthByte;
}

void far GSetBigFont(void)
{
    TEXTMETRIC tm;
    int hdc;
    int oldFont;

    if (bigFontH == 0) {
        if (AddFontResource("fontres.fon"))
            SendMessage(-1, 0x1d, 0, 0L);
        bigFontH = CreateFont(0xe, 8, 0, 0, 0x190, 0, 0, 0, 0, 2, 1, 2, 1, "Gaia8x14");
        hdc = GetDC(rootWnd);
        oldFont = SelectObject(hdc, bigFontH);
        savedFont = oldFont;
        GetTextMetrics(hdc, &tm);
        bigAvgWidthByte = (unsigned char)(tm.tmExternalLeading + tm.tmHeight);
        bigFontHeightByte = (unsigned char)((tm.tmAveCharWidth + tm.tmMaxCharWidth) / 2);
        SetMapperFlags(hdc, 0L);
        SelectObject(hdc, savedFont);
        ReleaseDC(rootWnd, hdc);
        savedFont = 0;
    }
    if (clipDC != 0) {
        SetMapperFlags(clipDC, 0L);
        if (savedFont == 0)
            savedFont = SelectObject(clipDC, bigFontH);
        else
            SelectObject(clipDC, bigFontH);
    }
    fontWidth = bigFontHeightByte;
    fontHeight = bigAvgWidthByte;
}
