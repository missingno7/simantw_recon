/* Refresh map, yard, edit, and status windows from their current modes and timers. */
extern int far MapMode[];
extern int far UDcntr;
extern int far UDMapFlip;
extern int near YardMode;
extern long far mapMessage;
extern long far editMessage;
extern long far TickCount(void);
extern int far WaitedEnough(long far *timer, int delay);
extern int far win_IsWinOpen(int window);
extern int far win_IsWinInFront(int window);
extern void far DrawMap(void);
extern void far DrawMapData(void);
extern void far DrawYardData(void);
extern void far UpdateYard(void);
extern void far UpdateEdit(void);
extern void far UpdateYardMessage(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far font_SetFont(int font);
extern int far ConvColor(int color);
extern void far win_PrintfAtObj(int object, long format);
extern void far win_FillObjRect(int object, int color);
extern int near win_hwnd[];
static unsigned char yardDrawPending;
static unsigned char editDrawPending;
static long updateStamp;

void far UpdateWindows(void)
{
    int far * volatile flipState;
    int far * volatile modeState;
    int flip;

    modeState = &MapMode[2];
    if (*modeState == 0)
        goto mapWork;
    if (*modeState == 1)
        goto mapWork;
    if (*modeState == 2) {
        if (UDcntr & 1) {
            if (*modeState != 3)
                goto yardWork;
            if (UDcntr & 3)
                goto yardWork;
        }
    } else if (UDcntr & 3) {
        goto yardWork;
    }

mapWork:
    if (!win_IsWinOpen(0x100)) {
        DrawMapData();
    } else {
        flipState = &UDMapFlip;
        if (*flipState < 0 || win_IsWinInFront(0x100) || *modeState == 3) {
            DrawMap();
            *flipState = 0;
        } else {
            flip = *(unsigned char far *)flipState;
            flip &= 1;
            if (flip == 1)
                DrawMap();
            else
                DrawMapData();
            *(unsigned char far *)flipState ^= 1;
        }
    }

yardWork:
    if (win_IsWinOpen(0x1900)) {
        if (WaitedEnough(&updateStamp, 0x48) && YardMode >= 2) {
            DrawYardData();
            if (YardMode > 1)
                UpdateYardMessage();
        }
        if (!win_IsWinInFront(0x1900) && !(yardDrawPending & 1)) {
            DrawYardData();
            yardDrawPending ^= 1;
        }
    } else {
        UpdateYard();
        yardDrawPending = 0;
    }

    if (win_IsWinOpen(0) && !win_IsWinInFront(0) && !(editDrawPending & 1))
        editDrawPending ^= 1;
    else
        UpdateEdit();

    if (win_IsWinOpen(0x2200)) {
        MSClipStart(win_hwnd[42]);
        if (WaitedEnough(&updateStamp, 0x48)) {
            mapMessage = 0L;
            editMessage = 0L;
        }
        if (mapMessage != 0L || editMessage != 0L) {
            font_SetFont(2);
            win_PrintfAtObj(0x221f, mapMessage);
            font_SetFont(0);
        } else {
            win_FillObjRect(0x221f, ConvColor(12));
        }
        MSClipEnd();
    }
    UDcntr = (UDcntr + 1) & 0x3f;
}








