/* Channel zero occupies three words before the channel-one WORD/FAR pair. */
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
    unsigned int channel0Handle;
    unsigned int channel0State;
    unsigned int channel0Page;
    unsigned int closeHandle;
    void far *pageBuffer;
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

void far vocSoundBlasterClose(void)
{
    SoundCloseProc proc;

    proc = GetProcAddress(stateViaSelector.moduleHandle,
                          wSoundBlasterMsg + 0x16a);
    if (proc != 0)
        proc();
    GlobalPageUnlock((unsigned int)((unsigned long)stateViaSelector.pageBuffer >> 16));
    GlobalUnwire(stateViaSelector.closeHandle);
    GlobalFree(stateViaSelector.closeHandle);
    stateViaSelector.closeHandle = 0;
    stateViaSelector.pageBuffer = 0;
}