/*
 * Build a framed, inverted mono bitmap for a multi-line balloon.  The glyph
 * block, diagnostic and allocator tag are one initialized private record in
 * the executable's data image.
 */
struct BalloonAssets {
    unsigned char glyph[11][16];
    char fontError[23];
    char allocName[8];
};

static struct BalloonAssets balloonAssets = {
    {
        { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0x0f,0x3f,0x3f,0x7f,0x3f,0x7f },
        { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0xf0,0xfc,0xfc,0xfe,0xfc,0xfe },
        { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
        { 0xfc,0xfe,0xfc,0xfe,0xfc,0xfe,0xfc,0xfe,0xfc,0xfe,0xfc,0xfe,0xfc,0xfe,0xfc,0xfe },
        { 0x3f,0x7f,0x3f,0x7f,0x3f,0x7f,0x3f,0x7f,0x3f,0x7f,0x3f,0x7f,0x3f,0x7f,0x3f,0x7f },
        { 0x3f,0x7f,0x3f,0x7f,0x0f,0x3f,0x00,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
        { 0xfc,0xfe,0xfc,0xfe,0xf0,0xfc,0x00,0xf0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
        { 0xff,0xff,0xff,0xff,0xff,0xff,0x00,0xff,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 },
        { 0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff },
        { 0xff,0xff,0xff,0xff,0xff,0xff,0x3e,0xff,0x0e,0x1f,0x06,0x0f,0x02,0x07,0x00,0x02 },
        { 0xff,0xff,0xff,0xff,0xff,0xff,0x7c,0xff,0x70,0xf8,0x60,0xf0,0x40,0xe0,0x00,0x40 }
    },
    "BAD font in MakeBaloon",
    "balloon"
};

struct FarMask {
    int type;
    unsigned char flag;
    unsigned char pad[5];
    int width;
    int height;
};

extern unsigned char near displayType;
extern void far * far curFontPtr;
extern int unsigned strlen(const char far *text);
extern char far *far strcpy(char far *dst, const char far *src);
extern void far *malloc(unsigned int size);
extern void far free(void far *block);
extern void Punt(char far *message, ...);
extern volatile int near font_StringWidth(volatile char far *text);
extern int far _font_FontHeight(void far *font);
extern void far *font_MakeImage(char far *text, int mode, void far *font);
extern void far CopyChar(void far *glyph, int x, int y, void far *surface);
extern void far CopyCharRep(void far *glyph, int x, int y,
                            void far *surface, int count);
extern void far MoveTextToBalloon(void far *bitmap, void far *surface,
                                  int x, int y);
extern void far ClearBuffer(void far *destination, unsigned int count);
extern unsigned int mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int mem_Unlock(unsigned int handle);
extern void far exchange(void far *destination, void far *source,
                        unsigned int count);
extern void ConvertMonoMaskToColor(unsigned int handle);
extern unsigned int ConvertMonoMaskToTandy(unsigned int handle);

unsigned int far MakeBalloon(char far *text, int mode)
{
    char far *copy;
    char far *lines[10];
    char far * near *lineSlot;
    char far * near *firstSlot;
    struct FarMask far *mask;
    unsigned char far *surface;
    unsigned char far *bottomSurface;
    unsigned char far *frameSurface;
    unsigned char far *pixels;
    unsigned char far *pixelsNext;
    unsigned long allocationBytes;
    unsigned int handle;
    int cols;
    int rowBytes;
    unsigned int clearBytes;
    int lineCount;
    int widest;
    int width;
    int maskWidth;
    int maskHeight;
    int bottom;
    int fontHeight;
    int line;
    int x;
    int y;
    int i;

    copy = (char far *)malloc(0x12c);

    if (curFontPtr == 0)
        Punt(balloonAssets.fontError);

    strcpy(copy, text);

    lines[0] = copy;
    i = 0;
    lineCount = 0;
    if (lines[0][0] != 0) {
        lineSlot = &lines[0];
        firstSlot = &lines[0];
        while (lineSlot < &lines[10]) {
            if ((*firstSlot)[i] == '\\' && (*firstSlot)[i + 1] == 'n') {
                lines[0][i] = 0;
                ++lineCount;
                ++i;
                *++lineSlot = lines[0] + i + 1;
            }
            ++i;
            if (lines[0][i] == 0)
                break;
        }
    }
    widest = 0;
    for (line = 0; line <= lineCount; ++line) {
        if (font_StringWidth(lines[line]) > widest)
            widest = font_StringWidth(lines[line]);
    }

    fontHeight = _font_FontHeight(curFontPtr);
    maskHeight = fontHeight * (lineCount + 1) + 16;
    maskWidth = (widest + 16 + 7) & 0xfff8;
    clearBytes = (unsigned int)(((maskHeight + 1) * maskWidth) / 4);
    allocationBytes = (unsigned long)(unsigned int)(clearBytes + 12);
    handle = mem_Alloc(allocationBytes, 1, balloonAssets.allocName);

    mask = (struct FarMask far *)mem_Lock(handle);
    surface = (unsigned char far *)mask + 8;
    ClearBuffer(surface, clearBytes);
    mask->width = maskWidth;
    mask->height = maskHeight;
    bottom = maskHeight - 8;
    cols = (maskWidth >> 3) - 2;

    CopyChar(balloonAssets.glyph[0], 0, 0, surface);
    CopyCharRep(balloonAssets.glyph[2], 1, 0, surface,
                cols);
    CopyChar(balloonAssets.glyph[1], cols + 1, 0, surface);

    for (y = 8; y < bottom; y += 8) {
        frameSurface = (unsigned char far *)mask + 8;
        CopyCharRep(balloonAssets.glyph[8], 1, y, frameSurface, cols);
        CopyChar(balloonAssets.glyph[4], 0, y, frameSurface);
        CopyChar(balloonAssets.glyph[3], cols + 1, y, frameSurface);
    }

    for (line = 0; line <= lineCount; ++line) {
        fontHeight = _font_FontHeight(curFontPtr);
        y = fontHeight * line + 6;
        MoveTextToBalloon(font_MakeImage(lines[line],
                                        (unsigned int)(-font_StringWidth(lines[line]) & 6) >> 1,
                                        curFontPtr),
                          (unsigned char far *)mask + 8, 1, y);
    }

    bottomSurface = (unsigned char far *)mask + 8;
    fontHeight = _font_FontHeight(curFontPtr);
    y = fontHeight * (lineCount + 1) + 6;
    CopyChar(balloonAssets.glyph[6], cols + 1, y, bottomSurface);
    CopyChar(balloonAssets.glyph[5], 0, y, bottomSurface);
    CopyCharRep(balloonAssets.glyph[7], 1, y, bottomSurface,
                cols);

    if (mode == 0)
        CopyChar(balloonAssets.glyph[9], cols, y - 1, bottomSurface);
    else
        CopyChar(balloonAssets.glyph[10], 1, 1, bottomSurface);

    --mask->height;
    if (lineCount < 1)
        --mask->height;

    free(copy);

    rowBytes = mask->width / 8;

    if (displayType == 2 || displayType == 10) {
        mem_Unlock(handle);
        return ConvertMonoMaskToTandy(handle);
    }

    if ((displayType & 1) == 0) {
        mem_Unlock(handle);
        ConvertMonoMaskToColor(handle);
        return handle;
    }

    pixels = (unsigned char far *)mask + 12;
    i = mask->height;
    while (i > 0) {
        pixelsNext = pixels + rowBytes;
        exchange(pixels, pixelsNext, rowBytes);
        pixels = pixelsNext;
        pixels += rowBytes;
        --i;
    }
    mask->type = 3;
    mask->flag = 1;
    mem_Unlock(handle);
    return handle;
}
