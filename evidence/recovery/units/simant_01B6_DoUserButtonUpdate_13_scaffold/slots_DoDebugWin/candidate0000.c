/* Candidate translation unit simant_01B6_DoDebugWin_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _DoDebugWin */

static long near lastTick = -1;
static long near frames = 0;
static long near total = 0;
static char near debugFormat[] = "Ave Length: %lu Speed: %lu";
extern int near win_hwnd[];
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
            MSClipStart(win_hwnd[28]);
            font_SetFont(2);
            win_PrintfAtObj(0x1c03, debugFormat, total / frames, 60000L / (total / frames));
            font_SetFont(0);
            MSClipEnd();
        }
    }
    lastTick = GetTickCount();
}

