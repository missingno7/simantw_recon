/* _MciOutWave: decode the packed differential sample stream in the locked MCI
 * block, then submit the resulting PCM data through the dynamically resolved
 * waveOut interface. The two global-memory handles are retained in the shared
 * buffer-lock words until completion or failure. */

struct MultimediaState {
    int moduleHandle;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
    unsigned int songState;
};
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)

struct WaveHeader {
    void far *data;
    unsigned long bufferLength;
    unsigned long bytesRecorded;
    unsigned long user;
    unsigned long flags;
    unsigned long loops;
    void far *next;
    unsigned long reserved;
};

typedef int (far pascal *WaveOutProc)(unsigned int device,
                                      struct WaveHeader far *header,
                                      unsigned int headerBytes);
typedef int (far pascal *WaveOutCloseProc)(unsigned int device);
extern WaveOutProc far pascal GetProcAddress(int module, char far *name);
extern void far * far mem_Lock(unsigned int handle);
extern unsigned long far mem_Size(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern unsigned int far pascal GlobalAlloc(unsigned int flags,
                                            unsigned long bytes);
extern void far * far pascal GlobalLock(unsigned int handle);
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern void far WinPrintf(char far *format, ...);
extern int near _rootWnd;
static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;

void far MciOutWave(unsigned int handle)
{
    int far *moduleHandle;
    int far *waveHandle;
    int far *refCount;
    WaveOutProc prepare;
    WaveOutProc writeWave;
    WaveOutProc unprepare;
    WaveOutCloseProc closeWave;
    unsigned char far *packed;
    unsigned char far *pcm;
    unsigned char delta[16];
    struct WaveHeader far *header;
    unsigned int outputBytes;
    unsigned int i;
    unsigned int outIndex;
    unsigned char sample;

    moduleHandle = (int far *)&stateViaSelector.moduleHandle;
    prepare = GetProcAddress(*moduleHandle,
                             "waveOutPrepareHeader");
    packed = (unsigned char far *)mem_Lock(handle);

    vocBufLocked1 = GlobalAlloc(0x2002, 0x20L);
    header = (struct WaveHeader far *)GlobalLock(vocBufLocked1);
    vocBufLocked2 = GlobalAlloc(
        0x2002,
        (unsigned long)(outputBytes =
            (unsigned int)(mem_Size(handle) - 0x10L) << 1));
    header->data = GlobalLock(vocBufLocked2);
    pcm = (unsigned char far *)header->data;
    header->bufferLength = (unsigned long)outputBytes;
    sample = 0x80;
    for (i = 0; i != 16; ++i)
        delta[i] = packed[i];
    packed += 16;
    outIndex = 0;
    outputBytes >>= 1;
    for (i = 0; i < outputBytes; ++i) {
        unsigned char packedByte = packed[i];
        sample += delta[packedByte >> 4];
        pcm[outIndex++] = sample;
        sample += delta[packedByte & 0x0f];
        pcm[outIndex++] = sample;
    }

    header->bytesRecorded = 0L;
    header->user = (unsigned long)vocBufLocked1 |
                   ((unsigned long)vocBufLocked2 << 16);
    header->flags = 0L;
    header->loops = 0L;
    WinPrintf("myBeginSound:  WaveHeader(%lu)(%#x)\n",
              (unsigned long)outputBytes * 2L, (unsigned int)_rootWnd);
    refCount = (int far *)&stateViaSelector.refCount;
    ++*refCount;

    waveHandle = (int far *)&stateViaSelector.waveHandle;
    if (prepare &&
        prepare(*waveHandle, header, 0x20) == 0) {
        writeWave = GetProcAddress(*moduleHandle,
                                   "waveOutWrite");
        if (writeWave &&
            writeWave(*waveHandle, header, 0x20) == 0) {
            unprepare = GetProcAddress(*moduleHandle,
                                       "waveOutUnprepareHeader");
            WinPrintf("myBeginSound: Error trying to out mci wave.\n");
            WinPrintf("MciOutWave(flags)(%#x)\n", header->flags);
            if (unprepare &&
                (unprepare(*waveHandle, header, 0x20) == 0)) {
                GlobalUnlock(vocBufLocked2);
                GlobalFree(vocBufLocked2);
                vocBufLocked2 = 0;
                GlobalUnlock(vocBufLocked1);
                GlobalFree(vocBufLocked1);
                vocBufLocked1 = 0;
                if (--*refCount == 0) {
                    closeWave = (WaveOutCloseProc)GetProcAddress(
                        *moduleHandle, "waveOutClose");
                    if (closeWave) {
                        closeWave(*waveHandle);
                        *waveHandle = 0;
                    }
                }
            } else {
                GlobalUnlock(vocBufLocked2);
                GlobalFree(vocBufLocked2);
                vocBufLocked2 = 0;
                GlobalUnlock(vocBufLocked1);
                GlobalFree(vocBufLocked1);
                vocBufLocked1 = 0;
                if (--*refCount == 0) {
                    closeWave = (WaveOutCloseProc)GetProcAddress(
                        *moduleHandle, "waveOutClose");
                    if (closeWave) {
                        closeWave(*waveHandle);
                        *waveHandle = 0;
                    }
                }
            }
        } else {
            WinPrintf("myBeginSound: Unable to prepare wave header.\n");
            GlobalUnlock(vocBufLocked2);
            GlobalFree(vocBufLocked2);
            vocBufLocked2 = 0;
            GlobalUnlock(vocBufLocked1);
            GlobalFree(vocBufLocked1);
            vocBufLocked1 = 0;
            if (--*refCount == 0) {
                closeWave = (WaveOutCloseProc)GetProcAddress(
                    *moduleHandle, "waveOutClose");
                if (closeWave) {
                    closeWave(*waveHandle);
                    *waveHandle = 0;
                }
            }
        }
    }
    mem_Unlock(handle);
}
