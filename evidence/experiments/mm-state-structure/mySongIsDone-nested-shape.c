/* Probe whether source nesting places the fast true return before the final test. */
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
    if (songReady != 0 && songsOnFlag != 0) {
        if (soundState.moduleHandle != 0 &&
            soundState.waveInstalled == 0 &&
            soundState.soundInstalled == 0)
            result = soundState.songState == 0;
        else
            result = 1;
    } else {
        return 1;
    }
    return result;
}
