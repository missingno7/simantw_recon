typedef unsigned long (far pascal *MMProc)();
extern MMProc far pascal GetProcAddress(unsigned int module, char far *name);
extern int far pascal LoadCursor(unsigned int instance, unsigned int cursor);
extern unsigned int far pascal SetCursor(unsigned int cursor);
extern char far * far strrchr(const char far *text, int character);
extern int far _fmemcmp(const void far *left, const void far *right, unsigned int count);
extern void far *_fmemcpy(void far *destination, const void far *source, unsigned int count);
extern int far sprintf(char far *buffer, const char far *format, ...);
extern void far WinPrintf(const char far *format, ...);
extern int near hInst;
extern int near rootWnd;
extern int far songsOnFlag;
extern unsigned int far db_LoadObject(unsigned int object, unsigned int kind, unsigned int lock);
extern void far db_ReleaseHandle(unsigned int handle);
extern void far * mem_Lock(unsigned int handle);
extern unsigned long mem_Size(unsigned int handle);
extern void mem_Unlock(unsigned int handle);
extern unsigned short far FlipWord(unsigned short value);
extern unsigned long far FlipLong(unsigned long value);
extern unsigned long ExtractVariableLen(unsigned char far **cursor, unsigned long far *remaining);
extern int far pascal OpenSound();
extern int far pascal CloseSound();
extern int far pascal SetVoiceQueueSize();
extern int far pascal SetVoiceNote();
extern int far pascal StartSound();
extern unsigned int far pascal GlobalAlloc(unsigned int flags, unsigned long bytes);
extern int far pascal GlobalPageLock(unsigned int handle);
extern int far pascal GlobalPageUnlock(unsigned int handle);
extern void far * far pascal GlobalWire(unsigned int handle);
extern int far pascal GlobalUnWire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern unsigned int far pascal GlobalUnlock(unsigned int handle);
extern char far * far pascal GetModuleFileName(unsigned int instance, char far *path, unsigned int maximum);

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
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) soundState = {0};
#define mmState (*(struct MultimediaState __based(mmSelector) *)&soundState)
static void far * __based(__segname("SIMANT_DATA_GROUP")) songBuffer = 0;
static char far * __based(__segname("SIMANT_DATA_GROUP")) songFileNames[32] = {0};
static int __based(__segname("SIMANT_DATA_GROUP")) activeSongIds[32] = {0};

