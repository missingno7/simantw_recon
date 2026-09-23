/* Probe whether a far object declaration explains the selector load. */
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
extern struct MultimediaState far mmState;

int snd_IsSongDone(void)
{
    if (mmState.moduleHandle == 0 ||
        mmState.waveInstalled != 0 ||
        mmState.soundInstalled != 0)
        return 1;
    return mmState.songState == 0;
}
