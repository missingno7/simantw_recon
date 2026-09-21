typedef void (far *WindowProc)(void);

extern int near hInst;
extern int near rootWnd;
extern int near ribbonBarWnd;
extern void far StopSimulation(void);
extern WindowProc far pascal MakeProcInstance(WindowProc procedure,
                                              int instance);
extern void far pascal FreeProcInstance(WindowProc procedure);
extern int far pascal EnumChildWindows(int parent, WindowProc procedure,
                                       unsigned long parameter);
extern int far pascal InvalidateRect(int window, void far *rect,
                                     unsigned flags);

void far RedrawWindows(int window)
{
    WindowProc procedure;
    int procedureSegment;

    procedure = MakeProcInstance((WindowProc)StopSimulation, hInst);
    EnumChildWindows(rootWnd, procedure, (unsigned long)(unsigned int)window);
    FreeProcInstance(procedure);
    if (ribbonBarWnd != 0 && window != ribbonBarWnd)
        InvalidateRect(ribbonBarWnd, (void far *)0, 0);
}
