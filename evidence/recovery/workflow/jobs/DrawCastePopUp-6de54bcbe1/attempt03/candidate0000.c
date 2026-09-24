/*
 * DrawCastePopUp: target-grounded working draft. The HWND passed to the
 * capture and clip helpers is win_hwnd[23] (DGROUP base 0xbca6, operand
 * 0xbcd4). The target measures digits, normalizes the bars against the
 * largest population among caste entries 1..5, draws two colony rows, then
 * handles events until the held button is released or window 0x1700 closes.
 */
struct WinRect { int left, top, right, bottom; };
extern int far GamePaused;
extern int far LessonTemp;
extern int near rootWnd;
extern int near _foreColor;
extern int near win_hwnd[];
extern int near CastePopB[];
extern int near CastePopR[];
static char countFormatBlue[3] = "%d";
static char countFormatRed[3] = "%d";
extern void far SetPause(int pause);
extern int far pascal GetClientRect(int window, struct WinRect far *rect);
extern int far pascal GetSystemMetrics(int index);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern int far win_LockWin(int window);
extern void far win_UnlockWin(int window);
extern int far win_Open(int window, ...);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far ButtonHeldInit(void);
extern int far ButtonHeld(void);
extern int far win_Events(void);
extern int far win_IsWinOpen(int window);
extern void far win_Close(int window);
extern void far font_SetFont(int font);
extern int far font_CharWidth(int character);
extern int far font_FontHeight(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern void far win_SetColorFromObjNum(int objectNumber);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far font_PrintStr(int x, int y, char far *text);
extern void far GBoxFill(int left, int top, int right, int bottom, int color);

void far DrawCastePopUp(void)
{
    struct WinRect client;
    struct WinRect sourceRect;
    struct WinRect popup;
    int savedPause;
    int i;
    int ch;
    int digitWidth;
    int fontHeight;
    int x;
    int y;
    int maxPop;
    int blueWidth;
    int redWidth;
    int bluePop;
    int redPop;
    char text[32];

    savedPause = GamePaused;
    SetPause(1);
    LessonTemp = 1;
    if (/* target's two-word popup placement state */ 1) {
        GetClientRect(rootWnd, &client);
        win_GetObjRect(0x2201, &sourceRect);
        win_LockWin(0x1700);
        win_Open(0x1700, sourceRect.left, 0);
        win_UnlockWin(0x1700);
    } else {
        win_Open(0x1700);
    }
    MySetCapture(win_hwnd[23]);
    ButtonHeldInit();
    win_GetObjRect(0x1702, &popup);
    font_SetFont(2);
    digitWidth = 0;
    for (ch = '0'; ch <= '9'; ++ch) {
        i = font_CharWidth(ch);
        if (i > digitWidth)
            digitWidth = i;
    }
    fontHeight = font_FontHeight();
    maxPop = 1;
    for (i = 1; i < 6; ++i) {
        if (CastePopB[i] > maxPop)
            maxPop = CastePopB[i];
        if (CastePopR[i] > maxPop)
            maxPop = CastePopR[i];
    }
    MSClipStart(win_hwnd[23]);
    for (i = 0; i < 6; ++i) {
        x = popup.left + 2 + digitWidth * 4;
        y = popup.top + i * fontHeight;
        bluePop = CastePopB[i];
        redPop = CastePopR[i];
        blueWidth = (int)(((long)bluePop * (popup.right - x)) / maxPop);
        redWidth = (int)(((long)redPop * (popup.right - x)) / maxPop);
        win_SetColorFromObjNum(0x1703);
        sprintf(text, countFormatBlue, bluePop);
        font_PrintStr(popup.left, y, text);
        if (i != 0 && blueWidth != 0)
            GBoxFill(x, y, x + blueWidth, y + fontHeight, _foreColor);
        win_SetColorFromObjNum(0x1704);
        sprintf(text, countFormatRed, redPop);
        font_PrintStr(popup.left, y + fontHeight, text);
        if (i != 0 && redWidth != 0)
            GBoxFill(x, y + fontHeight, x + redWidth, y + 2 * fontHeight, _foreColor);
    }
    MSClipEnd();
    font_SetFont(0);
    ButtonHeldInit();
    while (win_Events() != 0) {
        if (!win_IsWinOpen(0x1700))
            break;
        if (!ButtonHeld())
            break;
    }
    MyReleaseCapture();
    win_Close(0x1700);
    SetPause(savedPause);
}
