/* Reconstructed body of the sound playback dispatcher. */
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
    unsigned int state16;
    unsigned int state18;
    unsigned int state1a;
    unsigned int state1c;
    unsigned int state1e;
    unsigned int soundMode;
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
struct WaveMessage {
    unsigned int hwnd;
    unsigned int message;
    unsigned int wParam;
    unsigned long lParam;
    unsigned long time;
    int x;
    int y;
};
struct WaveOpenRecord {
    unsigned int device;
    unsigned int flags;
    unsigned long callback;
    unsigned int instance;
    unsigned int formatTag;
    unsigned int channels;
    unsigned long samplesPerSecond;
    unsigned long averageBytesPerSecond;
    unsigned int blockAlign;
    unsigned int bitsPerSample;
};

typedef int (far *MMProc)(void);
typedef int (far pascal *MMOneWordProc)(unsigned int);
typedef int (far pascal *WaveHeaderProc)(unsigned int,
                                          struct WaveHeader far *,
                                          unsigned int);
typedef int (far pascal *MciCommandProc)(unsigned int, unsigned int,
                                          unsigned int, void far *);
typedef int (far pascal *WaveOpenProc)(unsigned int far *, unsigned int,
                                        void far *, unsigned int,
                                        unsigned int, unsigned int,
                                        unsigned int, unsigned int,
                                        unsigned int, unsigned int,
                                        unsigned int);

extern int near effectsOnFlag;
extern int near rootWnd;
static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;
extern unsigned int far db_LoadObject(unsigned int id, unsigned int kind,
                                      unsigned int lock);
extern unsigned long far db_GetObjectSize(unsigned int id, unsigned int type,
                                           unsigned int index);
extern void far db_ReleaseHandle(unsigned int handle);
extern void far * far mem_Lock(unsigned int handle);
extern int far mem_Unlock(unsigned int handle);
extern void far WinPrintf(const char far *format, ...);
extern MMProc far pascal GetProcAddress(unsigned int module,
                                        const char far *name);
extern unsigned int far pascal GlobalAlloc(unsigned int flags,
                                            unsigned long bytes);
extern void far * far pascal GlobalLock(unsigned int handle);
extern int far pascal GlobalUnlock(unsigned int handle);
extern int far pascal GlobalPageLock(unsigned int handle);
extern int far pascal GlobalPageUnlock(unsigned int handle);
extern int far pascal GlobalWire(unsigned int handle);
extern int far pascal GlobalUnWire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern unsigned int far pascal LocalAlloc(unsigned int flags,
                                           unsigned int bytes);
extern void far * far pascal LocalLock(unsigned int handle);
extern int far pascal LocalUnlock(unsigned int handle);
extern unsigned int far pascal LocalFree(unsigned int handle);
extern unsigned long far pascal GetTickCount(void);
extern unsigned int far pascal LoadCursor(unsigned int instance,
                                           unsigned int cursor);
extern unsigned int far pascal SetCursor(unsigned int cursor);
extern int far pascal PeekMessage(struct WaveMessage far *message,
                                  int hwnd, unsigned int first,
                                  unsigned int last, int remove);
extern int far pascal TranslateMessage(struct WaveMessage far *message);
extern int far pascal DispatchMessage(struct WaveMessage far *message);
extern int far pascal CloseSound(void);
extern void far MciOutWave(unsigned int handle);

