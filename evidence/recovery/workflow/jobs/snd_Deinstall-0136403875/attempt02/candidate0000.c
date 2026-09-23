/* Hypothesis: the routine tears down the multimedia handles recorded in the
   GR_MODULE shared state, resolving optional driver entry points by name. */
typedef int (far *MMProc)(void);
typedef int (far pascal *MCIProc)(int, unsigned int, unsigned long,
                                  unsigned long, void far *);
typedef int (far pascal *WaveCloseProc)(int);
typedef int (far pascal *NoArgProc)(void);
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
struct MCIGeneric { unsigned char data[8]; };
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)
extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern int far pascal GlobalFree(unsigned int handle);
extern int far pascal GlobalPageUnlock(unsigned int handle);
extern int far pascal GlobalUnWire(unsigned int handle);
extern int far pascal FreeLibrary(int module);
extern void far CloseSound(void);
extern void far WinPrintf(char far *text, ...);

void far snd_Deinstall(void)
{
    MMProc proc;
    struct MCIGeneric parms;
    int result;
    int module;`r`n    struct MultimediaState far *state;`r`n    int far *midiHandle;`r`n    int far *waveHandle;

    state = (struct MultimediaState far *)&mmState;`r`n    module = state->moduleHandle;
    if (module != 0 && state->waveInstalled == 0) {
        if (state->soundInstalled != 0) {
            midiHandle = &state->midiHandle;`r`n            if (*midiHandle != 0) {
                proc = GetProcAddress(module, "mciSendCommand");
                WinPrintf("Midi: Close Device\n");
                if (proc != 0)
                    ((MCIProc)proc)(*midiHandle, 0x804,
                                    0L, 0L, (void far *)&parms);
                *midiHandle = 0;
            }
            waveHandle = &state->waveHandle;`r`n            if (*waveHandle != 0) {
                proc = GetProcAddress(module, "waveOutClose");
                if (proc != 0)
                    ((WaveCloseProc)proc)(*waveHandle);
                *waveHandle = 0;
            }
            proc = GetProcAddress(module, "sbcTerminateDLL");
            if (proc != 0)
                ((NoArgProc)proc)();
        }
    }

    if (module != 0 && state->waveInstalled != 0) {
        if (state->soundInstalled != 0) {
            proc = GetProcAddress(module, "waveOutClose");
            WinPrintf("Midi: Close Device\n");
            if (proc != 0) {
                ((MCIProc)proc)(*midiHandle, 0x804,
                                0L, 0L, (void far *)&parms);
                *midiHandle = 0;
            }
        } else {
            proc = GetProcAddress(module, "musStopMusic");
            if (proc != 0) {
                result = ((NoArgProc)proc)();
                if (result != 0)
                    WinPrintf("SBPro Error(musStopMusic)(%u)\n", result);
            }
            proc = GetProcAddress(module, "musCloseDevice");
            if (proc != 0)
                ((NoArgProc)proc)();
            GlobalPageUnlock(state->songState);
            GlobalUnWire(state->songState);
            GlobalFree(state->songState);
            state->songState = 0;
        }
    }

    CloseSound();
    if (module != 0 && state->waveInstalled != 0) {
        proc = GetProcAddress(module, "waveOutClose");
        if (proc != 0) {
            ((WaveCloseProc)proc)(*waveHandle);
            state->waveHandle = 0;
        }
    }
    FreeLibrary(module);
    if (state->songState != 0)
        FreeLibrary(state->songState);
}

