/* Unit review (gr:7712): GetProcAddress returns the generic far procedure
 * pointer FARPROC (KERNEL.50); each caller converts it to its own procedure
 * type, so the two members share one declaration in the unit. */
/*
 * vocMciClose: release the two voice buffers and, when the last user of
 * the multimedia module goes away, close the wave device.  Two private
 * near flags (unnamed DGROUP words at 0xaf0/0xaf2, zero-initialised after
 * the hanim literals) record whether each buffer handle is locked; a set
 * flag unlocks and frees the corresponding handle (KERNEL ordinals 19 and
 * 17, verified Pascal imports) and clears the flag.  The module reference
 * count, the wave handle and the module handle are unnamed zero words in
 * SIMANT_DATA_GROUP (0x8d1a, 0x8d14, 0x8d08; the module handle is the
 * based static admitted in IsMMWaveAvail, selector 0xbf78).  When the
 * count reaches zero, GetProcAddress (KERNEL 50) resolves "waveOutClose"
 * (wSoundBlasterMsg + 0x179, the near string table used by the verified
 * IsMMWaveAvail) and, if found, the Pascal entry closes the wave handle
 * through a far pointer local; the handle is then cleared.
 */
typedef int (far pascal *FARPROC)();
typedef void (far pascal *MMCloseProc)(int handle);

extern int far pascal GlobalUnlock(unsigned int handle);
extern unsigned int far pascal GlobalFree(unsigned int handle);
extern MMProc far pascal GetProcAddress(int handle, char far *name);
extern char near wSoundBlasterMsg[];

static int near vocBufLocked1 = 0;
static int near vocBufLocked2 = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) mmModule = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) mmWaveHandle = 0;
static int __based(__segname("SIMANT_DATA_GROUP")) mmRefCount = 0;

void far vocMciClose(unsigned int buffer1, unsigned int buffer2)
{
    MMCloseProc proc;

    if (vocBufLocked2) {
        GlobalUnlock(buffer2);
        GlobalFree(buffer2);
        vocBufLocked2 = 0;
    }
    if (vocBufLocked1) {
        GlobalUnlock(buffer1);
        GlobalFree(buffer1);
        vocBufLocked1 = 0;
    }
    if (--mmRefCount == 0) {
        proc = (MMCloseProc)GetProcAddress(mmModule, wSoundBlasterMsg + 0x179);
        if (proc)
            proc(mmWaveHandle);
        mmWaveHandle = 0;
    }
}