void far myBeginSound(unsigned int soundId, unsigned int soundMode,
                      unsigned int soundDevice)
{
    unsigned int kind;
    unsigned int object;
    unsigned int oldBuffer;
    unsigned int localBlock;
    unsigned int outputBlock;
    unsigned int cursor;
    unsigned int device;
    unsigned int messageResult;
    unsigned int sampleCount;
    unsigned int inputCount;
    unsigned int i;
    unsigned int j;
    unsigned long objectSize;
    unsigned long outputSize;
    unsigned long beganAt;
    unsigned long now;
    unsigned long elapsed;
    unsigned char sample;
    unsigned char packed;
    unsigned char high;
    unsigned char low;
    unsigned char deltaTable[16];
    unsigned char far *lockedObject;
    unsigned char far *waveBytes;
    unsigned char far *pcmBytes;
    struct WaveHeader far *waveHeader;
    struct WaveOpenRecord far *openRecord;
    struct WaveMessage message;
    unsigned int far *stateBefore;
    MMProc proc0;
    MMProc proc1;
    MMProc proc2;
    MMProc proc3;
    MMProc proc4;
    MMProc proc5;
    WaveHeaderProc prepareHeader;
    WaveHeaderProc writeHeader;
    WaveHeaderProc unprepareHeader;
    WaveOpenProc openWave;
    MciCommandProc sendCommand;
    int error;

    /* Entry state and the effects switch. */
    stateBefore = (unsigned int far *)&stateViaSelector.moduleHandle;
    if (stateBefore[-1] != 0) {
        if (stateViaSelector.soundInstalled == 0)
            goto tail_message;
        goto device_path;
    }
    if (effectsOnFlag == 0)
        goto done;

    /* Load and identify the packed sound object. */
    kind = stateViaSelector.soundMode == 1 ? 0x33 : 0x105;
    object = db_LoadObject(soundId, kind, 1);
    if (object == 0)
        goto done;
    WinPrintf("myBeginSound(%u)\n", soundId);

    /* Resolve the active multimedia module and discard the previous buffer. */
    if (stateViaSelector.moduleHandle == 0)
        goto legacy_output;
    if (stateViaSelector.soundInstalled == 0)
        goto close_mci;
    proc0 = GetProcAddress(stateViaSelector.moduleHandle,
                           "sbcGetDLLVersion");
    if (stateViaSelector.state1a == 0)
        goto close_mci;
    proc1 = GetProcAddress(stateViaSelector.moduleHandle,
                           "sbcGetCardName");
    if (proc1 != 0) {
        messageResult = ((MMOneWordProc)proc1)(stateViaSelector.moduleHandle);
        if (messageResult != 0)
            WinPrintf("myBeginSound: sound device %u\n", messageResult);
    }
    proc2 = GetProcAddress(stateViaSelector.moduleHandle, "sbcTerminateDLL");
    if (proc2 != 0)
        ((MMOneWordProc)proc2)(0);
    if (stateViaSelector.state1e != 0) {
        GlobalPageUnlock(stateViaSelector.state1e);
        GlobalUnWire(stateViaSelector.state1e);
        GlobalFree(stateViaSelector.state1e);
        stateViaSelector.state1e = 0;
    }
    if (stateViaSelector.state1c != 0) {
        GlobalPageUnlock(stateViaSelector.state1c);
        GlobalUnWire(stateViaSelector.state1c);
        GlobalFree(stateViaSelector.state1c);
        stateViaSelector.state1c = 0;
    }
    stateViaSelector.state18 = 0;
    stateViaSelector.state16 = 0;
    if (proc0 != 0) {
        messageResult = ((MMOneWordProc)proc0)(rootWnd);
        if (messageResult != 0)
            WinPrintf("myBeginSound: device ready %u\n", messageResult);
    }

    /* Lock the packed record, allocate decoded samples, and expand its nibbles. */
    lockedObject = (unsigned char far *)mem_Lock(object);
    objectSize = db_GetObjectSize(soundId, 5, 2);
    outputSize = (objectSize - 0x10L) * 2L;
    outputBlock = GlobalAlloc(0, outputSize);
    stateViaSelector.state1e = outputBlock;
    waveBytes = (unsigned char far *)GlobalLock(outputBlock);
    for (i = 0; i < 16; ++i)
        deltaTable[i] = lockedObject[i];
    sample = 0x80;
    inputCount = (unsigned int)(outputSize >> 1);
    for (i = 0; i < inputCount; ++i) {
        packed = lockedObject[0x10 + i];
        high = packed >> 4;
        low = packed & 0x0f;
        sample += deltaTable[high];
        waveBytes[i * 2] = sample;
        sample += deltaTable[low];
        waveBytes[i * 2 + 1] = sample;
    }
    GlobalPageLock(outputBlock);
    GlobalWire(outputBlock);
    WinPrintf("myBeginSound: packed data %lu bytes\n", outputSize);

    /* Submit the decoded block through the MCI interface. */
    sendCommand = (MciCommandProc)GetProcAddress(
        stateViaSelector.moduleHandle, "mciSendCommand");
    if (sendCommand == 0) {
        GlobalUnWire(outputBlock);
        GlobalPageUnlock(outputBlock);
        GlobalUnlock(outputBlock);
        GlobalFree(outputBlock);
        stateViaSelector.state1e = 0;
        mem_Unlock(object);
        WinPrintf("myBeginSound: MCI command entry missing\n");
        goto done_with_object;
    }
    error = sendCommand(stateViaSelector.waveHandle, 0x806, 0x1000,
                        (void far *)waveBytes);
    if (error != 0) {
        WinPrintf("myBeginSound: MCI command error %u\n", error);
        GlobalUnWire(outputBlock);
        GlobalPageUnlock(outputBlock);
        GlobalUnlock(outputBlock);
        GlobalFree(outputBlock);
        stateViaSelector.state1e = 0;
        mem_Unlock(object);
        goto done_with_object;
    }
    beganAt = GetTickCount();
    stateViaSelector.refCount++;
    stateViaSelector.songState = soundId;
    cursor = LoadCursor(0, 32512);
    if (rootWnd != 0 && cursor != 0)
        SetCursor(cursor);

    /* Pump only the sound notification messages while this block is active. */
    do {
        if (PeekMessage(&message, rootWnd, 0, 0, 1)) {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
        now = GetTickCount();
        elapsed = now - beganAt;
    } while (stateViaSelector.refCount != 0 && elapsed < 1000L);

    /* Release the first pair of global handles, then run waveOut callbacks. */
    if (vocBufLocked1 != 0) {
        oldBuffer = vocBufLocked1;
        waveHeader = (struct WaveHeader far *)GlobalLock(oldBuffer);
        if (waveHeader != 0)
            WinPrintf("MciOutWave(flags)(%#x)\n", (unsigned int)waveHeader->flags);
        prepareHeader = (WaveHeaderProc)GetProcAddress(
            stateViaSelector.moduleHandle, "waveOutPrepareHeader");
        writeHeader = (WaveHeaderProc)GetProcAddress(
            stateViaSelector.moduleHandle, "waveOutWrite");
        if (prepareHeader != 0 && waveHeader != 0 &&
            prepareHeader(stateViaSelector.waveHandle, waveHeader, 0x20) == 0) {
            if (writeHeader != 0)
                writeHeader(stateViaSelector.waveHandle, waveHeader, 0x20);
        }
        GlobalUnlock(oldBuffer);
        GlobalUnWire(oldBuffer);
        GlobalPageUnlock(oldBuffer);
        GlobalFree(oldBuffer);
        vocBufLocked1 = 0;
    }
    if (vocBufLocked2 != 0) {
        GlobalUnlock(vocBufLocked2);
        GlobalUnWire(vocBufLocked2);
        GlobalPageUnlock(vocBufLocked2);
        GlobalFree(vocBufLocked2);
        vocBufLocked2 = 0;
    }
    if (--stateViaSelector.refCount == 0) {
        proc3 = GetProcAddress(stateViaSelector.moduleHandle, "waveOutClose");
        if (proc3 != 0) {
            ((MMOneWordProc)proc3)(stateViaSelector.waveHandle);
            stateViaSelector.waveHandle = 0;
        }
    }
    if (stateViaSelector.state1e != 0) {
        proc4 = GetProcAddress(stateViaSelector.moduleHandle,
                               "waveOutReset");
        if (proc4 != 0)
            ((MMOneWordProc)proc4)(stateViaSelector.state1e);
        stateViaSelector.state1e = 0;
    }
    if (stateViaSelector.state1c != 0) {
        proc5 = GetProcAddress(stateViaSelector.moduleHandle,
                               "sbcTerminateDLL");
        if (proc5 != 0)
            ((MMOneWordProc)proc5)(stateViaSelector.state1c);
        stateViaSelector.state1c = 0;
    }

    /* Build a second wave record for the asynchronous driver path. */
    localBlock = LocalAlloc(2, 0x10);
    if (localBlock == 0) {
        MciOutWave(object);
        goto service_existing;
    }
    openRecord = (struct WaveOpenRecord far *)LocalLock(localBlock);
    if (openRecord == 0) {
        LocalUnlock(localBlock);
        LocalFree(localBlock);
        MciOutWave(object);
        goto service_existing;
    }
    openRecord->device = 1;
    openRecord->flags = 1;
    openRecord->callback = 0x1000L;
    openRecord->instance = 0;
    openRecord->formatTag = 0x1000;
    openRecord->channels = 0;
    openRecord->samplesPerSecond = 1L;
    openRecord->averageBytesPerSecond = 0x1000L;
    openRecord->blockAlign = 1;
    openRecord->bitsPerSample = 8;
    openWave = (WaveOpenProc)GetProcAddress(stateViaSelector.moduleHandle,
                                              "waveOutOpen");
    if (openWave == 0) {
        LocalUnlock(localBlock);
        LocalFree(localBlock);
        MciOutWave(object);
        goto service_existing;
    }
    device = stateViaSelector.waveHandle;
    error = openWave(&device, 0, openRecord, rootWnd, 0, 1,
                     0, 0, 0, 0, 0);
    if (error != 0) {
        WinPrintf("myBeginSound: unable to open wave output\n");
        LocalUnlock(localBlock);
        LocalFree(localBlock);
        MciOutWave(object);
        goto service_existing;
    }
    stateViaSelector.waveHandle = device;

    /* Decode the record again into the output buffer expected by waveOut. */
    lockedObject = (unsigned char far *)mem_Lock(object);
    objectSize = db_GetObjectSize(soundId, 5, 0x2002);
    outputSize = (objectSize - 0x10L) * 2L;
    outputBlock = GlobalAlloc(0, outputSize + 0x2cL);
    stateViaSelector.state1c = outputBlock;
    waveHeader = (struct WaveHeader far *)GlobalLock(outputBlock);
    pcmBytes = (unsigned char far *)((unsigned long)waveHeader + 0x2cL);
    waveHeader->bufferLength = outputSize;
    waveHeader->bytesRecorded = 0;
    waveHeader->user = ((unsigned long)vocBufLocked1 << 16) | vocBufLocked2;
    waveHeader->flags = 0;
    waveHeader->loops = 0;
    waveHeader->next = 0;
    waveHeader->reserved = 0;
    for (i = 0; i < 16; ++i)
        deltaTable[i] = lockedObject[i];
    sample = 0x80;
    inputCount = (unsigned int)(outputSize >> 1);
    for (i = 0; i < inputCount; ++i) {
        packed = lockedObject[0x10 + i];
        sample += deltaTable[packed >> 4];
        pcmBytes[i * 2] = sample;
        sample += deltaTable[packed & 0x0f];
        pcmBytes[i * 2 + 1] = sample;
    }
    unprepareHeader = (WaveHeaderProc)GetProcAddress(
        stateViaSelector.moduleHandle, "waveOutPrepareHeader");
    if (unprepareHeader == 0 ||
        unprepareHeader(stateViaSelector.waveHandle, waveHeader, 0x14) != 0) {
        WinPrintf("myBeginSound: Unable to prepare wave header.\n");
        goto second_wave_failed;
    }
    beganAt = GetTickCount();
    cursor = LoadCursor(0, 32512);
    if (rootWnd != 0 && cursor != 0)
        SetCursor(cursor);
    sendCommand = (MciCommandProc)GetProcAddress(
        stateViaSelector.moduleHandle, "mciSendCommand");
    if (sendCommand != 0)
        error = sendCommand(stateViaSelector.waveHandle, 0x806, 0x1000,
                            (void far *)waveHeader);
    else
        error = 1;
    if (error == 0) {
        while (stateViaSelector.songState != 0 &&
               GetTickCount() - beganAt < 1000L) {
            if (PeekMessage(&message, rootWnd, 0, 0, 1)) {
                TranslateMessage(&message);
                DispatchMessage(&message);
            }
        }
    }
    LocalUnlock(localBlock);
    LocalFree(localBlock);
    mem_Unlock(object);
    goto service_existing;

second_wave_failed:
    if (waveHeader != 0) {
        GlobalUnWire(outputBlock);
        GlobalPageUnlock(outputBlock);
        GlobalUnlock(outputBlock);
        GlobalFree(outputBlock);
        stateViaSelector.state1c = 0;
    }
    LocalUnlock(localBlock);
    LocalFree(localBlock);
    mem_Unlock(object);
    goto service_existing;

close_mci:
    sendCommand = (MciCommandProc)GetProcAddress(
        stateViaSelector.moduleHandle, "mciSendCommand");
    if (sendCommand != 0) {
        sendCommand(stateViaSelector.waveHandle, 0x804, 0x1000,
                    (void far *)&message);
        stateViaSelector.waveHandle = 0;
    }
    goto legacy_output;

legacy_output:
    /* The non-MCI path uses the legacy sound library and its local record. */
    if (stateViaSelector.moduleHandle == 0 || stateViaSelector.waveInstalled == 0) {
        CloseSound();
        lockedObject = (unsigned char far *)mem_Lock(object);
        GlobalPageLock(object);
        objectSize = db_GetObjectSize(soundId, 0x33, 4);
        proc2 = GetProcAddress(stateViaSelector.moduleHandle,
                               "sbcGetCardName");
        if (proc2 != 0)
            ((MMOneWordProc)proc2)(soundDevice);
        GlobalPageUnlock(object);
        mem_Unlock(object);
        SetCursor(soundDevice);
        db_ReleaseHandle(object);
        goto done;
    }

    /* Release a previous asynchronous wave handle before re-opening it. */
    if (stateViaSelector.state1a == 0)
        goto device_path;
    proc3 = GetProcAddress(stateViaSelector.moduleHandle, "waveOutClose");
    if (proc3 != 0) {
        ((MMOneWordProc)proc3)(stateViaSelector.state1a);
        stateViaSelector.state1a = 0;
    }
    proc4 = GetProcAddress(stateViaSelector.moduleHandle, "waveOutOpen");
    if (proc4 == 0)
        goto device_path;
    cursor = LoadCursor(0, 0x7f02);
    SetCursor(cursor);
    error = ((MMOneWordProc)proc4)(stateViaSelector.state1a);
    if (error != 0)
        goto device_path;
    stateViaSelector.state18 = 0;

    /* The callback path prepares and writes the current sound header. */
    if (stateViaSelector.soundInstalled == 0)
        goto device_path;
    if (stateViaSelector.waveInstalled == 0)
        goto device_path;
    prepareHeader = (WaveHeaderProc)GetProcAddress(
        stateViaSelector.moduleHandle, "waveOutPrepareHeader");
    if (prepareHeader != 0) {
        waveHeader = (struct WaveHeader far *)GlobalLock(stateViaSelector.state1c);
        if (waveHeader != 0) {
            error = prepareHeader(stateViaSelector.waveHandle,
                                  waveHeader, 0x20);
            if (error == 0) {
                writeHeader = (WaveHeaderProc)GetProcAddress(
                    stateViaSelector.moduleHandle, "waveOutWrite");
                if (writeHeader != 0)
                    writeHeader(stateViaSelector.waveHandle,
                                waveHeader, 0x20);
            }
        }
    }
    goto service_existing;

service_existing:
    /* Close or unprepare the asynchronous header when its callback is done. */
    if (stateViaSelector.state1a != 0) {
        unprepareHeader = (WaveHeaderProc)GetProcAddress(
            stateViaSelector.moduleHandle, "waveOutUnprepareHeader");
        if (unprepareHeader != 0) {
            waveHeader = (struct WaveHeader far *)GlobalLock(
                stateViaSelector.state1c);
            if (waveHeader != 0)
                unprepareHeader(stateViaSelector.waveHandle, waveHeader, 8);
        }
        stateViaSelector.state1a = 0;
    }
    if (stateViaSelector.state1c != 0) {
        GlobalUnlock(stateViaSelector.state1c);
        GlobalUnWire(stateViaSelector.state1c);
        GlobalPageUnlock(stateViaSelector.state1c);
        GlobalFree(stateViaSelector.state1c);
        stateViaSelector.state1c = 0;
    }
    if (stateViaSelector.state1e != 0) {
        GlobalUnlock(stateViaSelector.state1e);
        GlobalUnWire(stateViaSelector.state1e);
        GlobalPageUnlock(stateViaSelector.state1e);
        GlobalFree(stateViaSelector.state1e);
        stateViaSelector.state1e = 0;
    }
    if (--stateViaSelector.refCount == 0) {
        proc5 = GetProcAddress(stateViaSelector.moduleHandle, "waveOutClose");
        if (proc5 != 0) {
            ((MMOneWordProc)proc5)(stateViaSelector.waveHandle);
            stateViaSelector.waveHandle = 0;
        }
    }

tail_message:
    /* Drop the final sound objects and restore the caller's cursor. */
    if (object != 0) {
        mem_Unlock(object);
        db_ReleaseHandle(object);
    }
    messageResult = SetCursor(0);
    if (messageResult == 0)
        WinPrintf("myBeginSound: sound request complete\n");
    goto done;

device_path:
    /* A state-only completion may close the external DLL entry points. */
    if (stateViaSelector.moduleHandle != 0) {
        proc0 = GetProcAddress(stateViaSelector.moduleHandle,
                               "sbcTerminateDLL");
        if (proc0 != 0)
            ((MMOneWordProc)proc0)(stateViaSelector.moduleHandle);
        if (stateViaSelector.state18 != 0) {
            proc1 = GetProcAddress(stateViaSelector.moduleHandle,
                                   "waveOutReset");
            if (proc1 != 0)
                ((MMOneWordProc)proc1)(stateViaSelector.state18);
            stateViaSelector.state18 = 0;
        }
        stateViaSelector.state16 = 0;
    }
    if (object != 0) {
        mem_Unlock(object);
        db_ReleaseHandle(object);
    }
    goto done;

done_with_object:
    if (object != 0)
        db_ReleaseHandle(object);

done:
    return;
}
