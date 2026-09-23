/*
 * DrawCastePopUp: evidence-backed working reconstruction.  The target opens
 * the 0x1700 popup, measures decimal glyph widths, prints paired caste
 * population values from CastePopB/CastePopR, redraws the value bars, then
 * runs the held-button/event loop until the popup closes.
 */
struct WinRect { int left, top, right, bottom; };
extern int far GamePaused;
extern int far LessonTemp;
extern int near rootWnd;
extern int near foreColor;
extern int near CastePopB[];
extern int near CastePopR[];
extern void far SetPause(int pause);
extern int far GetClientRect(int window, struct WinRect far *rect);
extern void far win_GetObjRect(int object, struct WinRect far *rect);
extern int far win_LockWin(int window);
extern void far win_UnlockWin(int window);
extern int far win_Open(int window);
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
    struct WinRect popup;
    int i;
    int ch;
    int digitWidth;
    int fontHeight;
    int x;
    int y;
    int maxBlue;
    int maxRed;
    int blueValue;
    int redValue;
    char text[32];

    SetPause(1);
    LessonTemp = 1;
    GetClientRect(rootWnd, &client);
    win_GetObjRect(0x2201, &popup);
    win_LockWin(0x1700);
    win_Open(0x1700);
    MySetCapture(0x1700);
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
    maxBlue = 0;
    maxRed = 0;
    for (i = 0; i < 6; ++i) {
        if (CastePopB[i] > maxBlue)
            maxBlue = CastePopB[i];
        if (CastePopR[i] > maxRed)
            maxRed = CastePopR[i];
    }
    MSClipStart(0x1700);
    for (i = 0; i < 6; ++i) {
        x = popup.left + i * digitWidth;
        y = popup.top + i * fontHeight;
        blueValue = CastePopB[i];
        redValue = CastePopR[i];
        win_SetColorFromObjNum(0x1703);
        sprintf(text, "%d", blueValue);
        font_PrintStr(x, y, text);
        if (blueValue != 0)
            GBoxFill(popup.left, y, popup.right, y + fontHeight, foreColor);
        win_SetColorFromObjNum(0x1704);
        sprintf(text, "%d", redValue);
        font_PrintStr(x, y + fontHeight, text);
        if (redValue != 0)
            GBoxFill(popup.left, y + fontHeight, popup.right, y + 2 * fontHeight, foreColor);
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
    SetPause(GamePaused);
}
