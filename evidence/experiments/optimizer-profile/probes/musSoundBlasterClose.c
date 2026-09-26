/*
 * Hypothesis: the close handle is a far object whose first word is the
 * 16-bit HGLOBAL passed to GlobalUnwire/GlobalFree; its adjacent selector
 * word is cleared with the object. The added page word follows it. The
 * previously admitted GR_MODULE multimedia prefix and selector view place
 * those observed words at 8d1c/1e/20.
 */
typedef void (far *SoundCloseProc)(void);
struct MultimediaState {
    int moduleHandle;
    int soundInstalled;
    int waveInstalled;
    int midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
    void far *closeHandle;
    unsigned int page;
};
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP"))
    mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)
extern SoundCloseProc far pascal GetProcAddress(int handle, char far *name);
extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);
extern unsigned int far pascal GlobalUnwire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern char near wSoundBlasterMsg[];

void far musSoundBlasterClose(void)
{
    SoundCloseProc proc;

    proc = GetProcAddress(stateViaSelector.moduleHandle,
                          wSoundBlasterMsg + 0x15b);
    if (proc != 0)
        proc();
    GlobalPageUnlock(stateViaSelector.page);
    GlobalUnwire((unsigned int)stateViaSelector.closeHandle);
    GlobalFree((unsigned int)stateViaSelector.closeHandle);
    stateViaSelector.closeHandle = 0;
    stateViaSelector.page = 0;
}
