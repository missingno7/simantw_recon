/*
 * font_PrintStr: draw a string at (x, y) with the current font.  An empty
 * string only records the far lastStrPos.  Without a current font the
 * string goes through GPutStr.  Otherwise font_MakeImage renders it into
 * the far out_buffer (width, height, then the far image pointer) which
 * GPutImgS draws in mode 1, and lastStrPos advances by the image width.
 */
struct OutBuffer {
    int width;
    int height;
    void far *image;
};

struct StrPos {
    int x;
    int y;
};

extern void far * near curFontPtr;
#define FONTARG void far *font
#define FONTTEST curFontPtr == 0
#define FONTPASS curFontPtr
extern struct OutBuffer far out_buffer;
extern struct StrPos far lastStrPos;

extern void far GPutStr(int x, int y, char far *text);
extern void far font_MakeImage(char far *text, int mode, FONTARG);
extern void far GPutImgS(int x, int y, void far *image, int width, int height, int mode);

void far font_PrintStr(int x, int y, char far *text)
{
    if (*text == 0) {
        lastStrPos.x = x;
        lastStrPos.y = y;
        return;
    }
    if (FONTTEST) {
        GPutStr(x, y, text);
        return;
    }
    font_MakeImage(text, 0, FONTPASS);
    GPutImgS(x, y, out_buffer.image, out_buffer.width, out_buffer.height, 1);
    lastStrPos.x = x + out_buffer.width;
    lastStrPos.y = y;
}
