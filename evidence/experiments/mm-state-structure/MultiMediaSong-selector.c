/* The far fields and selector view are controlled by the admitted sound unit. */
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
extern struct MultimediaState __based(mmSelector) soundState;
extern int near songsOnFlag;

int MultiMediaSong(void)
{
    if (songsOnFlag == 0)
        goto inactive;
    if (soundState.moduleHandle == 0)
        goto inactive;
    if (soundState.soundInstalled == 0)
        goto inactive;
    if (soundState.waveInstalled != 0)
        goto inactive;
    if (soundState.midiHandle == 0)
        goto inactive;
    return 1;
inactive:
    return 0;
}
