/*
 * Hypothesis: resolve and invoke the voice Sound Blaster close procedure
 * through the private multimedia module handle, release its page and data
 * handles, then clear the three observed state words.  The paired close
 * routine establishes wSoundBlasterMsg + 0x16a = DS:0xc5e; the ES offsets
 * below are taken directly from this target's selector-liveness packet.
 * Exact proof still requires the historical private state declaration that
 * emits the direct BF78 selector loads.
 */
typedef void (far *SoundCloseProc)(void);

struct VoiceSoundState {
    unsigned int module;
    unsigned char reserved[0x14];
    unsigned int handle;
    unsigned int stateWord;
    unsigned int page;
};

static struct VoiceSoundState __based(__segname("SIMANT_DATA_GROUP"))
    voiceSoundState = { 0, { 0 }, 0, 0, 0 };

extern SoundCloseProc far pascal GetProcAddress(int handle,
                                                char far *name);
extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);
extern unsigned int far pascal GlobalUnwire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern char near wSoundBlasterMsg[];

void far vocSoundBlasterClose(void)
{
    SoundCloseProc proc;

    proc = GetProcAddress(voiceSoundState.module,
                          wSoundBlasterMsg + 0x16a);
    if (proc == 0)
        return;

    proc();
    GlobalPageUnlock(voiceSoundState.page);
    GlobalUnwire(voiceSoundState.handle);
    GlobalFree(voiceSoundState.handle);
    voiceSoundState.handle = 0;
    voiceSoundState.page = 0;
    voiceSoundState.stateWord = 0;
}
