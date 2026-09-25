/*
 * A song is done when the shared song-state block is not active, songs are
 * disabled, or the state does not describe a live song.  The last word is
 * tested as an unsigned value; the historical compiler therefore implements
 * the final zero test with SBB/NEG rather than a high-level boolean helper.
 */
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
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)
extern unsigned int far songState[];
extern int near songsOnFlag;

int mySongIsDone(void)
{
    if (songState[0x4683] == 0)
        goto outer_done;
    if (songsOnFlag == 0)
        goto outer_done;
    if (stateViaSelector.moduleHandle == 0)
        goto inner_done;
    if (stateViaSelector.waveInstalled != 0)
        goto inner_done;
    if (stateViaSelector.soundInstalled == 0)
        goto final_test;

inner_done:
    return 1;

final_test:
    return stateViaSelector.songState == 0;

outer_done:
    return 1;
}
