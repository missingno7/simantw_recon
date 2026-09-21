/*
 * OpenCasteWindow: open the caste tool window (0x1300).  After the window
 * layout is recalculated, and only while the near modeBitmap handle is
 * still zero, the caste bitmap buffer is allocated: gr_BitMapSize fills a
 * local width/height pair for bitmap 0x120c, one of two BitmapImageSize
 * calls (4 bits per pixel unless displayType bit 0 marks a
 * monochrome-class display, then 1; the compiler merges the two calls and homes the long
 * result in the frame) converts it to a byte count, and the verified three-argument
 * mem_Alloc allocates that plus four bytes under the private literal
 * "castebuf" into the near casteBitmap handle.  The caste controls are
 * then refreshed, object 0x1302 hidden, the window opened and updated, and
 * group 4 of the window hidden.  Same-code-group callees are far (LINK
 * translation); the others are far entries in other code groups.
 */
struct BitmapSize {
    int width;
    int height;
};

extern unsigned char near displayType;
extern int near modeBitmap;
extern unsigned int near casteBitmap;
extern void far win_Recalc(int window);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern long far BitmapImageSize(int width, int height, int depth);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far win_CasteControlChanged(void);
extern void far win_MakeObjInvisible(int object);
extern void far win_Open(int window);
extern void far UpdateCasteWindow(void);
extern void far win_MakeGroupInvisible(int window, int group);

void far OpenCasteWindow(void)
{
    long bytes;
    struct BitmapSize size;

    win_Recalc(0x1300);
    if (modeBitmap == 0) {
        gr_BitMapSize(&size, 0x120c);
        casteBitmap = mem_Alloc((((displayType & 1) == 0)
                                     ? BitmapImageSize(size.width, size.height, 4)
                                     : BitmapImageSize(size.width, size.height, 1)) + 4,
                                1, "castebuf");
    }
    win_CasteControlChanged();
    win_MakeObjInvisible(0x1302);
    win_Open(0x1300);
    UpdateCasteWindow();
    win_MakeGroupInvisible(0x1300, 4);
}