typedef unsigned long (far pascal *MidiProc)();
struct MidiOpenParms {
    unsigned int callback;
    unsigned int device;
    char far *deviceType;
    char far *elementName;
    char far *alias;
};
struct MidiTimeParms {
    unsigned int timeFormat;
    unsigned int tempo;
    unsigned int meter;
    unsigned int songPointer;
};
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
    unsigned int midiHandle;
    unsigned int memoryHandle;
    unsigned int musicGlobalHandle;
    unsigned int slot;
    unsigned int oldSong;
    unsigned int cursorHandle;
    unsigned int format;
    unsigned int trackCount;
    unsigned int division;
    unsigned int trackNumber;
    unsigned int status;
    unsigned int eventType;
    unsigned int note;
    unsigned int velocity;
    unsigned int duration;
    unsigned int program;
    unsigned long fileSize;
    unsigned long trackLength;
    unsigned long remaining;
    unsigned long delta;
    unsigned long tempo;
    unsigned long ticks;
    unsigned long allocationSize;
    unsigned char far *songData;
    unsigned char far *cursor;
    unsigned char far *trackEnd;
    unsigned char runningStatus;
    char path[0x80];
    char midiPath[0x80];
    struct MidiOpenParms openParms;
    struct MidiTimeParms timeParms;
    MidiProc mciProc;
    MidiProc soundProc;
    long commandResult;
    int parseFailed;

    /* A loaded multimedia module and enabled song output are preconditions. */
    if (mmState.moduleHandle == 0)
        return;
    if (songsOnFlag == 0)
        return;
    WinPrintf("myBeginSong(find)(%d)\n", song);

    /* Read the song's database record, then locate an already active slot. */
    songHandle = db_LoadObject(song, 0x12, 1);
    if (songHandle == 0)
        return;
    songData = (unsigned char far *)mem_Lock(songHandle);
    if (songData == 0) {
        db_ReleaseHandle(songHandle);
        return;
    }
    slot = FlipWord(*(unsigned short far *)songData);
    oldSong = FlipWord(*(unsigned short far *)(songData + 6));
    parseFailed = 0;
    for (trackNumber = 0; activeSongIds[trackNumber] != 0xffff; ++trackNumber) {
        if (activeSongIds[trackNumber] == song)
            break;
    }
    mem_Unlock(songHandle);
    db_ReleaseHandle(songHandle);

    /* Close an MCI device already associated with this song-table slot. */
    if (activeSongIds[trackNumber] != 0xffff) {
        WinPrintf("myBeginSong(shift=%d)(id=%d)(file=%s)\n",
                  slot, oldSong, songFileNames[trackNumber]);
        mciProc = GetProcAddress(mmState.moduleHandle, "mciSendCommand");
        cursorHandle = SetCursor(LoadCursor(0, 0x7f02));
        if (mmState.moduleHandle != 0 && mmState.soundInstalled != 0 &&
            mmState.waveInstalled == 0 && mmState.midiHandle != 0 &&
            mciProc != 0) {
            WinPrintf("Midi: Close Device\n");
            commandResult = mciProc(mmState.midiHandle, 0x0804, 0L, &openParms);
            mmState.midiHandle = 0;
            if (commandResult == 0) {
                soundProc = GetProcAddress(mmState.moduleHandle, "musStopMusic");
                if (soundProc != 0) {
                    commandResult = soundProc();
                    if (commandResult != 0)
                        WinPrintf("SBPro Error(musStopMusic)(%u)\n", commandResult);
                }
                soundProc = GetProcAddress(mmState.moduleHandle, "musCloseDevice");
                if (soundProc != 0) {
                    soundProc();
                    GlobalPageUnlock(musicGlobalHandle);
                    GlobalUnWire(musicGlobalHandle);
                    GlobalFree(musicGlobalHandle);
                    songBuffer = 0;
                    mmState.songState = 0;
                }
            }
        }
    }
