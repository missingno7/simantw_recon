/* Read configuration/command-line display and sound switches, choose the
 * installation directories, then initialise the splash screen and windows. */
extern int near musicDevice;
extern char near debugOn;
extern char near mouseBug;
extern unsigned char near displayType;
extern int near rootWnd;
extern int near hInst;
extern int near screenWidth;
extern int near screenHeight;
extern int far match_position[];

extern char far * far usageStr;
extern char far * far notEnoughMemoryStr;
extern char far * far graphicsName;
extern char far * far iniPath;
extern int far iniDrive;
extern char far * far helpFileName;
extern char far helpFile[];
extern int far ReadConfig(void);
extern void mem_Debugging(int value);

extern unsigned long RallocMemoryFree(void);

extern char far * far getenv(const char far *name);
extern int far strcmpi(const char far *left, const char far *right);
extern int far isdigit(int ch);
extern int far pascal LSTRLEN(const char far *text);
extern char far *getcwd(char far *buffer, int maxlen);

extern int far sprintf(char far *buffer, char far *format, ...);
extern unsigned int strlen(const char far *text);
extern char far *strcat(char far *destination, const char far *source);

extern void far WinPrintf(char far *format, ...);

extern void far Punt(char far *message, ...);

extern int far db_SetDataBase(char far *name);

extern void far SetMenuEntries(void);
extern void far LoadTiles(void);
extern void far InitApplicationStuff(void);
extern void InitApplicationWindows(void);

extern int far InitMenu(int option);
extern void InitPalette(void);

extern void far win_SetPalette(int which);
extern int far pascal GetDesktopWindow(void);
extern int far pascal GetDC(int hwnd);
extern int far pascal ReleaseDC(int hwnd, int dc);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far ConvColor(int color);
extern void far GBoxFill(int left, int top, int right, int bottom,
                         int color);
struct BitmapSize { int width; int height; };
extern void far gr_BitMapSize(struct BitmapSize far *size, int bitmap);
extern void far win_DrawBitMap(int x, int y, unsigned int bitmap);

extern void far MSClipStart(int hwnd);
extern void far MSClipEnd(void);
extern long far TickCount(void);
extern int far WaitedEnough(long far *timer, int delay);

extern void RedrawScreen(void);

extern unsigned long mem_Flush(void);

extern unsigned long ralloc_CompressMemory(void);

extern void far exit(int status);

