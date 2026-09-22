/*
 * OpenModeWindow: open the mode tool window (0x1200).  After the window
 * layout is recalculated, and only while the near modeBitmap handle is
 * still zero, the mode bitmap buffer is allocated: gr_BitMapSize fills a
 * local width/height pair for bitmap 0x11f8, one of two BitmapImageSize
 * calls (4 bits per pixel unless displayType bit 0 marks a
 * monochrome-class display, then 1; the compiler merges the two calls and homes the long
 * result in the frame) converts it to a byte count, and the verified three-argument
 * mem_Alloc allocates that plus four bytes under the private literal
 * "modebuf" into the near modeBitmap handle.  The mode controls are
 * then refreshed, object 0x1202 hidden, the window opened and updated, and
 * group 4 of the window hidden.  Same-code-group callees are far (LINK
 * translation); the others are far entries in other code groups.
 */
struct BitmapSize {
    int width;
    int height;
};

extern unsigned char near displayType;
extern unsigned int near modeBitmap;
extern void far win_Recalc(int window);
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern long far BitmapImageSize(int width, int height, int depth);
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far win_ModeControlChanged(void);
extern void far win_MakeObjInvisible(int object);
extern void far win_Open(int window);
extern void far UpdateModeWindow(void);
extern void far win_MakeGroupInvisible(int window, int group);

void far OpenModeWindow(void)
{
    long bytes;
    struct BitmapSize size;

    win_Recalc(0x1200);
    if (modeBitmap == 0) {
        gr_BitMapSize(&size, 0x11f8);
        modeBitmap = mem_Alloc((((displayType & 1) == 0)
                                     ? BitmapImageSize(size.width, size.height, 4)
                                     : BitmapImageSize(size.width, size.height, 1)) + 4,
                                1, "modebuf");
    }
    win_ModeControlChanged();
    win_MakeObjInvisible(0x1202);
    win_Open(0x1200);
    UpdateModeWindow();
    win_MakeGroupInvisible(0x1200, 4);
}
