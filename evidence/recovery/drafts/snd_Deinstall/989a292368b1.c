/* Hypothesis: take the original far state view once, and take each far field
   address only at the branch where the original uses LES into a saved pair. */
typedef int (far *MMProc)(void);
typedef int (far pascal *MCIProc)(int, unsigned int, unsigned long, unsigned long, void far *);
typedef int (far pascal *WaveCloseProc)(int);
typedef int (far pascal *NoArgProc)(void);
struct MultimediaState {
    int moduleHandle, soundInstalled, waveInstalled, midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
    union {
        unsigned int songState;
        struct { unsigned int closeHandle; void far *pageBuffer; } firstChannel;
        struct { unsigned int channel0Handle; unsigned int channel0State; unsigned int channel0Page; } channel0;
    } channel0State;
    unsigned int closeHandle;
    void far *pageBuffer;
    int soundModuleHandle;
};
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)
struct MCIGeneric { unsigned char data[8]; };
extern MMProc far pascal GetProcAddress(int, char far *);
extern unsigned int far pascal GlobalFree(unsigned int handle);

extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);

extern int far pascal GlobalUnWire(unsigned int);
extern int far pascal FreeLibrary(int);
extern void far CloseSound(void);
extern void far WinPrintf(char far *, ...);
void far snd_Deinstall(void)
{
    int far *moduleHandle;
    int far *midiHandle;
    int far *waveHandle;
    MMProc proc;
    struct MCIGeneric parms;
    register int result;

    moduleHandle = &stateViaSelector.moduleHandle;
    if (*moduleHandle != 0 && stateViaSelector.waveInstalled == 0) {
        if (stateViaSelector.soundInstalled != 0) {
            midiHandle = &stateViaSelector.midiHandle;
            if (*midiHandle != 0) {
                proc = GetProcAddress(*moduleHandle, "mciSendCommand");
                WinPrintf("Midi: Close Device\n");
                if (proc != 0)
                    ((MCIProc)proc)(*midiHandle, 0x804, 0L, 0L, (void far *)&parms);
                *midiHandle = 0;
            }
            waveHandle = &stateViaSelector.waveHandle;
            if (*waveHandle != 0) {
                proc = GetProcAddress(*moduleHandle, "waveOutClose");
                if (proc != 0)
                    ((WaveCloseProc)proc)(*waveHandle);
                *waveHandle = 0;
            }
            proc = GetProcAddress(*moduleHandle, "sbcTerminateDLL");
            if (proc != 0) ((NoArgProc)proc)();
        }
    }
    if (*moduleHandle != 0 && stateViaSelector.waveInstalled != 0) {
        if (stateViaSelector.soundInstalled != 0) {
            proc = GetProcAddress(*moduleHandle, "mciSendCommand");
            WinPrintf("Midi: Close Device\n");
            if (proc != 0) {
                ((MCIProc)proc)(stateViaSelector.midiHandle, 0x804, 0L, 0L, (void far *)&parms);
                stateViaSelector.midiHandle = 0;
            }
        } else {
            proc = GetProcAddress(*moduleHandle, "musStopMusic");
            if (proc != 0) {
                result = ((NoArgProc)proc)();
                if (result != 0) WinPrintf("SBPro Error(musStopMusic)(%u)\n", result);
            }
            proc = GetProcAddress(*moduleHandle, "musCloseDevice");
            if (proc != 0) ((NoArgProc)proc)();
            GlobalPageUnlock(stateViaSelector.channel0State.channel0.channel0Page);
            GlobalUnWire(stateViaSelector.channel0State.channel0.channel0Handle);
            GlobalFree(stateViaSelector.channel0State.channel0.channel0Handle);
            stateViaSelector.channel0State.channel0.channel0Handle = 0;
            stateViaSelector.channel0State.channel0.channel0State = 0;
            stateViaSelector.channel0State.channel0.channel0Page = 0;
        }
    }
    CloseSound();
    if (*moduleHandle != 0 && stateViaSelector.waveInstalled != 0) {
        waveHandle = &stateViaSelector.waveHandle;
        if (*waveHandle != 0) {
            proc = GetProcAddress(*moduleHandle, "waveOutClose");
            if (proc != 0)
                ((WaveCloseProc)proc)(*waveHandle);
            *waveHandle = 0;
        }
    }
    if (stateViaSelector.soundModuleHandle != 0)
        FreeLibrary(stateViaSelector.soundModuleHandle);
}
