typedef int (far pascal *FARPROC)();
typedef void (far pascal *MMCloseProc)(int handle);
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern FARPROC far pascal GetProcAddress(int handle, char far *name);
extern char near wSoundBlasterMsg[];
static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;

struct MMStateProbe {
    int module;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    int state08;
    int state0A;
    int waveHandle;
    int state0E;
    int state10;
    int refCount;
};
static struct MMStateProbe __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};

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
        proc = (MMCloseProc)GetProcAddress(mmState.module, wSoundBlasterMsg + 0x179);
        if (proc)
            proc(mmState.waveHandle);
        mmState.waveHandle = 0;
    }
}
