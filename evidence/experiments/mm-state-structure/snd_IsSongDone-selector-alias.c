/* Test a selector-based view over the same far state object. */
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
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)

int snd_IsSongDone(void)
{
    if (stateViaSelector.moduleHandle == 0 ||
        stateViaSelector.waveInstalled != 0 ||
        stateViaSelector.soundInstalled != 0)
        return 1;
    return stateViaSelector.songState == 0;
}
