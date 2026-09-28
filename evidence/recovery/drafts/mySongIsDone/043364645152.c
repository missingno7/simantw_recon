/* Return one immediately when the shared enable word or near songs flag is
 * clear. Otherwise derive the result from the shared multimedia state record.
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
extern int near songsOnFlag;

int mySongIsDone(void)
{
    int result;
    int __based(mmSelector) *stateWords;

    stateWords = (int __based(mmSelector) *)&mmState;
    if (stateWords[-1] == 0 || songsOnFlag == 0)
        return 1;
    if (stateViaSelector.moduleHandle == 0 ||
        stateViaSelector.waveInstalled != 0)
        result = 1;
    else if (stateViaSelector.soundInstalled != 0)
        result = 1;
    else
        result = stateViaSelector.songState == 0;
    return result;
}
