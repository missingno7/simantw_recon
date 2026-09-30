/* Read configuration/command-line display and sound switches, choose the
 * installation directories, then initialise the splash screen and windows. */
extern int near musicDevice;
extern char near debugOn;
extern char near mouseBug;
extern char near displayType;
extern int near rootWnd;
extern int near hInst;
extern int far hHelpCursor;
extern unsigned int far pascal LoadCursor(unsigned int instance, char far *name);
extern int near screenWidth;
extern int near screenHeight;
extern int far match_position[];

extern char far * far usageStr;
extern char far * far notEnoughMemoryStr;
extern char far * far graphicsName;
extern char far * far iniPath;
extern int far iniDrive;
extern void far * far initialMemory;
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
extern int far pascal _lopen(char far *path, int mode);
extern int far pascal _lclose(int handle);

extern int far sprintf(char far *buffer, char far *format, ...);
extern unsigned int strlen(const char far *text);
extern char far *strcat(char far *destination, const char far *source);

extern void far WinPrintf(char far *format, ...);
extern int far pascal MessageBox(int window, char far *text,
                                  char far *caption, unsigned style);

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
    long value;
    struct BitmapSize bitmapSize;
    int code;
    int helpHandle;
    int i;
    long start;

    musicDevice = -1;
    ReadConfig();

    if (commandLine != 0 && LSTRLEN(commandLine) > 0) {
        i = 0;
        while (commandLine[i] != 0) {
            while (commandLine[i] == ' ' || commandLine[i] == '\t')
                i++;
            if (commandLine[i] == 0)
                break;
            if (commandLine[i] != '\\') {
                while (commandLine[i] != 0 && commandLine[i] != ' ' &&
                       commandLine[i] != '\t')
                    i++;
                continue;
            }
            option = commandLine[i + 1];
            value = commandLine[i + 2];
            switch (option) {
            case '!':
                debugOn = value != '-';
                mem_Debugging(debugOn);
                break;
            case 'b':
                mouseBug = 1;
                break;
            case 'd':
                switch (value) {
                case '2': displayType = 6; break;
                case '?': displayType = (char)-1; break;
                case 'E': displayType = 0; break;
                case 'H': displayType = 3; break;
                case 'M': displayType = 5; break;
                case 'T': displayType = 2; break;
                case 'V': displayType = 8; break;
                case 'W': displayType = 10; break;
                case 'w': displayType = 9; break;
                case 'e': displayType = 4; break;
                case 'm': displayType = 7; break;
                default:
                    MessageBox(rootWnd, usageStr, "Error Message", 0x30);
                    exit(4);
                }
                break;
            case 's':
                if (isdigit(value))
                    musicDevice = value - '0';
                break;
            }            while (commandLine[i] != 0 && commandLine[i] != ' ' &&
                   commandLine[i] != '\t')
                i++;
        }
    }
    if (getenv("BUG") != 0 &&
        strcmpi(getenv("BUG"), "MSMOUSE") == 0)
        mouseBug = 1;
    initialMemory = (void far *)RallocMemoryFree();
    if (debugOn == 0 && (unsigned long)initialMemory < 0xf4240UL) {
        MessageBox(rootWnd, notEnoughMemoryStr, "Error Message", 0x30);
        exit(1);
    }
    cwd = getcwd(0, 0);
    iniPath = cwd;
    iniDrive = cwd[0];
    i = strlen(cwd) - 1;
    if (cwd[i] == '\\')
        cwd[i] = 0;
    if ((i = _lopen("language.dat", 0)) > 0) {
        _lclose(i);
        db_SetDataBase("language");
    }
    db_SetDataBase("shared");
    if (displayType == 2 || displayType == 4)
        db_SetDataBase("lrshare");
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
    hHelpCursor = LoadCursor(hInst, "HelpCursor");

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
