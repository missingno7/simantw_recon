/*
 * DoDebugWin: frame-rate display.  Each call counts a frame and adds the
 * tick delta since the previous call (GetTickCount, USER.13) to the total;
 * the first call, with the last tick still -1, only records the tick.
 * Every fifth frame the average frame length and the derived speed
 * (60000 / average) are printed at object 0x1c03 inside a mouse-clipped
 * section with font 2.  The tick, frame and total counters and the
 * format string are private initialized data (-1, 0, 0, "Ave Length:
 * %lu Speed: %lu").  The clip window handle is an unnamed DGROUP word.
 */
static long near lastTick = -1;
static long near frames = 0;
static long near total = 0;
static char near debugFormat[] = "Ave Length: %lu Speed: %lu";
static unsigned near debugWindow;

extern unsigned long far pascal GetTickCount(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far font_SetFont(int font);
extern void far win_PrintfAtObj(int object, char far *format, ...);

void far DoDebugWin(void)
{
    if (lastTick != -1) {
        frames++;
        total += GetTickCount() - lastTick;
        if (frames % 5 == 0) {
            MSClipStart(debugWindow);
            font_SetFont(2);
            win_PrintfAtObj(0x1c03, debugFormat, total / frames, 60000L / (total / frames));
            font_SetFont(0);
            MSClipEnd();
        }
    }
    lastTick = GetTickCount();
}
