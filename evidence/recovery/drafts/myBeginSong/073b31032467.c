#define MAKEINTRESOURCE(id) ((char far *)(unsigned long)(id))

typedef int (far *MMProc)(void);

extern MMProc far pascal GetProcAddress(int handle, char far *name);

extern unsigned int far pascal LoadCursor(unsigned int instance,
                                          char far *name);

extern unsigned int far pascal SetCursor(unsigned int cursor);
extern char far * far strrchr(const char far *text, int character);
extern int far _fmemcmp(const void far *left, const void far *right, unsigned int count);
extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern int far sprintf(char far *buffer, char far *format, ...);

extern void far WinPrintf(char far *format, ...);

extern int near hInst;
extern int near rootWnd;
extern int near songsOnFlag;
extern unsigned short far colorValue[];
extern unsigned char far Dx8[];
extern unsigned int far db_LoadObject(int object, int kind, int lock);

extern void db_ReleaseHandle(unsigned int handle);

extern void far * mem_Lock(unsigned int handle);
extern unsigned long mem_Size(unsigned handle);

extern int far mem_Unlock(unsigned int handle);

extern unsigned short FlipWord(unsigned short);

extern unsigned long far FlipLong(unsigned long value);
extern void near ExtractVariableLen(char far **cursor, unsigned long far *value, unsigned long far *remaining);
extern int far pascal OpenSound();
extern int far pascal CloseSound();
extern int far pascal SetVoiceQueueSize();
extern int far pascal SetVoiceNote();
extern int far pascal StartSound();
extern unsigned int far pascal GlobalAlloc(unsigned int flags, unsigned long bytes);
extern int far pascal GlobalPageLock(unsigned int handle);
extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);

extern void far * far pascal GlobalWire(unsigned int handle);
extern int far pascal GlobalUnWire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern int far pascal GlobalUnlock(unsigned int handle);

extern unsigned int far pascal GetModuleFileName(int hInstance, char far *path, unsigned int size);


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
    void far *pageBuffer;
};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) soundState = {0};
#define mmState (*(struct MultimediaState __based(mmSelector) *)&soundState)
static void far * __based(__segname("SIMANT_DATA_GROUP")) songBuffer = 0;

typedef int (far pascal *MidiNoArgProc)(void);
typedef int (far pascal *MidiOpenProc)(int);
typedef int (far pascal *MidiWordProc)(unsigned int);
typedef int (far pascal *MidiBufferProc)(void far *);
typedef int (far pascal *MciSendCommandProc)(unsigned int, unsigned int, unsigned long, void far *);
struct MidiOpenParms {
    unsigned long callback;
    unsigned int device;
    unsigned int reserved;
    char far *deviceType;
    char far *elementName;
    char far *alias;
};
struct MidiTimeParms {
    unsigned long callback;
    unsigned long timeFormat;
    unsigned long tempo;
    unsigned long songPointer;
};
struct ThreeBytes { unsigned char b[3]; };
union MidiTempoValue { unsigned long value; struct { unsigned char low; struct ThreeBytes high; } bytes; };

struct MidiFileHeader {
    char tag[4];
    unsigned long size;
    unsigned short format;
    unsigned short tracks;
    unsigned short division;
};

