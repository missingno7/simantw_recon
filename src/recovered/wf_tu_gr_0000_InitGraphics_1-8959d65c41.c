/* Candidate translation unit gr_0000_InitGraphics_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _InitGraphics */

extern int far pascal GetDesktopWindow(void);
extern int far pascal GetDC(int window);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal ReleaseDC(int window, int dc);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far WinPrintf(char far *format, ...);
extern void far db_SetDataBase(char far *text);
extern signed char near displayType;

void far InitGraphics(char far *labels)
{
    int window;
    int dc;
    int detectedType;
    char buffer[100];
    char far * volatile displayNames[11] = {
        "hcega", "mono", "tdyga", "mono", "lcega", "mono",
        "l256", "mono", "hcega", "mwin", "winga"
    };

    if ((unsigned char)displayType == 0xff) {
        window = GetDesktopWindow();
        dc = GetDC(window);
        if (GetDeviceCaps(dc, 12) == 1 &&
            GetDeviceCaps(dc, 14) == 1) {
            ReleaseDC(window, dc);
            detectedType = 9;
        } else {
            ReleaseDC(window, dc);
            detectedType = 10;
        }
        displayType = (unsigned char)detectedType;
    }

    sprintf(buffer, "%s%s", displayNames[displayType], labels);
    WinPrintf("db_SetDataBase: %s\n", buffer);
    db_SetDataBase(buffer);
}

