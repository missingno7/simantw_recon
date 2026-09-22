/* Candidate translation unit gr_7712_vocMciClose_1: composed from preserved exact-body sources
 * in MAPSYM order. Internal evidence id, not a historical filename.
 * Members: _vocMciClose */

typedef void (far pascal *MMCloseProc)(int handle);
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern MMCloseProc far pascal GetProcAddress(int handle, char far *name);
extern char near wSoundBlasterMsg[];
static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) mmWaveHandle = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) mmRefCount = 0;

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
    if (--mmRefCount == 0) {
        proc = GetProcAddress(mmModule, wSoundBlasterMsg + 0x179);
        if (proc)
            proc(mmWaveHandle);
        mmWaveHandle = 0;
    }
}

