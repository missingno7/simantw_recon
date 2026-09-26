/* Read configuration/command-line display and sound switches, choose the
 * installation directories, then initialise the splash screen and windows. */
extern int near musicDevice;
extern char near debugOn;
extern char near mouseBug;
extern char near displayType;
extern int near rootWnd;
extern int near hInst;
extern int near screenWidth;
extern int near screenHeight;
extern char far match_position[];
extern char far * far usageStr;
extern char far * far notEnoughMemoryStr;
extern char far * far graphicsName;
extern char far * far iniPath;
extern char far * far iniDrive;
extern char far * far helpFileName;
extern int near ReadConfig(void);
extern int far mem_Debugging(int enabled);
extern void far * RallocMemoryFree(void);
extern char far * far getenv(const char far *name);
extern int far strcmpi(const char far *left, const char far *right);
extern int far isdigit(int ch);
extern char far * far getcwd(char far *buffer, unsigned int size);
extern int far sprintf(char far *buffer, const char far *format, ...);
extern void far WinPrintf(const char far *text);
extern void far Punt(const char far *text);
extern void far db_SetDataBase(const char far *name);
extern void far SetMenuEntries(void);
extern void far LoadTiles(void);
extern void far InitApplicationStuff(void);
extern void far InitApplicationWindows(void);
extern int far InitMenu(void);
extern void far InitPalette(void);
extern void far win_SetPalette(int which);
extern void far * InitBitmapInfo(void);
extern int far ConvColor(int color);
extern void far GBoxFill(int left, int top, int right, int bottom,
                         int color);
extern void far gr_BitMapSize(unsigned int bitmap, int far *width,
                              int far *height);
extern void far win_DrawBitMap(unsigned int bitmap, int x, int y);
extern void far MSClipStart(int hwnd);
extern void far MSClipEnd(void);
extern unsigned long far TickCount(void);
extern int far WaitedEnough(unsigned long start, unsigned int delay);
extern void far RedrawScreen(void);
extern void far mem_Flush(void);
extern void far ralloc_CompressMemory(void);
extern void far exit(int status);

static int is_switch(char ch)
{
    return ch == '-' || ch == '/';
}

void far IBMInitStuff(char far *commandLine)
{
    char far *p;
    char far *env;
    char far *cwd;
    char path[260];
    char message[96];
    char option;
    int width;
    int height;
    int code;
    int i;
    unsigned long start;

    musicDevice = -1;
    ReadConfig();

    p = commandLine;
    while (*p != 0) {
        while (*p == ' ' || *p == '\t')
            p++;
        if (!is_switch(*p)) {
            while (*p != 0 && *p != ' ' && *p != '\t')
                p++;
            continue;
        }
        p++;
        option = *p++;
        if (option == 'd' || option == 'D') {
            switch (*p) {
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
            while (*p != 0 && *p != ' ' && *p != '\t')
                p++;
        } else if (option == 'm' || option == 'M') {
            if (isdigit(*p)) {
                musicDevice = *p - '0';
                p++;
            }
        } else if (option == 'g' || option == 'G') {
            debugOn = *p == '1' || *p == 'Y' || *p == 'y';
            mem_Debugging(debugOn);
        } else if (option == 'b' || option == 'B') {
            mouseBug = 1;
        } else if (option == '?') {
            WinPrintf(usageStr);
            exit(4);
        }
    }

    env = getenv("SIMANT_MOUSE_BUG");
    if (env != 0) {
        cwd = getenv("SIMANT_MOUSE_BUG");
        if (cwd != 0 && strcmpi(env, cwd) == 0)
            mouseBug = 1;
    }
    {
        void far *memory;
        memory = RallocMemoryFree();
        if (memory == 0 && debugOn == 0)
            Punt(notEnoughMemoryStr);
    }
    cwd = getcwd(path, sizeof(path));
    if (cwd != 0) {
        for (i = 0; path[i] != 0; i++)
            ;
        if (i != 0 && path[i - 1] != '\\')
            path[i++] = '\\';
        path[i] = 0;
        iniPath = cwd;
        iniDrive = path;
    }

    db_SetDataBase("simant.dat");
    if (displayType == 3 || displayType == 4)
        db_SetDataBase("simantc.dat");
    else if (displayType == 5 || displayType == 6)
        db_SetDataBase("simantm.dat");

    if (displayType == (char)-1) {
        width = 0;
        height = 0;
        code = InitBitmapInfo();
        if (code != 0) {
            displayType = (char)code;
        } else {
            displayType = 9;
        }
    }
    sprintf(message, "%s", graphicsName);
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

    getcwd(match_position, 256);
    if (InitMenu() != 0)
        Punt("Cannot initialise menu");
    MSClipStart(rootWnd);
    code = ConvColor(15);
    GBoxFill(0, 0, screenWidth, screenHeight, code);
    gr_BitMapSize((unsigned int)displayType, &width, &height);
    win_DrawBitMap((unsigned int)displayType,
                   (screenWidth - width) / 2,
                   (screenHeight - height) / 2);
    MSClipEnd();
    SetMenuEntries();
    LoadTiles();
    InitApplicationStuff();
    InitApplicationWindows();
    SetMenuEntries();
    if (WaitedEnough(start, 0x48))
        RedrawScreen();
}
