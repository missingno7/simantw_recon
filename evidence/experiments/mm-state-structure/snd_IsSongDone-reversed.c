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
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};

int snd_IsSongDone(void)
{
    if (mmState.moduleHandle == 0 ||
        mmState.waveInstalled != 0 ||
        mmState.soundInstalled != 0)
        return 1;
    return 1 > mmState.songState;
}
