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
extern void near WinPrintf(char far *, ...);
void far snd_Deinstall(void)
{
    struct MultimediaState far *state;
    int far *handle;
    MMProc proc;
    struct MCIGeneric parms;
    register int result;
    state = (struct MultimediaState far *)&mmState;
    if (state->moduleHandle != 0 && state->waveInstalled == 0) {
        if (state->soundInstalled != 0) {
            handle = &state->midiHandle;
            if (*handle != 0) {
                proc = GetProcAddress(state->moduleHandle, "mciSendCommand");
                WinPrintf("Midi: Close Device\n");
                if (proc != 0) ((MCIProc)proc)(*handle, 0x804, 0L, 0L, (void far *)&parms);
                *handle = 0;
            }
            handle = &state->waveHandle;
            if (*handle != 0) {
                proc = GetProcAddress(state->moduleHandle, "waveOutClose");
                if (proc != 0) ((WaveCloseProc)proc)(*handle);
                *handle = 0;
            }
            proc = GetProcAddress(state->moduleHandle, "sbcTerminateDLL");
            if (proc != 0) ((NoArgProc)proc)();
        }
    }
    if (state->moduleHandle != 0 && state->waveInstalled != 0) {
        if (state->soundInstalled != 0) {
            proc = GetProcAddress(state->moduleHandle, "mciSendCommand");
            WinPrintf("Midi: Close Device\n");
            if (proc != 0) {
                ((MCIProc)proc)(state->midiHandle, 0x804, 0L, 0L, (void far *)&parms);
                state->midiHandle = 0;
            }
        } else {
            proc = GetProcAddress(state->moduleHandle, "musStopMusic");
            if (proc != 0) {
                result = ((NoArgProc)proc)();
                if (result != 0) WinPrintf("SBPro Error(musStopMusic)(%u)\n", result);
            }
            proc = GetProcAddress(state->moduleHandle, "musCloseDevice");
            if (proc != 0) ((NoArgProc)proc)();
            GlobalPageUnlock(state->songState);
            GlobalUnWire(state->songState);
            GlobalFree(state->songState);
            state->songState = 0;
        }
    }
    CloseSound();
    if (state->moduleHandle != 0 && state->waveInstalled != 0) {
        handle = &state->waveHandle;
        if (*handle != 0) {
            proc = GetProcAddress(state->moduleHandle, "waveOutClose");
            if (proc != 0) ((WaveCloseProc)proc)(*handle);
            *handle = 0;
        }
    }
    FreeLibrary(state->moduleHandle);
    if (state->songState != 0) FreeLibrary(state->songState);
}

