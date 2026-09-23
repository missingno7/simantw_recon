typedef int (far pascal *FARPROC)();
typedef void (far pascal *MMCloseProc)(int handle);
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern FARPROC far pascal GetProcAddress(int handle, char far *name);
static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;

struct MultimediaState {
    int moduleHandle;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
};
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};

void far vocMciClose(unsigned int buffer1, unsigned int buffer2)
{
    MMCloseProc proc;
    if (vocBufLocked2) {
        GlobalUnlock(buffer2);
        GlobalFree(buffer2);
        vocBufLocked2 = 0;
    }
    if (vocBufLocked1) {
        GlobalUnlock(buffer1);
        GlobalFree(buffer1);
        vocBufLocked1 = 0;
    }
    if (--mmState.refCount == 0) {
        proc = (MMCloseProc)GetProcAddress(mmState.moduleHandle, "waveOutClose");
        if (proc)
            proc(mmState.waveHandle);
        mmState.waveHandle = 0;
    }
}
