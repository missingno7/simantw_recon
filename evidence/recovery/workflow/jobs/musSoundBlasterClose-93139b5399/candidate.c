/*
 * Hypothesis: resolve the Sound Blaster close entry point from the private
 * multimedia module handle, call it when present, release the private page,
 * unwire and free handles, then clear the three handle words.  The based
 * record follows the observed SIMANT_DATA_GROUP offsets: module at 8d08,
 * handle at 8d1c, and the remaining words at 8d1e and 8d20.  The GetProc
 * name is the verified wSoundBlasterMsg object at 0af4 plus 15b = 0c4f.
 */
typedef void (far *SoundCloseProc)(void);

static unsigned int __based(__segname("SIMANT_DATA_GROUP")) soundModule = 0;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) soundHandle = 0;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) soundStateWord = 0;
static unsigned int __based(__segname("SIMANT_DATA_GROUP")) soundPage = 0;

extern SoundCloseProc far pascal GetProcAddress(int handle,
                                                char far *name);
extern unsigned int far pascal GlobalPageUnlock(unsigned int handle);
extern unsigned int far pascal GlobalUnwire(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern char near wSoundBlasterMsg[];

void far musSoundBlasterClose(void)
{
    SoundCloseProc proc;

    proc = GetProcAddress(soundModule, wSoundBlasterMsg + 0x15b);
    if (proc == 0)
        return;

    proc();
    GlobalPageUnlock(soundPage);
    GlobalUnwire(soundHandle);
    GlobalFree(soundHandle);
    soundHandle = 0;
    soundPage = 0;
    soundStateWord = 0;
}
