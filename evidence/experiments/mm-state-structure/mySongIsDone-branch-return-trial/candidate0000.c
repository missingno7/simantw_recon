/* Test branch-local return before the final song-state test. */
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
        goto outer_done;
    if (soundState.moduleHandle == 0 ||
        soundState.waveInstalled != 0)
        goto inner_done;
    if (soundState.soundInstalled == 0)
        goto final_test;
inner_done:
    result = 1;
    return result;
final_test:
    result = soundState.songState == 0;
    return result;
outer_done:
    return 1;
}
