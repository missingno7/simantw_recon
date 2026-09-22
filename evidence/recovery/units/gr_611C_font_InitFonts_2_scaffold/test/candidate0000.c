/* Candidate translation unit gr_611C_font_InitFonts_2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _font_InitFonts, _font_PrintStr
 * SCAFFOLDED: unclaimed members _font_SetFont are stand-ins in POOLSTUB_TEXT (pool order only, never compared). */

struct OutBuffer {
    int width;
    int height;
    void far *image;
};
extern struct OutBuffer far out_buffer;
static void far * __based(__segname("SIMANT_DATA_GROUP")) fonts[10];
static unsigned char __based(__segname("SIMANT_DATA_GROUP")) fontBuffer[1288];
extern void far * far font_ReadFont(char far *name);
struct StrPos {
    int x;
    int y;
};
extern void far * near curFontPtr;
#define FONTARG void far *font
#define FONTTEST curFontPtr == 0
#define FONTPASS curFontPtr
extern struct StrPos far lastStrPos;
extern void far GPutStr(int x, int y, char far *text);
extern void far font_MakeImage(char far *text, int mode, FONTARG);
extern void far GPutImgS(int x, int y, void far *image, int width, int height, int mode);

extern int far Dx8;  /* scaffold reference for pool word C16A (segment 8, SEGMENT_REPRESENTATIVE) */

void far pool_stub_font_SetFont(void);

#pragma alloc_text(POOLSTUB_TEXT, pool_stub_font_SetFont)

/* SCAFFOLD, not recovered source: stand-in for the unclaimed member _font_SetFont.
 * It only reproduces the object's selector-pool allocation order for the
 * words C16A; its code is compiled into the reserved
 * segment POOLSTUB_TEXT, which the matcher never compares or credits. */
void far pool_stub_font_SetFont(void)
{
    volatile int t;

    t = Dx8;
}

void far font_InitFonts(void)
{
    out_buffer.image = fontBuffer;
    fonts[0] = font_ReadFont("font1");
    fonts[1] = font_ReadFont("font2");
    fonts[2] = font_ReadFont("font3");
    fonts[3] = font_ReadFont("font4");
    fonts[4] = font_ReadFont("font5");
    fonts[5] = font_ReadFont("font6");
}

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

