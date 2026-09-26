/*
 * MYTIMERFUNC services the main window timer: refresh the icon for paused or
 * completed play, update simulation/network/audio state, invalidate the
 * client when needed, and drain the timer-message queue.  The private timer
 * words are kept as natural counters; their original data ownership is still
 * provisional.
 */
struct WinRect { int left; int top; int right; int bottom; };
struct TimerMessage {
    int window;
    unsigned int message;
    unsigned int wParam;
    unsigned long lParam;
    unsigned long time;
    int x;
    int y;
};

extern int near mainRootWnd;
extern int near hInst;
extern int far GamePaused;
extern int far IsGameOver;
extern int far BlackWon;
extern unsigned long far gameCycles;
extern int far SimAntClientFlag;
extern int far SimAntServerFlag;
extern int far SimAntClientNum;
extern int far MeMoveMe;
extern int far CurGameTool;
extern int far GameSpeed;
extern int far SpeedDelayVals[];
extern int far ncbHead;
extern int far ncbTail;

static unsigned int timerCallCount = 0;
static unsigned long timerCadence = 0;
static int timerBusy = 0;

extern int far pascal IsIconic(int window);
extern int far pascal LoadIcon(int instance, char far *resource);
extern unsigned int far pascal GetClassWord(int window, int index);
extern unsigned int far pascal SetClassWord(int window, int index,
                                             unsigned int value);
extern int far pascal InvalidateRect(int window, struct WinRect far *rect,
                                     int erase);
extern int far pascal PeekMessage(struct TimerMessage far *message, int window,
                                  unsigned int first, unsigned int last,
                                  int remove);
extern int far pascal GetAsyncKeyState(int key);
extern int far SRand1(int range);
extern int far sprintf(char far *buffer, char far *format, ...);
extern void far DoAntSim(void);
extern void far myServiceSong(void);
extern void far MSClipStart(int window);
extern void far MSClipEnd(void);
extern unsigned long far TickCount(void);
extern int far win_IsWinOpen(int window);
extern void far win_PrintfAtObj(int object, char far *format, ...);
extern void far win_FillObjRect(int object, int color);
extern void far UpdateYardMessage(void);
extern int near ProcessPost(void);
extern void near NetworkSend(void);
extern void near UpdateWindows(void);
extern char near iconNormal[];
extern char near iconPaused[];
extern char near iconWon[];
extern char near iconLost[];
extern char near timerFormat[];

void far pascal MYTIMERFUNC(int window, int message, int timerId,
                            unsigned int lowTime, unsigned int highTime)
{
    struct TimerMessage timerMessage;
    struct WinRect invalid;
    unsigned long now;
    unsigned int icon;
    int status;
    int keyState;
    char statusText[10];

    window = mainRootWnd;
    if (window == 0)
        return;

    if (IsIconic(window)) {
        if (GamePaused == 0)
            icon = LoadIcon(hInst, iconNormal);
        else if (IsGameOver && BlackWon)
            icon = LoadIcon(hInst, iconWon);
        else if (IsGameOver)
            icon = LoadIcon(hInst, iconLost);
        else
            icon = LoadIcon(hInst, iconPaused);
        if (GetClassWord(window, -14) != icon)
            SetClassWord(window, -14, icon);
    }

    status = SRand1(7);
    sprintf(statusText, timerFormat, status);
    MSClipStart(window);
    win_PrintfAtObj(window, timerFormat, statusText);
    MSClipEnd();

    now = TickCount();
    if (now != timerCadence) {
        timerCadence = now;
        ++timerCallCount;
        if (!GamePaused && !IsGameOver)
            DoAntSim();
        UpdateYardMessage();
        myServiceSong();
    }

    if (SimAntClientFlag && ncbHead != ncbTail)
        NetworkSend();
    if (ProcessPost())
        UpdateWindows();

    if (GamePaused)
        InvalidateRect(window, 0, 1);
    if (SimAntServerFlag && SimAntClientNum)
        timerCadence += gameCycles;
    if (MeMoveMe && CurGameTool == 10)
        UpdateYardMessage();

    status = PeekMessage(&timerMessage, 0, 0x113, 0x113, 3);
    while (status) {
        ++timerCallCount;
        keyState = GetAsyncKeyState(1);
        if (keyState & 1)
            InvalidateRect(window, &invalid, 0);
        status = PeekMessage(&timerMessage, 0, 0x113, 0x113, 3);
    }
}
