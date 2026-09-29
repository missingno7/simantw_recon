struct MSG {
    int hwnd;
    unsigned int message;
    unsigned int wParam;
    long lParam;
    unsigned long time;
    int pt_x;
    int pt_y;
};
/* _myBeginSound: packed resource decode and multimedia output paths. */
struct MultimediaState {
    int moduleHandle;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
    union {
        unsigned int songState;
        struct {
            unsigned int closeHandle;
            void far *pageBuffer;
        } firstChannel;
        struct {
            unsigned int channel0Handle;
            unsigned int channel0State;
            unsigned int channel0Page;
        } channel0;
    } channel0State;
    unsigned int closeHandle;
    union {
        void far *pointer;
        struct {
            unsigned int offset;
            unsigned int selector;
        } words;
    } pageBuffer;
};
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)
#define state8d06 (*(unsigned int __based(mmSelector) *)((char __based(mmSelector) *)&mmState - 2))
#define state8d1e (stateViaSelector.channel0State.channel0.channel0State)
#define state8d20 (stateViaSelector.channel0State.channel0.channel0Page)
#define state8d22 (stateViaSelector.closeHandle)
#define state8d24 (stateViaSelector.pageBuffer.words.offset)
#define state8d26 (stateViaSelector.pageBuffer.words.selector)
#define state8d28 (*(unsigned int __based(mmSelector) *)((char __based(mmSelector) *)&mmState + 0x20))
#define DB_RESOURCE_POINTER(segment, offset) ((char far *)(((unsigned long)(segment) << 16) | (unsigned int)(offset)))
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
struct WaveOpenRecord {
    unsigned int tag;
    unsigned int channels;
    unsigned long samplesPerSecond;
    unsigned long averageBytesPerSecond;
    unsigned int blockAlign;
    unsigned int bitsPerSample;
};
struct MultimediaTime {
    unsigned int type;
    unsigned long milliseconds;
};
struct RiffWave {
    unsigned long riff;
    unsigned long riffBytes;
    unsigned long wave;
    unsigned long fmt;
    unsigned long fmtBytes;
    unsigned int formatTag;
    unsigned int channels;
    unsigned long samplesPerSecond;
    unsigned long averageBytesPerSecond;
    unsigned int blockAlign;
    unsigned int bitsPerSample;
    unsigned long data;
    unsigned long dataBytes;
    unsigned char samples[1];
};
struct SoundMessage {
    unsigned int hwnd;
    unsigned int message;
    unsigned int wParam;
    unsigned long lParam;
    unsigned long time;
    int x;
    int y;
};
typedef int (far *MMProc)(void);
typedef int (far pascal *MMOneWordProc)(unsigned int);
typedef int (far pascal *LegacySoundProc)(unsigned char far *, unsigned long,
                                          unsigned int, unsigned int,
                                          unsigned int, unsigned int);
typedef int (far pascal *WaveHeaderProc)(unsigned int,
                                          struct WaveHeader far *,
                                          unsigned int);
typedef int (far pascal *MciProc)(unsigned int, unsigned int,
                                  unsigned int, void far *);
typedef int (far pascal *WaveOpenProc)(unsigned int far *, unsigned int,
                                       void far *, unsigned int,
                                       unsigned int, unsigned int,
                                       unsigned int, unsigned int,
                                       unsigned int, unsigned int,
                                       unsigned int);
typedef int (far pascal *SndPlayProc)(const char far *, unsigned int);
extern int near effectsOnFlag;

extern int near rootWnd;
static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;
static unsigned long near soundDeadline = 0;
extern unsigned int far db_LoadObject(int object, int kind, int lock);

extern int db_GetObjectSize(char far *name);
extern void db_ReleaseHandle(unsigned int handle);

extern void far * far mem_Lock(unsigned int);
extern int far mem_Unlock(unsigned int);
extern void far WinPrintf(char far *format, ...);
extern char far * far strcpy(char far *destination, char far *source);

extern MMProc far pascal GetProcAddress(int handle, char far *name);

extern unsigned int far pascal GlobalAlloc(unsigned int, unsigned long);
extern void far * far pascal GlobalLock(unsigned int);
extern int far pascal GlobalUnlock(unsigned int);
extern int far pascal GlobalPageLock(unsigned int);
extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);

extern int far pascal GlobalWire(unsigned int);
extern int far pascal GlobalUnWire(unsigned int);
extern unsigned int far pascal GlobalFree(unsigned int);
extern unsigned int far pascal LocalAlloc(unsigned int, unsigned int);
extern void far * far pascal LocalLock(unsigned int);
extern int far pascal LocalUnlock(unsigned int);
extern unsigned int far pascal LocalFree(unsigned int);
extern unsigned long far pascal GetTickCount(void);
extern unsigned int far pascal LoadCursor(unsigned int instance,
                                          char far *name);

