/* Probe a named selector word rather than a compile-time segment name. */
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
extern unsigned int near mmSelector;
extern struct MultimediaState __based(mmSelector) mmState;

int snd_IsSongDone(void)
{
    if (mmState.moduleHandle == 0 ||
        mmState.waveInstalled != 0 ||
        mmState.soundInstalled != 0)
        return 1;
    return mmState.songState == 0;
}
