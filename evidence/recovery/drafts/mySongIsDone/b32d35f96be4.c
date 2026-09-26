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
    int result=1;
    int __based(mmSelector) *stateWords; stateWords=(int __based(mmSelector) *)&mmState; if (stateWords[-1] == 0) goto early;
    if (songsOnFlag == 0 || stateViaSelector.moduleHandle == 0 || stateViaSelector.waveInstalled != 0 || stateViaSelector.soundInstalled == 0) goto early;
finish:
    result=stateViaSelector.songState == 0;
    return result;
early:
    return result;
}
