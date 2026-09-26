/* Register the DDE client window class and its class resource handles. */
struct WndClass {
    unsigned style;
    void (far *windowProc)(void);
    int classExtra;
    int windowExtra;
    unsigned instance;
    unsigned icon;
    unsigned cursor;
    unsigned background;
    char far *menuName;
    char far *className;
};
extern void far GTCLIENTWNDPROC(void);
extern unsigned far pascal LoadIcon(unsigned, unsigned long);
extern unsigned far pascal LoadCursor(unsigned, unsigned long);
extern int far pascal RegisterClass(struct WndClass far *);
int GtRegisterClass(unsigned instance)
{
    struct WndClass wc;
    wc.style = 0;
    wc.windowProc = GTCLIENTWNDPROC;
    wc.classExtra = 0;
    wc.windowExtra = 0;
    wc.instance = instance;
    wc.icon = LoadIcon(0, 0x7f00L);
    wc.cursor = LoadCursor(0, 0x7f00L);
    wc.background = 0x000d;
    wc.menuName = 0L;
    wc.className = "ClientDDEClass";
    return RegisterClass(&wc);
}
