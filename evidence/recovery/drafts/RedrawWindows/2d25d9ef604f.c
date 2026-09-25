/* RedrawWindows: enumerate the child windows of rootWnd through a MakeProcInstance
 * thunk of the exported MYENUMFUNC callback (MAPSYM SIMANT_MODULE:1C38), then
 * invalidate the ribbon bar unless it is the redrawn window. The earlier draft
 * pushed StopSimulation's far pointer; MAPSYM names the real callback. */
typedef void (far *WindowProc)(void);

extern int near hInst;
extern int near rootWnd;
extern int near ribbonBarWnd;
extern int far pascal MyEnumFunc(int window, unsigned long parameter);
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

    procedure = MakeProcInstance((WindowProc)MyEnumFunc, hInst);
    EnumChildWindows(rootWnd, procedure, (unsigned long)(unsigned int)window);
    FreeProcInstance(procedure);
    if (ribbonBarWnd != 0 && window != ribbonBarWnd)
        InvalidateRect(ribbonBarWnd, (void far *)0, 0);
}