void far myBeginSong(unsigned int song)
{
    unsigned int songHandle;
    unsigned int memoryHandle;
    unsigned int activeSlot;
    unsigned int oldSong;
    unsigned int lookupColor;
    unsigned int loggedColor;
    unsigned int cursorHandle;
    unsigned int format;
    unsigned long trackLength;
    char far *songData;
    struct MidiOpenParms openParms;
    MMProc mciProc;
    MMProc soundProc;
    MMProc openMusicProc;
    int commandResult;

    if (mmState.moduleHandle == 0 || songsOnFlag == 0)
        return;

    WinPrintf("myBeginSong(find)(%d)\n", song);
    songHandle = db_LoadObject(song, 0x12, 1);
    if (songHandle == 0)
        return;

    songData = (unsigned char far *)mem_Lock(songHandle);
    format = FlipWord(*(unsigned short far *)songData);
    oldSong = FlipWord(*(unsigned short far *)(songData + 6));
    for (activeSlot = 0; colorValue[0x80 + activeSlot] != 0xffff &&
         colorValue[0x80 + activeSlot] != song; ++activeSlot)
        ;
    mem_Unlock(songHandle);
    db_ReleaseHandle(songHandle);
    lookupColor = colorValue[0x80 + activeSlot];
    loggedColor = lookupColor;
    if (lookupColor++ == 0xffff)
        return;

    WinPrintf("myBeginSong(shift=%d)(id=%d)(file=%s)\n",
              oldSong, loggedColor,
              ((char far * far *)(Dx8 + 0x8d2a))[activeSlot]);

    if (mmState.moduleHandle == 0 || mmState.waveInstalled != 0)
        goto mapper_cleanup;

    if (mmState.soundInstalled != 0) {
        char path[0x80];
        char midiPath[0x60];
        struct MidiTimeParms timeParms;

        mciProc = GetProcAddress(mmState.moduleHandle, "mciSendCommand");
        if (mciProc != 0) {
            cursorHandle = SetCursor(LoadCursor(0, MAKEINTRESOURCE(0x7f02)));
            if (mmState.waveInstalled != 0)
                goto mci_restore_cursor;

        if (mmState.midiHandle != 0 && mmState.moduleHandle != 0 &&
            mmState.waveInstalled == 0) {
            if (mmState.soundInstalled != 0) {
                mciProc = GetProcAddress(mmState.moduleHandle, "mciSendCommand");
                WinPrintf("Midi: Close Device\n");
                if (mciProc != 0)
                commandResult = ((MciSendCommandProc)mciProc)(mmState.midiHandle, 0x0804, 0L, &openParms);
                mmState.midiHandle = 0;
            } else {
                soundProc = GetProcAddress(mmState.moduleHandle, "musStopMusic");
                if (soundProc != 0) {
                    commandResult = ((MidiNoArgProc)soundProc)();
                    if (commandResult != 0)
                        WinPrintf("SBPro Error(musStopMusic)(%u)\n", commandResult);
                }
                soundProc = GetProcAddress(mmState.moduleHandle, "musCloseDevice");
                if (soundProc != 0)
                    ((MidiNoArgProc)soundProc)();
                GlobalUnWire(mmState.channel0State.songState);
                GlobalPageUnlock(mmState.channel0State.songState);
                GlobalFree(mmState.channel0State.songState);
                songBuffer = 0;
                mmState.channel0State.songState = 0;
            }
        }

        CloseSound();
        GetModuleFileName(hInst, path, 0x80);
        strrchr(path, 0x5c)[1] = 0;
        sprintf(midiPath, "%ssound\\%s.mid", path, ((char far * far *)(Dx8 + 0x8d2a))[activeSlot]);
        WinPrintf("Midi: %s\n", midiPath);

        openParms.callback = 0;
        openParms.device = 0;
        openParms.deviceType = 0;
        openParms.elementName = midiPath;
        openParms.alias = 0;
        commandResult = ((MciSendCommandProc)mciProc)(0, 0x0803, 0x200L, &openParms);
        if (commandResult != 0) {
            WinPrintf("MultiMedia Open: FAILURE\n");
            goto mci_restore_cursor;
        }

        mmState.midiHandle = openParms.device;
        WinPrintf("MultiMedia Open: SUCCESS\n");
        commandResult = ((MciSendCommandProc)mciProc)(mmState.midiHandle, 0x0814, 0x4003L, &timeParms);
        if (timeParms.timeFormat != 0xffff || timeParms.tempo != 0xffff)
            WinPrintf("Midi Mapper: NO\n");

        WinPrintf("Midi: Set Time\n");
        timeParms.timeFormat = 0xffff;
        timeParms.tempo = 0xffff;
        commandResult = ((MciSendCommandProc)mciProc)(mmState.midiHandle, 0x080d, 2L, &timeParms);
        if (commandResult != 0)
            WinPrintf("Midi Mapper: INSTALL FAILED\n");
        else
            WinPrintf("Midi Mapper: INSTALLED\n");

        timeParms.timeFormat = 0;
        timeParms.tempo = 0;
        ((MciSendCommandProc)mciProc)(mmState.midiHandle, 0x080d, 0x400L, &timeParms);
        WinPrintf("Midi: Start Play\n");
        ((MciSendCommandProc)mciProc)(mmState.midiHandle, 0x0806, 4L, &timeParms);

mci_restore_cursor:
            SetCursor(cursorHandle);
        } else {
            WinPrintf("Unable to get address: mciSendCommand.\n");
        }
        return;
    }

    openMusicProc = GetProcAddress(mmState.moduleHandle, "musOpenDevice");
    if (mmState.midiHandle != 0 && mmState.moduleHandle != 0 &&
        mmState.waveInstalled == 0) {
        if (mmState.soundInstalled != 0) {
            mciProc = GetProcAddress(mmState.moduleHandle, "mciSendCommand");
            WinPrintf("Midi: Close Device\n");
            if (mciProc != 0)
                ((MciSendCommandProc)mciProc)(mmState.midiHandle, 0x0804, 0L, &openParms);
            mmState.midiHandle = 0;
        } else {
            soundProc = GetProcAddress(mmState.moduleHandle, "musStopMusic");
            if (soundProc != 0) {
                commandResult = ((MidiNoArgProc)soundProc)();
                if (commandResult != 0)
                    WinPrintf("SBPro Error(musStopMusic)(%u)\n", commandResult);
            }
            soundProc = GetProcAddress(mmState.moduleHandle, "musCloseDevice");
            if (soundProc != 0)
                ((MidiNoArgProc)soundProc)();
            GlobalUnWire(mmState.channel0State.songState);
            GlobalPageUnlock(mmState.channel0State.songState);
            GlobalFree(mmState.channel0State.songState);
            songBuffer = 0;
            mmState.channel0State.songState = 0;
        }
    }

    CloseSound();
    if (openMusicProc == 0)
        return;
    commandResult = ((MidiOpenProc)openMusicProc)(rootWnd);
    if (commandResult != 0) {
        WinPrintf("SBPro Error(musOpenDevice)(%u)\n", commandResult);
        return;
    }

    memoryHandle = db_LoadObject(format, 0x14, 1);
    if (memoryHandle == 0)
        return;
    songData = (unsigned char far *)mem_Lock(memoryHandle);
    soundProc = GetProcAddress(mmState.moduleHandle, "musTransposeNote");
    if (soundProc != 0)
        ((MidiWordProc)soundProc)(oldSong);
    soundProc = GetProcAddress(mmState.moduleHandle, "musPlayMemMidi");
    if (songData != 0 && soundProc != 0) {
        mmState.channel0State.songState = GlobalAlloc(2, mem_Size(memoryHandle));
        songBuffer = (void far *)GlobalWire(mmState.channel0State.songState);
        trackLength = mem_Size(memoryHandle);
        _fmemcpy(songBuffer, songData, (unsigned int)trackLength);
        GlobalPageLock(mmState.channel0State.songState);
        commandResult = ((MidiBufferProc)soundProc)(songBuffer);
        if (commandResult != 0)
            WinPrintf("SBPro Error(musPlayMemMidi)(%u)\n", commandResult);
        soundProc = GetProcAddress(mmState.moduleHandle, "musCloseDevice");
        if (soundProc != 0)
            ((MidiNoArgProc)soundProc)();
        GlobalUnWire(mmState.channel0State.songState);
        GlobalPageUnlock(mmState.channel0State.songState);
        GlobalFree(mmState.channel0State.songState);
        songBuffer = 0;
        mmState.channel0State.songState = 0;
    }
    mem_Unlock(memoryHandle);

mapper_cleanup:
    if (mmState.midiHandle != 0 && mmState.moduleHandle != 0 &&
        mmState.soundInstalled != 0 && mmState.waveInstalled == 0) {
        mciProc = GetProcAddress(mmState.moduleHandle, "mciSendCommand");
        if (mciProc != 0) {
            WinPrintf("Midi: Close Device\n");
            ((MciSendCommandProc)mciProc)(mmState.midiHandle, 0x0804, 0L, &openParms);
            mmState.midiHandle = 0;
        } else {
            soundProc = GetProcAddress(mmState.moduleHandle, "musStopMusic");
            if (soundProc != 0) {
                commandResult = ((MidiNoArgProc)soundProc)();
                if (commandResult != 0)
                    WinPrintf("SBPro Error(musStopMusic)(%u)\n", commandResult);
            }
            soundProc = GetProcAddress(mmState.moduleHandle, "musCloseDevice");
            if (soundProc != 0)
                ((MidiNoArgProc)soundProc)();
            GlobalUnWire(mmState.channel0State.songState);
            GlobalPageUnlock(mmState.channel0State.songState);
            GlobalFree(mmState.channel0State.songState);
            songBuffer = 0;
            mmState.channel0State.songState = 0;
        }
    }

    CloseSound();
    if (OpenSound() == 0)
        return;

    memoryHandle = db_LoadObject(format, 0x32, 1);
    SetVoiceQueueSize(1, 0x1400);
    if (memoryHandle == 0)
        return;
    songData = (unsigned char far *)mem_Lock(memoryHandle);
    {
        unsigned int trackCount;
        unsigned int division;
        unsigned char status;
        unsigned int note;
        unsigned int velocity;
        unsigned int previousNote;
        unsigned int previousVelocity;
        int duration;
        int noteResult;
        int metadataLength;
        unsigned long remaining;
        unsigned long delta;
        union MidiTempoValue tempo;
        char far *cursor;
        unsigned char runningStatus;

        cursor = songData;

    WinPrintf("myBeginSong: %c%c%c%c\n",
              cursor[0], cursor[1], cursor[2], cursor[3]);
    if (_fmemcmp(cursor, "MThd", 4) != 0) {
        WinPrintf("Midi Header missing\n");
        goto midi_release;
    }

    cursor = (char far *)((unsigned long)cursor + 4);
    trackLength = *(unsigned long far *)cursor;
    trackLength = FlipLong(trackLength);
    cursor = (char far *)((unsigned long)cursor + 4);
    WinPrintf("Length = %#lx\n", trackLength);
    format = *(unsigned short far *)cursor;
    format = FlipWord(format);
    cursor = (char far *)((unsigned long)cursor + 2);
    trackCount = *(unsigned short far *)cursor;
    trackCount = FlipWord(trackCount);
    cursor = (char far *)((unsigned long)cursor + 2);
    division = *(unsigned short far *)cursor;
    division = FlipWord(division);
    cursor = (char far *)((unsigned long)cursor + 2);
    WinPrintf("Format = %#x, NTrks = %#x, Division = %#x\n",
              format, trackCount, division);

    if (_fmemcmp(cursor, "MTrk", 4) != 0) {
        WinPrintf("Midi Track 0 missing\n");
        goto midi_release;
    }
    cursor += 4;
    trackLength = FlipLong(*(unsigned long far *)cursor);
    cursor += 4;
    remaining = trackLength;
    if ((remaining >> 16) == 0 && (unsigned short)remaining == 0)
        goto track0_done;
track0_loop:
    {
        ExtractVariableLen(&cursor, &delta, &remaining);
        WinPrintf("DeltaTime: %lu\n", delta);
        if (*cursor == -1) {
            ++cursor;
            --remaining;
            if (*cursor != 0x51) {
                ++cursor;
                --remaining;
                metadataLength = (unsigned char)*cursor;
                cursor += metadataLength + 1;
                remaining -= metadataLength + 1;
            } else {
                cursor += 2;
                remaining -= 2;
                tempo.value = 0;
                tempo.bytes.high = *(struct ThreeBytes far *)cursor;
                tempo.value = FlipLong(tempo.value);
                cursor += 3;
                remaining -= 3;
                WinPrintf("SetTempo: %lu %#lx\n", tempo.value, tempo.value);
            }
        } else {
            WinPrintf("Unknown command\n");
        }
        if ((remaining >> 16) != 0)
            goto track0_loop;
        if ((unsigned short)remaining != 0)
            goto track0_loop;
    }
track0_done:
    ;

    if (_fmemcmp(cursor, "MTrk", 4) != 0) {
        WinPrintf("Midi Track 1 missing\n");
        goto midi_release;
    }
    cursor += 4;
    remaining = FlipLong(*(unsigned long far *)cursor);
    cursor += 4;

    cursor = (char far *)((unsigned long)cursor + remaining);
    if (_fmemcmp(cursor, "MTrk", 4) == 0) {
        cursor += 4;
        remaining = FlipLong(*(unsigned long far *)cursor);
        cursor += 4;
    } else {
        WinPrintf("Unable to skip track.\n");
        cursor = (char far *)((unsigned long)cursor - remaining);
    }

    runningStatus = 0;
    previousNote = 0;
    previousVelocity = 0;
    while (remaining > 1) {
        ExtractVariableLen(&cursor, &delta, &remaining);
        if (*cursor & 0x80) {
            runningStatus = *cursor++;
            --remaining;
        }
        status = runningStatus;
        switch (status) {
        case 0x80: case 0x81: case 0x82: case 0x83:
        case 0x84: case 0x85: case 0x86: case 0x87:
        case 0x88: case 0x89: case 0x8a: case 0x8b:
        case 0x8c: case 0x8d: case 0x8e:
            cursor += 2;
            remaining -= 2;
            if ((short)(delta >> 16) == 0 && (unsigned short)delta == 0)
                duration = 1;
            else {
                duration = (unsigned int)(delta / (division * 4));
                if (duration == 0)
                    duration = 1;
            }
            if (duration > 0x20)
                duration = 0x20;
            noteResult = SetVoiceNote(1,
                                      previousVelocity == 0 ? 0 : previousNote + oldSong,
                                      duration, 0);
            switch (noteResult) {
            case -7: WinPrintf("Invalid Dot Count.\n"); break;
            case -6: WinPrintf("Invalid Note Length.\n"); break;
            case -5: WinPrintf("Invalid Note.\n"); break;
            case -4: WinPrintf("Sound Queue Full.\n"); break;
            }
            previousNote = 0;
            previousVelocity = 0;
            break;

        case 0x90: case 0x91: case 0x92: case 0x93:
        case 0x94: case 0x95: case 0x96: case 0x97:
        case 0x98: case 0x99: case 0x9a: case 0x9b:
        case 0x9c: case 0x9d: case 0x9e: case 0x9f:
            note = *cursor++ - 0x1e;
            --remaining;
            velocity = *cursor++;
            --remaining;
            if ((short)(delta >> 16) == 0 && (unsigned short)delta == 0)
                duration = 1;
            else {
                duration = (unsigned int)(delta / (division * 4));
                if (duration == 0)
                    duration = 1;
            }
            if (duration > 0x20)
                duration = 0x20;
            noteResult = SetVoiceNote(1,
                                      previousVelocity == 0 ? 0 : previousNote + oldSong,
                                      duration, 0);
            switch (noteResult) {
            case -7: WinPrintf("Invalid Dot Count.\n"); break;
            case -6: WinPrintf("Invalid Note Length.\n"); break;
            case -5: WinPrintf("Invalid Note.\n"); break;
            case -4: WinPrintf("Sound Queue Full.\n"); break;
            }
            previousNote = note;
            previousVelocity = velocity;
            break;

        case 0xb0: case 0xb1: case 0xb2: case 0xb3:
        case 0xb4: case 0xb5: case 0xb6: case 0xb7:
        case 0xb8: case 0xb9: case 0xba: case 0xbb:
        case 0xbc: case 0xbd: case 0xbe:
            WinPrintf("Set Parameters\n");
            cursor += 2;
            remaining -= 2;
            break;

        case 0xc0: case 0xc1: case 0xc2: case 0xc3:
        case 0xc4: case 0xc5: case 0xc6: case 0xc7:
        case 0xc8: case 0xc9: case 0xca: case 0xcb:
        case 0xcc: case 0xcd: case 0xce:
            WinPrintf("Program Change\n");
            cursor = (char far *)((unsigned long)cursor + 1);
            --remaining;
            break;

        case 0xff:
            WinPrintf("Meta Event\n");
            cursor = (char far *)((unsigned long)cursor + 1);
            --remaining;
            ExtractVariableLen(&cursor, &delta, &remaining);
            cursor += delta;
            remaining -= delta;
            break;

        default:
            WinPrintf("Unknown command: %#x\n", status);
            break;
        }
    }
    StartSound();

midi_release:
        mem_Unlock(memoryHandle);
        db_ReleaseHandle(memoryHandle);
    }
    return;
}
