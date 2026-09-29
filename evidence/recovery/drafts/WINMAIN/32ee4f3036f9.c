struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};
struct Rect {
    int left;
    int top;
    int right;
    int bottom;
};
/* WINMAIN authoring source: isolated C body and evidence-named data views. */
typedef void (far *WindowProc)(void);
extern unsigned int near magCursor, rockCursor, digCursor, antCursor;
extern unsigned int near foodCursor, dropCursor, sprayCursor;
extern void far SetUserButton(int object, int button);
extern WindowProc far pascal MakeProcInstance(WindowProc procedure, int instance);
extern void far pascal FreeProcInstance(WindowProc procedure);

extern int near mapUserButton[8];
extern int near yardUserButton[8];
extern char near winMainClassName[];
extern char near notInstalledPattern[];
extern char near notInstalledMessage[];
extern char near cursorMagResource[], cursorRockResource[];
extern char near cursorDigResource[], cursorAntResource[];
extern char near cursorFoodResource[], cursorDropResource[];
extern char near cursorSprayResource[];
extern char near appSection0[], appSection1[], appSection2[], appSection3[];
extern char near appSection4[], appSection5[], appSection6[], appSection7[];
extern char near appSection8[], appSection9[], appSection10[], appSection11[];
extern char near appSection12[], appSection13[], appSection14[], appSection15[];
extern char near optionSound[], optionAutotrack[], optionMusic[];
extern char near optionEffects[], optionEvents[], optionMessages[], optionSilly[];
extern char near mapButtonProfile[], yardButtonProfile[];
extern char near acceleratorResource[], releasingCaptureMessage[];
extern char near winMainPropertyIndex[];
extern char near mapButtonProfileAgain[], yardButtonProfileAgain[];
extern char near optionAutotrackAgain[], optionMusicAgain[], optionEffectsAgain[];
extern char near optionEventsAgain[], optionMessagesAgain[], optionSillyAgain[];
extern char near profileOne0[], profileOne1[], profileOne2[], profileOne3[];
extern char near profileOne4[], profileOne5[];
extern char near profileZero0[], profileZero1[], profileZero2[], profileZero3[];
extern char near profileZero4[], profileZero5[];
extern char near integerFormat0[], integerFormat1[];
extern char near cancelledMessage[];

struct WinBucket {
    unsigned char header[0x2c];
    struct WinRect far *rects[256];
};
extern struct WinBucket far * near win_handles[];

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
extern void (far *near lpTimerFunc)(void) = 0;


extern unsigned char near displayType;


extern int far OptionStates[];
extern int far songsOnFlag;
extern int far effectsOnFlag;
extern int far UDcntr;
extern int far UDMapFlip;
extern void far SetDebugFlag(int value);
extern int far InitApplication(int instance);
extern int far InitInstance(int instance, int show);
extern void PopMsg(char far *text);

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

extern void far SetMenuEntries(void);
extern void far StopSimulation(void);
extern void far WinPrintf(char far *format, ...);
extern int far pascal FindWindow(char far *className, char far *windowName);
extern int far pascal BringWindowToTop(int window);

extern int far pascal GetDC(int window);
extern int far pascal ReleaseDC(int window, int dc);
extern int far pascal Escape(int dc, int count, int function, void far *input, void far *output);
extern int far pascal GetDeviceCaps(int dc, int index);
extern void far pascal GetClientRect(unsigned int window, struct Rect far *rect);


extern int far pascal SetWindowPos(int window, int after, int x, int y, int width, int height, int flags);
extern int far pascal SetProp(int window, char far *name, int value);
extern void far pascal InvalidateRect(int window, void far *rect,
                                      unsigned flags);

extern int far pascal UpdateWindow(int window);
extern int far pascal GetProfileInt(char far *section, char far *key, int defaultValue);
extern int far pascal WriteProfileString(char far *section, char far *key, char far *value);


extern int far pascal SetTimer(int window, unsigned int timer,
                               unsigned int interval,
                               void (far *timerFunc)(void));

extern unsigned int far pascal LoadCursor(unsigned int instance,
                                          char far *name);


extern int far pascal LoadAccelerators(int instance, char far *name);
extern int far pascal GetMessage(struct WinMsg far *message, int window, int first, int last);
extern int far pascal TranslateAccelerator(int window, int accelerators, struct WinMsg far *message);
extern int far pascal TranslateMessage(struct MSG far *message);

extern long far pascal DispatchMessage(struct MSG far *message);

extern int far pascal GetCapture(void);
extern void far pascal ReleaseCapture(void);

extern int far sprintf(char far *buffer, char far *format, ...);

extern int far memcmp(const void far *, const void far *, unsigned int);
extern char near __qczrinit[];

