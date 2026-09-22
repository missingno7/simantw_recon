/* SoundBlasterMessage: multimedia driver-style dispatcher.  wMsg selects
 * one of three cases; any other value (or wMsg>0x28) is a no-op.
 * wMsg==1: resolve an entry point (mmModule, wSoundBlasterMsg+0xc7a-base)
 * and forward dwParam to it.
 * wMsg==0x14 (only when dwParam==0x00050000): resolve a second entry
 * point (wSoundBlasterMsg+0xc5e-base), call it with no arguments, then
 * release the device's wave/buffer handles (0x8d26/0x8d22/0x8d22) and
 * zero 0x8d22/0x8d24/0x8d26.
 * wMsg==0x28 (only when dwParam==0x00000001): the same shape against a
 * second handle set (0x8d1c/0x8d1c/0x8d1c reused, via a third resolved
 * entry point at wSoundBlasterMsg+0xc4f-base) and zero 0x8d1c/0x8d1e/0x8d20.
 */

extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
typedef void (far pascal *SbProc0)(void);
typedef void (far pascal *SbProc1)(unsigned long dwParam);
extern SbProc0 far pascal GetProcAddress(int handle, char far *name);
extern char near wSoundBlasterMsg[];

static int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;

static int __based(__segname("SIMANT_DATA_GROUP")) sbWaveHandleA = 0; /* 0x8d26 */
static int __based(__segname("SIMANT_DATA_GROUP")) sbBufHandleA = 0;  /* 0x8d22 */
static int __based(__segname("SIMANT_DATA_GROUP")) sbFlagA = 0;       /* 0x8d24 */

static int __based(__segname("SIMANT_DATA_GROUP")) sbBufHandleB = 0;  /* 0x8d1c */
static int __based(__segname("SIMANT_DATA_GROUP")) sbWaveHandleB = 0; /* 0x8d20 */
static int __based(__segname("SIMANT_DATA_GROUP")) sbFlagB = 0;       /* 0x8d1e */

void far pascal SoundBlasterMessage(unsigned int wMsg, unsigned long dwParam)
{
    SbProc1 proc1;
    SbProc0 proc0;

    if (wMsg == 1) {
        proc1 = (SbProc1)GetProcAddress(mmModule, wSoundBlasterMsg + 0x186);
        if (proc1)
            proc1(dwParam);
        return;
    }

    if (wMsg == 0x14) {
        if (dwParam != 0x50000L)
            return;
        proc0 = GetProcAddress(mmModule, wSoundBlasterMsg + 0x16a);
        if (proc0)
            proc0();
        GlobalUnlock(sbWaveHandleA);
        GlobalFree(sbBufHandleA);
        GlobalFree(sbBufHandleA);
        sbBufHandleA = 0;
        sbWaveHandleA = 0;
        sbFlagA = 0;
        return;
    }

    if (wMsg == 0x28) {
        if (dwParam != 1L)
            return;
        proc0 = GetProcAddress(mmModule, wSoundBlasterMsg + 0x15b);
        if (proc0)
            proc0();
        GlobalUnlock(sbBufHandleB);
        GlobalFree(sbBufHandleB);
        GlobalFree(sbBufHandleB);
        sbBufHandleB = 0;
        sbWaveHandleB = 0;
        sbFlagB = 0;
        return;
    }
}
