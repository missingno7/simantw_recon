/* Detect the desktop display only when the shared type is uninitialized,
   format the selected display description with the caller's two labels,
   report it, and register the same text with the database layer. */
extern int far pascal GetDesktopWindow(void);
extern int far pascal GetDC(int window);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal ReleaseDC(int window, int dc);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far WinPrintf(char far *text, ...);
extern void far db_SetDataBase(char far *text);
extern unsigned char near displayType;

void far InitGraphics(char far *display, char far *adapter)
{
    int window;
    int dc;
    char buffer[100];
    char far *displayNames[11] = {
        "display 0", "display 1", "display 2", "display 3",
        "display 4", "display 5", "display 6", "display 7",
        "display 8", "monochrome", "color"
    };

    if (displayType == 0xff) {
        window = GetDesktopWindow();
        dc = GetDC(window);
        if (GetDeviceCaps(dc, 12) == 1 &&
            GetDeviceCaps(dc, 14) == 1) {
            ReleaseDC(window, dc);
            displayType = 9;
        } else {
            ReleaseDC(window, dc);
            displayType = 10;
        }
    }

    sprintf(buffer, "%s", displayNames[displayType], display, adapter);
    WinPrintf(buffer);
    db_SetDataBase(buffer);
}