extern unsigned int far pascal SetCursor(unsigned int);
extern int far pascal PeekMessage(struct MSG far *message,
                                  int hwnd, unsigned int first,
                                  unsigned int last, unsigned int remove);

extern int far pascal TranslateMessage(struct MSG far *message);

extern long far pascal DispatchMessage(struct MSG far *message);

extern int far pascal CloseSound(void);
extern void far MciOutWave(unsigned int);

void far myBeginSound(unsigned int soundId, unsigned int device,
                      unsigned int reserved)
{
    unsigned int kind;
    unsigned int object;
    unsigned int buffer;
    unsigned int cleanupBuffer1;
    unsigned int cleanupBuffer2;
    unsigned int localBlock;
    unsigned int cursor;
    unsigned int i;
    unsigned int count;
    unsigned int result;
    unsigned int far *state8d28Pointer;
    unsigned int far * volatile modulePointer;
    unsigned int far *state8d22Pointer;
    unsigned int far *waveHandlePointer;
    unsigned int bytes;
    unsigned int objectSize;
    unsigned long beganAt;
    unsigned long now;
    unsigned long headerFlags;
    unsigned char sample;
    unsigned char packed;
    unsigned char delta[16];
    unsigned char delta2[16];
    unsigned char far *source;
    unsigned char far *output;
    struct WaveHeader far *header;
    struct RiffWave far *riff;
    struct WaveOpenRecord far *format;
    struct SoundMessage message;
    MMProc getState;
    MMProc closeState;
    MMProc finishState;
    MMProc resetWave;
    MMProc getDevice;
    MMProc playSoundAddress;
    SndPlayProc sndPlay;
    WaveHeaderProc getPosition;
    WaveHeaderProc prepare;
    WaveHeaderProc writeWave;
    WaveHeaderProc unprepare;
    WaveOpenProc openWave;
    MciProc sendMci;

    if (state8d06 == 0)
        goto done;
    if (effectsOnFlag == 0)
        goto done;

    state8d28Pointer = (unsigned int far *)&state8d28;
    kind = (*state8d28Pointer == 0) ? 5 : 0x33;
    object = db_LoadObject(soundId, kind, 1);
    if (object != 0) {
    WinPrintf("Sound loaded: SUCCESS(%d)", soundId);

    /* Stop the prior MCI wave and discard its page-locked buffers. */
    modulePointer = (unsigned int far *)&stateViaSelector.moduleHandle;
    if (*modulePointer != 0) {
    if (stateViaSelector.soundInstalled == 0) {
    getState = GetProcAddress(*modulePointer,
                              "vocOpenDevice");
    state8d22Pointer = (unsigned int far *)&state8d22;
    if (*state8d22Pointer != 0) {
        closeState = GetProcAddress(*modulePointer,
                                    "vocStopVoice");
        if (closeState != 0) {
            result = ((MMOneWordProc)closeState)(*modulePointer);
            if (result != 0)
                WinPrintf("SBPro Error(vocStopVoice)(%u)\n", result);
        }
        finishState = GetProcAddress(*modulePointer,
                                     "vocCloseDevice");
        if (finishState != 0)
            ((MMOneWordProc)finishState)(0);
        if (state8d26 != 0) {
            GlobalPageUnlock(state8d26);
            GlobalUnWire(state8d26);
            GlobalFree(state8d26);
            state8d26 = 0;
        }
        if (state8d24 != 0) {
            GlobalPageUnlock(state8d24);
            GlobalUnWire(state8d24);
            GlobalFree(state8d24);
            state8d24 = 0;
        }
        state8d26 = 0;
        state8d24 = 0;
    }
    if (getState != 0) {
        result = ((MMOneWordProc)getState)(rootWnd);
        if (result != 0) {
            WinPrintf("SBPro Error(vocOpenDevice)(%u)\n", result);
            goto finish_object;
        }
    }

    sendMci = (MciProc)GetProcAddress(*modulePointer,
                                      "vocPlayMemUnFormat");

    /* Decode the packed four bit deltas into a page-locked sample buffer. */
    source = (unsigned char far *)mem_Lock(object);
    buffer = GlobalAlloc(2,
        bytes = ((unsigned int)(db_GetObjectSize(
            DB_RESOURCE_POINTER(5, soundId)) - 0x10) << 1));
    *state8d22Pointer = buffer;
    state8d26 = buffer;
    output = (unsigned char far *)GlobalLock(buffer);
    GlobalWire(buffer);
    for (i = 0; i < 16; ++i)
        delta[i] = source[i];
    sample = 0x80;
    count = (unsigned int)(bytes >> 1);
    for (i = 0; i < count; ++i) {
        packed = source[0x10 + i];
        sample += delta[packed >> 4];
        output[i * 2] = sample;
        sample += delta[packed & 15];
        output[i * 2 + 1] = sample;
    }
    GlobalPageLock(buffer);
    WinPrintf("vocPlayMemUnFormat(start)(%ld)\n", bytes);

    /* The sound DLL accepts the decoded object as an unformatted wave block. */
    result = sendMci(stateViaSelector.waveHandle, 0, 0x1000,
                     (void far *)output);
    if (result != 0) {
        WinPrintf("SBPro Error(vocPlayMemUnFormat)(%u)\n", result);
        finishState = GetProcAddress(*modulePointer,
                                     "vocCloseDevice");
        if (finishState != 0)
            ((MMOneWordProc)finishState)(0);
        GlobalPageUnlock(state8d26);
        GlobalUnWire(*state8d22Pointer);
        GlobalFree(*state8d22Pointer);
        *state8d22Pointer = 0;
        state8d24 = 0;
        state8d26 = 0;
    }
    mem_Unlock(object);
    WinPrintf("vocPlayMemUnFormat(done)\n");
    goto finish_object;
    }

event_pump:
    waveHandlePointer = (unsigned int far *)&stateViaSelector.waveHandle;
    if (PeekMessage(&message, rootWnd, 0, 0x3bd, 1)) {
        do {
            TranslateMessage(&message);
            DispatchMessage(&message);
        } while (PeekMessage(&message, rootWnd, 0, 0x3bd, 1));
    }

    /* Only reclaim the old device after both buffers pass their deadline. */
    if (*waveHandlePointer != 0 &&
        vocBufLocked1 != 0 && vocBufLocked2 != 0) {
        WinPrintf("Wave device still in use.\n");
        now = GetTickCount();
        if (now <= soundDeadline)
            goto done;

    /* Reset the current wave output and release its prepared headers. */
    resetWave = GetProcAddress(*modulePointer, "waveOutReset");
    unprepare = (WaveHeaderProc)GetProcAddress(
        *modulePointer, "waveOutUnprepareHeader");
    if (resetWave != 0)
        ((MMOneWordProc)resetWave)(*waveHandlePointer);
    if (vocBufLocked1 != 0) {
        header = (struct WaveHeader far *)GlobalLock(vocBufLocked1);
        WinPrintf("myBeginSound:  WaveHeader(%lu)(%#x)", header->flags);
        headerFlags = header->flags;
        headerFlags &= ~0x1fL;
        if (headerFlags == 0) {
            unprepare(*waveHandlePointer, header, 0x20);
            GlobalUnlock(vocBufLocked1);
            cleanupBuffer1 = vocBufLocked1;
            cleanupBuffer2 = vocBufLocked2;
        } else {
            GlobalUnlock(vocBufLocked1);
            vocBufLocked2 = 0;
            vocBufLocked1 = 0;
            cleanupBuffer2 = 0;
            cleanupBuffer1 = 0;
        }
        if (cleanupBuffer2 != 0) {
            GlobalUnlock(cleanupBuffer2);
            GlobalFree(cleanupBuffer2);
            vocBufLocked2 = 0;
        }
        if (cleanupBuffer1 != 0) {
            GlobalUnlock(cleanupBuffer1);
            GlobalFree(cleanupBuffer1);
            vocBufLocked1 = 0;
        }
    }
    if (--stateViaSelector.refCount == 0) {
        closeState = GetProcAddress(*modulePointer,
                                    "waveOutClose");
        if (closeState != 0) {
            ((MMOneWordProc)closeState)(*waveHandlePointer);
            *waveHandlePointer = 0;
        }
    }
    }

    /* Open waveOut, then use sndPlaySound when waveOut cannot start. */
    openWave = (WaveOpenProc)GetProcAddress(*modulePointer,
                                             "waveOutOpen");
    localBlock = LocalAlloc(2, 0x10);
    format = (struct WaveOpenRecord far *)LocalLock(localBlock);
    format->tag = 1;
    format->channels = 1;
    format->samplesPerSecond = 0x1000L;
    format->averageBytesPerSecond = 0x1000L;
    format->blockAlign = 1;
    format->bitsPerSample = 8;
    result = openWave(waveHandlePointer, 0, format, rootWnd, 0, 1,
                      0, 0, 0, 0, 0);
    if (result == 0) {
        MciOutWave(object);
        LocalUnlock(localBlock);
        LocalFree(localBlock);
        goto wave_position;
    }

    playSoundAddress = GetProcAddress(*modulePointer,
                                      "sndPlaySound");
    WinPrintf("myBeginSound: Unable to open wave device(%u).", result);
    if (playSoundAddress == 0) {
        LocalUnlock(localBlock);
        LocalFree(localBlock);
        goto wave_position;
    }
    sndPlay = (SndPlayProc)playSoundAddress;
    source = (unsigned char far *)mem_Lock(object);
    buffer = GlobalAlloc(0x2002,
        (bytes = db_GetObjectSize(DB_RESOURCE_POINTER(5, soundId)),
         bytes = ((unsigned int)(bytes - 0x10) << 1),
         bytes + 0x2c));
    vocBufLocked2 = buffer;
    riff = (struct RiffWave far *)GlobalLock(buffer);
    strcpy((char far *)&riff->riff, "RIFF");
    riff->riffBytes = bytes + 8L;
    strcpy((char far *)&riff->wave, "WAVE");
    strcpy((char far *)&riff->fmt, "fmt ");
    riff->fmtBytes = 0x10L;
    riff->formatTag = 1;
    riff->channels = 1;
    riff->samplesPerSecond = 0x1000L;
    riff->averageBytesPerSecond = 0x1000L;
    riff->blockAlign = 1;
    riff->bitsPerSample = 8;
    strcpy((char far *)&riff->data, "data");
    riff->dataBytes = bytes;
    for (i = 0; i < 16; ++i)
        delta2[i] = source[i];
    sample = 0x80;
    count = (unsigned int)(bytes >> 1);
    for (i = 0; i < count; ++i) {
        packed = source[0x10 + i];
        sample += delta2[packed >> 4];
        riff->samples[i * 2] = sample;
        sample += delta2[packed & 15];
        riff->samples[i * 2 + 1] = sample;
    }
    result = sndPlay((const char far *)riff, 0x14);
    if (result != 0)
        WinPrintf("Play Sound(success)");
    else
        WinPrintf("Play Sound(failure)");
    GlobalUnlock(vocBufLocked2);
    GlobalFree(vocBufLocked2);
    vocBufLocked2 = 0;
    mem_Unlock(object);
    LocalUnlock(localBlock);
    LocalFree(localBlock);

wave_position:
    if (*waveHandlePointer != 0) {
    struct MultimediaTime timeRecord;
        getPosition = (WaveHeaderProc)GetProcAddress(
            *modulePointer, "waveOutGetPosition");
        timeRecord.type = 1;
        getPosition(*waveHandlePointer,
                    (struct WaveHeader far *)&timeRecord, 8);
        soundDeadline = GetTickCount() + timeRecord.milliseconds;
    }
    goto finish_object;
    }

old_sound:
    if (*state8d28Pointer == 0)
        goto finish_object;
    playSoundAddress = GetProcAddress(*modulePointer,
                                      "PlaySound");
    if (playSoundAddress == 0)
        goto finish_object;
    sndPlay = (SndPlayProc)playSoundAddress;
    cursor = LoadCursor(0, 0x7f02);
    cursor = SetCursor(cursor);
    if (*modulePointer != 0 &&
        stateViaSelector.waveInstalled == 0) {
        if (stateViaSelector.soundInstalled == 0) {
            sendMci = (MciProc)GetProcAddress(*modulePointer,
                                              "mciSendCommand");
            WinPrintf("Midi: Close Device");
            if (sendMci != 0) {
                sendMci(stateViaSelector.waveHandle, 0x804, 0,
                        (void far *)&message);
                stateViaSelector.waveHandle = 0;
                goto close_sound;
            }
        }
        finishState = GetProcAddress(*modulePointer,
                                     "musStopMusic");
        if (finishState != 0) {
            result = ((MMOneWordProc)finishState)(0);
            if (result != 0)
                WinPrintf("SBPro Error(musStopMusic)(%u)", result);
        }
        getDevice = GetProcAddress(*modulePointer,
                                   "musCloseDevice");
        if (getDevice != 0)
            ((MMProc)getDevice)();
        if (state8d20 != 0)
            GlobalPageUnlock(state8d20);
        if (stateViaSelector.channel0State.songState != 0) {
            GlobalUnWire(stateViaSelector.channel0State.songState);
            GlobalFree(stateViaSelector.channel0State.songState);
            stateViaSelector.channel0State.songState = 0;
        }
        state8d20 = 0;
        state8d1e = 0;
    }
close_sound:
    CloseSound();
    source = (unsigned char far *)mem_Lock(object);
    GlobalPageLock(object);
    objectSize = db_GetObjectSize(DB_RESOURCE_POINTER(0x33, soundId));
    ((LegacySoundProc)sndPlay)(source, (unsigned long)objectSize,
                               reserved, 0, 0x32, 4);
    GlobalPageUnlock(object);
    mem_Unlock(object);
    goto finish_object;

finish_object:
    if (object != 0) {
        SetCursor(cursor);
        db_ReleaseHandle(object);
    }
    goto done;

    } else {
        WinPrintf("Sound loaded: FAILURE(%d)", soundId);
    }

done:
    return;
}
