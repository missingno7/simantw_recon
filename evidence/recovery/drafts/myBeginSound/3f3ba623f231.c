/* Load one sound database object and route it through the shared multimedia
 * device state. The MCI record tail and dynamic entry points remain open. */
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
struct WaveRecord {
    unsigned int format;
    unsigned int headerBytes;
    unsigned long dataBytes;
    unsigned int channels;
    unsigned int rate;
    unsigned int sampleBits;
    unsigned int flags;
};
extern int near effectsOnFlag;
extern int near rootWnd;
extern unsigned int far db_LoadObject(unsigned int id, unsigned int kind,
                                      unsigned int flags);
extern unsigned long far db_GetObjectSize(unsigned int id, unsigned int type,
                                           unsigned int index);
extern void far db_ReleaseHandle(unsigned int handle);
extern void far * far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern unsigned long far mem_Size(unsigned int handle);
extern void far WinPrintf(const char far *format, ...);
extern void far * far pascal GetProcAddress(unsigned int module,
                                             const char far *name);
extern unsigned int far pascal GlobalAlloc(unsigned int flags,
                                            unsigned long bytes);
extern void far * far pascal GlobalLock(unsigned int handle);
extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern int far pascal GlobalPageLock(unsigned int handle);
extern int far pascal GlobalPageUnlock(unsigned int handle);
extern int far pascal GlobalWire(unsigned int handle);
extern int far pascal GlobalUnWire(unsigned int handle);
extern unsigned long far pascal GetTickCount(void);
extern int far pascal LoadCursor(unsigned int instance, unsigned int cursor);
extern int far pascal SetCursor(unsigned int cursor);
extern int far pascal PeekMessage(void far *message, int hwnd, unsigned int min,
                                 unsigned int max, unsigned int remove);
extern int far pascal TranslateMessage(void far *message);
extern int far pascal DispatchMessage(void far *message);
extern void far MciOutWave(unsigned int handle);
void far myBeginSound(unsigned int soundId)
{
    unsigned int kind;
    unsigned int object;
    unsigned int globalBlock;
    unsigned int globalData;
    unsigned int cursor;
    unsigned long objectSize;
    unsigned long dataSize;
    unsigned char far *locked;
    unsigned char far *copy;
    struct WaveRecord far *record;
    unsigned char message[32];
    void far *sendCommand;
    void far *notifyWindow;
    unsigned long start;
    unsigned int i;

    if (stateViaSelector.moduleHandle == 0)
        return;
    if (effectsOnFlag == 0)
        return;

    kind = stateViaSelector.waveInstalled == 1 ? 0x33 : 0x105;
    object = db_LoadObject(soundId, kind, 1);
    if (object == 0) {
        WinPrintf("myBeginSound: load failed %u\n", soundId);
        return;
    }
    WinPrintf("myBeginSound(%u)\n", soundId);

    sendCommand = GetProcAddress(stateViaSelector.moduleHandle,
                                 "mciSendCommand");
    if (sendCommand == 0 || stateViaSelector.waveHandle == 0) {
        db_ReleaseHandle(object);
        return;
    }
    locked = (unsigned char far *)mem_Lock(object);
    objectSize = db_GetObjectSize(soundId, 5, 2);
    if (locked == 0 || objectSize < 0x10) {
        if (locked != 0)
            mem_Unlock(object);
        db_ReleaseHandle(object);
        return;
    }

    record = (struct WaveRecord far *)locked;
    dataSize = (unsigned long)(objectSize - 0x10) * 2L;
    globalBlock = GlobalAlloc(0x2000, dataSize + sizeof(message));
    if (globalBlock == 0) {
        mem_Unlock(object);
        db_ReleaseHandle(object);
        return;
    }
    GlobalPageLock(globalBlock);
    GlobalWire(globalBlock);
    copy = (unsigned char far *)GlobalLock(globalBlock);
    if (copy == 0) {
        GlobalUnWire(globalBlock);
        GlobalPageUnlock(globalBlock);
        GlobalFree(globalBlock);
        mem_Unlock(object);
        db_ReleaseHandle(object);
        return;
    }

    for (i = 0; i < 16; ++i)
        message[i] = locked[i];
    for (i = 0; i < dataSize; ++i)
        copy[i] = locked[i + 16];
    record->headerBytes = 0;
    start = GetTickCount();
    globalData = stateViaSelector.waveHandle;
    cursor = LoadCursor(0, 32512);
    notifyWindow = (void far *)rootWnd;
    if (notifyWindow != 0 && cursor != 0)
        SetCursor(cursor);
    ((int (far pascal *)(unsigned int, unsigned int, unsigned int,
                         unsigned int, void far *))sendCommand)(
                             globalData, 0x806, soundId, start, copy);
    if (kind == 0x33)
        MciOutWave(object);

    GlobalUnlock(globalBlock);
    GlobalUnWire(globalBlock);
    GlobalPageUnlock(globalBlock);
    GlobalFree(globalBlock);
    mem_Unlock(object);
    db_ReleaseHandle(object);
}
