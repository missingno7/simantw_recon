/* Probe control flow with the observed 8D06 word kept in a separate declaration. */
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
extern __segment near mmSelector;
extern int __based(mmSelector) songReady;
extern struct MultimediaState __based(mmSelector) soundState;
extern int near songsOnFlag;

int mySongIsDone(void)
{
    int result;
    if (songReady == 0 || songsOnFlag == 0)
        return 1;
    if (soundState.moduleHandle == 0 ||
        soundState.waveInstalled != 0 ||
        soundState.soundInstalled != 0)
        result = 1;
    else
        result = soundState.songState == 0;
    return result;
}
