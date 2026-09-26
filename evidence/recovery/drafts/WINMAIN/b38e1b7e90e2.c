/*
 * WINMAIN prevents a second copy, initializes the application and instance,
 * probes display capabilities, configures windows and persisted options,
 * installs cursors/timer/accelerators, builds both user-button groups, and
 * runs the message pump before freeing the callback instance.
 */
struct WinRect { int left, top, right, bottom; };
struct WinPoint { int x, y; };
struct WinMsg { int hwnd, message, wParam; long lParam; unsigned long time; struct WinPoint point; };
extern int near hInst;
extern int near rootWnd;
extern int near mainRootWnd;
extern int near ribbonBarWnd;
extern int near paletteFlag;
extern unsigned char near displayType;
extern unsigned int near antCursor, digCursor, dropCursor, foodCursor;
extern unsigned int near magCursor, rockCursor, sprayCursor;
extern int far OptionStates[];
extern int far UDMapFlip;
extern void far SetDebugFlag(int value);
extern int far InitApplication(int show);
extern int far InitInstance(int instance, int show);
extern void far PopMsg(char far *text);
extern void far SetUpPalette(int enabled);
extern void far IBMInitStuff(unsigned int commandLineOffset, int previousInstance);
extern void far win_Recalc(int window);
extern void far db_SetDataBase(char far *name);
extern void far snd_Install(void);
extern void far LoadMonoPats(void);
extern void far PatchColorArrays(void);
extern void far ShowIntro(void);
extern void far CustomerIDDialog(void);
extern int far NewGame(int firstGame);
extern void far Quit(char far *message, int code);
extern void far CleanUp(void);
extern int far SetUserButton(int object, char far *text);
extern void far SetMenuEntries(void);
extern void far StopSimulation(void);
extern void far WinPrintf(char far *format, ...);
extern int far pascal FindWindow(char far *className, char far *windowName);
extern int far pascal BringWindowToTop(int window);
extern int far pascal GetDC(int window);
extern int far pascal ReleaseDC(int window, int dc);
extern int far pascal Escape(int dc, int function, int count, void far *input, void far *output, int flags);
extern int far pascal GetDeviceCaps(int dc, int index);
extern int far pascal GetClientRect(int window, struct WinRect far *rect);
extern int far pascal SetWindowPos(int window, int after, int x, int y, int width, int height, int flags);
extern int far pascal SetProp(int window, char far *name, int value);
extern int far pascal GetProfileInt(char far *section, char far *key, int defaultValue);
extern int far pascal WriteProfileString(char far *section, char far *key, char far *value);
extern int far pascal MakeProcInstance(void far *proc, int instance);
extern void far pascal FreeProcInstance(int proc);
extern int far pascal SetTimer(int window, int id, int interval, void far *proc);
extern int far pascal LoadCursor(int instance, char far *name);
extern int far pascal LoadAccelerators(int instance, char far *name);
extern int far pascal GetMessage(struct WinMsg far *message, int window, int first, int last);
extern int far pascal TranslateAccelerator(int window, int accelerators, struct WinMsg far *message);
extern int far pascal TranslateMessage(struct WinMsg far *message);
extern int far pascal DispatchMessage(struct WinMsg far *message);
extern int far pascal GetCapture(void);
extern int far pascal ReleaseCapture(void);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far StopSimulation(void);

