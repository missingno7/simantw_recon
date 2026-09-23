/* Build the intro code and run its modal window until completion. */
extern unsigned char far Dx8[];
extern unsigned int far custIDStrHandle;
extern unsigned int far mem_Alloc(unsigned long bytes, int kind, char far *name);
extern void far *mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far win_FlushEvents(void);
extern void far win_Open(int flags);
extern void far win_Close(int object);
extern int far win_IsWinOpen(int object);
extern int far win_Events(void);
extern int far MySetCapture(int window);
extern void far MyReleaseCapture(void);
extern void far myBeginSong(unsigned int song, unsigned int priority);
extern void DialogWaitInit(int ticks);
extern int DialogAbortOrCont(void);
extern void DialogDone(void);

void far ShowIntro(void)
{
    char far *text;
    int i;
    int divisor;
    int waited;

    win_FlushEvents();
    win_Open(0x300);
    MySetCapture(0xBCAC);
    myBeginSong(0x2711, 0x7e);
    custIDStrHandle = mem_Alloc(0x1eL, 1, "Malloc");
    text = (char far *)mem_Lock(custIDStrHandle);
    for (i = 0; i < 0x100; ++i) {
        divisor = 0x1e;
        text[i % 0x1e] = (char)(((text[i % 8] + Dx8[i % divisor] + i) % 10) + '0');
    }
    text[8] = 0;
    mem_Unlock(custIDStrHandle);
    DialogWaitInit(0x28);
    waited = 0;
    while (win_IsWinOpen(0x300)) {
        if (waited)
            break;
        if (win_Events())
            continue;
        if (DialogAbortOrCont())
            waited = 1;
    }
    if (win_IsWinOpen(0x300)) {
        MyReleaseCapture();
        win_Close(0x300);
    }
    DialogDone();
    win_FlushEvents();
}
