/* MciMessage: multimedia device callback.  Runs only when both private
 * buffer-lock flags (near words at 0xaf0/0xaf2, the same
 * vocBufLocked1/vocBufLocked2 the admitted vocMciClose body reads) are
 * set; otherwise it is a no-op and returns immediately.  It resolves a
 * first entry point by name through the shared module handle (stateViaSelector.moduleHandle,
 * the based word admitted in IsMMMidiAvail/vocMciClose) and, if found,
 * calls it with the current wave handle (stateViaSelector.waveHandle, 0x8d14).  It then
 * reloads the far parameter block; when the block's status word (offset
 * 0x10, only bits 0xE0 relevant) and its reserved word (offset 0x12) are
 * both zero, it resolves a second entry point and calls it with
 * (stateViaSelector.waveHandle, block, 0x20) -- otherwise (status set) both buffer
 * flags/handles are abandoned without unlocking.  On the normal path,
 * each of the block's two handles (offset 0xc paired with the 0xaf0
 * flag, offset 0xe paired with the 0xaf2 flag) is unlocked and freed
 * (KERNEL GlobalUnlock/GlobalFree) when its flag is set, mirroring
 * vocMciClose's pattern.  When the shared module reference count
 * (stateViaSelector.refCount, 0x8d1a) reaches zero, a third resolved entry point closes
 * the wave handle exactly like vocMciClose.
 */

struct MciBlock {
    int unused[6];          /* +0 .. +0xb */
    unsigned int handle1;   /* +0xc, paired with vocBufLocked1 (0xaf0) */
    unsigned int handle2;   /* +0xe, paired with vocBufLocked2 (0xaf2) */
    unsigned long status;   /* +0x10 .. +0x13 */
};

typedef int (far *MMProc)(void);
typedef int (far pascal *MciProc0)(unsigned int handle);
typedef int (far pascal *MciProc1)(unsigned int handle, struct MciBlock far *block, unsigned int flags);
typedef MciProc0 (far pascal *GetProcAddress0Type)(int handle, char far *name);
typedef MciProc1 (far pascal *GetProcAddress1Type)(int handle, char far *name);

extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern char near wSoundBlasterMsg[2];

static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;
struct MultimediaState {
    int moduleHandle, soundInstalled, waveInstalled, midiHandle;
    void far *midiEntry;
    int waveHandle;
    void far *waveEntry;
    int refCount;
    union {
        unsigned int songState;
        struct { unsigned int closeHandle; void far *pageBuffer; } firstChannel;
        struct { unsigned int channel0Handle; unsigned int channel0State; unsigned int channel0Page; } channel0;
    } channel0State;
    unsigned int closeHandle;
    void far *pageBuffer;
};
static struct MultimediaState __based(__segname("SIMANT_DATA_GROUP")) mmState = {0};
static const __segment near mmSelector = __segname("SIMANT_DATA_GROUP");
#define stateViaSelector (*(struct MultimediaState __based(mmSelector) *)&mmState)

void far MciMessage(unsigned int deviceId, struct MciBlock far *block)
{
    MciProc0 proc0;
    volatile MciProc1 proc1;
    unsigned int handle1;
    unsigned int handle2;


    if (!vocBufLocked2)
        return;
    if (!vocBufLocked1)
        return;

    proc0 = (MciProc0)GetProcAddress(stateViaSelector.moduleHandle, wSoundBlasterMsg + 0x192);
    proc1 = (MciProc1)GetProcAddress(stateViaSelector.moduleHandle, wSoundBlasterMsg + 0x19f);
    if (proc0)
        proc0(stateViaSelector.waveHandle);

    if ((block->status & 0xffffffe0UL) == 0) {
        if (proc1)
            proc1(stateViaSelector.waveHandle, block, 0x20);
        handle1 = block->handle1;
        handle2 = block->handle2;
    } else {
        vocBufLocked2 = 0;
        vocBufLocked1 = 0;
        handle1 = 0;
        handle2 = 0;
    }

    if (vocBufLocked2) {
        GlobalUnlock(handle2);
        GlobalFree(handle2);
        vocBufLocked2 = 0;
    }
    if (vocBufLocked1) {
        GlobalUnlock(handle1);
        GlobalFree(handle1);
        vocBufLocked1 = 0;
    }


    if (--stateViaSelector.refCount == 0) {
        proc1 = (MciProc1)GetProcAddress(stateViaSelector.moduleHandle, wSoundBlasterMsg + 0x179);
        if (proc1)
            ((MciProc0)proc1)(stateViaSelector.waveHandle);
        stateViaSelector.waveHandle = 0;
    }
}
