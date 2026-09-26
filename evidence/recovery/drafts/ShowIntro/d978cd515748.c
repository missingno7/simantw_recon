/* Known ShowIntro lifecycle: open dialog 0x300, prepare its customer-ID handle, wait for dialog events, then release capture and close. The data-table string fill remains a hypothesis. */
static int introCaptureWindow;
extern unsigned int far custIDStrHandle;
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_FlushEvents(void);
extern void far win_Open(int window);
extern void far win_Close(int window);
extern int far win_IsWinOpen(int window);
extern int far win_Events(void);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void far DialogWaitInit(int flags);
extern int far DialogAbortOrCont(void);
extern void far DialogDone(void);
void far ShowIntro(void)
{
    char far *customerText;
    int dialogState;
    int divisor;
    win_FlushEvents();
    win_Open(0x300);
    MySetCapture(introCaptureWindow);
    myBeginSong(0x2711, 0x7e);
    custIDStrHandle = mem_Alloc(30L, 1, "Malloc");
    customerText = (char far *)mem_Lock(custIDStrHandle);
    dialogState = 0;
    {
        int i;
        int rem8;
        int v;
        extern unsigned char far Dx8[];
        for (i = 0; i < 256; ++i) {
            rem8 = i % 8;
            v = customerText[rem8];
            divisor = 30;
            v += Dx8[0x8b3e + i % divisor];
            v += i;
            customerText[rem8] = (char)(v % 10 + 48);
        }
    }
    customerText[8] = 0;
    mem_Unlock(custIDStrHandle);
    DialogWaitInit(0x28);
    while (win_IsWinOpen(0x300)) {
        if (dialogState)
            break;
        if (!win_Events() && DialogAbortOrCont())
            dialogState = 1;
        if (!win_IsWinOpen(0x300))
            break;
    }
    MyReleaseCapture();
    win_Close(0x300);
    DialogDone();
    win_FlushEvents();
}