void far IBMInitStuff(char far *commandLine)
{
    char far *env;
    char far *cwd;
    char far *localGraphicsName;
    char far *displaySuffix[11];
    char message[100];
    unsigned int bitmapTable[11] = {
        0x6d60, 0, 0x6d61, 0x6d62, 0x6d61, 0x6d62,
        0, 0x6d62, 0x6d63, 0x6d62, 0x6d63
    };
    char option;
    struct BitmapSize bitmapSize;
    int code;
    int i;
    long start;

    musicDevice = -1;
    ReadConfig();

    i = 0;
    if (commandLine != 0 && LSTRLEN(commandLine) > 0) {
    while (commandLine[i] != 0) {
        while (commandLine[i] == ' ' || commandLine[i] == '\t')
            i++;
        if (commandLine[i] == 0)
            break;
        if (commandLine[i] != '-' && commandLine[i] != '/') {
            while (commandLine[i] != 0 && commandLine[i] != ' ' &&
                   commandLine[i] != '\t')
                i++;
            continue;
        }
        i++;
        option = commandLine[i++];
        if (option == 'd' || option == 'D') {
            switch (commandLine[i]) {
            case 'C': displayType = 6; break;
            case 'E': displayType = (char)-1; break;
            case 'H': displayType = 0; break;
            case 'M': displayType = 3; break;
            case 'P': displayType = 5; break;
            case 'R': displayType = 2; break;
            case 'T': displayType = 8; break;
            case 'V': displayType = 10; break;
            case 'W': displayType = 4; break;
            case 'X': displayType = 7; break;
            case 'Y': displayType = 9; break;
            default: break;
            }
            while (commandLine[i] != 0 && commandLine[i] != ' ' &&
                   commandLine[i] != '\t')
                i++;
        } else if (option == 'm' || option == 'M') {
            if (isdigit(commandLine[i])) {
                musicDevice = commandLine[i] - '0';
                i++;
            }
        } else if (option == 'g' || option == 'G') {
            debugOn = commandLine[i] == '1' || commandLine[i] == 'Y' ||
                      commandLine[i] == 'y';
            mem_Debugging(debugOn);
        } else if (option == 'b' || option == 'B') {
            mouseBug = 1;
        } else if (option == '?') {
            WinPrintf(usageStr);
            exit(4);
        }
    }
    }

    env = getenv("BUG");
    if (env != 0) {
        cwd = getenv("MSMOUSE");
        if (cwd != 0 && strcmpi(cwd, "BUG") == 0)
            mouseBug = 1;
    }
    {
        unsigned long memory;
        memory = RallocMemoryFree();
        if (memory == 0 && debugOn == 0)
            Punt(notEnoughMemoryStr);
    }
    cwd = getcwd(0, 0);
    iniPath = cwd;
    iniDrive = cwd[0];
    i = strlen(cwd) - 1;
    if (cwd[i] == 92)
        cwd[i] = 0;

    db_SetDataBase("simant.dat");
    if (displayType == 3 || displayType == 4)
        db_SetDataBase("simantc.dat");
    else if (displayType == 5 || displayType == 6)
        db_SetDataBase("simantm.dat");

    localGraphicsName = graphicsName;
    displaySuffix[0] = "hcega";
    displaySuffix[1] = "mono";
    displaySuffix[2] = "tdyga";
    displaySuffix[3] = "mono";
    displaySuffix[4] = "lcega";
    displaySuffix[5] = "mono";
    displaySuffix[6] = "l256";
    displaySuffix[7] = "mono";
    displaySuffix[8] = "hcega";
    displaySuffix[9] = "mwin";
    displaySuffix[10] = "winga";

    if (displayType == (char)-1) {
        int desktop;
        int dc;
        desktop = GetDesktopWindow();
        dc = GetDC(desktop);
        if (GetDeviceCaps(dc, 12) == 1 && GetDeviceCaps(dc, 14) == 1) {
            ReleaseDC(desktop, dc);
            displayType = 9;
        } else {
            ReleaseDC(desktop, dc);
            displayType = 10;
        }
    }
    sprintf(message, "%s%s", localGraphicsName, displaySuffix[displayType]);
    WinPrintf(message);
    db_SetDataBase(message);

    switch (displayType) {
    case 0:
    case 8:
        win_SetPalette(0);
        break;
    default:
        InitPalette();
        break;
    }
    mem_Flush();
    ralloc_CompressMemory();
    start = TickCount();

    getcwd(helpFile, 256);
    if (strlen(helpFile) != 0 && helpFile[strlen(helpFile) - 1] != '\\')
        strcat(helpFile, "\\");
    strcat(helpFile, helpFileName);
    if (InitMenu(0) != 0)
        Punt("Cannot initialise menu");
    MSClipStart(rootWnd);
    code = ConvColor(15);
    GBoxFill(0, 0, screenWidth, screenHeight, code);
    gr_BitMapSize(&bitmapSize, bitmapTable[displayType]);
    win_DrawBitMap((screenWidth - bitmapSize.width) / 2,
                   (screenHeight - bitmapSize.height) / 2,
                   bitmapTable[displayType]);
    MSClipEnd();
    SetMenuEntries();
    LoadTiles();
    InitApplicationStuff();
    InitApplicationWindows();
    SetMenuEntries();
    if (WaitedEnough(&start, 0x48))
        RedrawScreen();
}
