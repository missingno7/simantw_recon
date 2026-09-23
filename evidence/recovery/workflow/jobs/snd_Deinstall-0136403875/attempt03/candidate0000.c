/* Hypothesis: retain the selector-derived far pointer and field addresses as locals,
   matching the target's saved ES:BX pairs for the state and two handles. */
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
    unsigned int songState;
};
struct MCIGeneric { unsigned char data[8]; };
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
extern MMProc far pascal GetProcAddress(int, char far *);
extern int far pascal GlobalFree(unsigned int);
extern int far pascal GlobalPageUnlock(unsigned int);
extern int far pascal GlobalUnWire(unsigned int);
extern int far pascal FreeLibrary(int);
extern void far CloseSound(void);
extern void far WinPrintf(char far *, ...);
void far snd_Deinstall(void)
{
    struct MultimediaState far *state;
    int far *midiHandle;
    int far *waveHandle;
    MMProc proc;
    struct MCIGeneric parms;
    int module, result;
    state = (struct MultimediaState far *)&mmState;
    midiHandle = &state->midiHandle;
    waveHandle = &state->waveHandle;
    module = state->moduleHandle;
    if (module != 0 && state->waveInstalled == 0) {
        if (state->soundInstalled != 0) {
            if (*midiHandle != 0) {
                proc = GetProcAddress(module, "mciSendCommand");
                WinPrintf("Midi: Close Device\n");
                if (proc != 0) ((MCIProc)proc)(*midiHandle, 0x804, 0L, 0L, (void far *)&parms);
                *midiHandle = 0;
            }
            if (*waveHandle != 0) {
                proc = GetProcAddress(module, "waveOutClose");
                if (proc != 0) ((WaveCloseProc)proc)(*waveHandle);
                *waveHandle = 0;
            }
            proc = GetProcAddress(module, "sbcTerminateDLL");
            if (proc != 0) ((NoArgProc)proc)();
        }
    }
    if (module != 0 && state->waveInstalled != 0) {
        if (state->soundInstalled != 0) {
            proc = GetProcAddress(module, "mciSendCommand");
            WinPrintf("Midi: Close Device\n");
            if (proc != 0) {
                ((MCIProc)proc)(state->midiHandle, 0x804, 0L, 0L, (void far *)&parms);
                state->midiHandle = 0;
            }
        } else {
            proc = GetProcAddress(module, "musStopMusic");
            if (proc != 0) {
                result = ((NoArgProc)proc)();
                if (result != 0) WinPrintf("SBPro Error(musStopMusic)(%u)\n", result);
            }
            proc = GetProcAddress(module, "musCloseDevice");
            if (proc != 0) ((NoArgProc)proc)();
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
            *waveHandle = 0;
        }
    }
    FreeLibrary(module);
    if (state->songState != 0) FreeLibrary(state->songState);
}
