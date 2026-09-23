/* Test whether a near selector with an authentic segment relocation can own the far state. */
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
static __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
static struct MultimediaState __based(mmSelector) mmState = {0};

int snd_IsSongDone(void)
{
    if (mmState.moduleHandle == 0 ||
        mmState.waveInstalled != 0 ||
        mmState.soundInstalled != 0)
        return 1;
    return mmState.songState == 0;
}
