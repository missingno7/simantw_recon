/* Candidate translation unit simant_D3E2_scaffold: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _ShowIntro
 * SCAFFOLDED: claimed members in 1 code runs; no pool stand-ins were needed. */

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




static int introCaptureWindow;
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
            { signed char tableByte = Dx8[0x8b3e + i % divisor];
              v = v + tableByte; }
            v = v + i;
            customerText[rem8] = (char)(v % 10 + 48);
        }
    }
    customerText[8] = 0;
    mem_Unlock(custIDStrHandle);
    DialogWaitInit(0x28);
    if (win_IsWinOpen(0x300)) {
        do {
            if (dialogState)
                break;
            if (win_Events() || DialogAbortOrCont())
                dialogState = 1;
        } while (win_IsWinOpen(0x300));
    }
    MyReleaseCapture();
    win_Close(0x300);
    DialogDone();
    win_FlushEvents();
}

