/*
 * MYTIMERFUNC is the application timer callback.  It refreshes the class icon
 * for the current game state, advances simulation and network work, updates
 * the display, then drains the callback's keyboard/message work.  The five
 * callback words follow the observed RETF 0x0a convention.
 */
struct WinRect {
    int left;
    int top;
    int right;
    int bottom;
};
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
extern int near editMessage;
extern int near mapMessage;
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

static unsigned int timerCallCount;
static unsigned long timerCadence;
static int timerBusy;

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
extern void near DispatchTimerMessage(struct TimerMessage far *message);
extern char near iconNormal[];
extern char near iconPaused[];
extern char near iconWon[];
extern char near iconLost[];
extern char near timerFormat[];
extern char near networkFormat[];

void far pascal MYTIMERFUNC(int window, int message, int timerId,
                            unsigned int lowTime, unsigned int highTime)
{
    struct TimerMessage timerMessage;
    struct WinRect invalid;
    unsigned long now;
    unsigned long previous;
    unsigned int icon;
    unsigned int oldIcon;
    int status;
    int keyState;
    int row;
    int col;
    int pending;
    char statusText[32];

    window = mainRootWnd;
    if (window == 0)
        return;

    if (IsIconic(window)) {
        if (GamePaused)
            icon = LoadIcon(hInst, iconPaused);
        else if (IsGameOver && BlackWon)
            icon = LoadIcon(hInst, iconWon);
        else if (IsGameOver)
            icon = LoadIcon(hInst, iconLost);
        else
            icon = LoadIcon(hInst, iconNormal);
        oldIcon = GetClassWord(window, -14);
        if (oldIcon != icon)
            SetClassWord(window, -14, icon);
    } else if (GamePaused) {
        icon = LoadIcon(hInst, iconPaused);
        oldIcon = GetClassWord(window, -14);
        if (oldIcon != icon)
            SetClassWord(window, -14, icon);
    }

    status = SRand1(7);
    sprintf(statusText, timerFormat, status);
    if (win_IsWinOpen(window)) {
        MSClipStart(window);
        win_PrintfAtObj(window, timerFormat, statusText);
        MSClipEnd();
    }

    previous = timerCadence;
    now = TickCount();
    timerCadence = now;
    if (now != previous) {
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

    if (GamePaused) {
        win_FillObjRect(window, 0);
        InvalidateRect(window, &invalid, 1);
    }

    if (SimAntServerFlag && SimAntClientNum)
        timerCadence += gameCycles;
    if (MeMoveMe && CurGameTool == 10)
        UpdateYardMessage();

    row = GameSpeed;
    if (row < 0)
        row = 0;
    if (row > 7)
        row = 7;
    col = SpeedDelayVals[row];
    if (timerBusy == 0 && col != 0) {
        timerBusy = 1;
        timerCallCount = 0;
        PeekMessage(&timerMessage, 0, 0x113, 0x113, 1);
        timerBusy = 0;
    }

    pending = PeekMessage(&timerMessage, window, 0x100, 0x109, 1);
    if (pending) {
        DispatchTimerMessage(&timerMessage);
        keyState = GetAsyncKeyState(1);
        if (keyState & 1)
            InvalidateRect(window, &invalid, 0);
    }
}