int far pascal WINMAIN(int instance, int previousInstance,
                       char far *commandLine, int show)
{
    int oldWindow;
    int dc;
    int caps;



    int messageStatus;
    int accelerators;
    struct WinBucket far *bucket;
    int i;
    int exitCode;
    struct WinRect client;
    struct WinMsg message;
    char far buttonText[32];
    char far titleText[32];

    messageStatus = 1;
    oldWindow = FindWindow(winMainClassName, (char far *)0);
    if (oldWindow != 0) {
        BringWindowToTop(oldWindow);
        return 0;
    }

    SetDebugFlag(1);
    if (previousInstance == 0)
        if (!InitApplication(instance))
            return 0;
    if (!InitInstance(instance, show))
        return 0;
    if (memcmp(*(char far **)(__qczrinit + 12),
               notInstalledPattern, 11) == 0) {
        PopMsg(notInstalledMessage);
        return 0;
    }

    dc = GetDC(0);
    caps = 4;
    if (Escape(dc, 8, 2, &caps, 0) == 0) {

        if (GetDeviceCaps(dc, 0x26) & 0x100) {
            SetUpPalette(1);
        } else if (GetDeviceCaps(dc, 0x0c) < 8 &&
                   GetDeviceCaps(dc, 0x0e) < 8) {
            if (GetDeviceCaps(dc, 0x0c) <= 1)
                GetDeviceCaps(dc, 0x0e);
        }
    }
    ReleaseDC(0, dc);

    IBMInitStuff((unsigned int)commandLine, previousInstance);
    if (rootWnd != 0 || ribbonBarWnd != 0) {
        GetClientRect(mainRootWnd, &client);
        win_Recalc(0x2200);
        bucket = win_handles[0x22];


        SetProp(0x2200, winMainPropertyIndex, ribbonBarWnd);
        SetWindowPos(ribbonBarWnd, 0, 0, 0, client.right,
                     *(int far *)&bucket->header[6] -
                     *(int far *)&bucket->header[2], 2);
        SetWindowPos(rootWnd, 0, 0, 0,
                     *(int far *)&bucket->header[6] -
                     *(int far *)&bucket->header[2], 0, 1);
        SetWindowPos(rootWnd, 0, 0, 0, client.right,
                     *(int far *)&bucket->header[2] -
                     *(int far *)&bucket->header[6] + client.bottom, 2);
        InvalidateRect(ribbonBarWnd, (struct WinRect far *)0, 0);
        UpdateWindow(ribbonBarWnd);
    }

    db_SetDataBase(optionSound);
    snd_Install();
    OptionStates[0] = GetProfileInt(appSection0, optionAutotrack,
                                    OptionStates[0]);
    OptionStates[1] = GetProfileInt(appSection1, optionMusic,
                                    OptionStates[1]);
    OptionStates[2] = GetProfileInt(appSection2, optionEffects,
                                    OptionStates[2]);
    OptionStates[3] = GetProfileInt(appSection3, optionEvents,
                                    OptionStates[3]);
    OptionStates[4] = GetProfileInt(appSection4, optionMessages,
                                    OptionStates[4]);
    OptionStates[5] = GetProfileInt(appSection5, optionSilly,
                                    OptionStates[5]);
    songsOnFlag = OptionStates[1];
    effectsOnFlag = OptionStates[2];

    if (displayType & 1) {
        LoadMonoPats();
        if (displayType == 10)
            PatchColorArrays();
    }
    ShowIntro();
    CustomerIDDialog();
    if (NewGame(1) < 0) {

        Quit(cancelledMessage, 0);
        CleanUp();
        exitCode = 0;
    } else {
        lpTimerFunc = MakeProcInstance((WindowProc)StopSimulation, hInst);
        for (i = 0; i < 8; ++i) {
            sprintf(buttonText, mapButtonProfile, i);
            mapUserButton[i] = GetProfileInt(appSection6, buttonText,
                                             mapUserButton[i]);
            SetUserButton(0x2210 + i, mapUserButton[i]);
            sprintf(buttonText, yardButtonProfile, i);
            yardUserButton[i] = GetProfileInt(appSection7, buttonText,
                                              yardUserButton[i]);
            SetUserButton(0x230b + i, yardUserButton[i]);
        }
        SetMenuEntries();
        UDcntr = 0;
        UDMapFlip = 0;
        magCursor = LoadCursor(hInst, cursorMagResource);
        rockCursor = LoadCursor(hInst, cursorRockResource);
        digCursor = LoadCursor(hInst, cursorDigResource);
        antCursor = LoadCursor(hInst, cursorAntResource);
        foodCursor = LoadCursor(hInst, cursorFoodResource);
        dropCursor = LoadCursor(hInst, cursorDropResource);
        sprayCursor = LoadCursor(hInst, cursorSprayResource);
        SetTimer(rootWnd, 0, 0x11, (void far *)lpTimerFunc);
        accelerators = LoadAccelerators(hInst, acceleratorResource);

        if (mainRootWnd != 0) {
            do {
                messageStatus = GetMessage(&message, 0, 0, 0);
                if (messageStatus == 0)
                    break;
                if (!TranslateAccelerator(rootWnd, accelerators, &message)) {
                    TranslateMessage(&message);
                    DispatchMessage(&message);
                }
            } while (mainRootWnd != 0);
        }
        if (GetCapture() != 0) {
            WinPrintf(releasingCaptureMessage);
            ReleaseCapture();
        }
        WriteProfileString(appSection8, optionAutotrackAgain,
                           OptionStates[0] ? profileZero0 : profileOne0);
        WriteProfileString(appSection9, optionMusicAgain,
                           OptionStates[1] ? profileZero1 : profileOne1);
        WriteProfileString(appSection10, optionEffectsAgain,
                           OptionStates[2] ? profileZero2 : profileOne2);
        WriteProfileString(appSection11, optionEventsAgain,
                           OptionStates[3] ? profileZero3 : profileOne3);
        WriteProfileString(appSection12, optionMessagesAgain,
                           OptionStates[4] ? profileZero4 : profileOne4);
        WriteProfileString(appSection13, optionSillyAgain,
                           OptionStates[5] ? profileZero5 : profileOne5);
        for (i = 0; i < 8; ++i) {
            sprintf(buttonText, mapButtonProfileAgain, i);
            sprintf(titleText, integerFormat0, mapUserButton[i]);
            WriteProfileString(appSection14, buttonText, titleText);
            sprintf(buttonText, yardButtonProfileAgain, i);
            sprintf(titleText, integerFormat1, yardUserButton[i]);
            WriteProfileString(appSection15, buttonText, titleText);
        }
        FreeProcInstance(lpTimerFunc);
        if (messageStatus != 0)
            exitCode = 0;
    }
    return exitCode;
}