int far pascal WINMAIN(int instance, int previousInstance,
                       char far *commandLine, int show)
{
    int oldWindow;
    int dc;
    int caps;
    int width;
    int height;
    int status;
    int accelerators;
    int callback;
    int i;
    int runFlag;
    int exitCode;
    struct WinRect client;
    struct WinMsg message;
    char far buttonText[32];
    char far titleText[32];

    runFlag = 1;
    oldWindow = FindWindow("SimAnt", (char far *)0);
    if (oldWindow != 0) {
        BringWindowToTop(oldWindow);
        return 0;
    }

    SetDebugFlag(1);
    if (previousInstance == 0) {
        if (!InitApplication(instance))
            return 0;
        if (!InitInstance(instance, show))
            return 0;
    }

    dc = GetDC(0);
    caps = 0;
    Escape(dc, 2, 8, &caps, 0, 0);
    if ((caps & 0x100) == 0 && GetDeviceCaps(dc, 0x26) == 0 &&
        GetDeviceCaps(dc, 0x0c) < 8 && GetDeviceCaps(dc, 0x0e) < 8)
        SetUpPalette(1);
    ReleaseDC(0, dc);

    IBMInitStuff((unsigned int)commandLine, previousInstance);
    if (mainRootWnd != 0 && GetClientRect(mainRootWnd, &client)) {
        width = client.right - client.left;
        height = client.bottom - client.top;
        win_Recalc(0x2200);
        SetWindowPos(ribbonBarWnd, 0, 0, 0, width, 2, 2);
        SetWindowPos(rootWnd, 0, 0, 0, width, height, 0);
        SetWindowPos(rootWnd, 0, 0, height, width, 0, 1);
        SetWindowPos(ribbonBarWnd, 0, 0, 0, 0, 0, 0);
        SetProp(ribbonBarWnd, "SimAnt", 0);
    }

    db_SetDataBase("SIMANT.DAT");
    snd_Install();
    OptionStates[0] = GetProfileInt("SimAnt", "Sound", OptionStates[0]);
    OptionStates[1] = GetProfileInt("SimAnt", "Music", OptionStates[1]);
    OptionStates[2] = GetProfileInt("SimAnt", "Effects", OptionStates[2]);
    OptionStates[3] = GetProfileInt("SimAnt", "Hints", OptionStates[3]);
    OptionStates[4] = GetProfileInt("SimAnt", "Auto", OptionStates[4]);
    OptionStates[5] = GetProfileInt("SimAnt", "Fast", OptionStates[5]);

    if (displayType & 1) {
        LoadMonoPats();
        if (displayType == 10)
            PatchColorArrays();
    }
    ShowIntro();
    CustomerIDDialog();
    status = NewGame(1);
    if (status < 0) {
        Quit("Unable to start the simulation", 0);
        CleanUp();
        exitCode = 0;
    } else {
        StopSimulation();
        callback = MakeProcInstance((void far *)StopSimulation, instance);
        for (i = 0; i < 8; ++i) {
            sprintf(buttonText, "%u", i);
            status = SetUserButton(0x2210 + i, buttonText);
            sprintf(titleText, "%u", i);
            SetUserButton(0x230b + i, titleText);
        }
        SetMenuEntries();
        UDMapFlip = 0;
        magCursor = LoadCursor(hInst, "MAG");
        rockCursor = LoadCursor(hInst, "ROCK");
        digCursor = LoadCursor(hInst, "DIG");
        antCursor = LoadCursor(hInst, "ANT");
        foodCursor = LoadCursor(hInst, "FOOD");
        dropCursor = LoadCursor(hInst, "DROP");
        sprayCursor = LoadCursor(hInst, "SPRAY");
        SetTimer(rootWnd, 0, 0x11, (void far *)callback);
        accelerators = LoadAccelerators(hInst, "SIMANT");

        if (mainRootWnd != 0) {
            GetClientRect(rootWnd, &client);
            if (client.right != 0 && client.bottom != 0)
                SetWindowPos(rootWnd, 0, 0, 0, client.right, client.bottom, 0);
            while (mainRootWnd != 0) {
                status = GetMessage(&message, 0, 0, 0);
                if (status <= 0)
                    break;
                if (!TranslateAccelerator(rootWnd, accelerators, &message)) {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            }
        }
        if (mainRootWnd != 0) {
            runFlag = 0;
        } else {
            WinPrintf("Window initialization failed");
        }
        if (runFlag) {
            ReleaseCapture();
            for (i = 0; i < 6; ++i)
                WriteProfileString("SimAnt", "Option", OptionStates[i] ? "1" : "0");
            FreeProcInstance(callback);
        }
    }
    return exitCode;
}