old_song_done:

    /* Resolve MCI, name this song's file, and open the MIDI device. */
    mciProc = GetProcAddress(mmState.moduleHandle, "mciSendCommand");
    if (mciProc == 0) {
        WinPrintf("Unable to get address: mciSendCommand.\n");
        goto finish;
    }
    cursorHandle = SetCursor(LoadCursor(0, 0x7f02));
    if (mmState.moduleHandle == 0 || mmState.waveInstalled != 0 ||
        mmState.soundInstalled != 0)
        goto finish;
    if (songFileNames[slot] == 0)
        goto finish;
    GetModuleFileName(hInst, path, 0x80);
    strrchr(path, 0x5c)[1] = 0;
    sprintf(midiPath, "%ssound\\%s.mid", path, songFileNames[slot]);
    WinPrintf("Midi: %s\n", midiPath);
    openParms.callback = 0;
    openParms.device = 0;
    openParms.deviceType = 0;
    openParms.elementName = midiPath;
    openParms.alias = 0;
    commandResult = mciProc(0, 0x0803, 0x200L, &openParms);
    if (commandResult != 0) {
        WinPrintf("MultiMedia Open: FAILURE\n");
        goto finish;
    }
    mmState.midiHandle = openParms.device;
    WinPrintf("MultiMedia Open: SUCCESS\n");

    /* Verify MCI status and initialize the Sound Blaster music mapper. */
    commandResult = mciProc(mmState.midiHandle, 0x0814, 0x4003L, &timeParms);
    if (timeParms.timeFormat == 0xffff && timeParms.tempo == 0xffff) {
        WinPrintf("Midi Mapper: NO\n");
    } else {
        soundProc = GetProcAddress(mmState.moduleHandle, "musOpenDevice");
        if (soundProc == 0) {
            WinPrintf("Midi Mapper: NO\n");
            goto finish;
        }
        commandResult = soundProc(rootWnd);
        if (commandResult != 0) {
            WinPrintf("Midi Mapper: YES\n");
        } else {
            WinPrintf("Midi Mapper: NO\n");
            goto finish;
        }
    }
    WinPrintf("Midi: Set Time\n");
    timeParms.timeFormat = 0;
    timeParms.tempo = 0;
    timeParms.meter = 0;
    commandResult = mciProc(mmState.midiHandle, 0x080d, 2L, &timeParms);
    if (commandResult != 0)
        WinPrintf("Midi Mapper: INSTALL FAILED\n");
    WinPrintf("Midi: Start Play\n");
    commandResult = mciProc(mmState.midiHandle, 0x080d, 0x4003L, &timeParms);
    if (commandResult != 0)
        goto finish;
    commandResult = mciProc(mmState.midiHandle, 0x0806, 4L, &timeParms);
    if (commandResult != 0)
        goto finish;

    /* The 0x14 object carries the mapper's transpose/play data. */
    memoryHandle = db_LoadObject(slot, 0x14, 1);
    if (memoryHandle == 0)
        goto finish;
    songData = (unsigned char far *)mem_Lock(memoryHandle);
    soundProc = GetProcAddress(mmState.moduleHandle, "musTransposeNote");
    if (soundProc != 0)
        commandResult = soundProc(oldSong);
    soundProc = GetProcAddress(mmState.moduleHandle, "musPlayMemMidi");
    if (songData != 0 && soundProc != 0) {
        musicGlobalHandle = GlobalAlloc(2, mem_Size(memoryHandle));
        songBuffer = (void far *)GlobalWire(musicGlobalHandle);
        fileSize = mem_Size(memoryHandle);
        _fmemcpy(songBuffer, songData, (unsigned int)fileSize);
        GlobalPageLock(musicGlobalHandle);
        commandResult = soundProc(songBuffer);
        if (commandResult != 0)
            WinPrintf("SBPro Error(musPlayMemMidi)(%u)\n", commandResult);
        soundProc = GetProcAddress(mmState.moduleHandle, "musCloseDevice");
        if (soundProc != 0)
            soundProc();
        GlobalPageUnlock(musicGlobalHandle);
        GlobalUnWire(musicGlobalHandle);
        GlobalFree(musicGlobalHandle);
        songBuffer = 0;
    }
    mem_Unlock(memoryHandle);
    db_ReleaseHandle(memoryHandle);

    /* A second active-device branch clears the same private MCI state. */
    if (mmState.songState != 0 && mmState.moduleHandle != 0 &&
        mmState.soundInstalled != 0 && mmState.waveInstalled == 0 &&
        mmState.midiHandle != 0) {
        mciProc = GetProcAddress(mmState.moduleHandle, "mciSendCommand");
        if (mciProc != 0) {
            WinPrintf("Midi: Close Device\n");
            commandResult = mciProc(mmState.midiHandle, 0x0804, 0L, &openParms);
            mmState.midiHandle = 0;
            soundProc = GetProcAddress(mmState.moduleHandle, "musStopMusic");
            if (soundProc != 0) {
                commandResult = soundProc();
                if (commandResult != 0)
                    WinPrintf("SBPro Error(musStopMusic)(%u)\n", commandResult);
            }
            soundProc = GetProcAddress(mmState.moduleHandle, "musCloseDevice");
            if (soundProc != 0) {
                soundProc();
                GlobalPageUnlock(musicGlobalHandle);
                GlobalUnWire(musicGlobalHandle);
                GlobalFree(musicGlobalHandle);
                songBuffer = 0;
                mmState.songState = 0;
            }
        }
    }

    /* OpenSound and the 0x32 object provide the MIDI event stream. */
    CloseSound();
    if (OpenSound() == 0)
        goto finish;
    memoryHandle = db_LoadObject(slot, 0x32, 1);
    SetVoiceQueueSize(1, 0x1400);
    if (memoryHandle == 0)
        goto finish;
    songData = (unsigned char far *)mem_Lock(memoryHandle);

    /* The locked object remains the far source for the parser below. */
    fileSize = mem_Size(memoryHandle);

    /* Check the standard MIDI header and report its fields. */
    WinPrintf("myBeginSong: %c%c%c%c\n", songData[0], songData[1], songData[2], songData[3]);
    if (_fmemcmp(songData, "MThd", 4) != 0) {
        WinPrintf("Midi Header missing\n");
        parseFailed = 1;
        goto midi_done;
    }
    cursor = songData + 4;
    trackLength = FlipLong(*(unsigned long far *)cursor);
    cursor += 4;
    WinPrintf("Length = %#lx\n", trackLength);
    format = FlipWord(*(unsigned short far *)cursor);
    cursor += 2;
    trackCount = FlipWord(*(unsigned short far *)cursor);
    cursor += 2;
    division = FlipWord(*(unsigned short far *)cursor);
    cursor += 2;
    WinPrintf("Format = %#x, NTrks = %#x, Division = %#x\n",
              format, trackCount, division);

    /* Track zero contains the tempo map; skip unsupported metadata safely. */
    if (_fmemcmp(cursor, "MTrk", 4) != 0) {
        WinPrintf("Midi Track 0 missing\n");
        parseFailed = 1;
        goto midi_done;
    }
    cursor += 4;
    trackLength = FlipLong(*(unsigned long far *)cursor);
    cursor += 4;
    remaining = trackLength;
    ticks = 0;
    while (remaining != 0) {
        delta = ExtractVariableLen(&cursor, &remaining);
        ticks += delta;
        if (*cursor == 0xff) {
            ++cursor;
            --remaining;
            eventType = *cursor++;
            --remaining;
            trackLength = ExtractVariableLen(&cursor, &remaining);
            if (eventType == 0x51) {
                tempo = 0;
                ((unsigned char far *)&tempo)[1] = cursor[0];
                ((unsigned char far *)&tempo)[2] = cursor[1];
                ((unsigned char far *)&tempo)[3] = cursor[2];
                tempo = FlipLong(tempo);
                cursor += 3;
                remaining -= 3;
                WinPrintf("SetTempo: %lu %#lx\n", delta, tempo);
            } else {
                cursor += (unsigned int)trackLength;
                remaining -= trackLength;
            }
        } else {
            WinPrintf("Unknown command\n");
            ++cursor;
            --remaining;
        }
    }

    /* The second track carries notes; use the MIDI status byte as a dense switch. */
    if (trackCount < 2 || _fmemcmp(cursor, "MTrk", 4) != 0) {
        WinPrintf("Midi Track 1 missing\n");
        parseFailed = 1;
        goto midi_done;
    }
    cursor += 4;
    trackLength = FlipLong(*(unsigned long far *)cursor);
    cursor += 4;
    remaining = trackLength;
    runningStatus = 0;
    while (remaining != 0) {
        delta = ExtractVariableLen(&cursor, &remaining);
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
            break;
        case 0x90: case 0x91: case 0x92: case 0x93:
        case 0x94: case 0x95: case 0x96: case 0x97:
        case 0x98: case 0x99: case 0x9a: case 0x9b:
        case 0x9c: case 0x9d: case 0x9e: case 0x9f:
            note = *cursor++ - 0x1e;
            velocity = *cursor++;
            remaining -= 2;
            duration = delta / ((unsigned long)division * 4);
            if (duration == 0)
                duration = 1;
            if (duration > 0x20)
                duration = 0x20;
            if (velocity == 0)
                program = SetVoiceNote(1, 0, duration, 0);
            else
                program = SetVoiceNote(1, note + oldSong, duration, 0);
            if (program == (unsigned int)-7)
                WinPrintf("Invalid Dot Count.\n");
            else if (program == (unsigned int)-8)
                WinPrintf("Invalid Note Length.\n");
            else if (program == (unsigned int)-9)
                WinPrintf("Invalid Note.\n");
            else if (program == (unsigned int)-10)
                WinPrintf("Sound Queue Full.\n");
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
            ++cursor;
            --remaining;
            break;
        case 0xff:
            WinPrintf("Meta Event\n");
            ++cursor;
            --remaining;
            trackLength = ExtractVariableLen(&cursor, &remaining);
            cursor += (unsigned int)trackLength;
            remaining -= trackLength;
            break;
        default:
            WinPrintf("Unknown command: %#x\n", status);
            break;
        }
    }
    StartSound();

midi_done:
    if (songBuffer != 0) {
        GlobalUnWire(musicGlobalHandle);
        GlobalPageUnlock(musicGlobalHandle);
        GlobalFree(musicGlobalHandle);
        songBuffer = 0;
    }
    if (memoryHandle != 0) {
        mem_Unlock(memoryHandle);
        db_ReleaseHandle(memoryHandle);
    }
    if (parseFailed)
        CloseSound();
finish:
    SetCursor(cursorHandle);
    return;
}
