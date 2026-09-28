/*
 * StopSong: stop the current MIDI/SoundBlaster song through the private
 * multimedia module state (SIMANT_DATA_GROUP, same object family as the
 * admitted IsMMWaveAvail/musSoundBlasterClose/vocMciClose: module handle
 * at 0x8d08, plus unnamed flag/handle words at 0x8d0a/0x8d0c/0x8d0e/
 * 0x8d1c/0x8d1e/0x8d20).  If the module isn't loaded, or the "installed"
 * flag (0x8d0c) is clear, just call the legacy CLOSESOUND driver entry.
 * Otherwise, when the MCI flag (0x8d0a) is set, resolve and invoke
 * mciSendCommand to close the MCI device (logging "Midi: Close Device")
 * and clear the device id; when clear, resolve and invoke musStopMusic
 * (logging any nonzero error via "SBPro Error(musStopMusic)(%u)") and
 * musCloseDevice, then release the wired page/handle and zero the three
 * state words.  GetProcAddress names come from the wSoundBlasterMsg near
 * string table (base 0xaf4, matching the admitted siblings).
 */
typedef int (far *MMProc)(void);
typedef void (far pascal *VoidProc)(void);
typedef unsigned int (far pascal *ErrProc)(void);
typedef void (far pascal *MciProc)(unsigned int deviceId, unsigned int msg,
                                    unsigned long flags, void far *params);

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
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)

extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);
extern unsigned int far pascal GlobalUnwire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern void far pascal CloseSound(void);
extern void far WinPrintf(char far *format, ...);
extern char near wSoundBlasterMsg[2];

void far StopSong(void)
{
    long mciParams[2];
    MciProc mciProc;
    ErrProc stopProc;
    VoidProc closeProc;
    unsigned int err;
    int far *moduleHandle;

    moduleHandle = (int far *)&stateViaSelector.moduleHandle;
    if (*moduleHandle == 0 || stateViaSelector.waveInstalled != 0) {
        CloseSound();
        return;
    }

    if (stateViaSelector.soundInstalled != 0) {
        mciProc = (MciProc)GetProcAddress(*moduleHandle, wSoundBlasterMsg + 0x1c2);
        WinPrintf("Midi: Close Device\n");
        if (mciProc != 0)
            mciProc(stateViaSelector.midiHandle, 0x804, 0, mciParams);
        stateViaSelector.midiHandle = 0;
        return;
    }

    stopProc = (ErrProc)GetProcAddress(*moduleHandle, wSoundBlasterMsg + 0x1e5);
    if (stopProc != 0) {
        err = stopProc();
        if (err != 0)
            WinPrintf("SBPro Error(musStopMusic)(%u)\n", err);
    }
    closeProc = (VoidProc)GetProcAddress(*moduleHandle, wSoundBlasterMsg + 0x15b);
    if (closeProc != 0)
        closeProc();
    GlobalPageUnlock(stateViaSelector.channel0State.channel0.channel0Page);
    GlobalUnwire(stateViaSelector.channel0State.channel0.channel0State);
    GlobalFree(stateViaSelector.channel0State.channel0.channel0State);
    stateViaSelector.channel0State.channel0.channel0State = 0;
    stateViaSelector.channel0State.channel0.channel0Page = 0;
    stateViaSelector.channel0State.songState = 0;
}


